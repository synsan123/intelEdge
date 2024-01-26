/* 레이블링 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* 영상의 레이블링 예제 */
void labeling_basic()
{
	/* 이진 영상에서 흰색으로 구분된 각 객체 영역에 고유의 번호를 지정하는 레이블링 기법 */
	/* 레이블링이란 영상 내부에 있는 각 객체의 위치, 크기, 모양 등 특징을 분석할 때 사용 */
	/* 이진화를 통해 배경과 객체를 구분하였다면, 다시 각각의 객체를 구분하고 분적하는 작업인 레이블링이 필요함 */
	/* 레이블링은 연상 내에 존재하는 객체 픽셀 집합에 고유 번호를 매기는 작업으로 구성 요소 레이블링이라고도 함 */
	/* 각 객체의 위치와 크기 등 정보를 추출하는 작업은 객체 인식을 위한 전처리 과정으로 자주 사용됨 */
	/* 검은색은 배경, 흰색은 객체로 간주 */
	/* 하나의 객체는 한 개 이상의 인접한 픽셀로 이루어지며, 하나의 객체를 구성하는 모든 픽셀에는 같은 레이블 번호가 지정됨 */
	/* 특정 픽셀과 이웃한 픽셀의 연결 관계는 크게 두 가지 방식으로 정의 */
	/* 1. 특정 픽셀의 상하좌우로 붙어 있는 픽셀끼리 연결되어 있다고 정의하는 4-방향 연결성 */
	/* 2. 상하좌우대각선으방향으로 인접한 픽셀도 연결되어 있다고 간주하는 8-방향 연결성 */
	/* 이진 영상에 레이블링을 수행하면 각각의 객체 영역에 고유의 번호가 매겨진 2차원 정수 행렬이 만들어짐 */
	/* 이러한 정수 행렬을 레이블 맵이라고 부름 */
	/* 레이블링을 수행하는 알고리즘은 매우 다양하게 존재하지만 모두 같은 형태의 레이블 맵을 생성 */

	/* 레이블링을 수행하는 기본적인 함수 이름은 connectedComponents() */
	/* connectedComponents(image, labels, connectivity = 8, ltype = CV_32S) */
	/* image = threshold, adaptiveThreshold 등의 함수를 통해 얻은 이진 입력 영상을 지정 */
	/* labels = 출력 레이블 맵 행렬, connectivity = 연결성, ltype = 출력 행렬 타입(CV_16S도 가능) */
	/* 반환값은 레이블 개수, 반환값이 N이면 0 ~ N-1까지의 레이블 번호가 존재, 0은 배경, N-1은 실제 객체 개수 */




	/* 입력 영상과 동일한 형태의 그레이스케일 영상 src를 생성, uchar 자료형 배열 data를 픽셀 데이터로 사용되는 임시 Mat객체를 생성 */
	/* 모든 원소에 255를 곱한 결과 행렬을 src에 저장 */
	uchar data[] = { // 8x8 행렬 사용 
		0,0,1,1,0,0,0,0,
		1,1,1,1,0,0,1,0,
		1,1,1,1,0,0,0,0,
		0,0,0,0,0,1,1,0,
		0,0,0,1,1,1,1,0,
		0,0,0,1,0,0,1,0,
		0,0,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,
	};

	Mat src = Mat(8, 8, CV_8UC1, data) * 255;

	Mat labels; /* 함수를 실행하고 레이블 맥을 labels 행렬에 저장 */
	int cnt = connectedComponents(src, labels);

	cout << "src : \n" << src << endl; /* src , labels, connectedComponets함수가 반환한 정수를 화면에 출력 */
	cout << "labes : \n" << labels << endl;
	cout << "number of labels" << cnt << endl;
}

/* 레이블링을 이용하여 객체의 바운딩 박스 그리기 (레이블링 응용) */
void labeling_stats()
{

	/* 레이블링을 수행한 후에는 각각의 객체 영역이 어느 위치에 어느 정도의 크기로 존재하는지 확인할 필요가 있음 */
	/* 레이블 맵과 각 객체 영역의 통계 정보를 한꺼번에 반환하는 connectedComponestsWithStats함수를 제공 */
	/* connectedComponestsWithStats(image, labels, stats, centroids, connectivity, ltype) */
	/* stats = 각각의 레이블 영역에 대한 통계 정보를 담은 행렬. CV_32S */
	/* centroids = 각각의 레이블 영역의 무게 중심 좌표 정보를 담은 행렬. CV_64F */
	/* 위의 두 인자에는 Mat 자료형 변수를 지정함 */
	/* stats 행렬의 행 개수는 레이블 개수와 같고, 열 개수는 항상 5임 */
	/* 첫 번쨰 행은 배경 영역 정보를, 두 번째 행부터는 1번부터 시작하는 객체 영역에 대한 정보를 담고 있음 */
	/* 각 열은 차례대로 특정 영역을 감싸는 바운딩 박스의 (x, y ,width, height) 그리고 면적(해당 영역의 픽셀 개수) 정보를 담고 있음 */
	/* centroids 행렬의 행 개수는 레블 개수와 같고 열 개수는 항상 2임 */
	/* 각 열은 차례대로 각 영역의 무게 중심 x좌표, y좌표를 저장 */
	Mat src = imread("keyboard.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	/* bin영상에 대해 레이블링을 수행하고 각 객체 영역의 통계 정보를 추출 */
	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	/* 배경 영역을 제외하고 흰색 객체 영역에 대해서만 for문을 수행 */
	for (int i = 1; i < cnt; i++) {
		int* p = stats.ptr<int>(i);

		if (p[4] < 20) continue; // 객체의 픽셀 개수가 20보다 작으면 잡음이라고 간주하고 무시함 

		rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 255, 255), 2); // 검출된 객체를 감싸는 바운딩 박스를 노란색으로 그림
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main()
{
	//labeling_basic();
	labeling_stats();

	return 0;
}