#include <iostream>
using namespace std;

int main() {
    int a;
    int cnt = 0;
    while ((a = cin.get()) != EOF) {
        if (a == 'a')
            cnt++;
        else if (a == '\n')
            break;
    }
    cout << cnt;
}
