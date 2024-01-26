/* 크기 및 타입 변환 함수 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	/* 행렬 원소의 타입을 다른 타입으로 변경하고 추가적으로 원소에 일정한 값을 더하거나 곱하는 함수 */
	Mat img1 = imread("lenna.bmp", IMREAD_GRAYSCALE);
	Mat img1f;
	img1.convertTo(img1f, CV_32FC1); // (img1f가 출력되는 행렬, 원하는 출력 행렬의 타입, 곱할 값, 더할 값) 으로 표현

	/* 주어진 행렬의 크기 또는 채널 수를 변경하는 함수. 다양하게 재정의되어있으므로 널리 사용되는 형식을 아래에 적음 */
	/* (새로운 채널 수, 새로운 행의 수)로 표현. 0을 사용하면 변경안함 */
	/* 새로운 행렬을 만드는 것이 아님, 원소값은 그대로 두고 형태를 변경시키는 것임 */
	/* 함수에 의해 반환된 행렬 원소 값을 변경하면 원본 행렬의 원소 값도 함께 바뀜 */
	uchar data1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	Mat mat1(3, 4, CV_8UC1, data1);
	Mat mat2 = mat1.reshape(0, 1); // 채널 수 고정, 행의 수 1개로 변경 => 1x12 행렬이 됨.
	cout << mat1 << endl;
	cout << mat2 << endl;

	/* 단순히 행렬의 행 크기를 변경하고 싶을 때 사용하는 함수 */
	/* (새로운 행 개수, 새로 추가되는 행의 원소 초기값 설정) or 새로운 행 개수만으로 표현 */
	/* 기존의 행렬의 행 개수보다 작으면 아래쪽 행 제거, 많으면 추가 */
	mat1.resize(5, 100);
	cout << mat1 << endl;

	/* 이미 존재하는 행렬에 원소 데이터를 추가하고 싶을 때 사용하는 함수 */
	/* 행렬의 맨 마지막 행에 추가할 원소 데이터(기존 행렬은 1열 짜리 행렬이어야 함) or 행렬의 맨 마지막 행에 추가할 행렬(기존 행렬과 열 개수가 동일해야 함 */
	/* 자료형 동일해야 함, 이 함수는 4가지 경우가 있음. 각각 2개씩 */
	Mat mat3 = Mat::ones(1, 4, CV_8UC1) * 255;
	mat1.push_back(mat3);
	cout << mat3 << endl;
	cout << mat1 << endl;

	cout << endl << endl;

	/* 맨 아래 행을 제거할 때 사용하는 함수 */
	/* 제거할 행 개수 입력 */
	Mat mat4 = Mat::ones(2, 4, CV_8UC1) * 199;
	cout << mat4 << endl << endl;
	mat4.pop_back(1);
	cout << mat4 << endl;

	return 0;
}