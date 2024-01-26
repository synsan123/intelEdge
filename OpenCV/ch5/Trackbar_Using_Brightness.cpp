/* Ʈ���ٸ� �̿��� ������ ��� ���� */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void on_brightness(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;

	imshow("dst", dst); // Ʈ���� �ݹ� �Լ����� ��� ������ ��� ���� dst�� ȭ�鿡 ���
}

int main()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	namedWindow("dst");
	createTrackbar("Brightness", "dst", 0, 100, on_brightness, (void*)&src);
	on_brightness(0, (void*)&src); // dstâ�� ���� ������ ���������� ǥ�õǵ��� ������ on_brightness �Լ��� ȣ��. ������ Ʈ���� ������ �� ���� 

	waitKey();
	destroyAllWindows();

	return 0;
}