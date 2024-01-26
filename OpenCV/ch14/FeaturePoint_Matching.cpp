/* 특징점 매칭 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* 두 장의 영상에서 추출한 특징점 기술자를 비교하여 서로 비슷한 특징점을 찾는 특징점 매칭 
   크기 불변 특징점으로부터 구한 기술자를 매칭하면 크기와 회전에 강인한 영상 매칭을 수행할 수 있음 
   특징점 매칭 정보를 저장할 때 사용하는 DMatch 클래스.
   DMatch 클래스는 한 장의 영상에서 추출한 특징점과 다른 한 장의 영상 또는 여러 영상에서 추출한 특징점 사이의 매칭 정보를 표현할 수 있음
   DMatch 클래스 멤버 변수
   queryIdx = 질의 기술자 번호. trainIdx = 훈련 기술자 번호. imgIdx = 훈련 영상 번호(여러 장의 영상을 훈련 영상으로 설정한 경우에 사용)
   distance = 두 기술자 사이의 거리. < 연산자 재정의 = distance 변수 값을 이용하여 크기를 비교 
   
   distance = 두 키포인트 기술자가 얼마나 차이가 나는지를 나타내는 매칭 척도의 역할.
   두 특징점이 서로 유사하면 0에 가깝고, 서로 다른 특징점이면 값이 크게 나타남.
   다차원 벡터의 유클리드 거리를 이용하여 주로 계산하며, 다만 이진 기술자끼리 비교하는 경우에는 해밍 거리를 사용
   DMatch 클래스 객체는 사용자가 직접 생성하지 않고, 특징점 매칭 알고리즘 내부에서 생성하여 사용자에게 반환함 
   
   특징점 매칭 클래스는 DescriptorMatcher 클래스를 상속받아 만들어짐. 
   DescriptorMatcher 클래스는 match, knnMatch, radiusMatch등의 가상 멤버 함수를 가지고 있는 추상클래스이며,
   DescriptorMatcher 클래스를 상속받은 BFMatcher 클래스와 FlannBasedMatcher 클래스는 이들 멤버 함수 기능을 실제로 구현하도록 설계됨
   match함수는 가장 비슷한 기술자 쌍을 하나 찾고, knnMatch함수는 비슷한 기술자 쌍 k개를 찾음
   radiusMatch는 지정한 거리 반경 안에 있는 기술자 쌍을 모두 찾아 반환함 
   
   BFMatcher클래스는 전수조사 매칭을 수행함. 질의 기술자 집합에 있는 모든 기술자와 훈련 기술자 집합에 있는 모든 기술자 사이의 거리를 계산하고,
   이 중 가장 거리가 작은 기술자를 찾아 매칭하는 방식
   매칭 결정 방법은 매우 직관적이지만 특징점 개수가 늘어날수록 거리 계산횟수가 급격하게 늘어날 수 있다는 단점이 있음
   예를 들어 첫 번쨰 영상에 1000개 특징점, 두 번째 영상에 2000개 특징점이 있으면 총 2,000,000의 비교연산을 수행
   
   그러므로 FlannBasedMatcher 클래스를 사용하는 것이 효율적. Flann은 근사회된 최근방 이웃 알고리즘을 빠르게 구현한 라이브러리임
   FlannBasedMatcher 클래스는 Flann라이브러리를 이용하여 빠르게 매칭을 수행하는 클래스
   FlannBasedMatcher 클래스는 근사회된 거리 계산 방법을 사용하므로 가장 거리가 작은 특징점을 찾지 못할 수 있지만, 매우 빠르게 동작
   다만, FlannBasedMatcher 클래스는 기본적으로 L2 노름 거리 측정 방식을 사용하므로 해밍 거리를 사용하는 이진 기술자에 대해서는 사용 못 함
   
   위 두 클래스의 객체를 생성하려면 creat 정적 멤버 함수를 사용해야함
   BFMatcher::create(normType, crossCheck)
   normType = 기술자 거리 측정 방식. NORM_L1, NORM_L2, NORM_HAMMING, NORM_HAMMING2 중 하나를 지정
   crossCheck = 이 값이 true이면 i번째 질의 기술자와 가장 유사한 훈련 기술자가 j이고 j번쩨 훈련 기술자와 가장 유사한
   질의 기술자가 i인 경우에만 매칭 결과로 반환함 
   반환값 = BFMatcher 객체를 참조하는 Ptr 스마트 포인터 객체 
   ORB, BRIEF, AKAZE 알고리즘처럼 이진 기술자를 사용하는 경우에는 NORM_HAMMIN플래그를 지정해야함. 
   만약 ORB기술자에서 WTA_K를 3 or 4로 설정한 경우에는 NORM_HAMMING2를 지정
   
   FlannBasedMatcher::creat()
   반환값 = FlannBasedMatcher 객체를 참조하는 Ptr 스마트 포인터 객체 
   
   Ptr<DescriptorMatcher> matcher = BFMatcher::create();
   원래 Ptr<BFMatcher> 타입을 반환하지만, DescriptorMatcher클래스가 부모 클래스이기 때문에 matcher 객체를 Ptr<DescriptorMatcher>타입으로 선언
   인자를 지정하지 않으면 NORM_L2사용. 이진 기술자를 생성하는 경우에는 해밍거리 사용
   Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING); 
   
   객체를 생성한 후에는 두 입력 영상에서 추출한 기술자 행렬 사이의 매칭을 수행할 수 있음 
   예를 들어 첫 번째 영상에서 추출한 특징점 기술자 행렬이 desc1이고 두 번째 영상에서 추출한 특징점 기술자 행렬이 desc2인 경우
   vector<DMatch> matches;
   matcher->match(desc1,desc2,matches); 코드로 매칭을 수행할 수 있음 
   
   DescripotrMatcher::matche()함수는 desc1에 포함된 각각의 기술자와 가장 유사한 기술자를 desc2에서 찾고, 그 결과를 vector<DMatch>타입의
   변수 matches에 저장함
   DescripotrMatcher::matche(queryDescriptors, trainDescriptors, matches, mask)
   1. 질의 기술자 집합. 2. 훈련 기술자 집합. 3 매칭 결과.
   4. 서로 매칭 가능한 질의 기술자와 훈련 기술자를 지정할 때 사용. 행 개수는 질의 기술자 개수와 같아야 하고, 열의 개수는 훈련 기술자 개수와 같아야 함
   만약 mask.at<uchar>(i,j)값이 0이면 queryDescriptors[i]는 trainDescriptors[j]로 매칭될 수 없음.
   noArray()로 지정하면 모든 가능한 매칭을 찾음
   위 함수는 queryDescriptors에 저장된 각각의 기술자에 대해 가장 유사한 기술자를 trainDescriptors에서 찾음.
   각각의 매칭 결과에 대해 DMatch::queryIdx에는 queryDescriptors의 번호가 저장되고, DMatch::trainIdx에는 trainDescriptors의 번호가 저장됨
   mask인자를 지정하지 않는 경우, 매칭 결과가 저장되는 matches에는 queryDescriptors 기술자 개수와 같은 수의 DMatch 객체가 저장됨
   
   주어진 질의 기술자에 대해 k개의 유사한 훈련 기술자를 찾아 반환하는 DescripotrMatcher::knnMatch함수와
   지정한 거리보다 작은 거리를 찾는 훈련 기술자를 모두 찾아 반환하는 DescripotrMatcher::radiusMatch함수는 OPENCV문서 사이트 참고 
   
   두 영상에서 추출한 특징점의 매칭 결과를 한눈에 확인할 수 있도록 매칭 결과 영상 생성 기능을 제공함 
   drawMatches함수는 두 매칭 입력 영상을 가로로 이어 붙이고, 각 영상에서 추출한 특징점과 매칭 결과를 다양한 색상으로 표시한 결과 영상을 제공
   drawMatches(img1, keypoints1, img2, keypoints2, mathces1to2, outImg, matchColor, singlePointColor, matchesMask, flags)
   matches1to2 = 첫 번째 입력 영상에서 두 번째 입력 영상으로의 매칭 정보
   outImg = 출력 영상
   matchColor = 매칭된 특징점과 직선 색상. Scalar::all(-1)을 지정하면 임의의 색상으로 그림
   singlePointColor = 매칭되지 않은 특징점 색상. Scalar::all(-1)을 지정하면 임의의 색상으로 그림
   matchesMask = 매칭 정보를 선택하여 그릴 때 사용할 마스크. std::vector<char>()를 지정하면 모든 매칭 결과를 그림
   flags = 매칭 정보 그리기 방법. DrawMatchesFlags 열거형 상수를 지정 448p 참고
   위 함수는 2개의 입력 영상을 가로로 이어 붙이고, 두 영상 사이의 특징점 매칭 결과를 직선으로 그린 결과 영상 outimg를 반환 
   두 입력 영상 사이의 매칭 정보는 matches1to2인자로 전달함. */


