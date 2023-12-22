#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	char coffee[100];
	int cups_number;
	int coffee_value = 0;
	int total_coffee_value = 0;

	cout << "에스프레소 2000원, 아메리카노 2300원, 카푸치노 2500원입니다." << endl;
	while (true)
	{
		cout << "주문 >> ";
		cin >> coffee >> cups_number;
		if (strcmp(coffee, "에스프레소") == 0)
		{
			coffee_value = cups_number * 2000;
			cout << coffee_value << "입니다. 맛있게 드세요." << endl;
			total_coffee_value += coffee_value;
		}
		else if (strcmp(coffee, "아메리카노") == 0)
		{
			coffee_value = cups_number * 2300;
			cout << coffee_value << "입니다. 맛있게 드세요." << endl;
			total_coffee_value += coffee_value;
		}
		else if (strcmp(coffee, "카푸치노") == 0)
		{
			coffee_value = cups_number * 2500;
			cout << coffee_value << "입니다. 맛있게 드세요." << endl;
			total_coffee_value += coffee_value;
		}
		if (total_coffee_value >= 20000)
		{
			cout << "오늘 " << total_coffee_value << "원을 판매하여 카페를 닫습니다. 내일 봐요~~~" << endl;
			break;
		}
	}
	return 0;
}