/* ������ OpenCV ��� */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

#if 0
int main()
{
	/* ����ũ ���� */
	/* setTo �Լ��� ����� �ȼ� ���� �����ϱ⵵ ������ ����ũ ������ �����ϴ� �Լ��̱⵵ �� */
	/* (��� ���ҿ� ������ ��, ����ũ ���� ����(=����ũ ���)) */
	/* ���� */

	Mat src = imread("lenna.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_smile.bmp", IMREAD_GRAYSCALE);

	if (src.empty() || mask.empty()) {
		cerr << "image load fail" << endl;
		return -1;
	}

	src.setTo(Scalar(0, 255, 255), mask); // mask���󿡼� �ȼ� ���� 0�� �ƴ� ��ġ������ src���� �ȼ��� ��������� ����.

	imshow("src", src);
	imshow("mask", mask);

	waitKey();
	destroyAllWindows();
}
#endif

#if 0
int main()
{
	/* ��� ���� �Լ� copyTo�Լ��̱⵵ ������ ����ũ ������ �����ϴ� �Լ� */
	/* ��� ���� �Լ� �� ���� (���纻�� ����� ���) */
	/* ����ũ �������� �� ���� (���纻�� ����� ���, ����ũ ���� ����(=����ũ ���)) */
	/* ���� */
	Mat src = imread("airplane.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_plane.bmp", IMREAD_GRAYSCALE);
	Mat dst = imread("field.bmp", IMREAD_COLOR);
	imshow("src", src);
	imshow("mask", mask);
	imshow("dst_origin", dst);
	if (src.empty() || mask.empty() || dst.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	src.copyTo(dst, mask); // mask���󿡼� ��� ���� ��ġ������ src ���� �ȼ� ���� dst�� ����

	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}
#endif

#if 0
int main()
{
	/* ���� �ð� ���� */ /* relese���� �����Ͽ� �����ؾ� �� */
	/* ���� �ܰ�� ������ ������ ó�� �ý����� �����ϴ� ���, �� �ܰ迡�� �ҿ�Ǵ� ���� �ð��� �����ϴµ� ��� */
	/* getTickCount�Լ��� getTickFrequency�Լ��� ���*/
	/* Count�� Ư�� �������� ������� �߻��� ƽ Ƚ���� ��ȯ */
	/* tick�� Ŭ��ó�� �ſ� ������ �����ϴ� ���� ���� ����� �ǹ� */
	/* ���� ���� �ð��� �˾Ƴ��� ���ؼ��� ƽ Ƚ�� ���̸� �ý����� ƽ ���ļ��� ������ �۾��� ���ݵǾ�� �� */
	/* ƽ ���ļ��� 1�� ���� �߻��ϴ� ƽ Ƚ���� �ǹ���.*/
	/* Count�� ���� ƽ(tick) Ƚ��, Frequency�� �ý����� �ʴ� ƽ Ƚ���� ��ȯ */
	/* Ư�� ������ ����Ǵ� �ð��� �����ϱ� ���ؼ��� �� �Լ��� ���� �����ؼ� ����Ͽ��� �� */
	/* ���� */

	//int64 t1 = getTickCount();
	//my_func(); // �� �Լ� ȣ�� ���Ŀ� ���� Count�� ȣ���Ͽ� ƽ Ƚ�� ���̸� ���
	//int64 t2 = getTickCount();
	//double ms = (t2 - t1) * 1000 / getTickFrequency();

	/* TickMeter Ŭ������ ����Ͽ� ���� �������� */
	/* ���� */
	
	/*TickMeter tm;
	tm.start();

	my_func();

	tm.stop();
	double ms = tm.getTimeMilli();*/
	
	/* TickMeter�� �̿��� ������ ���� �ð� ���� ���� */
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	Mat dst(src.rows, src.cols, src.type()); //src�� ��,��,Ÿ���� �����Ͽ� dst ����

	TickMeter tm;
	tm.start();

	/* ������ ��� �ȼ��� ������Ŵ */
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = 255 - src.at<uchar>(j, i); // at�Լ��� �� ���ҿ� �����ϱ� ���� �Լ�. uchar�� �ڷ������� ���� Grayscale �ǹ�
		}
	}

	tm.stop();
	cout << "Image Inverse took " << tm.getTimeMilli() << "ms. " << endl;
}
#endif


int main()
{
	/* �־��� ����� ��ü ���� �� �Ǵ� ����� ���ϴ� �Լ� */
	/* sum(�Է����), mean(�Է����, ����ũ ����) => ����ũ ������ �����Ͽ� Ư�� ������ ���� ����� ���� �� �� ����.(�ᵵ�ǰ� �Ƚᵵ �ǰ�) */
	/* ���� */
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);

	cout << "Sum : " << (int)sum(img)[0] << endl;  // Scalar �ڷ����� ��ȯ. ù ��° ���� ���� �����ϱ� ���� [0]�� ���
	cout << "Mean : " << (int)mean(img)[0] << endl;

	/* �־��� ����� �ּڰ�, �ִ��� ã�� �Լ� */
	/* minMaxLoc(�Է¿���(����ä��), �ּҰ��� ���� double�� ������ �ּ�, �ִ밪�� ���� double�� ������ �ּ�, �ּڰ� ��ġ ��ǥ�� ���� Point�� ������ �ּ�, �ִ밪 ��ġ ��ǥ�� ���� Point�� ������ �ּ�, ����ũ ����) */
	/* minMaxLoc(src, minVal, maxVal, minLoc, maxLoc, mask) */
	/* ���� */
	double minVal, maxVal;
	Point minPos, maxPos;
	minMaxLoc(img, &minVal, &maxVal, &minPos, &maxPos);

	cout << "minVal : " << minVal << " at " << minPos << endl;
	cout << "maxVal : " << maxVal << " at " << maxPos << endl;

	/* ����� norm ���� ����ȭ�ϰų� �Ǵ� ���� �� ������ Ư�� ������ ����ȭ�� �� ����� �� �ִ� �Լ� */
	/* normalize(src, dst, alpha, beta, norm_type, dtype, mask) */
	/* (�Է����, ������, (norm ����ȭ�� ���)��ǥ norm��( (���� �� ���� ����ȭ�� ���� �ּڰ�), (���� �� ���� ����ȭ�� ���)�ִ�, ����ȭ Ÿ��, ��� ������ Ÿ��, ����ũ ����) */
	/* NORM_MINMAXŸ������ ���� ���. Ư�� �Ǽ��� ������ ����� �׷��̽����� ���� ���·� ��ȯ�ϰ��� �� �� ����ϸ� ���� */
	/* ���� */
	Mat src = Mat_<float>({ 1,5 }, { -1.f,-0.5f,0.f,0.5f,1.f });

	Mat dst;
	normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1); // -1���� 1������ �Ǽ��� ������ 1x5����� 0���� 255 ������ ���� ��ķ� ��ȯ

	cout << "src : " << src << endl;
	cout << "dst : " << dst << endl;

	/* �Ǽ� ���� �ݿø� ������ ���� cvRound �Լ��� ��� */
	/* cvRound(double value), cvRound(float value), value = �Է� �Ǽ� �� */
	/* �̿ܿ� �ø��� cvCeil, ������ cvFloor ��� */
	/* ���� */
	cout << "cvRound(2.5) : " << cvRound(2.5) << endl;
	cout << "cvRound(2.51) : " << cvRound(2.51) << endl;
	cout << "cvRound(3.4999) : " << cvRound(3.4999) << endl;
	cout << "cvRound(3.5) : " << cvRound(3.5) << endl;
}