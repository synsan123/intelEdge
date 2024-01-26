/* 14�� ���� Ư¡�� ����� ��Ī */
/* �ڳ� ���� */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* Harris �ڳ� ����� FAST �ڳ� ���� ���

   ũ�� �Һ� Ư¡�� ������ �⺻�� �Ǵ� ����̹Ƿ� ����� ������ �ʿ䰡 ���� 

   ���ø� ��Ī�� �Է� ���󿡼� Ư�� ��ü ��ġ�� ã�� �� �����ϰ� ����� �� ������ ������ ũ�Ⱑ �ٲ�ų� ȸ���� �Ǹ� �۵��� ����� �ȉ� 
   
   ���󿡼� Ư¡�̶� �������κ��� ������ �� �ִ� ������ ������ �ǹ��ϸ� ��� ���, ������׷�, ����, ���� ����, �ڳ� ���� Ư¡�� �� �� ����
   ����, ���� ����, �ڳ�ó�� ������ �Ϻ� �������� ������ �� �մ� Ư¡�� ���� Ư¡�̶�� ��
   �ڳʴ� ������ ������ �ް��ϰ� ���ϴ� �κ����μ� �ﰢ���� �������̳� ���� ��ó�� �����ϰ� Ƣ��� �ִ� �κ��� �ڳʰ� �� �� ����
   �ڳʴ� �ٸ� ���� Ư¡�� ���� �к����� ���� ��ü�� ���� �� ������ ���� �����ϱ� ������ ������ �м��ϴµ� ������
   �ڳ�ó�� �� ���� ���·� ǥ���� �� �ִ� Ư¡�� Ư¡���̶�� �ϸ�, Ư¡���� Ű����Ʈ �Ǵ� �������̶�� �θ��⵵ ��
   �ڳʴ� ������ ��ź�� ������ ���� �������� ���Ƽ� �� ��ġ�� �ľ��ϱ� ������ 
   
   �ظ����� ���� ���ǵ� �ڳ� ���� �Լ� R�� �Է� ���� ������ �ȼ����� ���ǵǴ� �Ǽ� ���̸�
   R�� 0���� ����� ū ����̸� �ڳ� ���̶�� ������
   R�� 0�� ����� �Ǽ��̸� ��ź�� ����, 0���� ���� �����̸� ������� �Ǻ��� 
   
   �ظ��� �ڳ� ���� �Լ� ���� ����ϴ� cornerHarris()�Լ��� ����. �ظ��� �ڳ� ���� �Լ� ���� ��ȯ
   �� ���� ������ �Ӱ谪 ������ �����ϸ� ���󿡼� �ڳ� ��ġ�� ��� ã�� �� ���� 
   cornerHarris(src, dst, blockSize, ksize, k, borderType = BORDER_DEFAULT) 
   dst = �ظ��� �ڳ� ���� �Լ� ���� ������ ���. CV_32FC1. �� ���� ����ڰ� ������ �Ӱ谪���� ũ�� �ڳ� ������ �Ǵ��� �� ����
   blockSize = ��� M ���꿡 ����� �̿� �ȼ� ũ��. �ȼ� �ֺ� blockSize x blockSize �����츦 �����Ͽ� ��� M�� ����� 
   ksize = �Һ� �����ڸ� ���� Ŀ�� ũ��
   k = �ظ��� �ڳ� ���� ���. ���� 0.04 ~ 0.06 ������ ���� ��� 
   borderType = �����ڸ� �ȼ� Ȯ�� ��� 
    
   �ϳ��� �ڳ� ��ġ�� ����� ���� �Ӱ谪���� ū �ȼ��� ���� �� �߻��� �� �����Ƿ�,
   ������ ���ִ� ������ �����Ͽ� ���� �ִ� ��ġ�� �ڳʷ� �Ǻ��ϴ� ���� ���� */

