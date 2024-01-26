#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

#if 0
Rect box; // ���콺�� �巡���� �簢�� ������ ���� ��ü
bool drawing = false; // ���콺 �巡�� ���¸� �����ϴ� ����

// �簢���� �׸��� �Լ�
void draw_box(Mat& img, Rect box) {
    rectangle(img, box, Scalar(0, 0, 255), 2); // img �̹����� box ������ ���������� �׸�
}

// ���콺 �̺�Ʈ ó�� �Լ�
void onMouse(int event, int x, int y, int, void* param) {
    Mat& image = *(Mat*)param; // ���콺 �̺�Ʈ�� �߻��� �̹���
    switch (event) {
    case EVENT_MOUSEMOVE:
        if (drawing) {
            box.width = x - box.x; // ���콺�� �巡���ϴ� ���� �簢���� �ʺ� ����
            box.height = y - box.y; // ���콺�� �巡���ϴ� ���� �簢���� ���� ����
        }
        break;
    case EVENT_LBUTTONDOWN:
        drawing = true; // ���콺 ���� ��ư�� ������ �巡�� ����
        box = Rect(x, y, 0, 0); // ���� ��ǥ ����
        break;
    case EVENT_LBUTTONUP:
        drawing = false; // ���콺 ���� ��ư�� ���� �巡�� ����
        if (box.width < 0) {
            box.x += box.width; // �簢���� �ʺ� ������ ��� ��ǥ�� �ʺ� ������
            box.width *= -1;
        }
        if (box.height < 0) {
            box.y += box.height; // �簢���� ���̰� ������ ��� ��ǥ�� ���̸� ������
            box.height *= -1;
        }
        draw_box(image, box); // �巡�װ� ����� ���� �簢���� �׸�
        break;
    }
}

int main() {
    Mat image = imread("lenna.bmp"), temp; // lenna.bmp �̹����� �ҷ��� image�� ����, temp�� �ӽ� �̹���
    if (image.empty()) {
        cout << "Could not open image file" << endl; // �̹��� ������ ���� ��� ���� �޽��� ��� �� ����
        return -1;
    }
    box = Rect(-1, -1, 0, 0); // �ʱ� �簢�� ���� ����
    temp = image.clone(); // temp�� image ����

    namedWindow("window"); // window��� �̸��� â ����
    setMouseCallback("window", onMouse, (void*)&image); // window â���� ���콺 �̺�Ʈ�� �߻��ϸ� onMouse �Լ� ȣ��

    while (1) {
        image.copyTo(temp); // temp�� image ����
        if (drawing) draw_box(temp, box); // �巡�� ���̸� �簢�� �׸�
        imshow("window", temp); // window â�� temp �̹����� ������

        // 's' Ű�� ������ ������ ������ ROI.bmp ���Ϸ� ����
        if (waitKey(1) == 's') {
            if (box.width > 0 && box.height > 0) {
                Mat roi = image(box); // ������ ������ roi�� ����
                imwrite("ROI.bmp", roi); // roi�� ROI.bmp ���Ϸ� ����
                break;
            }
        }
    }

    destroyAllWindows();
    return 0;
}
#endif

Rect box;
bool drawing = false;

void draw_box(Mat& img, Rect box) {
    rectangle(img, box, Scalar(0, 0, 255), 2);
}

void onMouse(int event, int x, int y, int, void* param) {
    Mat& image = *(Mat*)param;
    switch (event) {
    case EVENT_MOUSEMOVE:
        if (drawing) {
            box.width = x - box.x;
            box.height = y - box.y;
        }
        break;
    case EVENT_LBUTTONDOWN:
        drawing = true;
        box = Rect(x, y, 0, 0);
        break;
    case EVENT_LBUTTONUP:
        drawing = false;
        if (box.width < 0) {
            box.x += box.width;
            box.width *= -1;
        }
        if (box.height < 0) {
            box.y += box.height;
            box.height *= -1;
        }
        draw_box(image, box);
        break;
    }
}

int main() {
    VideoCapture cap(1); // 1�� ī�޶� ����.
    if (!cap.isOpened()) {
        cout << "Could not open camera" << endl;
        return -1;
    }

    Mat frame, temp;
    namedWindow("Camera");
    namedWindow("Captured_image");
    setMouseCallback("Camera", onMouse, (void*)&frame);

    while (1) {
        cap >> frame;
        if (frame.empty()) break;

        frame.copyTo(temp);
        if (drawing) draw_box(temp, box);
        imshow("Camera", temp);

        if (box.width > 0 && box.height > 0) {
            Mat roi = frame(box);
            imshow("Captured_image", roi);
        }

        if (waitKey(1) == 27) break; // ESCŰ�� ������ ����
    }
    cap.release();
    return 0;
}