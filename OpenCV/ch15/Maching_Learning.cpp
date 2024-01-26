/* �ӽ� ���װ� OpenCV */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
using namespace cv::ml;

/* �ӽŷ����̶� �־��� �����͸� �м��Ͽ� ��Ģ��, ���� ���� ã��, �̸� �̿��Ͽ� �ǹ� �ִ� ������ �����ϴ� ����
   �����ͷκ��� ��Ģ�� ã�Ƴ��� ������ �н�(train) �Ǵ� �Ʒ��̶�� �ϰ�, �н��� ���� ������ ��Ģ�� ���̶�� �Ѵ�
   ���ο� �����͸� �н��� �𵨿� �Է����� �����ϰ� ����� �Ǵ��ϴ� ������ ���� �Ǵ� �߷��̶�� �Ѵ�.
   
   �ӽŷ����� �����н�(supervised learning)�� �������н�(unsupervised learning)���� ����
   �����н��� ������ �˰� �ִ� �����͸� �̿��Ͽ� �н��� �����ϴ� ���. 
   �̶� �Ʒ� �����Ϳ� ���� ���信 �ش��ϴ� ������ ���̺�(label)�̶�� �Ѵ�
   ���� ���, ����� �ٳ��������� �����Ϸ��� ������ ������ ����������� �ٳ������������� �˷��־�� �Ѵ�
   �� ���, �ӽŷ��� �˰������� ���� ���� ���� �� �ִ� ��Ģ�� ã�� ���� ������ �Ǵ� ������ ������ �����Ѵ� 
   
   ���� �����ʹ� �ȼ��� �����Ǿ� ������, �� �ȼ� ���� �״�� �ӽŷ��� �Է����� ����ϴ� ���� �״��� ��ġ ���� 
   ������ �ȼ� ���� ������ȭ, ��ü�� �̵� �� ȸ�� � ���� �ſ� �ΰ��ϰ� ��ȭ�ϱ� ����
   �׷��Ƿ� ���� �ӽŷ��� ���뿡���� ������ �پ��� ��ȯ���� ũ�� ������� �ʴ� Ư¡ ������ �����Ͽ� �ӽŷ��� �Է����� ����
   ���� �����͸� ����ϴ� �����н������� ���� �ټ��� �Ʒ� ���󿡼� Ư¡ ���͸� �����ϰ�, �̸� �̿��Ͽ� �ӽŷ��� �˰������� �н���Ŵ
   �н��� ����� ������ �н� ���� ���� ���� �������� ����
   ���� ���������� �Է� �������κ��� Ư¡ ���͸� �����ϰ�, �� Ư¡ ���͸� �н� �� �Է����� �����ϸ� �Է� ������ 
   � ���������� ���� ���� ����� ���� �� ����
   
   ���� �н��� �ַ� ȸ��(regression) �Ǵ� �з�(classification)�� ����
   ȸ�ʹ� ���ӵ� ��ġ ���� �����ϴ� �۾�. ���� ��� �л����� Ű�� �������� ������踦 �ӽŷ������� �н��ϰ�, 
   ���ο� �л��� Ű�� �Է����� �־��� �� �����Ը� �����ϴ� ���� ȸ����
   �з��� �̻����� ���� ����� ����ϴ� �ӽŷ���. ���� ��� ����� 0�� Ŭ����, �ٳ����� 1�� Ŭ������� �����ϰ�, 
   ���ο� ������ �ӽŷ��� �Է����� ������ ����� 0 or 1�� ������ �����ϴ� ���� �з��� 
   ��, �Է� ������ ������� �ٳ��������� �����ϴ� ���� �ν�(recognition)�̶���� �θ����� �ᱹ�� �з��� 
   
   ������ �н��� �Ʒ� �������� ���信 ���� ���� ���� ������ ������ ��ü���� �̿��ϴ� �н� ���
   ���� ���, �������� ���� �ִ� ����� �ٳ��� ������ �Է����� �����ϰ�, ��ü ������ �� ���� �׷����� �������� �н���Ű�� ���
   ���� ������ �����ϰ� �̿��Ͽ��� ��ü ������ ��� ������ �ٳ��� �������� ������ �� ���� ����
   �ٸ�, ������ �н��� ��� �и��� �� ���� ���� ������ ������ �ǹ��ϴ����� �� �� ����
   ����, �� ���� ���տ��� ���� ���еǴ� Ư¡�� �̿��Ͽ� ���� �и��ϴ� �۾��� ����
   ������ �н��� �ַ� ����ȭ(clustering)�� ����
   
   �ӽŷ����� �̿��Ͽ� �з��� ������ ���, �н��� �η� ���� �󸶳� ����� �����ϴ����� Ȯ���ؾ� �ϴ� ��찡 ����
   �н��� ���� ������ ���� �ʴٸ� �ٸ� �ӽŷ��� �˰������� �����ϰų� ���󿡼� �ٸ� Ư¡ ���͸� �����ϴ� ���� �����ؾ� ��
   �׷��Ƿ� ���� ����� ����� �� �ִ� ���� ������ ��ü�� �н��� ������� �ʰ�,
   �Ϻδ� ���� ������ ���� �׽�Ʈ �뵵�� ����ϱ⵵ ��. ���� ��� 1�� �� �ڷ�� 8000���� �н�, 2000���� �׽�Ʈ�� �����Ͽ� ��Ȯ���� ���
   
   �ӽŷ��� �˰����� ������ ���� ���������� ����ϴ� �Ķ���Ϳ� ���� ������ �޶���
   �׷��Ƿ� ������ �Ķ���͸� ã�� ���� �� �ϳ��� �ذ��ؾ� �� ����.
   �� ���, �Ʒ� �����͸� k���� �κ� �������� �����Ͽ� �н��� ����(vaildation)�� �ݺ��ϸ鼭 ������ �Ķ���͸� ã��
   ���� ���, 8000���� �Ʒ� ������ 800���� 10���� �κ� �������� �����ϰ�, �� �� 9���� �н��ϰ� ������ 1���� �̿��Ͽ� ������ ����
   �׸��� ������ ���� �κ� ���դ��� �ٲ� ���鼭 ���� �� �н��� ������ �����Ͽ� �پ��� �Ķ���Ϳ� ���� �����ϸ鼭 
   ���� ������ ���� ��Ÿ���� �Ķ���͸� ã�´�
   ��ó�� �Ʒ� �����͸� k���� �κ� �������� �����Ͽ� �н��� ������ �ݺ��ϴ� �۾��� k-���� ���� ����(k-fold cross-validation)�̶�� �� 
   
   �ӽŷ��� �˰��������� �Ʒ� �����͸� �н��� ��� �Ʒ� �����Ϳ� ���Ե� ���� �Ǵ� �̻�ġ�� ������ �����ؾ� ��
   ���� �ӽŷ��� �з� �˰������� �Ʒ� �����͸� ȿ�������� �����ϴ� ������ ã������ ��.
   ���� �Ʒ� �����Ϳ� �߸��� ������ ���� �ִٸ� ������ ��� �����ϴ� ���� ������ ��ȣ���� �� ���� */

