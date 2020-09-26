#pragma once
#include <string>
#include <functional>
#include <vector>
#include <map>

using std::vector;
using std::function;
using std::string;
using std::wstring;

namespace Helpers
{
	enum class Color : int
	{
		BLACK = 0,
		DARKBLUE = 1,
		RED = 4,
		PURPLE = 5,
		DEFAULT = 7,
		GRAY = 8,
		BLUE = 9,
		GREEN = 10,
		LIGHTBLUE = 11,
		PINK = 13,
		YELLOW = 14,
		WHITE = 15
	};

	//Transform a string into a vector, with a set delimiter.
	vector<string> delimstr(char delimiter, const string& str);

	//Concatenate strings in a vector into a single string (and put 'delim' in between)
	string vecsum(unsigned int offset, const vector<string>& vec, bool useDelim = false, char delim = '\n');

	void SetPrintCol(Color color);

	//Case insensitive string compare - returns true if they are the same.
	bool StringCmp(const string& str, const string& str2);

	bool StringFind(const string& str, const char* toFind);

	//Returns true only if the process is running with administrator rights
	bool IsElevated();

	//Why include Windows.h if I only need one function?
	bool SetConsoleTitleS(string str);
}