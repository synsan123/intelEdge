/* 모폴로지 연산 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* 모폴로지 연산은 영상 내부 객체의 형태와 구조를 분석하고 처리하는 기법 */
/* 그레이스케일 영상과 이진 영상에 모두 적용이 가능 */
/* 주로 이진 영상에서 객체의 모양을 변형하고 잡음을 제거하는 용도로 사용 */
/* 모폴로지는 형태 또는 모양에 관한 학문을 의미 */
/* 모폴로지 연산을 정의하려면 먼저 구조 요소를 정의해야 함 */
/* 구조 요소는 마치 필터링에서 사용되는 마스크처럼 모폴로지 연산의 동작을 결정하는 작은 크기의 행렬 */
/* 구조 요소는 다양한 크기와 모양으로 정의할 수 있음 */
/* 대부분 3x3 정방형 구조 요소를 많이 사용 */
/* 모폴로지 연산 결과가 저장될 위치를 나타내는 고정점 = 구조 요소의 중심 */

/* 이진 영상의 침식과 팽창 예제 프로그램 */
void erode_dilate()
{
	/* 모폴로지 연산에서 가장 기본이 되는 연산은 침식(erosion)과 팽창(dilation) */
	/* 이진 영상의 침식 연산은 객체 영역의 외곽을 골고루 깎아 내는 연산으로 전체적으로 객체 영역은 축소되고 배경은 확대됨 */
	/* 구조 요소를 영상 전체에 대해 스캔하면서, 구조 요소가 객체 영역 내부에 완전히 포함될 경우 고정점 위치 픽셀을 255로 설정 */
	/* 이진 영상의 팽창 연산은 객체 외곽을 확대하는 연산 */
	/* 객체 영역은 확대되고 배경 영역은 축소 */
	/* 구조 요소를 영상 전체에 대해 이동시키면서, 구조 요소와 객체 영역이 한 픽셀이라도 만날 경우 고정점 위치 픽셀을 255로 설정 */
	/* 구조 요소는 OPEN_CV에서 원소 값이 0 또는 1로 구성된 CV_8UC1타입의 Mat행렬로 표현 */
	/* 구조 요소 행렬에서 값이 1인 원소만을 이용하여 구조 요소의 모양을 결정 */
	
	/* 구조 요소 행렬을 생성하는 함수 */
	/* getStructuringElement(shape, ksize, anchor = Point(-1,-1) */
	/* shape = 구조 요소의 모양, ksize = 구조 요소의 크기, anchor =  MORPH_CROSS모양의 구조 요소에서 십자가 중심 좌표 */
	/* (-1, -1)이면 구조 요소 중앙을 십자가 중심 좌표로 사용 */
	/* kszie = 홀수 사용. shape = MORPH_RECT or MORPH_CROSS, MORPH_ELLIPSE 사용 */

	/* 침식 연산 함수 */
	/* erode(src, dst, kernel, anchor = (-1,-1), iterations = 1, borderType = BORDER_CONSTANT, borderValue = morphologyDefaultBorderValue()) */
	/* kernel = 구조 요소를 지정하면 3x3 사각형 구조 요소를 사용, 그 외에는 위의 getStructuringElement를 사용하여 만듬 */
	/* anchor = 고정점 위치, iterations = 반복 횟수, borderType = 가장자리 픽셀 확장 방식 */
	/* borderValue = borderType이 BORDER_CONSTANE인 경우, 확장된 가장자리 픽셀을 채울 값 */
	/* kernel에 Mat() or noArray()를 지정하면 3x3 정방형 구조 요소를 사용 */

	/* 팽창 연산 함수 */
	/* dilate() = erode와 매개변수가 동일 */

	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU); // src 영상에 대해 오츠 알고리즘으로 자동 이진화를 수행하고 bin에 저장

	Mat dst1, dst2;
	erode(bin, dst1, Mat());
	dilate(bin, dst2, Mat());

	imshow("src", src);
	imshow("bin", bin);
	imshow("erode", dst1);
	imshow("dilate", dst2);

	waitKey();
	destroyAllWindows();
}

/* 이진 영상의 열기과 닫기 예제 프로그램 */
void open_close()
{
	/* 모폴로지 기법 중에서 열기와 닫기 연산 */
	/* 침식과 팽창 연산을 이용하여 쉽게 구현할 수 있음 */
	/* 열기 연산은 입력 영상에 대하여 침식 연산을 수행한 후, 다시 팽창 연산을 수행하는 연산 */
	/* 닫기 연산은 입력 영상에 대하여 팽창 연산을 수행한 후, 다시 침식 연산을 수행하는 연산 */
	/* 침식과 팽창 연산을 적용하는 순서에 따라 서로 다른 효과가 발생 ( 객체 영역의 크기가 크게 바뀌지는 않음 ) */
	/* 열기 연산은 침식 연산을 먼저 수행하기 때문에 한두 픽셀짜리 영역이 제거된 후, 팽창 연산이 수행됨 */
	/* 그 결과 이진 영상에 존재하는 작은 크기의 객체가 효과적으로 제거됨 */
	/* 닫기 연산은 객체 내부의 작은 구멍이 메워짐. 결과적으로 작은 구멍을 제거함 */

	/* 모폴로지 열기와 닫기는 morphologyEx()함수를 이용하여 수행 */
	/* morphologyEx(src, dst, op, kernel, anchor, iterations, borderType, borderValue) */
	/* op를 제외한 나머지는 erode, dilate함수와 동일한 매개변수를 가짐 */
	/* op = 모폴로지 연산 방법을 지정 */
	/* MORPH_ERODE, MORPH_DILATE, MORPH_OPEN, MORPH_CLOSE, MORPH_GRADIENT 사용 */

	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat dst1, dst2;
	morphologyEx(bin, dst1, MORPH_OPEN, Mat());
	morphologyEx(bin, dst2, MORPH_CLOSE, Mat());

	imshow("src", src);
	imshow("bin", bin);
	imshow("opening", dst1);
	imshow("closing", dst2);

	waitKey();
	destroyAllWindows();
}

int main()
{
	//erode_dilate();
	open_close();

	return 0;
}