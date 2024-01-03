#include <iostream>

using namespace std;

class Seat {
	string name;
public:
	Seat(string n = "---") { name = n; }
	void reservation(string n) { name = n; }
	void cancle() { name = "---"; }
	void show() { cout << name; }
};
class Schedule {
	Seat* schedule;
	string time;
public:
	Schedule(string time = "00��") { schedule = new Seat[8]; this->time = time; }
	void reservation(int index, string name) { schedule[index].reservation(name); }
	void cancle(int index) { schedule[index].cancle(); }
	void show() {
		for (int i = 0; i < 8; i++) {
			schedule[i].show();
			cout << "\t";
		}
		cout << endl;
	}
	void setTime(string time) {
		this->time = time;
	}
	string getTime() {
		return time;
	}
};

class AirlineBook {
	Schedule* airlines;
public:
	AirlineBook() {
		airlines = new Schedule[3];
		airlines[0].setTime("07��");
		airlines[1].setTime("12��");
		airlines[2].setTime("17��");
	}
	void show(int index) {
		cout << airlines[index].getTime() << '\t';
		airlines[index].show();
	}
	void reservation(int index, int seat, string name) {
		airlines[index].reservation(seat, name);
	}
	void cancle(int index, int seat, string name) {
		airlines[index].cancle(seat);
	}
};

class Console {
public:
	static int menu;
	static int time;
	static AirlineBook hansung;
	static void start() {
		cout << "***** �Ѽ��װ��� ���Ű��� ȯ���մϴ� *****" << endl;
		while (true) {
			showMenu();
			switch (menu) {
			case 1:
				reservation(); break;
			case 2:
				cancle(); break;
			case 3:
				show(); break;
			case 4:
				return;
			}
		}
	}
	static void showMenu() {
		cout << "����:1, ���:2, ����:3, ������:4>>";
		cin >> menu;
	}
	static void reservation() {
		cout << "07��:1, 12��:2, 17��:3>>";
		cin >> time;
		hansung.show(time - 1);
		int seatNum;
		string name;
		cout << "�¼���ȣ>>";
		cin >> seatNum;
		cout << "�̸��Է�>>";
		cin >> name;
		hansung.reservation(time - 1, seatNum - 1, name);
	}
	static void cancle() {
		cout << "07��:1, 12��:2, 17��:3>>";
		cin >> time;
		hansung.show(time - 1);
		int seatNum;
		string name;
		cout << "�¼���ȣ>>";
		cin >> seatNum;
		cout << "�̸��Է�>>";
		cin >> name;
		hansung.cancle(time - 1, seatNum - 1, name);
	}
	static void show() {
		for (int i = 0; i < 3; i++) {
			hansung.show(i);
		}
	}
};
int Console::menu = 0;
int Console::time = 0;
AirlineBook Console::hansung;

int main() {
	Console::start();

	return 0;
}