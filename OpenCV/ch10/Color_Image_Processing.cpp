/* �÷� ���� ó�� */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void color_inverse() // �÷� ������ �ȼ� �� ����
{
	/* �÷� ���󿡼� �� ���� ���� ���� uchar �ڷ����� ����Ͽ� ǥ�� */
	/* �÷� ���󿡼� �ϳ��� �ȼ��� �� ���� ���� ����(BGR)�� ������ �����Ƿ� �� �ȼ��� ��Ȯ�ϰ� ǥ���Ϸ��� Vec3b �ڷ����� ��� */
	/* Vec3b(vector 3byte)Ŭ������ ũ��� 3����Ʈ�̸� ���� 3ä�� �÷� ������ �� �ȼ��� �����ϴ� ����Ʈ ���� ����.*/
	/* ���󿡼� �ȼ� ���� ������ ���� Mat::at()�Լ��� �����. ���ø� �Լ��̹Ƿ� �ڷ����� Vec3b�� ������־�� �� */
	/* ��) Vec3b& pixel = img.at<Vec3b>(0,0) => img��ü���� (0,0) ��ġ�� �ȼ� ���� ���� */
	/* pixel�� (0,0)��ǥ���� BGR���� ������ ����Ŵ */
	/* �����̹Ƿ� pixel���� ���ϸ� (0,0)�� �ȼ����� ����� */
	/* Vec3bŬ������ []������ �����Ǹ� �̿��Ͽ� �� ��� ���� ���� ������ �� ���� */
	/* ��) uchar b1 = pixel[0], uchar g1 = pixel[1], uchar r1 = pixel[2] */

	/* Mat::ptr() �Լ��� �̿��Ͽ� �÷� ������ Ư�� �� ���� �ּҸ� ��� �� ������ Vec3bŬ������ �ڷ����� ����ؾ��� */
	/* Vec3b* ptr = img.ptr<Vec3b>(0) => img��ü�� 0��° �� ���� �ȼ� �ּҸ� �˰� �ʹٴ� �� */
	/* ptr[0]�� (0,0)��ǥ �ȼ��� ����Ű��, �̴� Vec3b �ڷ����� �ش� */
	/* ptr[0]�ڿ� []�� �ٽ� �ѹ� ����ϸ� �ش� �ȼ��� BGR���а��� ���� �� ���� */
	/* uchar b2 = ptr[0][0], uchar g2 = ptr[0][1], uchar r2 = ptr[0][2] => (0,0)�ȼ��� BGR���а� */

	/* �÷� ������ �����Ϸ��� BGR�� ���� ���� ���� ���� 255���� ���� ������ ������ */

	Mat src = imread("butterfly.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type()); // src�� ������ m x n ��� �� Ÿ���� ���� dst�� ����

	for (int j = 0; j < src.rows; j++) { 
		for (int i = 0; i < src.cols; i++) {
			Vec3b& p1 = src.at<Vec3b>(j, i);  // �ȼ� ��ǥ ���� ������ �޾ƿ� 
			Vec3b& p2 = dst.at<Vec3b>(j, i);

			p2[0] = 255 - p1[0]; // p1�ȼ��� �� �� ���� ���� ���� ��� �������� p2�ȼ� ������ ����
			p2[1] = 255 - p1[1];
			p2[2] = 255 - p1[2];
		}
	}

	/* ���� �ݺ����� �Ʒ��� ���� ������ �� ���� */
	/*
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<Vec3b>(j, i) = Vec3b(255, 255, 255) - src.at<Vec3b>(j, i);
		}
	}
	*/

	/* �̷��� ���������� ��� ���������� MatŬ������ ���� ���ǵ� - ������ ������ �Լ��� ����ϴ� ���� ȿ���� */
	/* Mat src = imread("butterfle.jpg", IMREAD_COLOR); */
	/* Mat dst = Scalar(255,255,255) - src; */ // �������� ����ϴ� ��� 

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void color_grayscale()
{
	/* �� ���� ��ȯ */
	/* �÷� ���� ó�������� ���� ���� ������ ������ HSV, HSL �� ������ �̿� */
	/* �Ǵ� �ֵ� ������ ���еǾ� �ִ� YCrCb, YUV �� �� ������ ����ϴ� ���� ���� */
	/* ������ �� ������ �ٸ� �� �������� ��ȯ�� ������ cvtColor()�Լ��� ��� */
	/* cvtColor(src, dst, code, dstCn = 0) */
	/* dstCn = 0 �̸� �ڵ����� ��� ������ ä�� ���� ���� */
	/* code�� �� ���� ��ȯ �ڵ� 339p ����*/
	
	/* �׷��̽������� ����ϴ� ������ ����ӵ��� �޸� ��뷮�� ���̱� ���ؼ� ��� */

	/* HSV = H(hue, ����), S(saturation, ä�� = ���� ����), V(value, �� = ���� ����)�� ���� ǥ���ϴ� ��� */
	/* H���� 0 ~ 179, S�� V�� 0 ~ 255 ������ ������ ǥ�� */
	/* ���� ���¶� 0���� 360�� ������ ������ ǥ��������, uchar �ڷ������δ� 256 �̻��� ���� ǥ���� ���� */
	/* �׷��� ������ 2�� ���� ���� H �������� ����*/

	/* YCrCb = Y(��� �Ǵ� �ֵ� = luminance, Cr�� Cb������ ���� �Ǵ� ����(chrominance)������ ��Ÿ�� */
	/* YCrCb �� ������ ������ �׷��̽����� ������ ���� ������ �и��Ͽ� ó���� �� ������ */
	/* ������ ������ 0 ~ 255 ������ ������ ǥ���� */

	Mat src = imread("butterfly.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void color_split() // BGR �÷� ������ ä�� ������
{
	/* ���� ä�� ������ */
	/* �÷� ������ �ٷ�� ���� R���и��� �̿��ϰų� HSV �� �������� ��ȯ�� �� H���и��� �̿��ϴ� ��찡 ���� �߻� */
	/* �̷��� ��쿡�� 3ä�� Mat ��ü�� 1ä�� Mat ��ü 3���� �и��ؼ� �ٷ�� ���� ȿ���� */
	/* Split(src, mvbegin or mv) */
	/* mvbegin = �и��� 1ä�� ����� ������ Mat�迭 �ּ� */
	/* mv = �и��� 1ä�� ����� ������ ����. vector<Mat>������ ������ ����  */
	
	/* 1ä�� ��� � ���� ���ļ� ��ä�� ��� �ϳ��� �����Ϸ��� merge�Լ��� ��� */
	/* merge(mv, count, dst) or merge(mv, dst) */
	/* mv = 1ä�� ����� �����ϰ� �ִ� �迭 �Ǵ� ����. count = (mv�� MatŸ���� �迭�� ���) Mat �迭�� ũ��, dst = ��� ��ä�� ��� */

	Mat src = imread("candies.png");

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	vector<Mat> bgr_planes; // src ������ ä���� �����Ͽ� bgr_planes ���Ϳ� ����.
	split(src, bgr_planes);

	imshow("src", src);
	imshow("B_plane", bgr_planes[0]);
	imshow("G_plane", bgr_planes[1]);
	imshow("R_plane", bgr_planes[2]);

	waitKey();
	destroyAllWindows();
}


int main()
{
	//color_inverse();
	//color_grayscale();
	color_split();

	return 0;
}