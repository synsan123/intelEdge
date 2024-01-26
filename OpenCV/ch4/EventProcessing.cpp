/* 이벤트 처리 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

#if 0
int main()
{
	/* 키보드 이벤트 처리 */
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
Point ptd; // on_mouse 함수에서 이전 마우스 이벤트 발생 위치를 저장하기 위한 용도
void on_mouse(int event, int x, int y, int flags, void*);

int main()
{
	/* 마우스 이벤트 처리 */
	/* 마우스 콜백 함수를 먼저 등록하고, 이후 마우스 콜백 함수에 마우스 이벤트를 처리하는 코드를 추가해야 함 */
	img = imread("lenna.bmp");

	if (img.empty()) {
		cerr << "img open Fail" << endl;
		return -1;
	}

	namedWindow("img"); //setMouseCallback 함수를 사용하기 전에 마우스 이벤트를 받을 창이 미리 생성되어 있어야 함
	setMouseCallback("img", on_mouse);

	imshow("img", img);
	waitKey();

	return 0;
}

void on_mouse(int event, int x, int y, int flags, void*)
{
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptd = Point(x, y); // 마우스 왼쪽 버튼이 눌린 좌표를 저장, ptd는 마우스가 움직인 궤적을 그릴 때 사용
		cout << "EVENT_LBUTTONDOWN : " << x << ", " << y << endl; // 마우스 왼쪽 버튼이 눌린 좌표를 출력
		break;
	case EVENT_LBUTTONUP: // 마우스 왼쪽 버튼이 떼어진 좌표를 출력
		cout << "EVENT_LBUTTONUP : " << x << ", " << y << endl;
		break;
	case EVENT_MOUSEMOVE: // 마우스가 움직이는 경우, 마우스 왼쪽 버튼이 눌려 있는 상태이면 노란색 직선을 이어 그림
		if (flags & EVENT_FLAG_LBUTTON) { // 직선은 ptd 좌표부터 현재 마우스 이벤트 발생 좌표까지 그림
			line(img, ptd, Point(x, y), Scalar(0, 255, 255), 2); 
			imshow("img", img);
			ptd = Point(x, y); // 직선을 그리고 난 후에는 현재 마우스 이벤트 발생 좌표를 ptd에 저장
		}
		break;
	default:
		break;
	}
}
#endif

/* 만약 트랙바의 현재위치를 알고 싶다면 getTrackbarPos함수를 사용. (트랙바이름, 트랙바가 부착되어 있는 창 이름) */
/* 트랙바 위치를 강제로 특정 위치로 옮기고 싶다면 setTrackbarPos함수를 사용. (트랙바이름, 트랙바가 부착되어 있는 창 이름, 트랙바를 이동할 위치) */

void trackbar_callback_function(int position, void* userdata);
int main()
{
	/* 트랙바(=슬라이더 컨트롤) 사용하기 */
	/* (트랙바이름, 트랙바 생성할 창 이름, 트랙바 위치를 받을 정수형 변수의 주소, 트랙바 최대 위치, NULL(onChange,166p참고), userdata) */
	Mat img = Mat::zeros(400, 800, CV_8UC1); // 픽셀값이 0으로 초기화된 800 x 400 영상

	namedWindow("image"); // 트랙바를 부착할 창을 미리 생성
	createTrackbar("level", "image", 0, 16, trackbar_callback_function, (void*)&img); // img객체의 주소를 사용자 데이터로 지정

	imshow("image", img);
	waitKey();

	return 0;
}

void trackbar_callback_function(int position, void* userdata)
{
	Mat img = *(Mat*)userdata; //void* 타입의 인자 userdata를 Mat* 타입으로 형변환한 후 img변수로 참조 => 결국 main함수의 img영상과 같은 영상 데이터를 사용

	img.setTo(position * 16); // 트랙바 위치 position(0 ~ 16)에 16을 곱한 결과를 img영상의 전체 픽셀 값으로 설정
	imshow("image", img);
}