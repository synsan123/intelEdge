/* ����� ���� �� ���� */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	/* ���� �������� ��� ���� ���� ��� at�Լ� */
	/* y��° ��, x��° ���� ���� �� ���� �������� ��� (��� ���� �ڷ��� ����� ���� �ʿ�) */
	Mat mat1 = Mat::zeros(3, 4, CV_8UC1);

	for (int j = 0; j < mat1.rows; j++) {
		for (int i = 0; i < mat1.cols; i++) {
			mat1.at<uchar>(j, i)++; // uchar = unsigend char = 8U (��� ���� �ڷ��� ����� ����)
		}
	}
	cout << mat1 << endl;

	/* ptr�Լ�, Ư�� ���� ù ��° ���� �ּ�(y��° ���� ���� �ּ� �� ������)�� ��ȯ. ���� �θ� ����ϴ� ptr�Լ� ������ ���� */
	/* at�� ���������� ���ø� �Լ��̱⿡ �ڷ����� ��������� ��������� �Ѵ�. */
	for (int j = 0; j < mat1.rows; j++) {
		uchar* p = mat1.ptr<uchar>(j);
		for (int i = 0; i < mat1.cols; i++) {
			p[i]++;
		}
	}
	cout << mat1 << endl;

	/* MatIterator_(�ݺ��� Ŭ����), ���ø����� ����. Mat::begin�Լ��� �̿��Ͽ� ù ��° ���� ��ġ, end�Լ��� �̿��Ͽ� ������ ���� ��ġ ���� */
	/* ����� ��� ���ҿ� �����ϴ� ����� ���� */
	/* mat1�� ���� �� ���� ũ�⸦ �����ϴ� �ڵ尡 ����. ����� ����, ���� ũ�⿡ ������� ����� ��� ���Ҹ� �����ϰ� �湮 ����*/
	/* �ٸ� ���� �ӵ��� ������, ������ ��ġ�� �����Ӱ� �����ϴ� ���� ������ �� ������� �ʴ� Ŭ�����Լ��� */
	for (MatIterator_<uchar> it = mat1.begin<uchar>(); it != mat1.end<uchar>(); ++it) {
		(*it)++;
	}
	cout << mat1 << endl;

	return 0;
}