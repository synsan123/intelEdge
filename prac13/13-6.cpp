#include <iostream>
using namespace std;

int* concat(int a[], int sizea, int b[], int sizeb) throw(int) {
	if (sizea <= 0 || sizeb <= 0)
		throw - 1;
	else if (a == NULL || b == NULL)
		throw - 2;
	int* p = new int[sizea + sizeb];
	if (p == NULL)
		throw - 3;

	for (int i = 0; i < sizea; i++)
		p[i] = a[i];
	for (int i = 0; i < sizeb; i++)
		p[sizea + i] = b[i];

	return p;
}

int main() {
	int x[] = { 1,2,3,4,5 };
	int y[] = { 10,20,30,40 };
	try {
		int* p = concat(x, 5, y, 4); // 5 대신에 0을 입력하면 예외가 발생
		for (int n = 0; n < 9; n++) cout << p[n] << ' ';
		cout << endl;
		delete[] p;
	}
	catch (int failCode) {
		cout << "오류 코드 : " << failCode << endl;
	}
}