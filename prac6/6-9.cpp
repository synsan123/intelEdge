#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Board {
public:
	static string* notices;
	static int index;
	static void add(string str);
	static void print();
};
string* Board::notices = new string[100];
int Board::index = 0;

void Board::add(string str) {
	notices[index++] = str;
}
void Board::print() {
	cout << "******** �Խ����Դϴ�. ********" << endl;
	for (int i = 0; i < index; i++) {
		cout << i << ": " << notices[i] << endl;
	}
	cout << endl;
}

int main() {
	Board::add("�߰����� ���� ���� ���� �����Դϴ�.");
	Board::add("�ڵ� ����� ���� �̿��� �ּ���.");
	Board::print();
	Board::add("���Ҹ� �л��� ������ȸ �Ի��Ͽ����ϴ�. �������ּ���");
	Board::print();
	return 0;
}