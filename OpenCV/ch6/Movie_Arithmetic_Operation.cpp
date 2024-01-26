/* 영상의 산술 연산 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	/*add(src1, src2, dst, mask, dtype), dtype의 경우 src1과 src2의 깊이가 다르다면 반드시 지정이 필요. default는 -1 */
	/* src에는 Scalar, 정수, 실수 자료형 등이 올 수 있음 */
	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;
	add(src1, src2, dst1); // Or dst1 = src1 + src2; 가능. 단 두 입력 영상의 타입이 동일하다면 

	/* 가중치 부여 */
	/* 두 영상의 가중치 합을 구하는 함수 addWeighted() */
	/* addWeighted(src1, alpha, src2, beta, gamma, dst, dtype), gamma는 가중합 결과에 추가적으로 더할 값 */
	/* alpha + beta = 1 (두 입력 영상의 윤곽을 골고루 가짐) , alpha + beta < 1 (어두워짐), alpha + beta > 1 (밝아짐) */
	addWeighted(src1, 0.5, src2, 0.5, 0, dst2);

	/* subtract(src1, src2, dst, mask, dtype) 빼기 함수 */
	/* 뺄셈의 대상이 되는 영상 순서에 따라 결과값이 달라짐 (앞에 오느냐 뒤에오느냐에 따라 달라진단 말) */
	subtract(src1, src2, dst3);

	/* 차이 연산 */
	/* 영상의 뺄셈 순서에 상관없이 픽셀 값 차이가 큰 영역을 두드러지게 나타내게 하는 함수 absdiff() */
	/* absdiff(src1, src2, dst) */
	/* 뺄셈 연산 결과에 절대값을 취하는 연산. 차이 연산으로 구한 결과 영상을 차영상이라고 한다. */
	absdiff(src1, src2, dst4);

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);

	waitKey();
	destroyAllWindows();

	return 0;
	/* 영상도 일종의 행렬이므로 두 입력 영상을 행렬로 생각하여 곱셈을 수행할 수 도 있지만 거의 안함. */
	/* 다만 두 영상에서 같은 위치에 있는 픽셀 값끼리 서로 곱하거나 나누는 연산을 수행할 수 있음 */
	/* multiply(src1, src2, dst, scale = 1, dtype). scale은 추가적으로 확대/축소할 비율 */
	/* divide(src1, src2, dst, scale = 1, dtype) */
}