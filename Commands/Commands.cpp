#include "Commands.hpp"
#include <iostream>

/*
File: Commands.cpp
Purpose: Stores commands that are not exposed to the user, like the one responsible for binary execution.
Author: Pin (https://github.com/sailent704)
*/

HRESULT Commands::RunFile(vector<string> args)
{
	string sApplicationName = args[0].erase(0, 2);

	if (sApplicationName.find_last_of('\\') != string::npos)
	{
		sApplicationName.erase(0, sApplicationName.find_last_of('\\') + 1);
	}

	if (!fs::exists(sApplicationName))
	{
		std::cout << "./" << args[0] << ": No such file or directory" << std::endl;
		return E_INVALIDARG;
	}

	string sCommandLine = Helpers::vecsum(1, args, true);

	if (sApplicationName.empty())
		return E_INVALIDARG;

	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (CreateProcessA(
		sApplicationName.c_str(),
		const_cast<char*>(string(sApplicationName + ' ' + sCommandLine).c_str()),
		NULL,
		NULL,
		FALSE,
		NORMAL_PRIORITY_CLASS | CREATE_NEW_PROCESS_GROUP,
		NULL,
		NULL,
		&si,
		&pi
	))
	{
		WaitForSingleObject(pi.hProcess, INFINITE);

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		return S_OK;
	}
	else
	{
		std::cout << "./" << args[0] << ": Failed to launch file (error code " << GetLastError() << ")\n";
	}

	return S_OK;
}
