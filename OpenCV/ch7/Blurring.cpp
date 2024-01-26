/* 블러링 : 영상 부드럽게 하기 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* 평균값 필터 */
#if 0
int main()
{
	/* 영상을 부드럽게 함. 스무딩이라고도 함. */
	/* 인접한 픽셀 간의 픽셀 값 변화가 크지 않은 경우 부드러운 느낌을 받음 */
	/* 잡음을 제거하는 전처리 과정으로도 사용됨 */
	
	/* 평균값 필터 */
	/* 입력 영상에서 특정 픽셀과 주변 픽셀들의 산술 평균을 결과 영상 픽셀 값으로 설정하는 필터 */
	/* 픽셀값은 전부 1 / n x n 임*/
	/* 과도하게 사용 시 사물의 경계가 흐릿해지고 사물의 구분이 어려워짐 */
	/* blur(src, dst, ksize, anchor, borderType) => ksize는 블러링 커널 크기 */
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	imshow("src", src);

	Mat dst;
	for (int ksize = 3; ksize <= 7; ksize += 2) {
		blur(src, dst, Size(ksize, ksize));

		String desc = format("Mean: %d x %d", ksize, ksize);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
	return 0;
}
#endif

/* 가우시안 필터 */
int main()
{
	/* 가우시안 분포는 평균을 중심으로 좌우 대칭의 종 모양을 갖는 확률 분포를 말하며 정규 분포라고도 한다. */
	/* 평균과 표준 편차에 따라 분포 모양이 결정됨 */
	/* 표준 편차가 클수록 넓게 펴지고 완만해짐, 반대는 뾰족해짐 */
	/* 가우시안 필터 마스크는 가중평균을 구하기 위한 가중치 행렬 역할을 함 */
	/* GaussianBlur(src, dst, ksize, sigmaX, sigmaY = 0, borderType) */
	/* ksize = 가우시안 커널 크기, sigma = 표준편차. sigmaY = 0 이면 sigmaX와 같은 표준편차 사용 */
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	imshow("src", src);

	Mat dst;
	for (int sigma = 1; sigma <= 5; sigma++) {
		GaussianBlur(src, dst, Size(), (double)sigma);

		String text = format("sigma = %d", sigma);
		putText(dst, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}