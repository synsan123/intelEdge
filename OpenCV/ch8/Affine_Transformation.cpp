/* ������ ��ȯ */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* ������ ������ ��ȯ ���� */
void affine_transform()
{
	/* ������ ���� �̵�, Ȯ�� �� ���, ȸ�� ���� �������� ���� �� �ִ� �������� ��ȯ */
	/* ������ �������� ��ȯ = ������ �����ϴ� �ȼ��� ��ġ ������ ���������ν� ��ü ������ ����� �ٲٴ� �۾� */
	/* �ȼ� ���� �״�� �����ϵ� ��ġ�� �����ϴ� �۾� */
	/* 2 x 3 �Ǽ��� ��� �ϳ��� ������ ��ȯ�� ǥ���� �� ���� */
	/* �ּ� �� ���� �̵� ���踦 �˾ƾ� ��. �˰� �ִٸ� 6���� ���ҷ� ���ǵ� ������ ��ȯ ����� ���� �� ���� */
	/* getAffineTransform() = ������ ��ȯ ����� ���ϴ� �Լ� */
	/* getAffineTransform(src, dst) or (src[], dst[]) => ���� �Է�, ��¿��� �� ���� ��ǥ */
	/* src�� dst���� ũ�Ⱑ 3�� Point2f�迭 �Ǵ� vector<Point2f>�ڷ��� ���� ��� ���� */
	/* ���� �Լ��� ��ȯ�ϴ� Mat��ü�� CV_64FC1Ÿ���� ����ϴ� 2x3ũ���� ������ ��ȯ ��� */

	/* ������ ��ȯ ����� ������ ���� ��, ������ ������ ��ȯ�� ��� ������ �����Ϸ��� warpAffine�Լ� ��� */
	/* wrapAffine(src, dst, M, dsize, flags, borderMode, borderValue) */
	/* M = 2x3 ������ ��ȯ ���, dsize = ��� ���� ũ��, flags = ������ �˰���(279p ����) */
	/* M�� CV_32FC1 or CV_64FC1 Ÿ���̾�� �ϰ�, ũ��� 2x3�̾�� ��. */
	/* dsize�� Size()�� �����ϸ� �Է� ����� ���� ũ���� ��� ������ ���� */

	Mat src = imread("tekapo.bmp");  //GrayScale �̳� Color�� �����ϰ� ����Ǳ� ������ �÷��� ��.

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Point2f srcPts[3], dstPts[3]; // �� �� ��ǥ�� ������ �迭�� ����
	srcPts[0] = Point2f(0, 0);    // �Է� ������ ���� ���, ���� ���, ���� �ϴ��� ��ǥ�� ����
	srcPts[1] = Point2f(src.cols - 1, 0); // 639, 0
	srcPts[2] = Point2f(src.cols - 1, src.rows -1); // 639, 479
	dstPts[0] = Point2f(50, 50);  // srcPts ������ �̵��� ��ǥ�� ����
	dstPts[1] = Point2f(src.cols - 100, 100);
	dstPts[2] = Point2f(src.cols - 50, src.rows - 50);

	Mat M = getAffineTransform(srcPts, dstPts); // ������ ��ȯ ��� ����

	/* ������ ����� ������ ���� ��, �Ϻ� ������ ��� ��ġ�� �̵��ϴ����� �˰� �ʹٸ� transform() �Լ��� �̿� */
	/* transform(src,dst,m) */
	/* (100, 20), (200, 50)�� ������ ��ȯ ��Ŀ� ���� �̵��ϴ� ��ġ�� �˰� �ʹٸ� */
	/* vector<Point2f> src = { Point2f(100,20), Point2f(200, 50) } */
	/* vector<Point2f> dst */
	/* transform(src, dst, m) ���� �ۼ��Ѵ�. */

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void affine_translation() // �̵� ��ȯ (x,y) -> (x',y')�� ����
{
	/* ������ ����� �ʿ� */
	/* [ 1 0 a ] */
	/* [ 0 1 b ] */
	/* ���� ���� 2x3 ������ ����� �ʿ�� ��, (a, b) ��ŭ �̵����� (x', y')�� ���� */
	Mat src = imread("tekapo.bmp");  //GrayScale �̳� Color�� �����ϰ� ����Ǳ� ������ �÷��� ��.

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Mat M = Mat_<double>({ 2,3 }, { 1,0,150,0,1,100 }); // ������ ���

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();

}

void affine_shear() // ���� ��ȯ
{
	/* ���簢�� ������ ������ ���� �������� �о ����纯�� ������� �����Ǵ� ��ȯ, ���и� ��ȯ�̶�� �� */
	/* ���� ����, ���� �������� ������ �� ���� */
	/* ���� ��ȯ�� ������ ���� ��ȯ�� ���� �̵����� �ʰ� �״�� ������ �ӹ� */
	/* y��ǥ�� �����Կ� ���� ������ ���η� �̵� x' = x + mxy */
	/* x��ǥ�� �����Կ� ���� ������ ���η� �̵� y' = y + myx */
	/* m�� ���� ���ι���� ���ι������� �и� ������ ��Ÿ���� �Ǽ� */
	/* [ 1 mx 0 ]   [ 1 0  0 ] */
	/* [ 0 1  0 ]   [ m 1y 0 ] */
	/* ���� ���� ���� ������ ��ȯ ����� ���� */
	Mat src = imread("tekapo.bmp");  

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	double mx = 0.3;
	Mat M = Mat_<double>({ 2,3 }, { 1,mx,0,0,1,0 }); // ������ ���

	Mat dst;
	/* ���� ��ȯ�� ���� �Է� ������ �Ϻΰ� �߸��� �ʵ��� ��� ���� ���� ũ�⸦ cvRound(src.cols + src.rows*mx)���·� ���� */
	warpAffine(src, dst, M, Size(cvRound(src.cols + src.rows*mx), src.rows));

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void affine_scale() // ũ�� ��ȯ
{
	/* ������ ��ü���� ũ�⸦ Ȯ�� �Ǵ� ����ϴ� ��ȯ */
	/* sx(x�� ũ�� ����) = w' / w or x' / x */
	/* sy(y�� ũ�� ����) = h' / h or y' / y */
	/* s > 1�̸� ������ Ȯ��, s < 1�̸� ������ ��� */
	/* ������ ��ȯ ����� �Ʒ��� ���� */
	/* [ sx 0  0 ] */
	/* [ 0  sy 0 ] */
	/* ������ ��ȯ���� ũ�� ��ȯ ���� �ʰ� resize�Լ��� �̿��ؼ��� ������ */
	/* resize(src, dst, dsize, fx, fy, interpolation), f = �� ���������� ũ�� ��ȯ ����. dsize�� Size()�� ������ ��쿡�� ��� */
	
	/* 480x320ũ���� ��� ������ �پ��� ���������� Ȯ���ϰ� ��� ������ �Ϻθ� ȭ�鿡 ����ϴ� ���� */
	Mat src = imread("rose.bmp");

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}
	
	Mat dst1, dst2, dst3, dst4;
	resize(src, dst1, Size(), 4, 4, INTER_NEAREST); // x,y�������� 4�� Ȯ�� => (480 x 320) x 4 => 1920 x 1280�� ��
	resize(src, dst2, Size(1920, 1280)); // Default = INTER_LINEAR
	resize(src, dst3, Size(1920, 1280), 0, 0, INTER_CUBIC);
	resize(src, dst4, Size(1920, 1280), 0, 0, INTER_LANCZOS4);

	imshow("src", src);
	imshow("dst1", dst1(Rect(400, 500, 400, 400))); // (400, 500)��ǥ���� 400 x 400 ũ���� �κ� ������ ȭ�鿡 ��� 
	imshow("dst2", dst2(Rect(400, 500, 400, 400)));
	imshow("dst3", dst3(Rect(400, 500, 400, 400)));
	imshow("dst4", dst4(Rect(400, 500, 400, 400)));

	waitKey();
	destroyAllWindows();
}

void affine_rotation() // ȸ�� ��ȯ
{
	/* ȸ�� ��ȯ�� �ﰢ�Լ��� �̿��� */
	/* ������ ��ȯ ��� M�� */
	/* [ cos��Ÿ sin��Ÿ   0 ] */
	/* [ -sin��Ÿ cos��Ÿ  0 ] */
	/* ���� ȸ���� ���� ������ ��ȯ ����� �����ϴ� getRotationMatrix2D�Լ��� ���� */
	/* getRotationMatrix2D(center, angle(����� �ݽð�, ������ �ð� ���� ȸ��), scale), scale = ȸ�� �� �߰������� Ȯ�� �Ǵ� ����� ����. ���� 1 */

	/* 90�� ������ ȸ���ϰ� ���� ��쿡�� rotate()�Լ��� ��� */
	/* rotate(src, dst, rotateCode) rotateCode = ȸ�� ���� ���� �÷����� 294p ���� (3�� ����)*/

	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Point2f cp(src.cols / 2.f, src.rows / 2.f); // ������ �߽� ��ǥ(center Point)
	Mat M = getRotationMatrix2D(cp, 20, 1);

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void affine_flip() // ��Ī ��ȯ 
{
	/* ���� ��Ī �Ǵ� ���� ����, �¿� ��Ī �Ǵ� �¿� ���� */
	/* �Է� ����� ���� ũ���� ��� ������ �����ϸ�, �Է� ������ �ȼ��� ��� ������ �ȼ��� �ϴ��Ϸ� �����ǹǷ� �������� �ʿ���� */
	/* flip(src, dst, flipCode) flipCode = ��Ī ��� �÷��� */
	/* ����� �¿� ��Ī, 0�̸� ���� ��Ī, �����̸� �¿���� ��Ī�� ����, (1, 0 ,-1) �߿� �����ϸ� �� */

	Mat src = imread("eastsea.bmp");

	if (src.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	imshow("src", src);

	Mat dst;
	int flipCode[] = { 1, 0, -1 };
	for (int i = 0; i < 3; i++) {
		flip(src, dst, flipCode[i]);

		String desc = format("flipCode : %d", flipCode[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SCRIPT_SIMPLEX, 1.0, Scalar(255, 0, 0), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}

int main()
{
	//affine_transform(); // ������ ��ȯ 
	//affine_translation(); // �̵� ��ȯ 
	//affine_shear(); // ���� ��ȯ
	//affine_scale(); // ũ�� ��ȯ
	//affine_rotation(); // ȸ�� ��ȯ
	affine_flip(); // ��Ī ��ȯ 
	return 0;
}