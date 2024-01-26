/* 엣지 검출 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void sobel_edge()
{
	/* 엣지란 한쪽 방향으로 픽셀 값이 급격하게 바뀌는 부분을 말한다. */
	/* 객체와 배경의 경계 또는 객체와 다른 객체의 경계에서 엣지가 발생함 */
	/* 엣지를 찾아내는 작업은 객체의 윤곽을 알아낼 수 있는 유용한 방법 */
	/* 엣지를 찾아내려면 픽셀 값의 변화율을 측정하여 변화율이 큰 픽셀을 선택 */
	/* 영상은 2차원 평면에서 정의된 함수. 엣지를 찾기 위해서는 가로방향, 세로방향으로 각각 미분해야 함 */
	/* 여기서 x축 편미분, y축 편미분은 자기 자신을 기준으로 앞뒤의 값을 빼고 2로 나눈 중앙 차분 방법을 이용함 */
	/* 그래디언트 = 함수의 x축 방향, y축 방향 미분을 한꺼번에 벡터로 표현한 것 */
	/* 2차원 영상에서 엣지를 찾는 기본적인 방법은 그래디언트 크기가 특정 값보다 큰 위치를 찾는 것 */
	/* 엣지 여부를 판단하기 위해 기준이 디는 값을 임계값 또는 문턱치라고 함 */
	/* 임계값이 높으면 밝기 차이가 급격하게 변하는 엣지 픽셀만 검출, 낮으면 약한 엣지 성분도 검출됨 */

	/* 가장 널리 사용되는 미분 근사 마스크는 소벨 필터 마스크(Sobel filter mask) */
	/* 잡음의 영향을 줄이기 위해 사용. 3x3크기의 마스크. x축과 y축 방향의 미분 마스크가 존재 */
	/* 현재행에 대해 중앙 차분 연산을 2회, 이전 행과 다음 행에서 중앙 차분 연산을 1회씩 수행 */
	/* 현재 행과 이웃 행에서의 픽셀 값 변화가 유사하다는 점을 이용하여 잡음의 영향을 줄임 */
	/* 현재 행에서 2번 하는 이유는 큰 가중치를 주기 위함 */
	/* Sobel(src, dst, ddepth, dx, dy, ksize = 3, scale = 1, delat = 0, borderType) */
	/* ddepth = -1이면 src와 같은 타입을 사용하는 dst 영상을 생성. dx, dy는 편미분 차수 */
	/* ksize = 3 이면 3x3, ksize = 1이면 1 x 3 또는 3 x 1 커널 사용 */

	/* Scharr filter(샤르 필터). 소벨보다 정확한 미분 계산을 수행하는 것으로 알려짐 */
	/* Scharr(src, dst, ddepth, dx, dy, scale = 1, delta = 0, borderType) */
	/* Sobel함수의 ksize = FILTER_SCHARR or -1 을 하면 샤르 필터가 적용됨 */

	/* 2차원 벡터의 x방향 좌표와 y방향 좌표를 이용하여 벡터의 크기를 계산하는 magnituede 함수 */
	/* magnitude(x, y, magnitude) => (벡터의 x, y좌표를 나타내는 실수 행렬 및 벡터의 크기를 나타내는 실수 행렬) */

	/* (x와 y)편미분이 저장된 두 개의 행렬이 있을 때, 그래디언트의 방향을 계산하고 싶다면 phase함수를 사용 */
	/* phase(x, y, angle, angleInDegrees) => angle은 벡터의 방향을 나타내는 실수 행렬, angleInDegrees는 true면 degree단위, 반대면 radian단위 사용 */

	/* 소벨은 그래디언트 키기만을 기준으로 엣지 픽셀을 검출하기 때문에 임계값에 민감하고 엣지 픽셀이 두겁게 표현되는 문제점이 있음 */

	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat dx, dy;
	Sobel(src, dx, CV_32FC1, 1, 0); // 1차 편미분을 구하여 dx와 dy 행렬에 저장. ddepth는 출력 영상의 자료형(type)설정
	Sobel(src, dy, CV_32FC1, 0, 1); // 1과 0은 x와 y의 차수

	Mat fmag, mag;
	magnitude(dx, dy, fmag); // 그래디언트 크기를 계산하여 fmag에 저장
	fmag.convertTo(mag, CV_8UC1); // fmag를 그레이스케일로 변경하여 mag에 저장

	Mat edge = mag > 150; // 엣지 판별을 위한 그래디언트 크기 임계값을 150으로 설정하여 엣지를 판별. mag가 150보다 크면 edge 255, 반대면 0

	imshow("src", src);
	imshow("mag", mag); // 그래디언트 크기를 그레이스케일 영상 형식으로 나타냄. 그래디언트가 255보다 크면 포화 연산에 의해 흰색으로 표현됨
	imshow("edge", edge); // 0, 255이니 이진 영상(black, white)

	waitKey();
	destroyAllWindows();
}

