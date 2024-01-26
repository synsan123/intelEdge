/* 컬러 영상 처리 기법 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

#if 0
int main()
{
	/* 컬러 히스토그램 평활화 */
	/* equalizeHist()함수는 GrayScale에만 가능함 */
	/* 컬러 히스토그램 평활화를 수행하려면 직접 구현하여야 함 */
	/* 컬러 영상에 대한 히스토그램 평활화를 수행하려면 입력 영상을 밝기 정보와 색상 정보로 분리한 후, 밝기 정보에 대해서만 평활화를 수행 */
	/* 예를 들어 색 공간을 YCrCb로 변경한 후, Y성분에 대해서만 평활화를 진행. Cr,Cb는 그대로 유지. 그리고 합치면 평활화 결과 영상을 얻을 수 있음 */
	/* 이렇게 되면 색상 정보는 전혀 변경되지 않으므로, 입력 영상의 색감이 그대로 유지되며, 오직 밝기 성분에 대해서만 명암비가 증가하게 됨 */
	
	Mat src = imread("pepper.bmp", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	Mat src_ycrcb; // src 영상을 YCrCb색 공간으로 변경하여 src_ycrcb에 저장
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	vector<Mat> ycrcb_planes; // src_ycrcb영상의 채널을 분리하여 ycrcb_planes에 저장
	split(src_ycrcb, ycrcb_planes);

	equalizeHist(ycrcb_planes[0], ycrcb_planes[0]); // Y성분에 해당하는 ycrcb_planes[0]영상에 대해서만 평활화를 수행

	Mat dst_ycrcb; // ycrcb_planes벡터에 들어 있는 3영상을 합쳐서 dst_ycrcb영상을 생성
	merge(ycrcb_planes, dst_ycrcb);

	Mat dst; // dst_ycrcb영상의 색 공간을 BGR색 공간으로 변환하여 dst에 저장
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();

	return 0;
}
#endif


#if 0
int lower_hue = 40, upper_hue = 80; // 두 개의 트랙바 위치를 저장할 정수형 변수를 전역 변수로 선언
Mat src, src_hsv, mask; // main함수와 트랙바 콜백 함수 on_hue_changed함수에서 함께 사용할 Mat객체를 전역 변수로 선언

void on_hue_changed(int, void*) // 트랙바 콜백 함수
{
	Scalar lowerb(lower_hue, 100, 0); // 사용자가 지정한 하한값과 상한값을 이용하여 lowerb, upperb객체를 생성.
	Scalar upperb(upper_hue, 255, 255); // 채도의 범위는 100 ~ 255, 명도의 영향은 무시하도록 0 ~ 255로 설정
	inRange(src_hsv, lowerb, upperb, mask); // src_hsv 영상에서 HSV 색 성분 범위가 lowerb ~ upperb 사이인 위치의 픽셀만 흰색으로 설정한 mask 영상을 생성

	imshow("mask", mask);
}

