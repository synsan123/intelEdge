/* �κ� ��� ���� */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	/* ��ȣ () ������ ������ �̿�, �޸� ���� Ȯ���� �ƴ� �ȼ� �����͸� �����ϴ� ���� ������ */
	Mat img1 = imread("cat.bmp");

	/* �̹��� �ҷ����� ���� �� ���α׷� ���� */
	if (img1.empty())
	{
		cerr << "Image Load Fail" << endl;
		return -1;
	}

	/* (220, 120) ��ǥ�κ��� 340 x 240 ũ�⸸ŭ�� �簢�� */
	Mat img2 = img1(Rect(220, 120, 340, 240)); // Rect Ŭ������ �̿��� �簢�� ���ɿ��� ����
	
	/* ������ ���� */
	/* �κ� ���� ���� �� �ȼ� �����͸� �����Ѵٴ� Ư���� �̿��ϸ� �Է� ������ �Ϻκп��� Ư���� ����ó���� ������ �� ����*/
	//img2 = ~img2;

	imshow("img1", img1);
	imshow("img2", img2);

	/* clone�� �̿��� ���� ���� �� �κ� ���� ���� */
	Mat img3 = img1(Rect(220, 120, 240, 240)).clone();
	// img3 = ~img3; // ������ �ص� img1���� ������� ����

	imshow("img3", img3);

	waitKey();
	destroyAllWindows();
	//�̿ܿ��� rowRange, colRange, row, col�� ����
	return 0;
}