/* 영상의 논리 연산 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	/* 픽셀 값을 이진수로 표현하여 각 비트 단위 논리 연산을 수행하는 것을 의미 */
	/* bitwise_and(src1, src2, dst, mask), bitwise_or, bitwise_xor, bitwise_not(src1, dst, mask) */
	/* bitwise_not은 한 개의 영상만을 입력으로 받음 */

	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	bitwise_and(src1, src2, dst1);
	bitwise_or(src1, src2, dst2);
	bitwise_xor(src1, src2, dst3);
	bitwise_not(src1, dst4);

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);

	waitKey();
	destroyAllWindows();

	return 0;
}