/* OpenCV �ӽŷ��� Ŭ���� 
   OpenCV�� �پ��� �ӽŷ��� �˰������� Ŭ������ �����Ͽ� ����
   �ַ� ml��⿡ ���ԵǾ� �ְ�, cv::ml::StatModel �߻� Ŭ������ ��ӹ޾� �������
   StatModel Ŭ���� �̸��� ����� ��(Statistical Model)�� �ǹ�
   StatModel Ŭ������ �ӽŷ��� �˰������� �н���Ű�� StatModel::train() ����Լ��� �н��� ���� �̿��Ͽ�
   �׽�Ʈ �����Ϳ� ���� ����� �����ϴ� StatModel::predict()����Լ��� ������ ����
   StatModel Ŭ������ ��ӹ޾� ���� �ӽ� ���� ���� Ŭ������ ������ �ӽŷ��� �˰����� �ش��ϴ� train, predict����� �������ϰ� ������,
   ��� Ŭ������ �ڽŸ��� �н� �� ������ ���� ��� �Լ��� ���� �����ϱ⵵ ��
   
   StatModel::train(samples, layout, responses)�� �н��� �����ϴ� �Լ�
   1. �Ʒ� ������ ����. 2 �Ʒ� ������ ��ġ ���. ROW_SAMPLE or COL_SAMPLE�� ����
   3. �� �Ʒ� �����Ϳ� �����Ǵ� ����(���̺�)���. 4. ���������� �н��� �Ϸ�Ǹ� true�� ��ȯ 
   samples�� ����� �ټ��� �Ʒ� �����͸� ����Ͽ� �ӽŷ��� �˰������� �н�
   �Ʒ� �����Ϳ� ���� ���� �Ǵ� ���̺� ������ responses ���ڷ� ���޵�
   samples, responses�� MatŸ�� ��ü�� ������. Mat��Ŀ� �Ʒ� �����Ͱ� ��� ������� ����Ǿ� �ִ����� layout���ڷ� ����
   
   �̹� �н��� �𵨿� ���� �׽�Ʈ �������� ������ ��� ������ StatModel::predict()�Լ��� ���
   StatModel::predict(samples, results = noArray(), flags = 0)
   1. �Է� ���Ͱ� �� ������ ����� ���. CV_32F
   2. �� �Է� ���ÿ� ���� ���� ����� ����� ���
   3. �߰����� �÷��� ���. StatModel::Flags ������ ��� �� �ϳ��� ������ �� ������, �𵨿� ���� ������ �ٸ�
   4. ��ȯ���� �˰����� ���� �ٸ�
   StatModel::predict�Լ��� ���� ���� �Լ��� ����Ǿ� ������, ������ �ӽŷ��� �˰����� ���� Ŭ������ �ڽŸ��� �˰������� �̿���
   ������ �����ϵ��� predict�Լ��� �������ϰ� ����
   �Ϻ� �ӽ� ���� �˰����� ���� Ŭ������ predict�Լ��� ����� �� �ִ� ������ �����Լ��� �����ϱ⵵ ��
   
   OpenCV���� StatModelŬ������ ��ӹ޾� ������� �ӽŷ��� �˰����� ���� Ŭ������ ���� �̸��� �ǹ̿� ���� ǥ 477p ����.*/

