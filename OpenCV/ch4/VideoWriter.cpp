/* VideoWriter Ŭ����. ������ ���� �����ϱ� */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap(0); // ī�޶� ��� �ȉ�.

	if (!cap.isOpened()) {
		cerr << "Camera open Failed" << endl;
		return -1;
	}

	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	double fps = cap.get(CAP_PROP_FPS);
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	int delay = cvRound(1000 / fps);

	VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));

	if (!outputVideo.isOpened()) {
		cout << "File open Failed" << endl;
		return -1;
	}

	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty()) break;

		inversed = ~frame;
		outputVideo << inversed; // inversed�� ��� ������ outputVideo�� �߰�

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27) break;
	}

	destroyAllWindows();
}