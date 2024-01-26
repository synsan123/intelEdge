#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Range r1(0, 10); // 0 ~ 9까지 start = 0, end = 10. end는 범위에 미포함.
	cout << r1 << endl;

	return 0;
}