/* 유용한 OpenCV 기능 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

#if 0
int main()
{
	/* 마스크 연산 */
	/* setTo 함수는 행렬의 픽셀 값을 설정하기도 하지만 마스크 연산을 지원하는 함수이기도 함 */
	/* (행렬 원소에 설정할 값, 마스크 인자 지정(=마스크 행렬)) */
	/* 예제 */

	Mat src = imread("lenna.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_smile.bmp", IMREAD_GRAYSCALE);

	if (src.empty() || mask.empty()) {
		cerr << "image load fail" << endl;
		return -1;
	}

	src.setTo(Scalar(0, 255, 255), mask); // mask영상에서 픽셀 값이 0이 아닌 위치에서만 src영상 픽셀을 노란색으로 설정.

	imshow("src", src);
	imshow("mask", mask);

	waitKey();
	destroyAllWindows();
}
#endif

#if 0
int main()
{
	/* 행렬 복사 함수 copyTo함수이기도 하지만 마스크 연산을 지원하는 함수 */
	/* 행렬 복사 함수 일 때는 (복사본이 저장될 행렬) */
	/* 마스크 연산으로 쓸 때는 (복사본이 저장될 행렬, 마스크 인자 지정(=마스크 행렬)) */
	/* 예제 */
	Mat src = imread("airplane.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_plane.bmp", IMREAD_GRAYSCALE);
	Mat dst = imread("field.bmp", IMREAD_COLOR);
	imshow("src", src);
	imshow("mask", mask);
	imshow("dst_origin", dst);
	if (src.empty() || mask.empty() || dst.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	src.copyTo(dst, mask); // mask영상에서 흰색 영역 위치에서만 src 영상 픽셀 값을 dst로 복사

	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}
#endif

#if 0
int main()
{
	/* 연산 시간 측정 */ /* relese모드로 빌드하여 실행해야 함 */
	/* 여러 단계로 구성된 영ㅅ아 처리 시스템을 개발하는 경우, 각 단계에서 소요되는 연산 시간을 측정하는데 사용 */
	/* getTickCount함수와 getTickFrequency함수를 사용*/
	/* Count는 특정 시점부터 현재까지 발생한 틱 횟수를 반환 */
	/* tick은 클럭처럼 매우 빠르게 증가하는 성능 측정 계수를 의미 */
	/* 실제 연산 시간을 알아내기 위해서는 틱 횟수 차이를 시스템의 틱 주파수로 나누어 작업이 동반되어야 함 */
	/* 틱 주파수란 1초 동안 발생하는 틱 횟수를 의미함.*/
	/* Count는 현재 틱(tick) 횟수, Frequency는 시스템의 초당 틱 횟수를 반환 */
	/* 특정 연산이 수행되는 시간을 측정하기 위해서는 두 함수를 같이 조합해서 사용하여야 함 */
	/* 예제 */

	//int64 t1 = getTickCount();
	//my_func(); // 이 함수 호출 전후에 각각 Count를 호출하여 틱 횟수 차이를 계산
	//int64 t2 = getTickCount();
	//double ms = (t2 - t1) * 1000 / getTickFrequency();

	/* TickMeter 클래스를 사용하여 쉽게 측정가능 */
	/* 예제 */
	
	/*TickMeter tm;
	tm.start();

	my_func();

	tm.stop();
	double ms = tm.getTimeMilli();*/
	
	/* TickMeter를 이용한 영상의 반전 시간 측정 예제 */
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	Mat dst(src.rows, src.cols, src.type()); //src의 행,열,타입을 복사하여 dst 생성

	TickMeter tm;
	tm.start();

	/* 영상의 모든 픽셀을 반전시킴 */
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = 255 - src.at<uchar>(j, i); // at함수는 각 원소에 접근하기 위한 함수. uchar는 자료형으로 보통 Grayscale 의미
		}
	}

	tm.stop();
	cout << "Image Inverse took " << tm.getTimeMilli() << "ms. " << endl;
}
#endif


int main()
{
	/* 주어진 행렬의 전체 원소 합 또는 평균을 구하는 함수 */
	/* sum(입력행렬), mean(입력행렬, 마스크 영상) => 마스크 영상을 지정하여 특정 영역의 원소 평균을 구할 수 도 있음.(써도되고 안써도 되고) */
	/* 예제 */
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);

	cout << "Sum : " << (int)sum(img)[0] << endl;  // Scalar 자료형을 반환. 첫 번째 원소 값을 참조하기 위해 [0]을 사용
	cout << "Mean : " << (int)mean(img)[0] << endl;

	/* 주어진 행렬의 최솟값, 최댓값을 찾는 함수 */
	/* minMaxLoc(입력영상(단일채널), 최소값을 받을 double형 변수의 주소, 최대값을 받을 double형 변수의 주소, 최솟값 위치 좌표를 받을 Point형 변수의 주소, 최대값 위치 좌표를 받을 Point형 변수의 주소, 마스크 영상) */
	/* minMaxLoc(src, minVal, maxVal, minLoc, maxLoc, mask) */
	/* 예제 */
	double minVal, maxVal;
	Point minPos, maxPos;
	minMaxLoc(img, &minVal, &maxVal, &minPos, &maxPos);

	cout << "minVal : " << minVal << " at " << minPos << endl;
	cout << "maxVal : " << maxVal << " at " << maxPos << endl;

	/* 행렬의 norm 값을 정규화하거나 또는 원소 값 범위를 특정 범위로 정규화할 때 사용할 수 있는 함수 */
	/* normalize(src, dst, alpha, beta, norm_type, dtype, mask) */
	/* (입력행렬, 출력행렬, (norm 정규화인 경우)목표 norm값( (원소 값 범위 정규화인 경우는 최솟값), (원소 값 범위 정규화인 경우)최댓값, 정규화 타입, 결과 영상의 타입, 마스크 영상) */
	/* NORM_MINMAX타입으로 많이 사용. 특히 실수로 구성된 행렬을 그레이스케일 영상 형태로 변환하고자 할 때 사용하면 유용 */
	/* 예제 */
	Mat src = Mat_<float>({ 1,5 }, { -1.f,-0.5f,0.f,0.5f,1.f });

	Mat dst;
	normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1); // -1에서 1사이의 실수로 구성된 1x5행렬을 0부터 255 사이의 정수 행렬로 변환

	cout << "src : " << src << endl;
	cout << "dst : " << dst << endl;

	/* 실수 값의 반올림 연산을 위해 cvRound 함수를 사용 */
	/* cvRound(double value), cvRound(float value), value = 입력 실수 값 */
	/* 이외에 올림은 cvCeil, 내림은 cvFloor 사용 */
	/* 예제 */
	cout << "cvRound(2.5) : " << cvRound(2.5) << endl;
	cout << "cvRound(2.51) : " << cvRound(2.51) << endl;
	cout << "cvRound(3.4999) : " << cvRound(3.4999) << endl;
	cout << "cvRound(3.5) : " << cvRound(3.5) << endl;
}