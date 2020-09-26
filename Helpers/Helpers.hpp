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
	//Transform a string into a vector, with a set delimiter.
	vector<string> delimstr(char delimiter, const string& str);

	//Concatenate strings in a vector into a single string (and put 'delim' in between)
	string vecsum(unsigned int offset, const vector<string>& vec, bool useDelim = false, char delim = '\n');

	//Returns true only if the process is running with administrator rights
	bool IsElevated();
}