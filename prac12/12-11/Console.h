#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
using namespace std;

class Console {
public:
	void beep();
	void write(string msg);
	char prompt(string msg);
};

#endif