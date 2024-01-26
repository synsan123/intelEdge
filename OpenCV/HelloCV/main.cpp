#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	cout << "Hello OpenCV " << CV_VERSION << endl;

	Mat img;
	img = imread("lenna.bmp"); // imread = image read (이미지 불러오기)

	if (img.empty()) // Mat클래스의 empty함수는 파일을 불러오지 못할 경우 true를 반환
	{
		cerr << "Image load Failed" << endl;
		return -1;
	}

	namedWindow("image"); //namedWindow함수를 이용하여 영상을 화면에 나타내기 위한 새로운 창을 생성 및 image라는 이름을 부여
	imshow("image", img); // image show (이미지 보여주기), img객체가 가지고 있는 lenna.bmp 영상을 출력

	vector<int> params;
	params.push_back(IMWRITE_JPEG_QUALITY);
	params.push_back(95);
	imwrite("lenna.jpg", img, params);
	imwrite("lenna.png", img);

	waitKey(); // 사용자의 키보드 입력을 기다리는 함수. 누르기 전까지 영상을 화면에 보여줌.
	return 0;
}