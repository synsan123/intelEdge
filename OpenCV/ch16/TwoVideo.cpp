#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(1); // USB 카메라 사용으로 1 사용. 컴퓨터 내장 카메라는 0
	 
	if (!cap.isOpened()) { // 안 열리면 에러 메시지 출력
		cerr << "Video Fail" << endl;
		return -1;
	}

	Mat frame, Gray, Thresh; // Mat 객체 생성 

	while (true) {
		cap >> frame; // 카메라 화면을 frame에 실시간으로 전달(캡처)
		if (frame.empty()) { // frame에 전달이 안되어 비어있으면 종료
			break;
		}

		//namedWindow("Gray");
		//namedWindow("Thresh"); // namedWindow없이도 실행 잘 됨( 굳이 없어도 됨 ) 

		cvtColor(frame, Gray, COLOR_BGR2GRAY); // BGR => GRAYSCALE로 변경하여 Gray에 저장
		threshold(Gray, Thresh, 128, 255, THRESH_BINARY | THRESH_OTSU); // GRAYSCALE영상 Gray에 이진화를 적용. Thresh에 저장. 128은 임계값

		imshow("frame", frame);
		imshow("Gray", Gray);
		imshow("Thresh", Thresh);

		if (waitKey(10) == 27) break; // ESC 누르면 종료
	}

	destroyAllWindows();
}