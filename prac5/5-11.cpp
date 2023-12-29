#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#if 0
class Book
{
public:
	Book(const char* title, int price);
	~Book();
	void set(const char* title, int price);
	void show() { cout << title << ' ' << price << "원" << endl; }
private:
	char* title;
	int price;
};

Book::Book(const char* title, int price)
{
	int size = strlen(title) + 1;
	this->title = new char[size];
	this->price = price;
	strcpy(this->title, title);
}

Book::~Book()
{
	delete[] title;
}
void Book::set(const char* title, int price)
{
	if (this->title)
		delete[] this->title;
	this->price = price;
	int size = strlen(title) + 1;
	this->title = new char[size];
	strcpy(this->title, title);
}

int main()
{
	Book cpp("명품C++", 10000);
	Book java = cpp;
	java.set("명품자바", 12000);
	cpp.show();
	java.show();
}
#endif

class Book {
	string title;
	int price;
public:
	Book(string title, int price);
	void set(string title, int price);
	void show() { cout << title << ' ' << price << "원" << endl; }
};

Book::Book(string title, int price)
{
	this->title = title;
	this->price = price;
}

void Book::set(string title, int price)
{
	this->title = title;
	this->price = price;
}

int main()
{
	Book cpp("명품C++", 10000);
	Book java = cpp;
	java.set("명품자바", 12000);
	cpp.show();
	java.show();
}