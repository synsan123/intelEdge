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
    if (search(100, x, 5)) cout << "100이 배열 x에 포함되어 있다"; // 이 cout 실행
    else cout << "100이 배열 x에 포함되어 있지 않다";
}
