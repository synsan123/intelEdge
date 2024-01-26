/* 영상의 필터링 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main()
{
	/* 마스크라고 부르는 작은 크기의 행렬을 이용. 마스크(= 커널, 윈도우, 필터) */
	/* 마스크의 행렬 원소는 보통 실수로 구성됨. 다양한 모양의 필터 마스크 중 3x3을 가장 많이 사용 */
	/* 고정점 = 마스크 행렬 정중앙 */
	/* 마스크 연산 = 마스크 행렬 원소 값과 같은 위치에 있는 입력 영상 픽셀 값을 곱한 후, 그 결과를 모두 더하는 연산 */
	/* 영상의 가장자리 픽셀에서는 수식을 적용하기 어려워 특별한 처리를 해야 함 */
	/* 가장자리 픽셀을 확장하여 바깥쪽에 가상의 픽셀을 만듬 */
	/* 실제 영상의 픽셀 값이 대칭 형태로 나타나도록 설정 */
	/* BORDER_CONSTANT, BORDER_REPLICATE, BORDER_REFLECT, BORDER_REFLECT_101 종류가 있음 */
	/* filter2D(src, dst, ddepth, kernel, anchor, delta, bordertype) */
	/* kernel = 필터링 커널(1채널 실수형 행렬), anchor(고정점 좌표. (-1,-1)로 default) */
	/* ddepth에 -1을 지정하면 출력 영상의 깊이는 입력 영상과 같게 됨.(248p 참고) */
	
	/* filter2D를 이용하여 엠보싱 필터링을 적용하는 예제 */
	/* 음수 값은 전부 포화연산에 의해 0이 되어 버리기 때문에 입체감이 줄어들어 결과 영상에 128을 더하는 것이 보기 좋음 */
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	/* data 배열을 이용하여 3x3크기의 엠보싱 필터 마스크 행렬 생성 */
	float data[] = { -1, -1, 0, -1, 0, 1, 0, 1, 1 };
	Mat emboss(3, 3, CV_32FC1, data);

	Mat dst;
	filter2D(src, dst, -1, emboss, Point(-1, -1), 128);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();

	return 0;
}