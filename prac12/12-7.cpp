#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream fin("c:\\windows\\system.ini", ios::in | ios::binary);
	if (!fin) {
		cout << "c:\\windows\\system.ini 열기 오류";
		return 0;
	}
	ofstream fout("c:\\temp\\system.txt", ios::out | ios::binary);
	if (!fout) {
		cout << "c:\\temp\\system.txt 열기 오류";
		return 0;
	}

	// 파일 크기 알아내기
	fin.seekg(0, ios::end);
	int fileSize = fin.tellg();

	for (int i = 0; i < fileSize; i++) {
		fin.seekg(fileSize - 1 - i, ios::beg);
		int ch = fin.get();
		fout.put(ch);
	}
	cout << "복사 완료" << endl;

	fin.close();
	fout.close();
}