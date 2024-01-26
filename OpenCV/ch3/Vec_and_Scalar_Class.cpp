/* Vec(Vector)Ŭ���� �� Scalar Ŭ���� */
/* Mat Ŭ������ŭ ��� �󵵰� ���� Ŭ������ */
/* ���⼭�� ���ʸ� ������ �������� OpenCV ����Ʈ ���� */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

/* �ϳ��� �����θ� �̷���� ��� = �� ���� */
/* �ϳ��� ���θ� �̷���� ��� = �� ���� */
/* �� ���� ���ļ� ���� �Ǵ� ���� ����̶�� �θ� */
/* ���� = ���� �ڷ����� ���� ���� �� ���� ������ ������ ���� */

int main()
{
	// Vec<int, 3> or Vec<uchar, 3> ������ ����Ͽ� �ڷ��� �� ����(ä�� ����)�� ��Ÿ��
	// Vec<uchar, 3> p1, p2(0,0,255); �������� ���� ����
	// ������ ���� ���� ����� ������. �׷��� �̸� �����Ǹ� �̿��Ͽ� ���� ǥ���� �� ����
	// Vec<uchar, 3>�� Vec3b�� =>���� Color���� b = uchar, s = short, w = ushort, i,f,d�� int, float, double (114p����)
	// �� ��° �ּ��� Vec3b p1, p2(0,0,255);�� ǥ�� ����
	// �� �ּ��� ���ο� uchar val[3] ������ ��� ������ ������ p1�� ���� 0, p2�� p2.val[0], p2.val[1]�� 0, p2.val[2]�� 255�� �ʱ�ȭ
	// p1.val[0] = 100;���� �ϸ� ù ��° ������ 100���� �ʱ�ȭ ����
	// []������ �����Ǹ� ���� p1[0] = 100; ����
	Vec3b p1, p2(0, 0, 255);
	cout << p1 << endl;
	cout << p2 << endl;

	cout << endl;

	p1[0] = 100;
	p1.val[1] = 255;
	cout << p1 << endl;

	/* Scalar Ŭ������ 4ä�� ������ ���󿡼� �ȼ� ���� ǥ���ϴ� �뵵�� ���� ��� */
	/* 4���� ���Ҹ� ������ ���ø� Ŭ���� */
	/* Scalar Ŭ������ ũ�Ⱑ 4�� double�� �迭 val�� ��� ������ ������ �ִ� �ڷ��� */
	Scalar gray = 128; // grayscale�� ��Ⱚ�� ���� (128, 0, 0, 0)
	cout << "gray : " << gray << endl;

	Scalar yellow(0, 255, 255); // True Color�� BGR���� ���� (0, 255, 255, 0)
	cout << "yellow : " << yellow << endl;

	Mat img1(256, 256, CV_8UC3, yellow);
	for (int i = 0; i < 4; i++)
		cout << yellow[i] << endl;

	return 0;
}