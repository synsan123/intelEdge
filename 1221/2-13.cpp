#include <iostream>
using namespace std;

int main()
{
	int number;
	int people_number;
	cout << "***** 승리장에 오신 것을 환영합니다. *****" << endl;
	
	while (true)
	{
		cout << "짬뽕:1, 짜장:2, 군만두:3, 종료:4 >> ";
		cin >> number;

		if (number == 4)
		{
			cout << "오늘 영업은 끝났습니다.";
			break;
		}
		else if(number > 4)
		{
			cout << "다시 주문하세요!!" << endl;
			continue;
		}

		cout << "몇 인분? ";
		cin >> people_number;

		if (number == 1)
		{
			cout << "짬뽕 " << people_number << "인분 나왔습니다." << endl;
		}
		else if (number == 2)
		{
			cout << "짜장 " << people_number << "인분 나왔습니다." << endl;
		}
		else if (number == 3) 
		{
			cout << "군만두 " << people_number << "인분 나왔습니다." << endl;
		}
	}
	return 0;
}