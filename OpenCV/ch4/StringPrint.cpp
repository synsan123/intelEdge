/* ���ڿ� ����ϱ� */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	///* ���� ���� ������ ��Ʈ�� ���ڿ��� ����ϴ� �Լ� */
	///* (img, text, org(��ǥ), FontFace, FontSize, color, �β�, ����Ÿ��, (true = �����ϴ�, false = �������(=default��) */
	//Mat img(500, 800, CV_8UC3, Scalar(255, 255, 255)); // (800 x 500)

	//putText(img, "FONT_HERSHEY_SIMPLEX", Point(20, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255));
	//putText(img, "FONT_HERSHEY_PLAIN", Point(20, 100), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
	//putText(img, "FONT_HERSHEY_DUPLEX", Point(20, 150), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));
	//putText(img, "FONT_HERSHEY_COMPLEX", Point(20, 200), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0));
	//putText(img, "FONT_HERSHEY_TRIPLEX", Point(20, 250), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 0, 0));
	//putText(img, "FONT_HERSHEY_COMPLEX_SMALL", Point(20, 300), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255, 0, 0));
	//putText(img, "FONT_HERSHEY_SCRIPT_SIMPLEX", Point(20, 350), FONT_HERSHEY_SCRIPT_SIMPLEX, 1, Scalar(255, 0, 255));
	//putText(img, "FONT_HERSHEY_SCRIPT_COMPLEX", Point(20, 400), FONT_HERSHEY_SCRIPT_COMPLEX, 1, Scalar(255, 0, 255));
	///* ���Ÿ�ü�� �ٸ� ��ƮŸ�԰� | �Ͽ��� �� */
	//putText(img, "FONT_HERSHEY_COMPLEX | FONT_ITALIC", Point(20, 450), FONT_HERSHEY_COMPLEX | FONT_ITALIC, 1, Scalar(255, 0, 0));
	//
	//imshow("img", img);
	//waitKey();

	//destroyAllWindows();

	/* ���ڿ� ����� ���� �ʿ��� �簢�� ���� ũ�⸦ ������ �� �ִ� �Լ� getTextSize() */
	/* �� �̿��ϸ� ���ڿ��� �������� ġ��ġ�� �ʰ� ������ ��ġ�� ��µǵ��� ������ ������ */
	Mat img(200, 640, CV_8UC3, Scalar(255, 255, 255));

	const String text = "Hello, OpenCV";
	int fontFace = FONT_HERSHEY_TRIPLEX;
	double fontScale = 2.0;
	int thickness = 1;

	Size sizeText = getTextSize(text, fontFace, fontScale, thickness, 0); // ������ 0�� baseLine(��� ���� �ϴ��� �ؽ�Ʈ ��ġ ���ؼ��� y��ǥ)
	Size sizeImg = img.size();

	Point org((sizeImg.width - sizeText.width) / 2, (sizeImg.height + sizeText.height) / 2); // org = ��ǥ
	putText(img, text, org, fontFace, fontScale, Scalar(255, 0, 0), thickness);
	/*�簢�� ��ǥ�� Rect��ü ���� ����̶� �簢��������(pt1) �� pt1�� �밢���� �������� ����ϴ� ����� ���� */
	rectangle(img, org, org + Point(sizeText.width, -sizeText.height), Scalar(255, 0, 0), 1);

	imshow("img", img);
	waitKey();

	destroyAllWindows();
	return 0;
}