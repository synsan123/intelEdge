#include <iostream>
using namespace std;

template <class T>
T* remove(T src[], int sizeSrc, T minus[], int sizeMinus, int& retsize) {
    int j;
    T* tmpArray = new T[sizeSrc];
    for (int i = 0; i < sizeSrc; i++) {
        for (j = 0; j < sizeMinus; j++) {
            if (src[i] == minus[j]) { // src�� ���ҿ� minus�� ���Ұ� ������ j�� ���� �ϳ� ���� �� break 
                --j;
                break;
            }
        }
        if (j == sizeMinus) { // j==sizeMinus ��°� src�� minus�� ���� ���Ұ� ���� �߰��� break ���� ���� ��� 
            tmpArray[retsize] = src[i]; // src[i]�� ���� �Ҵ� �Ͽ� ������ tmpArray�� ���� 
            retsize++; // return �� size�� ���� �ϳ� �÷��� 
        }
    }
    return tmpArray;
}

int main() {
    int a[] = { 1,2,3,4,5,6,7,8,9,10 };
    int b[] = { 5,6,7,8,9 };
    int size = 0;
    int* p = remove(a, 10, b, 5, size);
    for (int i = 0; i < size; ++i)
        cout << p[i] << ' ';
    cout << endl;
    delete[] p;
    size = 0;
    char c[] = { 'a','b','i','m','c','d','e', };
    char d[] = { 'k','i','m','n','u' };
    char* q = remove(c, 7, d, 5, size);
    for (int i = 0; i < size; ++i)
        cout << q[i] << ' ';
    cout << endl;
    delete[] q;

}
