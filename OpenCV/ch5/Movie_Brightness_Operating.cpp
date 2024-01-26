/* ������ ��� ���� */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;


#if 0
int main()
{
	/* ���� ���� ���ϰų� ���� ��⸦ ������ */
	/* ������ ��� ������ ������ ���� ��ȭ������ ����Ͽ��� �� */
	/* ��ȭ����(Ư������ �ѱ��� ���ϰ� �ϴ� ��)�� ���� 255�� �Ѿ ��� 255�� ����. 0���� ���� ��� 0���� �����ϴ� ���� �� �� ���� */
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	Mat dst = src + 100;
	Mat dst1 = src - 100;
	//�ڱ��ڽſ��� ����� ���� ������ ���� += �����ڸ� ���
	// src += 100;
	// add�Լ��� subtract�Լ��� ����� �� ����
	// add(src, 100, dst) or subtract(src, 100, dst)

	imshow("src", src);
	imshow("dst", dst);
	imshow("dst1", dst1);

	waitKey();
	destroyAllWindows();

	return 0;
}
#endif


/* ������ ��� ���� ���� ����, �˾Ƶθ� ���� */
/* Mat ����� ���� �� ���� ����� ��� */
int main()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	Mat dst(src.rows, src.cols, src.type()); // src�� ũ��, Ÿ���� ���� ��� ������ ����

	for (int j = 0; j < src.rows; j++) { // ���� ��ü ��ĵ �� �Է� ������ �ȼ� ���� 100�� ���Ͽ� ��� ���� �ȼ� ������ ���� 
		for (int i = 0; i < src.cols; i++) {
			// int v = src.at<uchar>(j, i) + 100;
			/* ��ȭ ������ ���� */
			/* v > 255�̸� 255 �ƴϸ� v < 0? ���� ���� �ٽ� v�� 0���� ������ 0 �ƴϸ� v */
			/* �Ʒ��� �� ���� ���� �ۼ�������. �׷��� OpenCV�� ��ȭ������ �����ϴ� ĳ���� �Լ��� saturate_cast �Լ��� ������*/
			// dst.at<uchar>(j, i) = v > 255 ? 255 : v < 0 ? 0 : v; // ���� ���� �����ڸ� �ߺ� 
			// dst.at<uchar>(j, i) = saturate_cast<uchar>(v);
			/* ���������δ� �Ʒ��� ���� �ۼ� ���� */
			dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + 100);
		}
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();

	return 0;
}
