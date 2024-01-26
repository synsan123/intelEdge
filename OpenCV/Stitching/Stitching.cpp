/* ���� �̾� ���̱� */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* �������ϸ� ������ �ȵ�. ����Ǿ��ִ� ������ ���� x64 -> Debug���� ��� ������ �� cmd �Ѱ� D: �Է� -> cd ������ Ŭ��
   Stitching.exe img1.jpg img2.jpg img3.jpg ��� �Է��ؾ� ��. �߿��� ���� img���ϵ��� Debug ������ �־�� �� */

/* ���� �̾� ���̱�� ���� ���� ������ ���� �̾� �ٿ��� �ϳ��� ū ������ ����� ���
   ���� �̾� ���̱�� ������� ������ �ĳ�� �����̶�� �θ�
   ���� �̾� ���̱⿡�� �Է����� ����� ������ ���� ���� ���� �̻����� ��ġ�� ������ �����ؾ� �ϸ�,
   ���� ���� ��ġ�� �а��� �� �ֵ��� ��ȿ�� Ư¡���� ���� �־�� �Ѵ�.

   ���� �̾� ���̱⸦ �����Ϸ��� �Է� ���󿡼� Ư¡���� �����ϰ�, ���� ��Ī�� �����Ͽ� ȣ��׷��Ǹ� ���ؾ� �Ѵ�.
   ������ ȣ��׷��� ����� ������� �Է� ������ �����Ͽ� ���� �̾� ���̴� �۾��� ����
   ������ �̾� ���� ����� �ڿ������� ���̵��� �̾� ���� ������ ��⸦ �����ϰ� �����ϴ� ���� ó���� �ؾ� ��
   �̷��� �Ϸ��� ���� �̾���̱� �۾��� �����ϴ� Stitcher Ŭ������ ����

   Stitcher Ŭ������ �̿��Ͽ� ���� ���� ������ �̾� ���̷��� ��ü ���� ����.
   Stitcher::create(mode);
   mode = Stitcher::PANORAMA or Stitcher::SCANS�� ����. ��ȯ���� Stitcher��ü�� �����ϴ� Ptr ����Ʈ ������ ��ü
   mode ��������. ��ĳ�� ������ ��ĵ�� ���� ���� ������ �̾� ���̷��� SCANS�� ����
   PANORAMA ���� �Է� ������� ���� ���� ��ȯ(�Ǵ� ȣ��׷���) ���迡 �ִٰ� �����ϰ�,
   SCANS ���� �Է� ������� ���� ������ ��ȯ ������ ����

   ��ü ���� ��, ������ ������ �̾� ���̴� �۾��� Stitcher::stitch(images, pano)�Լ��� ���
   �ټ��� ������ �Է����� �ް�, �̾� ���� ��� ������ ��ȯ��
   images = �Է� ������ ����. vector<Mat>Ÿ���� ���. pano = ��� �ĳ�� ����.
   ��ȯ�� = �Լ� ���� ��� �ڵ�. �� ���� Stitcher::Status::OK�̸� ���� ������ �ǹ�
   �� �Լ��� imgages�� ���Ե� �Է� ���󿡼� ORB Ư¡���� ã�� ���� ��Ī�ϰ� ȣ��׷��� ����� ���
   ȣ��׷��� ����� �̿��Ͽ� ������ ������ �����ϰ� ���� ��ȯ�ϰ�, ���� �̾� ���� �κ��� ��⸦ �����ϰ� ������ ��� ���� pano�� ��ȯ*/

int main(int argc, char* argv[])
{
	/* ����� ���� ������ 3���� ������ ���α׷� ������ �ܼ� â�� ����ϰ� ���α׷��� ����*/
	if (argc < 3) {
		cerr << "Usage: stitching.exe <image_file1> <image_file2> [<image_file3>...]" << endl;
		return -1;
	}

	/* ����� ���ڷ� ���޵� ���� ������ ���� �ҷ��ͼ� vector<Mat>Ÿ���� ���� imgs�� �߰�
	   ���������� �ҷ����� ���ϸ� ���� �޽��� ��� */
	vector<Mat> imgs;
	for (int i = 1; i < argc; i++) {
		Mat img = imread(argv[i]);

		if (img.empty()) {
			cerr << "Image Fail" << endl;
			return -1;
		}

		imgs.push_back(img);
	}

	/* Stitcher ��ü�� ���� */
	Ptr<Stitcher> stitcher = Stitcher::create();

	/* imgs�� ����� �Է� ������ �̾� �ٿ��� ��� ���� dst�� ���� */
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


