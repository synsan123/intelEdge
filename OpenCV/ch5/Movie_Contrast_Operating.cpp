/* 영상의 명암비 조절 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;


#if 0
int main()
{
	/* 명암비란? */
	/* 밝은 영역과 어두운 영역 사이에 드러나는 밝기 차이의 강도를 의미 */
	/* 밝은 영역과 어두운 영역이 골고루 있으면 명암비가 높다라고 함. 어느 한쪽에 치우쳐있으면 낮다고 함. */
	/* 명암비는 곱셈 연산을 사용하여 구현 */
	/* 실제로 일정 상수를 곱하는 방법은 잘 사용 안 함. 오히려 명암비가 나빠지고 사물의 윤곽을 구분하는 것이 좋지 않아서 */
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	float s = 2.f;
	Mat dst = s * src;

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();

	return 0;
}
#endif

int main()
{
	/* 효과적인 명암비 조절 방법 */
	/* dst(x,y) = saturate(src(x,y) + (src(x,y)-128)*a) */ // 128을 기준으로 
	/* 반드시 (128, 128)를 지나고 -1<= a <= 0이면 명암비를 감소. a > 0이면 명암비를 증가 */
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Fail" << endl;
		return -1;
	}

	float alpha = 1.f;
	Mat dst = src + (src - 128) * alpha;

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();

	return 0;
}