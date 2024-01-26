/* GrayScale 영상 다루기 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	/* GrayScale 형태의 Mat 객체를 생성하는 방법 */
	Mat img1 = imread("lenna.bmp",IMREAD_GRAYSCALE);
	Mat img2(480, 640, CV_8UC1, Scalar(0)); // 모든 픽셀 값이 0(black)으로 초기화된 640x480 GrayScale 영상
	Mat img3 = imread("lenna.bmp", IMREAD_COLOR);

	/* cvtColor함수는 Mat 객체에 저장된 색상 정보를 변경할 때 사용하는 함수 */
	/* (입력영상, 출력영상, 컬러 변환 코드) */
	Mat img4;
	cvtColor(img3, img4, COLOR_BGR2GRAY); 

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
	imshow("img4", img4);

	waitKey();
	destroyAllWindows();
}