/* 부분 행렬 추출 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	/* 괄호 () 연산자 재정의 이용, 메모리 공간 확보가 아닌 픽셀 데이터를 공유하는 얕은 복사임 */
	Mat img1 = imread("cat.bmp");

	/* 이미지 불러오기 실패 시 프로그램 종료 */
	if (img1.empty())
	{
		cerr << "Image Load Fail" << endl;
		return -1;
	}

	/* (220, 120) 좌표로부터 340 x 240 크기만큼의 사각형 */
	Mat img2 = img1(Rect(220, 120, 340, 240)); // Rect 클래스를 이용한 사각형 관심영역 정의
	
	/* 영상의 반전 */
	/* 부분 영상 추출 시 픽셀 데이터를 공유한다는 특성을 이용하면 입력 영상의 일부분에만 특정한 영상처리를 수행할 수 있음*/
	//img2 = ~img2;

	imshow("img1", img1);
	imshow("img2", img2);

	/* clone을 이용한 깊은 복사 및 부분 영상 추출 */
	Mat img3 = img1(Rect(220, 120, 240, 240)).clone();
	// img3 = ~img3; // 반전을 해도 img1에는 적용되지 않음

	imshow("img3", img3);

	waitKey();
	destroyAllWindows();
	//이외에도 rowRange, colRange, row, col이 있음
	return 0;
}