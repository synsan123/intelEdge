#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	RotatedRect rtr1(Point2f(40, 30), Size2f(40, 20), 30.f);
	Point2f pts[4]; // pts = �簢�� �� �������� ��ǥ�� ���
	rtr1.points(pts); // rtr1��ü�� RotatedRect ����Լ� points�� pts ������ �Է��Ͽ� rtr1�� ȸ���Ͽ� ���� �簢���� �� ������ ��ǥ ����.
	
	for (int i = 0; i < 4; i++) // ȸ���� �簢���� �ײ����� ��ǥ ���.
	{
		cout << pts[i] << endl;
	}

	Rect br = rtr1.boundingRect2f();
	cout << br << endl;

	return 0;
}