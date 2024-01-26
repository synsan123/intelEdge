/* ����Ʈ ���� �ӽ� */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
using namespace cv::ml;

/* ����Ʈ ���� �ӽ�(SVM, Support Vector Machine) */
/* �⺻������ 2���� Ŭ������ ������ �����͸� ���� ���� �ְ� �и��ϴ� ������� ã�� �ӽŷ��� �˰��� 
   ������̶� 2Ŭ������ �����͸� �и��ϴ� N���� �������� ����� �ǹ�
   SVM�˰����� ���� �н��� �����̸�, �з��� ȸ�Ϳ� ���� �� ���� 
   
   ����(margin)�� ������� �������� ���� ������ �ִ� ������ �Ÿ��� ���Ѵ�. 
   SVM�� �� ������ �ִ�� ����� ������� ���ϴ� �˰��� 
   
   SVM�˰����� �⺻������ �������� �и� ������ �����Ϳ� ������ �� ����
   �ǻ�Ȱ���� ����ϴ� �����ʹ� �������� �и����� �ʴ� ��찡 ������, SVM�˰����� �����ϱ� ���Ͽ� 
   SVM������ Ŀ�� Ʈ���̶�� ����� ���.
   Ŀ�� Ʈ���̶� ������ Ŀ�� �Լ��� �̿��Ͽ� �Է� ������ Ư¡ ���� ������ �ø��� ���
   ���� ������ ���������� �������� �и��� �� ������ �����͸� Ŀ�� Ʈ������ ������ Ư¡ �������� �̵��ϸ� �������� �и� ������ ���·� �ٲ�
   492p���� �� �����س���. 
   SVM�˰��򿡼� ����� �� �ִ� Ŀ�� �Լ� ������ 493p ����
   
   SVM�˰����� SVMŬ������ �����Ǿ�����. LIBSVM�� ������� �������. SVM::create�Լ��� �̿��Ͽ� ��ü�� ����
   ��ȯ���� SVM��ü�� �����ϴ� Ptr ����Ʈ ������ ��ü
   
   SVMŬ���� ��ü�� ������ ��, �Ʒ� �����͸� �н��ϱ� ���� ���� SVM�˰��� �Ӽ��� �����ؾ���.
   ��ǥ������ Ÿ�԰� Ŀ�� �Լ� ������ ����
   SVM::setType(int val)�Լ��� Ÿ���� ����. val = SVMŸ��. C_SVC, NU_SVC, ONE_CLASS, EPS_SVR, NU_SVR �� �ϳ� ���� (494p ����)
   C_SVCŸ���� �Ϲ����� N-Ŭ���� �з� �������� ���Ǵ� ���. 
   C_SVCŸ���� ����ϴ� ���, SVM�˰��� ���ο��� ����ϴ� C�Ķ���� ���� �����ϰ� �����ؾ���.
   C���� �۰� �����ϸ� �Ʒ� ������ �߿� �߸� �з��Ǵ� �����Ͱ� �־ �ִ� ������ ����
   C���� ũ�� �����ϸ� ������ �۾������� �߸� �з��Ǵ� �����Ͱ� ���������� �з�
   �Ʒ� ���� �����Ϳ� ���� �Ǵ� �̻�ġ �����Ͱ� ���� ���ԵǾ� �ִ� ��쿡�� C�Ķ���� ���� ���� ũ�� �����ϴ� ���� ���� 
   
   SVMŸ���� �����Ͽ�����, SVM�˰��򿡼� ����� Ŀ�� �Լ��� ����.
   SVM::setKernel(int kernelType)�Լ��� Ŀ�� �Լ��� ����. kernelType = Ŀ�� �Լ� ����. LINEAR, POLY, RBF, SIGMOID, CHI2, INTER �� �ϳ�
   
   Ÿ�԰� Ŀ�� �Լ��� ������ �Ŀ��� ������ Ÿ�԰� Ŀ�� �Լ� ���ǿ� �ʿ��� �Ķ���͸� �����ؾ���
   SVMŬ�������� ������ �� �ִ� �Ķ���ʹ� C, Nu, P, Degree, Gamma, Coef0 ���� ������,
   �̵� �Ķ���ʹ� ���ʴ�� 1, 0, 0, 0, 1, 0���� �ʱ�ȭ��
   ������ �Ķ���ʹ� �Ķ���� �̸��� �ش��ϴ� setXXX()�� getXXX()�Լ��� �̿��Ͽ� ���� �����ϰų� �о� �� �� ����
   ���� ���, C_SVCŸ���� ����ϰ� RBF Ŀ���� ����� ���, SVM::setC�� SVM::setGamma�Լ��� ����Ͽ� ������ �Ķ���� ���� ����
   
   SVM ��ü�� �����ϰ� Ÿ�԰� Ŀ���Լ� ����, �׸��� �Ķ���͸� ������ �Ŀ��� StatModel::train()�Լ��� �̿��Ͽ� �н���ų �� ����
   �׷��� SVM���� ����ϴ� �Ķ���͸� �����ϰ� �������� ������ �н��� ����� ���� �ʴ� ��찡 �߻���
   ��κ��� �Ʒ� �����ʹ� ������ �������� �پ��� ������ ���¸� ���� ������ SVM �Ķ���� ���� ��� �����ؾ� �н��� �� �� ��������
   ���������� �˱� �����.
   OpenCV�� SVMŬ������ ������ �Ķ���Ϳ� ���� ���� ������ ���� ������ ����, ���� ���� ������ ���� �Ķ���͸� �ڵ����� ã�� �н��ϴ�
   SVM::trainAuto()�Լ��� ����
   SVM::trainAuto(samples, layout, responses, kFold = 10, Cgrid, gammaGrid, pGrid, nuGrid, coeffGrid, degreeGrid, balanced = false)
   1. �Ʒ� ������ ��� 2. �Ʒ� ������ ��ġ ���. ROW_SAMPLE or COL_SAMPLE�� ����
   3. �� �Ʒ� �����Ϳ� �����Ǵ� ���� ���� 4. ���� ������ ���� �κ� ���� ����
   5 ~ 10. �� Ÿ���� Ž�� ����
   11. �� ���� true�̰� �� Ŭ���� �з� ������ ���, ��ü �Ʒ� ������ ������ ����Ͽ� �� �� ���� ���� ���� ���� �κ� ������ ����
   
   SVM::trainAuto()�Լ��� �پ��� �Ķ���� ���� �̿��Ͽ� ���� �� �н��� ������ �ݺ��� ��, ������ �Ķ���͸� �̿��Ͽ� �н��� �Ϸ� 
   �Ʒ� �����͸� kFold���� �κ� �������� �����ϰ� �� �� (kFold - 1)���� �κ� �������� �н��ϰ� ������ �� ���� �κ� �������� ������ �����ϴ�
   k-���� ���� ������ ����. ������ �Ķ���Ͱ� ���� �� �ִ� ���� ������ 5 ~ 10 Ÿ���� ���ڷ� ������ �� ������
   �̵� ������ Ÿ�� ParamGridŬ������ �Ķ���� ���� ���� �� �ִ� �ּڰ�, �ִ�, ���� �ܰ� ���� ǥ���ϴ� ������ ��.
   �ᱹ �پ��� �Ķ���͸� �̿��Ͽ� ���� ������ �����ϰ�, ���� ���� ������ ���� ��Ÿ���� �Ķ���͸� ã�� ����̱� ������ ���� �ð��� ���� �ɸ�
   SVM�н��� �Ϸ�Ǿ����� ���� �׽�Ʈ �����Ϳ� ���� ������ ������ �� ����. SVM::predict�Լ��� ����� 
   
   SVM::trainAuto�Լ��� �� �� ����� �Ŀ��� ���õ� �Ķ���͸� �����ߴٰ� �����ϴ� ���� ����
   ��, SVM::getXXX()�Լ��� �̿��Ͽ� ���� �Ķ���͸� �˾Ƴ� ��, ���� �� �н� �ÿ��� SVM::setXXX�Լ��� �̿��Ͽ� �Ķ���͸� ���� �����ϴ� ���
   (trainAuto�Լ��� �׳� ���� �ð��� �ʹ� �����ɸ��� ������)
   
   ���� �Ʒ� �����Ͱ� �����Ǿ� �ְ� �̹� trainAuto�Լ��� �н��� �Ϸ�Ǿ��ٸ� StatModel::save�Լ��� �̿��Ͽ� SVM�н� ����� ���� ���·� ����
   �׸��� ����� ������ �ٽ� SVM::load()�Լ��� �̿��Ͽ� �ҷ��� �� ����. ������ OpenCV���� ����Ʈ ���� */

