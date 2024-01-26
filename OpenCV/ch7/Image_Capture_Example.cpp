#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

#if 0
Rect box; // 마우스로 드래그한 사각형 영역을 담을 객체
bool drawing = false; // 마우스 드래그 상태를 저장하는 변수

// 사각형을 그리는 함수
void draw_box(Mat& img, Rect box) {
    rectangle(img, box, Scalar(0, 0, 255), 2); // img 이미지에 box 영역을 빨간색으로 그림
}

// 마우스 이벤트 처리 함수
void onMouse(int event, int x, int y, int, void* param) {
    Mat& image = *(Mat*)param; // 마우스 이벤트가 발생한 이미지
    switch (event) {
    case EVENT_MOUSEMOVE:
        if (drawing) {
            box.width = x - box.x; // 마우스를 드래그하는 동안 사각형의 너비 설정
            box.height = y - box.y; // 마우스를 드래그하는 동안 사각형의 높이 설정
        }
        break;
    case EVENT_LBUTTONDOWN:
        drawing = true; // 마우스 왼쪽 버튼을 누르면 드래그 시작
        box = Rect(x, y, 0, 0); // 시작 좌표 설정
        break;
    case EVENT_LBUTTONUP:
        drawing = false; // 마우스 왼쪽 버튼을 떼면 드래그 종료
        if (box.width < 0) {
            box.x += box.width; // 사각형의 너비가 음수인 경우 좌표와 너비를 재조정
            box.width *= -1;
        }
        if (box.height < 0) {
            box.y += box.height; // 사각형의 높이가 음수인 경우 좌표와 높이를 재조정
            box.height *= -1;
        }
        draw_box(image, box); // 드래그가 종료된 최종 사각형을 그림
        break;
    }
}

int main() {
    Mat image = imread("lenna.bmp"), temp; // lenna.bmp 이미지를 불러와 image에 저장, temp는 임시 이미지
    if (image.empty()) {
        cout << "Could not open image file" << endl; // 이미지 파일이 없는 경우 에러 메시지 출력 후 종료
        return -1;
    }
    box = Rect(-1, -1, 0, 0); // 초기 사각형 영역 설정
    temp = image.clone(); // temp에 image 복사

    namedWindow("window"); // window라는 이름의 창 생성
    setMouseCallback("window", onMouse, (void*)&image); // window 창에서 마우스 이벤트가 발생하면 onMouse 함수 호출

    while (1) {
        image.copyTo(temp); // temp에 image 복사
        if (drawing) draw_box(temp, box); // 드래그 중이면 사각형 그림
        imshow("window", temp); // window 창에 temp 이미지를 보여줌

        // 's' 키를 누르면 선택한 영역을 ROI.bmp 파일로 저장
        if (waitKey(1) == 's') {
            if (box.width > 0 && box.height > 0) {
                Mat roi = image(box); // 선택한 영역을 roi에 저장
                imwrite("ROI.bmp", roi); // roi를 ROI.bmp 파일로 저장
                break;
            }
        }
    }

    destroyAllWindows();
    return 0;
}
#endif

Rect box;
bool drawing = false;

void draw_box(Mat& img, Rect box) {
    rectangle(img, box, Scalar(0, 0, 255), 2);
}

void onMouse(int event, int x, int y, int, void* param) {
    Mat& image = *(Mat*)param;
    switch (event) {
    case EVENT_MOUSEMOVE:
        if (drawing) {
            box.width = x - box.x;
            box.height = y - box.y;
        }
        break;
    case EVENT_LBUTTONDOWN:
        drawing = true;
        box = Rect(x, y, 0, 0);
        break;
    case EVENT_LBUTTONUP:
        drawing = false;
        if (box.width < 0) {
            box.x += box.width;
            box.width *= -1;
        }
        if (box.height < 0) {
            box.y += box.height;
            box.height *= -1;
        }
        draw_box(image, box);
        break;
    }
}

int main() {
    VideoCapture cap(1); // 1번 카메라를 연다.
    if (!cap.isOpened()) {
        cout << "Could not open camera" << endl;
        return -1;
    }

    Mat frame, temp;
    namedWindow("Camera");
    namedWindow("Captured_image");
    setMouseCallback("Camera", onMouse, (void*)&frame);

    while (1) {
        cap >> frame;
        if (frame.empty()) break;

        frame.copyTo(temp);
        if (drawing) draw_box(temp, box);
        imshow("Camera", temp);

        if (box.width > 0 && box.height > 0) {
            Mat roi = frame(box);
            imshow("Captured_image", roi);
        }

        if (waitKey(1) == 27) break; // ESC키를 누르면 종료
    }
    cap.release();
    return 0;
}