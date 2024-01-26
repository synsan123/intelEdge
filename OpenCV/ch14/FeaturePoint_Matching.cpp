/* Ư¡�� ��Ī */
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

/* �� ���� ���󿡼� ������ Ư¡�� ����ڸ� ���Ͽ� ���� ����� Ư¡���� ã�� Ư¡�� ��Ī 
   ũ�� �Һ� Ư¡�����κ��� ���� ����ڸ� ��Ī�ϸ� ũ��� ȸ���� ������ ���� ��Ī�� ������ �� ���� 
   Ư¡�� ��Ī ������ ������ �� ����ϴ� DMatch Ŭ����.
   DMatch Ŭ������ �� ���� ���󿡼� ������ Ư¡���� �ٸ� �� ���� ���� �Ǵ� ���� ���󿡼� ������ Ư¡�� ������ ��Ī ������ ǥ���� �� ����
   DMatch Ŭ���� ��� ����
   queryIdx = ���� ����� ��ȣ. trainIdx = �Ʒ� ����� ��ȣ. imgIdx = �Ʒ� ���� ��ȣ(���� ���� ������ �Ʒ� �������� ������ ��쿡 ���)
   distance = �� ����� ������ �Ÿ�. < ������ ������ = distance ���� ���� �̿��Ͽ� ũ�⸦ �� 
   
   distance = �� Ű����Ʈ ����ڰ� �󸶳� ���̰� �������� ��Ÿ���� ��Ī ô���� ����.
   �� Ư¡���� ���� �����ϸ� 0�� ������, ���� �ٸ� Ư¡���̸� ���� ũ�� ��Ÿ��.
   ������ ������ ��Ŭ���� �Ÿ��� �̿��Ͽ� �ַ� ����ϸ�, �ٸ� ���� ����ڳ��� ���ϴ� ��쿡�� �ع� �Ÿ��� ���
   DMatch Ŭ���� ��ü�� ����ڰ� ���� �������� �ʰ�, Ư¡�� ��Ī �˰��� ���ο��� �����Ͽ� ����ڿ��� ��ȯ�� 
   
   Ư¡�� ��Ī Ŭ������ DescriptorMatcher Ŭ������ ��ӹ޾� �������. 
   DescriptorMatcher Ŭ������ match, knnMatch, radiusMatch���� ���� ��� �Լ��� ������ �ִ� �߻�Ŭ�����̸�,
   DescriptorMatcher Ŭ������ ��ӹ��� BFMatcher Ŭ������ FlannBasedMatcher Ŭ������ �̵� ��� �Լ� ����� ������ �����ϵ��� �����
   match�Լ��� ���� ����� ����� ���� �ϳ� ã��, knnMatch�Լ��� ����� ����� �� k���� ã��
   radiusMatch�� ������ �Ÿ� �ݰ� �ȿ� �ִ� ����� ���� ��� ã�� ��ȯ�� 
   
   BFMatcherŬ������ �������� ��Ī�� ������. ���� ����� ���տ� �ִ� ��� ����ڿ� �Ʒ� ����� ���տ� �ִ� ��� ����� ������ �Ÿ��� ����ϰ�,
   �� �� ���� �Ÿ��� ���� ����ڸ� ã�� ��Ī�ϴ� ���
   ��Ī ���� ����� �ſ� ������������ Ư¡�� ������ �þ���� �Ÿ� ���Ƚ���� �ް��ϰ� �þ �� �ִٴ� ������ ����
   ���� ��� ù ���� ���� 1000�� Ư¡��, �� ��° ���� 2000�� Ư¡���� ������ �� 2,000,000�� �񱳿����� ����
   
   �׷��Ƿ� FlannBasedMatcher Ŭ������ ����ϴ� ���� ȿ����. Flann�� �ٻ�ȸ�� �ֱٹ� �̿� �˰����� ������ ������ ���̺귯����
   FlannBasedMatcher Ŭ������ Flann���̺귯���� �̿��Ͽ� ������ ��Ī�� �����ϴ� Ŭ����
   FlannBasedMatcher Ŭ������ �ٻ�ȸ�� �Ÿ� ��� ����� ����ϹǷ� ���� �Ÿ��� ���� Ư¡���� ã�� ���� �� ������, �ſ� ������ ����
   �ٸ�, FlannBasedMatcher Ŭ������ �⺻������ L2 �븧 �Ÿ� ���� ����� ����ϹǷ� �ع� �Ÿ��� ����ϴ� ���� ����ڿ� ���ؼ��� ��� �� ��
   
   �� �� Ŭ������ ��ü�� �����Ϸ��� creat ���� ��� �Լ��� ����ؾ���
   BFMatcher::create(normType, crossCheck)
   normType = ����� �Ÿ� ���� ���. NORM_L1, NORM_L2, NORM_HAMMING, NORM_HAMMING2 �� �ϳ��� ����
   crossCheck = �� ���� true�̸� i��° ���� ����ڿ� ���� ������ �Ʒ� ����ڰ� j�̰� j���� �Ʒ� ����ڿ� ���� ������
   ���� ����ڰ� i�� ��쿡�� ��Ī ����� ��ȯ�� 
   ��ȯ�� = BFMatcher ��ü�� �����ϴ� Ptr ����Ʈ ������ ��ü 
   ORB, BRIEF, AKAZE �˰���ó�� ���� ����ڸ� ����ϴ� ��쿡�� NORM_HAMMIN�÷��׸� �����ؾ���. 
   ���� ORB����ڿ��� WTA_K�� 3 or 4�� ������ ��쿡�� NORM_HAMMING2�� ����
   
   FlannBasedMatcher::creat()
   ��ȯ�� = FlannBasedMatcher ��ü�� �����ϴ� Ptr ����Ʈ ������ ��ü 
   
   Ptr<DescriptorMatcher> matcher = BFMatcher::create();
   ���� Ptr<BFMatcher> Ÿ���� ��ȯ������, DescriptorMatcherŬ������ �θ� Ŭ�����̱� ������ matcher ��ü�� Ptr<DescriptorMatcher>Ÿ������ ����
   ���ڸ� �������� ������ NORM_L2���. ���� ����ڸ� �����ϴ� ��쿡�� �عְŸ� ���
   Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING); 
   
   ��ü�� ������ �Ŀ��� �� �Է� ���󿡼� ������ ����� ��� ������ ��Ī�� ������ �� ���� 
   ���� ��� ù ��° ���󿡼� ������ Ư¡�� ����� ����� desc1�̰� �� ��° ���󿡼� ������ Ư¡�� ����� ����� desc2�� ���
   vector<DMatch> matches;
   matcher->match(desc1,desc2,matches); �ڵ�� ��Ī�� ������ �� ���� 
   
   DescripotrMatcher::matche()�Լ��� desc1�� ���Ե� ������ ����ڿ� ���� ������ ����ڸ� desc2���� ã��, �� ����� vector<DMatch>Ÿ����
   ���� matches�� ������
   DescripotrMatcher::matche(queryDescriptors, trainDescriptors, matches, mask)
   1. ���� ����� ����. 2. �Ʒ� ����� ����. 3 ��Ī ���.
   4. ���� ��Ī ������ ���� ����ڿ� �Ʒ� ����ڸ� ������ �� ���. �� ������ ���� ����� ������ ���ƾ� �ϰ�, ���� ������ �Ʒ� ����� ������ ���ƾ� ��
   ���� mask.at<uchar>(i,j)���� 0�̸� queryDescriptors[i]�� trainDescriptors[j]�� ��Ī�� �� ����.
   noArray()�� �����ϸ� ��� ������ ��Ī�� ã��
   �� �Լ��� queryDescriptors�� ����� ������ ����ڿ� ���� ���� ������ ����ڸ� trainDescriptors���� ã��.
   ������ ��Ī ����� ���� DMatch::queryIdx���� queryDescriptors�� ��ȣ�� ����ǰ�, DMatch::trainIdx���� trainDescriptors�� ��ȣ�� �����
   mask���ڸ� �������� �ʴ� ���, ��Ī ����� ����Ǵ� matches���� queryDescriptors ����� ������ ���� ���� DMatch ��ü�� �����
   
   �־��� ���� ����ڿ� ���� k���� ������ �Ʒ� ����ڸ� ã�� ��ȯ�ϴ� DescripotrMatcher::knnMatch�Լ���
   ������ �Ÿ����� ���� �Ÿ��� ã�� �Ʒ� ����ڸ� ��� ã�� ��ȯ�ϴ� DescripotrMatcher::radiusMatch�Լ��� OPENCV���� ����Ʈ ���� 
   
   �� ���󿡼� ������ Ư¡���� ��Ī ����� �Ѵ��� Ȯ���� �� �ֵ��� ��Ī ��� ���� ���� ����� ������ 
   drawMatches�Լ��� �� ��Ī �Է� ������ ���η� �̾� ���̰�, �� ���󿡼� ������ Ư¡���� ��Ī ����� �پ��� �������� ǥ���� ��� ������ ����
   drawMatches(img1, keypoints1, img2, keypoints2, mathces1to2, outImg, matchColor, singlePointColor, matchesMask, flags)
   matches1to2 = ù ��° �Է� ���󿡼� �� ��° �Է� ���������� ��Ī ����
   outImg = ��� ����
   matchColor = ��Ī�� Ư¡���� ���� ����. Scalar::all(-1)�� �����ϸ� ������ �������� �׸�
   singlePointColor = ��Ī���� ���� Ư¡�� ����. Scalar::all(-1)�� �����ϸ� ������ �������� �׸�
   matchesMask = ��Ī ������ �����Ͽ� �׸� �� ����� ����ũ. std::vector<char>()�� �����ϸ� ��� ��Ī ����� �׸�
   flags = ��Ī ���� �׸��� ���. DrawMatchesFlags ������ ����� ���� 448p ����
   �� �Լ��� 2���� �Է� ������ ���η� �̾� ���̰�, �� ���� ������ Ư¡�� ��Ī ����� �������� �׸� ��� ���� outimg�� ��ȯ 
   �� �Է� ���� ������ ��Ī ������ matches1to2���ڷ� ������. */


