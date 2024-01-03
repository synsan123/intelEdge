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
		cout << "--- " << tag << "�±��� Trace ������ ����մϴ�. ---" << endl;
		for (int i = 0; i < index; i++) {
			if (log[i][0].compare(tag) == 0) {
				cout << log[i][0] << ":" << log[i][1] << endl;
			}
		}
	}
	else {
		cout << tag << "--- ��� Trace ������ ����մϴ�. ---" << endl;
		for (int i = 0; i < index; i++) {
			cout << log[i][0] << ":" << log[i][1] << endl;
		}
	}
}

void f() {
	int a, b, c;
	cout << "�� ���� ������ �Է��ϼ���>>";
	cin >> a >> b;
	Trace::put("f()", "������ �Է� �޾���");
	c = a + b;
	Trace::put("f()", "�� ���");
	cout << "���� " << c << endl;
}

int main() {
	Trace::put("main()", "���α׷� �����մϴ�");
	f();

	Trace::put("main()", "����");
	Trace::print("f()");
	Trace::print();
	return 0;
}