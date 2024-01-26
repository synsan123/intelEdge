/* ���� ���� �� �� ���� */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void hough_line() // ���� ��ȯ ���� ����
{
	/* ������ ã�� ���� �뵵�� ���� ��ȯ ����� �θ� ���� */
	/* ���� ��ȯ�� 2���� xy ��ǥ���� ������ �������� �Ķ���� �������� ��ȯ�Ͽ� ������ ã�� �˰��� */
	/* ������ ���� �����ϴ� ���� ã�� ���ؼ� ���� �迭�� ����� */
	/* ���� �迭�� 0���� �ʱ�ȭ�� 2���� �迭���� ������ �������� ��ġ�� �迭 ���� ���� 1�� �������� ���� */
	/* ���� ��ȯ�� ������ ������ y = ax + b ���°� �ƴ϶� ����ǥ�� ������ xcos + ysin = p ������ ������ �������� ���*/
	/* p�� ��Ÿ�� �Ǽ� ���� ������ ������ ���� �迭�� �����Ϸ��� �̵��� ������ ������ ũ��� ������ �����ϴ� ����ȭ ������ ���ľ� �� */
	/* HoughLines(image, lines, rho, theta, threshold, srn = 0, stn = 0, min_theta = 0, max_theta = CV_PI) */
	/* image = 8��Ʈ 1ä�� �Է� ����. ���� ���� ����(canny�Լ� ���� �̿��Ͽ� ����)�� ����. lines = ���� ����(rho, theta)�� ������ ��� ���� */
	/* rho = p���� �ػ�(�ȼ�����), theta = ��Ÿ ���� �ػ�(���� ����), threshold = �������� �Ǵ��� �Ӱ谪 */
	/* srn = ��Ƽ������ ���� ��ȯ���� rho �ػ󵵸� ������ ��. ���� �Ǽ��� �����ϸ� ��Ƽ������ ���� ��ȯ ����. */
	/* stn = ��Ƽ������ ���� ��ȯ���� theta �ػ󵵸� ������ ��. srn = stn = 0�̸� �Ϲ� ���� ��ȯ ���� */
	/* min_theta, max_theta = ������ ������ �ּ� �ִ� theta�� */
	/* lines���ڿ��� vector<Vec2f> or vector<Vec3f> �ڷ����� ������ ���� */

	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat edge;
	Canny(src, edge, 50, 150);

	vector<Vec2f> lines; // vector<Vec2f> �ڷ����� ��� �� p�� ��Ÿ������ lines�� ����. ���� �迭���� p������ 1�ȼ�����, ��Ÿ�� 1�� ������ ó��
	HoughLines(edge, lines, 1, CV_PI / 180, 250); // rho = 1, theta = 1��, threshold = 250

	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	for (size_t i = 0; i < lines.size(); i++) { // HoughLines�Լ��� ���� ������ ������ ������ŭ for���� ����
		float r = lines[i][0], t = lines[i][1];  // rho(p)�� r�� theta�� t�� ����.
		double cos_t = cos(t), sin_t = sin(t);
		double x0 = r * cos_t, y0 = r * sin_t; // �������� ������ ������ ������ �� ������ ���� ��ǥ
		double alpha = 1000; // ����� ũ�� �����ؾ� pt1�� pt2�� ���� �ٱ��ʿ� ��ġ�ϸ� �ڿ������� ������ �׸� �� ���� 

		Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t)); /* pt1�� pt2����(x0, y0)���� ����� �ָ� ������ �ִ� */
		Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t)); /* �������� �� �� ��ǥ�� �����(������ �׸��� ���� �������� �� �� ��ǥ) */
		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);  /* ����� ������ �β��� 2�� ������ �Ǽ����� �׸� */
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void hough_line_segments() // Ȯ���� ���� ��ȯ ���� ����
{
	/* Ȯ���� ���� ��ȯ�� ������ ������ �Ķ������ rho�� theta�� ��ȯ�ϴ� ���� �ƴ϶� ������ �������� ���� ��ǥ�� ��ȯ */
	/* ������ �ƴ� ������ ã�� ����� */
	/* HoughLinesP(image, lines, rho, theta, threshold, minLineLength = 0, maxLineGap = 0) */
	/* lines = ������ �������� ������ ����(x1, y1, x2, y2)�� ������ ��� ����, vector<Vec4i> �ڷ��� ��� */
	/* minLineLength = ������ ������ �ּ� ���� */
	/* maxLineGap = �������� ������ �ִ� ���� �� ���� */

	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat edge;
	Canny(src, edge, 50, 150);

	vector<Vec4i> lines; // ��� ���� ������ �������� ���� ��ǥ�� ���Ͽ� ����
	HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 50, 5);

	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	/* ���� ��� for �ݺ��� */
	/* vector �Ǵ� �迭 � ����Ǿ� �ִ� ��� ���Ҹ� �ϳ��� ������ ����� �� �� */
	/* vector<Vec4i> Ÿ������ ����� lines ��ü���� Vec4i Ÿ���� �ڷḦ �ϳ��� ������ ���� l�� ������ ��, dst ���� ������ �׸��� ���� ��� */
	for (Vec4i l : lines) { // HoughLineP�� ���� ������ ��� ���� ������ dst ���� ���� ������ �������� �׸� 
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void hough_circles()  // ���� ��ȯ �� ����
{
	/* ���� �׷����Ʈ ����� ����Ͽ� ���� ���� */
	/* 1. ���� �����ϴ� ��� ���� �߽� ��ǥ�� ã�� */
	/* 2. ����� ���� �߽����κ��� ���� ������ �������� ���� */
	/* ���� �߽� ��ǥ�� ã�� �������� ���� �迭�� ���� */
	/* ���� �׷����Ʈ ����� �Ķ���� �������� ����� ���� �ƴ϶� �Է� ����� ������ xy��ǥ �������� 2���� �迭�� ���� �迭�� ���� */
	/* ���� �߽��� ã�� ���� �Է� ������ ��� �����ȼ����� �׷����Ʈ�� ���ϰ�, �׷����Ʈ ������ ������ �������� ���� �迭 ���� 1�� ������Ŵ */
	/* HoughCircles(image, circles, method, dp, minDist, param1 = 100, param2 = 100, minRadius = 0, maxRadius = 0) */
	/* image = ������ �׷��̽����� ������ ������, �Լ� ��ü���� �Һ��� ĳ�ϸ� �̿��Ͽ� ���� ���� ��� �� ���� �׷����Ʈ ����� ����� */
	/* circles = ����� �� ������ ������ ��� ����, method = HOUGH_GRADIENT�� ���� ����  */
	/* dp = �Է� ����� ���� �迭�� ũ�� ����, minDist = ������ �� �߽��� �ּ� �Ÿ� */
	/* param1 = Canny ���� ������� ���� �Ӱ谪, param2 = ���� �迭���� �� ������ ���� �Ӱ谪 */
	/* min, maxRadius = ������ ���� �ּ�, �ִ� ������ */

	/* circles���ڿ��� vector<Vec3f> or vector<Vec4f> �ڷ��� ������ ���� */
	/* vector<Vec3f> �ڷ����� ����ϸ� ���� �߽� ��ǥ�� �������� ���ʴ�� ����� */
	/* vector<Vec4f> �ڷ����� �߰������� ���� �迭 �������� ����� */
	/* dp = 1 �̸� �Է� ����� ������ ũ���� ���� �迭�� ���. 2�̸� ���ο� ���� ũ�⸦ 2�� ���� ũ���� ���� �迭�� ��� */

	Mat src = imread("coins.png", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat blurred;
	blur(src, blurred, Size(3, 3)); // ���� ���ŷ� blur�Լ� ���

	vector<Vec3f> circles;
	/* ���� ����.dp = 1, minDist = 50(�� ���� �߽��� �Ÿ��� 50�ȼ����� ������ ���� ���� */
	/* param1 = 150, param2 = 30(���� �迭 ���� ���� 30���� ũ�� ���� �߽������� ����) */
	/* ����� ���� �߽���ǥ�� ������ ������ circles������ ����� */
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30); 

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (Vec3f c : circles) {  // circles ��ü�� ����� ������ �ϳ��� ���� c�� ����, ���� �׸��� ���� ��� 
		Point center(cvRound(c[0]), cvRound(c[1]));
		int radius = cvRound(c[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}


int main()
{
	//hough_line();
	//hough_line_segments();
	hough_circles();

	return 0;
}