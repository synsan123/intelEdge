/* ������ ���͸� */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main()
{
	/* ����ũ��� �θ��� ���� ũ���� ����� �̿�. ����ũ(= Ŀ��, ������, ����) */
	/* ����ũ�� ��� ���Ҵ� ���� �Ǽ��� ������. �پ��� ����� ���� ����ũ �� 3x3�� ���� ���� ��� */
	/* ������ = ����ũ ��� ���߾� */
	/* ����ũ ���� = ����ũ ��� ���� ���� ���� ��ġ�� �ִ� �Է� ���� �ȼ� ���� ���� ��, �� ����� ��� ���ϴ� ���� */
	/* ������ �����ڸ� �ȼ������� ������ �����ϱ� ����� Ư���� ó���� �ؾ� �� */
	/* �����ڸ� �ȼ��� Ȯ���Ͽ� �ٱ��ʿ� ������ �ȼ��� ���� */
	/* ���� ������ �ȼ� ���� ��Ī ���·� ��Ÿ������ ���� */
	/* BORDER_CONSTANT, BORDER_REPLICATE, BORDER_REFLECT, BORDER_REFLECT_101 ������ ���� */
	/* filter2D(src, dst, ddepth, kernel, anchor, delta, bordertype) */
	/* kernel = ���͸� Ŀ��(1ä�� �Ǽ��� ���), anchor(������ ��ǥ. (-1,-1)�� default) */
	/* ddepth�� -1�� �����ϸ� ��� ������ ���̴� �Է� ����� ���� ��.(248p ����) */
	
	/* filter2D�� �̿��Ͽ� ������ ���͸��� �����ϴ� ���� */
	/* ���� ���� ���� ��ȭ���꿡 ���� 0�� �Ǿ� ������ ������ ��ü���� �پ��� ��� ���� 128�� ���ϴ� ���� ���� ���� */
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	/* data �迭�� �̿��Ͽ� 3x3ũ���� ������ ���� ����ũ ��� ���� */
	float data[] = { -1, -1, 0, -1, 0, 1, 0, 1, 1 };
	Mat emboss(3, 3, CV_32FC1, data);

	Mat dst;
	filter2D(src, dst, -1, emboss, Point(-1, -1), 128);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();

	return 0;
}