/* K �ֱ��� �̿�(KNN = K-Nearest Neighbor) */
/* K �ֱ��� �̿� �˰������� �з� �Ǵ� ȸ�Ϳ� ���Ǵ� ���� �н� �˰������� �ϳ�
   KNN �˰������� �з��� ����� ���, Ư¡ �������� �׽�Ʈ �����Ϳ� ���� ����� k���� �Ʒ� �����͸� ã��,
   k���� �Ʒ� ������ �߿��� ���� ���� Ŭ������ �׽�Ʈ �������� Ŭ������ ����
   KNN �˰������� ȸ�� ������ ������ ��쿡�� �׽�Ʈ �����Ϳ� ������ k���� �Ʒ� ������ ����� �׽�Ʈ ������ ������ ����
   
   KNN �˰����� ���� ��� 479p�� ������ �� �Ǿ� ���� 
   KNN �˰����򿡼� k�� 1�� �����ϸ� �ֱ��� �̿� �˰������� ��
   �׷��Ƿ� ���� k�� 1���� ū ������ �����ϸ�, k���� ��� �����ϴ��Ŀ� ���� �з� �� ȸ�� ����� �޶��� �� ����
   �ּ��� k���� �����ϴ� ���� �־��� �����Ϳ� �������̸�, ���� k���� Ŀ������ ���� �Ǵ� �̻�ġ �������� ������ ����
   �׷��� k���� ��� ���� �̻����� Ŀ�� ��� ������ �з� �� ȸ�� ������ ������ �� ���� 
   
   KNN �˰������� KNearest Ŭ������ �����Ǿ� ����.
   KNearest Ŭ������ ml��⿡ ���ԵǾ� �ְ�, cv::ml ���ӽ����̽��� ���ǵǾ� ����. ����Ϸ��� ��ü ���� ����
   KNearest::create() ���. �ܼ��� ��� �ִ� KNearest ��ü�� �����ϸ� ��ȯ���� KNearest ��ü�� �����ϴ� Ptr<KNearest> ����Ʈ ������ ��ü 
   
   KNearest Ŭ������ �⺻������ k���� 10���� ����. �����Ϸ��� KNearest::setDefaultK�Լ��� �̿��Ͽ� ����
   StatModel::predict�Լ� ��� KNearest::findNearest�Լ��� �̿��Ͽ� �׽�Ʈ �������� ������ ���� ��쿡��
   k���� KNearest::findNearest�Լ� ���ڷ� ���������� ������ �� ����
   KNearest::setDefaultK(int val). val = KNN�˰����򿡼� ����� k��. StatModel::predict�� ����� ��� �̸� k���� �����ϰ� �����ؾ� ��
   KNearest ��ü�� �⺻������ �з��� ���� �뵵�� ������
   KNearest ��ü�� �з��� �ƴ� ȸ�Ϳ� �����Ϸ��� KNearest::setIsClassifier(bool val)�� false�� �����Ͽ� ȣ��
   true�̸� �з�, false�̸� ȸ�ͷ� ���
   
   KNearest ��ü�� �����ϰ� �Ӽ��� ������ �Ŀ��� StatModel::train�Լ��� �̿��Ͽ� �н��� ������ �� ����
   KNearest Ŭ������ ��쿡�� train�Լ����� �������� �н��� ����Ǵ� ������, �ܼ��� �Ʒ� �����Ϳ� ���̺� �����͸�
   KNearest Ŭ���� ��� ������ ��� �����ϴ� �۾��� �̷����
   
   KNearest Ŭ�������� �Ʒ� �����͸� �н��� ��, �׽�Ʈ �����Ϳ� ���� ������ ������ ������ �ַ� KNearest::findNearest�Լ��� ���
   KNearest Ŭ���������� StatModel::perdict�Լ��� ����� �� ������ KNearest::findNearest�Լ��� ���� ����� ���õ� ������ 
   �� ���� ��ȯ�ϱ� ������ ����
   KNearest::findNearest(samples, k, results, neighborResponses = noArray(), dist = noArray();)
   1. �׽�Ʈ ������ ���Ͱ� �� ������ ����� ���. �Է� ������ ������ �Ʒ� ������ ������ ���ƾ� �ϸ�  CV_32FC1�̾�� ��
   2. ����� �ֱ��� �̿� ����, 1���� ũ�ų� ���ƾ� �Ѵ�.
   3. �� �Է� ���ÿ� ���� ����(�з� �Ǵ� ȸ��)����� ������ ���. samples.rows x 1 ũ�⸦ ����, Ÿ���� CV_32FC1�̾�� ��
   4. ������ ���� k���� �ֱ��� �̿� Ŭ���� ������ ��� �ִ� ���. samples.rows x k ũ�⸦ ����, Ÿ���� CV_32FC1�̾�� ��
   5. �Է� ���Ϳ� ������ ���� k���� �ֱ��� �̿����� �Ÿ��� ������ ���. samples.rows x k ũ�⸦ ����, Ÿ���� CV_32FC1�̾�� ��
   6. ��ȯ�� = �Է� ���Ͱ� �ϳ��� ��쿡 ���� ������ ��ȯ�� 
   
   KNearest::findNearest�Լ��� samples��� �� �࿡ ����� �׽�Ʈ �����Ϳ� ����� k���� �Ʒ� �����͸� ã�� �з� �Ǵ� ȸ�� ������ ��ȯ
   samples ����� �� ������ ������ �׽�Ʈ ������ ������ ����, �� ������ �н� �� ����� �Ʒ� �������� ������ ���ƾ� ��
   �з� �� ȸ�� ����� ����Ǵ� results ����� samples ��İ� ���� �� ������ ������, �� ������ �׻� 1
   ��, samples ��Ŀ��� i��° �࿡ ���� ������ results ����� i��° �࿡ �����
   neighborResponses�� dist ���ڴ� KNN �˰����� ���� �� �߰����� ������ �޾ƿ��� �뵵�̸�, �ʿ����� ������ ���� ���� */

