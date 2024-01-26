/* 캐스케이드 분류기와 얼굴 검출 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;


/* OPEN_CV에서 제공하는 얼굴 검출 기능은 캐스케이드 분류기 알고리즘을 기반으로 함 
   비올라-존스 얼굴 검출 알고리즘은 기본적으로 영상을 24 x 24 크기로 정규화한 후, 유사-하르필터 집합으로부터 
   특징 정보를 추출하여 얼굴 여부를 판별함 
   유사-하르필터란 흑백 사각형이 서로 붙어 있는 형태로 구성된 필터
   유사-하르 필터 형태에서 흰색 영역 픽셀 값은 모두 더하고, 검은색 영역 픽셀 값은 모두 빼서 하나의 특징 값을 얻을 수 있음 

   사람의 정면 얼굴 형태가 전형적으로 밝은 영역과 어두운 영역이 정해져 있기 때문에 유사-하르 필터로 구한 특징 값은 얼굴을 판별하는 용도로 사용
   시간이 오래걸린다는 단점이 있지만 에이다부스트 알고리즘과 적분 영상을 이용하여 해결함 
   에이다부스트는 수많은 필터 중에서 얼굴 검출에 효과적인 유사-하르 필터를 선별하는 역할을 수행 
   그래도 입력 영상 전체에서 부분 영상을 추출하여 검사해야 하기 떄문에 여전히 연산량이 부담이 됨 
   
   캐스케이드 구조라는 새로운 방식을 도입하여 얼굴이 아닌 영역을 빠르게 걸러 내는 방식을 사용 
   비올라-존스 알고리즘을 구현하여 객체를 분류할 수 있는 CascadeClassifier 클래스를 제공 
   객체를 검출하려면 CascadeClaaifier 객체를 생성해야 함. 
   CascadeClassifier::load(filename)을 이용하여 분류기 XML 파일을 불러올 수 있음 
   
   OPEN_CV는 미리 훈련된 얼굴 검출, 눈 검출 등을 위한 분류기 XML파일 제공함 
   %OPENCV_DIR%\etc\haarcascades 폴더에서 찾을 수 있음   413p 참고
   
   CascadeClassifier classifier;
   classifier.load("haarcascade_fromtalface_default.xml); 또는 
   CascadeClassifier classifier("haarcascade_fromtalface_default.xml); 가능 
   
   객체 검출 함수
   CascadeClassifier.detectMultiScale(image, objects, scaleFactor, minNeighbors =3, flags = 0, minSize = Size(), maxSize = Size())
   object = 출력 검출된 객체의 사각형 좌표 정보. vector<Rect> 타입 , scaleFactor = 검색 윈도우 확대 비율. 1보다 커야 함 
   minNeighbors = 검출 영역으로 선택하기 위한 최소 검출 횟수, flags는 안씀
   minSize 및 maxSize = 검출할 객체의 최소 최대 크기 */

void detect_face()
{
	Mat src = imread("peopleMany.jpg");

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	/* 객체를 생성함과 동시에 파일을 불러옴 */
	CascadeClassifier classifier("haarcascade_frontalface_default.xml");

	if (classifier.empty()) {
		cerr << "XML Fail" << endl;
		return;
	}

	/* src 영상에서 얼굴을 검출하여 검출된 사각형 정보를 faces에 저장 */
	vector<Rect> faces;
	classifier.detectMultiScale(src, faces);

	/* 검출된 얼굴 영역 사각형을 src영상에 빨간색으로 그림 */
	for (Rect rc : faces) {
		rectangle(src, rc, Scalar(0, 0, 255), 2);
	}

	imshow("src", src);

	waitKey();
	destroyAllWindows();
}

void detect_eyes()
{
	Mat src = imread("mask.jpg");

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	/* 객체를 생성함과 동시에 파일을 불러옴 */
	CascadeClassifier face_classifier("haarcascade_frontalface_default.xml");
	CascadeClassifier eye_classifier("haarcascade_eye.xml");

	if (face_classifier.empty() || eye_classifier.empty()) {
		cerr << "XML Fail" << endl;
		return;
	}

	/* src 영상에서 얼굴을 검출하여 검출된 사각형 정보를 faces에 저장 */
	vector<Rect> faces;
	face_classifier.detectMultiScale(src, faces);

	for (Rect face : faces) {
		rectangle(src, face, Scalar(0, 0, 255), 2);

		Mat faceROI = src(face); // 입력 영상에서 검출한 사각형 얼굴 영역의 부분 영상을 추출하여 faceROI에 저장
		vector<Rect> eyes; // faceROI 영상에서 눈을 검출함 
		eye_classifier.detectMultiScale(faceROI, eyes);

		/* 검출한 눈의 중앙에 파란색 원을 그림. faceROI 영상은 src 영상의 부분 영상을 참조하므로 faceROI에 원을 그리면 src영상에도 원이 그려짐 */
		for (Rect eye : eyes) { 
			Point center(eye.x + eye.width / 2, eye.y + eye.height / 2);
			circle(faceROI, center, eye.width / 2, Scalar(255, 0, 0), 2, LINE_AA);
		}
	}
	imshow("src", src);

	waitKey();
	destroyAllWindows();
}


int main()
{
	//detect_face();
	detect_eyes();

	return 0;
}
