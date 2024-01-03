#ifndef WORDS_H
#define WORDS_H

#include <cmath>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Words {
	ifstream fin;
	vector<string> wordVector;
public:
	Words(const char* fileName);
	string getNext();
	virtual ~Words();
};
#endif