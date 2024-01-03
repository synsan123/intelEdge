#include <iostream>

using namespace std;

class Printer {
	string model;
	string manufacturer;
	int printedCount;
	int availableCount;
protected:
	Printer(string mo = "", string me = "", int a = 0) {
		this->model = mo;
		this->manufacturer = me;
		this->availableCount = a;
		this->printedCount = 0;
	}
	bool isValidPrint(int pages) {
		if (availableCount > pages) return true;
		else return false;
	}
	void print(int pages) {
		if (isValidPrint(pages)) {
			printedCount += pages;
			availableCount -= pages;
		}
		else cout << "������ �����Ͽ� ����Ʈ�� �� �����ϴ�." << endl;
	}
	void showPrinter() { cout << model << ", " << manufacturer << ", ���� ���� " << availableCount << "��"; }
};

class InkJetPrinter : public Printer {
	int availableInk;
public:
	InkJetPrinter(string mo = "", string me = "", int a = 0, int i = 0) : Printer(mo, me, a) { this->availableInk = i; }
	bool isValidInkJetPrint(int pages) {
		if (availableInk > pages) return true;
		else return false;
	}
	void printInkJet(int pages) {
		if (isValidPrint(pages)) {
			if (isValidInkJetPrint(pages)) {
				print(pages);
				availableInk -= pages;
				cout << "����Ʈ�Ͽ����ϴ�" << endl;
			}
			else {
				cout << "��ũ�� �����Ͽ� ����Ʈ�� �� �����ϴ�." << endl;
			}
		}
		else cout << "������ �����Ͽ� ����Ʈ�� �� �����ϴ�." << endl;
	}
	void showInkJetPrinter() {
		showPrinter();
		cout << ", ���� ��� " << availableInk << endl;
	}
};

class LaserPrinter : public Printer {
	int availableToner;
public:
	LaserPrinter(string mo = "", string me = "", int a = 0, int t = 0) : Printer(mo, me, a) { this->availableToner = t; }
	bool isValidLaserPrint(int pages) {
		if (availableToner > pages) return true;
		else return false;
	}
	void printInkJet(int pages) {
		if (isValidPrint(pages)) {
			if (isValidLaserPrint(pages)) {
				print(pages);
				availableToner -= pages;
				cout << "����Ʈ�Ͽ����ϴ�" << endl;
			}
			else {
				cout << "��ʰ� �����Ͽ� ����Ʈ�� �� �����ϴ�." << endl;
			}
		}
		else cout << "������ �����Ͽ� ����Ʈ�� �� �����ϴ�." << endl;
	}
	void showLaserPrinter() {
		showPrinter();
		cout << ", ���� ��� " << availableToner << endl;
	}
};

int main() {
	InkJetPrinter ink("Officejet V40", "HP", 5, 10);
	LaserPrinter laser("SCX-6x45", "�Ｚ����", 3, 20);

	cout << "���� �۵����� 2���� �����ʹ� �Ʒ��� ����" << endl;
	cout << "��ũ�� : ";
	ink.showInkJetPrinter();
	cout << "������ : ";
	laser.showLaserPrinter();

	int printer, paper;
	char ch;
	while (true) {
		cout << endl << "������(1:��ũ��, 2:������)�� �ż� �Է�>>";
		cin >> printer >> paper;
		switch (printer) {
		case 1: ink.printInkJet(paper); break;
		case 2: laser.printInkJet(paper); break;
		default: break;
		}
		ink.showInkJetPrinter();
		laser.showLaserPrinter();

		cout << "�Լ� ����Ʈ �Ͻðڽ��ϱ�(y/n)>>";
		cin >> ch;
		if (ch == 'n') break;
		else continue;
	}

	return 0;
}