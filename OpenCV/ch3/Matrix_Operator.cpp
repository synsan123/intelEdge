/* 행렬 연산 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	float data[] = { 1, 1, 2, 3 };
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1 : "<< endl << mat1 << endl;

	Mat mat2 = mat1.inv(); //역행렬
	cout << "mat2 : " << endl << mat2 << endl;

	Mat mat3 = mat1.t(); // 전치행렬
	cout << "mat3 : " << endl << mat3 << endl;
	
	cout << "mat1 + 3 : " << endl << mat1 + 3 << endl;
	cout << "mat1 + mat2 : " << endl << mat1 + mat2 << endl;
	cout << "mat1 - mat2 : " << endl << mat1 - mat2 << endl;
	cout << "mat1 * mat2 : " << endl << mat1 * mat2 << endl;

	return 0;
}