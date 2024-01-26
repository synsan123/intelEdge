/* 어파인 변환 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* 영상의 어파인 변환 예제 */
void affine_transform()
{
	/* 영상의 평행 이동, 확대 및 축소, 회전 등의 조합으로 만들 수 있는 기하학적 변환 */
	/* 영상의 기하학적 변환 = 영상을 구성하는 픽셀의 배치 구조를 변경함으로써 전체 영상의 모양을 바꾸는 작업 */
	/* 픽셀 값은 그대로 유지하되 위치만 변경하는 작업 */
	/* 2 x 3 실수형 행렬 하나로 어파인 변환을 표현할 수 있음 */
	/* 최소 세 점의 이동 관계를 알아야 함. 알고 있다면 6개의 원소로 정의된 어파인 변환 행렬을 구할 수 있음 */
	/* getAffineTransform() = 어파인 변환 행렬을 구하는 함수 */
	/* getAffineTransform(src, dst) or (src[], dst[]) => 각각 입력, 출력에서 세 점의 좌표 */
	/* src와 dst에는 크기가 3인 Point2f배열 또는 vector<Point2f>자료형 변수 사용 가능 */
	/* 위의 함수가 반환하는 Mat객체는 CV_64FC1타입을 사용하는 2x3크기의 어파인 변환 행렬 */

	/* 어파인 변환 행렬을 가지고 있을 때, 영상을 어파인 변환한 결과 영상을 생성하려면 warpAffine함수 사용 */
	/* wrapAffine(src, dst, M, dsize, flags, borderMode, borderValue) */
	/* M = 2x3 어파인 변환 행렬, dsize = 결과 영상 크기, flags = 보간법 알고리즘(279p 참고) */
	/* M은 CV_32FC1 or CV_64FC1 타입이어야 하고, 크기는 2x3이어야 함. */
	/* dsize에 Size()를 전달하면 입력 영상과 같은 크기의 결과 영상을 생성 */

	Mat src = imread("tekapo.bmp");  //GrayScale 이나 Color나 동일하게 적용되기 때문에 컬러로 함.

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Point2f srcPts[3], dstPts[3]; // 세 점 좌표를 저장할 배열을 선언
	srcPts[0] = Point2f(0, 0);    // 입력 영상의 좌측 상단, 우측 상단, 우측 하단의 좌표를 저장
	srcPts[1] = Point2f(src.cols - 1, 0); // 639, 0
	srcPts[2] = Point2f(src.cols - 1, src.rows -1); // 639, 479
	dstPts[0] = Point2f(50, 50);  // srcPts 점들이 이동할 좌표를 저장
	dstPts[1] = Point2f(src.cols - 100, 100);
	dstPts[2] = Point2f(src.cols - 50, src.rows - 50);

	Mat M = getAffineTransform(srcPts, dstPts); // 어파인 변환 행렬 생성

	/* 어파인 행렬을 가지고 있을 때, 일부 점들이 어느 위치로 이동하는지를 알고 싶다면 transform() 함수를 이용 */
	/* transform(src,dst,m) */
	/* (100, 20), (200, 50)이 어파인 변환 행렬에 의해 이동하는 위치를 알고 싶다면 */
	/* vector<Point2f> src = { Point2f(100,20), Point2f(200, 50) } */
	/* vector<Point2f> dst */
	/* transform(src, dst, m) 으로 작성한다. */

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void affine_translation() // 이동 변환 (x,y) -> (x',y')로 변경
{
	/* 어파인 행렬이 필요 */
	/* [ 1 0 a ] */
	/* [ 0 1 b ] */
	/* 위와 같은 2x3 어파인 행렬을 필요로 함, (a, b) 만큼 이동시켜 (x', y')를 만듬 */
	Mat src = imread("tekapo.bmp");  //GrayScale 이나 Color나 동일하게 적용되기 때문에 컬러로 함.

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat M = Mat_<double>({ 2,3 }, { 1,0,150,0,1,100 }); // 어파인 행렬

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();

}

void affine_shear() // 전단 변환
{
	/* 직사각형 형태의 영상을 한쪽 방향으로 밀어서 평행사변형 모양으로 변형되는 변환, 층밀림 변환이라고도 함 */
	/* 가로 방향, 세로 방향으로 정의할 수 있음 */
	/* 전단 변환에 원점은 전단 변환에 의해 이동하지 않고 그대로 원점에 머뭄 */
	/* y좌표가 증가함에 따라 영상이 가로로 이동 x' = x + mxy */
	/* x좌표가 증가함에 따라 영상이 세로로 이동 y' = y + myx */
	/* m은 각각 가로방향과 세로방향으로 밀림 정도를 나타내는 실수 */
	/* [ 1 mx 0 ]   [ 1 0  0 ] */
	/* [ 0 1  0 ]   [ m 1y 0 ] */
	/* 각각 위와 같은 어파인 변환 행렬을 가짐 */
	Mat src = imread("tekapo.bmp");  

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	double mx = 0.3;
	Mat M = Mat_<double>({ 2,3 }, { 1,mx,0,0,1,0 }); // 어파인 행렬

	Mat dst;
	/* 전단 변환에 의해 입력 영상의 일부가 잘리지 않도록 결과 영상 가로 크기를 cvRound(src.cols + src.rows*mx)형태로 지정 */
	warpAffine(src, dst, M, Size(cvRound(src.cols + src.rows*mx), src.rows));

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void affine_scale() // 크기 변환
{
	/* 영상의 전체적인 크기를 확대 또는 축소하는 변환 */
	/* sx(x의 크기 비율) = w' / w or x' / x */
	/* sy(y의 크기 비율) = h' / h or y' / y */
	/* s > 1이면 영상이 확대, s < 1이면 영상이 축소 */
	/* 어파인 변환 행렬은 아래와 같음 */
	/* [ sx 0  0 ] */
	/* [ 0  sy 0 ] */
	/* 어파인 변환으로 크기 변환 하지 않고 resize함수를 이용해서도 가능함 */
	/* resize(src, dst, dsize, fx, fy, interpolation), f = 축 방향으로의 크기 변환 비율. dsize에 Size()를 지정한 경우에만 사용 */
	
	/* 480x320크기의 장미 영상을 다양한 보간법으로 확대하고 결과 영상의 일부를 화면에 출력하는 예제 */
	Mat src = imread("rose.bmp");

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}
	
	Mat dst1, dst2, dst3, dst4;
	resize(src, dst1, Size(), 4, 4, INTER_NEAREST); // x,y방향으로 4배 확대 => (480 x 320) x 4 => 1920 x 1280이 됨
	resize(src, dst2, Size(1920, 1280)); // Default = INTER_LINEAR
	resize(src, dst3, Size(1920, 1280), 0, 0, INTER_CUBIC);
	resize(src, dst4, Size(1920, 1280), 0, 0, INTER_LANCZOS4);

	imshow("src", src);
	imshow("dst1", dst1(Rect(400, 500, 400, 400))); // (400, 500)좌표부터 400 x 400 크기의 부분 영상을 화면에 출력 
	imshow("dst2", dst2(Rect(400, 500, 400, 400)));
	imshow("dst3", dst3(Rect(400, 500, 400, 400)));
	imshow("dst4", dst4(Rect(400, 500, 400, 400)));

	waitKey();
	destroyAllWindows();
}

void affine_rotation() // 회전 변환
{
	/* 회전 변환은 삼각함수를 이용함 */
	/* 어파인 변환 행렬 M은 */
	/* [ cos세타 sin세타   0 ] */
	/* [ -sin세타 cos세타  0 ] */
	/* 영상 회전을 위한 어파인 변환 행렬을 생성하는 getRotationMatrix2D함수를 제공 */
	/* getRotationMatrix2D(center, angle(양수면 반시계, 음수면 시계 방향 회전), scale), scale = 회전 후 추가적으로 확대 또는 축소할 비율. 보통 1 */

	/* 90도 단위로 회전하고 싶은 경우에는 rotate()함수를 사용 */
	/* rotate(src, dst, rotateCode) rotateCode = 회전 각도 지정 플래그임 294p 참고 (3개 있음)*/

	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Point2f cp(src.cols / 2.f, src.rows / 2.f); // 영상의 중심 좌표(center Point)
	Mat M = getRotationMatrix2D(cp, 20, 1);

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void affine_flip() // 대칭 변환 
{
	/* 상하 대칭 또는 상하 반전, 좌우 대칭 또는 좌우 반전 */
	/* 입력 영상과 같은 크기의 결과 영상을 생성하며, 입력 영상의 픽셀과 결과 영상의 픽셀이 일대일로 대응되므로 보간법이 필요없음 */
	/* flip(src, dst, flipCode) flipCode = 대칭 방법 플래그 */
	/* 양수면 좌우 대칭, 0이면 상하 대칭, 음수이면 좌우상하 대칭을 수행, (1, 0 ,-1) 중에 선택하면 됨 */

	Mat src = imread("eastsea.bmp");

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	imshow("src", src);

	Mat dst;
	int flipCode[] = { 1, 0, -1 };
	for (int i = 0; i < 3; i++) {
		flip(src, dst, flipCode[i]);

		String desc = format("flipCode : %d", flipCode[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SCRIPT_SIMPLEX, 1.0, Scalar(255, 0, 0), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}

int main()
{
	//affine_transform(); // 어파인 변환 
	//affine_translation(); // 이동 변환 
	//affine_shear(); // 전단 변환
	//affine_scale(); // 크기 변환
	//affine_rotation(); // 회전 변환
	affine_flip(); // 대칭 변환 
	return 0;
}