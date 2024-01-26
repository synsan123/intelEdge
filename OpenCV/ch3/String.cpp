#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	String str1 = "Hello";
	String str2 = "World";
	String str3 = str1 + " " + str2;
	cout << str1 << endl << str2 << endl << str3 << endl;

	bool ret = (str2 == "World");

	cout << boolalpha << ret << endl;

	return 0;
}
