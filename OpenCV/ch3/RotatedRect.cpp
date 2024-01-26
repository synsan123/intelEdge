#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	RotatedRect rtr1(Point2f(40, 30), Size2f(40, 20), 30.f);
	Point2f pts[4]; // pts = 사각형 네 꼭지점의 좌표를 출력
	rtr1.points(pts); // rtr1객체에 RotatedRect 멤버함수 points에 pts 변수를 입력하여 rtr1의 회전하여 변한 사각형의 네 꼭지점 좌표 저장.
	
	for (int i = 0; i < 4; i++) // 회전된 사각형의 네꼭지점 좌표 출력.
	{
		cout << pts[i] << endl;
	}

	Rect br = rtr1.boundingRect2f();
	cout << br << endl;

	return 0;
}