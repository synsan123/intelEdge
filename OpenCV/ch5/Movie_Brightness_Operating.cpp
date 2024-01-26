/* 영상의 밝기 조절 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;


#if 0
int main()
{
	/* 영상에 값을 더하거나 빼서 밝기를 조절함 */
	/* 영상의 밝기 조절을 구현할 때는 포화수식을 사용하여야 함 */
	/* 포화수식(특정값을 넘기지 못하게 하는 것)의 예로 255를 넘어설 경우 255로 고정. 0보다 작을 경우 0으로 고정하는 것을 들 수 있음 */
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	Mat dst = src + 100;
	Mat dst1 = src - 100;
	//자기자신에게 변경된 값을 저장할 때는 += 연산자를 사용
	// src += 100;
	// add함수나 subtract함수를 사용할 수 있음
	// add(src, 100, dst) or subtract(src, 100, dst)

	imshow("src", src);
	imshow("dst", dst);
	imshow("dst1", dst1);

	waitKey();
	destroyAllWindows();

	return 0;
}
#endif


/* 영상의 밝기 조절 직접 구현, 알아두면 좋음 */
/* Mat 행렬의 원소 값 참조 방법을 사용 */
int main()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	Mat dst(src.rows, src.cols, src.type()); // src와 크기, 타입이 같은 결과 영상을 생성

	for (int j = 0; j < src.rows; j++) { // 영상 전체 스캔 및 입력 영상의 픽셀 값에 100을 더하여 결과 영상 픽셀 값으로 설정 
		for (int i = 0; i < src.cols; i++) {
			// int v = src.at<uchar>(j, i) + 100;
			/* 포화 연산을 적용 */
			/* v > 255이면 255 아니면 v < 0? 으로 가서 다시 v가 0보다 작으면 0 아니면 v */
			/* 아래는 두 가지 경우로 작성가능함. 그러나 OpenCV는 포화연산을 수행하는 캐스팅 함수인 saturate_cast 함수를 지원함*/
			// dst.at<uchar>(j, i) = v > 255 ? 255 : v < 0 ? 0 : v; // 삼항 조건 연산자를 중복 
			// dst.at<uchar>(j, i) = saturate_cast<uchar>(v);
			/* 최종적으로는 아래와 같이 작성 가능 */
			dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + 100);
		}
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();

	return 0;
}
