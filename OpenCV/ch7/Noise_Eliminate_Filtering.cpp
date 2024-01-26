/* 잡음 제거 필터링 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* 가우시안 잡음 모델 */
/* 영상에 잡음을 추가함 */
/* randn(dst, mean, stddev) => 출력영상, 평균, 표준편차 */
/* dst행렬을 가우시안 분포를 따르는 난수로 채움 */
void noise_gaussian()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	imshow("src", src);

	for (int stddev = 10; stddev <= 30; stddev += 10) {
		Mat noise(src.size(), CV_32SC1);
		randn(noise, 0, stddev);

		Mat dst;
		add(src, noise, dst, Mat(), CV_8U);

		String desc = format("stddev = %d", stddev);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();

}


/* 양방향 필터 */
/* 에지 성분은 그대로 유지하면서 가우시안 잡음을 효과적으로 제거하는 알고리즘 */
/* bilateralFilter(src, dst, d, sigmaColor, sigmaSpace, borderType) => d = 필터링에 사용할 이수 픽셀과의 거리, -1이면 sigmaSpace로부터 자동 계산*/
/* sigmaColor값을 작게 지정하면 픽셀 값 차이가 큰 주변 픽셀과는 블러링이 적용 안됨 */
/* 반면에 크게 하면 픽셀 값 차이가 조금 크더라도 블러링이 적용됨, 이를 이용하여 어느 정도 밝기 차를 갖는 에지를 보존할 것인지 조정 가능 */
void filter_bilateral()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	/* src에 잡음을 추가함 */
	Mat noise(src.size(), CV_32SC1);
	randn(noise, 0, 5);
	add(src, noise, src, Mat(), CV_8U);

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 5);

	Mat dst2;
	bilateralFilter(src, dst2, -1, 10, 5);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}

/* 미디언 필터 */
/* 입력 영상에서 자기 자신 픽셀과 주변 픽셀 값 중에서 중간값을 선택하여 결과 영상 픽셀 값으로 설정하는 필터링 기법 */
/* 영상에 추가되는 잡음 중에 소금&후추 잡음은 픽셀 값이 일정 확률로 0 또는 255로 변경되는 형태의 잡음 */
/* medianBlur(src, dst, ksize) */
void filter_median()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	int num = (int)(src.total() * 0.1);
	for (int i = 0; i < num; i++) {
		int x = rand() % src.cols;
		int y = rand() % src.rows;
		src.at<uchar>(y, x) = (i * 2) * 255;
	}

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 1);

	Mat dst2;
	medianBlur(src, dst2, 3);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}

int main()
{
	// noise_gaussian();
	// filter_bilateral();
	filter_median();
	return 0;
}