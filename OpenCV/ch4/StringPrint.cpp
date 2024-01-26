/* 문자열 출력하기 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	///* 영상 위에 정해진 폰트로 문자열을 출력하는 함수 */
	///* (img, text, org(좌표), FontFace, FontSize, color, 두께, 라인타입, (true = 좌측하단, false = 좌측상단(=default값) */
	//Mat img(500, 800, CV_8UC3, Scalar(255, 255, 255)); // (800 x 500)

	//putText(img, "FONT_HERSHEY_SIMPLEX", Point(20, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255));
	//putText(img, "FONT_HERSHEY_PLAIN", Point(20, 100), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
	//putText(img, "FONT_HERSHEY_DUPLEX", Point(20, 150), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));
	//putText(img, "FONT_HERSHEY_COMPLEX", Point(20, 200), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0));
	//putText(img, "FONT_HERSHEY_TRIPLEX", Point(20, 250), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 0, 0));
	//putText(img, "FONT_HERSHEY_COMPLEX_SMALL", Point(20, 300), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255, 0, 0));
	//putText(img, "FONT_HERSHEY_SCRIPT_SIMPLEX", Point(20, 350), FONT_HERSHEY_SCRIPT_SIMPLEX, 1, Scalar(255, 0, 255));
	//putText(img, "FONT_HERSHEY_SCRIPT_COMPLEX", Point(20, 400), FONT_HERSHEY_SCRIPT_COMPLEX, 1, Scalar(255, 0, 255));
	///* 이탤릭체는 다른 폰트타입과 | 하여야 함 */
	//putText(img, "FONT_HERSHEY_COMPLEX | FONT_ITALIC", Point(20, 450), FONT_HERSHEY_COMPLEX | FONT_ITALIC, 1, Scalar(255, 0, 0));
	//
	//imshow("img", img);
	//waitKey();

	//destroyAllWindows();

	/* 문자열 출력을 위해 필요한 사각형 영역 크기를 가늠할 수 있는 함수 getTextSize() */
	/* 잘 이용하면 문자열이 한쪽으로 치우치지 않고 적당한 위치에 출력되도록 설정이 가능함 */
	Mat img(200, 640, CV_8UC3, Scalar(255, 255, 255));

	const String text = "Hello, OpenCV";
	int fontFace = FONT_HERSHEY_TRIPLEX;
	double fontScale = 2.0;
	int thickness = 1;

	Size sizeText = getTextSize(text, fontFace, fontScale, thickness, 0); // 마지막 0은 baseLine(출력 가장 하단의 텍스트 위치 기준선의 y좌표)
	Size sizeImg = img.size();

	Point org((sizeImg.width - sizeText.width) / 2, (sizeImg.height + sizeText.height) / 2); // org = 좌표
	putText(img, text, org, fontFace, fontScale, Scalar(255, 0, 0), thickness);
	/*사각형 좌표는 Rect객체 쓰는 방법이랑 사각형꼭지점(pt1) 및 pt1의 대각방향 꼭지점을 사용하는 방법이 있음 */
	rectangle(img, org, org + Point(sizeText.width, -sizeText.height), Scalar(255, 0, 0), 1);

	imshow("img", img);
	waitKey();

	destroyAllWindows();
	return 0;
}