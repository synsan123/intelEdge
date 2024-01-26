/* HOG�˰���� ������ ���� */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* �ٶ��� Ʈ������ ��ǥ�� HOG�˰����� �̿��� ������ ���� ��ɿ� ���� ���� 
   HOG(Histograms of Oriented Gradients)�� �׷����Ʈ ���� ������׷��� �ǹ��� 
   ����� �� �ִ� ���󿡼� �׷����Ʈ�� ���ϰ�, �׷����Ʈ�� ũ��� ���� ������ �̿��Ͽ� ����� �� �ִ� ���¿� ���� Ư�� ���͸� ������. 
   �ӽ� ������ ������ ����Ʈ ���� �ӽ�(SVM)�˰����� �̿��Ͽ� �Է� ���󿡼� ������ ��ġ�� �����ϴ� ����� ����
   
   HOG�� �⺻������ 64 x 128 ũ���� ���󿡼� �����.
   HOG�� ���� �Է� �������κ��� �׷����Ʈ�� �����. �׷����Ʈ�� ũ��� ���� �������� ����ϸ�, ���⼺���� 0 ~ 180�������� ������ 
   �� ������ �Է� ������ 8 x 8 ũ�� ������ ����. ������ 8 x 8 �κ� ������ ��(cell)�̶�� �θ�
   ���� ���� 8��, ���� 16�� ������ ( 64 x 128 ���󿡼� )
   ������ ���κ��� �׷����Ʈ ���� ���п� ���� ������׷��� ���ϸ�, �̶� ���� ������ 20�� ������ �����ϸ� �� ��ȩ ���� ��(����)���� ������
   ���� ������׷��� �������
   �׸��� ������ 4���� ���� ���ļ� ���(block)�̶�� ������ 
   ��� �ϳ������� �� 36���� �Ǽ� ������ �̷���� ���� ������׷� ������ ����� ( 9�� �� x 4 = 36 ) 
   ����� ���ο� ���� �������� ���� �� ���� ����ŭ �̵��ϸ鼭 ������ 
   �׷��Ƿ� ����� ���� 7��, ���� 15���� ������ �� ���� ( 64 x 128 ���󿡼� )
   �ᱹ 105���� ����� ����� �� �ְ�, ��ü ��Ͽ��� ����Ǵ� ���� ������׷� �Ǽ� �� ����� 105 x 36 = 3780�� �� 
   3780���� �Ǽ� ���� HOG Ư¡ ���� ������ ��. 
   
   ������ �� �����ڰ� �ƴ� ���󿡼� HOG Ư¡ ���͸� ����. �� �� Ư¡ ���͸� �����ϱ� ���� SVM�˰����� ���
   SVM�� �� ���� Ŭ������ ȿ�������� �и��ϴ� �ɷ��� ���� �ӽ� ���� �˰��� 
   
   HOG �˰����� ������ HOGDescriptor Ŭ������ ������. �̿��Ϸ��� ���� ��ü�� �����ؾ� ��. 
   ������ ������ �����̶�� �⺻ �����ڸ� ����Ͽ� ��ü�� �����ϸ� ��.
   �׷��� ���� ���� ó�� ��, ���, �׷����Ʈ ���� ������׷�, 3780���� float�Ǽ��� ������
   
   HOGDescriptor::getDefaultPeopleDetector()�� �̸� ���� ������ ������ ���� HOG ����� ������ ��ȯ�ϴ� ���� ��� �Լ� 
   �ȹٷ� �� �ִ� ����� �����ϴ� �뵵�� �Ʒõ� �з��� ����� ��ȯ 
   ���� ��� �Լ��̱� ������ �ҽ��ڵ� �ۼ� �ÿ� Ŭ���� �̸��� �Բ� ����ؾ� ��.
   
   HOGDescriptor::setSVMDetector(svmdetector)�Լ��� ���� ����� ����ϸ� ��
   svmdetector�� ���� SVM �з��⸦ ���� ���
   
   HOG ����ڸ� �̿��Ͽ� ���� �Է� ���󿡼� ��ü ������ �����Ϸ��� HOGDescriptor::detectMultiScale()��� �Լ��� �����
   hog.detectMultiScale(frame, detected)������ ��� 
   detectMultiScale(img, foundLocations, foundWeights, hitThreshold = 0, winStride = Size(), padding = Size(), scale = 1.05, finalThreshold = 2.0, useMeanshiftGrouping = false)
   detectMultiScale(img, foundLocations, hitThreshold = 0, winStride = Size(), padding = Size(), scale = 1.05, finalThreshold = 2.0, useMeanshiftGrouping = false)
   foundLocations = ��� ����� �簢�� ���� ����, foundWeights = ��� ����� �簢�� ������ ���� �ŷڵ�
   hitThreshold = Ư¡ ���Ϳ� SVM �з� �������� �Ÿ��� ���� �Ӱ谪 
   winStride = �� ������ �̵� ũ��. Size() ���� �� �� ũ��� ���� ������ 
   padding = �е� ũ��, scale = �˻� ������ ũ�� Ȯ�� ����, finalThreshold = ���� ������ ���� �Ӱ谪 
   useMeanshiftGrouping = ������ �˻� �����츦 ��ġ�� ��� ���� �÷��� 
   �� �Լ��� �Է� ���� img���� �پ��� ũ���� ��ü �簢�� ������ �����ϰ�, �� ����� std::vector<Rect> Ÿ���� ���� foundLocations�� ���� */

/* ������ �� Release ��� ���.
   ���� ���귮�� �ʿ�� �ϱ� ������ Debug���� ���� */
int main()
{
	VideoCapture cap("people.mp4");

	if (!cap.isOpened()) {
		cerr << "Fail" << endl;
		return -1;
	}

	HOGDescriptor hog; // ��ü hog�� ����
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector()); // ������ ������ ���� �뵵�� �Ʒõ� SVM �з��� ����� �����

	Mat frame;
	while (true) {
		cap >> frame;
		if (frame.empty()) break;

		vector<Rect> detected; // ������ �� �����Ӹ��� ������ ������ ����. ����� �簢�� ������ detected ������ ������ 
		hog.detectMultiScale(frame, detected);

		for (Rect r : detected) { // ����� �簢�� ������ �̿��Ͽ� ������ �������� 3�ȼ� �β��� �簢���� �׸� 
			Scalar c = Scalar(rand() % 256, rand() % 256, rand() % 256);
			rectangle(frame, r, c, 3);
		}

		imshow("frame", frame);

		if (waitKey(10) == 27) break;
	}

	return 0;
}
