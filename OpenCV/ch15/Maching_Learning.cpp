/* 머신 러닝과 OpenCV */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
using namespace cv::ml;

/* 머신러닝이란 주어진 데이터를 분석하여 규칙성, 패턴 등을 찾고, 이를 이용하여 의미 있는 정보를 추출하는 과정
   데이터로부터 규칙을 찾아내는 과정을 학습(train) 또는 훈련이라고 하고, 학습에 의해 결정된 규칙을 모델이라고 한다
   새로운 데이터를 학습된 모델에 입력으로 전달하고 결과를 판단하는 과정을 예측 또는 추론이라고 한다.
   
   머신러닝은 지도학습(supervised learning)과 비지도학습(unsupervised learning)으로 구분
   지도학습은 정답을 알고 있는 데이터를 이용하여 학습을 진행하는 방식. 
   이때 훈련 데이터에 대한 정답에 해당하는 내용을 레이블(label)이라고 한다
   예를 들어, 사과와 바나나인지를 구분하려면 각각의 사진이 사과사진인지 바나나사진인지를 알려주어야 한다
   이 경우, 머신러닝 알고리즘은 둘을 구분 지을 수 있는 규칙을 찾기 위해 수학적 또는 논리적 연산을 수행한다 
   
   영상 데이터는 픽셀로 구성되어 있지만, 이 픽셀 값을 그대로 머신러닝 입력으로 사용하는 것은 그다지 흔치 않음 
   영상의 픽셀 값은 조명변화, 객체의 이동 및 회전 등에 의해 매우 민감하게 변화하기 때문
   그러므로 많은 머신러닝 응용에서는 영상의 다양한 변환에도 크게 변경되지 않는 특징 정보를 추출하여 머신러닝 입력으로 전달
   영상 데이터를 사용하는 지도학습에서는 먼저 다수의 훈련 영상에서 특징 벡터를 추출하고, 이를 이용하여 머신러닝 알고리즘을 학습시킴
   학습의 결과로 생성된 학습 모델은 이후 예측 과정에서 사용됨
   예측 과정에서도 입력 영상으로부터 특징 벡터를 추출하고, 이 특징 벡터를 학습 모델 입력으로 전달하면 입력 영상이 
   어떤 영상인지에 대한 예측 결과를 얻을 수 있음
   
   지도 학습은 주로 회귀(regression) 또는 분류(classification)에 사용됨
   회귀는 연속된 수치 값을 예측하는 작업. 예를 들어 학생들의 키와 몸무게의 상관관계를 머신러닝으로 학습하고, 
   새로운 학생의 키를 입력으로 주었을 때 몸무게를 예측하는 것은 회귀임
   분류는 이산적인 값을 결과로 출력하는 머신러닝. 예를 들어 사과를 0번 클래스, 바나나를 1번 클래스라고 설정하고, 
   새로운 사진이 머신러닝 입력으로 들어오면 결과를 0 or 1로 나오게 설정하는 것은 분류임 
   즉, 입력 영상이 사과인지 바나나인지를 구분하는 것을 인식(recognition)이라고도 부르지만 결국은 분류임 
   
   비지도 학습은 훈련 데이터의 정답에 대한 정보 없이 오로지 데이터 자체만을 이용하는 학습 방식
   예를 들어, 무작위로 섞여 있는 사과와 바나나 사진을 입력으로 전달하고, 전체 사진을 두 개의 그룹으로 나누도록 학습시키는 방식
   색상 정보만 적절하게 이용하여도 전체 사진을 사과 사진과 바나나 사진으로 구분할 수 있을 것임
   다만, 비지도 학습의 경우 분리된 두 개의 사진 집합이 무엇을 의미하는지는 알 수 없음
   단지, 두 사진 집합에서 서로 구분되는 특징을 이용하여 서로 분리하는 작업만 수행
   비지도 학습은 주로 군집화(clustering)에 사용됨
   
   머신러닝을 이용하여 분류를 수행할 경우, 학습된 부류 모델이 얼마나 제대로 동작하는지를 확인해야 하는 경우가 있음
   학습된 모델의 성능이 좋지 않다면 다른 머신러닝 알고리즘을 선택하거나 영상에서 다른 특징 벡터를 추출하는 것을 고려해야 함
   그러므로 많은 사람이 사용할 수 있는 영상 데이터 전체를 학습에 사용하지 않고,
   일부는 성능 측정을 위한 테스트 용도로 사용하기도 함. 예를 들어 1만 개 자료는 8000개는 학습, 2000개는 테스트를 수행하여 정확도를 계산
   
   머신러닝 알고리즘 종류에 따라서 내부적으로 사용하는 파라미터에 의해 성능이 달라짐
   그러므로 최적의 파라미터를 찾는 것이 또 하나의 해결해야 할 문제.
   이 경우, 훈련 데이터를 k개의 부분 집합으로 분할하여 학습과 검증(vaildation)을 반복하면서 최적의 파라미터를 찾음
   예를 들어, 8000개의 훈련 영상을 800개씩 10개의 부분 집합으로 분할하고, 이 중 9개는 학습하고 나머지 1개를 이용하여 성능을 검증
   그리고 검증을 위한 부분 집합ㅇ르 바꿔 가면서 여러 번 학습과 검증을 수행하여 다양한 파라미터에 대해 수행하면서 
   가장 성능이 높게 나타나는 파라미터를 찾는다
   이처럼 훈련 데이터를 k개의 부분 집합으로 분할하여 학습과 검증을 반복하는 작업을 k-폴드 교차 검증(k-fold cross-validation)이라고 함 
   
   머신러닝 알고리즘으로 훈련 데이터를 학습할 경우 훈련 데이터에 포함된 잡음 또는 이상치의 영향을 고려해야 함
   많은 머신러닝 분류 알고리즘이 훈련 데이터를 효과적으로 구분하는 경계면을 찾으려고 함.
   만약 훈련 데이터에 잘못된 정보가 섞여 있다면 경계면을 어떻게 설정하는 것이 좋은지 모호해질 수 있음 */

