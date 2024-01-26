#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

/* 텐서플로에서 훈련된 모델 파일과 구성 파일 이름을 각각 model과 config 변수에 저장 */
const String model = "opencv_face_detector_uint8.pb";
const String config = "opencv_face_detector.pbtxt";

void open_close(Mat& frame, Rect faceROI);

int main(void)
{
    VideoCapture cap(1);

    if (!cap.isOpened()) {
        cerr << "Camera open failed!" << endl;
        return -1;
    }

    /* 모델 파일과 구성 파일을 이용하여 Net 객체 net을 생성 */
    Net net = readNet(model, config);

    if (net.empty()) {
        cerr << "Net open failed!" << endl;
        return -1;
    }

    Mat frame;
    while (true) {
        cap >> frame; // 카메라의 매 프레임을 frame 변수에 저장
        if (frame.empty())
            break;

        /* frame 영상을 이용하여 네트워크 입력 블롭을 설정하고, 네트워크 실행 결과를 res 행렬에 저장 */
        Mat blob = blobFromImage(frame, 1, Size(300, 300), Scalar(104, 177, 123));
        net.setInput(blob);
        Mat res = net.forward();

        Mat detect(res.size[2], res.size[3], CV_32FC1, res.ptr<float>());

        /* 결과 행렬에서 신뢰도 값이 0.5보다 작으면 무시 */
        for (int i = 0; i < detect.rows; i++) {
            float confidence = detect.at<float>(i, 2);
            if (confidence < 0.5)
                continue;

            /* 얼굴 검출 사각형 영역의 좌측 상단 좌표(x1, y1)과 우측 하단 좌표(x2, y2)를 계산 */
            int x1 = cvRound(detect.at<float>(i, 3) * frame.cols);
            int y1 = cvRound(detect.at<float>(i, 4) * frame.rows);
            int x2 = cvRound(detect.at<float>(i, 5) * frame.cols);
            int y2 = cvRound(detect.at<float>(i, 6) * frame.rows);

            /* frame 영상에서 얼굴 검출 영역에 녹색 사각형을 그리고, 얼굴 신뢰도를 출력 */
            Rect faceROI(Point(x1, y1), Point(x2, y2)); // 얼굴 영역만 관심 영역으로 지정
            rectangle(frame, faceROI, Scalar(0, 255, 0));

            String label = format("Face: %4.3f", confidence);
            putText(frame, label, Point(x1, y1 - 1), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 255, 0));

            // 감지된 얼굴에 대해서만 모폴로지 연산을 수행
            open_close(frame, faceROI);
        }

        imshow("frame", frame);
        if (waitKey(1) == 27)
            break;
    }

    return 0;
}

void open_close(Mat& frame, Rect faceROI) {
    
    // 얼굴 ROI 내에서 모폴로지 연산을 수행합니다.
    Mat face = frame(faceROI); // Mat 클래스를 사용하여 원본 이미지 frame의 faceROI에 정의된 영역을 참조하기 위한 Mat 객체 face를 생성
    cvtColor(face, face, COLOR_BGR2GRAY); // 그레이스케일로 변환

    // 오츠 알고리즘으로 자동 이진화를 수행하고, 그 결과를 binary에 저장
    Mat binary;
    threshold(face, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

    // 3 x 3 정방형 구조 요소를 이용하여 열기 연산을 수행하고, 그 결과를 dst에 저장
    Mat dst;
    morphologyEx(binary, dst, MORPH_OPEN, Mat()); 

    // 결과를 표시하기 위해 원본 이미지에 복사합니다. 흑백이미지를 컬러 이미지로 변환합니다.
    //cvtColor(dst, dst, COLOR_GRAY2BGR);
    //dst.copyTo(frame(faceROI)); // dst 이미지를 frame(faceROI)에 복사
    imshow("dst", dst);
}
