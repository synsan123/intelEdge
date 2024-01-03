#include <iostream>
using namespace std;

class ArrayUtility2 {
public:
	static int* concat(int s1[], int s2[], int size);
	static int* remove(int s1[], int s2[], int size, int& retSize);
};
int* ArrayUtility2::concat(int s1[], int s2[], int size) {
	int* ret = new int[size];
	int ind = 0;
	cout << "��ģ ���� �迭�� ����Ѵ�." << endl;
	for (int i = 0; i < size / 2; i++) {
		ret[ind] = s1[i];
		cout << ret[ind] << ' ';
		ind++;
	}
	for (int i = 0; i < size / 2; i++) {
		ret[ind] = s2[i];
		cout << ret[ind] << ' ';
		ind++;
	}
	cout << endl;

	return ret;
}
int* ArrayUtility2::remove(int s1[], int s2[], int size, int& retSize) {
	int cnt = 0;
	int* tmp = new int[size];

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (s1[i] == s2[j]) break;
			if (j == size - 1) tmp[cnt++] = s1[i];
		}
	}
	if (cnt == 0) return NULL;

	retSize = cnt;
	cout << "�迭 x[]���� y[]�� �� ����� ����Ѵ�. ������ " << retSize << endl;
	int* ret = new int[retSize];
	for (int i = 0; i < retSize; i++) {
		ret[i] = tmp[i];
		cout << ret[i] << ' ';
	}
	cout << endl;

	return ret;
}

int main() {
	int x[5], y[5], retSize;
	int* z, * w;

	cout << "������ 5�� �Է��϶�. �迭 x�� �����Ѵ�>>";
	for (int i = 0; i < 5; i++) {
		cin >> x[i];
	}
	cout << "������ 5�� �Է��϶�. �迭 y�� �����Ѵ�>>";
	for (int i = 0; i < 5; i++) {
		cin >> y[i];
	}
	z = ArrayUtility2::concat(x, y, 10);
	w = ArrayUtility2::remove(x, y, 5, retSize);
	return 0;
}