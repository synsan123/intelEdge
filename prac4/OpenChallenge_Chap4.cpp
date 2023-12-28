#include <iostream>
#include <string>
using namespace std;

class Player
{
public:
	void setname(string name);
	string getname();
private:
	string name;
};

void Player::setname(string name)
{
	this->name = name;
}
string Player::getname()
{
	return name;
}

class WordGame
{
public:
	WordGame(int number);
	~WordGame();
	void game();
private:
	int number;
	Player* p;
};

WordGame::WordGame(int number)
{
	this->number = number;
	p = new Player[number];
}
WordGame::~WordGame()
{
	delete[] p;
}
void WordGame::game()
{
	string name;
	for (int i = 0; i < number; i++) 
	{
		cout << "�������� �̸��� �Է��ϼ���. ��ĭ ���� >> ";
		cin >> name;
		p[i].setname(name);
	}
	cout << endl;
	cout << "�����ϴ� �ܾ�� �ƹ����Դϴ�." << endl;
	
	string a = "�ƹ���";
	string b;
	int i = 0;
	while (true)
	{
		cout << p[i % 3].getname() << " >> ";
		cin >> b;
		int j = a.size();
		if (a.at(j - 2) == b.at(0) && a.at(j - 1) == b.at(1))
		{
			a = b;
		}
		else
		{
			cout << p[i % 3].getname() << " Ż���Դϴ�." << endl;
			break;
		}
		i++;
	}
}

int main()
{
	int number;
	cout << "���� �ձ� ������ �����մϴ�." << endl;
	cout << "���ӿ� �����ϴ� �ο��� ����Դϱ�? ";
	cin >> number;

	WordGame WordGame(number);
	WordGame.game();
}