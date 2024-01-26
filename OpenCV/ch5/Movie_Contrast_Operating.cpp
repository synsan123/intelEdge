/* ������ ��Ϻ� ���� */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;


#if 0
int main()
{
	/* ��Ϻ��? */
	/* ���� ������ ��ο� ���� ���̿� �巯���� ��� ������ ������ �ǹ� */
	/* ���� ������ ��ο� ������ ���� ������ ��Ϻ� ���ٶ�� ��. ��� ���ʿ� ġ���������� ���ٰ� ��. */
	/* ��Ϻ�� ���� ������ ����Ͽ� ���� */
	/* ������ ���� ����� ���ϴ� ����� �� ��� �� ��. ������ ��Ϻ� �������� �繰�� ������ �����ϴ� ���� ���� �ʾƼ� */
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	float s = 2.f;
	Mat dst = s * src;

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();

	return 0;
}
#endif

int main()
{
	/* ȿ������ ��Ϻ� ���� ��� */
	/* dst(x,y) = saturate(src(x,y) + (src(x,y)-128)*a) */ // 128�� �������� 
	/* �ݵ�� (128, 128)�� ������ -1<= a <= 0�̸� ��Ϻ� ����. a > 0�̸� ��Ϻ� ���� */
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	float alpha = 1.f;
	Mat dst = src + (src - 128) * alpha;

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();

	return 0;
}