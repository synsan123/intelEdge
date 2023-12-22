#if 0
// 좋은 문제가 아님
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

int main() {

    char number[100];
    char* symbol;

    int first_number, second_number;

    while (true) {
        cout << "? ";
        cin.getline(number, 100);
        first_number = atoi(strtok(number, " "));
        symbol = strtok(NULL, " ");
        second_number = atoi(strtok(NULL, " "));

        if (*symbol == '+') {
            cout << first_number << " + " << second_number << " = " << first_number + second_number << endl;
        }
        else if (*symbol == '-') {
            cout << first_number << " - " << second_number << " = " << first_number - second_number << endl;
        }
        else if (*symbol == '*') {
            cout << first_number << " * " << second_number << " = " << first_number * second_number << endl;
        }
        else if (*symbol == '/') {
            cout << first_number << " / " << second_number << " = " << first_number / second_number << endl;
        }
        else if (*symbol == '%') {
            cout << first_number << " % " << second_number << " = " << first_number % second_number << endl;
        }
        else break;
    }
    return 0;
}
#endif

//있는 그래도 풀기
#include <iostream>
#include <cstring>
using namespace std;

int main() {

    int num1, num2;
    char symbol;

    while (true)
    {
        cout << "? ";
        cin >> num1 >> symbol >> num2;
        switch (symbol)
        {
        case '+': cout << num1 << " + " << num2 << " = " << num1 + num2 << "\n" << endl;
            break;
        case '-': cout << num1 << " - " << num2 << " = " << num1 - num2 << "\n" << endl;
            break;
        case '*': cout << num1 << " * " << num2 << " = " << num1 * num2 << "\n" << endl;
            break;
        case '/': cout << num1 << " / " << num2 << " = " << num1 / num2 << "\n" << endl;
            break;
        case '%': cout << num1 << " % " << num2 << " = " << num1 % num2 << "\n" << endl;
            break;
        default:
            cout << "잘못입력하셨습니다.";
            break;
        }
    }
}