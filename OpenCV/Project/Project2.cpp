#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

/* �ټ��÷ο��� �Ʒõ� �� ���ϰ� ���� ���� �̸��� ���� model�� config ������ ���� */
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

    /* �� ���ϰ� ���� ������ �̿��Ͽ� Net ��ü net�� ���� */
    Net net = readNet(model, config);

    if (net.empty()) {
        cerr << "Net open failed!" << endl;
        return -1;
    }

    Mat frame;
    while (true) {
        cap >> frame; // ī�޶��� �� �������� frame ������ ����
        if (frame.empty())
            break;

        /* frame ������ �̿��Ͽ� ��Ʈ��ũ �Է� ����� �����ϰ�, ��Ʈ��ũ ���� ����� res ��Ŀ� ���� */
        Mat blob = blobFromImage(frame, 1, Size(300, 300), Scalar(104, 177, 123));
        net.setInput(blob);
        Mat res = net.forward();

        Mat detect(res.size[2], res.size[3], CV_32FC1, res.ptr<float>());

        /* ��� ��Ŀ��� �ŷڵ� ���� 0.5���� ������ ���� */
        for (int i = 0; i < detect.rows; i++) {
            float confidence = detect.at<float>(i, 2);
            if (confidence < 0.5)
                continue;

            /* �� ���� �簢�� ������ ���� ��� ��ǥ(x1, y1)�� ���� �ϴ� ��ǥ(x2, y2)�� ��� */
            int x1 = cvRound(detect.at<float>(i, 3) * frame.cols);
            int y1 = cvRound(detect.at<float>(i, 4) * frame.rows);
            int x2 = cvRound(detect.at<float>(i, 5) * frame.cols);
            int y2 = cvRound(detect.at<float>(i, 6) * frame.rows);

            /* frame ���󿡼� �� ���� ������ ��� �簢���� �׸���, �� �ŷڵ��� ��� */
            Rect faceROI(Point(x1, y1), Point(x2, y2)); // �� ������ ���� �������� ����
            rectangle(frame, faceROI, Scalar(0, 255, 0));

            String label = format("Face: %4.3f", confidence);
            putText(frame, label, Point(x1, y1 - 1), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 255, 0));

            // ������ �󱼿� ���ؼ��� �������� ������ ����
            open_close(frame, faceROI);
        }

        imshow("frame", frame);
        if (waitKey(1) == 27)
            break;
    }

    return 0;
}

void open_close(Mat& frame, Rect faceROI) {
    
    // �� ROI ������ �������� ������ �����մϴ�.
    Mat face = frame(faceROI); // Mat Ŭ������ ����Ͽ� ���� �̹��� frame�� faceROI�� ���ǵ� ������ �����ϱ� ���� Mat ��ü face�� ����
    cvtColor(face, face, COLOR_BGR2GRAY); // �׷��̽����Ϸ� ��ȯ

    // ���� �˰������� �ڵ� ����ȭ�� �����ϰ�, �� ����� binary�� ����
    Mat binary;
    threshold(face, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

    // 3 x 3 ������ ���� ��Ҹ� �̿��Ͽ� ���� ������ �����ϰ�, �� ����� dst�� ����
    Mat dst;
    morphologyEx(binary, dst, MORPH_OPEN, Mat()); 

    // ����� ǥ���ϱ� ���� ���� �̹����� �����մϴ�. ����̹����� �÷� �̹����� ��ȯ�մϴ�.
    //cvtColor(dst, dst, COLOR_GRAY2BGR);
    //dst.copyTo(frame(faceROI)); // dst �̹����� frame(faceROI)�� ����
    imshow("dst", dst);
}
