/* ������ : ���� ��ī�Ӱ� �ϱ� */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* �繰�� ������ �ѷ��ϰ� ������ ������ ������ ������ �����ϴ� ���͸� ��� */
/* ������� ������ �̿��Ͽ� ������ ��ī�ο� ������ �����ϴ� ���͸� ����� ����ũ ���Ͷ�� �Ѵ�. */
/* ����� ����ũ ���͸� �������� �ʾ� ������ �� */
void unsharp_mask()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}
	imshow("src", src);

	for (int sigma = 1; sigma <= 5; sigma++) {
		Mat blurred;
		GaussianBlur(src, blurred, Size(), sigma);

		float alpha = 1.f;
		Mat dst = (1 + alpha) * src - alpha * blurred;

		String desc = format("sigma : %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();
}

int main()
{
	unsharp_mask();

	return 0;
}