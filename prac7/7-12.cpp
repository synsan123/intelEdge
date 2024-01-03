#include <iostream>
#include <string>

using namespace std;

class SortedArray {
	int size;
	int* p;
	void sort();
public:
	SortedArray();
	SortedArray(SortedArray& src);
	SortedArray(int p[], int size);
	~SortedArray();
	SortedArray operator +(SortedArray& op2);
	SortedArray& operator =(const SortedArray& op2);
	void show();
};
void SortedArray::sort() {
	int tmp;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (p[j] > p[j + 1]) {
				tmp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = tmp;
			}
		}
	}
}
SortedArray::SortedArray() {
	this->size = 0;
	this->p = NULL;
}
SortedArray::SortedArray(SortedArray& src) {
	this->size = src.size;
	this->p = new int[size];
	for (int i = 0; i < size; i++) {
		this->p[i] = src.p[i];
	}
	sort();
}
SortedArray::SortedArray(int p[], int size) {
	this->size = size;
	this->p = new int[size];
	for (int i = 0; i < size; i++) {
		this->p[i] = p[i];
	}
	sort();
}
SortedArray::~SortedArray() {
	delete[] p;
}
SortedArray SortedArray::operator +(SortedArray& op2) {
	SortedArray tmp;
	tmp.size = this->size + op2.size;
	tmp.p = new int[tmp.size];
	int ind = 0;
	for (int i = 0; i < this->size; i++) {
		tmp.p[ind++] = this->p[i];
	}
	for (int i = 0; i < op2.size; i++) {
		tmp.p[ind++] = op2.p[i];
	}
	sort();
	return tmp;
}
SortedArray& SortedArray::operator =(const SortedArray& op2) {
	delete[] this->p;
	this->size = op2.size;
	this->p = new int[this->size];
	for (int i = 0; i < size; i++) {
		this->p[i] = op2.p[i];
	}
	sort();
	return *this;
}
void SortedArray::show() {
	cout << "배열 출력 : ";
	for (int i = 0; i < size; i++) {
		cout << p[i] << ' ';
	}
	cout << endl;
}

int main() {
	int n[] = { 2,20,6 };
	int m[] = { 10,7,8,30 };

	SortedArray a(n, 3), b(m, 4), c;
	c = a + b;

	a.show();
	b.show();
	c.show();
	return 0;
}