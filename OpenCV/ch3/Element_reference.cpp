/* 행렬의 원소 값 참조 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	/* 가장 직관적인 행렬 원소 접근 방법 at함수 */
	/* y번째 행, x번째 열의 원소 값 참조 형식으로 출력 (행렬 원소 자료형 명시적 지정 필요) */
	Mat mat1 = Mat::zeros(3, 4, CV_8UC1);

	for (int j = 0; j < mat1.rows; j++) {
		for (int i = 0; i < mat1.cols; i++) {
			mat1.at<uchar>(j, i)++; // uchar = unsigend char = 8U (행렬 원소 자료형 명시적 지정)
		}
	}
	cout << mat1 << endl;

	/* ptr함수, 특정 행의 첫 번째 원소 주소(y번째 행의 시작 주소 즉 포인터)를 반환. 가장 널리 사용하는 ptr함수 형식을 설명 */
	/* at과 마찬가지로 템플릿 함수이기에 자료형을 명시적으로 지정해줘야 한다. */
	for (int j = 0; j < mat1.rows; j++) {
		uchar* p = mat1.ptr<uchar>(j);
		for (int i = 0; i < mat1.cols; i++) {
			p[i]++;
		}
	}
	cout << mat1 << endl;

	/* MatIterator_(반복자 클래스), 템플릿으로 정의. Mat::begin함수를 이용하여 첫 번째 원소 위치, end함수를 이용하여 마지막 다음 위치 원소 */
	/* 행렬의 모든 원소에 접근하는 방법의 예제 */
	/* mat1의 가로 및 세로 크기를 참조하는 코드가 없음. 행렬의 가로, 세로 크기에 상관없이 행렬의 모든 원소를 안전하게 방문 가능*/
	/* 다만 동작 속도가 느리고, 임의의 위치에 자유롭게 접근하는 것이 어려우며 잘 사용하지 않는 클래스함수임 */
	for (MatIterator_<uchar> it = mat1.begin<uchar>(); it != mat1.end<uchar>(); ++it) {
		(*it)++;
	}
	cout << mat1 << endl;

	return 0;
}