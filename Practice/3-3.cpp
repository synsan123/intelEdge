#include <iostream>
#include <string>
using namespace std;

class Account
{
public:
	Account(string array, int x, int y);
	void deposit(int z);
	string getOwner();
	int withdraw(int z);
	int inquiry();
private:
	string name;
	int id;
	int money;
};

Account::Account(string array, int x, int y)
{
	name = array;
	id = x;
	money = y;
}

void Account::deposit(int z)
{
	money += z;
}

string Account::getOwner()
{
	return name;
}

int Account::inquiry()
{
	return money;
}

int Account::withdraw(int z)
{
	money -= z;
	return z; // 출금한 실제 금액 반환
}

int main()
{
	Account a("Maria", 1, 5000);
	a.deposit(50000);
	cout << a.getOwner() << "의 잔액은 " << a.inquiry() << endl;
	int money = a.withdraw(20000);
	cout << a.getOwner() << "의 잔액은 " << a.inquiry() << endl;
	return 0;
}