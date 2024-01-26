/* 트랙바를 이용한 영상의 밝기 조절 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void on_brightness(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;

	imshow("dst", dst); // 트랙바 콜백 함수에서 밝기 조절된 결과 영상 dst를 화면에 출력
}

int main()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	namedWindow("dst");
	createTrackbar("Brightness", "dst", 0, 100, on_brightness, (void*)&src);
	on_brightness(0, (void*)&src); // dst창에 레나 영상이 정상적으로 표시되도록 강제로 on_brightness 함수를 호출. 없으면 트랙바 움직일 때 나옴 

	waitKey();
	destroyAllWindows();

	return 0;
}