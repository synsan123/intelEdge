/* �̺�Ʈ ó�� */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

#if 0
int main()
{
	/* Ű���� �̺�Ʈ ó�� */
	Mat img = imread("lenna.bmp");

	if (img.empty()) {
		cerr << "Img open Fail" << endl;
		return -1;
	}

	namedWindow("img");
	imshow("img", img);

	while (true) {
		int keycode = waitKey();

		if (keycode == 'i' || keycode == 'I') {
			img = ~img;
			imshow("img", img);
		}
		else if (keycode == 27 || keycode == 'q' || keycode == 'Q') {
			break;
		}
	}

	return 0;
}
#endif

#if 0
Mat img;
Point ptd; // on_mouse �Լ����� ���� ���콺 �̺�Ʈ �߻� ��ġ�� �����ϱ� ���� �뵵
void on_mouse(int event, int x, int y, int flags, void*);

int main()
{
	/* ���콺 �̺�Ʈ ó�� */
	/* ���콺 �ݹ� �Լ��� ���� ����ϰ�, ���� ���콺 �ݹ� �Լ��� ���콺 �̺�Ʈ�� ó���ϴ� �ڵ带 �߰��ؾ� �� */
	img = imread("lenna.bmp");

	if (img.empty()) {
		cerr << "img open Fail" << endl;
		return -1;
	}

	namedWindow("img"); //setMouseCallback �Լ��� ����ϱ� ���� ���콺 �̺�Ʈ�� ���� â�� �̸� �����Ǿ� �־�� ��
	setMouseCallback("img", on_mouse);

	imshow("img", img);
	waitKey();

	return 0;
}

void on_mouse(int event, int x, int y, int flags, void*)
{
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptd = Point(x, y); // ���콺 ���� ��ư�� ���� ��ǥ�� ����, ptd�� ���콺�� ������ ������ �׸� �� ���
		cout << "EVENT_LBUTTONDOWN : " << x << ", " << y << endl; // ���콺 ���� ��ư�� ���� ��ǥ�� ���
		break;
	case EVENT_LBUTTONUP: // ���콺 ���� ��ư�� ������ ��ǥ�� ���
		cout << "EVENT_LBUTTONUP : " << x << ", " << y << endl;
		break;
	case EVENT_MOUSEMOVE: // ���콺�� �����̴� ���, ���콺 ���� ��ư�� ���� �ִ� �����̸� ����� ������ �̾� �׸�
		if (flags & EVENT_FLAG_LBUTTON) { // ������ ptd ��ǥ���� ���� ���콺 �̺�Ʈ �߻� ��ǥ���� �׸�
			line(img, ptd, Point(x, y), Scalar(0, 255, 255), 2); 
			imshow("img", img);
			ptd = Point(x, y); // ������ �׸��� �� �Ŀ��� ���� ���콺 �̺�Ʈ �߻� ��ǥ�� ptd�� ����
		}
		break;
	default:
		break;
	}
}
#endif

/* ���� Ʈ������ ������ġ�� �˰� �ʹٸ� getTrackbarPos�Լ��� ���. (Ʈ�����̸�, Ʈ���ٰ� �����Ǿ� �ִ� â �̸�) */
/* Ʈ���� ��ġ�� ������ Ư�� ��ġ�� �ű�� �ʹٸ� setTrackbarPos�Լ��� ���. (Ʈ�����̸�, Ʈ���ٰ� �����Ǿ� �ִ� â �̸�, Ʈ���ٸ� �̵��� ��ġ) */

void trackbar_callback_function(int position, void* userdata);
int main()
{
	/* Ʈ����(=�����̴� ��Ʈ��) ����ϱ� */
	/* (Ʈ�����̸�, Ʈ���� ������ â �̸�, Ʈ���� ��ġ�� ���� ������ ������ �ּ�, Ʈ���� �ִ� ��ġ, NULL(onChange,166p����), userdata) */
	Mat img = Mat::zeros(400, 800, CV_8UC1); // �ȼ����� 0���� �ʱ�ȭ�� 800 x 400 ����

	namedWindow("image"); // Ʈ���ٸ� ������ â�� �̸� ����
	createTrackbar("level", "image", 0, 16, trackbar_callback_function, (void*)&img); // img��ü�� �ּҸ� ����� �����ͷ� ����

	imshow("image", img);
	waitKey();

	return 0;
}

void trackbar_callback_function(int position, void* userdata)
{
	Mat img = *(Mat*)userdata; //void* Ÿ���� ���� userdata�� Mat* Ÿ������ ����ȯ�� �� img������ ���� => �ᱹ main�Լ��� img����� ���� ���� �����͸� ���

	img.setTo(position * 16); // Ʈ���� ��ġ position(0 ~ 16)�� 16�� ���� ����� img������ ��ü �ȼ� ������ ����
	imshow("image", img);
}