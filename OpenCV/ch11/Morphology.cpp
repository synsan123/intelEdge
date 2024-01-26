/* �������� ���� */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* �������� ������ ���� ���� ��ü�� ���¿� ������ �м��ϰ� ó���ϴ� ��� */
/* �׷��̽����� ����� ���� ���� ��� ������ ���� */
/* �ַ� ���� ���󿡼� ��ü�� ����� �����ϰ� ������ �����ϴ� �뵵�� ��� */
/* ���������� ���� �Ǵ� ��翡 ���� �й��� �ǹ� */
/* �������� ������ �����Ϸ��� ���� ���� ��Ҹ� �����ؾ� �� */
/* ���� ��Ҵ� ��ġ ���͸����� ���Ǵ� ����ũó�� �������� ������ ������ �����ϴ� ���� ũ���� ��� */
/* ���� ��Ҵ� �پ��� ũ��� ������� ������ �� ���� */
/* ��κ� 3x3 ������ ���� ��Ҹ� ���� ��� */
/* �������� ���� ����� ����� ��ġ�� ��Ÿ���� ������ = ���� ����� �߽� */

/* ���� ������ ħ�İ� ��â ���� ���α׷� */
void erode_dilate()
{
	/* �������� ���꿡�� ���� �⺻�� �Ǵ� ������ ħ��(erosion)�� ��â(dilation) */
	/* ���� ������ ħ�� ������ ��ü ������ �ܰ��� ���� ��� ���� �������� ��ü������ ��ü ������ ��ҵǰ� ����� Ȯ��� */
	/* ���� ��Ҹ� ���� ��ü�� ���� ��ĵ�ϸ鼭, ���� ��Ұ� ��ü ���� ���ο� ������ ���Ե� ��� ������ ��ġ �ȼ��� 255�� ���� */
	/* ���� ������ ��â ������ ��ü �ܰ��� Ȯ���ϴ� ���� */
	/* ��ü ������ Ȯ��ǰ� ��� ������ ��� */
	/* ���� ��Ҹ� ���� ��ü�� ���� �̵���Ű�鼭, ���� ��ҿ� ��ü ������ �� �ȼ��̶� ���� ��� ������ ��ġ �ȼ��� 255�� ���� */
	/* ���� ��Ҵ� OPEN_CV���� ���� ���� 0 �Ǵ� 1�� ������ CV_8UC1Ÿ���� Mat��ķ� ǥ�� */
	/* ���� ��� ��Ŀ��� ���� 1�� ���Ҹ��� �̿��Ͽ� ���� ����� ����� ���� */
	
	/* ���� ��� ����� �����ϴ� �Լ� */
	/* getStructuringElement(shape, ksize, anchor = Point(-1,-1) */
	/* shape = ���� ����� ���, ksize = ���� ����� ũ��, anchor =  MORPH_CROSS����� ���� ��ҿ��� ���ڰ� �߽� ��ǥ */
	/* (-1, -1)�̸� ���� ��� �߾��� ���ڰ� �߽� ��ǥ�� ��� */
	/* kszie = Ȧ�� ���. shape = MORPH_RECT or MORPH_CROSS, MORPH_ELLIPSE ��� */

	/* ħ�� ���� �Լ� */
	/* erode(src, dst, kernel, anchor = (-1,-1), iterations = 1, borderType = BORDER_CONSTANT, borderValue = morphologyDefaultBorderValue()) */
	/* kernel = ���� ��Ҹ� �����ϸ� 3x3 �簢�� ���� ��Ҹ� ���, �� �ܿ��� ���� getStructuringElement�� ����Ͽ� ���� */
	/* anchor = ������ ��ġ, iterations = �ݺ� Ƚ��, borderType = �����ڸ� �ȼ� Ȯ�� ��� */
	/* borderValue = borderType�� BORDER_CONSTANE�� ���, Ȯ��� �����ڸ� �ȼ��� ä�� �� */
	/* kernel�� Mat() or noArray()�� �����ϸ� 3x3 ������ ���� ��Ҹ� ��� */

	/* ��â ���� �Լ� */
	/* dilate() = erode�� �Ű������� ���� */

	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU); // src ���� ���� ���� �˰������� �ڵ� ����ȭ�� �����ϰ� bin�� ����

	Mat dst1, dst2;
	erode(bin, dst1, Mat());
	dilate(bin, dst2, Mat());

	imshow("src", src);
	imshow("bin", bin);
	imshow("erode", dst1);
	imshow("dilate", dst2);

	waitKey();
	destroyAllWindows();
}

/* ���� ������ ����� �ݱ� ���� ���α׷� */
void open_close()
{
	/* �������� ��� �߿��� ����� �ݱ� ���� */
	/* ħ�İ� ��â ������ �̿��Ͽ� ���� ������ �� ���� */
	/* ���� ������ �Է� ���� ���Ͽ� ħ�� ������ ������ ��, �ٽ� ��â ������ �����ϴ� ���� */
	/* �ݱ� ������ �Է� ���� ���Ͽ� ��â ������ ������ ��, �ٽ� ħ�� ������ �����ϴ� ���� */
	/* ħ�İ� ��â ������ �����ϴ� ������ ���� ���� �ٸ� ȿ���� �߻� ( ��ü ������ ũ�Ⱑ ũ�� �ٲ����� ���� ) */
	/* ���� ������ ħ�� ������ ���� �����ϱ� ������ �ѵ� �ȼ�¥�� ������ ���ŵ� ��, ��â ������ ����� */
	/* �� ��� ���� ���� �����ϴ� ���� ũ���� ��ü�� ȿ�������� ���ŵ� */
	/* �ݱ� ������ ��ü ������ ���� ������ �޿���. ��������� ���� ������ ������ */

	/* �������� ����� �ݱ�� morphologyEx()�Լ��� �̿��Ͽ� ���� */
	/* morphologyEx(src, dst, op, kernel, anchor, iterations, borderType, borderValue) */
	/* op�� ������ �������� erode, dilate�Լ��� ������ �Ű������� ���� */
	/* op = �������� ���� ����� ���� */
	/* MORPH_ERODE, MORPH_DILATE, MORPH_OPEN, MORPH_CLOSE, MORPH_GRADIENT ��� */

	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat dst1, dst2;
	morphologyEx(bin, dst1, MORPH_OPEN, Mat());
	morphologyEx(bin, dst2, MORPH_CLOSE, Mat());

	imshow("src", src);
	imshow("bin", bin);
	imshow("opening", dst1);
	imshow("closing", dst2);

	waitKey();
	destroyAllWindows();
}

int main()
{
	//erode_dilate();
	open_close();

	return 0;
}