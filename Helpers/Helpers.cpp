#include "Helpers.hpp"
#include <sstream>
//Don't include it in the header, because why should I
#include <Windows.h>

//Separate a string into a vector (delimited by a character)
vector<string> Helpers::delimstr(char delimiter, const string& str)
{
	vector<string> vLines;
	auto stream = std::stringstream(str);

	for (string sLine; std::getline(stream, sLine, delimiter);)
	{
		//Handle empty strings (space)
		if (!sLine.empty())
			vLines.push_back(sLine);
	}

	return vLines;
}

string Helpers::vecsum(unsigned int offset, const vector<string>& vec, bool useDelim, char delim)
{
	string sComplete;
	size_t vecSize = vec.size();

	for (size_t off = offset; off < vecSize; off++)
	{
		sComplete += vec[off];

		if (useDelim && (off + 1) < vecSize)
			sComplete += delim;
	}

	return sComplete;
}

void Helpers::SetPrintCol(Color color)
{
	//Get the console output handle
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}

bool Helpers::StringCmp(const string& str, const string& str2)
{
	return _stricmp(str.c_str(), str2.c_str()) == 0;
}

bool Helpers::StringFind(const std::string& str, const char* toFind)
{
	return str.find(toFind) != string::npos;
}

int Helpers::VectorFind(const string& str, const vector<string>& vec)
{
	int nLast = 0;

	for (int n = 0; n < vec.size(); n++)
	{
		if (StringFind(vec[n], str.c_str()))
			nLast = n;
	}

	return nLast;
}

bool Helpers::IsElevated()
{
	HANDLE hTk = nullptr;
	bool bReturn = false;

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hTk))
	{
		TOKEN_ELEVATION tkElevate;
		DWORD dwRetLen;

		if (GetTokenInformation(hTk, TokenElevation, &tkElevate, sizeof(tkElevate), &dwRetLen))
		{
			bReturn = static_cast<bool>(tkElevate.TokenIsElevated);
		}
		CloseHandle(hTk);
	}
	
	return bReturn;
}

bool Helpers::SetConsoleTitleS(std::string str)
{
	return SetConsoleTitleA(str.c_str());
}
