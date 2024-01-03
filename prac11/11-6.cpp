#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

void showNumber(const double& num) {
    cout << setw(15) << setfill('_') << num;
}

void showSqrt(const double& num) {
    cout << setprecision(3) << setw(15) << setfill('_') << sqrt(num) << endl;
}

int main() {
    cout.setf(ios::left);
    cout << setw(15) << "Number";
    cout << setw(15) << "Square";
    cout << setw(15) << "Square Root" << endl;
    for (double i = 0; i <= 45; i += 5) {
        cout.precision(4);
        showNumber(i); // Number 출력 
        showNumber(i * i); // Square 출력 
        showSqrt(i); // Square Root 출력 
    }
}
