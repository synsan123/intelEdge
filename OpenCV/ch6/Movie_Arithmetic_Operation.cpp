/* ������ ��� ���� */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	/*add(src1, src2, dst, mask, dtype), dtype�� ��� src1�� src2�� ���̰� �ٸ��ٸ� �ݵ�� ������ �ʿ�. default�� -1 */
	/* src���� Scalar, ����, �Ǽ� �ڷ��� ���� �� �� ���� */
	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;
	add(src1, src2, dst1); // Or dst1 = src1 + src2; ����. �� �� �Է� ������ Ÿ���� �����ϴٸ� 

	/* ����ġ �ο� */
	/* �� ������ ����ġ ���� ���ϴ� �Լ� addWeighted() */
	/* addWeighted(src1, alpha, src2, beta, gamma, dst, dtype), gamma�� ������ ����� �߰������� ���� �� */
	/* alpha + beta = 1 (�� �Է� ������ ������ ���� ����) , alpha + beta < 1 (��ο���), alpha + beta > 1 (�����) */
	addWeighted(src1, 0.5, src2, 0.5, 0, dst2);

	/* subtract(src1, src2, dst, mask, dtype) ���� �Լ� */
	/* ������ ����� �Ǵ� ���� ������ ���� ������� �޶��� (�տ� ������ �ڿ������Ŀ� ���� �޶����� ��) */
	subtract(src1, src2, dst3);

	/* ���� ���� */
	/* ������ ���� ������ ������� �ȼ� �� ���̰� ū ������ �ε巯���� ��Ÿ���� �ϴ� �Լ� absdiff() */
	/* absdiff(src1, src2, dst) */
	/* ���� ���� ����� ���밪�� ���ϴ� ����. ���� �������� ���� ��� ������ �������̶�� �Ѵ�. */
	absdiff(src1, src2, dst4);

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);

	waitKey();
	destroyAllWindows();

	return 0;
	/* ���� ������ ����̹Ƿ� �� �Է� ������ ��ķ� �����Ͽ� ������ ������ �� �� ������ ���� ����. */
	/* �ٸ� �� ���󿡼� ���� ��ġ�� �ִ� �ȼ� ������ ���� ���ϰų� ������ ������ ������ �� ���� */
	/* multiply(src1, src2, dst, scale = 1, dtype). scale�� �߰������� Ȯ��/����� ���� */
	/* divide(src1, src2, dst, scale = 1, dtype) */
}