#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat img1 = imread("dog.bmp"); // dog.bmp를 불러와 img1에 저장

	/* img1의 픽셀 데이터를 img2가 참조. img1과 img2는 하나의 영상을 공유하는 서로 다른 이름의 변수 형태로 동작 */
	Mat img2 = img1; // Mat 클래스의 복사 생성자를 이용한 영상 or 행렬 복사(이 경우 얕은 복사), 행렬의 원소 데이터를 공유

	Mat img3;
	img3 = img1; // 대입 연산자를 이용한 복사(이 경우도 얕은 복사임)

	/* 복사본 영상을 새로 생성할 때, 픽셀 데이터를 공유하는 것이 아니라 메모리 공간을 새로 할당하여 픽셀 데이터 전체를 복사하고자 할 때 */
	/* Mat클래스의 clone, copyTo 함수를 사용*/
	Mat img4 = img1.clone(); // 깊은 복사, 자기 자신과 동일한 Mat객체를 완전히 새로 만들어서 반환
	
	/* 깊은 복사, 호출한 행렬과 인자로 전달된 행렬 m이 서로 크기와 타입이 같으면 원소 값만 복사 */
	/* 다를 경우 copyTo함수 내부에서 행렬 m을 새로 생성한 후 픽셀(원소) 값을 복사 */
	/* clone과 copyTo함수로 생성된 이미지들은 픽셀 데이터를 저장할 메모리 공간을 따로 가지고 있고, img1에 저장된 영상의 복사본을 저장함 */
	Mat img5;
	img1.copyTo(img5); 

	/* 원하는 값으로 행렬 또는 이미지의 원소 값(픽셀 값)을 초기화(변경) */
	img1 = Scalar(0, 255, 255);
	//img1.setTo(Scalar(0, 255, 255));

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
	imshow("img4", img4);
	imshow("img5", img5);

	waitKey();
	destroyAllWindows();

	return 0;
}