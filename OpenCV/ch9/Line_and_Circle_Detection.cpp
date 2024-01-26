/* 직선 검출 및 원 검출 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void hough_line() // 허프 변환 직선 검출
{
	/* 직선을 찾기 위한 용도로 허프 변환 기법이 널리 사용됨 */
	/* 허프 변환은 2차원 xy 좌표에서 직선의 방정식을 파라미터 공간으로 변환하여 직선을 찾는 알고리즘 */
	/* 직선이 많이 교차하는 점을 찾기 위해서 축적 배열을 사용함 */
	/* 축적 배열은 0으로 초기화된 2차원 배열에서 직선이 지나가는 위치의 배열 원소 값을 1씩 증가시켜 생성 */
	/* 허프 변환을 구현할 떄에는 y = ax + b 형태가 아니라 극좌표계 형식인 xcos + ysin = p 형식의 직선의 방정식을 사용*/
	/* p와 세타는 실수 값을 가지기 때문에 축적 배열을 구현하려면 이들의 범위를 적당한 크기로 나눠서 저장하는 양자화 과정을 거쳐야 함 */
	/* HoughLines(image, lines, rho, theta, threshold, srn = 0, stn = 0, min_theta = 0, max_theta = CV_PI) */
	/* image = 8비트 1채널 입력 영상. 보통 엣지 영상(canny함수 등을 이용하여 구한)을 지정. lines = 직선 정보(rho, theta)를 저장할 출력 벡터 */
	/* rho = p값의 해상도(픽셀단위), theta = 세타 값의 해상도(라디안 단위), threshold = 직선으로 판단할 임계값 */
	/* srn = 멀티스케일 허프 변환에서 rho 해상도를 나누는 값. 양의 실수를 지정하면 멀티스케일 허프 변환 수행. */
	/* stn = 멀티스케일 허프 변환에서 theta 해상도를 나누는 값. srn = stn = 0이면 일반 허프 변환 수행 */
	/* min_theta, max_theta = 검출할 직선의 최소 최대 theta값 */
	/* lines인자에는 vector<Vec2f> or vector<Vec3f> 자료형의 변수를 지정 */

	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat edge;
	Canny(src, edge, 50, 150);

	vector<Vec2f> lines; // vector<Vec2f> 자료형을 사용 시 p와 세타정보를 lines에 저장. 축적 배열에서 p간격은 1픽셀단위, 세타는 1도 단위로 처리
	HoughLines(edge, lines, 1, CV_PI / 180, 250); // rho = 1, theta = 1도, threshold = 250

	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	for (size_t i = 0; i < lines.size(); i++) { // HoughLines함수에 의해 구해진 직선의 개수만큼 for문을 수행
		float r = lines[i][0], t = lines[i][1];  // rho(p)를 r에 theta를 t에 저장.
		double cos_t = cos(t), sin_t = sin(t);
		double x0 = r * cos_t, y0 = r * sin_t; // 원점에서 직선에 수선을 내렸을 때 만나는 점의 좌표
		double alpha = 1000; // 충분히 크게 설정해야 pt1과 pt2가 영상 바깥쪽에 위치하며 자연스러운 직선을 그릴 수 있음 

		Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t)); /* pt1과 pt2에는(x0, y0)에서 충분히 멀리 떨어져 있는 */
		Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t)); /* 직선상의 두 점 좌표가 저장됨(직선을 그리기 위한 직선상의 두 점 좌표) */
		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);  /* 검출된 직선을 두께가 2인 빨간색 실선으로 그림 */
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void hough_line_segments() // 확률적 허프 변환 선분 검출
{
	/* 확률적 허프 변환은 직선의 방정식 파라미터인 rho와 theta를 반환하는 것이 아니라 직선의 시작점과 끝점 좌표를 반환 */
	/* 직선이 아닌 선분을 찾는 방법임 */
	/* HoughLinesP(image, lines, rho, theta, threshold, minLineLength = 0, maxLineGap = 0) */
	/* lines = 선분의 시작점과 끝점의 정보(x1, y1, x2, y2)를 저장할 출력 벡터, vector<Vec4i> 자료형 사용 */
	/* minLineLength = 검출할 선분의 최소 길이 */
	/* maxLineGap = 직선으로 간주할 최대 엣지 점 간격 */

	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat edge;
	Canny(src, edge, 50, 150);

	vector<Vec4i> lines; // 모든 직선 성분의 시작점과 끝점 좌표를 구하여 저장
	HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 50, 5);

	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	/* 범위 기반 for 반복문 */
	/* vector 또는 배열 등에 저장되어 있는 모든 원소를 하나씩 꺼내어 사용할 때 편리 */
	/* vector<Vec4i> 타입으로 선언된 lines 객체에서 Vec4i 타입의 자료를 하나씩 꺼내어 변수 l에 저장한 후, dst 영상에 직선을 그리기 위해 사용 */
	for (Vec4i l : lines) { // HoughLineP에 의해 구해진 모든 직선 성분을 dst 영상 위에 빨간색 직선으로 그림 
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void hough_circles()  // 허프 변환 원 검출
{
	/* 허프 그래디언트 방법을 사용하여 원을 검출 */
	/* 1. 영상에 존재하는 모든 원의 중심 좌표를 찾음 */
	/* 2. 검출된 원의 중심으로부터 원에 적합한 반지름을 구함 */
	/* 원의 중심 좌표를 찾는 과정에서 축적 배열이 사용됨 */
	/* 허프 그래디언트 방법은 파라미터 공간에서 만드는 것이 아니라 입력 영상과 동일한 xy좌표 공간에서 2차원 배열로 축적 배열을 만듬 */
	/* 원의 중심을 찾기 위해 입력 영상의 모든 엣지픽셀에서 그래디언트를 구하고, 그래디언트 방향을 따르는 직선상의 축적 배열 값을 1씩 증가시킴 */
	/* HoughCircles(image, circles, method, dp, minDist, param1 = 100, param2 = 100, minRadius = 0, maxRadius = 0) */
	/* image = 원본의 그레이스케일 영상을 지정함, 함수 자체에서 소벨과 캐니를 이용하여 엣지 영상 계산 후 허프 그래디언트 방법을 사용함 */
	/* circles = 검출된 원 정보를 저장할 출력 벡터, method = HOUGH_GRADIENT만 지정 가능  */
	/* dp = 입력 영상과 축적 배열의 크기 비율, minDist = 인접한 원 중심의 최소 거리 */
	/* param1 = Canny 엣지 검출기의 높은 임계값, param2 = 축적 배열에서 원 검출을 위한 임계값 */
	/* min, maxRadius = 검출할 원의 최소, 최대 반지름 */

	/* circles인자에는 vector<Vec3f> or vector<Vec4f> 자료형 변수를 지정 */
	/* vector<Vec3f> 자료형을 사용하면 원의 중심 좌표와 반지름이 차례대로 저장됨 */
	/* vector<Vec4f> 자료형은 추가적으로 축적 배열 누적값이 저장됨 */
	/* dp = 1 이면 입력 영상과 동일한 크기의 축적 배열을 사용. 2이면 가로와 세로 크기를 2로 나눈 크기의 축적 배열을 사용 */

	Mat src = imread("coins.png", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat blurred;
	blur(src, blurred, Size(3, 3)); // 잡음 제거로 blur함수 사용

	vector<Vec3f> circles;
	/* 원을 검출.dp = 1, minDist = 50(두 원의 중심점 거리가 50픽셀보다 작으면 검출 안함 */
	/* param1 = 150, param2 = 30(축적 배열 원소 값이 30보다 크면 원의 중심점으로 선택) */
	/* 검출된 원의 중심좌표와 반지름 정보는 circles변수에 저장됨 */
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30); 

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (Vec3f c : circles) {  // circles 객체에 저장된 정보를 하나씩 변수 c에 저장, 원을 그리기 위해 사용 
		Point center(cvRound(c[0]), cvRound(c[1]));
		int radius = cvRound(c[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}


int main()
{
	//hough_line();
	//hough_line_segments();
	hough_circles();

	return 0;
}