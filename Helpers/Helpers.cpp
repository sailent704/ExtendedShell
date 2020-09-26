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
