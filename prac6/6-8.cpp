#include <iostream>
#include <string>

using namespace std;

class Trace {
public:
	static string log[100][2];
	static int index;
	static void put(string tag, string str);
	static void print(string tag = "");
};

string Trace::log[100][2] = { "" };
int Trace::index = 0;
void Trace::put(string tag, string str) {
	log[index][0] = tag;
	log[index][1] = str;
	index++;
}
void Trace::print(string tag) {
	if (!tag.empty()) {
		cout << "--- " << tag << "태그의 Trace 정보를 출력합니다. ---" << endl;
		for (int i = 0; i < index; i++) {
			if (log[i][0].compare(tag) == 0) {
				cout << log[i][0] << ":" << log[i][1] << endl;
			}
		}
	}
	else {
		cout << tag << "--- 모든 Trace 정보를 출력합니다. ---" << endl;
		for (int i = 0; i < index; i++) {
			cout << log[i][0] << ":" << log[i][1] << endl;
		}
	}
}

void f() {
	int a, b, c;
	cout << "두 개의 정수를 입력하세요>>";
	cin >> a >> b;
	Trace::put("f()", "정수를 입력 받았음");
	c = a + b;
	Trace::put("f()", "합 계산");
	cout << "합은 " << c << endl;
}

int main() {
	Trace::put("main()", "프로그램 시작합니다");
	f();

	Trace::put("main()", "종료");
	Trace::print("f()");
	Trace::print();
	return 0;
}