/* �÷� ���� ó�� ��� */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

#if 0
int main()
{
	/* �÷� ������׷� ��Ȱȭ */
	/* equalizeHist()�Լ��� GrayScale���� ������ */
	/* �÷� ������׷� ��Ȱȭ�� �����Ϸ��� ���� �����Ͽ��� �� */
	/* �÷� ���� ���� ������׷� ��Ȱȭ�� �����Ϸ��� �Է� ������ ��� ������ ���� ������ �и��� ��, ��� ������ ���ؼ��� ��Ȱȭ�� ���� */
	/* ���� ��� �� ������ YCrCb�� ������ ��, Y���п� ���ؼ��� ��Ȱȭ�� ����. Cr,Cb�� �״�� ����. �׸��� ��ġ�� ��Ȱȭ ��� ������ ���� �� ���� */
	/* �̷��� �Ǹ� ���� ������ ���� ������� �����Ƿ�, �Է� ������ ������ �״�� �����Ǹ�, ���� ��� ���п� ���ؼ��� ��Ϻ� �����ϰ� �� */
	
	Mat src = imread("pepper.bmp", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	Mat src_ycrcb; // src ������ YCrCb�� �������� �����Ͽ� src_ycrcb�� ����
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	vector<Mat> ycrcb_planes; // src_ycrcb������ ä���� �и��Ͽ� ycrcb_planes�� ����
	split(src_ycrcb, ycrcb_planes);

	equalizeHist(ycrcb_planes[0], ycrcb_planes[0]); // Y���п� �ش��ϴ� ycrcb_planes[0]���� ���ؼ��� ��Ȱȭ�� ����

	Mat dst_ycrcb; // ycrcb_planes���Ϳ� ��� �ִ� 3������ ���ļ� dst_ycrcb������ ����
	merge(ycrcb_planes, dst_ycrcb);

	Mat dst; // dst_ycrcb������ �� ������ BGR�� �������� ��ȯ�Ͽ� dst�� ����
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();

	return 0;
}
#endif


#if 0
int lower_hue = 40, upper_hue = 80; // �� ���� Ʈ���� ��ġ�� ������ ������ ������ ���� ������ ����
Mat src, src_hsv, mask; // main�Լ��� Ʈ���� �ݹ� �Լ� on_hue_changed�Լ����� �Բ� ����� Mat��ü�� ���� ������ ����

void on_hue_changed(int, void*) // Ʈ���� �ݹ� �Լ�
{
	Scalar lowerb(lower_hue, 100, 0); // ����ڰ� ������ ���Ѱ��� ���Ѱ��� �̿��Ͽ� lowerb, upperb��ü�� ����.
	Scalar upperb(upper_hue, 255, 255); // ä���� ������ 100 ~ 255, ���� ������ �����ϵ��� 0 ~ 255�� ����
	inRange(src_hsv, lowerb, upperb, mask); // src_hsv ���󿡼� HSV �� ���� ������ lowerb ~ upperb ������ ��ġ�� �ȼ��� ������� ������ mask ������ ����

	imshow("mask", mask);
}

int main(int argc, char* argv[])
{
	/* ���� ���� ������ ���� ���� ���� */
	/* �÷� ������ �ٷ�� ���뿡�� ���� �䱸�Ǵ� ����� Ư�� ���� ������ �����ϴ� �۾��̴� */
	/* ���� ��� �Է� ���󿡼� ������ �ȼ��� ��� ã�Ƴ��� ������ ��ü�� ��ġ�� ũ�⸦ �� �� ���� */
	/* HSV���� ���� ������ ���� �����Ǿ� �ִ� �� ������ ����ϴ� ���� ���� */
	/* ����� ���� ���� Ư�� ���� �ȿ� �ִ��� Ȯ���Ϸ��� inRange() �Լ��� ��� */
	/* inRange(src, lowerb, upperb, dst)*/
	/* lowerb, upperb = ���� ��, ���� ��. �ַ� Mat or Scalar ��ü�� ���� */
	/* �Է� ������ �ȼ� ���� ������ ��� �Ǵ� ���� ������ ���ԵǾ� ������ ���, �׷��� ������ ���������� ä���� ����ũ ���� dst�� ��ȯ */
	/* �׷��̽����� ������ �Է� �������� ����� ���, Ư�� ��� �� ������ �ִ� �ȼ� ������ ������ �� ���� */
	/* Mat��ü�� ������ ���, src�� ��� �ȼ��� ���� �ٸ� ���� ���� ���� ���� ������ �� ���� */
	/* Scalar��ü �Ǵ� int, double�� ���� �ڷ����� ������ ��쿡�� src�� ��� �ȼ��� ������ ���� ���� ���� ���� ����� */

	/* H�� 40 ~ 80 �� �߰����� 60�̸� ���, 100 ~ 140 �� �߰����� 120�̸� �Ķ��� */
	/* S�� ä���� ������ 100 ~ 255, V�� ���� ������ 0 ~ 255�� */
	src = imread("candies.png", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	cvtColor(src, src_hsv, COLOR_BGR2HSV); // HSV�� ���� �� src_hsv�� ����

	imshow("src", src);

	namedWindow("mask");
	createTrackbar("Lower Hue", "mask", &lower_hue, 179, on_hue_changed); // ������ ���� ���� ���� ���� ������ �� �ִ� Ʈ���ٸ� ����
	createTrackbar("Upper Hue", "mask", &upper_hue, 179, on_hue_changed); // ������ �ִ��� 179�� ����. Ʈ���� �ݹ� �Լ��� on_hue_changed�Լ��� ����
	on_hue_changed(0, 0); // ���α׷��� ó�� ����� �� ������ ���������� ��µǵ��� Ʈ���� �ݹ� �Լ��� ������ ȣ��

	waitKey();
	destroyAllWindows();

	return 0;
}
#endif


int main()
{
	/* ������׷� ������ */
	/* HSV�� ������ ������ ����� ������ ã�⿡�� ȿ���������� ����� �Ǻλ�ó�� �̼��� ��ȭ�� �ְų� ���� ���� ��ġ������ �����ϱ� ����� ���״� �������� ���� */
	/* �Է� ���󿡼� ã���� �ϴ� ��ü�� ���� ������ �̸� ������ �ִٸ� �÷� ������׷� ������ �̿��Ͽ� ����� ���� ������ ã�� �� ���� */
	/* ��, ���� �������κ��� ã���� �ϴ� ��ü�� �÷� ������׷��� �̸� ���ϰ�, �־��� �Է� ���󿡼� �ش� ������׷��� �����ϴ� ������ ã�Ƴ��� ��� */
	/* ��ó�� �־��� ������׷� �𵨰� ��ġ�ϴ� �ȼ��� ã�Ƴ��� ����� ������׷� �������̶�� �Ѵ� */
	/* calcBackProject(images, nimages, channels, hist, backProject, ranges, scale = 1, uniform = true) */
	/* images = �Է� ������ �迭 �Ǵ� �ּ�, nimages = �Է� ���� ����, channels = ������ ��� �� ����� ä�� ��ȣ �迭 */
	/* hist = �Է� ������׷�, backProject = ��� ������׷� ������ ����(�Է� ����� ���� ũ��, ���̸� ���� 1ä�� ���) */
	/* ranges = �� ������ ������׷� ��(����) ������ ��Ÿ���� �迭�� �迭 */
	/* scale = ������׷� ������ ���� �߰������� ���� ��. uniform = ������׷� ���� ������ �յ������� ��Ÿ���� �÷��� */
	/* hist�� calcHist�Լ��� �̿��Ͽ� ����. */

	Mat ref, ref_ycrcb, mask;
	ref = imread("ref.png", IMREAD_COLOR); // �Ǻλ� ������׷� ������ ������ ���� ���� ref.png������ �ҷ�
	mask = imread("mask.bmp", IMREAD_GRAYSCALE); // ���� ���󿡼� �Ǻλ��� �ִ� ��ġ�� ������� ǥ���� ����ũ ���� ������ �ҷ� 
	cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);

	Mat hist; // ���� ���󿡼� �Ǻλ� ������ CrCb 2���� ������׷��� ����Ͽ� hist�� ����
	int channels[] = { 1, 2 };
	int cr_bins = 128;
	int cb_bins = 128;
	int histSize[] = { cr_bins, cb_bins };
	float cr_range[] = { 0, 256 };
	float cb_range[] = { 0, 256 };
	const float* ranges[] = { cr_range, cb_range };

	calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);

	Mat src, src_ycrcb; 
	src = imread("kids.png", IMREAD_COLOR);
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	Mat backproj; // �ռ� ���� ������׷� hist�� �̿��Ͽ� �Է� ���󿡼� ������׷� �������� ����. ����� backproj�� ����
	calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges, 1, true);

	imshow("src", src);
	imshow("backproj", backproj);

	waitKey();
	destroyAllWindows();

	return 0;
}