/* box ���󿡼� ������ ��� Ư¡�� ����ڿ� ���� ���� ������ box_in_scene������ Ư¡�� ����ڸ� ã�� ������ �׷ȱ� ������
   ��Ī ����� �ſ� �����ϰ� ��Ÿ����, box_in_scene ���󿡼� ����� �Ϻ� Ư¡���� ��Ī�� ���� �ʾ� ������ ����Ǿ� ���� ���� */
void keypoint_matching()
{
	Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Ptr<Feature2D> feature = ORB::create(); // ORB ��ü�� ����

	/* src1, src2 ���󿡼� ���� Ư¡���� �����ϰ� ����ڸ� �����. �� ������ ����ڴ� desc1, desc2��Ŀ� ����� */
	vector<KeyPoint> keypoints1, keypoints2;
	Mat desc1, desc2;
	feature->detectAndCompute(src1, Mat(), keypoints1, desc1);
	feature->detectAndCompute(src2, Mat(), keypoints2, desc2);

	/* BFMatcher Ŭ���� ��ü�� ����. ����� �Ÿ� ��� ����� �ع� �Ÿ��� ����� */
	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

	/* desc1, desc2 ����ڸ� ���� ��Ī�Ͽ� �� ����� matces�� ������ */
	vector<DMatch> matches;
	matcher->match(desc1, desc2, matches);

	/* matches ������ �̿��Ͽ� ��Ī ��� ���� dst�� ���� */
	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, matches, dst);

	imshow("src1", src1);
	imshow("src2", src2);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