/* OpenCV 머신러닝 클래스 
   OpenCV는 다양한 머신러닝 알고리즘을 클래스로 구현하여 제공
   주로 ml모듈에 포함되어 있고, cv::ml::StatModel 추상 클래스를 상속받아 만들어짐
   StatModel 클래스 이름은 통계적 모델(Statistical Model)을 의미
   StatModel 클래스는 머신러닝 알고리즘을 학습시키는 StatModel::train() 멤버함수와 학습된 모델을 이용하여
   테스트 데이터에 대한 결과를 예측하는 StatModel::predict()멤버함수를 가지고 있음
   StatModel 클래스를 상속받아 만든 머신 러닝 구현 클래스는 각각의 머신러닝 알고리즘에 해당하는 train, predict기능을 재정의하고 있으며,
   몇몇 클래스는 자신만의 학습 및 예측을 위한 멤버 함수를 따로 제공하기도 함
   
   StatModel::train(samples, layout, responses)은 학습을 수행하는 함수
   1. 훈련 데이터 정렬. 2 훈련 데이터 배치 방법. ROW_SAMPLE or COL_SAMPLE을 지정
   3. 각 훈련 데이터에 대응되는 응답(레이블)행렬. 4. 정상적으로 학습이 완료되면 true를 반환 
   samples에 저장된 다수의 훈련 데이터를 사용하여 머신러닝 알고리즘을 학습
   훈련 데이터에 대한 정답 또는 레이블 정보는 responses 인자로 전달됨
   samples, responses는 Mat타입 객체로 전달함. Mat행렬에 훈련 데이터가 어떠한 방식으로 저장되어 있는지를 layout인자로 설정
   
   이미 학습된 모델에 대해 테스트 데이터의 응답을 얻고 싶으면 StatModel::predict()함수를 사용
   StatModel::predict(samples, results = noArray(), flags = 0)
   1. 입력 벡터가 행 단위로 저장된 행렬. CV_32F
   2. 각 입력 샘플에 대한 예측 결과가 저장된 행렬
   3. 추가적인 플래그 상수. StatModel::Flags 열거형 상수 중 하나를 지정할 수 있으며, 모델에 따라 사용법이 다름
   4. 반환값은 알고리즘에 따라 다름
   StatModel::predict함수는 순수 가상 함수로 선언되어 있으며, 각각의 머신러닝 알고리즘 구현 클래스는 자신만의 알고리즘을 이용한
   예측을 수행하도록 predict함수를 재정의하고 있음
   일부 머신 러닝 알고리즘 구현 클래스는 predict함수를 대신할 수 있는 고유의 예측함수를 제공하기도 함
   
   OpenCV에서 StatModel클래스를 상속받아 만들어진 머신러닝 알고리즘 구현 클래스에 대한 이름과 의미에 대한 표 477p 참고.*/

