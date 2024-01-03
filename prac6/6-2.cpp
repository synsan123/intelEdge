#include <iostream>
#include <string>
using namespace std;

// 생성자 중복을 이용하여 작성.
#if 0
class Person {
	int id;
	double weight;
	string name;
public:
	Person();
	Person(int id, string name, double weight);
	Person(int id, string name);
	void show() { cout << id << ' ' << weight << ' ' << name << endl; }
};

Person::Person() {
	id = 1; 
	name = "Grace";
	weight = 20.5;
}

Person::Person(int id, string name) {
	this->id = id;
	this->name = name;
	weight = 20.5;
}

Person::Person(int id, string name, double weight) {
	this->id = id;
	this->name = name;
	this->weight = weight;
}

int main()
{
	Person Grace, ashley(2, "Ashley"), Helen(3, "Helen", 32.5);
	Grace.show();
	ashley.show();
	Helen.show();
}
#endif

//생성자 디폴트 매개변수 사용하여 정리한 것
class Person {
	int id;
	double weight;
	string name;
public:
	Person(int id = 1, string name = "Grace", double weight = 20.5);
	void show() { cout << id << ' ' << weight << ' ' << name << endl; }
};

Person::Person(int id, string name, double weight) {
	this->id = id;
	this->name = name;
	this->weight = weight;
}

int main()
{
	Person Grace, ashley(2, "Ashley"), Helen(3, "Helen", 32.5);
	Grace.show();
	ashley.show();
	Helen.show();
}
