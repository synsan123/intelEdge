/* 영상의 이진화 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* 전역 이진화라고 함 */
#if 0
void on_threshold(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;

	Mat dst;
	threshold(src, dst, pos, 255, THRESH_BINARY); // 사용자가 지정한 트랙바 위치(pos)를 이용하여 이진화를 수행하고, 그 결과를 dst에 저장

	imshow("dst", dst);
}

int main(int argc, char* argv[]) // 프로그램 실행 시 명령행 인자를 받을 수 있도록 argc와 argv인자를 지정함
{
	/* 영상의 이진화는 영상의 각 픽셀을 두 개의 분류(0 또는 255)로 나누는 작업 */
	/* 관심 있는 객체 영역과 배경 영역을 구분하기 위한 용도로 사용됨 */
	/* 또는 관심 영역과 비관심 영역으로 구분하는 용도로 사용함 */
	/* 영상의 이진화는 기본적으로 영상의 각 픽셀 값을 이용함 */
	/* 영상의 픽셀 값이 특정 값보다 크면 255로 설정, 작으면 0으로 설정 */
	/* 이 때 각 픽셀과의 크기 비교 대상이 되는 값을 임계값이라고 함 (0 ~ 255사이의 정수를 지정할 수 있음) */
	/* 이진화는 threshold()함수를 이용하여 수행. 임계값을 이용한 다양한 연산을 지원하는 함수임 */
	/* threshold(src, dst, thresh, maxval, type) */
	/* thresh = 임계값, maxval = THRESH_BINARY or THRESH_BINARY_INV방법을 사용할 때 결과 영상의 최댓값 */
	/* type = 임계값 연산 방법. 361p 참고 */
	/* 영상을 이진화하려면 maxval = 255를 지정하고 type = 위의 THRESH_BINARY or THRESH_BINARY_INV를 사용 */
	/* THRESH_OTSU or THRESH_TRIANGLE은 임계값을 자동으로 결정할 때 사용 */
	/* 임계값 설정이 필요없음. 그러므로 0으로 설정하면 됨. */
	/* type 부분에 사용할 때는 THRESH_BINARY | THRESH_OTSU와 같은 방식으로 사용 */
	/* 위의 타입을 사용하여 임계값을 확인하고 싶다면 */
	/* int th = (int)threshold(src, dst, 0, 255, THRESH_BINARY | THRESH_OTSU)을 사용 */

	/* Mat 영상을 부등호 연산자 재정의를 이용하여 간단하게 이진화 할 수 있음 */
	/* Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	   Mat dst = src > 128; */ 
	/* 위와 같이 코드를 짤 수 있음. src의 각 픽셀 값이 128보다 크면(참이면) 255를, 작으면 dst에 0을 설정함 */

	Mat src;

	if (argc < 2) // 명령행 인자 개수가 2보다 작으면 if문을 
		src = imread("neutrophils.png", IMREAD_GRAYSCALE);
	else // 프로그램 실행 파일 이름 뒤에 사용할 영상 파일 이름을 명시하면 해당 파일을 입력 영상으로 사용
		src = imread(argv[1], IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	imshow("src", src);

	namedWindow("dst");
	createTrackbar("Threshold", "dst", 0, 255, on_threshold, (void*)&src); // dst창에 "Threshold"이름의 트랙바를 생성
	setTrackbarPos("Threshold", "dst", 128); // 프로그램이 처음 실행될 때 트랙바 위치가 128이 되도록 설정하여 on_threshold함수가 처음에 한 번 실행됨

	waitKey();
	destroyAllWindows();

	return 0;
}
#endif

/* 적응형 이진화 */

void on_trackbar(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;

	int bsize = pos;
	if (bsize % 2 == 0) bsize--;
	if (bsize < 3) bsize = 3;

	Mat dst;
	/* 트랙바에서 설정한 블록 크기를 이용하여 적응형 이진화를 수행함, 가우시안 가중 평균을 사용, 블록 평균에서 5를 뺸 값을 임계값으로 사용 */
	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, bsize, 5);

	imshow("dst", dst);
}

int main()
{
	/* 전역 이진화는 균일하지 않은 조명 환경에서 촬영된 영상에 대해 전역 이진화를 수행하면 객체와 배경이 적절하게 분리되지 않는 경우가 발생함 */
	/* 적응형 이진화 = 각 픽셀마다 서로 다른 임계값을 사용하는 이진화 */
	/* 영상의 모든 픽셀에서 정해진 크기의 사각형 블록 영역을 설정하고, 블록 영역 내부의 픽셀 값 분포로부터 고유의 임계값을 결정하여 이진화하는 방식 */
	/* adpativeThreshold(src, dst, maxValue, adaptiveMethod, thresholdType, blockSize, C) */
	/* maxValue = 이진화 결과 영상의 최댓값 */
	/* adaptiveMethod = 적응형 이진화에서 블록 평균 계산 방법 지정 (ADAPTIVE_THRESH_MEAN_C or ADAPTIVE_THRESH_GAUSSIAN_C) 중 하나 지정 */
	/* thresholdType = THRESH_BINARY or THRESH_BINARY_INV 중 하나 지정 */
	/* blockSize = 임계값 계산 시 사용하는 블록 크기, 3과 같거나 보다 큰 홀수를 지정해야 함 */
	/* C = 임계값 조정을 위한 상수, 블록 평균에서 C를 뺀 값을 임계값으로 사용함 */
	/* adaptiveMethod를 설정하면 blockSize x blockSize 크기의 주변 영역 픽셀로부터 산술 평균을 구함 / 가우시안 마스크를 적용하여 가우시안 가중 평균을 계산함 */

	Mat src = imread("sudoku.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	imshow("src", src);

	namedWindow("dst");
	createTrackbar("Block Size", "dst", 0, 200, on_trackbar, (void*)&src); // dst창에 "Threshold"이름의 트랙바를 생성
	setTrackbarPos("Block Size", "dst", 11);

	waitKey();
	destroyAllWindows();

	return 0;
}