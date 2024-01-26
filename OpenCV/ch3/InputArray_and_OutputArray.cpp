/* InputArray와 OutputArray 클래스 */
/* OpenCV함수의 입력과 출력으로 사용되는 인터페이스 클래스 */
/* 사용자가 직접 InputArray, OutputArray타입의 변수를 생성해서는 안됨 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

/* InputArray클래스 타입의 인자를 사용하는 함수를 정의하는 방법과 실제 사용 방법을 보여줌 */
void printMat(InputArray _mat)
{
	Mat mat = _mat.getMat(); //getMat(int idx = -1)함수는 idx는 참조할 행 번호이고 idx < 0이면 행렬 전체를 참조
	cout << mat << endl;	
}

int main()
{
	uchar data1[] = { 1,2,3,4,5,6 };
	Mat mat1(2, 3, CV_8U, data1);
	printMat(mat1);

	vector<float> vec1 = { 1.2f, 3.4f, -2.1f };
	printMat(vec1);
}