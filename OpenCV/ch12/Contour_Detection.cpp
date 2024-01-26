/* 외곽선 검출 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* 레이블링과 더불어 이진 영상에서 객체의 위치 및 크기 정보를 추출하는 유용한 방법 중에 외곽선 검출이 있음 */
/* 객체의 외곽선 픽셀 좌표를 모두 추출하여 계층 정보와 함께 반환 */

void contours_basic()
{
	/* 객체의 외곽선은 객체 영역 픽셀 중에서 배경 영역과 인접한 일련의 픽셀을 의미 */
	/* 객체의 외곽선은 객체 바깥쪽 외곽선과 안쪽 홀 외곽선으로 구분할 수 있음 */
	/* 객체 하나의 외곽선은 여러 개의 점으로 구성됨 */
	/* 그러므로 객체 하나의 외곽선 정보는 vector<Point> 타입으로 저장할 수 있음 */
	/* 또한 하나의 영상에는 여러 개의 객체가 존재할 수 있으므로 영상 하나에서 추출된 전체 객체의 외곽선 정보는 vector<vector<Point>> 타입으로 표현 */
	/* 검출된 외곽선 점들의 좌표는 앞에서 선언한 타입의 변수에 모두 저장됨 */
	/* vector<vector<Point>> 타입은 vector<Point> 타입을 여러 개 포함할 수 있는 타입임 */
	/* 만약 외곽선 객체가 3개 있다면 vector<Point> 타입의 변수가 3개 있는 것임 */
	/* 변수이름이 contours이면 contours[0 ~ 2] 형태의 vector<Point> 타입이 3가지 있다는 것을 의미 */
	/* contours 변수로부터 전체 객체 개수를 알고 싶다면 contours.size() 반환값을 확인하면 됨 */
	/* 외곽선의 점 개수를 알고 싶다면 contours[number].size()형태로 코드를 작성 */

	/* 영상 내부 객체들의 외곽선을 검출하는 함수는 findContours()함수 */
	/* 외곽선들의 계층 정보를 받아 오는 hierarchy 인자가 있는 형태와 없는 형태 두 가지로 정의됨 */
	/* findContours(image, contours, hierarchy, mode, method, offset = Point()) */
	/* findContours(image, contours, mode, method, offset = Point())*/
	/* image = 입력 영상 8bit 1-channel 영상. 0이 아닌 픽셀을 객체로 취급. mode = RETR_CCOMP이면 CV_32SC1타입 지정 가능 */
	/* 이진화된 영상을 사용 */
	/* contours = 검출된 외곽선 정보. vector<vector<Point>> 타입 변수를 지정 */
	/* hierarchy = 외곽선 계층 정보. vector<Vec4i> 타입 변수 지정. int 자료형 4개를 저장할 수 있는 벡터 클래스 */
	/* hierarchy[i][1]에는 이전 외곽선 번호, hierarchy[i][2]에는 자식 외곽선 번호 */
	/* hierarchy[i][3]에는 부모 외곽선 번호가 저장됨. 계층 구조에서 해당 외곽선이 존재하지 않으면 -1이 저장됨 */
	/* mode = 외곽선 검출 모드. 390p 참고 */ 
	/* method = 외곽선 근사화 방법. 390p 참고 */
	/* offset = 외곽선 점 좌표의 오프셋(이동 변위) */

	/* 외곽선의 계층 구조는 외곽선의 포함 관계에 의해 결정됨 */
	/* 390 ~ 391p 참고 */
	/* 즉, 0번 외곽선 안에는 1,2,3번 홀 외곽선이 있으므로 0번 외곽선은 1,2,3번 외곽선의 부모 외곽선. 1,2,3은 0번 외곽선의 자식 외곽선임 */
	/* 0번과 4번 외곽선은 서로 포함 관계가 없이 대등하므로 이전 외곽선 또는 다음 외곽선의 관계를 가짐. */

	/* mode에 따라 검출되는 외곽선과 계층 구조가 서로 달라짐 */
	/* 391 ~ 392p 참고 */

	/* findContours()함수로 검출한 외곽선 정보를 이용하여 영상 위에 외곽선을 그리고 싶다면 drawContours함수를 사용 */
	/* drawContours(image, contours, contourIdx, color, thickness, lineType, hierarchy = noArray(), maxLevel = INT_MAX, offset = Point()) */
	/* contours = findContours로 구한 전체 전체 외곽선 정보, contourIdx = 외곽선 번호(음수를 지정하면 전체 외곽선을 그림) */
	/* color = 외곽선 색상, lineType = 외곽선 타입, hierarchy = 외곽선 계층 정보 */
	/* maxLevel = 그릴 외곽선의 최대 레벨. 이 값이 0이면 지정한 번호의 외곽선만 그림. 1보다 크거나 같으면 그에 해당하는 하위 레벨의 외곽선까지 그림 */
	/* offset = 추가적으로 지정할 외곽선 점 좌표의 오프셋(이동 변위), 지정한 좌표 크기만큼 외곽선 좌표를 이동하여 그림 */

	Mat src = imread("contours.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	/* src 영상으로부터 모든 외곽선을 검출하여 contours변수에 저장. 계층 구조는 없음 (RETR_LIST 모드는 계층 구조 없음) */
	vector<vector<Point>> contours;
	findContours(src, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	/* 전체 외곽선 개수만큼 for문을 수행 */
	for (int i = 0; i < contours.size(); i++) {
		Scalar c(rand() & 255, rand() & 255, rand() & 255); // contours에 저장된 각각의 외곽선을 임의의 색상으로 그림
		drawContours(dst, contours, i, c, 5);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

/* 계층 구조를 사용하는 외곽선 검출과 그리기 */
void contours_hier()
{
	/* RETR_CCOMP모드를 사용. 외곽선 검출 및 계층 구조 정보를 활용하여 외곽선을 그림 */
	Mat src = imread("contours.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	/* findContours함수 호출 시 hierarchy인자를 전달하여 계층정보를 받아옴 */
	/* src 영상으로부터 모든 외곽선을 검출하여 contours변수에 저장. */
	/* RETR_CCOMP모드를 사용하여 2단계로 구성된 계층 구조가 만들어짐. 392p 참고 */
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(src, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	/* 0번 외곽선부터 시작하여 계층 정보의 다음 외곽선으로 이동하면서 for문을 수행 */
	/* 변수 idx의 초기값은 0이고, idx = hierarchy[idx][0]코드를 이용하여 idx값이 갱신됨 */
	/* 여기서 hierarchy[idx][0]은 idx번에 해당하는 외곽선의 다음 외곽선 번호를 가리킴 */
	/* 모두 3회 반복됨. 색상이 3개 있다는 것으로 모두 3회 반복됨을 추측(즉, 계층 구조가 3개 있음) */
	for (int idx = 0; idx >= 0; idx = hierarchy[idx][0]) {
		Scalar c(rand() & 255, rand() & 255, rand() & 255); // contours에 저장된 각각의 외곽선을 임의의 색상으로 그림
		/*drawContours함수에 hierarchy정보를 전달하여 외곽선을 그리도록 함. 선의 두께를 -1로 지정하였으므로 외곽선 내부를 지정한 색깔로 채움 */
		drawContours(dst, contours, idx, c, -1, LINE_8, hierarchy); 
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

#if 1
int main()
{
	contours_basic();
	//contours_hier();

	return 0;
}
#endif

/* 외곽선 처리 함수 */
/* 외곽선 검출 후 외곽선 좌표 정보를 이용하는 여러 함수 사용법. 
   외곽선 정보로부터 객체의 위치와 크기 등 정보를 알아낼 수 있는 몇 가지 함수들 
   주어진 외곽선 점들을 감싸는 가장 작은 크기의 사각형, 즉 바운딩 박스를 구하는 함수는 boundingRect(points)함수 
   points = 입력 점들의 집합으로 vector<Point> or Mat 타입임 
   connectComponentsWithStats()함수를 이용해도 구할 수 있으나 외곽선 정보를 가지고 있는 경우에는 boundingRect가 효율적 
   
   외곽선 또는 점들을 감싸는 최소 크기의 회전된 사각형을 구할 때는 minAreaRect(points)함수를 사용 
   특정 외곽선을 감싸는 가장 작은 면적의 사각형 정보를 반환하는 함수. RotatedRect클래스 객체를 반환 
   
   외곽선 또는 점들을 감싸는 최소 크기의 원을 구하고 싶을 떄는 minEnclosingCircle(points, center, radius)함수 사용
   
   임의의 곡선을 형성하는 점들의 집합을 가지고 있을 때, 해당 곡선의 길이를 구하고 싶다면 arcLength(curve, bool closed)함수 사용 
   curve = 입력 곡선, closed = 폐곡선 여부. (true이면 폐곡선있음. false면 없음) 
   
   임의의 외곽선 정보를 가지고 있을 때, 외곽선이 감싸는 영역의 면적을 알고 싶다면 contourArea(contour, oriented = false) 함수 사용 
   contour = 입력 곡선, oriented = 진행 방향 정보 사용 여부. true이면 진행 방향에 따라 면적의 부호가 달라짐. false면 절대값 면적 반환 
   
   외곽선 또는 곡선을 근사화하는 approxPolyDP(curve, approxCurve, epsilon, closed) 함수 사용 
   주어진 곡선의 형태를 단순화하여 작은 개수의 점으로 구성된 곡선을 생성함 
   curve = 입력 2차원 점들의 좌표. approxCurve = 출력 근사화된 점들의 좌표 
   epsilon = 근사화 정밀도 파라미터. 입력 곡선과 근사화된 곡선까지의 최대 거리를 지정 
   더글라스-포이커 알고리즘을 사용하여 곡선 또는 다각형을 단순화 시킴 399p 참고 */

/* setLabel 함수는 img영상에서 pts 외곽선 주변에 바운딩 박스를 그리고 label 문자열을 출력함 */
void setLabel(Mat& img, const vector<Point>& pts, const String& label)
{
	Rect rc = boundingRect(pts); // pts 외곽선을 감싸는 바운딩 박스를 구함 
	rectangle(img, rc, Scalar(0, 0, 255), 1); // 바운딩 박스를 빨간색으로 구함 
	putText(img, label, rc.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255)); // 바운딩 박스 좌측 상단에 label문자열을 출력
}
#if 0
int main(int argc, char* argv[])
{
	Mat img = imread("polygon.bmp", IMREAD_COLOR);

	if (img.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	Mat bin;
	threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);

	/* bin 영상에서 모든 객체의 바깥쪽 외곽선을 검출함 */
	vector<vector<Point>> contours;
	findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	/* 검출된 각 객체의 외곽선 좌표를 pts변수로 참조하면서 for문을 수행 */
	for (vector<Point>& pts : contours) {
		if (contourArea(pts) < 400) /* 외곽선이 감싸는 면적이 400보다 작으면 잡음으로 간주하여 무시함*/
			continue;

		/* pts외곽선을 근사화하여 approx변수에 저장 */
		vector<Point> approx;
		approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);

		int vtc = (int)approx.size(); // approx변수에 저장된 외곽선 점의 개수를 vtc에 저장

		/* 근사화된 외곽선의 꼭지점 개수가 3개이면 외곽선 주변에 바운딩 박스를 그리고 TRI 문자열을 출력 */
		if (vtc == 3) {
			setLabel(img, pts, "TRI");
		}
		else if (vtc == 4) { /* 근사화된 외곽선의 꼭지점 개수가 4개이면 외곽선 주변에 바운딩 박스를 그리고 RECT 문자열을 출력 */
			setLabel(img, pts, "RECT");
		}
		else if (vtc > 4) { /* 객체의 면적 대 길이 비율을 조사하여 원에 가까우면 외곽선 주변에 바운딩 박스를 그리고 CIR 문자열을 출력 */
			double len = arcLength(pts, true); // pts는 각 객체의 외곽선 좌표가 저장된 vector<Point> 객체
			double area = contourArea(pts);
			double ratio = 4. * CV_PI * area / (len * len);

			if (ratio > 0.8) { // ratio가 1에 가까울수록 원 모양에 가까움.
				setLabel(img, pts, "CIR");
			}
		}
	}

	imshow("img", img);

	waitKey();
	destroyAllWindows();
	return 0;
}
#endif