/* 2���� ��鿡�� 3���� Ŭ������ ������ ������ KNN �˰��������� �з��ϰ�, �� ������ ȭ�鿡 ǥ���ϴ� ���� ���α׷�
   (150, 150), (350, 150), (250, 400) ��ǥ�� �߽����� �ϴ� ����þ� ������ ���� ���� 30���� �����Ͽ� KNN�˰����� �Ʒ� �����ͷ� ���
   (0, 0)���� (499, 499)��ǥ ������ ��� ���� ���� KNN �з��� �����Ͽ� �� ����� RGB�� ��Ÿ��
   kNN�˰������� k���� Ʈ���ٸ� �̿��Ͽ� ���α׷� ���� �� ������ �� �ֵ��� �� */

#if 0
Mat img;
Mat train, label;
Ptr<KNearest> knn;
int k_value = 1;

void on_k_changed(int, void*);
void addPoint(const Point& pt, int cls);
void trainAndDisplay();

int main(void)
{
	img = Mat::zeros(Size(500, 500), CV_8UC3);
	knn = KNearest::create();

	const int NUM = 30;
	Mat rn(NUM, 2, CV_32SC1);

	/* (150, 150)��ǥ�� �߽����� �ϴ� 0�� Ŭ���� ��, (350, 150)��ǥ�� �߽����� �ϴ� 1�� Ŭ���� ��
	   (250, 400)��ǥ�� �߽����� �ϴ� 2�� Ŭ���� ���� ���� 30���� �����Ͽ� �Ʒ� �����Ϳ� �߰��Ѵ� 
	   0���� 1�� Ŭ���� ���� ������ �߽��� �������� ǥ�� ���� 50�� �ش��ϴ� ����þ� ������ ������,
	   2�� Ŭ���� ���� �߽��� �������� ǥ�� ���� 70�� �ش��ϴ� ����þ� ������ ������ 
	   �ڵ尡 ����Ǹ� train ����� 90 x 2 ũ���� ����� �ǰ�, label ����� 90 x 1 ũ���� ����� ��
	   train ����� 2���� ��鿡�� ���ǵ� ������ ��ǥ�� �����ϰ� ������, �� ������ ���� Ŭ���� ������ label ��Ŀ� ����Ǿ����� */
	randn(rn, 0, 50);
	for (int i = 0; i < NUM; i++)
		addPoint(Point(rn.at<int>(i, 0) + 150, rn.at<int>(i, 1) + 150), 0);

	randn(rn, 0, 50);
	for (int i = 0; i < NUM; i++)
		addPoint(Point(rn.at<int>(i, 0) + 350, rn.at<int>(i, 1) + 150), 1);

	randn(rn, 0, 70);
	for (int i = 0; i < NUM; i++)
		addPoint(Point(rn.at<int>(i, 0) + 250, rn.at<int>(i, 1) + 400), 2);

	/* KNN �̸��� â�� Ʈ���ٸ� �����ϰ�, Ʈ���ٰ� �����̸� on_k_changed �Լ��� ����ǵ��� �� */
	namedWindow("knn");
	createTrackbar("k", "knn", &k_value, 5, on_k_changed);

	/* ���α׷��� ó�� ������ڸ��� KNN�˰��������� �з��� ����� ���� �ֵ��� �Լ��� ȣ����
	   KNN�˰����� ���� �н��� img ���� ��� ��ǥ������ Ŭ���� �� ������ �����ϰ� �� ����� knnâ�� ǥ�� */
	trainAndDisplay();

	waitKey();
	return 0;
}