void canny_edge()
{
	/* 엣지 검출을 최적화 문제 관점으로 접근함으로써 소벨의 단점을 해결할 수 있는 방법을 제시 */
	/* 그래디언트의 크기와 방향을 모두 고려하여 좀 더 정확한 엣지 위치를 찾을 수 있음 */
	/* 엣지는 서로 연결되어 있는 가능성이 높다는 점을 고려하여 그래디언트 크기가 다소 약하게 나타나는 엣지도 찾을 수 있음 */
	/* 4개의 연산 과정을 거침 */
	/* 1. 가우시안 필터링. 잡음을 제거하기 위함. 영상이 부드러워져서 엣지의 세기도 감소할 수 있으므로 표준 편차를 적절히 조절해야 함 */
	/* 2. 그래디언트 계산. 소벨마스크를 적용한 후 그래디언트 크기와 뱡향을 모두 계산한다. */
	/* 3. 비최대 억제. 엣지가 두껍게 표현되는 현상을 방지하기 위해 사용. 그래디언트 크기가 국지적 최대인 픽셀만을 엣지 픽셀로 설정하는 기법 */
	/* 그래디언트 벡터의 방향과 같은 방향에 있는 인접 픽셀끼리만 국지적 최대 검사를 수행함. 가장 변화율이 큰 위치의 픽셀만 엣지로 검색됨 */
	/* 4. 이중 임계값을 이용한 히스테리시스 엣지 트래킹 */
	/* 하나의 임계값만 사용하면 환경 변화에 민감해짐. 그래서 두 개의 임계값을 사용 */
	/* 높은 임계값과 낮은 임계값 두 가지를 사용. 그래디언트 크기가 높은 임계값보다 크면 그 픽셀은 강한 엣지로 판단. */
	/* 낮은 임계값보다 작으면 엣지 픽셀이 아님. 그 사이이면 엣지일 수도 있고 아닐 수도 있다고 판단. 추가적 검사를 수행 (약한 엣지로 표현) */
	/* 히스테리시스 엣지 트래킹을 사용하여 약한 엣지 중에서 최종적으로 엣지로 판별할 픽셀을 선택 */
	/* 엣지가 대체로 상호 연결되어 있다는 점을 이용. 강한엣지와 연결되어 있으면 엣지로 판단. 아니면 아님 */

	/* Canny(image, edges, threshold1, threshold2, apertureSize = 3, L2gradient = false) */
	/* 첫 번째 Canny는 일반 영상을 입력으로 전달하여 엣지를 검출할 때 사용 */
	/* Canny(dx, dy, edges, threshold1, threshold2, L2gradient = false) */
	/* 두 번째 Canny는 이미 편미분 영상을 가지고 있을 때 사용 */
	/* image = 8비트 입력 영상, dx와 dy = 입력 영상의 편미분 영상. CV_16SC1 또는 CV_16SC3 */
	/* edges = 출력 엣지 영상. threshold1,2 = 히스테리시스 엣지 검출을 위한 임계값. apertureSize = 그래디언트 계산을 위한 소벨 마스크 크기 */
	/* L2gradient = 그래디언트 크기 계산 시 L2노름을 사용하려면 true. false는 L1노름을 사용 */
	/* 임계값은 보통 1:2 또는 1:3 비율로 지정*/

	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat dst1, dst2;
	Canny(src, dst1, 50, 100);
	Canny(src, dst2, 50, 150);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();

}


int main()
{
	//sobel_edge();
	canny_edge();

	return 0;
}