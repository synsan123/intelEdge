#include <iostream>
#include <string>
using namespace std;

#include "MorseSignal.h"

MorseSignal::MorseSignal() {
	alphabet[0] = ".-"; // A
	alphabet[1] = "-..."; // B
	alphabet[2] = "-.-."; // C
	alphabet[3] = "-.."; // D
	alphabet[4] = "."; // E 
	alphabet[5] = "..-."; // F
	alphabet[6] = "--."; // G
	alphabet[7] = "...."; // H
	alphabet[8] = ".."; // I
	alphabet[9] = ".---"; // J
	alphabet[10] = "-.-"; // K
	alphabet[11] = ".-.."; // L
	alphabet[12] = "--"; // M
	alphabet[13] = "-."; // N
	alphabet[14] = "---"; // O
	alphabet[15] = ".--."; // P
	alphabet[16] = "--.-"; // Q
	alphabet[17] = ".-."; // R
	alphabet[18] = "..."; // S
	alphabet[19] = "-"; // T
	alphabet[20] = "..-"; // U
	alphabet[21] = "...-"; // V
	alphabet[22] = ".--"; // W
	alphabet[23] = "-..-"; // X
	alphabet[24] = "-.--"; // Y
	alphabet[25] = "--.."; // Z

	digit[0] = "-----";
	digit[1] = ".----";
	digit[2] = "..---";
	digit[3] = "...--";
	digit[4] = "....-";
	digit[5] = ".....";
	digit[6] = "-....";
	digit[7] = "--...";
	digit[8] = "---..";
	digit[9] = "----.";

	slash = "-..-.";
	question = "..--..";
	comma = "--..--";
	period = ".-.-.-";
	plus = ".-.-.";
	equal = "-...-";
}
void MorseSignal::text2Morse(string text, string& morse) {
	bool blankFound = false;
	for (int i = 0; i < text.length(); i++) {
		if (text[i] == ' ') {
			if (blankFound == false) {
				blankFound = true;
				morse.append("  "); // two more blanks
			}
		}
		else {
			blankFound = false;
			if (text[i] == '/')
				morse.append(slash + " "); // one blank
			else if (text[i] == '?')
				morse.append(question + " "); // one blank
			else if (text[i] == ',')
				morse.append(comma + " "); // one blank
			else if (text[i] == '.')
				morse.append(period + " "); // one blank
			else if (text[i] == '+')
				morse.append(plus + " "); // one blank
			else if (text[i] == '=')
				morse.append(equal + " "); // one blank
			else if (isalpha(text[i])) {
				int index = toupper(text[i]) - 'A';
				morse.append(alphabet[index] + " "); // one blank
			}
			else if (isdigit(text[i])) {
				int index = text[i] - '0';
				morse.append(digit[index] + " "); // one blank
			}
			else if (text[i] == '\n')
				morse.append("\n");
		}
	}
	if (morse[morse.length() - 1] == ' ')
		morse.erase(morse.length() - 1, 1); // 끝에 붙은 ' ' 제거
}

bool MorseSignal::morse2Letter(string morseLetter, char& letter) {
	for (int i = 0; i < 26; i++) {
		if (alphabet[i] == morseLetter) {
			letter = 'a' + i;
			return true;
		}
	}
	for (int i = 0; i < 10; i++) {
		if (digit[i] == morseLetter) {
			letter = '0' + i;
			return true;
		}
	}
	if (slash == morseLetter) letter = '/';
	else if (question == morseLetter) letter = '?';
	else if (comma == morseLetter) letter = ',';
	else if (period == morseLetter) letter = '.';
	else if (plus == morseLetter) letter = '+';
	else if (equal == morseLetter) letter = '=';
	else
		return false;
	return true;
}

bool MorseSignal::morseWord2Text(string morse, string& text) {
	string morseLetter;
	int index = 0, nextIndex;
	char letter;
	while (true) {
		nextIndex = morse.find(" ", index); // one blanks
		if (nextIndex == -1) {
			morseLetter = morse.substr(index);
			if (morseLetter.length() == 0)	break;
			bool b = morse2Letter(morseLetter, letter);
			if (!b) return false;
			text += letter;
			break;
		}
		morseLetter = morse.substr(index, nextIndex - index);
		bool b = morse2Letter(morseLetter, letter);
		if (!b) return false;
		text += letter;
		index = nextIndex + 1; // after one blank
	}

	return true;
}

bool MorseSignal::morse2Text(string morse, string& text) {
	string word;
	int index = 0, nextIndex;
	while (true) {
		nextIndex = morse.find("   ", index); // three blanks
		if (nextIndex == -1) {
			word = morse.substr(index);
			bool b = morseWord2Text(word, text);
			if (!b) return false;
			break;
		}
		word = morse.substr(index, nextIndex - index);
		bool b = morseWord2Text(word, text);
		if (!b) return false;
		text.append(" "); // 단어 사이의 빈 칸
		index = nextIndex + 3; // after three blanks
	}

	return true;
}