/* box 영상에서 추출한 모든 특징점 기술자에 대해 가장 유사한 box_in_scene영상의 특징점 기술자를 찾아 직선을 그렸기 때문에
   매칭 결과가 매우 복잡하게 나타나고, box_in_scene 영상에서 추출된 일부 특징점은 매칭이 되지 않아 직선이 연결되어 있지 않음 */
void keypoint_matching()
{
	Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Ptr<Feature2D> feature = ORB::create(); // ORB 객체를 생성

	/* src1, src2 영상에서 각각 특징점을 검출하고 기술자를 계산함. 각 영상의 기술자는 desc1, desc2행렬에 저장됨 */
	vector<KeyPoint> keypoints1, keypoints2;
	Mat desc1, desc2;
	feature->detectAndCompute(src1, Mat(), keypoints1, desc1);
	feature->detectAndCompute(src2, Mat(), keypoints2, desc2);

	/* BFMatcher 클래스 객체를 생성. 기술자 거리 계산 방식은 해밍 거리를 사용함 */
	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

	/* desc1, desc2 기술자를 서로 매칭하여 그 결과를 matces에 저장함 */
	vector<DMatch> matches;
	matcher->match(desc1, desc2, matches);

	/* matches 정보를 이용하여 매칭 결과 영상 dst를 생성 */
	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, matches, dst);

	imshow("src1", src1);
	imshow("src2", src2);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