/* K 최근접 이웃(KNN = K-Nearest Neighbor) */
/* K 최근접 이웃 알고리즘은 분류 또는 회귀에 사용되는 지도 학습 알고리즘의 하나
   KNN 알고리즘을 분류에 사용할 경우, 특징 공간에서 테스트 데이터와 가장 가까운 k개의 훈련 데이터를 찾고,
   k개의 훈련 데이터 중에서 가장 많은 클래스를 테스트 데이터의 클래스로 지정
   KNN 알고리즘을 회귀 문제에 적용할 경우에는 테스트 데이터에 인접한 k개의 훈련 데이터 평균을 테스트 데이터 값으로 설정
   
   KNN 알고리즘 동작 방식 479p에 설명이 잘 되어 있음 
   KNN 알고리즘에서 k를 1로 설정하면 최근접 이웃 알고리즘이 됨
   그러므로 보통 k는 1보다 큰 값으로 설정하며, k값을 어떻게 설정하느냐에 따라 분류 및 회귀 결과가 달라질 수 있음
   최선의 k값을 결정하는 것은 주어진 데이터에 의존적이며, 보통 k값이 커질수록 잡음 또는 이상치 데이터의 영향이 감소
   그러나 k값이 어느 정도 이상으로 커질 경우 오히려 분류 및 회귀 성능이 떨어질 수 있음 
   
   KNN 알고리즘은 KNearest 클래스에 구현되어 있음.
   KNearest 클래스는 ml모듈에 포함되어 있고, cv::ml 네임스페이스에 정의되어 있음. 사용하려면 객체 먼저 생성
   KNearest::create() 사용. 단순히 비어 있는 KNearest 객체를 생성하며 반환값은 KNearest 객체를 참조하는 Ptr<KNearest> 스마트 포인터 객체 
   
   KNearest 클래스는 기본적으로 k값을 10으로 설정. 변경하려면 KNearest::setDefaultK함수를 이용하여 변경
   StatModel::predict함수 대신 KNearest::findNearest함수를 이용하여 테스트 데이터의 응답을 구할 경우에는
   k값을 KNearest::findNearest함수 인자로 명시적으로 지정할 수 있음
   KNearest::setDefaultK(int val). val = KNN알고리즘에서 사용할 k값. StatModel::predict를 사용할 경우 미리 k값을 적절하게 설정해야 함
   KNearest 객체는 기본적으로 분류를 위한 용도로 생성됨
   KNearest 객체를 분류가 아닌 회귀에 적용하려면 KNearest::setIsClassifier(bool val)에 false를 지정하여 호출
   true이면 분류, false이면 회귀로 사용
   
   KNearest 객체를 생성하고 속성을 설정한 후에는 StatModel::train함수를 이용하여 학습을 진행할 수 있음
   KNearest 클래스의 경우에는 train함수에서 실제적인 학습이 진행되는 않으며, 단순히 훈련 데이터와 레이블 데이터를
   KNearest 클래스 멤버 변수에 모두 저장하는 작업이 이루어짐
   
   KNearest 클래스에서 훈련 데이터를 학습한 후, 테스트 데이터에 대한 예측을 수행할 때에는 주로 KNearest::findNearest함수를 사용
   KNearest 클래스에서도 StatModel::perdict함수를 사용할 수 있지만 KNearest::findNearest함수가 예측 결과와 관련된 정보를 
   더 많이 반환하기 때문에 유용
   KNearest::findNearest(samples, k, results, neighborResponses = noArray(), dist = noArray();)
   1. 테스트 데이터 벡터가 행 단위로 저장된 행렬. 입력 벡터의 차원은 훈련 벡터의 차원과 같아야 하며  CV_32FC1이어야 함
   2. 사용할 최근접 이웃 개수, 1보다 크거나 같아야 한다.
   3. 각 입력 샘플에 대한 예측(분류 또는 회귀)결과를 저장한 행렬. samples.rows x 1 크기를 갖고, 타입은 CV_32FC1이어야 함
   4. 예측에 사용된 k개의 최근접 이웃 클래스 정보를 담고 있는 행렬. samples.rows x k 크기를 갖고, 타입은 CV_32FC1이어야 함
   5. 입력 벡터와 예측에 사용된 k개의 최근접 이웃과의 거리를 저장한 행렬. samples.rows x k 크기를 갖고, 타입은 CV_32FC1이어야 함
   6. 반환값 = 입력 벡터가 하나인 경우에 대한 응답이 반환됨 
   
   KNearest::findNearest함수는 samples행렬 각 행에 저장된 테스트 데이터와 가까운 k개의 훈련 데이터를 찾아 분류 또는 회귀 응답을 반환
   samples 행렬의 행 개수는 예측할 테스트 데이터 개수와 같고, 열 개수는 학습 시 사용한 훈련 데이터의 차원과 같아야 함
   분류 및 회귀 결과가 저장되는 results 행렬은 samples 행렬과 같은 행 개수를 가지고, 열 개수는 항상 1
   즉, samples 행렬에서 i번째 행에 대한 응답이 results 행렬의 i번째 행에 저장됨
   neighborResponses와 dist 인자는 KNN 알고리즘 수행 후 추가적인 정보를 받아오는 용도이며, 필요하지 않으면 생략 가능 */

