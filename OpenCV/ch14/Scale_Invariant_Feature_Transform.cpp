/* 크기 불변 특징점 검출과 기술 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;


/* 영상의 크기가 변경되거나 회전이 되어도 반복적으로 찾을 수 있는 크기 불변 특징점 검출 방법과 검출된 특징점을 표현하는 기술 방법
   코너는 영상이 회전되어도 여전히 코너로 검출됨. 즉, 회전 불변 특징점임 
   그러나 영상의 크기가 변결될 경우 코너는 더 이상 검출되지 않을 수 있음 
   동일한 모양의 크기가 다른 두 객체 영상에서 단순한 코너 점을 이용하여 서로 같은 위치를 찾는 것에는 한계가 있음
   크기 불변 특징 변환의 대표적인 알고리즘은 SIFT임 (SIFT를 풀어서 해석하면 크기 불변 특징 변환임)
   SIFT알고리즘은 영상의 크기 변화에 무관하게 특징점을 추출하기 위하여 입력 영상으로부터 스케일 스페이스를 구성함 
   스케일 스페이스는 영상에 다양한 표준 편차를 이용한 가우시안 블러링을 적용하여 구성한 영상 집합을 의미
   블러링이 된 영상이 스케일 스페이스를 구성하여 이루어진 영상 집합을 옥타브라고 부름
   SIFT알고리즘에서 크기 불변 특징점을 검출할 때에는 인접한 가우시안 블ㄹ링 영상끼리의 차영상을 사용, 이를 DoG영상이라고 함
   SIFT알고리즘은 DoG영상 집합에서 인접한 DoG 영상을 고려한 지역 극값 위치를 특징점으로 사용하며,
   엣지 성분이 강하거나 명암비가 낮은 지점은 제외함 
   
   SIFT알고리즘은 특징점을 검출하는 기능뿐만 아니라 특징점 주변의 픽셀 값을 이용한 기술자 계산 방법도 포함
   특징점 기술자는 특징점 주변 영상의 특성을 여러 개의 실수값으로 표현한 것을 의미하며, 특징 벡터라고도 함
   서로 같은 특징점에서 추출된 기술자는 실수 값 구성이 서로 일치해야 함
   SIFT는 기본적으로 특징점 부근의 부분 영상으로부터 그래디언트 방향 히스토그램을 추출하여 기술자로 사용
   특징점 근방으로부터 특징점의 주된 방향 성분을 계산하고, 이 방향만큼 회전한 부분 영상으로부터 128개의 빈으로 구성된 
   그래디언트 방향 히스토그램을 계산함
   각각의 빈 값은 float 자료형을 사용하며, 하나의 SIFT 특징점은 512바이트 크기의 기술자로 표현됨 
   
   SURF알고리즘은 Dog영상을 단순한 이진 패턴으로 근사화하여 속도를 향상시킴
   KAZE알고리즘은 비등방성 확산 필터를 이용하여 비선형 스케일 스페이스를 구축하여 특징점을 검출. 
   객체의 윤곽을 잘 보전하여 블러링, 크기 및 회전 변환, 잡음 등의 영향으로 변형된 영상에서 같은 특징점을 반복적으로 찾아내는 성능이 뛰어남
   
   그러나 위의 셋 다 복잡한 연산을 수행해야 하기 때문에 실시간 응용이 어려움. 메모리 사용량이 많고 특징점 사이의 거리 계산도 오래걸림
   그래서 특징점 검출이 매우 빠르고 이진수로 구성된 기술자를 사용하는 알고리즘이 발표되기 시작함
   
   ORB 알고리즘은 FAST코너 검출 방법을 이용하여 특징점을 추출함.
   다만 FAST알고리즘은 영상의 크기 변화에 취약하기 때문에 ORB알고리즘은 입력 영상의 크기를 점진적으로 축소한 피라미드 영상을 구축하여 특징점 추출
   각 특징점에서 주된 방향 성분을 계산하고, 방향을 고려한 BRIEF알고리즘으로 이진 기술자를 계산함 
   BRIEF는 순수하게 특징점 기술자만 생성하는 알고리즘.
   BRIEF는 특징점 주변의 픽셀 쌍을 미리 정하고, 해당 픽셀 값 크기를 비교햐여 0과 1로 특징을 기술함
   특징점 주변 정보를 이진수 형태로 표현하는 기술자를 이진 기술자라고 함 
   
   ORB알고리즘은 FAST기반의 방법으로 특징점을 구한 후, 각 특징점에서 픽셀 밝기 값 분포를 고려한 코너 방향 성분을 계산
   이 방향 성분을 이용하여 BRIEF계산에 필요한 점들의 위치를 보정함으로써 회전에 불변한 BRIEF 기술자를 계산함
   256개의 크기 비교 픽셀 쌍을 사용하여 이진 기술자를 구성하며, 결과적으로 하나의 특징점은 256비트로 표현할 수 있음
   SIFT, SURF 기술자가 512바이트, 256바이트인데 ORB는 32바이트의 크기로 특징점을 기술할 수 있어 효율적임
   
   이진 기술자로 표현된 특징점 사이의 거리 계산은 주로 해밍거리 방법을 사용 
   해밍 거리는 이진수로 표현된 두 기술자에서 서로 값이 다른 비트의 개수를 세는 방식으로 계산 
   두 기술자의 비트단위 배타적 논리함 연산 후, 비트 값이 1인 개수를 세는 방식으로 빠르게 계산할 수 있음 
   이외에도 BRISK, AKAZE, FREAK가 있으나 주로 ORB 사용
   
   특징점 검출 알고리즘 구현 클래스
   특징점 정보를 저장할 때 사용하는 KeyPoint클래스(특징점 = 키포인트)
   KeyPoint의 멤버 변수 pt, size, angle, response, octave, class_id 등이 있음.
   변수들은 특징점 주변 영역의 특징을 표현하는 기술자 계산 시에도 사용됨 
   KeyPoint 객체는 사용자가 직접 생성하지 않고, 특징점 검출 클래스 내부에서 생성하여 사용자에게 반환함
   
   OpenCV에서 특징점 관련 클래스는 모두 Feature2D클래스를 상속받아 만들어짐.
   Feature2D클래스는 detect(), compute(), detectAndCompute()라는 이름의 가상 멤버 함수를 가지고 있음
   Feature2D 클래스를 상속받은 각각 특징점 알고리즘 구현 클래스는 이들 멤버 함수 기능을 실제로 구현하도록 설계됨 
   detect()는 영상에서 키포인트를 검출, compute는 검출된 키포인트를 표현하는 기술자를 생성 
   
   특징점 알고리즘 구현 클래스 중에는 특징점 굼출만 지원하거나 기술자 생성만 지원하는 클래스도 있음
   예를 들어 FastFeatureDetector 클래스는 FAST 코너 검출 방법을 클래스로 구현한 것이며, 특징점을 검출하는 기능만 있음.
   compute 또는 detectAndCompute함수는 호출하면 에러가 발생
   BriefDescriptorExtractor 클래스는 다른 방법으로 구한 특징점 위치에서 BRIEF이진 기술자를 구하는 기능만 제공함
   그러므로 detect 또는 detectAndCompute 함수를 호출하면 안됌
   SIFT, SURF, KAZE, ORB처럼 검술과 기술을 함께 지원하는 알고리즘 클래스는 위의 세 함수를 모두 사용할 수 있음
   
   특징점 구현 알고리즘 클래스를 이용하려면 각 특징점 클래스 객체를 create라는 이름의 정적 멤버 함수를 이용하여 생성해야함
   특징점 클래스마다 정의된 create 정적 멤버 함수의 인자 구성은 각기 다르지만, 모든 인자에 기본값이 지정되어 있기 때문에
   인자를 지정하지 않고도 사용할 수 있음. 그리고 각 특징점 클래스의 create함수는 해당 클래스 객체를 참조하는 스마트 포인터를 반환함 
   
   예를 들어 ORB 클래스 객체를 생성하는 ORB::create()멤버 함수의 원형
   ORB::create(nfeatures = 500, scaleFactor = 1.2f, nlevels = 8, edgeThreshold = 31, firstLevel = 0, WTA_K = 2,
   scoreType = ORB::HARRIS_SCORE, patchSize = 31, fastThreshold = 20)
   위의 인자들을 순서대로 설명.
   1. 검출할 최대 특징 개수
   2. 피라미드 생성 비율(영상 축소 비율)
   3. 피라미드 단계 개수
   4. 특징을 검출하지 않을 영상 가장자리 픽셀 크기
   5. 항상 0을 지정해야 함
   6. BRIEF 기술자 계산 시 사용할 점의 개수. 2, 3, 4 중 하나를 지정해야 함
   7. 특징점 점수 결정 방법. ORB::HARRIS_SCORE 또는 ORB::FAST_SCORE 둘 중 하나를 지정
   8. BRIEF 기술자 계산 시 사용할 패치 크기
   9. FAST 코너 검출 방법에서 사용되는 임계값
   10. 반환값 = ORB 객체를 참조하는 Ptr 스마트 포인터 객체 
   ORB::create함수는 ORB 특징점 검출 및 기술자 계산에 필요한 많은 인자를 가지고 있지만 모두 기본값을 가지고 있어 간단하게 객체를 생성할 수 있음
   Ptr<ORB> feature = ORB::create() 형식으로 
   
   Ptr클래스는 스마트 포인터 클래스임. 그러므로 변수 feature는 마치 ORB객체의 포인터처럼 사용할 수 있고, 동적으로 할당된 ORB객체의 메모리는 자동으로 해제됨
   ORB클래스가 Feature2F클래스를 상속받아 만들어진 클래스이기 때문에 Ptr<Feature2D> feature = ORB::create();로 변경할 수 있음
   ORB말고 KAZE 특징점 검출 방법을 사용하고 싶다면 ORB대신 KAZE를 쓰면 됨
   
   특징점 클래스 객체를 생성하였다면, 영상에서 특징점을 검출하거나 검출된 특징점을 표현하는 기술자를 계산할 수 있음
   검출할 때는 Feature2D::detect() 가상 멤버 함수를 사용
   Feature2D::detect(image, keypoints, mask) => 다수의 특징점을 검출하여 vector<KeyPoint>타입의 변수 keypoints에 저장
   입력 영상의 일부 영역에서만 특징점을 검출하려면 mask인자를 설정하면 됨
   예를 들어 
   Mat src = imread("box_in_scene.png", IMREAD_GRAYSCALE);
   Ptr<Feature2D> feature = ORB::create();
   vector<KeyPoint> keypoints;
   feature->detect(src, keypoints); 영상에서 ORB특징점을 검출하는 코드 예제
   featur 변수는 Ptr<Feature2D>타입으로 선언되었지만 실제로는 ORB클래스 객체를 가리키고 있음 
   그러므로 feature->detect()형태로 함수를 호출하면 실제로는 ORB알고리즘 구현 클래스의 detect함수가 실행되고
   결과적으로 ORB특징점이 keypoints에 저장됨
   
   이미 검출된 특징점에서 각 특징점 주변의 부분 영상을 표현하는 기술자를 추출하려면 Feature2D::compute()함수를 사용
   Feature2D::compute(image, keypoints, descriptors)
   keypoints = 미리 검출해 둔 키포인트 정보. descriptors = 계산된 기술자 행렬. i번째 행은 i번째 키포인트의 기술자를 나타냄 
   keypoints로 전달된 특징점에서 기술자를 계산할 수 없으면 해당 특징점은 제거됨.
   계산된 각 특징점의 기술자는 모두 descriptor 행렬에 저장됨
   descriptor 행렬의 행 개수는 특징점 개수와 같고, 열 개수는 사용하는 기술자 알고리즘에 의해 자동으로 결정됨 
   
   위의 과정을 한꺼번에 수행하려면 Feature2D::detectAndCompute()멤버 함수 사용
   Feature2D::detectAndCompute(image, mask, keypoints, descriptors, useProviededKeypoints = false)
   useProviededKeypoints가 true이면 keypoints인자로 전달된 키포인트 정보를 이용하여 기술자를 계산함 
   
   특징점을 검출한 후에는 입력 영상 어느 위치에서 특징점이 검출되었는지를 영상 위에 직접 표시하여 확인할 수 있음
   Feature2D::detectAndCompute와 Feature2D::detect함수에 의해 검출된 특징점을 직접 영상 위에 그린 후,
   그 결과 영상을 반환하는 drawKeypoints 함수를 제공
   drawKeypoints(image, keypoints, outImage, color, flags)
   outImage = 키포인트가 그려진 출력 영상(원을 그려서 표시함)
   color = 키포인트 색상. 이 값이 Scalar::all(-1)이면 각 특징점을 임의의 색상으로 그림
   flags = 키포인트 그리기 방법. DrawMatchesFlags 열거형 상수 중 하나를 지정 448p 참고*/
