/* ���� ���� ���͸� */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* ����þ� ���� �� */
/* ���� ������ �߰��� */
/* randn(dst, mean, stddev) => ��¿���, ���, ǥ������ */
/* dst����� ����þ� ������ ������ ������ ä�� */
void noise_gaussian()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	imshow("src", src);

	for (int stddev = 10; stddev <= 30; stddev += 10) {
		Mat noise(src.size(), CV_32SC1);
		randn(noise, 0, stddev);

		Mat dst;
		add(src, noise, dst, Mat(), CV_8U);

		String desc = format("stddev = %d", stddev);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();

}


/* ����� ���� */
/* ���� ������ �״�� �����ϸ鼭 ����þ� ������ ȿ�������� �����ϴ� �˰��� */
/* bilateralFilter(src, dst, d, sigmaColor, sigmaSpace, borderType) => d = ���͸��� ����� �̼� �ȼ����� �Ÿ�, -1�̸� sigmaSpace�κ��� �ڵ� ���*/
/* sigmaColor���� �۰� �����ϸ� �ȼ� �� ���̰� ū �ֺ� �ȼ����� ������ ���� �ȵ� */
/* �ݸ鿡 ũ�� �ϸ� �ȼ� �� ���̰� ���� ũ���� ������ �����, �̸� �̿��Ͽ� ��� ���� ��� ���� ���� ������ ������ ������ ���� ���� */
void filter_bilateral()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	/* src�� ������ �߰��� */
	Mat noise(src.size(), CV_32SC1);
	randn(noise, 0, 5);
	add(src, noise, src, Mat(), CV_8U);

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 5);

	Mat dst2;
	bilateralFilter(src, dst2, -1, 10, 5);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}

/* �̵�� ���� */
/* �Է� ���󿡼� �ڱ� �ڽ� �ȼ��� �ֺ� �ȼ� �� �߿��� �߰����� �����Ͽ� ��� ���� �ȼ� ������ �����ϴ� ���͸� ��� */
/* ���� �߰��Ǵ� ���� �߿� �ұ�&���� ������ �ȼ� ���� ���� Ȯ���� 0 �Ǵ� 255�� ����Ǵ� ������ ���� */
/* medianBlur(src, dst, ksize) */
void filter_median()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	int num = (int)(src.total() * 0.1);
	for (int i = 0; i < num; i++) {
		int x = rand() % src.cols;
		int y = rand() % src.rows;
		src.at<uchar>(y, x) = (i * 2) * 255;
	}

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 1);

	Mat dst2;
	medianBlur(src, dst2, 3);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}

int main()
{
	// noise_gaussian();
	// filter_bilateral();
	filter_median();
	return 0;
}