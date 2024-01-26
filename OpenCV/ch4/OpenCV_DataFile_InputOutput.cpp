/* OpenCV 데이터 파일 입출력 */
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

String filename = "mydata.json"; // (readData()함수에서 함께 사용하기 위하여) 데이터 파일 이름을 전역변수로 선언

int main()
{
	/* 데이터 파일 입출력은 FileStorage 클래스가 담당 */
	/* 데이터를 저장하거나 읽어오려면 FileStorage 클래스의 객체를 먼저 생성해야함*/
	/* 실제 사용할 파일을 열 때는 open함수를 이용. (파일 이름, 파일 열기 모드, 파일 인코딩 방식) */
	/* 파일 열기 모드에는 READ, WRITE, APPEND, MEMORY 형식이 있음 */

	/* open함수를 이용, 생성자를 이용한 예제 */
	/*FileStorage fs;
	fs.open("mydata.json", FileStorage::WRITE);

	FileStorage fs("mydata.json", FileStorage::WRITE);*/

	/* 정상적으로 열렸는지를 확인하려면 isOpened함수를 이용*/
	/* 파일에 데이터를 저장할 때에는 << 연산자 재정의 함수를 사용 */
	/* 파일로부터 데이터를 읽어 오는 작업을 할 때에는 >> 연산자 재정의를 사용 */
	/* 작업이 완료되면 release함수를 사용하여 파일을 닫고 메모리 버퍼를 해제해줘야 함 */

	/* << 연산자 재정의 함수 (FileStorage 객체, 저장할 데이터 또는 문자열) */
	/* 파일에 여러 개의 데이터를 저장할 때에는 데이터의 구분을 위한 문자열 형식의 이름을 함께 저장 */
	/* 즉, 객체에 데이터 이름을 먼저 저장한 후, 실제 저장할 데이터를 저장 */
	/* << 연산자 재정의 함수를 이용하여 파일에 여러 개의 데이터를 저장하는 예제 */

	//String name = "Jane";
	//int age = 10;
	//Point p1(100, 200);
	//vector<int> scores = { 80, 90, 50 };
	//Mat mat1 = (Mat_<float>(2, 2) << 1.0f, 1.5f, 2.0f, 3.2f);

	//FileStorage fs(filename, FileStorage::WRITE); // 생성자를 이용하여 파일 open. 객체를 쓰기 모드 생성

	//if (!fs.isOpened()) {
	//	cerr << "File open Failed" << endl;
	//	return -1;
	//}

	//fs << "name" << name; // 준비한 데이터를 << 연산자를 이용하여 파일에 저장
	//fs << "age" << age;
	//fs << "point" << p1;
	//fs << "scores" << scores;
	//fs << "data" << mat1;

	//fs.release();

	/* 데이터 파일 불러오기 */
	/* 파일을 읽기 모드로 열면 FileStorage 객체는 파일 전체를 분석하여 계층적 구조를 갖는 노드 집합을 구성 */
	/* 노드 = 이름과 값으로 구성된 하나의 데이터 */
	/* FileNode클래스를 이용하여 노드를 표현 */
	/* FileNode 객체에 접근하려면 []연산자 재정의 함수를 사용 [](nodename)*/
	/* FileNode 객체를 얻어 온 후에는 >> 연산자 재정의 함수를 이용하여 노드에 저장된 데이터 값을 받아옴 */
	/* >> 함수 (FileNode 객체, value or vec) , vec은 STL vector형식 저장된 데이터 불러올 때 사용 */
	/* 예제, fn의 경우 한 번 쓰고 필요없어지므로 두 번째 경우를 많이 씀 */

	/* 객체 fs로부터 "year"이라는 노드 이름의 데이터를 읽어 와서 year 변수에 저장하는 코드 */
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
	cout << "scores: " << endl << (Mat)scores << endl; // std::vector<int>형식으로 정의된 변수이며 scores에 저장된 정수 값으로 구성된 1열짜리 행렬을 생성
	cout << "data : " << endl << mat1 << endl;
}