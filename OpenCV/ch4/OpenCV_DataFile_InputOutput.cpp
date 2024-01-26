/* OpenCV ������ ���� ����� */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

String filename = "mydata.json"; // (readData()�Լ����� �Բ� ����ϱ� ���Ͽ�) ������ ���� �̸��� ���������� ����

int main()
{
	/* ������ ���� ������� FileStorage Ŭ������ ��� */
	/* �����͸� �����ϰų� �о������ FileStorage Ŭ������ ��ü�� ���� �����ؾ���*/
	/* ���� ����� ������ �� ���� open�Լ��� �̿�. (���� �̸�, ���� ���� ���, ���� ���ڵ� ���) */
	/* ���� ���� ��忡�� READ, WRITE, APPEND, MEMORY ������ ���� */

	/* open�Լ��� �̿�, �����ڸ� �̿��� ���� */
	/*FileStorage fs;
	fs.open("mydata.json", FileStorage::WRITE);

	FileStorage fs("mydata.json", FileStorage::WRITE);*/

	/* ���������� ���ȴ����� Ȯ���Ϸ��� isOpened�Լ��� �̿�*/
	/* ���Ͽ� �����͸� ������ ������ << ������ ������ �Լ��� ��� */
	/* ���Ϸκ��� �����͸� �о� ���� �۾��� �� ������ >> ������ �����Ǹ� ��� */
	/* �۾��� �Ϸ�Ǹ� release�Լ��� ����Ͽ� ������ �ݰ� �޸� ���۸� ��������� �� */

	/* << ������ ������ �Լ� (FileStorage ��ü, ������ ������ �Ǵ� ���ڿ�) */
	/* ���Ͽ� ���� ���� �����͸� ������ ������ �������� ������ ���� ���ڿ� ������ �̸��� �Բ� ���� */
	/* ��, ��ü�� ������ �̸��� ���� ������ ��, ���� ������ �����͸� ���� */
	/* << ������ ������ �Լ��� �̿��Ͽ� ���Ͽ� ���� ���� �����͸� �����ϴ� ���� */

	//String name = "Jane";
	//int age = 10;
	//Point p1(100, 200);
	//vector<int> scores = { 80, 90, 50 };
	//Mat mat1 = (Mat_<float>(2, 2) << 1.0f, 1.5f, 2.0f, 3.2f);

	//FileStorage fs(filename, FileStorage::WRITE); // �����ڸ� �̿��Ͽ� ���� open. ��ü�� ���� ��� ����

	//if (!fs.isOpened()) {
	//	cerr << "File open Failed" << endl;
	//	return -1;
	//}

	//fs << "name" << name; // �غ��� �����͸� << �����ڸ� �̿��Ͽ� ���Ͽ� ����
	//fs << "age" << age;
	//fs << "point" << p1;
	//fs << "scores" << scores;
	//fs << "data" << mat1;

	//fs.release();

	/* ������ ���� �ҷ����� */
	/* ������ �б� ���� ���� FileStorage ��ü�� ���� ��ü�� �м��Ͽ� ������ ������ ���� ��� ������ ���� */
	/* ��� = �̸��� ������ ������ �ϳ��� ������ */
	/* FileNodeŬ������ �̿��Ͽ� ��带 ǥ�� */
	/* FileNode ��ü�� �����Ϸ��� []������ ������ �Լ��� ��� [](nodename)*/
	/* FileNode ��ü�� ��� �� �Ŀ��� >> ������ ������ �Լ��� �̿��Ͽ� ��忡 ����� ������ ���� �޾ƿ� */
	/* >> �Լ� (FileNode ��ü, value or vec) , vec�� STL vector���� ����� ������ �ҷ��� �� ��� */
	/* ����, fn�� ��� �� �� ���� �ʿ�������Ƿ� �� ��° ��츦 ���� �� */

	/* ��ü fs�κ��� "year"�̶�� ��� �̸��� �����͸� �о� �ͼ� year ������ �����ϴ� �ڵ� */
	/*FileStorage fs("mydata.json", FileStorage::READ);
	int year;
	FileNode fn = fs["year"];
	fn >> year;

	fs["year"] >> year;*/

	String name;
	int age;
	Point p1;
	vector<int> scores;
	Mat mat1;

	FileStorage fs(filename, FileStorage::READ);

	if (!fs.isOpened()) {
		cerr << "File open Fail" << endl;
		return -1;
	}

	fs["name"] >> name;
	fs["age"] >> age;
	fs["point"] >> p1;
	fs["scores"] >> scores;
	fs["data"] >> mat1;

	fs.release();

	cout << "name : " << name << endl;
	cout << "age : " << age << endl;
	cout << "point : " << p1 << endl;
	cout << "scores: " << endl << (Mat)scores << endl; // std::vector<int>�������� ���ǵ� �����̸� scores�� ����� ���� ������ ������ 1��¥�� ����� ����
	cout << "data : " << endl << mat1 << endl;
}