#if 0
int main(void)
{
	/* 8���� �� ��ǥ�� �����ϴ� train ����� ����. train ����� CV_32FC1Ÿ���̸� ũ��� 8 x 2 */
	Mat train = Mat_<float>({ 8, 2 }, {
		150, 200, 200, 250, 100, 250, 150, 300, // �� 4��ǥ�� ������ 0�� Ŭ������ ����
		350, 100, 400, 200, 400, 300, 350, 400 }); // �Ʒ� 4��ǥ�� ������ 1�� Ŭ������ ����

	/* �Ʒ� ������ ������ Ŭ������ ������ label����� ����.
	   ó�� 4�� ���� Ŭ������ 0�̰�, ������ 4�� ���� Ŭ������ 1. label����� CV_32SC1Ÿ���̸� ũ��� 8 x 1 */
	Mat label = Mat_<int>({ 8, 1 }, { 0, 0, 0, 0, 1, 1, 1, 1 });

	Ptr<SVM> svm = SVM::create(); // SVM��ü�� �����Ͽ� svm�� ����
	svm->setType(SVM::C_SVC); // SVMŸ���� C_SVC�� ����
	svm->setKernel(SVM::LINEAR); // SVMĿ�� �Լ��� RBF�� ���� , LINEAR�� �����ϸ� �� ������ ���η� ����ϴ� ������ ������ ������� 
	svm->trainAuto(train, ROW_SAMPLE, label); // SVM::trainAuto() �Լ��� ����Ͽ� ������ �Ķ���� C�� gamma�� �ڵ����� ã�� �н�

	Mat img = Mat::zeros(Size(500, 500), CV_8UC3); // SVM �з� ����� ��Ÿ�� img ������ ���� 

	/* img ������ ��� �ȼ� ��ǥ�� ���� SVM ������ ���Ͽ� ������ �Ǵ� ������� ǥ���� */
	for (int j = 0; j < img.rows; j++) {
		for (int i = 0; i < img.cols; i++) {
			Mat test = Mat_<float>({ 1, 2 }, { (float)i, (float)j });
			int res = cvRound(svm->predict(test));

			if (res == 0)
				img.at<Vec3b>(j, i) = Vec3b(128, 128, 255); // R
			else
				img.at<Vec3b>(j, i) = Vec3b(128, 255, 128); // G
		}
	}

	/* train��Ŀ� ����� �Ʒ� ������ ���� ������ 5�� ������ ǥ��. 0�� Ŭ���� ���� ������ ��, 1�� Ŭ���� ���� ��� ������ �׸� */
	for (int i = 0; i < train.rows; i++) {
		int x = cvRound(train.at<float>(i, 0));
		int y = cvRound(train.at<float>(i, 1));
		int l = label.at<int>(i, 0);

		if (l == 0)
			circle(img, Point(x, y), 5, Scalar(0, 0, 128), -1, LINE_AA); // R
		else
			circle(img, Point(x, y), 5, Scalar(0, 128, 0), -1, LINE_AA); // G
	}

	imshow("svm", img);

	waitKey();
	return 0;
}
#endif

