#include <iostream>
using namespace std;

class Myvector {
public:
	Myvector(int n = 100, int val = 0);
	~Myvector() { delete[] mem; }
	void show();
private:
	int* mem;
	int size;
};

Myvector::Myvector(int n, int val) {
	mem = new int[n];
	size = n;
	for (int i = 0; i < size; i++) {
		mem[i] = val;
	}
}

void Myvector::show() {
	for (int i = 0; i < size; i++) {
		cout << mem[i];
	}
	cout << endl;
}

int main()
{
	Myvector a, b(10, 50);
	a.show();
	b.show();
}