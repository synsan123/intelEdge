/* Mat클래스는 OpenCV라이브러리에서 가장 많이 사용하는 클래스. 행렬을 나타내는 클래스이다. */
/* 2차원 영상 데이터를 저장하고 처리하는 용도로 가장 많이 사용 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat img1;
	Mat img2(480, 640, CV_8UC1); // 640 x 480인데 중요한 건 적을 때 (세로, 가로) 순임. 1-channel은 grayscale에 (rows, cols)
	Mat img3(480, 640, CV_8UC3); // 3-channel은 color에 사용, rows = 행인데 세로, cols = 열인데 가로
	Mat img4(Size(640, 480), CV_8UC3); // 2차원 사각형, 행렬, 영상의 Size(width, Height)를 표현하기 위한 클래스

	/* 위의 첫번째는 사용하면 오류. 나머지는 쓰레기값이 저장되어있음 */
	/* 보통 초기값은 0으로 설정을 하므로 Scalar에 0넣으면 됨 */
	Mat img5(480, 640, CV_8UC1, Scalar(128)); // Scalar클래스를 이용하여 초기값을 정해주어야 함. grayscale은 1-channel이라서 하나
	Mat img6(480, 640, CV_8UC3, Scalar(0, 0, 255)); // color는 3-channel이므로 BGR순으로 초기값 설정.

	/* 행렬을 0으로 초기화시키는 함수를 제공함 => zeros를 사용 */
	/* zeros는 Mat클래스의 정적 멤버 함수이기 때문에 Mat::zeros로 사용하여야 함 */
	Mat mat1 = Mat::zeros(3, 3, CV_32SC1);
	Mat mat2 = Mat::ones(3, 3, CV_32FC1); // 전부 1
	Mat mat3 = Mat::eye(3, 3, CV_32FC1);  // 단위행렬

	/* 외부 메모리 공간의 주소를 지정하는 Mat클래스의 생성자*/
	/* 외부 배열을 행렬 원소 값으로 사용. 외부배열 크기와 생성할 행렬 원소 개수는 같아야함. 서로 자료형도 같아야 함 */
	/* Mat 객체의 원소 값과 외부 메모리 공간의 데이터 값이 상호공유된다는 점을 기억 */
	float data[] = { 1,2,3,4,5,6 };
	Mat mat4(2, 3, CV_32FC1, data);

	/* Mat_ 클래스를 이용한 행렬 생성. Mat_클래스의 경우 자료형 명시적으로 지정해야 함. 이 경우 1-channel임 */
	/* Mat_<float> mat5_(2,3); mat5_ << 1, 2, 3, 4, 5, 6; Mat mat5 = mat_; mat5_라는 변수를 사용할 시 이렇게 작성 */
	/* 위의 코드는 아래와 동일한 행렬을 가짐, 아래 코드는 mat_변수를 사용하지 않을 때 */
	Mat mat5 = (Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);

	/* 중괄호를 이용한 리스트 형태로 전달하여 행렬 크기와 초깃값을 설정하는 방법 */
	Mat mat6 = Mat_<float>({ 2,3 }, { 1,2,3,4,5,6 });

	/* 비어 있는 Mat객체 또는 이미 생성된 Mat 객체에 새로운 행렬을 할당하려면 Mat클래스의 Mat::create()함수를 사용 */
	/* 기존의 있는 행렬과 완전히 같으면 그냥 종료. 다르면 변경시킴 */
	/* 새로 만든 행렬의 원소 값을 초기화하는 기능이 없음 */
	mat4.create(256, 256, CV_8UC3);
	mat5.create(4, 4, CV_32FC1);

	/* create이후 행렬의 값을 초기화시키기 위해서는 = 연산자의 재정의 및 setTo함수를 사용한다 */
	mat4 = Scalar(255, 0, 0); // 블루인 255로 전체를 초기화
	mat5.setTo(1.f); // 전체를 1.f 즉 float 1로 초기화

	return 0;
}