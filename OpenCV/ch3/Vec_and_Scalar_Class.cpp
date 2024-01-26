/* Vec(Vector)클래스 및 Scalar 클래스 */
/* Mat 클래스만큼 사용 빈도가 높은 클래스임 */
/* 여기서는 기초만 나오고 나머지는 OpenCV 사이트 참고 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

/* 하나의 행으로만 이루어진 행렬 = 행 벡터 */
/* 하나의 열로만 이루어진 행렬 = 열 벡터 */
/* 두 개를 합쳐서 벡터 또는 벡터 행렬이라고 부름 */
/* 벡터 = 같은 자료형을 가진 원소 몇 개로 구성된 데이터 형식 */

int main()
{
	// Vec<int, 3> or Vec<uchar, 3> 형식을 사용하여 자료형 및 개수(채널 갯수)를 나타냄
	// Vec<uchar, 3> p1, p2(0,0,255); 형식으로 변수 생성
	// 하지만 위와 같은 방법은 불편함. 그래서 이름 재정의를 이용하여 쉽게 표현할 수 있음
	// Vec<uchar, 3>은 Vec3b임 =>보통 Color영상 b = uchar, s = short, w = ushort, i,f,d는 int, float, double (114p참고)
	// 두 번째 주석을 Vec3b p1, p2(0,0,255);로 표현 가능
	// 위 주석은 내부에 uchar val[3] 형식의 멤버 변수를 가지고 p1은 전부 0, p2는 p2.val[0], p2.val[1]은 0, p2.val[2]는 255로 초기화
	// p1.val[0] = 100;으로 하면 첫 번째 변수를 100으로 초기화 가능
	// []연산자 재정의를 통해 p1[0] = 100; 가능
	Vec3b p1, p2(0, 0, 255);
	cout << p1 << endl;
	cout << p2 << endl;

	cout << endl;

	p1[0] = 100;
	p1.val[1] = 255;
	cout << p1 << endl;

	/* Scalar 클래스는 4채널 이하의 영상에서 픽셀 값을 표현하는 용도로 자주 사용 */
	/* 4개의 원소를 가지는 템플릿 클래스 */
	/* Scalar 클래스는 크기가 4인 double형 배열 val을 멤버 변수로 가지고 있는 자료형 */
	Scalar gray = 128; // grayscale은 밝기값만 가짐 (128, 0, 0, 0)
	cout << "gray : " << gray << endl;

	Scalar yellow(0, 255, 255); // True Color는 BGR값을 가짐 (0, 255, 255, 0)
	cout << "yellow : " << yellow << endl;

	Mat img1(256, 256, CV_8UC3, yellow);
	for (int i = 0; i < 4; i++)
		cout << yellow[i] << endl;

	return 0;
}