/* HOG & SVM �ʱ�ü ���� �ν� */
/* ������ ����� KNN�˰��� ��� SVM�˰����� ����Ͽ� �ʱ�ü ���� �ν��� ���� */

/* �� ���� ���󿡼� HOG Ư¡ ���͸� �����Ͽ� SVM�˰��� �Է� �����ͷ� ����� ���� 
   HOG�� ������ �׷����Ʈ ���� ������׷��� �̿��Ͽ� ���� Ư¡ 13.3������ �����߾��� 
   
   HOG�� �Է� ������ ���� ũ���� ���� ������, 2 x 2 ���� ���� �ϳ��� ������� ����
   �ʱ�ü ���� ���� �ϳ��� ũ��� 20 x 20�̹Ƿ� ���⼭ �� �ϳ��� ũ�⸦ 5 x 5�� �����ϰ�,
   ��� �ϳ��� ũ��� 10 x 10���� ����
   �� �ϳ����� �׷����Ʈ ���� ������׷��� 9���� ������ �����ϹǷ�, ��� �ϳ������� 9 x 4 = 36���� ������ ������ ������׷� ������ �����
   ���� ����� ���� �ϳ��� �� ������ �̵��ϹǷ� ���� 3��, ���η� 3�� ���� �� ����
   �׷��Ƿ� �ʱ�ü ���� ���� �ϳ����� ��������� HOG Ư¡ ������ ���� ũ��� 36 x 9 = 324�� ������
   ��, 20 x 20 ���� ���� �ϳ����� 1 x 324 Ư¡ ���� ����� ���������, �� ����� ��� ���η� ������ 5000 x 324ũ����
   HOG Ư¡ ���� ����� ���� �� ����. �׸��� �� ����� SVM Ŭ������ �Ʒ� �����ͷ� ���� 
   
   �ʱ�ü ���� ���󿡼� HOG Ư¡ ���͸� �����Ϸ��� HOGDescriptor Ŭ������ ���
   13.3������ ������ ����� ���.
   HOGDescriptor Ŭ������ ������ ���󿡼� HOG ����ڸ� �����ϴ� ��ɵ� ����
   ����ڸ� �����Ϸ��� ��ü ���� ����. �⺻ �����ڷ� ��ü ���� �� ������ ���� �� ����� ������ ������� ��ü�� ������
   20 x 20���󿡼� 5 x 5���� 10 x 10����� ����ϴ� HOG ����ڸ� �����Ϸ��� ������ �����ڸ� ����ؾ� ��
   HOGDescriptor(_winSize, _blockSize, _bloceStride, _cellSize, _nbins, _derivAperture = 1, _winSigma = -1,
                 _histogramNormType = HOGDescriptor::L2Hys, _L2HysThreshold = 0.2, _gammaCorrection = false,
				 _nlevels = HOGDescriptor::DEFAULT_NLEVELS, _signedGradient = false) 
   1. ���� ������ ũ�� 2. ��� ũ�� 3. ��� �̵� ũ�� 4. �� ũ�� 5. ������׷� �� ���� 6. ���� ������ ����
   7. ����þ� ���� ���� ǥ�� ���� 8. ���� ������ ���� 9. L2-Hys ����ȭ �Ӱ谪 10. ���� ���� ���� ����
   11. ���� ������ ���� �ִ� Ƚ��, �⺻���� 64 12. �׷����Ʈ ���� ��ȣ ��� ����
   �� �����ڴ� �ſ� ���� ���ڸ� �޵��� �Ǿ� ������, �޺κ��� ���� ���ڴ� �⺻���� �����Ǿ� ����
   �׷��Ƿ� 1 ~ 5���ڸ� �����ϰ� �����Ͽ� ����� �� ����

   20 x 20���󿡼� 5 x 5 ���� 10 x 10 ũ���� ����� ����ϰ�, �� ������ 9���� �׷����Ʈ ���� ������׷��� ���ϵ��� �����Ϸ���
   HOGDescriptor hog(Size(20, 20), Size(10, 10), Size(5, 5), Size(5, 5), 9);�� ��ü�� ����
   
   HOGDescriptor ��ü�� ������ �Ŀ��� HOGDescriptor::compute �Լ��� �̿��Ͽ� HOG ����ڸ� ����� �� ����
   HOGDescriptor::compute(img, descriptors, winStride = Size(), padding = Size(), locations = std::vector<Point>())
   1. �Է� ���� 2. ��� HOG �����. CV_32F 3. ������ �̵� ũ��, ��� �̵� ũ���� ����̾�� ��
   4. ���� �����ڸ� �е� ũ�� 5. ��� ���� ��ġ 
   �� �Լ��� ���� ���Ǵ� HOG����ڴ� descriptors ���Ϳ� ����Ǹ�, �� ���Ϳ� ����Ǵ� float ���� ������ 
   HOGDescriptor ��ü ���� �� ������ �� ũ��, ��� ũ��, ��� �̵� ũ�� � ���� �ڵ����� ������*/

