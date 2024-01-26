/* 딥러닝과 OpenCV DNN 모듈 */
/* 508p부터 읽으셈 */
#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

#if 0
/* 학습된 모델 파일을 이용한 필기체 숫자 인식 예제 */
void on_mouse(int event, int x, int y, int flags, void* userdata);

int main()
{
	Net net = readNet("mnist_cnn.pb"); // mnist_cnn.pb 파일을 이용하여 Net 객체 net을 생성

	if (net.empty()) {
		cerr << "Network load failed!" << endl;
		return -1;
	}

	Mat img = Mat::zeros(400, 400, CV_8UC1); // 400 x 400 크기의 빈 영상 img를 생성. 이후 img영상에 숫자 그림을 그려서 숫자를 인식

	imshow("img", img);
	setMouseCallback("img", on_mouse, (void*)&img); // 마우스 콜백 함수를 등록. 마우스 콜백 함수에 사용자 데이터로 img 영상 주소를 전달

	while (true) {
		int c = waitKey();

		if (c == 27) {
			break;
		}
		else if (c == ' ') { // 스페이스바를 누르면 dnn 인식을 수행
			Mat blob = blobFromImage(img, 1 / 255.f, Size(28, 28)); // img영상을 28 x 28 크기로 줄이고, 픽셀 값을 0부터 1사이로 정규화하여 네트워크에 입력으로 전달할 블롭 inputBlob을 생성. inputBlob은 4차원 행렬이고, 1 x 1 x 28 x 28 크기 
			net.setInput(blob); // inputBlob을 네트워크 입력으로 설정
			Mat prob = net.forward(); // 네트워크를 순방향으로 실행하고, 네트워크 출력을 prob행렬에 저장. prob행렬은 1 x 10 크기. CV_32FC1 타입

			/* prob 행렬에서 최댓값과 최댓값 위치를 찾음. 최댓값 maxVal은 최대 확률 값, 최댓값 위치 maxLoc.x는 가장 확률이 높은 숫자를 나타냄*/
			double maxVal;
			Point maxLoc;
			minMaxLoc(prob, NULL, &maxVal, NULL, &maxLoc);
			int digit = maxLoc.x;

			cout << digit << " (" << maxVal * 100 << "%)" << endl; // 인식된 숫자와 확률을 콘솔 창에 출력함

			img.setTo(0); // img영상을 검은색으로 초기화하고, 화면에 출력함
			imshow("img", img);
		}
	}

	return 0;
}
/* 마우스를 이용하여 img영상에 숫자를 그리는 코드. */
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
/* 구글넷 영상 인식 예제 프로그램 */
int main(int argc, char* argv[]) // 명령행 인자를 받을 수 있도록 main()함수 인자를 설정
{
	// Load an image
	/* 프로그램 실행 시 명령행 인자를 지정하지 않으면 space_shuttl.jpg 파일을 입력 영상으로 사용하고, 명령행 인자가 있으면 해당 영상 파일을 입력 영상을 사용 */
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

	Net net = readNet("bvlc_googlenet.caffemodel", "deploy.prototxt"); //두 파일을 이용하여 Net의 객체 net을 생성

	if (net.empty()) {
		cerr << "Network load failed!" << endl;
		return -1;
	}

	// Load class names
	/* 아래 파일을 한 줄 씩 읽어서 해당 문자열을 classNames 벡터에 저장*/
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
	/* 입력 영상 img를 이용하여 입력 블롭 inputBlob을 생성하고, 이를 네트워크에 입력으로 주고 실행함. 실행 결과는 prob행렬에 저장됨 */
	Mat inputBlob = blobFromImage(img, 1, Size(224, 224), Scalar(104, 117, 123));
	net.setInput(inputBlob, "data");
	Mat prob = net.forward();

	// Check results & Display
	/* prob행렬에서 최댓값과 최댓값 위치를 찾음. 최댓갑 위치는 인식된 영상 클래스 번호이고, 최댓값은 확률을 의미 */
	double maxVal;
	Point maxLoc;
	minMaxLoc(prob, NULL, &maxVal, NULL, &maxLoc);
	/* 인식된 클래스 이름과 확률을 문자열 형태로 영상 위에 나타냄 */
	String str = format("%s (%4.2lf%%)", classNames[maxLoc.x].c_str(), maxVal * 100);
	putText(img, str, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 0, 255));
	imshow("img", img);

	waitKey();
	return 0;
}
#endif

/* 사용할 모델 파일과 구성 파일 이름을 각각 model과 config 변수에 저장 */
//const String model = "res10_300x300_ssd_iter_140000_fp16.caffemodel";
//const String config = "deploy.prototxt"; // 위 2행 오류 걸려서 안됌 
const String model = "opencv_face_detector_uint8.pb"; // => 텐서플로에서 훈련된 모델 파일과 구성파일을 사용하려면 이 2행을 사용
const String config = "opencv_face_detector.pbtxt";

int main(void)
{/* 컴퓨터에 연결된 기본 카메라 장치를 열어서 cap에 저장. 없으면 usb 연결한 카메라 사용. 그 떄는 0이 아니라 1을 사용 */
	VideoCapture cap(1);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return -1;
	}
	/* 모델 파일과 구성 파일을 이용하여 Net객체 net을 생성. */
	Net net = readNet(model, config);

	if (net.empty()) {
		cerr << "Net open failed!" << endl;
		return -1;
	}
	/* 카메라의 매 프레임을 frame 변수에 저장 */
	Mat frame;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;
		/* frame 영상을 이용하여 네트워크 입력 블롭을 설정하고, 네트워크 실행 결과를 res행렬에 저장 */
		Mat blob = blobFromImage(frame, 1, Size(300, 300), Scalar(104, 177, 123));
		net.setInput(blob);
		Mat res = net.forward();

		Mat detect(res.size[2], res.size[3], CV_32FC1, res.ptr<float>());
		/* 결과 행렬에서 신뢰도 값이 0.5보다 작으면 무시 */
		for (int i = 0; i < detect.rows; i++) {
			float confidence = detect.at<float>(i, 2);
			if (confidence < 0.5)
				break;
			/* 얼굴 검출 사각형 영역의 좌측 상단 좌표(x1, y1)과 우측 하단 좌표(x2, y2)를 계산 */
			int x1 = cvRound(detect.at<float>(i, 3) * frame.cols);
			int y1 = cvRound(detect.at<float>(i, 4) * frame.rows);
			int x2 = cvRound(detect.at<float>(i, 5) * frame.cols);
			int y2 = cvRound(detect.at<float>(i, 6) * frame.rows);
			/* frame 영상에서 얼굴 검출 영역에 녹색 사각형을 그리고, 얼굴 신뢰도를 출력 */
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