/* box_in_scene ���󿡼��� box ���� ���� ���� �Ϻΰ� ������ �ֱ� ������ box���󿡼� ������ Ư¡���� ��� ����� ��Ī�ǱⰡ ����� 
   ������ ���� �ʴ��� �������� ������ ���� ��ȭ�� ���� �Ϻ��� ��Ī�� ���� �Ұ���. ��Ī ��� �� ������ ������ �ٸ� Ư¡������ �߸� ��Ī��
   ��ü ��Ī ������� �߸� ��Ī�� ����� �����ϰ�, ����� ��Ī�Ǿ��ٰ� �ĳ��ϴ� ����� �����Ͽ� ����ؾ� ��
   
   DMatchŬ������ ����� ������ �Ÿ��� ǥ���ϴ� distance ��� ������ ������ ����. distance ���� �ʹ� ū ��Ī ����� �����ϰ�,
   ���� ���� ����� ����ϴ� ���� ����. 
   DMatchŬ������ �ε�ȣ �����ڿ� ���� �����ǰ� �Ǿ� �ְ�, �� ������ �����ǿ����� distance ���� ũ�⸦ ���ϱ� ������ DMatch ��ü��
   std::sort()�Լ��� �����ϸ� �ڵ����� distance���� �������� ������

   vector<DMatch> matches;
   matcher->match(desc1, desc2, matches);
   sort(matches.begin(), matches.end());
   vector<DMatch> good_matches(matches.begin(), matches.begin() + 50);
   ���� �ڵ�� �� ���󿡼� ������ ����� desc1�� desc2�� ��Ī�� ��, ��Ī ����� distance �� �������� �������� ����
   matches�� ����� DMatch��ü���� distance ���� ���� ������� ���ʿ� ��ġ�ϰ� ��
   �׷��Ƿ� ���ĵ� mathces���� ���� ��Ī ����� �����Ϸ��� ���� �ڵ� 4�������� �ۼ��ϸ� ��
   good_matches�������� ��ü ��Ī ��� matches �߿��� ��Ī�� �� �� 50���� ��Ī ����� ����� */

