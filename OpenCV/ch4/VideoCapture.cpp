#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

#if 1
int main()
{
	VideoCapture cap(1); // ��ü ���� �� ��ǻ�Ϳ� ����� �⺻ ī�޶� ��� (ī�޶� ��� �ȵ�)

	if (!cap.isOpened()) {
		cerr << "Camera open failed" << endl;
		return -1;
	}

	cout << "Frame width : " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height : " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;

	Mat frame, inversed;
	while (true) {
		cap >> frame; // ���� �������� �޾ƿ��� >> ������ ������
		if (frame.empty())
			break;

		inversed = ~frame;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(10) == 27) // ����ڷκ��� 10ms ���� Ű���� �Է��� ��ٸ�. ESC�� �Է� �� ����
			break;
	}

	destroyAllWindows();
}
#endif

#if 0
int main()
{
	VideoCapture cap("stopwatch.avi"); // ������ ������ �ҷ��´�.

	if (!cap.isOpened()) {
		cerr << "Video open Failed" << endl;
		return -1;
	}

	cout << "Frame Width : " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame Height : " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	cout << "Frame count : " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl; // ��ü ������ ��

	double fps = cap.get(CAP_PROP_FPS); 
	cout << "FPS : " << fps << endl;

	int delay = cvRound(1000 / fps);

	Mat frame, inversed;
	while (true) {
		cap >> frame; // ī�޶�κ��� �� �������� �޾� �ͼ� frame ������ ����.
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
