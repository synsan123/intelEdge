#include <iostream>
#include <string>

using namespace std;

class Book;
Book& operator +=(Book& b, int price);
Book& operator -=(Book& b, int price);

class Book {
	string title;
	int price, pages;
public:
	Book(string title = "", int price = 0, int pages = 0) {
		this->title = title; this->price = price; this->pages = pages;
	}
	void show() {
		cout << title << ' ' << price << "원 " << pages << " 페이지" << endl;
	}
	string getTitle() { return title; }
	friend Book& operator +=(Book& b, int price);
	friend Book& operator -=(Book& b, int price);
};

Book& operator +=(Book& b, int price) {
	b.price += price;
	return b;
}
Book& operator -=(Book& b, int price) {
	b.price -= price;
	return b;
}

int main() {
	Book a("청춘", 20000, 300), b("미래", 30000, 500);
	a += 500;
	b -= 500;
	a.show();
	b.show();

	return 0;
}