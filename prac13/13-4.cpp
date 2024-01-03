#include <iostream>
#include <fstream>
using namespace std;

int getFileSize(const char* file) throw(char*) {
	if (file == NULL)
		throw - 1; // file이 NULL 포인터이면 ?1 예외 발생
	ifstream fin(file);
	if (!fin)
		throw - 2; // 열기가 실패하면 ?2 예외 발생
	fin.seekg(0, ios::end);
	int length = fin.tellg();
	return length;
}

int main() {
	try {
		int n = getFileSize("c:\\windows\\system.ini"); // 파일 크기 219 리턴
		cout << "파일 크기 = " << n << endl;
		int m = getFileSize(NULL); // 이 호출에서 예외 발생
		cout << "파일 크기 = " << m << endl;
	}
	catch (int x) {
		if (x == -1)
			cout << "예외 발생 : 파일명이 NULL 입니다." << endl;
		else if (x == -2)
			cout << "예외 발생 : 파일 열기가 실패하였습니다." << endl;
	}
}