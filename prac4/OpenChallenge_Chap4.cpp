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
		cout << "참가자의 이름을 입력하세요. 빈칸 없이 >> ";
		cin >> name;
		p[i].setname(name);
	}
	cout << endl;
	cout << "시작하는 단어는 아버지입니다." << endl;
	
	string a = "아버지";
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
			cout << p[i % 3].getname() << " 탈락입니다." << endl;
			break;
		}
		i++;
	}
}

int main()
{
	int number;
	cout << "끝말 잇기 게임을 시작합니다." << endl;
	cout << "게임에 참가하는 인원은 몇명입니까? ";
	cin >> number;

	WordGame WordGame(number);
	WordGame.game();
}