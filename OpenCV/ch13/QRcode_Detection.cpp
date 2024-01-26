/* QR코드 검출 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* QR코드는 흑백 격자 무늬 모양의 2차원 바코드의 일종으로 숫자, 영문자, 8비트 문자, 한자 등의 정보를 저장할 수 있음 
   최근에는 URL문자열을 포함한 QR코드를 프린트하여 사용자가 QR코드 앱을 통해 해당 웹사이트에 쉽게 접속할 수 있는 서비스가 늘어남 
   
   입력 영상에서 QR코드를 인식하려면 먼저 QR 코드 세 모서리에 포함된 흑백 정사각형 패턴을 찾아 QR코드 전체 영역 위치를 알아내야 함
   검출된 QR코드를 정사각형 형태로 투시 변환한 후, QR 코드 내부에 포함된 흑백 격자 무늬를 해석하여 문자열을 추출해야 함 
   
   QR코드를 검출하고 해석하는 기능은 QRCodeDetector 클래스에 구현되어 있음. 사용하려면 객체 생성은 당연한 것
   입력 영상에서 QR코드 영역을 검출하기 위해서는 QRCodeDetector::detect() 함수를 사용 
   detect(img, points). points = 출력 QR 코드를 감싸는 사각형의 네 꼭지점 좌표. 반환 값은 true, false 인 bool 값 
   points 인자에는 vector<Point2f> or vector<Point>타입의 변수를 지정. 
   points 인자로 반환받은 QR코드 영역 위치 정보는 이후 QR코드를 해석할 때 입력 정보로 사용됨 
   
   검출된 QR코드 영역에서 QR코드에 저장된 문자열을 추출할 때에는 QRCodeDetector::decode()함수를 사용 
   decode(img, points, straight_qrcode) 형태
   straight_qrcode = 출력 정사각형 QR코드 영상. CV_8UC1. 반환 값은 QR코드에 포함된 문자열 
   
   입력 영상에서 QR코드 검출과 해석을 한꺼번에 수행하려면 QRCodeDetector::detectAndDecode()함수를 사용 
   detectAndDecode(img, points = noArray(), straight_qrcode = noArray())
   입력 영상에서 QR콛의 검출과 해석을 동시에 수행, 해석된 문자열을 반환하는 함수.
   만약 QR코드의 네 꼭지점 좌표 또는 정사각형 형태의 QR코드 영상이 필요하다면 points와 straight_qrcode에 인자를 전달해야함
   단순히 QR코드에 포함된 문자열을 얻고 싶다면 생략하면 됨.*/
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

		/* 카메라 매 프레임마다 QR코드 검출 및 해석을 수행함 */
		vector<Point> points;
		String info = detector.detectAndDecode(frame, points);

		/* QR코드를 검출하고 QR코드 문자열이 제대로 info 변수에 저장되었다면 QR코드에 빨간색 사각형을 그리고,
		   해석된 문자열을 화면 좌측 상단에 빨간색 글자로 출력함 */
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