/* Ʈ���ٸ� �������� k���� �ٲ�� �ٽ� KNN�˰������� �н���Ű�� �� ����� ȭ�鿡 ��Ÿ���� */
void on_k_changed(int, void*)
{
	if (k_value < 1) k_value = 1;
	trainAndDisplay();
}
 /* addPoint�Լ��� Ư�� ��ǥ �� pt�� clsŬ������ ����Ѵ� */
void addPoint(const Point& pt, int cls)
{
	Mat new_sample = (Mat_<float>(1, 2) << pt.x, pt.y);
	train.push_back(new_sample);

	Mat new_label = (Mat_<int>(1, 1) << cls);
	label.push_back(new_label);
}

void trainAndDisplay()
{
	/* StatModel::train�Լ��� �̿��Ͽ� KNN�˰������� �н� */
	knn->train(train, ROW_SAMPLE, label);

	/* img ���� ��ü ��ǥ�� ���� KNN�з��� ������ �����Ͽ� RGB�� ǥ�� */
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			Mat sample = (Mat_<float>(1, 2) << j, i);

			Mat res;
			knn->findNearest(sample, k_value, res);

			int response = cvRound(res.at<float>(0, 0));
			if (response == 0)
				img.at<Vec3b>(i, j) = Vec3b(128, 128, 255); // R
			else if (response == 1)
				img.at<Vec3b>(i, j) = Vec3b(128, 255, 128); // G
			else if (response == 2)
				img.at<Vec3b>(i, j) = Vec3b(255, 128, 128); // B
		}
	}

	/* 149 ~ 166�࿡�� �߰��� �Ʒ� ������ �� ��ǥ�� ������ 5�� ���� ���� RGB�� ǥ��*/
	for (int i = 0; i < train.rows; i++)
	{
		int x = cvRound(train.at<float>(i, 0));
		int y = cvRound(train.at<float>(i, 1));
		int l = label.at<int>(i, 0);

		if (l == 0)
			circle(img, Point(x, y), 5, Scalar(0, 0, 128), -1, LINE_AA);
		else if (l == 1)
			circle(img, Point(x, y), 5, Scalar(0, 128, 0), -1, LINE_AA);
		else if (l == 2)
			circle(img, Point(x, y), 5, Scalar(128, 0, 0), -1, LINE_AA);
	}

	imshow("knn", img);
}
#endif

