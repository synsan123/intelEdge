#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void contours_basic1();

// �۵� �ȵ�. �̿ϼ�.
void contours_basic()
{
	VideoCapture cap(1); // USB ī�޶� ������� 1 ���. ��ǻ�� ���� ī�޶�� 0

	if (!cap.isOpened()) { // �� ������ ���� �޽��� ���
		cerr << "Video Fail" << endl;
		return;
	}

    Mat frame;

    while (true) {
        cap >> frame; // ī�޶� ȭ���� frame�� �ǽð����� ����(ĸó)
        if (frame.empty()) { // frame�� ������ �ȵǾ� ��������� ����
            break;
        }
        // �ڽ��� �չٴ� �Կ��Ͽ� ����
        imwrite("hand.jpg", frame);

        // ������ �չٴ� ���� �ε�
        Mat hand = imread("hand.jpg", IMREAD_COLOR);

        // �չٴ� �ܰ��� ���� - �ܰ��� ���� ������ ����� ä��
        Mat gray;
        cvtColor(hand, gray, COLOR_BGR2GRAY);

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(gray, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        Mat dst;
        cvtColor(gray, dst, COLOR_GRAY2BGR);

        for (int idx = 0; idx >= 0; idx = hierarchy[idx][0]) {
            Scalar c(rand() & 255, rand() & 255, rand() & 255);
            drawContours(dst, contours, idx, c, -1, LINE_8, hierarchy);
        }

        imshow("gray", gray);
        imshow("dst", dst);

        if (waitKey(10) == 27) break; // ESC ������ ����
    }
	destroyAllWindows();
}
#if 0
int main(void)
{
	contours_basic();
    //contours_basic1();
	return 0;
}
#endif 

// �۵��� �ϳ� �չٴ� ���θ� ä���� ����(for�� �ٽ� �� ������)
#if 1
int main() {
    VideoCapture cap(1); // 1. ī�޶� �����ϰ� �ǽð����� ĸ��

    if (!cap.isOpened()) {
        cout << "ī�޶� �� �� �����ϴ�." << endl;
        return -1;
    }

    while (1) {
        Mat frame;
        cap >> frame; // 2. ī�޶�κ��� �������� ĸ��

        if (frame.empty()) {
            cout << "�������� ĸ���� �� �����ϴ�." << endl;
            break;
        }

        // 3. �ڽ��� �չٴ� �Կ��Ͽ� ����
        imwrite("hand.jpg", frame);

        // 4. ������ �չٴ� ���� �ε�
        Mat hand = imread("hand.jpg", IMREAD_COLOR);

        // 5. �չٴ� �ܰ��� ���� - �ܰ��� ���� ������ ����� ä��
        Mat gray, edges;
        cvtColor(hand, gray, COLOR_BGR2GRAY);
        Canny(gray, edges, 100, 200);

        vector<vector<Point>> contours;
        findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        for (auto& contour : contours) { // �̿ϼ�
            drawContours(hand, vector<vector<Point>>(1,contour), -1, Scalar(0, 0, 255), -1); // ä��� ������ ���������� ����
        }

        imwrite("contorushand.jpg", hand);
        imshow("Hand Contour", hand);
        imshow("gray", gray);
        imshow("edges", edges);
        
        // 6. ESCŰ�� ������ ���α׷� ����
        if (waitKey(1) == 27) {
            cout << "ESCŰ�� �����̽��ϴ�. ���α׷��� �����մϴ�." << endl;
            break;
        }
    }

    return 0;
}
#endif

void contours_basic1()
{
Mat src = imread("hand.jpg", IMREAD_GRAYSCALE);

if (src.empty()) {
    cerr << "Fail" << endl;
    return;
}
Mat edges;
Canny(src, edges, 50, 150);
/* src �������κ��� ��� �ܰ����� �����Ͽ� contours������ ����. ���� ������ ���� (RETR_LIST ���� ���� ���� ����) */
vector<vector<Point>> contours;
findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

Mat dst;
cvtColor(edges, dst, COLOR_GRAY2BGR);

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