/* 2차원 평면에서 3개의 클래스로 구성된 점들을 KNN 알고리즘으로 분류하고, 그 경계면을 화면에 표시하는 예제 프로그램
   (150, 150), (350, 150), (250, 400) 좌표를 중심으로 하는 가우시안 분포의 점을 각각 30개씩 생성하여 KNN알고리즘 훈련 데이터로 사용
   (0, 0)부터 (499, 499)좌표 사이의 모든 점에 대해 KNN 분류를 수행하여 그 결과를 RGB로 나타냄
   kNN알고리즘의 k값은 트랙바를 이용하여 프로그램 실행 중 변경할 수 있도록 함 */

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

	/* (150, 150)좌표를 중심으로 하는 0번 클래스 점, (350, 150)좌표를 중심으로 하는 1번 클래스 점
	   (250, 400)좌표를 중심으로 하는 2번 클래스 점을 각각 30개씩 생성하여 훈련 데이터에 추가한다 
	   0번과 1번 클래스 점은 각각의 중심을 기준으로 표준 편차 50에 해당하는 가우시안 부포를 따르고,
	   2번 클래스 점은 중심을 기준으로 표준 편차 70에 해당하는 가우시안 분포를 따른다 
	   코드가 실행되면 train 행렬은 90 x 2 크기의 행렬이 되고, label 행렬은 90 x 1 크기의 행렬이 됨
	   train 행렬은 2차원 평면에서 정의된 점들의 좌표를 포함하고 있으며, 각 점들이 속한 클래스 정보는 label 행렬에 저장되어있음 */
	randn(rn, 0, 50);
	for (int i = 0; i < NUM; i++)
		addPoint(Point(rn.at<int>(i, 0) + 150, rn.at<int>(i, 1) + 150), 0);

	randn(rn, 0, 50);
	for (int i = 0; i < NUM; i++)
		addPoint(Point(rn.at<int>(i, 0) + 350, rn.at<int>(i, 1) + 150), 1);

	randn(rn, 0, 70);
	for (int i = 0; i < NUM; i++)
		addPoint(Point(rn.at<int>(i, 0) + 250, rn.at<int>(i, 1) + 400), 2);

	/* KNN 이름의 창에 트랙바를 부착하고, 트랙바가 움직이면 on_k_changed 함수가 실행되도록 함 */
	namedWindow("knn");
	createTrackbar("k", "knn", &k_value, 5, on_k_changed);

	/* 프로그램이 처음 실행되자마자 KNN알고리즘으로 분류된 결과를 보여 주도록 함수를 호출함
	   KNN알고리즘에 의한 학습과 img 영상 모든 좌표에서의 클래스 값 예측을 진행하고 그 결과를 knn창에 표시 */
	trainAndDisplay();

	waitKey();
	return 0;
}

