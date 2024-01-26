/* 투시 변환 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;


Mat src; // 입력 영상을 저장할 변수
Point2f srcQuad[4], dstQuad[4]; // 네점 좌표를 저장할 배열 변수

void on_mouse(int event, int x, int y, int flags, void* userdata) // 마우스 콜백 함수
{
	/* 어파인 변환보다 자유도가 높은 변환 */
	/* 직사각형 형태의 영상을 임의의 볼록 사각형 형태로 변경할 수 있는 변환 */
	/* 직선성은 유지되지만 두 직선의 평행 관계는 깨질 수 있음 */
	/* 점(x,y)하나에서 x좌표에 대한 방정식, y좌표에 대한 방정식을 하나씩 얻을 수 있고 4좌표에 대해서 8개의 방정식을 얻을 수 있음 */
	/* 8개의 방정식에서 투시 변환을 표현하는 파라미터 정보를 계산할 수 있음 */
	/* 투시 변환은 3x3크기의 실수 행렬로 표현함 */
	/* 편의상 9개 원소를 사용. Mp라고 표현 */

	/* 투시 변환 행렬을 구하는 함수와 투시 변환 행렬을 이용하여 실제 영상을 투시 변환하는 함수를 모두 제공 */
	/* 투시 변환 행렬을 구하는 함수는 getPerspectiveTransform(src, dst, solveMethod) */
	/* solveMethod는 계산 방법 지정, src, dst는 Point2f 자료형 배열이나 vector<Point2f>자료형을 사용하면 됨 */
	/* 반환값은 CV_64FC1타입의 3x3 투시 변환 행렬 */

	/* 투시 변환을 구하는 함수는 warpPerspective(src, dst, M, dsize, flags, borderMode, borderValue) */
	
	/* 3x3 투시 변환 행렬을 가지고 있을 때, 점들이 투시 변환에 의해 어느 위치로 이동할 것인지를 알고 싶다면 */
	/* perspectiveTransform(src, dst, m) 함수를 사용하면 됨 */
	
	static int cnt = 0; // 왼쪽 버튼이 눌린 횟수를 저장하는 변수

	if (event == EVENT_LBUTTONDOWN) { 
		if (cnt < 4) {
			srcQuad[cnt++] = Point2f(x, y); // src창에서 마우스 왼쪽 버튼이 눌려진 좌표를 srcQuad배열에 저장. 그리고 cnt값을 1만큼 증가

			circle(src, Point(x, y), 5, Scalar(0, 0, 255), -1); // 마우스가 눌려진 위치에 반지름이 5인 빨간색 원을 그림
			imshow("src", src);

			if (cnt == 4) {
				int w = 200, h = 300; // 투시 변환하여 만들 결과 영상의 가로와 세로 크기를 변수에 저장

				dstQuad[0] = Point2f(0, 0); // src창에서 마우스로 선택한 사각형 꼭지점이 이동할 결과 영상 좌표를 설정 
				dstQuad[1] = Point2f(w - 1, 0);
				dstQuad[2] = Point2f(w - 1, h - 1);
				dstQuad[3] = Point2f(0, h - 1);

				Mat pers = getPerspectiveTransform(srcQuad, dstQuad);

				Mat dst;
				warpPerspective(src, dst, pers, Size(w, h)); // 투시 변환을 수행하여 wxh크기의 결과 영상 dst를 생성 

				imshow("dst", dst);
			}
		}
	}
}
int main()
{
	src = imread("card.bmp");

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	namedWindow("src"); // src창을 미리 생성한 후, src창에 마우스 콜백 함수를 등록 
	setMouseCallback("src", on_mouse);

	imshow("src", src);
	waitKey();

	return 0;
}