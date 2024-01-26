/* GrayScale ���� �ٷ�� */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	/* GrayScale ������ Mat ��ü�� �����ϴ� ��� */
	Mat img1 = imread("lenna.bmp",IMREAD_GRAYSCALE);
	Mat img2(480, 640, CV_8UC1, Scalar(0)); // ��� �ȼ� ���� 0(black)���� �ʱ�ȭ�� 640x480 GrayScale ����
	Mat img3 = imread("lenna.bmp", IMREAD_COLOR);

	/* cvtColor�Լ��� Mat ��ü�� ����� ���� ������ ������ �� ����ϴ� �Լ� */
	/* (�Է¿���, ��¿���, �÷� ��ȯ �ڵ�) */
	Mat img4;
	cvtColor(img3, img4, COLOR_BGR2GRAY); 

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
	imshow("img4", img4);

	waitKey();
	destroyAllWindows();
}