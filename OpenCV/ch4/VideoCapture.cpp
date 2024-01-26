#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

#if 1
int main()
{
	VideoCapture cap(1); // 객체 생성 및 컴퓨터에 연결된 기본 카메라를 사용 (카메라 없어서 안됨)

	if (!cap.isOpened()) {
		cerr << "Camera open failed" << endl;
		return -1;
	}

	cout << "Frame width : " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height : " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;

	Mat frame, inversed;
	while (true) {
		cap >> frame; // 다음 프레임을 받아오는 >> 연산자 재정의
		if (frame.empty())
			break;

		inversed = ~frame;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(10) == 27) // 사용자로부터 10ms 동안 키보드 입력을 기다림. ESC를 입력 시 종료
			break;
	}

	destroyAllWindows();
}
#endif

#if 0
int main()
{
	VideoCapture cap("stopwatch.avi"); // 동영상 파일을 불러온다.

	if (!cap.isOpened()) {
		cerr << "Video open Failed" << endl;
		return -1;
	}

	cout << "Frame Width : " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame Height : " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	cout << "Frame count : " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl; // 전체 프레임 수

	double fps = cap.get(CAP_PROP_FPS); 
	cout << "FPS : " << fps << endl;

	int delay = cvRound(1000 / fps);

	Mat frame, inversed;
	while (true) {
		cap >> frame; // 카메라로부터 한 프레임을 받아 와서 frame 변수에 저장.
		if (frame.empty()) break;

		inversed = ~frame;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27) break;
	}
	destroyAllWindows();

	return 0;
}
#endif
