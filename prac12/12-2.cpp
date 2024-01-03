#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	ifstream fin("c:\\windows\\system.ini");
	if (!fin) {
		cout << "열기 오류";
		return 0;
	}
	string line;
	int lineno = 1;
	while (getline(fin, line)) { // 한 라인을 읽어들인다.
		cout << lineno++ << " : "; // 라인 번호 출력
		cout << line << endl; // 라인 출력
	}
	fin.close();
}