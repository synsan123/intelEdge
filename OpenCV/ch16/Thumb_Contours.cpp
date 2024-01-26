#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void contours_basic1();

// 작동 안됨. 미완성.
void contours_basic()
{
	VideoCapture cap(1); // USB 카메라 사용으로 1 사용. 컴퓨터 내장 카메라는 0

	if (!cap.isOpened()) { // 안 열리면 에러 메시지 출력
		cerr << "Video Fail" << endl;
		return;
	}

    Mat frame;

    while (true) {
        cap >> frame; // 카메라 화면을 frame에 실시간으로 전달(캡처)
        if (frame.empty()) { // frame에 전달이 안되어 비어있으면 종료
            break;
        }
        // 자신의 손바닥 촬영하여 저장
        imwrite("hand.jpg", frame);

        // 저장한 손바닥 사진 로드
        Mat hand = imread("hand.jpg", IMREAD_COLOR);

        // 손바닥 외곽선 검출 - 외곽선 내부 지정한 색깔로 채움
        Mat gray;
        cvtColor(hand, gray, COLOR_BGR2GRAY);

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(gray, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        Mat dst;
        cvtColor(gray, dst, COLOR_GRAY2BGR);

        for (int idx = 0; idx >= 0; idx = hierarchy[idx][0]) {
            Scalar c(rand() & 255, rand() & 255, rand() & 255);
            drawContours(dst, contours, idx, c, -1, LINE_8, hierarchy);
        }

        imshow("gray", gray);
        imshow("dst", dst);

        if (waitKey(10) == 27) break; // ESC 누르면 종료
    }
	destroyAllWindows();
}
#if 0
int main(void)
{
	contours_basic();
    //contours_basic1();
	return 0;
}
#endif 

// 작동은 하나 손바닥 내부를 채우지 못함(for문 다시 손 봐야함)
#if 1
int main() {
    VideoCapture cap(1); // 1. 카메라를 실행하고 실시간으로 캡쳐

    if (!cap.isOpened()) {
        cout << "카메라를 열 수 없습니다." << endl;
        return -1;
    }

    while (1) {
        Mat frame;
        cap >> frame; // 2. 카메라로부터 프레임을 캡쳐

        if (frame.empty()) {
            cout << "프레임을 캡쳐할 수 없습니다." << endl;
            break;
        }

        // 3. 자신의 손바닥 촬영하여 저장
        imwrite("hand.jpg", frame);

        // 4. 저장한 손바닥 사진 로드
        Mat hand = imread("hand.jpg", IMREAD_COLOR);

        // 5. 손바닥 외곽선 검출 - 외곽선 내부 지정한 색깔로 채움
        Mat gray, edges;
        cvtColor(hand, gray, COLOR_BGR2GRAY);
        Canny(gray, edges, 100, 200);

        vector<vector<Point>> contours;
        findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        for (auto& contour : contours) { // 미완성
            drawContours(hand, vector<vector<Point>>(1,contour), -1, Scalar(0, 0, 255), -1); // 채우는 색깔을 빨간색으로 지정
        }

        imwrite("contorushand.jpg", hand);
        imshow("Hand Contour", hand);
        imshow("gray", gray);
        imshow("edges", edges);
        
        // 6. ESC키를 누르면 프로그램 종료
        if (waitKey(1) == 27) {
            cout << "ESC키를 누르셨습니다. 프로그램을 종료합니다." << endl;
            break;
        }
    }

    return 0;
}
#endif

void contours_basic1()
{
Mat src = imread("hand.jpg", IMREAD_GRAYSCALE);

if (src.empty()) {
    cerr << "Fail" << endl;
    return;
}
Mat edges;
Canny(src, edges, 50, 150);
/* src 영상으로부터 모든 외곽선을 검출하여 contours변수에 저장. 계층 구조는 없음 (RETR_LIST 모드는 계층 구조 없음) */
vector<vector<Point>> contours;
findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

Mat dst;
cvtColor(edges, dst, COLOR_GRAY2BGR);

/* 전체 외곽선 개수만큼 for문을 수행 */
for (int i = 0; i < contours.size(); i++) {
    Scalar c(rand() & 255, rand() & 255, rand() & 255); // contours에 저장된 각각의 외곽선을 임의의 색상으로 그림
    drawContours(dst, contours, i, c, 5);
}

imshow("src", src);
imshow("dst", dst);

waitKey();
destroyAllWindows();
}