void detect_keypoints()
{
	Mat src = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Ptr<Feature2D> feature = ORB::create(); // ORB 클래스 객체를 생성하여 feature 스마트 포인터에 저장함

	/* ORB 키포인트를 검출하여 keypoints 벡터에 저장함 */
	vector<KeyPoint> keypoints;
	feature->detect(src, keypoints);

	/* ORB 키포인트 기술자를 계산하여 desc행렬에 저장함 */
	Mat desc;
	feature->compute(src, keypoints, desc);

	/* keypoints에 저장된 키포인트 개수와 desc 행렬 크기를 콘솔 창에 출력함*/
	cout << "keypoints.size() : " << keypoints.size() << endl;
	cout << "desc.size() : " << desc.size() << endl;

	/* 입력 영상 src에 키포인트를 그린 결과를 dst에 저장함. 키포인트 그리는 방식을 DRAW_RICH_KEYPOINTS로 지정하여
	   키포인트 위치, 크기, 방향 정보를 함께 나타내도록 설정함
	   출력되는 원 크기는 특징점 검출 시 고려한 이웃 영역 크기를 나타냄
	   그리고 각 원의 중심에서 뻗어 나간 직선은 특징점 근방에서 추출된 주된 방향을 표시함 */
	Mat dst;
	drawKeypoints(src, keypoints, dst, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main()
{
	detect_keypoints();
	return 0;
}