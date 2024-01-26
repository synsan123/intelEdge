#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(1); // USB ī�޶� ������� 1 ���. ��ǻ�� ���� ī�޶�� 0
	 
	if (!cap.isOpened()) { // �� ������ ���� �޽��� ���
		cerr << "Video Fail" << endl;
		return -1;
	}

	Mat frame, Gray, Thresh; // Mat ��ü ���� 

	while (true) {
		cap >> frame; // ī�޶� ȭ���� frame�� �ǽð����� ����(ĸó)
		if (frame.empty()) { // frame�� ������ �ȵǾ� ��������� ����
			break;
		}

		//namedWindow("Gray");
		//namedWindow("Thresh"); // namedWindow���̵� ���� �� ��( ���� ��� �� ) 

		cvtColor(frame, Gray, COLOR_BGR2GRAY); // BGR => GRAYSCALE�� �����Ͽ� Gray�� ����
		threshold(Gray, Thresh, 128, 255, THRESH_BINARY | THRESH_OTSU); // GRAYSCALE���� Gray�� ����ȭ�� ����. Thresh�� ����. 128�� �Ӱ谪

		imshow("frame", frame);
		imshow("Gray", Gray);
		imshow("Thresh", Thresh);

		if (waitKey(10) == 27) break; // ESC ������ ����
	}

	destroyAllWindows();
}