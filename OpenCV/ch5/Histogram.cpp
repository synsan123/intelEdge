/* ������׷� */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

Mat calcGrayHist(const Mat& img)
{
	CV_Assert(img.type() == CV_8UC1); // CV_Assert��ũ���Լ��� �̿��Ͽ� img������ �׷��̽��������� �˻�

	Mat hist;  // ������׷� ������ ������ Mat Ÿ���� ����
	int channels[] = { 0 }; // �׷��̽������� ä���� 1��
	int dims = 1; // �ϳ��� ä�ο� ���ؼ��� ����. 1���� ��� 
	const int histSize[] = { 256 }; // �Է� ������ ù ��° ä�� ���� ������ 256�� ��(���ΰ�)���� ������ ������׷��� ���ϰڴ�
	float graylevel[] = { 0,256 }; // �׷��̽������� �ּڰ��� �ִ밪�� ���ʴ�� ����
	const float* ranges[] = { graylevel }; // graylevel�迭 �̸��� ���ҷ� ���� �迭

	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);

	return hist; // CV_32FC1 Ÿ���� ���� 256 x 1 ũ���� ���
}

Mat getGrayHistImage(const Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	double histMax;
	minMaxLoc(hist, 0, &histMax); // hist��� ������ �ִ��� histMax������ ����

	Mat imgHist(100, 256, CV_8UC1, Scalar(255)); // ������� �ʱ�ȭ�� 256 x 100ũ���� �� ���� imgHist�� ����
	for (int i = 0; i < 256; i++) { // ������ �� ���� ������׷� �׷����� �׸� 
		line(imgHist, Point(i, 100), Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
	}

	return imgHist;
}

void histogram_stretching()
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);

	Mat dst = (src - gmin) * 255 / (gmax - gmin);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}

#if 0
int main()
{
	/* ������ �ȼ� �� ������ �׷��� ���·� ������ �� */
	/* calcHist�Լ��� ��� */
	/* (�Է� ������ �迭 �Ǵ� �Է� ������ �ּ�, �Է� ���� ����, ������׷��� ���� ä��, ����ũ ����, ��� ������׷�, ��� ������׷� ���� ��
	, �� ������ ������׷� �迭 ũ�⸦ ��Ÿ���� �迭, �� ������ ������׷� ����, ������׷� ���� ������ �յ������� ��Ÿ���� �÷���, ���� �÷���) */ 
	/* (images, nimages, channels, mask, hist, dims, histSize, ranges, uniform, accumulate) */

	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	Mat src1 = src + 30;
	Mat hist = calcGrayHist(src);
	Mat hist_img = getGrayHistImage(hist);

	imshow("src", src);
	imshow("src1", src1);
	imshow("srcHist", hist_img);
	imshow("srcHist1", getGrayHistImage(calcGrayHist(src))); // hist�� hist_img�� �������� �ʰ� ����
	imshow("src1Hist1", getGrayHistImage(calcGrayHist(src1)));
	waitKey();
	destroyAllWindows();

	return 0;
 }
#endif


int main()
{
	/* ������׷� ��Ʈ��Ī */
	/* ������ ������׷��� �׷��̽����� �� ������ ���ļ� ��Ÿ������ �����ϴ� ���� ��ȯ ��� */
	/* ��Ϻ� ������ */
	// histogram_stretching();

	/* ������׷� ��Ȱȭ */ /* ��Ʈ��Ī�� ���������� ��Ϻ� ������ */
	/* Ư�� �׷��̽����� �� �ٹ濡�� �ȼ� ������ �ʹ� ���� ���� �ִ� ��� �̸� ���� ���� �ִ� ������� �ȼ� �� ������ ���� */
	/* ��Ʈ��Ī�� �޸� ��Ȱȭ�� equalizHist(�Է¿����� CV_8UC1�� ����, ��� ����) �Լ��� ������ */
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "fail" << endl;
		return -1;
	}

	Mat dst;
	equalizeHist(src, dst);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
	
	return 0;
}