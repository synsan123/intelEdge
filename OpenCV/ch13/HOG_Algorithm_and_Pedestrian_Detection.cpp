/* HOG알고리즘과 보행자 검출 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* 다랄과 트릭스가 발표한 HOG알고리즘을 이용한 보행자 검출 기능에 대해 설명 
   HOG(Histograms of Oriented Gradients)는 그래디언트 방향 히스토그램을 의미함 
   사람이 서 있는 영상에서 그래디언트를 구하고, 그래디언트의 크기와 방향 성분을 이용하여 사람이 서 있는 형태에 대한 특정 벡터를 정의함. 
   머신 러닝의 일종인 소포트 벡터 머신(SVM)알고리즘을 이용하여 입력 영상에서 보행자 위치를 검출하는 방법을 제안
   
   HOG는 기본적으로 64 x 128 크기의 영상에서 계산함.
   HOG는 먼저 입력 영상으로부터 그래디언트를 계산함. 그래디언트는 크기와 방향 성분으로 계산하며, 방향성분은 0 ~ 180도까지로 설정함 
   그 다음은 입력 영상을 8 x 8 크기 단위로 분할. 각각의 8 x 8 부분 영상을 셀(cell)이라고 부름
   셀은 가로 8개, 세로 16개 생성됨 ( 64 x 128 영상에서 )
   각각의 셀로부터 그래디언트 방향 성분에 대한 히스토그램을 구하며, 이때 방향 성분을 20도 단위로 구분하면 총 아홉 개의 빈(가로)으로 구성된
   방향 히스토그램이 만들어짐
   그리고 인접한 4개의 셀을 합쳐서 블록(block)이라고 정의함 
   블록 하나에서는 총 36개의 실수 값으로 이루어진 방향 히스토그램 정보가 추출됨 ( 9개 빈 x 4 = 36 ) 
   블록은 가로와 세로 방향으로 각각 한 개의 셀만큼 이동하면서 정의함 
   그러므로 블록은 가로 7개, 세로 15개로 정의할 수 있음 ( 64 x 128 영상에서 )
   결국 105개의 블록이 추출될 수 있고, 전체 블록에서 추출되는 방향 히스토그램 실수 값 계수는 105 x 36 = 3780이 됨 
   3780개의 실수 값이 HOG 특징 벡터 역할을 함. 
   
   보행자 및 보행자가 아닌 영상에서 HOG 특징 벡터를 추출. 이 두 특징 벡터를 구분하기 위해 SVM알고리즘을 사용
   SVM은 두 개의 클래스를 효과적으로 분리하는 능력을 가진 머신 러닝 알고리즘 
   
   HOG 알고리즘을 구현한 HOGDescriptor 클래스를 제공함. 이용하려면 먼저 객체를 생성해야 함. 
   보행자 검출이 목적이라면 기본 생성자를 사용하여 객체를 생성하면 됨.
   그러면 위의 설명 처럼 셀, 블록, 그래디언트 방향 히스토그램, 3780개의 float실수로 구성됨
   
   HOGDescriptor::getDefaultPeopleDetector()는 미리 계산된 보행자 검출을 위한 HOG 기술자 정보를 반환하는 정적 멤버 함수 
   똑바로 서 있는 사람을 검출하는 용도로 훈련된 분류기 계수를 반환 
   정적 멤버 함수이기 때문에 소스코드 작성 시에 클래스 이름과 함께 사용해야 함.
   
   HOGDescriptor::setSVMDetector(svmdetector)함수에 위의 계수를 등록하면 됨
   svmdetector는 선형 SVM 분류기를 위한 계수
   
   HOG 기술자를 이용하여 실제 입력 영상에서 객체 영역을 검출하려면 HOGDescriptor::detectMultiScale()멤버 함수를 사용함
   hog.detectMultiScale(frame, detected)식으로 사용 
   detectMultiScale(img, foundLocations, foundWeights, hitThreshold = 0, winStride = Size(), padding = Size(), scale = 1.05, finalThreshold = 2.0, useMeanshiftGrouping = false)
   detectMultiScale(img, foundLocations, hitThreshold = 0, winStride = Size(), padding = Size(), scale = 1.05, finalThreshold = 2.0, useMeanshiftGrouping = false)
   foundLocations = 출력 검출된 사각형 영역 정보, foundWeights = 출력 검출된 사각형 영역에 대한 신뢰도
   hitThreshold = 특징 벡터와 SVM 분류 평면까지의 거리에 대한 임계값 
   winStride = 셀 윈도우 이동 크기. Size() 지정 시 셀 크기와 같게 설정함 
   padding = 패딩 크기, scale = 검색 윈도우 크기 확대 비율, finalThreshold = 검출 결정을 위한 임계값 
   useMeanshiftGrouping = 겹쳐진 검색 윈도우를 합치는 방법 지정 플래그 
   위 함수는 입력 영상 img에서 다양한 크기의 객체 사각형 영역을 검출하고, 그 결과를 std::vector<Rect> 타입의 인자 foundLocations에 저장 */

/* 실행할 때 Release 모드 사용.
   많은 연산량을 필요로 하기 때문에 Debug모드는 느림 */
int main()
{
	VideoCapture cap("people.mp4");

	if (!cap.isOpened()) {
		cerr << "Fail" << endl;
		return -1;
	}

	HOGDescriptor hog; // 객체 hog를 선언
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector()); // 보행자 검출을 위한 용도로 훈련된 SVM 분류기 계수를 등록함

	Mat frame;
	while (true) {
		cap >> frame;
		if (frame.empty()) break;

		vector<Rect> detected; // 동영상 매 프레임마다 보행자 검출을 수행. 검출된 사각형 정보는 detected 변수에 저장함 
		hog.detectMultiScale(frame, detected);

		for (Rect r : detected) { // 검출된 사각형 정보를 이용하여 임의의 색상으로 3픽셀 두께의 사각형을 그림 
			Scalar c = Scalar(rand() % 256, rand() % 256, rand() % 256);
			rectangle(frame, r, c, 3);
		}

		imshow("frame", frame);

		if (waitKey(10) == 27) break;
	}

	return 0;
}
