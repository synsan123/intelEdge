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
	fin.seekg(0, ios::beg);

	// 복사 단위 결정
	int copyUnit = fileSize / 10;
	char* buf = new char[copyUnit]; // 메모리 할당

	cout << "복사 시작..." << endl;
	for (int i = 0; i < 10; i++) {
		fin.read(buf, copyUnit);
		int real = fin.gcount(); // 실제 읽은 바이트 수
		fout.write(buf, real); // 실제 읽은 바이트 만큼만 기록
		cout << '.';
		cout << real << "B ";
		cout << (i + 1) * 10 << '%' << endl;
		if (real < copyUnit) // 읽은 바이트가 시도한 바이트보다 작으면 종료
			break;
	}
	cout << fileSize << "B 복사 완료" << endl;

	delete[] buf;
	fin.close();
	fout.close();
}