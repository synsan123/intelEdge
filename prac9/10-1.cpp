#include <iostream>
using namespace std;

template <class T>
T biggest(T a[], T n) {
    T big = a[0]; // �迭 a�� ù��° ���Ҹ� big�� ���� 
    for (T i = 1; i < n; i++)
        big = big < a[i] ? a[i] : big; // big���� a[i]�� ���� �� ũ�� big�� a[i]�� ���� ���� 
    return big;
}

int main() {
    int big = 0;
    int x[] = { 1, 10, 100, 5, 4 };
    cout << biggest(x, 5) << endl;
}
