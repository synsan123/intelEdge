#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Point pt1;
	cout << pt1 << endl;

	pt1.x = 5;
	pt1.y = 10;
	cout << pt1 << endl;

	Point pt2(10, 30);
	cout << pt2 << endl;

	Point pt3;
	pt3 = pt1 + pt2;
	cout << pt3 << endl;

	Point pt4;
	pt4 = pt1 * 2;
	cout << pt4 << endl;

	int d1 = pt1.dot(pt2);
	bool b1 = (pt1 == pt2);
	cout << d1 << endl << boolalpha << b1 << endl;

	return 0;
}