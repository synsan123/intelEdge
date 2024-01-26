#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Rect rect1;
	Rect rect2(10, 10, 60, 40);
	cout << rect1 << endl << rect2 << endl;

	Rect rect3;
	rect3 = rect1 + Size(50, 40);
	cout << rect3 << endl;

	Rect rect4;
	rect4 = rect2 + Point(10, 10);
	cout << rect4 << endl;

	Rect rect5;
	rect5 = rect3 & rect4;
	cout << rect5 << endl;

	Rect rect6;
	rect6 = rect3 | rect4;
	cout << rect6 << endl;

	return 0;
}