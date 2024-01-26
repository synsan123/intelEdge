/* �����װ� OpenCV DNN ��� */
/* 508p���� ������ */
#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

#if 0
/* �н��� �� ������ �̿��� �ʱ�ü ���� �ν� ���� */
void on_mouse(int event, int x, int y, int flags, void* userdata);

int main()
{
	Net net = readNet("mnist_cnn.pb"); // mnist_cnn.pb ������ �̿��Ͽ� Net ��ü net�� ����

	if (net.empty()) {
		cerr << "Network load failed!" << endl;
		return -1;
	}

	Mat img = Mat::zeros(400, 400, CV_8UC1); // 400 x 400 ũ���� �� ���� img�� ����. ���� img���� ���� �׸��� �׷��� ���ڸ� �ν�

	imshow("img", img);
	setMouseCallback("img", on_mouse, (void*)&img); // ���콺 �ݹ� �Լ��� ���. ���콺 �ݹ� �Լ��� ����� �����ͷ� img ���� �ּҸ� ����

	while (true) {
		int c = waitKey();

		if (c == 27) {
			break;
		}
		else if (c == ' ') { // �����̽��ٸ� ������ dnn �ν��� ����
			Mat blob = blobFromImage(img, 1 / 255.f, Size(28, 28)); // img������ 28 x 28 ũ��� ���̰�, �ȼ� ���� 0���� 1���̷� ����ȭ�Ͽ� ��Ʈ��ũ�� �Է����� ������ ��� inputBlob�� ����. inputBlob�� 4���� ����̰�, 1 x 1 x 28 x 28 ũ�� 
			net.setInput(blob); // inputBlob�� ��Ʈ��ũ �Է����� ����
			Mat prob = net.forward(); // ��Ʈ��ũ�� ���������� �����ϰ�, ��Ʈ��ũ ����� prob��Ŀ� ����. prob����� 1 x 10 ũ��. CV_32FC1 Ÿ��

			/* prob ��Ŀ��� �ִ񰪰� �ִ� ��ġ�� ã��. �ִ� maxVal�� �ִ� Ȯ�� ��, �ִ� ��ġ maxLoc.x�� ���� Ȯ���� ���� ���ڸ� ��Ÿ��*/
			double maxVal;
			Point maxLoc;
			minMaxLoc(prob, NULL, &maxVal, NULL, &maxLoc);
			int digit = maxLoc.x;

			cout << digit << " (" << maxVal * 100 << "%)" << endl; // �νĵ� ���ڿ� Ȯ���� �ܼ� â�� �����

			img.setTo(0); // img������ ���������� �ʱ�ȭ�ϰ�, ȭ�鿡 �����
			imshow("img", img);
		}
	}

	return 0;
}
/* ���콺�� �̿��Ͽ� img���� ���ڸ� �׸��� �ڵ�. */
Point ptPrev(-1, -1);

void on_mouse(int event, int x, int y, int flags, void* userdata)
{
	Mat img = *(Mat*)userdata;

	if (event == EVENT_LBUTTONDOWN) {
		ptPrev = Point(x, y);
	}
	else if (event == EVENT_LBUTTONUP) {
		ptPrev = Point(-1, -1);
	}
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) {
		line(img, ptPrev, Point(x, y), Scalar::all(255), 40, LINE_AA, 0);
		ptPrev = Point(x, y);

		imshow("img", img);
	}
}
#endif

