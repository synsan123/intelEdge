#include<iostream>
using namespace std;


template <class T>
bool search(T search, T arr[], T arr_size) {
    for (int i = 0; i < arr_size; i++) {
        if (arr[i] == search)
            return true;
    }
    return false;
}

int main() {
    int x[] = { 1, 10, 100, 5, 4 };
    if (search(100, x, 5)) cout << "100�� �迭 x�� ���ԵǾ� �ִ�"; // �� cout ����
    else cout << "100�� �迭 x�� ���ԵǾ� ���� �ʴ�";
}
