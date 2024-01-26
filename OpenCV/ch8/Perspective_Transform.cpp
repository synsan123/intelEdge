/* ���� ��ȯ */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;


Mat src; // �Է� ������ ������ ����
Point2f srcQuad[4], dstQuad[4]; // ���� ��ǥ�� ������ �迭 ����

void on_mouse(int event, int x, int y, int flags, void* userdata) // ���콺 �ݹ� �Լ�
{
	/* ������ ��ȯ���� �������� ���� ��ȯ */
	/* ���簢�� ������ ������ ������ ���� �簢�� ���·� ������ �� �ִ� ��ȯ */
	/* �������� ���������� �� ������ ���� ����� ���� �� ���� */
	/* ��(x,y)�ϳ����� x��ǥ�� ���� ������, y��ǥ�� ���� �������� �ϳ��� ���� �� �ְ� 4��ǥ�� ���ؼ� 8���� �������� ���� �� ���� */
	/* 8���� �����Ŀ��� ���� ��ȯ�� ǥ���ϴ� �Ķ���� ������ ����� �� ���� */
	/* ���� ��ȯ�� 3x3ũ���� �Ǽ� ��ķ� ǥ���� */
	/* ���ǻ� 9�� ���Ҹ� ���. Mp��� ǥ�� */

	/* ���� ��ȯ ����� ���ϴ� �Լ��� ���� ��ȯ ����� �̿��Ͽ� ���� ������ ���� ��ȯ�ϴ� �Լ��� ��� ���� */
	/* ���� ��ȯ ����� ���ϴ� �Լ��� getPerspectiveTransform(src, dst, solveMethod) */
	/* solveMethod�� ��� ��� ����, src, dst�� Point2f �ڷ��� �迭�̳� vector<Point2f>�ڷ����� ����ϸ� �� */
	/* ��ȯ���� CV_64FC1Ÿ���� 3x3 ���� ��ȯ ��� */

	/* ���� ��ȯ�� ���ϴ� �Լ��� warpPerspective(src, dst, M, dsize, flags, borderMode, borderValue) */
	
	/* 3x3 ���� ��ȯ ����� ������ ���� ��, ������ ���� ��ȯ�� ���� ��� ��ġ�� �̵��� �������� �˰� �ʹٸ� */
	/* perspectiveTransform(src, dst, m) �Լ��� ����ϸ� �� */
	
	static int cnt = 0; // ���� ��ư�� ���� Ƚ���� �����ϴ� ����

	if (event == EVENT_LBUTTONDOWN) { 
		if (cnt < 4) {
			srcQuad[cnt++] = Point2f(x, y); // srcâ���� ���콺 ���� ��ư�� ������ ��ǥ�� srcQuad�迭�� ����. �׸��� cnt���� 1��ŭ ����

			circle(src, Point(x, y), 5, Scalar(0, 0, 255), -1); // ���콺�� ������ ��ġ�� �������� 5�� ������ ���� �׸�
			imshow("src", src);

			if (cnt == 4) {
				int w = 200, h = 300; // ���� ��ȯ�Ͽ� ���� ��� ������ ���ο� ���� ũ�⸦ ������ ����

				dstQuad[0] = Point2f(0, 0); // srcâ���� ���콺�� ������ �簢�� �������� �̵��� ��� ���� ��ǥ�� ���� 
				dstQuad[1] = Point2f(w - 1, 0);
				dstQuad[2] = Point2f(w - 1, h - 1);
				dstQuad[3] = Point2f(0, h - 1);

				Mat pers = getPerspectiveTransform(srcQuad, dstQuad);

				Mat dst;
				warpPerspective(src, dst, pers, Size(w, h)); // ���� ��ȯ�� �����Ͽ� wxhũ���� ��� ���� dst�� ���� 

				imshow("dst", dst);
			}
		}
	}
}
int main()
{
	src = imread("card.bmp");

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	namedWindow("src"); // srcâ�� �̸� ������ ��, srcâ�� ���콺 �ݹ� �Լ��� ��� 
	setMouseCallback("src", on_mouse);

	imshow("src", src);
	waitKey();

	return 0;
}