/* KNN�� �̿��� �ʱ�ü ���� �ν� */
/* �ӽŷ������� Ư�� ������ �ذ��Ϸ��� ���� ���� �Ʒ� �����Ͱ� �ʿ���
   digits.png ���� ���󿡴� 0 ~ 9������ �ʱ�ü ���ڰ� 5000�� ���� ����
   �� ������ �̿��Ͽ� �ӽŷ��� �˰������� �н���Ű���� ������ ���� ������ �κ� �������� �����Ͽ� �Ʒ� �����͸� �����ؾ���
   �ӽŷ������� ������ �ν� �Ǵ� �з��� ���, �������κ��� �ν� ������ ������ Ư¡ ���͸� �����Ͽ� �ӽŷ��� �Է����� ���
   �� �������� 20 x 20 ���� ���� �ȼ��� ��ü�� KNN �˰����� �Է����� ����ϰ��� (������ ���ڴ� 20 x 20 �ȼ� ũ����) 
   ���ڵ��� ��ü�� 20 x 20 �κ� ���� ���߾ӿ� ��ġ�� �ְ�, ���� ũ�⵵ ���� �����ϱ� ������ �ȼ����� �״�� ����ص�
   ����� �ν� ����� ���� �� ����
   �� ���� ���� ������ 20 x 20 �ȼ� ũ���̰�, �� �ȼ����� ��� �Ϸķ� �þ������ 1 x 400 ũ���� ��ķ� ��ȯ�� �� ����
   �ʱ�ü ���� �Ʒ� ������ �ϳ��� 400���� ���ڰ����� ǥ���ǰ�, �̴� 400���� ���������� �� ���� ����.
   ������ ���� ������ 1 x 400 ��ķ� �ٲٰ�, �� ����� ��� ���η� ������ ��ü ���� ���� �����͸� ǥ���ϴ� 5000 x 400 ũ���� ����� ��
   �� ����� KNearest Ŭ������ �Ʒ� �����ͷ� ����
   KNN�˰��������� ���� ������ �н���Ű���� �� �ʱ�ü ���� ������ ��Ÿ���� ���� ���� ���̺� ��ķ� �Բ� �����ؾ� ��
   ���̺� ����� �� ũ��� �Ʒ� ������ ���� ������ ����, �� ũ��� 1 
   �Ʒ� ������ ��Ŀ��� ó�� 500�� ���� ���� 0�� ���� ������, �� ���� 500�� ���� ���� 1�� ���� ��������
   �׷��Ƿ� ���̺� ��ĵ� ó�� 500�� �� ���Ҵ� 0���� ����, �� ���� 500�� ���� 1�� ����. 9���� ��� ������ ��,
   KNearest Ŭ������ ���̺� �����ͷ� ���� */

#if 0
Ptr<KNearest> train_knn();
void on_mouse(int event, int x, int y, int flags, void* userdata);