/* box_in_scene 영상에서는 box 스낵 상자 영상 일부가 가려져 있기 때문에 box영상에서 추출한 특징점이 모두 제대로 매칭되기가 어려움 
   가려져 있지 않더라도 기하학적 변형과 조명 변화로 인해 완벽한 매칭은 거의 불가능. 매칭 결과 중 상당수는 완전히 다른 특징점으로 잘못 매칭됨
   전체 매칭 결과에서 잘못 매칭된 결과는 제외하고, 제대로 매칭되었다고 파난하는 결과만 선별하여 사용해야 함
   
   DMatch클래스는 기술자 사이의 거리를 표현하는 distance 멤버 변수를 가지고 있음. distance 값이 너무 큰 매칭 결과는 무시하고,
   값이 작은 결과만 사용하는 것이 좋음. 
   DMatch클래스는 부등호 연산자에 대한 재정의가 되어 있고, 이 연산자 재정의에서는 distance 변수 크기를 비교하기 때문에 DMatch 객체를
   std::sort()함수로 정렬하면 자동으로 distance값을 기준으로 정렬함

   vector<DMatch> matches;
   matcher->match(desc1, desc2, matches);
   sort(matches.begin(), matches.end());
   vector<DMatch> good_matches(matches.begin(), matches.begin() + 50);
   위의 코드는 두 영상에서 추출한 기술자 desc1과 desc2를 매칭한 후, 매칭 결과를 distance 값 기준으로 오름차순 정렬
   matches에 저장된 DMatch객체들은 distance 값이 작은 순서대로 앞쪽에 위치하게 됨
   그러므로 정렬된 mathces에서 좋은 매칭 결과만 추출하려면 위의 코드 4번쨰줄을 작성하면 됨
   good_matches변수에는 전체 매칭 결과 matches 중에서 매칭이 잘 된 50개의 매칭 결과만 저장됨 */

/* 코드를 실행하면 전 함수보다 잘되는 것을 볼 수 있지만 여전히 몇몇 특징점은 box_in_scene영상에서 스낵 박스 위치가 아닌 
   다른 지점으로 매칭되는 것을 볼 수 있음. 호모그래피와 영상 매칭에서 일부 부정확한 매칭 정보가 포함되어 있어도
   box_in_scene영상에 box에 해당하는 스낵 상자 위치를 정확하게 찾는 방법에 대해 설명 */