/* �ڵ带 �����ϸ� �� �Լ����� �ߵǴ� ���� �� �� ������ ������ ��� Ư¡���� box_in_scene���󿡼� ���� �ڽ� ��ġ�� �ƴ� 
   �ٸ� �������� ��Ī�Ǵ� ���� �� �� ����. ȣ��׷��ǿ� ���� ��Ī���� �Ϻ� ����Ȯ�� ��Ī ������ ���ԵǾ� �־
   box_in_scene���� box�� �ش��ϴ� ���� ���� ��ġ�� ��Ȯ�ϰ� ã�� ����� ���� ���� */
void good_matching()
{
	Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Ptr<Feature2D> feature = ORB::create(); // ORB ��ü�� ����

	/* src1, src2 ���󿡼� ���� Ư¡���� �����ϰ� ����ڸ� �����. �� ������ ����ڴ� desc1, desc2��Ŀ� ����� */
	vector<KeyPoint> keypoints1, keypoints2;
	Mat desc1, desc2;
	feature->detectAndCompute(src1, Mat(), keypoints1, desc1);
	feature->detectAndCompute(src2, Mat(), keypoints2, desc2);

	/* BFMatcher Ŭ���� ��ü�� ����. ����� �Ÿ� ��� ����� �ع� �Ÿ��� ����� */
	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

	/* desc1, desc2 ����ڸ� ���� ��Ī�Ͽ� �� ����� matces�� ������ */
	vector<DMatch> matches;
	matcher->match(desc1, desc2, matches);

	/* �� ������ Ư¡�� ��Ī ����� ������ 
	   ���ĵ� ��Ī ������� ���� 50�� ��Ī����� good_matches�� ������ */
	sort(matches.begin(), matches.end());
	vector<DMatch> good_matches(matches.begin(), matches.begin() + 50);

	/* good_matches�� �̿��Ͽ� ��Ī ��� ������ ����
	   drawMatches()�Լ��� 10��° ���� DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS ����� �����Ͽ�
	   ��Ī���� ���� Ư¡���� ȭ�鿡 ǥ������ ���� */
	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, good_matches, dst, Scalar::all(-1), Scalar::all(-1), vector<char>(),
		DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	imshow("src1", src1);
	imshow("src2", src2);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();

}

