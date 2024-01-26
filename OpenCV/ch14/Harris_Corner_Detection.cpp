/* 14장 지역 특징점 검출과 매칭 */
/* 코너 검출 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* Harris 코너 검출과 FAST 코너 검출 방법

   크기 불변 특징점 검출의 기본이 되는 방법이므로 제대로 이해할 필요가 있음 

   템플릿 매칭은 입력 영상에서 특정 객체 위치를 찾을 때 유용하게 사용할 수 있으나 영상의 크기가 바뀌거나 회전이 되면 작동이 제대로 안됌 
   
   영상에서 특징이란 영상으로부터 추출할 수 있는 유용한 정보를 의미하며 평균 밝기, 히스토그램, 엣지, 직선 성분, 코너 등이 특징이 될 수 있음
   엣지, 직선 성분, 코너처럼 영상의 일부 영역에서 추출할 수 잇는 특징을 지역 특징이라고 함
   코너는 엣지의 방향이 급격하게 변하는 부분으로서 삼각형의 꼭지점이나 연필 심처럼 뾰족하게 튀어나와 있는 부분이 코너가 될 수 있음
   코너는 다른 지역 특징에 비해 분별력이 높고 대체로 영상 전 영역에 골고루 분포하기 때문에 영상을 분석하는데 유용함
   코너처럼 한 점의 형태로 표현할 수 있는 특징을 특징점이라고 하며, 특징점은 키포인트 또는 관심점이라고 부르기도 함
   코너는 엣지나 평탄한 영역에 비해 변별력이 높아서 그 위치를 파악하기 수월함 
   
   해리스에 의해 정의된 코너 응답 함수 R은 입력 영상 각각의 픽셀에서 정의되는 실수 값이며
   R이 0보다 충분히 큰 양수이면 코너 점이라고 간주함
   R이 0에 가까운 실수이면 평탄한 영역, 0보다 작은 음수이면 엣지라고 판별함 
   
   해리스 코너 응답 함수 값을 계산하는 cornerHarris()함수를 제공. 해리스 코너 응답 함수 값을 반환
   이 값에 적절한 임계값 연산을 적용하면 영상에서 코너 위치를 모두 찾을 수 있음 
   cornerHarris(src, dst, blockSize, ksize, k, borderType = BORDER_DEFAULT) 
   dst = 해리스 코너 응답 함수 값을 저장할 행렬. CV_32FC1. 이 값이 사용자가 지정한 임계값보다 크면 코너 점으로 판단할 수 있음
   blockSize = 행렬 M 연산에 사용할 이웃 픽셀 크기. 픽셀 주변 blockSize x blockSize 윈도우를 설정하여 행렬 M을 계산함 
   ksize = 소벨 연산자를 위한 커널 크기
   k = 해리스 코너 검출 상수. 보통 0.04 ~ 0.06 사이의 값을 사용 
   borderType = 가장자리 픽셀 확장 방식 
    
   하나의 코너 위치에 사용자 지정 임계값보다 큰 픽셀이 여러 개 발생할 수 있으므로,
   간단한 비최대 억제를 수행하여 지역 최댓값 위치만 코너로 판별하는 것이 좋음 */

