#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

void trackbar_callback_function(int position, void* userdata);

int main()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE); // rose.bmp 파일을 GrayScale로 불러옴

	if (src.empty()) { // rose.bmp를 불러오지 못하면 아래 문자열을 출력하고 프로그램 종료
		cerr << "IMAGE READ FAIL" << endl;
		return -1;
	}

	imshow("src", src);
	namedWindow("Sharp"); // 트랙바를 부착할 창을 미리 생성
	createTrackbar("Sigma", "Sharp", 0, 8, trackbar_callback_function, (void*)&src); // img객체의 주소를 사용자 데이터로 지정
	setTrackbarMin("Sigma", "Sharp", 1);
	setTrackbarPos("Sigma", "Sharp", 4);
	trackbar_callback_function(1, &src);

	for (int sigma = 1; sigma <= 8; sigma++) { // 표준편차를 1부터 8까지 증가시키면서 언샤프 마스크 필터링을 수행
		Mat blurred;
		GaussianBlur(src, blurred, Size(), (double)sigma); // 가우시안 필터를 이용한 블러링 영상을 blurred에 저장
		
		imwrite("bluerred.bmp", blurred); // 가우시안 필터를 이용한 블러링 영상 파일 저장

		float alpha = 3.f; // 변화를 좀 더 뚜렷하게 볼려면 값을 높임 
		Mat dst = (1 + alpha) * src - alpha * blurred; // 언샤프 마스크 필터링을 수행

		String desc = format("sigma : %d", sigma); // 샤프닝 결과 영상 dst에 사용된 sigma값을 출력
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		
		imshow("dst", dst);
		cout << "Sigma : " << sigma << endl;
		waitKey();
	}
	
	destroyAllWindows();

}

void trackbar_callback_function(int position, void* userdata)
{
	//int sigmaValue = max(position, 1); // position의 초기값을 0으로 할 수 없도록 조정 

	Mat img = *(Mat*)userdata; //void* 타입의 인자 userdata를 Mat* 타입으로 형변환한 후 img변수로 참조 => 결국 main함수의 img영상과 같은 영상 데이터를 사용
	
	Mat blurred;
	GaussianBlur(img, blurred, Size(), (double)position); // 가우시안 필터를 이용한 블러링 영상을 blurred에 저장

	float alpha = 3.f; // 변화를 좀 더 뚜렷하게 볼려면 값을 높임 
	Mat dst = (1 + alpha) * img - alpha * blurred;

	imshow("Sharp", dst);
}
	