Ptr<SVM> train_hog_svm(const HOGDescriptor& hog);
void on_mouse(int event, int x, int y, int flags, void* userdata);

int main()
{/* HOGDescriptorŬ���� �������� ������ svmdigits���α׷��� ����� ��忡�� ���� �� ���� �߻�. ����� ���� ������ ������ ���ڿ��� ��� �� ���� */
#if _DEBUG
	cout << "svmdigit.exe should be built as Relase mode!" << endl;
	return 0;
#endif

	HOGDescriptor hog(Size(20, 20), Size(10, 10), Size(5, 5), Size(5, 5), 9); // HOGDescriptor ��ü hog�� ����

	Ptr<SVM> svm = train_hog_svm(hog); // train_hog_svm�Լ��� �̿��Ͽ� SVM�� �н�

	if (svm.empty()) {
		cerr << "Training failed!" << endl;
		return -1;
	}

	Mat img = Mat::zeros(400, 400, CV_8U);

	imshow("img", img);
	setMouseCallback("img", on_mouse, (void*)&img);

	while (true) {
		int c = waitKey();

		if (c == 27) {
			break;
			/* img â���� spaceŰ�� ������ img ������ 20x20ũ��� ��ȯ�� �� HOG Ư¡ ���͸� ���
			   ���� HOG Ư¡ ���͸� 1 x 324 ũ���� ��ķ� ��ȯ�Ͽ� SVM����� �����ϰ�, �� ����� �ܼ� â�� ��� */
		}
		else if (c == ' ') {
			Mat img_resize;
			resize(img, img_resize, Size(20, 20), 0, 0, INTER_AREA);

			vector<float> desc;
			hog.compute(img_resize, desc);

			Mat desc_mat(desc);
			int res = cvRound(svm->predict(desc_mat.t()));
			cout << res << endl;

			img.setTo(0);
			imshow("img", img);
		}
	}

	return 0;
}