#if 0
/* ���۳� ���� �ν� ���� ���α׷� */
int main(int argc, char* argv[]) // ����� ���ڸ� ���� �� �ֵ��� main()�Լ� ���ڸ� ����
{
	// Load an image
	/* ���α׷� ���� �� ����� ���ڸ� �������� ������ space_shuttl.jpg ������ �Է� �������� ����ϰ�, ����� ���ڰ� ������ �ش� ���� ������ �Է� ������ ��� */
	Mat img;

	if (argc < 2)
		img = imread("space_shuttle.jpg", IMREAD_COLOR);
	else
		img = imread(argv[1], IMREAD_COLOR);

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	// Load network

	Net net = readNet("bvlc_googlenet.caffemodel", "deploy.prototxt"); //�� ������ �̿��Ͽ� Net�� ��ü net�� ����

	if (net.empty()) {
		cerr << "Network load failed!" << endl;
		return -1;
	}

	// Load class names
	/* �Ʒ� ������ �� �� �� �о �ش� ���ڿ��� classNames ���Ϳ� ����*/
	ifstream fp("classification_classes_ILSVRC2012.txt");

	if (!fp.is_open()) {
		cerr << "Class file load failed!" << endl;
		return -1;
	}

	vector<String> classNames;
	string name;
	while (!fp.eof()) {
		getline(fp, name);
		if (name.length())
			classNames.push_back(name);
	}

	fp.close();

	// Inference
	/* �Է� ���� img�� �̿��Ͽ� �Է� ��� inputBlob�� �����ϰ�, �̸� ��Ʈ��ũ�� �Է����� �ְ� ������. ���� ����� prob��Ŀ� ����� */
	Mat inputBlob = blobFromImage(img, 1, Size(224, 224), Scalar(104, 117, 123));
	net.setInput(inputBlob, "data");
	Mat prob = net.forward();

	// Check results & Display
	/* prob��Ŀ��� �ִ񰪰� �ִ� ��ġ�� ã��. �ִ� ��ġ�� �νĵ� ���� Ŭ���� ��ȣ�̰�, �ִ��� Ȯ���� �ǹ� */
	double maxVal;
	Point maxLoc;
	minMaxLoc(prob, NULL, &maxVal, NULL, &maxLoc);
	/* �νĵ� Ŭ���� �̸��� Ȯ���� ���ڿ� ���·� ���� ���� ��Ÿ�� */
	String str = format("%s (%4.2lf%%)", classNames[maxLoc.x].c_str(), maxVal * 100);
	putText(img, str, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 0, 255));
	imshow("img", img);

	waitKey();
	return 0;
}
#endif

/* ����� �� ���ϰ� ���� ���� �̸��� ���� model�� config ������ ���� */
//const String model = "res10_300x300_ssd_iter_140000_fp16.caffemodel";
//const String config = "deploy.prototxt"; // �� 2�� ���� �ɷ��� �ȉ� 
const String model = "opencv_face_detector_uint8.pb"; // => �ټ��÷ο��� �Ʒõ� �� ���ϰ� ���������� ����Ϸ��� �� 2���� ���
const String config = "opencv_face_detector.pbtxt";

int main(void)
{/* ��ǻ�Ϳ� ����� �⺻ ī�޶� ��ġ�� ��� cap�� ����. ������ usb ������ ī�޶� ���. �� ���� 0�� �ƴ϶� 1�� ��� */
	VideoCapture cap(1);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return -1;
	}
	/* �� ���ϰ� ���� ������ �̿��Ͽ� Net��ü net�� ����. */
	Net net = readNet(model, config);

	if (net.empty()) {
		cerr << "Net open failed!" << endl;
		return -1;
	}
	/* ī�޶��� �� �������� frame ������ ���� */
	Mat frame;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;
		/* frame ������ �̿��Ͽ� ��Ʈ��ũ �Է� ����� �����ϰ�, ��Ʈ��ũ ���� ����� res��Ŀ� ���� */
		Mat blob = blobFromImage(frame, 1, Size(300, 300), Scalar(104, 177, 123));
		net.setInput(blob);
		Mat res = net.forward();

		Mat detect(res.size[2], res.size[3], CV_32FC1, res.ptr<float>());
		/* ��� ��Ŀ��� �ŷڵ� ���� 0.5���� ������ ���� */
		for (int i = 0; i < detect.rows; i++) {
			float confidence = detect.at<float>(i, 2);
			if (confidence < 0.5)
				break;
			/* �� ���� �簢�� ������ ���� ��� ��ǥ(x1, y1)�� ���� �ϴ� ��ǥ(x2, y2)�� ��� */
			int x1 = cvRound(detect.at<float>(i, 3) * frame.cols);
			int y1 = cvRound(detect.at<float>(i, 4) * frame.rows);
			int x2 = cvRound(detect.at<float>(i, 5) * frame.cols);
			int y2 = cvRound(detect.at<float>(i, 6) * frame.rows);
			/* frame ���󿡼� �� ���� ������ ��� �簢���� �׸���, �� �ŷڵ��� ��� */
			rectangle(frame, Rect(Point(x1, y1), Point(x2, y2)), Scalar(0, 255, 0));

			String label = format("Face: %4.3f", confidence);
			putText(frame, label, Point(x1, y1 - 1), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 255, 0));
		}

		imshow("frame", frame);
		if (waitKey(1) == 27)
			break;
	}

	return 0;
}