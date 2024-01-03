#include "Hangman.h"
#include "Console.h"

void main() {
	Console* c = new Console();
	Hangman* e = new Hangman(c, 2); // 숨기는 글자의 개수를 2개로 한다.

	e->run();

	delete e;
	delete c;
}