void good_matching()
{
	Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Ptr<Feature2D> feature = ORB::create(); // ORB 객체를 생성

	/* src1, src2 영상에서 각각 특징점을 검출하고 기술자를 계산함. 각 영상의 기술자는 desc1, desc2행렬에 저장됨 */
	vector<KeyPoint> keypoints1, keypoints2;
	Mat desc1, desc2;
	feature->detectAndCompute(src1, Mat(), keypoints1, desc1);
	feature->detectAndCompute(src2, Mat(), keypoints2, desc2);

	/* BFMatcher 클래스 객체를 생성. 기술자 거리 계산 방식은 해밍 거리를 사용함 */
	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

	/* desc1, desc2 기술자를 서로 매칭하여 그 결과를 matces에 저장함 */
	vector<DMatch> matches;
	matcher->match(desc1, desc2, matches);

	/* 두 영상의 특징점 매칭 결과를 정렬함 
	   정렬된 매칭 결과에서 상위 50개 매칭결과를 good_matches에 저장함 */
	sort(matches.begin(), matches.end());
	vector<DMatch> good_matches(matches.begin(), matches.begin() + 50);

	/* good_matches를 이용하여 매칭 결과 영상을 생성
	   drawMatches()함수의 10번째 인자 DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS 상수를 지정하여
	   매칭되지 않은 특징점은 화면에 표시하지 않음 */
	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, good_matches, dst, Scalar::all(-1), Scalar::all(-1), vector<char>(),
		DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	imshow("src1", src1);
	imshow("src2", src2);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();

}

/* 호모그래피와 영상 매칭 */
/* 특징점 매칭 결과로부터 두 영상의 호모그래피를 계산하고, 이를 이용하여 크기가 다르고 회전이 되어 있는 객체를 정확하게 매칭하는 방법 
   호모그래피는 3차원 공간상의 평면을 서로 다른 시점에서 바라봤을 때 획득되는 영상 사이의 관계를 나타내는 용어 
   호모그래피는 수학적으로 하나의 평면을 다른 평면으로 투시 변환하는 것과 같은 관계에 있음 
   실제적인 연산 관점에서 호모그래피는 투시 변환과 같기 때문에 호모그래피는 3x3실수 행렬로 표현할 수 있음
   또한, 투시 변환을 구할 때와 마찬가지로 네 개의 대응되는 점의 좌표 이동 정보가 있으면 호모그래피 행렬을 구할 수 있음 
   그러나 특징점 매칭 정보로부터 호모그래피를 구하는 경우에는 서로 대응되는 점 개수가 네 개보다 훨씬 많기 때문에 이러한 경우에는 
   투시 변환 시 에러가 최소가 되는 형태의 호모그래피 행렬을 구해야 함 
   
   두 영상 평면에서 추출된 특징점 매칭 정보로부터 호모그래피를 계산할 때 사용할 수 있는 함수 findHomograpyh
   findHomography(srcPoints, dstPoints, method =0,ransacReprojThreshol = 3, mask = noarray(), maxIters = 2000, confidence = 0.955) 
   1. 원본 평면상의 점 좌표, CV_32FC2 타입의 Mat객체 또는 vector<Point2f> 타입의 변수 지정 
   2. 목표 평면상의 점 좌표, CV_32FC2 타입의 Mat객체 또는 vector<Point2f> 타입의 변수 지정
   3. 호모그래피 행렬 계산방법. 0 = 모든 점(입력점, 출력점 모두)을/를 사용하는 일반적인 방법(최소자승법)
   LMEDS = 최소 메디안 제곱 방법, RANSAC = RANSAC 방법, RHO = PROSAC 방법
   4. 최대 허용 재투영 에러, 이 값 이내로 특징점이 재투영되는 경우에만 정상치로 간주함. RANSAC or RHO 방법에서만 사용 
   5. 호모그래피 계산에 사용된 점들을 알려 주는 출력 마스크 행렬. LMEDS or RANSAC방법에서만 사용
   6. RANSAC 최대 반복 횟수
   7. 신뢰도 레벨. 0 ~ 1 사이의 실수를 지정
   8. 반환값 = CV_63FC1타입의 3x3호모그래피 행렬을 반환
   
   일반적으로 특징점 매칭 결과로부터 호모그래피를 계산할 때 최소자승법을 사용하면 호모그래피가 제대로 계산되지 않음
   잘못 매칭된 점들처럼 오차가 큰 입력 정보를 이상치라고 부르며, 이상치가 많이 존재하는 경우에는 호모그래피 계산 방법을
   LMEDS, RANSAC, RHO 방법으로 설정하는 것이 좋음
   LMEDS 메서드는 보통 이상치가 50%이하인 경우에는 올바르게 작동함
   RANSAC or RHO 방법은 이상치가 50%이상 존재하더라도 호모그래피 행렬을 잘 찾아주는 편
   RANSAC or RHO 방법을 사용할 경우에는 srcPoints와 dstPoints에 저장된 점이 이상치가 아니라고 판단하기 위한 임계값을 설정해야 하며,
   이 값은 ransacReprojThreshold 인자로 지정함.
   만약 H * srcPointsi와 dstPointsi 사이의 거리가 ransacReprojThreshold보다 작으면 정상치로 간주함
   
   RANSAC = RANdom SAmple Consensus 알고리즘은 이상치가 포함된 입력 데이터로부터 수학적 모델 파라미터를 효과적으로 결정하는 알고리즘
   RANSAC 알고리즘으로 호모그래피를 계산하는 경우, 다수의 특징점 매칭 정보로부터 네 개의 대응점을 임의로 추출함 
   이 대응점 정보를 이용하여 3x3 호모그래피 행렬을 계산하고, 나머지 특징점 매칭 쌍 중에서 현재 구한 호모그래피 행렬에 부합되는 매칭 쌍 개수를 셈
   다시 임의로 네 개의 대응점을 추출하고, 호모그래피 행렬 계산과 해당 호모그래피에 부합되는 매칭 쌍 개수 세는 작업을 반복함.
   이 작업을 여러 번 반복한 후, 가장 많은 매칭 쌍의 지지를 받은 호모그래피 행렬을 최종 호모그래피 행렬로 결정하는 방식이 RANSAC */

