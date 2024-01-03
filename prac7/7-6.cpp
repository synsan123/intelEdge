#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Matrix {
	int m[2][2];
public:
	Matrix() : Matrix(0, 0, 0, 0) {}
	Matrix(int m1, int m2, int m3, int m4) {
		m[0][0] = m1;
		m[0][1] = m2;
		m[1][0] = m3;
		m[1][1] = m4;
	}
	void show() {
		cout << "Matrix = { ";
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				cout << m[i][j] << ' ';
		cout << "}" << endl;
	}
	Matrix operator +(Matrix mat) {
		Matrix tmp;
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				tmp.m[i][j] = m[i][j] + mat.m[i][j];
		return tmp;
	}
	Matrix& operator +=(Matrix mat) {
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				m[i][j] += mat.m[i][j];
		return *this;
	}
	bool operator ==(Matrix mat) {
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				if (m[i][j] != mat.m[i][j]) return false;
		return true;
	}
};

int main() {
	Matrix a(1, 2, 3, 4), b(2, 3, 4, 5), c;
	c = a + b;
	a += b;
	a.show(); b.show(); c.show();
	if (a == c)
		cout << "a and c are the same" << endl;

	return 0;
}

#if 0
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Matrix;
Matrix operator +(Matrix mat1, Matrix mat2);
Matrix& operator +=(Matrix& mat1, Matrix mat2);
bool operator ==(Matrix mat1, Matrix mat2);

class Matrix {
	int m[2][2];
public:
	Matrix() : Matrix(0, 0, 0, 0) {}
	Matrix(int m1, int m2, int m3, int m4) {
		m[0][0] = m1;
		m[0][1] = m2;
		m[1][0] = m3;
		m[1][1] = m4;
	}
	void show() {
		cout << "Matrix = { ";
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				cout << m[i][j] << ' ';
		cout << "}" << endl;
	}
	friend Matrix operator +(Matrix mat1, Matrix mat2);
	friend Matrix& operator +=(Matrix& mat1, Matrix mat2);
	friend bool operator ==(Matrix mat1, Matrix mat2);
};
Matrix operator +(Matrix mat1, Matrix mat2) {
	Matrix tmp;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			tmp.m[i][j] = mat1.m[i][j] + mat2.m[i][j];
	return tmp;
}
Matrix& operator +=(Matrix& mat1, Matrix mat2) {
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			mat1.m[i][j] += mat2.m[i][j];
	return mat1;
}
bool operator ==(Matrix mat1, Matrix mat2) {
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (mat1.m[i][j] != mat2.m[i][j]) return false;
	return true;
}
int main() {
	Matrix a(1, 2, 3, 4), b(2, 3, 4, 5), c;
	c = a + b;
	a += b;
	a.show(); b.show(); c.show();
	if (a == c)
		cout << "a and c are the same" << endl;

	return 0;
}
#endif
