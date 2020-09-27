#include "Helpers.hpp"
#include <Windows.h>

/*
File: Helpers.cpp
Purpose: Has definitions of several helper functions.
Author: Pin (https://github.com/sailent704)
*/

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

bool Helpers::StringFind(const wstring& str, const wchar_t* toFind)
{
	return _wcsicmp(str.c_str(), toFind) == 0;
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

string Helpers::GetErrorMessage(const std::error_code& e)
{
	switch (e.value())
	{
	case ERROR_FILE_NOT_FOUND:
	case ERROR_PATH_NOT_FOUND:
		return "No such file or directory";
	case ERROR_ACCESS_DENIED:
	case ERROR_NETWORK_ACCESS_DENIED:
		return "Permission denied";
	case ERROR_NOT_ENOUGH_MEMORY:
		return "Out of memory: Insufficient or invalid memory";
	case ERROR_NOT_READY:
		return "The device is not ready";
	case ERROR_DIR_NOT_EMPTY:
		return "Directory not empty";
	case ERROR_ALREADY_EXISTS:
		return "File exists";
	case ERROR_INVALID_EXE_SIGNATURE:
	case ERROR_BAD_EXE_FORMAT:
		return "Cannot execute binary file";
	case ERROR_DIRECTORY:
		return "Directory name invalid";
	case ERROR_DEVICE_UNREACHABLE:
	case ERROR_DEVICE_NO_RESOURCES:
		return "Device is busy";
	}

	return "Error " + std::to_string(e.value());
}

bool Helpers::SetConsoleTitleS(std::string str)
{
	return SetConsoleTitleA(str.c_str());
}