/* ȣ��׷��ǿ� ���� ��Ī */
/* Ư¡�� ��Ī ����κ��� �� ������ ȣ��׷��Ǹ� ����ϰ�, �̸� �̿��Ͽ� ũ�Ⱑ �ٸ��� ȸ���� �Ǿ� �ִ� ��ü�� ��Ȯ�ϰ� ��Ī�ϴ� ��� 
   ȣ��׷��Ǵ� 3���� �������� ����� ���� �ٸ� �������� �ٶ���� �� ȹ��Ǵ� ���� ������ ���踦 ��Ÿ���� ��� 
   ȣ��׷��Ǵ� ���������� �ϳ��� ����� �ٸ� ������� ���� ��ȯ�ϴ� �Ͱ� ���� ���迡 ���� 
   �������� ���� �������� ȣ��׷��Ǵ� ���� ��ȯ�� ���� ������ ȣ��׷��Ǵ� 3x3�Ǽ� ��ķ� ǥ���� �� ����
   ����, ���� ��ȯ�� ���� ���� ���������� �� ���� �����Ǵ� ���� ��ǥ �̵� ������ ������ ȣ��׷��� ����� ���� �� ���� 
   �׷��� Ư¡�� ��Ī �����κ��� ȣ��׷��Ǹ� ���ϴ� ��쿡�� ���� �����Ǵ� �� ������ �� ������ �ξ� ���� ������ �̷��� ��쿡�� 
   ���� ��ȯ �� ������ �ּҰ� �Ǵ� ������ ȣ��׷��� ����� ���ؾ� �� 
   
   �� ���� ��鿡�� ����� Ư¡�� ��Ī �����κ��� ȣ��׷��Ǹ� ����� �� ����� �� �ִ� �Լ� findHomograpyh
   findHomography(srcPoints, dstPoints, method =0,ransacReprojThreshol = 3, mask = noarray(), maxIters = 2000, confidence = 0.955) 
   1. ���� ������ �� ��ǥ, CV_32FC2 Ÿ���� Mat��ü �Ǵ� vector<Point2f> Ÿ���� ���� ���� 
   2. ��ǥ ������ �� ��ǥ, CV_32FC2 Ÿ���� Mat��ü �Ǵ� vector<Point2f> Ÿ���� ���� ����
   3. ȣ��׷��� ��� �����. 0 = ��� ��(�Է���, ����� ���)��/�� ����ϴ� �Ϲ����� ���(�ּ��ڽ¹�)
   LMEDS = �ּ� �޵�� ���� ���, RANSAC = RANSAC ���, RHO = PROSAC ���
   4. �ִ� ��� ������ ����, �� �� �̳��� Ư¡���� �������Ǵ� ��쿡�� ����ġ�� ������. RANSAC or RHO ��������� ��� 
   5. ȣ��׷��� ��꿡 ���� ������ �˷� �ִ� ��� ����ũ ���. LMEDS or RANSAC��������� ���
   6. RANSAC �ִ� �ݺ� Ƚ��
   7. �ŷڵ� ����. 0 ~ 1 ������ �Ǽ��� ����
   8. ��ȯ�� = CV_63FC1Ÿ���� 3x3ȣ��׷��� ����� ��ȯ
   
   �Ϲ������� Ư¡�� ��Ī ����κ��� ȣ��׷��Ǹ� ����� �� �ּ��ڽ¹��� ����ϸ� ȣ��׷��ǰ� ����� ������ ����
   �߸� ��Ī�� ����ó�� ������ ū �Է� ������ �̻�ġ��� �θ���, �̻�ġ�� ���� �����ϴ� ��쿡�� ȣ��׷��� ��� �����
   LMEDS, RANSAC, RHO ������� �����ϴ� ���� ����
   LMEDS �޼���� ���� �̻�ġ�� 50%������ ��쿡�� �ùٸ��� �۵���
   RANSAC or RHO ����� �̻�ġ�� 50%�̻� �����ϴ��� ȣ��׷��� ����� �� ã���ִ� ��
   RANSAC or RHO ����� ����� ��쿡�� srcPoints�� dstPoints�� ����� ���� �̻�ġ�� �ƴ϶�� �Ǵ��ϱ� ���� �Ӱ谪�� �����ؾ� �ϸ�,
   �� ���� ransacReprojThreshold ���ڷ� ������.
   ���� H * srcPointsi�� dstPointsi ������ �Ÿ��� ransacReprojThreshold���� ������ ����ġ�� ������
   
   RANSAC = RANdom SAmple Consensus �˰����� �̻�ġ�� ���Ե� �Է� �����ͷκ��� ������ �� �Ķ���͸� ȿ�������� �����ϴ� �˰���
   RANSAC �˰������� ȣ��׷��Ǹ� ����ϴ� ���, �ټ��� Ư¡�� ��Ī �����κ��� �� ���� �������� ���Ƿ� ������ 
   �� ������ ������ �̿��Ͽ� 3x3 ȣ��׷��� ����� ����ϰ�, ������ Ư¡�� ��Ī �� �߿��� ���� ���� ȣ��׷��� ��Ŀ� ���յǴ� ��Ī �� ������ ��
   �ٽ� ���Ƿ� �� ���� �������� �����ϰ�, ȣ��׷��� ��� ���� �ش� ȣ��׷��ǿ� ���յǴ� ��Ī �� ���� ���� �۾��� �ݺ���.
   �� �۾��� ���� �� �ݺ��� ��, ���� ���� ��Ī ���� ������ ���� ȣ��׷��� ����� ���� ȣ��׷��� ��ķ� �����ϴ� ����� RANSAC */

