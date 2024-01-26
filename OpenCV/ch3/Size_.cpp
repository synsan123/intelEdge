#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Size sz1, sz2(10, 20);
	cout << sz1 << endl << sz2 << endl;

	sz1.width = 5;
	sz1.height = 10;
	cout << sz1 << endl;

	Size sz3;
	sz3 = sz1 + sz2;

	Size sz4;
	sz4 = sz1 * 2;

	int area1 = sz4.area();
	cout << sz3 << endl << sz4 << endl << area1 << endl;

	return 0;
}