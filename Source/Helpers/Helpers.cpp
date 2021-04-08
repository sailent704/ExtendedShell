#include "Helpers.hpp"
#include <Windows.h>

/*
File: Helpers.cpp
Purpose: Has definitions of several helper functions.
Author: Pin (https://github.com/sailent704)
*/

vector<wstring> Helpers::delimstr(const wchar_t delimiter, const wstring& str)
{
	vector<wstring> vLines;
	auto stream = std::wstringstream(str);

	for (wstring sLine; std::getline(stream, sLine, delimiter);)
	{
		//Handle empty strings (space)
		if (!sLine.empty())
			vLines.push_back(sLine);
	}

	return vLines;
}

wstring Helpers::vecsum(unsigned int offset, const vector<wstring>& vec, bool useDelim, char delim)
{
	wstring sComplete;
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
}

bool Helpers::StringCmp(const string& str, const string& str2)
{
	return _stricmp(str.c_str(), str2.c_str()) == 0;
}

bool Helpers::StringCmp(const wstring& str, const wchar_t* toFind)
{
	return _wcsicmp(str.c_str(), toFind) == 0;
}

bool Helpers::StringFind(const wstring& str, const wstring toFind)
{
	return str.find(toFind) != string::npos;
}

int Helpers::VectorFind(const wstring& str, const vector<wstring>& vec)
{
	int nLast = 0;

	for (int n = 0; n < vec.size(); n++)
	{
		if (StringCmp(vec[n], str.c_str()))
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

//G++ seems to have issues with these - credit: MousieDev
#ifndef ERROR_DEVICE_UNREACHABLE
#define ERROR_DEVICE_UNREACHABLE 321L
#endif // !ERROR_DEVICE_UNREACHABLE

#ifndef ERROR_DEVICE_NO_RESOURCES
#define ERROR_DEVICE_NO_RESOURCES 322L
#endif // !ERROR_DEVICE_NO_RESOURCES

wstring Helpers::GetErrorMessage(const std::error_code& e)
{
	switch (e.value())
	{
	case ERROR_FILE_NOT_FOUND:
	case ERROR_PATH_NOT_FOUND:
		return L"No such file or directory";
	case ERROR_ACCESS_DENIED:
	case ERROR_NETWORK_ACCESS_DENIED:
		return L"Permission denied";
	case ERROR_NOT_ENOUGH_MEMORY:
		return L"Out of memory: Insufficient or invalid memory";
	case ERROR_NOT_READY:
		return L"The device is not ready";
	case ERROR_DIR_NOT_EMPTY:
		return L"Directory not empty";
	case ERROR_ALREADY_EXISTS:
		return L"File already exists";
	case ERROR_INVALID_EXE_SIGNATURE:
	case ERROR_BAD_EXE_FORMAT:
		return L"Cannot execute binary file";
	case ERROR_INVALID_NAME:
		return L"Filename is invalid";
	case ERROR_DIRECTORY:
		return L"Directory name is invalid";
	case ERROR_INVALID_PARAMETER:
		return L"The parameter is invalid";
	case ERROR_DEVICE_UNREACHABLE:
	case ERROR_DEVICE_NO_RESOURCES:
		return L"Device is busy";
	}

	return L"Error " + std::to_wstring(e.value());
}

bool Helpers::SetConsoleTitleS(std::string str)
{
	return SetConsoleTitleA(str.c_str());
}

wstring Helpers::ToWString(string str)
{
	return wstring(str.begin(), str.end());
}