/* ��� ���� �����ϱ� */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	/* Mat ��ü���� ���� ���� �����ϴ� ������ ��� �Ǵ� ������ ũ�� ���� */
	/* Mat ��ü�� ����� ��� �Ӽ� ���� */
	Mat img1 = imread("lenna.bmp");
	if (img1.empty())
	{
		cerr << "Image Read Fail" << endl;
		return -1;
	}

	cout << "Width : " << img1.cols << endl; // ���� �ȼ� ũ��
	cout << "Height : " << img1.rows << endl; // ���� �ȼ� ũ�� 
	
	if (img1.type() == CV_8UC1)
		cout << "img1 is a GrayScale Image" << endl;
	else if (img1.type() == CV_8UC3)
		cout << "img1 is a True Color Image" << endl;

	cout << "Channel : " << img1.channels() << endl;
	cout << "Type : " << img1.type() << endl;
	cout << "Depth : " << img1.depth() << endl;
	cout << "All-channel 1-memory Memory Size : " << img1.elemSize() << endl; // 1byte x 3 = 3
	cout << "1-channel 1-element Memory Size : " << img1.elemSize1() << endl; // 1byte
	cout << "Size : " << img1.size() << endl;
	cout << "Total element : " << img1.total() << endl;

	/* ��� ���� �� ��� */
	/* cout �� << ������ �����Ǹ� �̿��Ͽ� ��� */
	float data[] = { 2.f, 1.414f, 3.f, 1.732f };
	Mat mat1(2, 2, CV_32FC1, data);
	cout << mat1 << endl;

	return 0;
}
