/* ĳ�����̵� �з���� �� ���� */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;


/* OPEN_CV���� �����ϴ� �� ���� ����� ĳ�����̵� �з��� �˰����� ������� �� 
   ��ö�-���� �� ���� �˰����� �⺻������ ������ 24 x 24 ũ��� ����ȭ�� ��, ����-�ϸ����� �������κ��� 
   Ư¡ ������ �����Ͽ� �� ���θ� �Ǻ��� 
   ����-�ϸ����Ͷ� ��� �簢���� ���� �پ� �ִ� ���·� ������ ����
   ����-�ϸ� ���� ���¿��� ��� ���� �ȼ� ���� ��� ���ϰ�, ������ ���� �ȼ� ���� ��� ���� �ϳ��� Ư¡ ���� ���� �� ���� 

   ����� ���� �� ���°� ���������� ���� ������ ��ο� ������ ������ �ֱ� ������ ����-�ϸ� ���ͷ� ���� Ư¡ ���� ���� �Ǻ��ϴ� �뵵�� ���
   �ð��� �����ɸ��ٴ� ������ ������ ���̴ٺν�Ʈ �˰���� ���� ������ �̿��Ͽ� �ذ��� 
   ���̴ٺν�Ʈ�� ������ ���� �߿��� �� ���⿡ ȿ������ ����-�ϸ� ���͸� �����ϴ� ������ ���� 
   �׷��� �Է� ���� ��ü���� �κ� ������ �����Ͽ� �˻��ؾ� �ϱ� ������ ������ ���귮�� �δ��� �� 
   
   ĳ�����̵� ������� ���ο� ����� �����Ͽ� ���� �ƴ� ������ ������ �ɷ� ���� ����� ��� 
   ��ö�-���� �˰����� �����Ͽ� ��ü�� �з��� �� �ִ� CascadeClassifier Ŭ������ ���� 
   ��ü�� �����Ϸ��� CascadeClaaifier ��ü�� �����ؾ� ��. 
   CascadeClassifier::load(filename)�� �̿��Ͽ� �з��� XML ������ �ҷ��� �� ���� 
   
   OPEN_CV�� �̸� �Ʒõ� �� ����, �� ���� ���� ���� �з��� XML���� ������ 
   %OPENCV_DIR%\etc\haarcascades �������� ã�� �� ����   413p ����
   
   CascadeClassifier classifier;
   classifier.load("haarcascade_fromtalface_default.xml); �Ǵ� 
   CascadeClassifier classifier("haarcascade_fromtalface_default.xml); ���� 
   
   ��ü ���� �Լ�
   CascadeClassifier.detectMultiScale(image, objects, scaleFactor, minNeighbors =3, flags = 0, minSize = Size(), maxSize = Size())
   object = ��� ����� ��ü�� �簢�� ��ǥ ����. vector<Rect> Ÿ�� , scaleFactor = �˻� ������ Ȯ�� ����. 1���� Ŀ�� �� 
   minNeighbors = ���� �������� �����ϱ� ���� �ּ� ���� Ƚ��, flags�� �Ⱦ�
   minSize �� maxSize = ������ ��ü�� �ּ� �ִ� ũ�� */

void detect_face()
{
	Mat src = imread("peopleMany.jpg");

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	/* ��ü�� �����԰� ���ÿ� ������ �ҷ��� */
	CascadeClassifier classifier("haarcascade_frontalface_default.xml");

	if (classifier.empty()) {
		cerr << "XML Fail" << endl;
		return;
	}

	/* src ���󿡼� ���� �����Ͽ� ����� �簢�� ������ faces�� ���� */
	vector<Rect> faces;
	classifier.detectMultiScale(src, faces);

	/* ����� �� ���� �簢���� src���� ���������� �׸� */
	for (Rect rc : faces) {
		rectangle(src, rc, Scalar(0, 0, 255), 2);
	}

	imshow("src", src);

	waitKey();
	destroyAllWindows();
}

void detect_eyes()
{
	Mat src = imread("mask.jpg");

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	/* ��ü�� �����԰� ���ÿ� ������ �ҷ��� */
	CascadeClassifier face_classifier("haarcascade_frontalface_default.xml");
	CascadeClassifier eye_classifier("haarcascade_eye.xml");

	if (face_classifier.empty() || eye_classifier.empty()) {
		cerr << "XML Fail" << endl;
		return;
	}

	/* src ���󿡼� ���� �����Ͽ� ����� �簢�� ������ faces�� ���� */
	vector<Rect> faces;
	face_classifier.detectMultiScale(src, faces);

	for (Rect face : faces) {
		rectangle(src, face, Scalar(0, 0, 255), 2);

		Mat faceROI = src(face); // �Է� ���󿡼� ������ �簢�� �� ������ �κ� ������ �����Ͽ� faceROI�� ����
		vector<Rect> eyes; // faceROI ���󿡼� ���� ������ 
		eye_classifier.detectMultiScale(faceROI, eyes);

		/* ������ ���� �߾ӿ� �Ķ��� ���� �׸�. faceROI ������ src ������ �κ� ������ �����ϹǷ� faceROI�� ���� �׸��� src���󿡵� ���� �׷��� */
		for (Rect eye : eyes) { 
			Point center(eye.x + eye.width / 2, eye.y + eye.height / 2);
			circle(faceROI, center, eye.width / 2, Scalar(255, 0, 0), 2, LINE_AA);
		}
	}
	imshow("src", src);

	waitKey();
	destroyAllWindows();
}


int main()
{
	//detect_face();
	detect_eyes();

	return 0;
}
