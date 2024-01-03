#include <iostream>
using namespace std;

istream& pos(istream& ins) { // pos 조작자 
    cout << "위치는? ";
    return ins;
}

int main() {
    int x, y;
    cin >> pos >> x;
    cin >> pos >> y;
    cout << x << ',' << y << endl;
}