void corner_harris()
{
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	/* src 영상으로부터 해리스 코너 응답 함수 행렬 harris를 구함 */
	Mat harris;
	cornerHarris(src, harris, 3, 3, 0.04);

	/* harris 행렬 원소 값 범위를 0 ~ 255로 정규화하고, 타입을 CV_8UC1으로 변환하여 harris_norm에 저장 
	   harris_norm은 그레이스케일 영상 형식을 따르며, 해리스 코너 응답 함수 분포를 영상 형태로 화면에 표시하기 위해 만듬 */
	Mat harris_norm;
	normalize(harris, harris_norm, 0, 255, NORM_MINMAX, CV_8UC1);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (int j = 1; j < harris.rows - 1; j++) {
		for (int i = 1; i < harris.cols - 1; i++) {
			if (harris_norm.at<uchar>(j, i) > 120) { // harris_norm 영상에서 값이 120보다 큰 픽셀을 코너로 간주함 
				/* 간단한 비최대 억제를 수행함. (i, j)위치에서 주변 네 개의 픽셀을 비교하여 지역 최대인 경우에만 dst 영상에
				   빨간색 원으로 코너를 표시함 */
				if (harris.at<float>(j, i) > harris.at<float>(j - 1, i) &&
					harris.at<float>(j, i) > harris.at<float>(j + 1, i) &&
					harris.at<float>(j, i) > harris.at<float>(j, i - 1) &&
					harris.at<float>(j, i) > harris.at<float>(j, i + 1)) {
					circle(dst, Point(i, j), 5, Scalar(0, 0, 255), 2);
				}
			}
		}
	}

	imshow("src", src);
	imshow("harris_norm", harris_norm);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

/* Harris 검출 방법은 복잡한 연산을 필요로 하기 때문에 연산 속도가 느리다는 단점이 있음
   이러한 코너 검출 방법과 달리 FAST코너 검출은 단순한 픽셀 값 비교 방법을 통해 코너를 검출함
   FAST 방법은 영상의 모든 픽셀에서 픽셀을 둘러싸고 있는 16개의 주변 픽셀과 밝기를 비교하여 코너 여부를 판별함 
   예를 들어 점 p가 있는데 점 p가 코너인지를 판별하기 위해 p점 주변 1번부터 16번 픽셀과의 밝기를 비교함 
   만약 주변 16개의 픽셀 중에서 점 p보다 충분히 밝거나 또는 충분히 어두운 픽셀이 9개 이상 연속으로 존재하면 코너로 정의
   
   FAST 코너 방법은 특정 코너 점 주변 픽셀들도 함께 코너로 검출하는 경우가 많기 때문에 주변 코너 픽셀 중에서
   가장 코너에 적합한 픽셀을 선택하는 비최대 억제 작업을 추가적으로 수행하는 것이 좋음
   FAST 코너 방법에는 코너 점과 주변 16개 점과의 픽셀 값 차이 합을 코너 점수로 정의하고
   인접한 코너 중에서 코너 점수가 가장 큰 코너만 최종 코너로 선택함 
   
   FAST 코너 검출 방법을 구현한 FAST()함수
   FAST(image, keypoints, threshold, nonmaxSuppression = true) 
   image = 그레이스케일 영상. 
   keypoints = 검출된 특징점을 표현하는 keyPoint 객체의 벡터(vector<keyPoint>자료형>. keyPoint::pt멤버 변수에 코너 점 과표가 저장됨
   threshold = 중심 픽셀 값과 주변 픽셀 값과의 차이 임계값 
   nonmaxSuppression = 비최대 억제 수행 여부, true이면 수행 
   FAST함수에 의해 결정된 코너 점 중에서 i번째 코너의 x, y좌표는 keypoints[i].pt.x와 keypoints[i].pt.y코드로 접근할 수 있음*/

void corner_fast()
{
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	/* src영상에서 FAST방법으로 코너 점을 검출합니다. 밝기 차이 임계값으로 60을 지정하였고, 비최대 억제를 수행하도록 설정하였음 
	   검출된 모든 코너 점 좌표는 keypoints변수에 저장함 */
	vector<KeyPoint> keypoints;
	FAST(src, keypoints, 60, true);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	/* 검출된 모든 코너 점에 반지름이 5인 빨간색 원을 그림 */
	for (KeyPoint kp : keypoints) {
		Point pt(cvRound(kp.pt.x), cvRound(kp.pt.y));
		circle(dst, pt, 5, Scalar(0, 0, 255), 2);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main()
{
	//corner_harris();
	corner_fast();
	return 0;
}