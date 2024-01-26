/* 컬러 영상 처리 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void color_inverse() // 컬러 영상의 픽셀 값 반전
{
	/* 컬러 영상에서 각 색상 성분 값은 uchar 자료형을 사용하여 표현 */
	/* 컬러 영상에서 하나의 픽셀은 세 개의 색상 성분(BGR)을 가지고 있으므로 한 픽셀을 정확하게 표현하려면 Vec3b 자료형을 사용 */
	/* Vec3b(vector 3byte)클래스의 크기는 3바이트이며 실제 3채널 컬러 영상의 한 픽셀이 차지하는 바이트 수와 같음.*/
	/* 영상에서 픽셀 값을 참조할 때는 Mat::at()함수를 사용함. 템플릿 함수이므로 자료형인 Vec3b를 명시해주어야 함 */
	/* 예) Vec3b& pixel = img.at<Vec3b>(0,0) => img객체에서 (0,0) 위치의 픽셀 값을 참조 */
	/* pixel은 (0,0)좌표에서 BGR색상 정보를 가리킴 */
	/* 참조이므로 pixel값이 변하면 (0,0)의 픽셀값도 변경됨 */
	/* Vec3b클래스는 []연산자 재정의를 이용하여 각 멤버 변수 값에 접근할 수 있음 */
	/* 예) uchar b1 = pixel[0], uchar g1 = pixel[1], uchar r1 = pixel[2] */

	/* Mat::ptr() 함수를 이용하여 컬러 영상의 특정 행 시작 주소를 얻어 올 때에도 Vec3b클래스를 자료형에 명시해야함 */
	/* Vec3b* ptr = img.ptr<Vec3b>(0) => img객체의 0번째 행 시작 픽셀 주소를 알고 싶다는 예 */
	/* ptr[0]은 (0,0)좌표 픽셀을 가리키며, 이는 Vec3b 자료형에 해당 */
	/* ptr[0]뒤에 []를 다시 한번 사용하면 해당 픽셀의 BGR성분값을 얻을 수 있음 */
	/* uchar b2 = ptr[0][0], uchar g2 = ptr[0][1], uchar r2 = ptr[0][2] => (0,0)픽셀의 BGR성분값 */

	/* 컬러 영상을 반전하려면 BGR의 색상 성분 값을 각각 255에서 빼는 연산을 수행함 */

	Mat src = imread("butterfly.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type()); // src와 동일한 m x n 행렬 및 타입을 갖는 dst를 생성

	for (int j = 0; j < src.rows; j++) { 
		for (int i = 0; i < src.cols; i++) {
			Vec3b& p1 = src.at<Vec3b>(j, i);  // 픽셀 좌표 값을 참조로 받아옴 
			Vec3b& p2 = dst.at<Vec3b>(j, i);

			p2[0] = 255 - p1[0]; // p1픽셀의 세 개 색상 성분 값을 모두 반전시켜 p2픽셀 값으로 설정
			p2[1] = 255 - p1[1];
			p2[2] = 255 - p1[2];
		}
	}

	/* 위의 반복문은 아래와 같이 변경할 수 있음 */
	/*
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<Vec3b>(j, i) = Vec3b(255, 255, 255) - src.at<Vec3b>(j, i);
		}
	}
	*/

	/* 이렇게 구현했지만 사실 실전에서는 Mat클래스에 대해 정의된 - 연산자 재정의 함수를 사용하는 것이 효율적 */
	/* Mat src = imread("butterfle.jpg", IMREAD_COLOR); */
	/* Mat dst = Scalar(255,255,255) - src; */ // 실전에서 사용하는 방법 

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void color_grayscale()
{
	/* 색 공간 변환 */
	/* 컬러 영상 처리에서는 보통 색상 구분이 용이한 HSV, HSL 색 공간을 이용 */
	/* 또는 휘도 성분이 구분되어 있는 YCrCb, YUV 등 색 공간을 사용하는 것이 유리 */
	/* 영상의 색 공간을 다른 색 공간으로 변환할 때에는 cvtColor()함수를 사용 */
	/* cvtColor(src, dst, code, dstCn = 0) */
	/* dstCn = 0 이면 자동으로 결과 영상의 채널 수를 결정 */
	/* code는 색 공간 변환 코드 339p 참고*/
	
	/* 그레이스케일을 사용하는 이유는 연산속도와 메모리 사용량을 줄이기 위해서 사용 */

	/* HSV = H(hue, 색상), S(saturation, 채도 = 색의 순도), V(value, 명도 = 빛의 세기)로 색을 표현하는 방식 */
	/* H값은 0 ~ 179, S와 V는 0 ~ 255 사이의 정수로 표현 */
	/* 원뿔 형태라 0부터 360도 사이의 각도로 표현하지만, uchar 자료형으로는 256 이상의 정수 표현을 못함 */
	/* 그래서 각도를 2로 나눈 값을 H 성분으로 저장*/

	/* YCrCb = Y(밝기 또는 휘도 = luminance, Cr과 Cb성분은 색상 또는 색차(chrominance)정보를 나타냄 */
	/* YCrCb 색 공간은 영상을 그레이스케일 정보와 색상 정보로 분리하여 처리할 때 유용함 */
	/* 각각의 성분은 0 ~ 255 사이의 값으로 표현됨 */

	Mat src = imread("butterfly.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void color_split() // BGR 컬러 영상의 채널 나누기
{
	/* 색상 채널 나누기 */
	/* 컬러 영상을 다루다 보면 R성분만을 이용하거나 HSV 색 공간으로 변환한 후 H성분만을 이용하는 경우가 종종 발생 */
	/* 이러한 경우에는 3채널 Mat 객체를 1채널 Mat 객체 3개로 분리해서 다루는 것이 효율적 */
	/* Split(src, mvbegin or mv) */
	/* mvbegin = 분리된 1채널 행렬을 저장할 Mat배열 주소 */
	/* mv = 분리된 1채널 행렬을 저장할 벡터. vector<Mat>형식의 변수로 받음  */
	
	/* 1채널 행렬 어러 개를 합쳐서 다채널 행렬 하나를 생성하려면 merge함수를 사용 */
	/* merge(mv, count, dst) or merge(mv, dst) */
	/* mv = 1채널 행렬을 저장하고 있는 배열 또는 벡터. count = (mv가 Mat타입의 배열인 경우) Mat 배열의 크기, dst = 출력 다채널 행렬 */

	Mat src = imread("candies.png");

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	vector<Mat> bgr_planes; // src 영상의 채널을 분할하여 bgr_planes 벡터에 저장.
	split(src, bgr_planes);

	imshow("src", src);
	imshow("B_plane", bgr_planes[0]);
	imshow("G_plane", bgr_planes[1]);
	imshow("R_plane", bgr_planes[2]);

	waitKey();
	destroyAllWindows();
}


int main()
{
	//color_inverse();
	//color_grayscale();
	color_split();

	return 0;
}