Ptr<SVM> train_hog_svm(const HOGDescriptor& hog)
{
	Mat digits = imread("digits.png", IMREAD_GRAYSCALE);

	if (digits.empty()) {
		cerr << "Image load failed!" << endl;
		return 0;
	}

	/* digits.png�� ���Ե� 5000���� �ʱ�ü ���� �κ� �������κ��� ���� HOG Ư¡ ���͸� �����Ͽ� 5000 x 324 ũ���� train_hog ��İ�
	   5000 x 1 ũ���� train_labels ����� ���� */
	Mat train_hog, train_labels;

	for (int j = 0; j < 50; j++) {
		for (int i = 0; i < 100; i++) {
			Mat roi = digits(Rect(i * 20, j * 20, 20, 20));

			vector<float> desc;
			hog.compute(roi, desc);

			Mat desc_mat(desc);
			train_hog.push_back(desc_mat.t());
			train_labels.push_back(j / 5);
		}
	}

	/* SVM ��ü�� ����
	   SVMŸ���� C_SVC, Ŀ�� �Լ��� RBF�� ����
	   �Ķ���� C�� Gamma���� ���� 2.5, 0.50625�� ����
	   SVM�н��� ���� */
	/* C�� Gamma �Ķ���� ���� SVM::trainAuto�Լ��� �̿��Ͽ� ���� ��
	   ��, svm->train�Լ� ȣ�� �ڵ� ��� ���� �ڵ带 �����ϰ�, �ܼ� â�� ��µǴ� C�� Gamma���� �ڵ忡 ����� �� 
	   svm->trainAuto(train_hog, ROW_SAMPLE, train_labels);
	   cout << "C : " << svm->getC() << endl; 
	   cout << "Gamma : " << svm->getGamma() << endl; */
	/* trainAuto��� �� ����� ���� �ð� ���� �н��� ����ǹǷ� ���� ���� ������ �Ķ���͸� �˾Ƴ� �Ŀ���
	   svm->trainAuto ��� svm->train�� ����ϴ� ���� ȿ���� */

	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::Types::C_SVC);
	svm->setKernel(SVM::KernelTypes::RBF);
	svm->setC(2.5);
	svm->setGamma(0.50625);
	svm->train(train_hog, ROW_SAMPLE, train_labels);

	return svm;
}

/* ���콺�� �̿��Ͽ� ���� ������ �׸� */
Point ptPrev(-1, -1);

void on_mouse(int event, int x, int y, int flags, void* userdata)
{
	Mat img = *(Mat*)userdata;

	if (event == EVENT_LBUTTONDOWN)
		ptPrev = Point(x, y);
	else if (event == EVENT_LBUTTONUP)
		ptPrev = Point(-1, -1);
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		line(img, ptPrev, Point(x, y), Scalar::all(255), 40, LINE_AA, 0);
		ptPrev = Point(x, y);

		imshow("img", img);
	}
}