void corner_harris()
{
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	/* src �������κ��� �ظ��� �ڳ� ���� �Լ� ��� harris�� ���� */
	Mat harris;
	cornerHarris(src, harris, 3, 3, 0.04);

	/* harris ��� ���� �� ������ 0 ~ 255�� ����ȭ�ϰ�, Ÿ���� CV_8UC1���� ��ȯ�Ͽ� harris_norm�� ���� 
	   harris_norm�� �׷��̽����� ���� ������ ������, �ظ��� �ڳ� ���� �Լ� ������ ���� ���·� ȭ�鿡 ǥ���ϱ� ���� ���� */
	Mat harris_norm;
	normalize(harris, harris_norm, 0, 255, NORM_MINMAX, CV_8UC1);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (int j = 1; j < harris.rows - 1; j++) {
		for (int i = 1; i < harris.cols - 1; i++) {
			if (harris_norm.at<uchar>(j, i) > 120) { // harris_norm ���󿡼� ���� 120���� ū �ȼ��� �ڳʷ� ������ 
				/* ������ ���ִ� ������ ������. (i, j)��ġ���� �ֺ� �� ���� �ȼ��� ���Ͽ� ���� �ִ��� ��쿡�� dst ����
				   ������ ������ �ڳʸ� ǥ���� */
				if (harris.at<float>(j, i) > harris.at<float>(j - 1, i) &&
					harris.at<float>(j, i) > harris.at<float>(j + 1, i) &&
					harris.at<float>(j, i) > harris.at<float>(j, i - 1) &&
					harris.at<float>(j, i) > harris.at<float>(j, i + 1)) {
					circle(dst, Point(i, j), 5, Scalar(0, 0, 255), 2);
				}
			}
		}
	}

	imshow("src", src);
	imshow("harris_norm", harris_norm);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

/* Harris ���� ����� ������ ������ �ʿ�� �ϱ� ������ ���� �ӵ��� �����ٴ� ������ ����
   �̷��� �ڳ� ���� ����� �޸� FAST�ڳ� ������ �ܼ��� �ȼ� �� �� ����� ���� �ڳʸ� ������
   FAST ����� ������ ��� �ȼ����� �ȼ��� �ѷ��ΰ� �ִ� 16���� �ֺ� �ȼ��� ��⸦ ���Ͽ� �ڳ� ���θ� �Ǻ��� 
   ���� ��� �� p�� �ִµ� �� p�� �ڳ������� �Ǻ��ϱ� ���� p�� �ֺ� 1������ 16�� �ȼ����� ��⸦ ���� 
   ���� �ֺ� 16���� �ȼ� �߿��� �� p���� ����� ��ų� �Ǵ� ����� ��ο� �ȼ��� 9�� �̻� �������� �����ϸ� �ڳʷ� ����
   
   FAST �ڳ� ����� Ư�� �ڳ� �� �ֺ� �ȼ��鵵 �Բ� �ڳʷ� �����ϴ� ��찡 ���� ������ �ֺ� �ڳ� �ȼ� �߿���
   ���� �ڳʿ� ������ �ȼ��� �����ϴ� ���ִ� ���� �۾��� �߰������� �����ϴ� ���� ����
   FAST �ڳ� ������� �ڳ� ���� �ֺ� 16�� ������ �ȼ� �� ���� ���� �ڳ� ������ �����ϰ�
   ������ �ڳ� �߿��� �ڳ� ������ ���� ū �ڳʸ� ���� �ڳʷ� ������ 
   
   FAST �ڳ� ���� ����� ������ FAST()�Լ�
   FAST(image, keypoints, threshold, nonmaxSuppression = true) 
   image = �׷��̽����� ����. 
   keypoints = ����� Ư¡���� ǥ���ϴ� keyPoint ��ü�� ����(vector<keyPoint>�ڷ���>. keyPoint::pt��� ������ �ڳ� �� ��ǥ�� �����
   threshold = �߽� �ȼ� ���� �ֺ� �ȼ� ������ ���� �Ӱ谪 
   nonmaxSuppression = ���ִ� ���� ���� ����, true�̸� ���� 
   FAST�Լ��� ���� ������ �ڳ� �� �߿��� i��° �ڳ��� x, y��ǥ�� keypoints[i].pt.x�� keypoints[i].pt.y�ڵ�� ������ �� ����*/

void corner_fast()
{
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	/* src���󿡼� FAST������� �ڳ� ���� �����մϴ�. ��� ���� �Ӱ谪���� 60�� �����Ͽ���, ���ִ� ������ �����ϵ��� �����Ͽ��� 
	   ����� ��� �ڳ� �� ��ǥ�� keypoints������ ������ */
	vector<KeyPoint> keypoints;
	FAST(src, keypoints, 60, true);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	/* ����� ��� �ڳ� ���� �������� 5�� ������ ���� �׸� */
	for (KeyPoint kp : keypoints) {
		Point pt(cvRound(kp.pt.x), cvRound(kp.pt.y));
		circle(dst, pt, 5, Scalar(0, 0, 255), 2);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main()
{
	//corner_harris();
	corner_fast();
	return 0;
}