#include <iostream>
using namespace std;

istream& pos(istream& ins) { // pos ������ 
    cout << "��ġ��? ";
    return ins;
}

int main() {
    int x, y;
    cin >> pos >> x;
    cin >> pos >> y;
    cout << x << ',' << y << endl;
}