void find_homography()
{
	Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Ptr<Feature2D> feature = ORB::create(); // ORB 객체를 생성

	/* src1, src2 영상에서 각각 특징점을 검출하고 기술자를 계산함. 각 영상의 기술자는 desc1, desc2행렬에 저장됨 */
	vector<KeyPoint> keypoints1, keypoints2;
	Mat desc1, desc2;
	feature->detectAndCompute(src1, Mat(), keypoints1, desc1);
	feature->detectAndCompute(src2, Mat(), keypoints2, desc2);

	/* BFMatcher 클래스 객체를 생성. 기술자 거리 계산 방식은 해밍 거리를 사용함 */
	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

	/* desc1, desc2 기술자를 서로 매칭하여 그 결과를 matces에 저장함 */
	vector<DMatch> matches;
	matcher->match(desc1, desc2, matches);

	/* 두 영상의 특징점 매칭 결과를 정렬함
	   정렬된 매칭 결과에서 상위 50개 매칭결과를 good_matches에 저장함 */
	sort(matches.begin(), matches.end());
	vector<DMatch> good_matches(matches.begin(), matches.begin() + 50);

	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, good_matches, dst, Scalar::all(-1), Scalar::all(-1), vector<char>(),
		DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	/* good_matches 매칭 결과에 저장된 질의 영상과 훈련 영상의 특징점 좌표를 추출하여 vector<Point2f>타입의 변수 pts1,pts2에 저장함 */
	vector<Point2f> pts1, pts2;
	for (size_t i = 0; i < good_matches.size(); i++) {
		pts1.push_back(keypoints1[good_matches[i].queryIdx].pt);
		pts2.push_back(keypoints2[good_matches[i].trainIdx].pt);
	}

	/* pts1점들이 pts2점들로 이동하는 호모그래피 행렬을 구하여 H에 저장
	   호모그래피 계산 방법은 RANSAC 알고리즘을 사용함 */
	Mat H = findHomography(pts1, pts2, RANSAC);

	/* src1영상의 네 모서리 점을 corners1에 저장한 후, 호모그래피 행렬 H를 이용하여 이 점들이 이동하는 위치를 계산하여 corners2에 저장 */
	vector<Point2f> corners1, corners2;
	corners1.push_back(Point2f(0, 0));
	corners1.push_back(Point2f(src1.cols - 1.f, 0));
	corners1.push_back(Point2f(src1.cols - 1.f, src1.rows - 1.f));
	corners1.push_back(Point2f(0, src1.rows - 1.f));
	perspectiveTransform(corners1, corners2, H);

	/* 매칭 결과 영상 dst에서 corner2 점들이 위치하는 좌표를 corners_dst에 저장함 */
	vector<Point> corners_dst;
	for (Point2f pt : corners2) {
		corners_dst.push_back(Point(cvRound(pt.x + src1.cols), cvRound(pt.y)));
	}

	/* 매칭 결과 영상 dst에서 box영상 스낵 박스가 있는 위치에 녹색으로 사각형을 그림 */
	polylines(dst, corners_dst, true, Scalar(0, 255, 0), 2, LINE_AA);

	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main()
{
	//keypoint_matching();
	//good_matching();
	find_homography();
	return 0;
}