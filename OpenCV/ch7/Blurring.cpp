/* ���� : ���� �ε巴�� �ϱ� */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* ��հ� ���� */
#if 0
int main()
{
	/* ������ �ε巴�� ��. �������̶�� ��. */
	/* ������ �ȼ� ���� �ȼ� �� ��ȭ�� ũ�� ���� ��� �ε巯�� ������ ���� */
	/* ������ �����ϴ� ��ó�� �������ε� ���� */
	
	/* ��հ� ���� */
	/* �Է� ���󿡼� Ư�� �ȼ��� �ֺ� �ȼ����� ��� ����� ��� ���� �ȼ� ������ �����ϴ� ���� */
	/* �ȼ����� ���� 1 / n x n ��*/
	/* �����ϰ� ��� �� �繰�� ��谡 �帴������ �繰�� ������ ������� */
	/* blur(src, dst, ksize, anchor, borderType) => ksize�� ���� Ŀ�� ũ�� */
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	imshow("src", src);

	Mat dst;
	for (int ksize = 3; ksize <= 7; ksize += 2) {
		blur(src, dst, Size(ksize, ksize));

		String desc = format("Mean: %d x %d", ksize, ksize);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
	return 0;
}
#endif

/* ����þ� ���� */
int main()
{
	/* ����þ� ������ ����� �߽����� �¿� ��Ī�� �� ����� ���� Ȯ�� ������ ���ϸ� ���� ������� �Ѵ�. */
	/* ��հ� ǥ�� ������ ���� ���� ����� ������ */
	/* ǥ�� ������ Ŭ���� �а� ������ �ϸ�����, �ݴ�� �������� */
	/* ����þ� ���� ����ũ�� ��������� ���ϱ� ���� ����ġ ��� ������ �� */
	/* GaussianBlur(src, dst, ksize, sigmaX, sigmaY = 0, borderType) */
	/* ksize = ����þ� Ŀ�� ũ��, sigma = ǥ������. sigmaY = 0 �̸� sigmaX�� ���� ǥ������ ��� */
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	imshow("src", src);

	Mat dst;
	for (int sigma = 1; sigma <= 5; sigma++) {
		GaussianBlur(src, dst, Size(), (double)sigma);

		String text = format("sigma = %d", sigma);
		putText(dst, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}