int main()
{
	Ptr<KNearest> knn = train_knn(); // train_knn�Լ��� �����Ͽ� �ʱ�ü ���ڸ� �н��� ����� knn�� ����

	if (knn.empty()) {
		cerr << "Training failed!" << endl;
		return -1;
	}

	Mat img = Mat::zeros(400, 400, CV_8U); // 400 x 400 ũ���� ���� img�� ����. img ���� ���콺�� �۾��� ���� ���ڸ� �ν��� ����

	imshow("img", img);
	setMouseCallback("img", on_mouse, (void*)&img);

	while (true) {
		int c = waitKey();

		if (c == 27) { // ESC ������ ����
			break;
		}
		else if (c == ' ') { // Ű���忡�� �����̽��ٸ� ������ �ʱ�ü ���� �ν��� ����
			Mat img_resize, img_float, img_flatten, res;

			resize(img, img_resize, Size(20, 20), 0, 0, INTER_AREA); // ���ڰ� ���� img������ 20 x 20 ũ��� ��ȯ�Ͽ� img_resize�� ����
			img_resize.convertTo(img_float, CV_32F); // img_resize ���� �ڷ����� float�� ��ȯ�Ͽ� img_float�� ����
			img_flatten = img_float.reshape(1, 1); // 20 x 20 img_float ������ 400 x 1 ũ���� �������� ��ȯ�Ͽ� img_flatten�� ����

			/* KNN�˰��������� �з��� ����� �ܼ� â�� ��� */
			knn->findNearest(img_flatten, 3, res);
			cout << cvRound(res.at<float>(0, 0)) << endl;

			/* img ������ ���������� �ʱ�ȭ�� �� ȭ�鿡 ��Ÿ�� */
			img.setTo(0);
			imshow("img", img);
		}
	}

	return 0;
}

Ptr<KNearest> train_knn()
{
	Mat digits = imread("digits.png", IMREAD_GRAYSCALE);

	if (digits.empty()) {
		cerr << "Image load failed!" << endl;
		return 0;
	}

	Mat train_images, train_labels;

	/* digits ���� ���� 100��, ���� 50���� �ʱ�ü ���ڰ� ���� �����Ƿ� for �ݺ��� ������ �����ϰ� ������ */
	for (int j = 0; j < 50; j++) {
		for (int i = 0; i < 100; i++) {
			Mat roi, roi_float, roi_flatten;
			roi = digits(Rect(i * 20, j * 20, 20, 20)); // ���� i, ���� j��° �ʱ�ü ���� ������ roi�� ����
			roi.convertTo(roi_float, CV_32F); // roi ���� �ڷ����� float�� ��ȯ�Ͽ� roi_float�� ����
			roi_flatten = roi_float.reshape(1, 1); // 20 x 20 roi_float ������ 400 x 1 ũ���� �������� ��ȯ�Ͽ� roi_flatten�� ����

			train_images.push_back(roi_flatten); // roi_flatten ������ train_images����� �� �Ʒ� ������ �߰�
			train_labels.push_back(j / 5); // train_labels ����� �� �Ʒ��� ���� �߰��� �ʱ�ü ���� ������ ����(���̺�)�� �߰�
		}
	}

	/* KNearest ��ü knn�� �����ϰ�, KNN�н��� ����.
	   knn->train�Լ� ���ڷ� ���Ǵ� train_images ��� ũ��� 5000 x 400�̰�. train_labels ��� ũ��� 5000 x 1 ��*/
	Ptr<KNearest> knn = KNearest::create();
	knn->train(train_images, ROW_SAMPLE, train_labels);

	return knn; // �н��� knn ����Ʈ �����͸� ��ȯ�� 
}

Point ptPrev(-1, -1);
/* ���콺 ���� ��ư�� ���� ���¿��� ���콺�� �����̸� �ش� ��ġ�� �β� 40�ȼ��� ��� �۾��� �� �� ���� */
void on_mouse(int event, int x, int y, int flags, void* userdata)
{
	Mat img = *(Mat*)userdata;

	/* ���콺 ���� ��ư�� ���� ��ġ�� ptPrev�� ������ */
	if (event == EVENT_LBUTTONDOWN) {
		ptPrev = Point(x, y);
	}
	else if (event == EVENT_LBUTTONUP) { // ���콺 ���� ��ư�� ���� ptPrev ��ǥ�� (-1, -1)�� �ʱ�ȭ��
		ptPrev = Point(-1, -1);
	}
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) { // ���콺 ���� ��ư�� ���� ���·� ���콺�� �����̸� 
		line(img, ptPrev, Point(x, y), Scalar::all(255), 40, LINE_AA, 0); // ptPrev��ǥ�κ��� (x ,y)��ǥ���� ������ �׸�
		ptPrev = Point(x, y); //�׸��� ptPrev ��ǥ�� (x, y)�� ������

		imshow("img", img);
	}
}
#endif