void find_homography()
{
	Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Fail" << endl;
		return;
	}

	Ptr<Feature2D> feature = ORB::create(); // ORB ��ü�� ����

	/* src1, src2 ���󿡼� ���� Ư¡���� �����ϰ� ����ڸ� �����. �� ������ ����ڴ� desc1, desc2��Ŀ� ����� */
	vector<KeyPoint> keypoints1, keypoints2;
	Mat desc1, desc2;
	feature->detectAndCompute(src1, Mat(), keypoints1, desc1);
	feature->detectAndCompute(src2, Mat(), keypoints2, desc2);

	/* BFMatcher Ŭ���� ��ü�� ����. ����� �Ÿ� ��� ����� �ع� �Ÿ��� ����� */
	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

	/* desc1, desc2 ����ڸ� ���� ��Ī�Ͽ� �� ����� matces�� ������ */
	vector<DMatch> matches;
	matcher->match(desc1, desc2, matches);

	/* �� ������ Ư¡�� ��Ī ����� ������
	   ���ĵ� ��Ī ������� ���� 50�� ��Ī����� good_matches�� ������ */
	sort(matches.begin(), matches.end());
	vector<DMatch> good_matches(matches.begin(), matches.begin() + 50);

	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, good_matches, dst, Scalar::all(-1), Scalar::all(-1), vector<char>(),
		DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	/* good_matches ��Ī ����� ����� ���� ����� �Ʒ� ������ Ư¡�� ��ǥ�� �����Ͽ� vector<Point2f>Ÿ���� ���� pts1,pts2�� ������ */
	vector<Point2f> pts1, pts2;
	for (size_t i = 0; i < good_matches.size(); i++) {
		pts1.push_back(keypoints1[good_matches[i].queryIdx].pt);
		pts2.push_back(keypoints2[good_matches[i].trainIdx].pt);
	}

	/* pts1������ pts2����� �̵��ϴ� ȣ��׷��� ����� ���Ͽ� H�� ����
	   ȣ��׷��� ��� ����� RANSAC �˰����� ����� */
	Mat H = findHomography(pts1, pts2, RANSAC);

	/* src1������ �� �𼭸� ���� corners1�� ������ ��, ȣ��׷��� ��� H�� �̿��Ͽ� �� ������ �̵��ϴ� ��ġ�� ����Ͽ� corners2�� ���� */
	vector<Point2f> corners1, corners2;
	corners1.push_back(Point2f(0, 0));
	corners1.push_back(Point2f(src1.cols - 1.f, 0));
	corners1.push_back(Point2f(src1.cols - 1.f, src1.rows - 1.f));
	corners1.push_back(Point2f(0, src1.rows - 1.f));
	perspectiveTransform(corners1, corners2, H);

	/* ��Ī ��� ���� dst���� corner2 ������ ��ġ�ϴ� ��ǥ�� corners_dst�� ������ */
	vector<Point> corners_dst;
	for (Point2f pt : corners2) {
		corners_dst.push_back(Point(cvRound(pt.x + src1.cols), cvRound(pt.y)));
	}

	/* ��Ī ��� ���� dst���� box���� ���� �ڽ��� �ִ� ��ġ�� ������� �簢���� �׸� */
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