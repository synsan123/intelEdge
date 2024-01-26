/* �پ��� �׸��� �Լ� */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));

	//line(img, point(50, 50), point(200, 50), scalar(0, 0, 255)); // (img, pt1, pt2, color, thickness)
	//line(img, point(50, 100), point(200, 100), scalar(255, 0, 255), 3);
	//line(img, point(50, 150), point(200, 150), scalar(255, 0, 0), 10);

	//line(img, point(250, 50), point(350, 100), scalar(0, 0, 255), 1, line_4); // (img, pt1, pt2, color, thickness, linetype)
	//line(img, point(250, 70), point(350, 120), scalar(255, 0, 255),1, line_8); // 4���� ����, 8���� ����, ��Ƽ���ϸ����
	//line(img, point(250, 90), point(350, 140), scalar(255, 0, 0), 1, line_aa);

	//arrowedline(img, point(50, 200), point(150, 200), scalar(0, 0, 255), 1); // ȭ��ǥ �׸���
	//arrowedline(img, point(50, 250), point(350, 250), scalar(255, 0, 255), 1); // (img, pt1, pt2, color, thickness, linetype, shift, tiplength)
	//arrowedline(img, point(50, 300), point(350, 300), scalar(255, 0, 0), 1, line_8, 0, 0.05);

	//drawmarker(img, point(50, 350), scalar(0, 0, 255), marker_cross); // ���� �׸��� �Լ�(�پ��� ����� ��Ŀ �׸���)
	//drawmarker(img, point(100, 350), scalar(0, 0, 255), marker_tilted_cross);
	//drawmarker(img, point(150, 350), scalar(0, 0, 255), marker_star); // (img, position, color, markertype, markersize, thickness, line_type)
	//drawmarker(img, point(200, 350), scalar(0, 0, 255), marker_diamond);
	//drawmarker(img, point(250, 350), scalar(0, 0, 255), marker_square);
	//drawmarker(img, point(300, 350), scalar(0, 0, 255), marker_triangle_up);
	//drawmarker(img, point(350, 350), scalar(0, 0, 255), marker_triangle_down);

	//imshow("img", img);
	//waitkey();

	//destroyAllWindows();

	rectangle(img, Rect(50, 50, 100, 50), Scalar(0, 0, 255), 2); // (img, RectŬ����, color, �β�)
	rectangle(img, Rect(50, 150, 100, 50), Scalar(0, 0, 128), -1); // -1�� ��� ���� ä���

	circle(img, Point(300, 120), 30, Scalar(255, 255, 0), -1, LINE_AA); //(img, �߽���, ������, color, �β�, ����Ÿ��)
	circle(img, Point(300, 120), 60, Scalar(255, 0, 255), 3, LINE_AA);

	/* Ÿ�� (img, �߽���, (x�� ������, y�� ������), angle(ȸ��), ȣ�� ���� ����, ȣ�� ������ ����, color, �β�, ����Ÿ�� */
	ellipse(img, Point(120, 300), Size(60, 30), 20, 0, 270, Scalar(128, 128, 0), -1, LINE_AA);
	ellipse(img, Point(120, 300), Size(100, 50), 20, 0, 360, Scalar(128, 255, 128), 2, LINE_AA);

	/* polylines(�ٰ��� �׸��� �Լ�) */
	/* (img, �ٰ��� �ܰ� ������ ��ǥ �迭�� vector<Point>Ÿ���� ����, true(150p����), color, �β�, ����Ÿ��, ��Һ���) */
	vector<Point> pts;
	pts.push_back(Point(250, 250)); pts.push_back(Point(300, 250));
	pts.push_back(Point(300, 300)); pts.push_back(Point(350, 300));
	pts.push_back(Point(350, 350)); pts.push_back(Point(250, 350));
	polylines(img, pts, true, Scalar(255, 0, 255), 2);

	imshow("img", img);
	waitKey();

	destroyAllWindows();

	return 0;
}























