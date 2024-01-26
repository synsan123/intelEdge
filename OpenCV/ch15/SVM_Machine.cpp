/* 서포트 벡터 머신 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
using namespace cv::ml;

/* 서포트 벡터 머신(SVM, Support Vector Machine) */
/* 기본적으로 2개의 클래스로 구성된 데이터를 가장 여유 있게 분리하는 초평면을 찾는 머신러닝 알고리즘 
   초평면이란 2클래스의 데이터를 분리하는 N차원 공간상의 평면을 의미
   SVM알고리즘은 지도 학습의 일종이며, 분류와 회귀에 사용될 수 있음 
   
   마진(margin)은 초평면을 기준으로 가장 가까이 있는 점과의 거리를 말한다. 
   SVM은 이 마진을 최대로 만드는 초평면을 구하는 알고리즘 
   
   SVM알고리즘은 기본적으로 선형으로 분리 가능한 데이터에 적용할 수 있음
   실생활에서 사용하는 데이터는 선형으로 분리되지 않는 경우가 많으며, SVM알고리즘을 적용하기 위하여 
   SVM에서는 커널 트릭이라는 기법을 사용.
   커널 트릭이란 적절한 커널 함수를 이용하여 입력 데이터 특징 공간 차원을 늘리는 방식
   원본 데이터 차원에서는 선형으로 분리할 수 없었던 데이터를 커널 트릭으로 고차원 특징 공간으로 이동하면 선형으로 분리 가능한 형태로 바뀜
   492p에서 잘 설명해놓음. 
   SVM알고리즘에서 사용할 수 있는 커널 함수 종류는 493p 참고
   
   SVM알고리즘은 SVM클래스에 구현되어있음. LIBSVM을 기반으로 만들어짐. SVM::create함수를 이용하여 객체를 생성
   반환값은 SVM객체를 참조하는 Ptr 스마트 포인터 객체
   
   SVM클래스 객체를 생성한 후, 훈련 데이터를 학습하기 전에 먼저 SVM알고리즘 속성을 설정해야함.
   대표적으로 타입과 커널 함수 선택이 있음
   SVM::setType(int val)함수로 타입을 설정. val = SVM타입. C_SVC, NU_SVC, ONE_CLASS, EPS_SVR, NU_SVR 중 하나 지정 (494p 참고)
   C_SVC타입은 일반적인 N-클래스 분류 문제에서 사용되는 방식. 
   C_SVC타입을 사용하는 경우, SVM알고리즘 내부에서 사용하는 C파라미터 값을 적절하게 설정해야함.
   C값을 작게 설정하면 훈련 데이터 중에 잘못 분류되는 데이터가 있어도 최대 마진을 선택
   C값을 크게 설정하면 마진이 작아지더라도 잘못 분류되는 데이터가 적어지도록 분류
   훈련 샘플 데이터에 잡음 또는 이상치 데이터가 많이 포함되어 있는 경우에는 C파라미터 값을 조금 크게 설정하는 것이 유리 
   
   SVM타입을 설정하였으면, SVM알고리즘에서 사용할 커널 함수를 지정.
   SVM::setKernel(int kernelType)함수로 커널 함수를 지정. kernelType = 커널 함수 종류. LINEAR, POLY, RBF, SIGMOID, CHI2, INTER 중 하나
   
   타입과 커널 함수를 설정한 후에는 각각의 타입과 커널 함수 정의에 필요한 파라미터를 설정해야함
   SVM클래스에서 설정할 수 있는 파라미터는 C, Nu, P, Degree, Gamma, Coef0 등이 있으며,
   이들 파라미터는 차례대로 1, 0, 0, 0, 1, 0으로 초기화됨
   각각의 파라미터는 파라미터 이름에 해당하는 setXXX()와 getXXX()함수를 이용하여 값을 설정하거나 읽어 올 수 있음
   예를 들어, C_SVC타입을 사용하고 RBF 커널을 사용할 경우, SVM::setC와 SVM::setGamma함수를 사용하여 적절한 파라미터 값을 설정
   
   SVM 객체를 생성하고 타입과 커널함수 선택, 그리고 파라미터를 설정한 후에는 StatModel::train()함수를 이용하여 학습시킬 수 있음
   그러나 SVM에서 사용하는 파라미터를 적절하게 설정하지 않으면 학습이 제대로 되지 않는 경우가 발생함
   대부분의 훈련 데이터는 다차원 공간에서 다양한 분포와 형태를 갖기 때문에 SVM 파라미터 값을 어떻게 설정해야 학습이 잘 될 것인지를
   직관적으로 알기 어려움.
   OpenCV의 SVM클래스는 각각의 파라미터에 대해 설정 가능한 값을 적용해 보고, 그중 가장 성능이 좋은 파라미터를 자동으로 찾아 학습하는
   SVM::trainAuto()함수를 제공
   SVM::trainAuto(samples, layout, responses, kFold = 10, Cgrid, gammaGrid, pGrid, nuGrid, coeffGrid, degreeGrid, balanced = false)
   1. 훈련 데이터 행렬 2. 훈련 데이터 배치 방법. ROW_SAMPLE or COL_SAMPLE을 지정
   3. 각 훈련 데이터에 대응되는 응답 벡터 4. 교차 검증을 위한 부분 집합 개수
   5 ~ 10. 각 타입의 탐색 범위
   11. 이 값이 true이고 투 클래스 분류 문제인 경우, 전체 훈련 데이터 비율을 고려하여 좀 더 균형 잡힌 교차 검증 부분 집합을 생성
   
   SVM::trainAuto()함수는 다양한 파라미터 값을 이용하여 여러 번 학습과 검증을 반복한 후, 최적의 파라미터를 이용하여 학습을 완료 
   훈련 데이터를 kFold개의 부분 집합으로 분할하고 이 중 (kFold - 1)개의 부분 집합으로 학습하고 나머지 한 개의 부분 집합으로 성능을 검증하는
   k-폴드 교차 검증을 수행. 각각의 파라미터가 가질 수 있는 값의 범위는 5 ~ 10 타입의 인자로 지정할 수 있으며
   이들 인자의 타입 ParamGrid클래스는 파라미터 값이 가질 수 있는 최솟값, 최댓값, 증가 단계 등을 표현하는 역할을 함.
   결국 다양한 파라미터를 이용하여 많은 검증을 수행하고, 그중 가장 성능이 좋게 나타나는 파라미터를 찾는 방식이기 때문에 실행 시간은 오래 걸림
   SVM학습이 완료되었으면 이제 테스트 데이터에 대한 예측을 수행할 수 있음. SVM::predict함수를 사용함 
   
   SVM::trainAuto함수를 한 번 사용한 후에는 선택된 파라미터를 저장했다가 재사용하는 것이 좋음
   즉, SVM::getXXX()함수를 이용하여 사용된 파라미터를 알아낸 후, 다음 번 학습 시에는 SVM::setXXX함수를 이용하여 파라미터를 직접 지정하는 방식
   (trainAuto함수를 그냥 쓰면 시간이 너무 오래걸리기 때문에)
   
   만약 훈련 데이터가 고정되어 있고 이미 trainAuto함수로 학습이 완료되었다면 StatModel::save함수를 이용하여 SVM학습 결과를 파일 형태로 저장
   그리고 저장된 파일은 다시 SVM::load()함수를 이용하여 불러올 수 있음. 사용법은 OpenCV문서 사이트 참고 */

