/* 13�� ��ü ���� */
/* ���ø� ��Ī */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* �Է� ���󿡼� ���� ũ���� �κ� ���� ��ġ�� ã�Ƴ��� ���� ��� ���ø� ��Ī�� ��� 
   ���⼭ ���ø��� ã���� �ϴ� ����� �Ǵ� ���� ũ���� ������ �ǹ��� 
   ���ø� ��Ī�� ���� ũ���� ���ø� ������ �Է� ���� ��ü ������ ���� �̵��ϸ鼭 ���� ����� ��ġ�� ��ġ������ ã�Ƴ��� ��� 
   
   ���� ��� ���� ���󿡼� ���� �� ���� �κ� ������ ���ø����� ����Ͽ� ���ø� ��Ī�� �����ϴ� �������� ���ø� ��Ī�� ���۹�� ���� 
   ���ø� ������ �Է� ���� ��ü ������ ���� �̵��ϸ鼭 ���ø� ����� �Է� ���� �κ� ������� ���絵 �Ǵ� �����絵�� ��� 
   
   ���絵�� ����� ���, �ۤ��ø� ����� ����� �κ� ���� ��ġ���� ���� ũ�� ��Ÿ����, �����絵�� ��� ���� �۰� ���� 
   
   ���ø� ��Ī �Լ� matchTemplate(image, templ, result, method, mask = noArray()) 
   templ = ���ø� ����. �Է� ���󺸴� �۰ų� ���ƾ� �ϸ�, Ÿ���� ���ƾ� ��
   result = ��� �� ����� ������ ���. CV_32FC1 Ÿ�� 
   method = ���ø� ��Ī �� ��� , 406p ����
   mask = ã���� �ϴ� ���ø��� ����ũ ����, templ�� ���� ũ�� �� Ÿ���̾�� ��. TM_SQDOFF, TM_CCORR_NORMED ��������� ������ 
   
   ���ø� ��Ī���� ���ܳ��� ���絵 �� �Ǵ� �����絵 ���� result���ڷ� ��ȯ. image = W x H �̰� templ = w x h�� ��� 
   result ����� ũ��� (W - w + 1) x (H - h + 1)�� ������ 
   
   ���� ��Ī ��� �߿��� ����ȭ�� �������(������) ��Ī ����� ���� ����� �����ϳ� ������ �����ϰ� ���귮�� ����(TM_CCORR_NORMED)
   ������ ��Ī ���(TM_SQDIFF)�� result ��� ��Ŀ��� �ּڰ� ��ġ�� ���� ��Ī�� �� �� ��ġ�� �����ؾ� ��.
   TM_CCORR or TM_CCOEFF(������� or ������ ��Ī ���)�� result ��� ��Ŀ��� �ִ� ��ġ�� ���� ��Ī�� �� �� ��ġ�� �����ؾ� �� 
   result ��Ŀ��� �ּڰ� ��ġ or �ִ� ��ġ�� minMaxLoc�Լ��� ����Ͽ� �˾Ƴ� �� ���� */
void template_matching()
{
	Mat img = imread("circuit.bmp", IMREAD_COLOR);
	Mat templ = imread("rectan.bmp", IMREAD_COLOR);

	if (img.empty() || templ.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	img = img + Scalar(50, 50, 50); // ���� ��⸦ 50��ŭ ����

	Mat noise(img.size(), CV_32SC3); // �Է� ���� ǥ�� ������ 10�� ����þ� ������ �߰�. 
	randn(noise, 0, 10);
	add(img, noise, img, Mat(), CV_8UC3);

	/* ���ø� ��Ī ��� ��� res�� -1 ���� 1������ �Ǽ� */
	Mat res, res_norm; // res_norm = ���ø� ��Ī���� ���� ���絵 ����� �׷��̽����� ���� �������� ��Ÿ�� ��
	matchTemplate(img, templ, res, TM_CCOEFF_NORMED); // ����ȭ�� ������ ��Ī ����� ����Ͽ� ���ø� ��Ī�� ����
	normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8UC1); // ���ø� ��Ī ��� ��� res�� ��� ���� ���� 0~255 ���̷� ����ȭ�ϰ� Ÿ���� CV_8UC1���� ��ȯ�Ͽ� res_norm ���� ����

	/* res ��Ŀ��� �ִ� ��ġ�� ã�� maxloc�� ������ */
	/* �� ��ġ������ �ִ� maxv�� ���ø� ��Ī�� �� �Ǿ������� �����ϴ� ô���� ����� �� ���� */
	/* 1�� �������� ��Ī�� �� �Ǿ��ٰ� ������ */
	double maxv;
	Point maxloc;
	minMaxLoc(res, 0, &maxv, 0, &maxloc);
	cout << "maxv : " << maxv << endl;

	/* img ���� ���ø� ��Ī���� ã�� ��ġ�� ������ �簢������ ǥ���� */
	rectangle(img, Rect(maxloc.x, maxloc.y, templ.cols, templ.rows), Scalar(0, 0, 255), 2);

	imshow("templ", templ);
	imshow("res_norm", res_norm);
	imshow("img", img);

	waitKey();
	destroyAllWindows();
}

#if 0
int main()
{
	template_matching();

	return 0;
}
#endif