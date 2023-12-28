#include <iostream>
#include <string>
using namespace std;

class Date
{
public:
	Date(int x, int y, int z);
	Date(string array);
	int getyear();
	int getmonth();
	int getday();
	void show();
private:
	int year, month, day;
};

Date::Date(int x, int y, int z)
{
	year = x;
	month = y;
	day = z;
}
Date::Date(string array)
{
	year = stoi(array.substr(0, 4)); // 0번째 문자열부터 짜름. 내가 원하는 글 수 만큼 ex 1945/ => 1은 0번째 인덱스. 1945를 int로 받고 싶다. => 뒤에 4를 써서 4개 가지고옴.
	month = stoi(array.substr(5, 1));
	day = stoi(array.substr(7, 2));
}

int Date::getyear()
{
	return year;
}
int Date::getmonth()
{
	return month;
}
int Date::getday()
{
	return day;
}

void Date::show()
{
	cout << year << "년" << month << "월" << day << "일" << endl;
}

int main()
{
	Date birth(2014, 3, 20);
	Date independenceDay("1945/8/15");
	independenceDay.show();
	cout << birth.getyear() << ',' << birth.getmonth() << ',' << birth.getday() << endl;
	return 0;
}