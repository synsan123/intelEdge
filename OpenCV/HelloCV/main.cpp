#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	cout << "Hello OpenCV " << CV_VERSION << endl;

	Mat img;
	img = imread("lenna.bmp"); // imread = image read (�̹��� �ҷ�����)

	if (img.empty()) // MatŬ������ empty�Լ��� ������ �ҷ����� ���� ��� true�� ��ȯ
	{
		cerr << "Image load Failed" << endl;
		return -1;
	}

	namedWindow("image"); //namedWindow�Լ��� �̿��Ͽ� ������ ȭ�鿡 ��Ÿ���� ���� ���ο� â�� ���� �� image��� �̸��� �ο�
	imshow("image", img); // image show (�̹��� �����ֱ�), img��ü�� ������ �ִ� lenna.bmp ������ ���

	vector<int> params;
	params.push_back(IMWRITE_JPEG_QUALITY);
	params.push_back(95);
	imwrite("lenna.jpg", img, params);
	imwrite("lenna.png", img);

	waitKey(); // ������� Ű���� �Է��� ��ٸ��� �Լ�. ������ ������ ������ ȭ�鿡 ������.
	return 0;
}