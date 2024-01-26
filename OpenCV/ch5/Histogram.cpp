/* 히스토그램 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

Mat calcGrayHist(const Mat& img)
{
	CV_Assert(img.type() == CV_8UC1); // CV_Assert매크로함수를 이용하여 img영상이 그레이스케일인지 검사

	Mat hist;  // 히스토그램 정보를 저장할 Mat 타입의 변수
	int channels[] = { 0 }; // 그레이스케일은 채널이 1개
	int dims = 1; // 하나의 채널에 대해서만 구함. 1차원 행렬 
	const int histSize[] = { 256 }; // 입력 영상의 첫 번째 채널 값의 범위를 256개 빈(가로값)으로 나누어 히스토그램을 구하겠다
	float graylevel[] = { 0,256 }; // 그레이스케일의 최솟값과 최대값을 차례대로 지정
	const float* ranges[] = { graylevel }; // graylevel배열 이름을 원소로 갖는 배열

	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);

	return hist; // CV_32FC1 타입을 갖는 256 x 1 크기의 행렬
}

Mat getGrayHistImage(const Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	double histMax;
	minMaxLoc(hist, 0, &histMax); // hist행렬 원소의 최댓값을 histMax변수에 저장

	Mat imgHist(100, 256, CV_8UC1, Scalar(255)); // 흰색으로 초기화된 256 x 100크기의 새 영상 imgHist를 생성
	for (int i = 0; i < 256; i++) { // 각가의 빈에 대한 히스토그램 그래프를 그림 
		line(imgHist, Point(i, 100), Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
	}

	return imgHist;
}

void histogram_stretching()
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);

	Mat dst = (src - gmin) * 255 / (gmax - gmin);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}

#if 0
int main()
{
	/* 영상의 픽셀 값 분포를 그래프 형태로 나나탠 것 */
	/* calcHist함수를 사용 */
	/* (입력 영상의 배열 또는 입력 영상의 주소, 입력 영상 개수, 히스토그램을 구할 채널, 마스크 영상, 출력 히스토그램, 출력 히스토그램 차원 수
	, 각 차원의 히스토그램 배열 크기를 나타내는 배열, 각 차원의 히스토그램 범위, 히스토그램 빈의 간격이 균등한지를 나타내는 플래그, 누적 플래그) */ 
	/* (images, nimages, channels, mask, hist, dims, histSize, ranges, uniform, accumulate) */

	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	Mat src1 = src + 30;
	Mat hist = calcGrayHist(src);
	Mat hist_img = getGrayHistImage(hist);

	imshow("src", src);
	imshow("src1", src1);
	imshow("srcHist", hist_img);
	imshow("srcHist1", getGrayHistImage(calcGrayHist(src))); // hist와 hist_img를 선언하지 않고도 가능
	imshow("src1Hist1", getGrayHistImage(calcGrayHist(src1)));
	waitKey();
	destroyAllWindows();

	return 0;
 }
#endif


int main()
{
	/* 히스토그램 스트레칭 */
	/* 영상의 히스토그램이 그레이스케일 전 구간에 걸쳐서 나타나도록 변경하는 선형 변환 기법 */
	/* 명암비가 좋아짐 */
	// histogram_stretching();

	/* 히스토그램 평활화 */ /* 스트레칭과 마찬가지로 명암비가 좋아짐 */
	/* 특정 그레이스케일 값 근방에서 픽셀 분포가 너무 많이 뭉쳐 있는 경우 이를 넗게 펼쳐 주는 방식으로 픽셀 값 분포를 조절 */
	/* 스트레칭과 달리 평활화는 equalizHist(입력영상은 CV_8UC1만 가능, 출력 영상) 함수를 제공함 */
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "fail" << endl;
		return -1;
	}

	Mat dst;
	equalizeHist(src, dst);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
	
	return 0;
}