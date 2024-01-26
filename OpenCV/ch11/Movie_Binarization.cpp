/* ������ ����ȭ */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* ���� ����ȭ��� �� */
#if 0
void on_threshold(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;

	Mat dst;
	threshold(src, dst, pos, 255, THRESH_BINARY); // ����ڰ� ������ Ʈ���� ��ġ(pos)�� �̿��Ͽ� ����ȭ�� �����ϰ�, �� ����� dst�� ����

	imshow("dst", dst);
}

int main(int argc, char* argv[]) // ���α׷� ���� �� ����� ���ڸ� ���� �� �ֵ��� argc�� argv���ڸ� ������
{
	/* ������ ����ȭ�� ������ �� �ȼ��� �� ���� �з�(0 �Ǵ� 255)�� ������ �۾� */
	/* ���� �ִ� ��ü ������ ��� ������ �����ϱ� ���� �뵵�� ���� */
	/* �Ǵ� ���� ������ ����� �������� �����ϴ� �뵵�� ����� */
	/* ������ ����ȭ�� �⺻������ ������ �� �ȼ� ���� �̿��� */
	/* ������ �ȼ� ���� Ư�� ������ ũ�� 255�� ����, ������ 0���� ���� */
	/* �� �� �� �ȼ����� ũ�� �� ����� �Ǵ� ���� �Ӱ谪�̶�� �� (0 ~ 255������ ������ ������ �� ����) */
	/* ����ȭ�� threshold()�Լ��� �̿��Ͽ� ����. �Ӱ谪�� �̿��� �پ��� ������ �����ϴ� �Լ��� */
	/* threshold(src, dst, thresh, maxval, type) */
	/* thresh = �Ӱ谪, maxval = THRESH_BINARY or THRESH_BINARY_INV����� ����� �� ��� ������ �ִ� */
	/* type = �Ӱ谪 ���� ���. 361p ���� */
	/* ������ ����ȭ�Ϸ��� maxval = 255�� �����ϰ� type = ���� THRESH_BINARY or THRESH_BINARY_INV�� ��� */
	/* THRESH_OTSU or THRESH_TRIANGLE�� �Ӱ谪�� �ڵ����� ������ �� ��� */
	/* �Ӱ谪 ������ �ʿ����. �׷��Ƿ� 0���� �����ϸ� ��. */
	/* type �κп� ����� ���� THRESH_BINARY | THRESH_OTSU�� ���� ������� ��� */
	/* ���� Ÿ���� ����Ͽ� �Ӱ谪�� Ȯ���ϰ� �ʹٸ� */
	/* int th = (int)threshold(src, dst, 0, 255, THRESH_BINARY | THRESH_OTSU)�� ��� */

	/* Mat ������ �ε�ȣ ������ �����Ǹ� �̿��Ͽ� �����ϰ� ����ȭ �� �� ���� */
	/* Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	   Mat dst = src > 128; */ 
	/* ���� ���� �ڵ带 © �� ����. src�� �� �ȼ� ���� 128���� ũ��(���̸�) 255��, ������ dst�� 0�� ������ */

	Mat src;

	if (argc < 2) // ����� ���� ������ 2���� ������ if���� 
		src = imread("neutrophils.png", IMREAD_GRAYSCALE);
	else // ���α׷� ���� ���� �̸� �ڿ� ����� ���� ���� �̸��� ����ϸ� �ش� ������ �Է� �������� ���
		src = imread(argv[1], IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	imshow("src", src);

	namedWindow("dst");
	createTrackbar("Threshold", "dst", 0, 255, on_threshold, (void*)&src); // dstâ�� "Threshold"�̸��� Ʈ���ٸ� ����
	setTrackbarPos("Threshold", "dst", 128); // ���α׷��� ó�� ����� �� Ʈ���� ��ġ�� 128�� �ǵ��� �����Ͽ� on_threshold�Լ��� ó���� �� �� �����

	waitKey();
	destroyAllWindows();

	return 0;
}
#endif

/* ������ ����ȭ */

void on_trackbar(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;

	int bsize = pos;
	if (bsize % 2 == 0) bsize--;
	if (bsize < 3) bsize = 3;

	Mat dst;
	/* Ʈ���ٿ��� ������ ��� ũ�⸦ �̿��Ͽ� ������ ����ȭ�� ������, ����þ� ���� ����� ���, ��� ��տ��� 5�� �A ���� �Ӱ谪���� ��� */
	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, bsize, 5);

	imshow("dst", dst);
}

int main()
{
	/* ���� ����ȭ�� �������� ���� ���� ȯ�濡�� �Կ��� ���� ���� ���� ����ȭ�� �����ϸ� ��ü�� ����� �����ϰ� �и����� �ʴ� ��찡 �߻��� */
	/* ������ ����ȭ = �� �ȼ����� ���� �ٸ� �Ӱ谪�� ����ϴ� ����ȭ */
	/* ������ ��� �ȼ����� ������ ũ���� �簢�� ��� ������ �����ϰ�, ��� ���� ������ �ȼ� �� �����κ��� ������ �Ӱ谪�� �����Ͽ� ����ȭ�ϴ� ��� */
	/* adpativeThreshold(src, dst, maxValue, adaptiveMethod, thresholdType, blockSize, C) */
	/* maxValue = ����ȭ ��� ������ �ִ� */
	/* adaptiveMethod = ������ ����ȭ���� ��� ��� ��� ��� ���� (ADAPTIVE_THRESH_MEAN_C or ADAPTIVE_THRESH_GAUSSIAN_C) �� �ϳ� ���� */
	/* thresholdType = THRESH_BINARY or THRESH_BINARY_INV �� �ϳ� ���� */
	/* blockSize = �Ӱ谪 ��� �� ����ϴ� ��� ũ��, 3�� ���ų� ���� ū Ȧ���� �����ؾ� �� */
	/* C = �Ӱ谪 ������ ���� ���, ��� ��տ��� C�� �� ���� �Ӱ谪���� ����� */
	/* adaptiveMethod�� �����ϸ� blockSize x blockSize ũ���� �ֺ� ���� �ȼ��κ��� ��� ����� ���� / ����þ� ����ũ�� �����Ͽ� ����þ� ���� ����� ����� */

	Mat src = imread("sudoku.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	imshow("src", src);

	namedWindow("dst");
	createTrackbar("Block Size", "dst", 0, 200, on_trackbar, (void*)&src); // dstâ�� "Threshold"�̸��� Ʈ���ٸ� ����
	setTrackbarPos("Block Size", "dst", 11);

	waitKey();
	destroyAllWindows();

	return 0;
}