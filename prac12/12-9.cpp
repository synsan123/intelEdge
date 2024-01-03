#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class FileViewer {
	ifstream fin;
	vector<string> v; // 라인별로 문자열을 관리하는 벡터
public:
	FileViewer(const char* f);
	~FileViewer();
	void run();
};

FileViewer::FileViewer(const char* f) {
	fin.open(f); // 파일 열기
	if (!fin) {
		cout << f << "열기 오류";
		exit(0);
	}

	// 파일을 라인별로 읽어 벡터에 저장
	string line;
	while (getline(fin, line)) { // 한 라인을 읽어 문자열 line에 저장
		v.push_back(line); // line의 문자열을 벡터에 삽입
	}
	cout << f << " 파일 읽기 완료" << endl;
}

void FileViewer::run() {
	cout << "라인 번호를 입력하세요. 1보다 작은 값을 입력하면 종료" << endl;
	while (true) {
		cout << ": ";
		int lineno;
		cin >> lineno; // 라인 번호 입력
		if (lineno > (int)v.size()) continue; // 라인 번호가 벡터 크기보다 크면 없는 라인
		else if (lineno < 1) { // 라인 번호가 0보다 작거나 같으면 
			cout << "종료 합니다." << endl;
			break;
		}
		cout << v.at(lineno - 1) << endl; // 라인 번호에 해당하는 라인 출력
	}
}

FileViewer::~FileViewer() {
	fin.close();
}

int main() {
	FileViewer viewer("C:\\windows\\system.ini");
	viewer.run();
}