#if 0
int main(void)
{
	/* 8개의 점 좌표를 포함하는 train 행렬을 생성. train 행렬은 CV_32FC1타입이며 크기는 8 x 2 */
	Mat train = Mat_<float>({ 8, 2 }, {
		150, 200, 200, 250, 100, 250, 150, 300, // 위 4좌표의 점들을 0번 클래스로 정의
		350, 100, 400, 200, 400, 300, 350, 400 }); // 아래 4좌표의 점들을 1번 클래스로 정의

	/* 훈련 데이터 점들의 클래스를 정의한 label행렬을 생성.
	   처음 4개 점의 클래스는 0이고, 나머지 4개 점의 클래스는 1. label행렬은 CV_32SC1타입이며 크기는 8 x 1 */
	Mat label = Mat_<int>({ 8, 1 }, { 0, 0, 0, 0, 1, 1, 1, 1 });

	Ptr<SVM> svm = SVM::create(); // SVM객체를 생성하여 svm에 저장
	svm->setType(SVM::C_SVC); // SVM타입을 C_SVC로 설정
	svm->setKernel(SVM::LINEAR); // SVM커널 함수를 RBF로 설정 , LINEAR로 변경하면 두 점들을 세로로 양분하는 형태의 경계면이 만들어짐 
	svm->trainAuto(train, ROW_SAMPLE, label); // SVM::trainAuto() 함수를 사용하여 최적의 파라미터 C와 gamma를 자동으로 찾아 학습

	Mat img = Mat::zeros(Size(500, 500), CV_8UC3); // SVM 분류 결과를 나타낼 img 영상을 생성 

	/* img 영상의 모든 픽셀 좌표에 대해 SVM 응답을 구하여 빨간색 또는 녹색으로 표현함 */
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

	/* train행렬에 저장된 훈련 데이터 점을 반지름 5인 원으로 표시. 0번 클래스 점은 빨간색 원, 1번 클래스 점은 녹색 원으로 그림 */
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

/* HOG & SVM 필기체 숫자 인식 */
/* 이전에 사용한 KNN알고리즘 대신 SVM알고리즘을 사용하여 필기체 숫자 인식을 만듬 */

/* 각 숫자 영상에서 HOG 특징 벡터를 추출하여 SVM알고리즘 입력 데이터로 사용할 것임 
   HOG는 영상의 그래디언트 방향 히스토그램을 이용하여 만든 특징 13.3절에서 설명했었음 
   
   HOG는 입력 영상을 일정 크기의 셀로 나누고, 2 x 2 셀을 합쳐 하나의 블록으로 설정
   필기체 숫자 영상 하나의 크기는 20 x 20이므로 여기서 셀 하나의 크기를 5 x 5로 지정하고,
   블록 하나의 크기는 10 x 10으로 설정
   셀 하나에서 그래디언트 방향 히스토그램은 9개의 빈으로 구성하므로, 블록 하나에서는 9 x 4 = 36개의 빈으로 구성된 히스토그램 정보가 추출됨
   또한 블록은 보통 하나의 셀 단위로 이동하므로 가로 3개, 세로로 3개 만들 수 있음
   그러므로 필기체 숫자 영상 하나에서 만들어지는 HOG 특징 벡터의 차원 크기는 36 x 9 = 324로 결정됨
   즉, 20 x 20 숫자 영상 하나에서 1 x 324 특징 벡터 행렬이 만들어지고, 이 행렬을 모두 세로로 쌓으면 5000 x 324크기의
   HOG 특징 벡터 행렬을 만들 수 있음. 그리고 이 행렬을 SVM 클래스의 훈련 데이터로 전달 
   
   필기체 숫자 영상에서 HOG 특징 벡터를 추출하려면 HOGDescriptor 클래스를 사용
   13.3에서는 보행자 검출로 사용.
   HOGDescriptor 클래스는 임의의 영상에서 HOG 기술자를 추출하는 기능도 제공
   기술자를 추출하려면 객체 먼저 생성. 기본 생성자로 객체 생성 시 보행자 검출 시 사용한 설정을 기반으로 객체가 생성됨
   20 x 20영상에서 5 x 5셀과 10 x 10블록을 사용하는 HOG 기술자를 생성하려면 다음의 생성자를 사용해야 함
   HOGDescriptor(_winSize, _blockSize, _bloceStride, _cellSize, _nbins, _derivAperture = 1, _winSigma = -1,
                 _histogramNormType = HOGDescriptor::L2Hys, _L2HysThreshold = 0.2, _gammaCorrection = false,
				 _nlevels = HOGDescriptor::DEFAULT_NLEVELS, _signedGradient = false) 
   1. 검출 윈도우 크기 2. 블록 크기 3. 블록 이동 크기 4. 셀 크기 5. 히스토그램 빈 개수 6. 현재 사용되지 않음
   7. 가우시안 블러를 위한 표준 편차 8. 현재 사용되지 않음 9. L2-Hys 정규화 임계값 10. 감마 보정 수행 여부
   11. 검출 윈도우 증가 최대 횟수, 기본값은 64 12. 그래디언트 방향 부호 사용 여부
   이 생성자는 매우 많은 인자를 받도록 되어 있지만, 뒷부분의 많은 인자는 기본값이 설정되어 있음
   그러므로 1 ~ 5인자만 적절하게 지정하여 사용할 수 있음

   20 x 20영상에서 5 x 5 셀과 10 x 10 크기의 블록을 사용하고, 각 셀마다 9개의 그래디언트 방향 히스토그램을 구하도록 설정하려면
   HOGDescriptor hog(Size(20, 20), Size(10, 10), Size(5, 5), Size(5, 5), 9);로 객체를 생성
   
   HOGDescriptor 객체를 생성한 후에는 HOGDescriptor::compute 함수를 이용하여 HOG 기술자를 계산할 수 있음
   HOGDescriptor::compute(img, descriptors, winStride = Size(), padding = Size(), locations = std::vector<Point>())
   1. 입력 영상 2. 출력 HOG 기술자. CV_32F 3. 윈도우 이동 크기, 블록 이동 크기의 배수이어야 함
   4. 영상 가장자리 패딩 크기 5. 계산 시작 위치 
   이 함수에 의해 계산되는 HOG기술자는 descriptors 벡터에 저장되며, 이 벡터에 저장되는 float 값의 개수는 
   HOGDescriptor 객체 생성 시 설정한 셀 크기, 블록 크기, 블록 이동 크기 등에 의해 자동으로 결정됨*/

Ptr<SVM> train_hog_svm(const HOGDescriptor& hog);
void on_mouse(int event, int x, int y, int flags, void* userdata);

int main()
{/* HOGDescriptor클래스 구현상의 문제로 svmdigits프로그램은 디버그 모드에서 실행 시 에러 발생. 디버그 모드로 실행할 때에는 문자열을 출력 후 종료 */
#if _DEBUG
	cout << "svmdigit.exe should be built as Relase mode!" << endl;
	return 0;
#endif

	HOGDescriptor hog(Size(20, 20), Size(10, 10), Size(5, 5), Size(5, 5), 9); // HOGDescriptor 객체 hog를 생성

	Ptr<SVM> svm = train_hog_svm(hog); // train_hog_svm함수를 이용하여 SVM을 학습

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
			/* img 창에서 space키를 누르면 img 영상을 20x20크기로 변환한 후 HOG 특징 벡터를 계산
			   계산된 HOG 특징 벡터를 1 x 324 크기의 행렬로 변환하여 SVM결과를 예측하고, 그 결과를 콘솔 창에 출력 */
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

	/* digits.png에 포함된 5000개의 필기체 숫자 부분 영상으로부터 각각 HOG 특징 벡터를 추출하여 5000 x 324 크기의 train_hog 행렬과
	   5000 x 1 크기의 train_labels 행렬을 생성 */
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

	/* SVM 객체를 생성
	   SVM타입은 C_SVC, 커널 함수는 RBF로 설정
	   파라미터 C와 Gamma값을 각각 2.5, 0.50625로 설정
	   SVM학습을 진행 */
	/* C와 Gamma 파라미터 값은 SVM::trainAuto함수르 이용하여 구한 값
	   즉, svm->train함수 호출 코드 대신 다음 코드를 실행하고, 콘솔 창에 출력되는 C와 Gamma값을 코드에 사용한 것 
	   svm->trainAuto(train_hog, ROW_SAMPLE, train_labels);
	   cout << "C : " << svm->getC() << endl; 
	   cout << "Gamma : " << svm->getGamma() << endl; */
	/* trainAuto사용 시 상당히 오랜 시간 동안 학습이 진행되므로 위와 같이 최적의 파라미터를 알아낸 후에는
	   svm->trainAuto 대신 svm->train을 사용하는 것이 효율적 */

	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::Types::C_SVC);
	svm->setKernel(SVM::KernelTypes::RBF);
	svm->setC(2.5);
	svm->setGamma(0.50625);
	svm->train(train_hog, ROW_SAMPLE, train_labels);

	return svm;
}

/* 마우스를 이용하여 숫자 영상을 그림 */
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