/* 트랙바를 움직여서 k값이 바뀌면 다시 KNN알고리즘을 학습시키고 그 결과를 화면에 나타낸다 */
void on_k_changed(int, void*)
{
	if (k_value < 1) k_value = 1;
	trainAndDisplay();
}
 /* addPoint함수는 특정 좌표 점 pt를 cls클래스로 등록한다 */
void addPoint(const Point& pt, int cls)
{
	Mat new_sample = (Mat_<float>(1, 2) << pt.x, pt.y);
	train.push_back(new_sample);

	Mat new_label = (Mat_<int>(1, 1) << cls);
	label.push_back(new_label);
}

void trainAndDisplay()
{
	/* StatModel::train함수를 이용하여 KNN알고리즘을 학습 */
	knn->train(train, ROW_SAMPLE, label);

	/* img 영상 전체 좌표에 대해 KNN분류가 응답을 조사하여 RGB로 표시 */
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

	/* 149 ~ 166행에서 추가한 훈련 데이터 점 좌표에 반지름 5인 원을 각각 RGB로 표시*/
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

/* KNN을 이용한 필기체 숫자 인식 */
/* 머신러닝으로 특정 문제를 해결하려면 많은 양의 훈련 데이터가 필요함
   digits.png 숫자 영상에는 0 ~ 9까지의 필기체 숫자가 5000개 적혀 있음
   이 영상을 이용하여 머신러닝 알고리즘을 학습시키려면 각각의 숫자 영상을 부분 영상으로 추출하여 훈련 데이터를 생성해야함
   머신러닝으로 영상을 인식 또는 분류할 경우, 영상으로부터 인식 목적에 적합한 특징 벡터를 추출하여 머신러닝 입력으로 사용
   이 절에서는 20 x 20 숫자 영상 픽셀값 자체를 KNN 알고리즘 입력으로 사용하겠음 (각각의 숫자는 20 x 20 픽셀 크기임) 
   숫자들이 대체로 20 x 20 부분 영상 정중앙에 위치해 있고, 숫자 크기도 거의 일정하기 때문에 픽셀값을 그대로 사용해도
   충분한 인식 결과를 얻을 수 있음
   한 장의 숫자 영상은 20 x 20 픽셀 크기이고, 이 픽셀값을 모두 일렬로 늘어놓으면 1 x 400 크기의 행렬로 변환할 수 있음
   필기체 숫자 훈련 데이터 하나는 400개의 숫자값으로 표현되고, 이는 400차원 공간에서의 한 점과 같음.
   각각의 숫자 영상을 1 x 400 행렬로 바꾸고, 이 행렬을 모두 세로로 쌓으면 전체 숫자 영상 데이터를 표현하는 5000 x 400 크기의 행렬이 됨
   이 행렬을 KNearest 클래스의 훈련 데이터로 전달
   KNN알고리즘으로 숫자 영상을 학습시키려면 각 필기체 숫자 영상이 나타내는 숫자 값은 레이블 행렬로 함께 전달해야 함
   레이블 행렬의 행 크기는 훈련 데이터 영상 개수와 같고, 열 크기는 1 
   훈련 데이터 행렬에서 처음 500개 행은 숫자 0에 대한 데이터, 그 다음 500개 행은 숫자 1에 대한 데이터임
   그러므로 레이블 행렬도 처음 500개 행 원소는 0으로 설정, 그 다음 500개 행은 1로 설정. 9까지 모두 설정한 후,
   KNearest 클래스의 레이블 데이터로 전달 */

#if 0
Ptr<KNearest> train_knn();
void on_mouse(int event, int x, int y, int flags, void* userdata);

int main()
{
	Ptr<KNearest> knn = train_knn(); // train_knn함수를 실행하여 필기체 숫자를 학습한 결과를 knn에 저장

	if (knn.empty()) {
		cerr << "Training failed!" << endl;
		return -1;
	}

	Mat img = Mat::zeros(400, 400, CV_8U); // 400 x 400 크기의 영상 img를 생성. img 영상에 마우스로 글씨를 쓰고 숫자를 인식할 것임

	imshow("img", img);
	setMouseCallback("img", on_mouse, (void*)&img);

	while (true) {
		int c = waitKey();

		if (c == 27) { // ESC 누르면 종료
			break;
		}
		else if (c == ' ') { // 키보드에서 스페이스바를 누르면 필기체 숫자 인식을 수행
			Mat img_resize, img_float, img_flatten, res;

			resize(img, img_resize, Size(20, 20), 0, 0, INTER_AREA); // 숫자가 씅진 img영상을 20 x 20 크기로 변환하여 img_resize에 저장
			img_resize.convertTo(img_float, CV_32F); // img_resize 영상 자료형을 float로 변환하여 img_float에 저장
			img_flatten = img_float.reshape(1, 1); // 20 x 20 img_float 영상을 400 x 1 크기의 영상으로 변환하여 img_flatten에 저장

			/* KNN알고리즘으로 분류한 결과를 콘솔 창에 출력 */
			knn->findNearest(img_flatten, 3, res);
			cout << cvRound(res.at<float>(0, 0)) << endl;

			/* img 영상을 검은색으로 초기화한 후 화면에 나타냄 */
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

	/* digits 영상에 가로 100개, 세로 50개의 필기체 숫자가 적혀 있으므로 for 반복문 범위를 동일하게 설정함 */
	for (int j = 0; j < 50; j++) {
		for (int i = 0; i < 100; i++) {
			Mat roi, roi_float, roi_flatten;
			roi = digits(Rect(i * 20, j * 20, 20, 20)); // 가로 i, 세로 j번째 필기체 숫자 영상을 roi에 저장
			roi.convertTo(roi_float, CV_32F); // roi 영상 자료형을 float로 변환하여 roi_float에 저장
			roi_flatten = roi_float.reshape(1, 1); // 20 x 20 roi_float 영상을 400 x 1 크기의 영상으로 변환하여 roi_flatten에 저장

			train_images.push_back(roi_flatten); // roi_flatten 영상을 train_images행렬의 맨 아래 행으로 추가
			train_labels.push_back(j / 5); // train_labels 행렬의 맨 아래에 현재 추가한 필기체 숫자 영상의 정답(레이블)을 추가
		}
	}

	/* KNearest 객체 knn을 생성하고, KNN학습을 수행.
	   knn->train함수 인자로 사용되는 train_images 행렬 크기는 5000 x 400이고. train_labels 행렬 크기는 5000 x 1 임*/
	Ptr<KNearest> knn = KNearest::create();
	knn->train(train_images, ROW_SAMPLE, train_labels);

	return knn; // 학습된 knn 스마트 포인터를 반환함 
}

Point ptPrev(-1, -1);
/* 마우스 왼쪽 버튼을 누른 상태에서 마우스를 움직이면 해당 위치에 두께 40픽셀로 흰색 글씨를 쓸 수 있음 */
void on_mouse(int event, int x, int y, int flags, void* userdata)
{
	Mat img = *(Mat*)userdata;

	/* 마우스 왼쪽 버튼을 누른 위치를 ptPrev에 저장함 */
	if (event == EVENT_LBUTTONDOWN) {
		ptPrev = Point(x, y);
	}
	else if (event == EVENT_LBUTTONUP) { // 마우스 왼쪽 버튼을 떼면 ptPrev 좌표를 (-1, -1)로 초기화함
		ptPrev = Point(-1, -1);
	}
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) { // 마우스 왼쪽 버튼을 누른 상태로 마우스가 움직이면 
		line(img, ptPrev, Point(x, y), Scalar::all(255), 40, LINE_AA, 0); // ptPrev좌표로부터 (x ,y)좌표까지 직선을 그림
		ptPrev = Point(x, y); //그리고 ptPrev 좌표를 (x, y)로 변경함

		imshow("img", img);
	}
}
#endif