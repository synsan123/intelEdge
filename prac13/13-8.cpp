#include <iostream>
using namespace std;

int* copy(int* src, int size) throw(int) {
	int* p = NULL;
	try {
		if (size < 0) throw - 1; // too small
		else if (size > 100) throw - 2; // too big

		p = new int[size]; // 메모리 할당
		if (p == NULL) throw - 3; // memory short
		else if (src == NULL) throw - 4; // NULL source
		else { // 정상적으로 배열을 복사하는 부분
			for (int n = 0; n < size; n++) p[n] = src[n];
			return p;
		}
	}
	catch (int x) {
		if (p) delete[] p;
		throw x;
	}
}

int main() {
	int x[] = { 1,2,3 };
	try {
		int* p = copy(x, 3);
		for (int i = 0; i < 3; i++) cout << p[i] << ' ';
		cout << endl;
		delete[] p;
	}
	catch (int x) {
		cout << "failCode = " << x << endl;
	}
}
