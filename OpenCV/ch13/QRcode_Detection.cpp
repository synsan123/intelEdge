/* QR�ڵ� ���� */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* QR�ڵ�� ��� ���� ���� ����� 2���� ���ڵ��� �������� ����, ������, 8��Ʈ ����, ���� ���� ������ ������ �� ���� 
   �ֱٿ��� URL���ڿ��� ������ QR�ڵ带 ����Ʈ�Ͽ� ����ڰ� QR�ڵ� ���� ���� �ش� ������Ʈ�� ���� ������ �� �ִ� ���񽺰� �þ 
   
   �Է� ���󿡼� QR�ڵ带 �ν��Ϸ��� ���� QR �ڵ� �� �𼭸��� ���Ե� ��� ���簢�� ������ ã�� QR�ڵ� ��ü ���� ��ġ�� �˾Ƴ��� ��
   ����� QR�ڵ带 ���簢�� ���·� ���� ��ȯ�� ��, QR �ڵ� ���ο� ���Ե� ��� ���� ���̸� �ؼ��Ͽ� ���ڿ��� �����ؾ� �� 
   
   QR�ڵ带 �����ϰ� �ؼ��ϴ� ����� QRCodeDetector Ŭ������ �����Ǿ� ����. ����Ϸ��� ��ü ������ �翬�� ��
   �Է� ���󿡼� QR�ڵ� ������ �����ϱ� ���ؼ��� QRCodeDetector::detect() �Լ��� ��� 
   detect(img, points). points = ��� QR �ڵ带 ���δ� �簢���� �� ������ ��ǥ. ��ȯ ���� true, false �� bool �� 
   points ���ڿ��� vector<Point2f> or vector<Point>Ÿ���� ������ ����. 
   points ���ڷ� ��ȯ���� QR�ڵ� ���� ��ġ ������ ���� QR�ڵ带 �ؼ��� �� �Է� ������ ���� 
   
   ����� QR�ڵ� �������� QR�ڵ忡 ����� ���ڿ��� ������ ������ QRCodeDetector::decode()�Լ��� ��� 
   decode(img, points, straight_qrcode) ����
   straight_qrcode = ��� ���簢�� QR�ڵ� ����. CV_8UC1. ��ȯ ���� QR�ڵ忡 ���Ե� ���ڿ� 
   
   �Է� ���󿡼� QR�ڵ� ����� �ؼ��� �Ѳ����� �����Ϸ��� QRCodeDetector::detectAndDecode()�Լ��� ��� 
   detectAndDecode(img, points = noArray(), straight_qrcode = noArray())
   �Է� ���󿡼� QR���� ����� �ؼ��� ���ÿ� ����, �ؼ��� ���ڿ��� ��ȯ�ϴ� �Լ�.
   ���� QR�ڵ��� �� ������ ��ǥ �Ǵ� ���簢�� ������ QR�ڵ� ������ �ʿ��ϴٸ� points�� straight_qrcode�� ���ڸ� �����ؾ���
   �ܼ��� QR�ڵ忡 ���Ե� ���ڿ��� ��� �ʹٸ� �����ϸ� ��.*/
void decode_qrcode()
{
	VideoCapture cap(1);

	if (!cap.isOpened()) {
		cerr << "Fail" << endl;
		return;
	}

	QRCodeDetector detector;

	Mat frame;
	while (true) {
		cap >> frame;

		if (frame.empty()) {
			cerr << "Frame Fail" << endl;
			break;
		}

		/* ī�޶� �� �����Ӹ��� QR�ڵ� ���� �� �ؼ��� ������ */
		vector<Point> points;
		String info = detector.detectAndDecode(frame, points);

		/* QR�ڵ带 �����ϰ� QR�ڵ� ���ڿ��� ����� info ������ ����Ǿ��ٸ� QR�ڵ忡 ������ �簢���� �׸���,
		   �ؼ��� ���ڿ��� ȭ�� ���� ��ܿ� ������ ���ڷ� ����� */
		if (!info.empty()) {
			polylines(frame, points, true, Scalar(0, 0, 255), 2);
			putText(frame, info, Point(10, 30), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));
		}

		imshow("frame", frame);
		if (waitKey(1) == 27) break;
	}
}

int main()
{
	decode_qrcode();

	return 0;
}