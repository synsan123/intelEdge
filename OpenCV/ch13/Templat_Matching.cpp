/* 13장 객체 검출 */
/* 템플릿 매칭 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* 입력 영상에서 작은 크기의 부분 영상 위치를 찾아내고 싶은 경우 템플릿 매칭을 사용 
   여기서 템플릿은 찾고자 하는 대상이 되는 작은 크기의 영상을 의미함 
   템플릿 매칭은 작은 크기의 템플릿 영상을 입력 영상 전체 영역에 대해 이동하면서 가장 비슷한 위치를 수치적으로 찾아내는 방식 
   
   예를 들어 레나 영상에서 레나 얼굴 영역 부분 영상을 템플릿으로 사용하여 템플릿 매칭을 수행하는 과정으로 템플릿 매칭의 동작방식 설명 
   템플릿 영상을 입력 영상 전체 영역에 대해 이동하면서 템플릿 영상과 입력 영상 부분 영상과의 유사도 또는 비유사도를 계산 
   
   유사도를 계산할 경우, 템ㅍ플릿 영상과 비슷한 부분 영상 위치에서 값이 크게 나타나고, 비유사도의 경우 값이 작게 나옴 
   
   템플릿 매칭 함수 matchTemplate(image, templ, result, method, mask = noArray()) 
   templ = 템플릿 영상. 입력 영상보다 작거나 같아야 하며, 타입은 같아야 함
   result = 출력 비교 결과를 저장할 행렬. CV_32FC1 타입 
   method = 템플릿 매칭 비교 방법 , 406p 참고
   mask = 찾고자 하는 템플릿의 마스크 영상, templ과 같은 크기 및 타입이어야 함. TM_SQDOFF, TM_CCORR_NORMED 방법에서만 지원됨 
   
   템플릿 매칭으로 생겨나는 유사도 맵 또는 비유사도 맵은 result인자로 반환. image = W x H 이고 templ = w x h인 경우 
   result 행렬의 크기는 (W - w + 1) x (H - h + 1)로 결정됨 
   
   여러 매칭 방법 중에서 정규화된 상관관계(상관계수) 매칭 방법이 좋은 결과를 제공하나 수식이 복잡하고 연산량이 많음(TM_CCORR_NORMED)
   제곱차 매칭 방법(TM_SQDIFF)은 result 결과 행렬에서 최솟값 위치를 가장 매칭이 잘 된 위치로 선택해야 함.
   TM_CCORR or TM_CCOEFF(상관관계 or 상관계수 매칭 방법)은 result 결과 행렬에서 최댓값 위치를 가장 매칭이 잘 된 위치로 선택해야 함 
   result 행렬에서 최솟값 위치 or 최댓값 위치는 minMaxLoc함수를 사용하여 알아낼 수 있음 */
void template_matching()
{
	Mat img = imread("circuit.bmp", IMREAD_COLOR);
	Mat templ = imread("rectan.bmp", IMREAD_COLOR);

	if (img.empty() || templ.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	img = img + Scalar(50, 50, 50); // 영상 밝기를 50만큼 증가

	Mat noise(img.size(), CV_32SC3); // 입력 영상에 표준 편차가 10인 가우시안 잡음을 추가. 
	randn(noise, 0, 10);
	add(img, noise, img, Mat(), CV_8UC3);

	/* 템플릿 매칭 결과 행렬 res는 -1 부터 1사이의 실수 */
	Mat res, res_norm; // res_norm = 템플릿 매칭으로 계산된 유사도 행렬을 그레이스케일 형식 영상으로 나타낸 것
	matchTemplate(img, templ, res, TM_CCOEFF_NORMED); // 정규화된 상관계수 매칭 방법을 사용하여 템플릿 매칭을 수행
	normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8UC1); // 템플릿 매칭 결과 행렬 res의 모든 원소 값을 0~255 사이로 정규화하고 타입을 CV_8UC1으로 변환하여 res_norm 영상에 저장

	/* res 행렬에서 최댓값 위치를 찾아 maxloc에 저장함 */
	/* 이 위치에서의 최댓값 maxv는 템플릿 매칭이 잘 되었는지를 가늠하는 척도로 사용할 수 있음 */
	/* 1에 가까울수록 매칭이 잘 되었다고 가늠함 */
	double maxv;
	Point maxloc;
	minMaxLoc(res, 0, &maxv, 0, &maxloc);
	cout << "maxv : " << maxv << endl;

	/* img 영상에 템플릿 매칭으로 찾은 위치를 빨간색 사각형으로 표시함 */
	rectangle(img, Rect(maxloc.x, maxloc.y, templ.cols, templ.rows), Scalar(0, 0, 255), 2);

	imshow("templ", templ);
	imshow("res_norm", res_norm);
	imshow("img", img);

	waitKey();
	destroyAllWindows();
}

#if 0
int main()
{
	template_matching();

	return 0;
}
#endif