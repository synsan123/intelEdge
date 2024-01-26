/* �ܰ��� ���� */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* ���̺��� ���Ҿ� ���� ���󿡼� ��ü�� ��ġ �� ũ�� ������ �����ϴ� ������ ��� �߿� �ܰ��� ������ ���� */
/* ��ü�� �ܰ��� �ȼ� ��ǥ�� ��� �����Ͽ� ���� ������ �Բ� ��ȯ */

void contours_basic()
{
	/* ��ü�� �ܰ����� ��ü ���� �ȼ� �߿��� ��� ������ ������ �Ϸ��� �ȼ��� �ǹ� */
	/* ��ü�� �ܰ����� ��ü �ٱ��� �ܰ����� ���� Ȧ �ܰ������� ������ �� ���� */
	/* ��ü �ϳ��� �ܰ����� ���� ���� ������ ������ */
	/* �׷��Ƿ� ��ü �ϳ��� �ܰ��� ������ vector<Point> Ÿ������ ������ �� ���� */
	/* ���� �ϳ��� ���󿡴� ���� ���� ��ü�� ������ �� �����Ƿ� ���� �ϳ����� ����� ��ü ��ü�� �ܰ��� ������ vector<vector<Point>> Ÿ������ ǥ�� */
	/* ����� �ܰ��� ������ ��ǥ�� �տ��� ������ Ÿ���� ������ ��� ����� */
	/* vector<vector<Point>> Ÿ���� vector<Point> Ÿ���� ���� �� ������ �� �ִ� Ÿ���� */
	/* ���� �ܰ��� ��ü�� 3�� �ִٸ� vector<Point> Ÿ���� ������ 3�� �ִ� ���� */
	/* �����̸��� contours�̸� contours[0 ~ 2] ������ vector<Point> Ÿ���� 3���� �ִٴ� ���� �ǹ� */
	/* contours �����κ��� ��ü ��ü ������ �˰� �ʹٸ� contours.size() ��ȯ���� Ȯ���ϸ� �� */
	/* �ܰ����� �� ������ �˰� �ʹٸ� contours[number].size()���·� �ڵ带 �ۼ� */

	/* ���� ���� ��ü���� �ܰ����� �����ϴ� �Լ��� findContours()�Լ� */
	/* �ܰ������� ���� ������ �޾� ���� hierarchy ���ڰ� �ִ� ���¿� ���� ���� �� ������ ���ǵ� */
	/* findContours(image, contours, hierarchy, mode, method, offset = Point()) */
	/* findContours(image, contours, mode, method, offset = Point())*/
	/* image = �Է� ���� 8bit 1-channel ����. 0�� �ƴ� �ȼ��� ��ü�� ���. mode = RETR_CCOMP�̸� CV_32SC1Ÿ�� ���� ���� */
	/* ����ȭ�� ������ ��� */
	/* contours = ����� �ܰ��� ����. vector<vector<Point>> Ÿ�� ������ ���� */
	/* hierarchy = �ܰ��� ���� ����. vector<Vec4i> Ÿ�� ���� ����. int �ڷ��� 4���� ������ �� �ִ� ���� Ŭ���� */
	/* hierarchy[i][1]���� ���� �ܰ��� ��ȣ, hierarchy[i][2]���� �ڽ� �ܰ��� ��ȣ */
	/* hierarchy[i][3]���� �θ� �ܰ��� ��ȣ�� �����. ���� �������� �ش� �ܰ����� �������� ������ -1�� ����� */
	/* mode = �ܰ��� ���� ���. 390p ���� */ 
	/* method = �ܰ��� �ٻ�ȭ ���. 390p ���� */
	/* offset = �ܰ��� �� ��ǥ�� ������(�̵� ����) */

	/* �ܰ����� ���� ������ �ܰ����� ���� ���迡 ���� ������ */
	/* 390 ~ 391p ���� */
	/* ��, 0�� �ܰ��� �ȿ��� 1,2,3�� Ȧ �ܰ����� �����Ƿ� 0�� �ܰ����� 1,2,3�� �ܰ����� �θ� �ܰ���. 1,2,3�� 0�� �ܰ����� �ڽ� �ܰ����� */
	/* 0���� 4�� �ܰ����� ���� ���� ���谡 ���� ����ϹǷ� ���� �ܰ��� �Ǵ� ���� �ܰ����� ���踦 ����. */

	/* mode�� ���� ����Ǵ� �ܰ����� ���� ������ ���� �޶��� */
	/* 391 ~ 392p ���� */

	/* findContours()�Լ��� ������ �ܰ��� ������ �̿��Ͽ� ���� ���� �ܰ����� �׸��� �ʹٸ� drawContours�Լ��� ��� */
	/* drawContours(image, contours, contourIdx, color, thickness, lineType, hierarchy = noArray(), maxLevel = INT_MAX, offset = Point()) */
	/* contours = findContours�� ���� ��ü ��ü �ܰ��� ����, contourIdx = �ܰ��� ��ȣ(������ �����ϸ� ��ü �ܰ����� �׸�) */
	/* color = �ܰ��� ����, lineType = �ܰ��� Ÿ��, hierarchy = �ܰ��� ���� ���� */
	/* maxLevel = �׸� �ܰ����� �ִ� ����. �� ���� 0�̸� ������ ��ȣ�� �ܰ����� �׸�. 1���� ũ�ų� ������ �׿� �ش��ϴ� ���� ������ �ܰ������� �׸� */
	/* offset = �߰������� ������ �ܰ��� �� ��ǥ�� ������(�̵� ����), ������ ��ǥ ũ�⸸ŭ �ܰ��� ��ǥ�� �̵��Ͽ� �׸� */

	Mat src = imread("contours.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	/* src �������κ��� ��� �ܰ����� �����Ͽ� contours������ ����. ���� ������ ���� (RETR_LIST ���� ���� ���� ����) */
	vector<vector<Point>> contours;
	findContours(src, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	/* ��ü �ܰ��� ������ŭ for���� ���� */
	for (int i = 0; i < contours.size(); i++) {
		Scalar c(rand() & 255, rand() & 255, rand() & 255); // contours�� ����� ������ �ܰ����� ������ �������� �׸�
		drawContours(dst, contours, i, c, 5);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

/* ���� ������ ����ϴ� �ܰ��� ����� �׸��� */
void contours_hier()
{
	/* RETR_CCOMP��带 ���. �ܰ��� ���� �� ���� ���� ������ Ȱ���Ͽ� �ܰ����� �׸� */
	Mat src = imread("contours.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	/* findContours�Լ� ȣ�� �� hierarchy���ڸ� �����Ͽ� ���������� �޾ƿ� */
	/* src �������κ��� ��� �ܰ����� �����Ͽ� contours������ ����. */
	/* RETR_CCOMP��带 ����Ͽ� 2�ܰ�� ������ ���� ������ �������. 392p ���� */
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(src, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	/* 0�� �ܰ������� �����Ͽ� ���� ������ ���� �ܰ������� �̵��ϸ鼭 for���� ���� */
	/* ���� idx�� �ʱⰪ�� 0�̰�, idx = hierarchy[idx][0]�ڵ带 �̿��Ͽ� idx���� ���ŵ� */
	/* ���⼭ hierarchy[idx][0]�� idx���� �ش��ϴ� �ܰ����� ���� �ܰ��� ��ȣ�� ����Ŵ */
	/* ��� 3ȸ �ݺ���. ������ 3�� �ִٴ� ������ ��� 3ȸ �ݺ����� ����(��, ���� ������ 3�� ����) */
	for (int idx = 0; idx >= 0; idx = hierarchy[idx][0]) {
		Scalar c(rand() & 255, rand() & 255, rand() & 255); // contours�� ����� ������ �ܰ����� ������ �������� �׸�
		/*drawContours�Լ��� hierarchy������ �����Ͽ� �ܰ����� �׸����� ��. ���� �β��� -1�� �����Ͽ����Ƿ� �ܰ��� ���θ� ������ ����� ä�� */
		drawContours(dst, contours, idx, c, -1, LINE_8, hierarchy); 
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

#if 1
int main()
{
	contours_basic();
	//contours_hier();

	return 0;
}
#endif

/* �ܰ��� ó�� �Լ� */
/* �ܰ��� ���� �� �ܰ��� ��ǥ ������ �̿��ϴ� ���� �Լ� ����. 
   �ܰ��� �����κ��� ��ü�� ��ġ�� ũ�� �� ������ �˾Ƴ� �� �ִ� �� ���� �Լ��� 
   �־��� �ܰ��� ������ ���δ� ���� ���� ũ���� �簢��, �� �ٿ�� �ڽ��� ���ϴ� �Լ��� boundingRect(points)�Լ� 
   points = �Է� ������ �������� vector<Point> or Mat Ÿ���� 
   connectComponentsWithStats()�Լ��� �̿��ص� ���� �� ������ �ܰ��� ������ ������ �ִ� ��쿡�� boundingRect�� ȿ���� 
   
   �ܰ��� �Ǵ� ������ ���δ� �ּ� ũ���� ȸ���� �簢���� ���� ���� minAreaRect(points)�Լ��� ��� 
   Ư�� �ܰ����� ���δ� ���� ���� ������ �簢�� ������ ��ȯ�ϴ� �Լ�. RotatedRectŬ���� ��ü�� ��ȯ 
   
   �ܰ��� �Ǵ� ������ ���δ� �ּ� ũ���� ���� ���ϰ� ���� ���� minEnclosingCircle(points, center, radius)�Լ� ���
   
   ������ ��� �����ϴ� ������ ������ ������ ���� ��, �ش� ��� ���̸� ���ϰ� �ʹٸ� arcLength(curve, bool closed)�Լ� ��� 
   curve = �Է� �, closed = �� ����. (true�̸� ������. false�� ����) 
   
   ������ �ܰ��� ������ ������ ���� ��, �ܰ����� ���δ� ������ ������ �˰� �ʹٸ� contourArea(contour, oriented = false) �Լ� ��� 
   contour = �Է� �, oriented = ���� ���� ���� ��� ����. true�̸� ���� ���⿡ ���� ������ ��ȣ�� �޶���. false�� ���밪 ���� ��ȯ 
   
   �ܰ��� �Ǵ� ��� �ٻ�ȭ�ϴ� approxPolyDP(curve, approxCurve, epsilon, closed) �Լ� ��� 
   �־��� ��� ���¸� �ܼ�ȭ�Ͽ� ���� ������ ������ ������ ��� ������ 
   curve = �Է� 2���� ������ ��ǥ. approxCurve = ��� �ٻ�ȭ�� ������ ��ǥ 
   epsilon = �ٻ�ȭ ���е� �Ķ����. �Է� ��� �ٻ�ȭ�� ������� �ִ� �Ÿ��� ���� 
   ���۶�-����Ŀ �˰����� ����Ͽ� � �Ǵ� �ٰ����� �ܼ�ȭ ��Ŵ 399p ���� */

/* setLabel �Լ��� img���󿡼� pts �ܰ��� �ֺ��� �ٿ�� �ڽ��� �׸��� label ���ڿ��� ����� */
void setLabel(Mat& img, const vector<Point>& pts, const String& label)
{
	Rect rc = boundingRect(pts); // pts �ܰ����� ���δ� �ٿ�� �ڽ��� ���� 
	rectangle(img, rc, Scalar(0, 0, 255), 1); // �ٿ�� �ڽ��� ���������� ���� 
	putText(img, label, rc.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255)); // �ٿ�� �ڽ� ���� ��ܿ� label���ڿ��� ���
}
#if 0
int main(int argc, char* argv[])
{
	Mat img = imread("polygon.bmp", IMREAD_COLOR);

	if (img.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	Mat bin;
	threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);

	/* bin ���󿡼� ��� ��ü�� �ٱ��� �ܰ����� ������ */
	vector<vector<Point>> contours;
	findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	/* ����� �� ��ü�� �ܰ��� ��ǥ�� pts������ �����ϸ鼭 for���� ���� */
	for (vector<Point>& pts : contours) {
		if (contourArea(pts) < 400) /* �ܰ����� ���δ� ������ 400���� ������ �������� �����Ͽ� ������*/
			continue;

		/* pts�ܰ����� �ٻ�ȭ�Ͽ� approx������ ���� */
		vector<Point> approx;
		approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);

		int vtc = (int)approx.size(); // approx������ ����� �ܰ��� ���� ������ vtc�� ����

		/* �ٻ�ȭ�� �ܰ����� ������ ������ 3���̸� �ܰ��� �ֺ��� �ٿ�� �ڽ��� �׸��� TRI ���ڿ��� ��� */
		if (vtc == 3) {
			setLabel(img, pts, "TRI");
		}
		else if (vtc == 4) { /* �ٻ�ȭ�� �ܰ����� ������ ������ 4���̸� �ܰ��� �ֺ��� �ٿ�� �ڽ��� �׸��� RECT ���ڿ��� ��� */
			setLabel(img, pts, "RECT");
		}
		else if (vtc > 4) { /* ��ü�� ���� �� ���� ������ �����Ͽ� ���� ������ �ܰ��� �ֺ��� �ٿ�� �ڽ��� �׸��� CIR ���ڿ��� ��� */
			double len = arcLength(pts, true); // pts�� �� ��ü�� �ܰ��� ��ǥ�� ����� vector<Point> ��ü
			double area = contourArea(pts);
			double ratio = 4. * CV_PI * area / (len * len);

			if (ratio > 0.8) { // ratio�� 1�� �������� �� ��翡 �����.
				setLabel(img, pts, "CIR");
			}
		}
	}

	imshow("img", img);

	waitKey();
	destroyAllWindows();
	return 0;
}
#endif