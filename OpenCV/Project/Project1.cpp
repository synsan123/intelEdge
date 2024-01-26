#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

void trackbar_callback_function(int position, void* userdata);

int main()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE); // rose.bmp ������ GrayScale�� �ҷ���

	if (src.empty()) { // rose.bmp�� �ҷ����� ���ϸ� �Ʒ� ���ڿ��� ����ϰ� ���α׷� ����
		cerr << "IMAGE READ FAIL" << endl;
		return -1;
	}

	imshow("src", src);
	namedWindow("Sharp"); // Ʈ���ٸ� ������ â�� �̸� ����
	createTrackbar("Sigma", "Sharp", 0, 8, trackbar_callback_function, (void*)&src); // img��ü�� �ּҸ� ����� �����ͷ� ����
	setTrackbarMin("Sigma", "Sharp", 1);
	setTrackbarPos("Sigma", "Sharp", 4);
	trackbar_callback_function(1, &src);

	for (int sigma = 1; sigma <= 8; sigma++) { // ǥ�������� 1���� 8���� ������Ű�鼭 ����� ����ũ ���͸��� ����
		Mat blurred;
		GaussianBlur(src, blurred, Size(), (double)sigma); // ����þ� ���͸� �̿��� ���� ������ blurred�� ����
		
		imwrite("bluerred.bmp", blurred); // ����þ� ���͸� �̿��� ���� ���� ���� ����

		float alpha = 3.f; // ��ȭ�� �� �� �ѷ��ϰ� ������ ���� ���� 
		Mat dst = (1 + alpha) * src - alpha * blurred; // ����� ����ũ ���͸��� ����

		String desc = format("sigma : %d", sigma); // ������ ��� ���� dst�� ���� sigma���� ���
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		
		imshow("dst", dst);
		cout << "Sigma : " << sigma << endl;
		waitKey();
	}
	
	destroyAllWindows();

}

void trackbar_callback_function(int position, void* userdata)
{
	//int sigmaValue = max(position, 1); // position�� �ʱⰪ�� 0���� �� �� ������ ���� 

	Mat img = *(Mat*)userdata; //void* Ÿ���� ���� userdata�� Mat* Ÿ������ ����ȯ�� �� img������ ���� => �ᱹ main�Լ��� img����� ���� ���� �����͸� ���
	
	Mat blurred;
	GaussianBlur(img, blurred, Size(), (double)position); // ����þ� ���͸� �̿��� ���� ������ blurred�� ����

	float alpha = 3.f; // ��ȭ�� �� �� �ѷ��ϰ� ������ ���� ���� 
	Mat dst = (1 + alpha) * img - alpha * blurred;

	imshow("Sharp", dst);
}
	
