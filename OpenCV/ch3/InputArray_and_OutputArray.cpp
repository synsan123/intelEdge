/* InputArray�� OutputArray Ŭ���� */
/* OpenCV�Լ��� �Է°� ������� ���Ǵ� �������̽� Ŭ���� */
/* ����ڰ� ���� InputArray, OutputArrayŸ���� ������ �����ؼ��� �ȵ� */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

/* InputArrayŬ���� Ÿ���� ���ڸ� ����ϴ� �Լ��� �����ϴ� ����� ���� ��� ����� ������ */
void printMat(InputArray _mat)
{
	Mat mat = _mat.getMat(); //getMat(int idx = -1)�Լ��� idx�� ������ �� ��ȣ�̰� idx < 0�̸� ��� ��ü�� ����
	cout << mat << endl;	
}

int main()
{
	uchar data1[] = { 1,2,3,4,5,6 };
	Mat mat1(2, 3, CV_8U, data1);
	printMat(mat1);

	vector<float> vec1 = { 1.2f, 3.4f, -2.1f };
	printMat(vec1);
}