/* 영상 이어 붙이기 */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* 컴파일하면 실행이 안됨. 저장되어있는 폴더로 가서 x64 -> Debug에서 경로 복사한 후 cmd 켜고 D: 입력 -> cd 오른쪽 클릭
   Stitching.exe img1.jpg img2.jpg img3.jpg 라고 입력해야 함. 중요한 것은 img파일들이 Debug 폴더에 있어야 함 */

/* 영상 이어 붙이기는 여러 장의 영상을 서로 이어 붙여서 하나의 큰 영상을 만드는 기법
   영상 이어 붙이기로 만들어진 영상을 파노라마 영상이라고 부름
   영상 이어 붙이기에서 입력으로 사용할 영상은 서로 일정 비율 이상으로 겹치는 영역이 존재해야 하며,
   서로 같은 위치를 분간할 수 있도록 유효한 특징점이 많이 있어야 한다.

   영상 이어 붙이기를 수행하려면 입력 영상에서 특징점을 검출하고, 서로 매칭을 수행하여 호모그래피를 구해야 한다.
   구해진 호모그래피 행렬을 기반으로 입력 영상을 변형하여 서로 이어 붙이는 작업을 수행
   영상을 이어 붙인 결과가 자연스럽게 보이도록 이어 붙인 영상의 밝기를 적절하게 보정하는 블렌딩 처리도 해야 함
   이러한 일련의 영상 이어붙이기 작업을 수행하는 Stitcher 클래스를 제공

   Stitcher 클래스를 이용하여 여러 장의 영상을 이어 붙이려면 객체 생성 먼저.
   Stitcher::create(mode);
   mode = Stitcher::PANORAMA or Stitcher::SCANS를 지정. 반환값은 Stitcher객체를 참조하는 Ptr 스마트 포인터 객체
   mode 생략가능. 스캐너 등으로 스캔한 여러 장의 영상을 이어 붙이려면 SCANS로 지정
   PANORAMA 모드는 입력 영상들이 서로 투시 변환(또는 호모그래피) 관계에 있다고 가정하고,
   SCANS 모드는 입력 영상들이 서로 어파인 변환 관계라고 간주

   객체 생성 후, 영상을 실제로 이어 붙이는 작업은 Stitcher::stitch(images, pano)함수가 담당
   다수의 영상을 입력으로 받고, 이어 붙인 결과 영상을 반환함
   images = 입력 영상의 벡터. vector<Mat>타입을 사용. pano = 출력 파노라마 영상.
   반환값 = 함수 동작 결과 코드. 이 값이 Stitcher::Status::OK이면 정상 동작을 의미
   이 함수는 imgages에 포함된 입력 영상에서 ORB 특징점을 찾아 서로 매칭하고 호모그래피 행렬을 계산
   호모그래피 행렬을 이용하여 인접한 영상을 적절하게 투시 변환하고, 서로 이어 붙인 부분의 밝기를 적절하게 보정한 결과 영상 pano를 반환*/

int main(int argc, char* argv[])
{
	/* 명령행 인자 개수가 3보다 작으면 프로그램 사용법을 콘솔 창에 출력하고 프로그램을 종료*/
	if (argc < 3) {
		cerr << "Usage: stitching.exe <image_file1> <image_file2> [<image_file3>...]" << endl;
		return -1;
	}

	/* 명령행 인자로 전달된 영상 파일을 각각 불러와서 vector<Mat>타입의 변수 imgs에 추가
	   영상파일을 불러오지 못하면 에러 메시지 출력 */
	vector<Mat> imgs;
	for (int i = 1; i < argc; i++) {
		Mat img = imread(argv[i]);

		if (img.empty()) {
			cerr << "Image Fail" << endl;
			return -1;
		}

		imgs.push_back(img);
	}

	/* Stitcher 객체를 생성 */
	Ptr<Stitcher> stitcher = Stitcher::create();

	/* imgs에 저장된 입력 영상을 이어 붙여서 결과 영상 dst를 생성 */
	Mat dst;
	Stitcher::Status status = stitcher->stitch(imgs, dst);

	if (status != Stitcher::Status::OK) {
		cerr << "Error on Stitching" << endl;
		return -1;
	}

	imwrite("result.jpg", dst);

	imshow("dst", dst);

	waitKey();
	destroyAllWindows();

	return 0;
}