int main(int argc, char* argv[])
{
	/* 색상 범위 지정에 의한 영역 분할 */
	/* 컬러 영상을 다루는 응용에서 자주 요구되는 기법은 특정 색상 영역을 추출하는 작업이다 */
	/* 예를 들어 입력 영상에서 빨간색 픽셀을 모두 찾아내면 빨간색 객체의 위치와 크기를 알 수 있음 */
	/* HSV등의 색상 정보가 따로 설정되어 있는 색 공간을 사용하는 것이 유리 */
	/* 행렬의 원소 값이 특정 범위 안에 있는지 확인하려면 inRange() 함수를 사용 */
	/* inRange(src, lowerb, upperb, dst)*/
	/* lowerb, upperb = 하한 값, 상한 값. 주로 Mat or Scalar 객체를 지정 */
	/* 입력 영상의 픽셀 값이 지정한 밝기 또는 색상 범위에 포함되어 있으면 흰색, 그렇지 않으면 검은색으로 채워진 마스크 영상 dst를 반환 */
	/* 그레이스케일 영상을 입력 영상으로 사용할 경우, 특정 밝기 값 범위에 있는 픽셀 영역을 추출할 수 있음 */
	/* Mat객체를 지정할 경우, src의 모든 픽셀에 각기 다른 하한 값과 상한 값을 지정할 수 있음 */
	/* Scalar객체 또는 int, double과 같은 자료형을 지정할 경우에는 src의 모든 픽셀에 동일한 하한 값과 상한 값이 적용됨 */

	/* H가 40 ~ 80 즉 중간값이 60이면 녹색, 100 ~ 140 즉 중간값이 120이면 파란색 */
	/* S인 채도의 범위는 100 ~ 255, V인 명도의 범위는 0 ~ 255임 */
	src = imread("candies.png", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	cvtColor(src, src_hsv, COLOR_BGR2HSV); // HSV로 변경 후 src_hsv에 저장

	imshow("src", src);

	namedWindow("mask");
	createTrackbar("Lower Hue", "mask", &lower_hue, 179, on_hue_changed); // 색상의 하한 값과 상한 값을 조절할 수 있는 트랙바를 생성
	createTrackbar("Upper Hue", "mask", &upper_hue, 179, on_hue_changed); // 색상의 최댓값을 179로 설정. 트랙바 콜백 함수를 on_hue_changed함수로 설정
	on_hue_changed(0, 0); // 프로그램이 처음 실행될 때 영상이 정상적으로 출력되도록 트랙바 콜백 함수를 강제로 호출

	waitKey();
	destroyAllWindows();

	return 0;
}
#endif


int main()
{
	/* 히스토그램 역투영 */
	/* HSV색 공간은 원색에 가까운 색상을 찾기에는 효과적이지만 사람의 피부색처럼 미세한 변화가 있거나 색상 값을 수치적으로 지정하기 어려운 경우네는 적합하지 않음 */
	/* 입력 영상에서 찾고자 하는 객체의 기준 영상을 미리 가지고 있다면 컬러 히스토그램 정보를 이용하여 비슷한 색상 영역을 찾을 수 있음 */
	/* 즉, 기준 영상으로부터 찾고자 하는 객체의 컬러 히스토그램을 미리 구하고, 주어진 입력 영상에서 해당 히스토그램에 부합하는 영역을 찾아내는 방식 */
	/* 이처럼 주어진 히스토그램 모델과 일치하는 픽셀을 찾아내는 기법을 히스토그램 역투영이라고 한다 */
	/* calcBackProject(images, nimages, channels, hist, backProject, ranges, scale = 1, uniform = true) */
	/* images = 입력 영상의 배열 또는 주소, nimages = 입력 영상 개수, channels = 역투영 계산 시 사용할 채널 번호 배열 */
	/* hist = 입력 히스토그램, backProject = 출력 히스토그램 역투영 영상(입력 영상과 같은 크기, 깊이를 갖는 1채널 행렬) */
	/* ranges = 각 차원의 히스토그램 빈(가로) 범위를 나타내는 배열의 배열 */
	/* scale = 히스토그램 역투영 값에 추가적으로 곱할 값. uniform = 히스토그램 빈의 간격이 균등한지를 나타내는 플래그 */
	/* hist는 calcHist함수를 이용하여 구함. */

	Mat ref, ref_ycrcb, mask;
	ref = imread("ref.png", IMREAD_COLOR); // 피부색 히스토그램 정보를 추출할 기준 영상 ref.png파일을 불럼
	mask = imread("mask.bmp", IMREAD_GRAYSCALE); // 기준 영상에서 피부색이 있는 위치를 흰색으로 표시한 마스크 영상 파일을 불럼 
	cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);

	Mat hist; // 기준 영상에서 피부색 영역의 CrCb 2차원 히스토그램을 계산하여 hist에 저장
	int channels[] = { 1, 2 };
	int cr_bins = 128;
	int cb_bins = 128;
	int histSize[] = { cr_bins, cb_bins };
	float cr_range[] = { 0, 256 };
	float cb_range[] = { 0, 256 };
	const float* ranges[] = { cr_range, cb_range };

	calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);

	Mat src, src_ycrcb; 
	src = imread("kids.png", IMREAD_COLOR);
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	Mat backproj; // 앞서 구한 히스토그램 hist를 이용하여 입력 영상에서 히스토그램 역투영을 수행. 결과는 backproj에 저장
	calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges, 1, true);

	imshow("src", src);
	imshow("backproj", backproj);

	waitKey();
	destroyAllWindows();

	return 0;
}