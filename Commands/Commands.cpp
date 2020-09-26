#include "Commands.hpp"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

#define eq(str, str2) stricmp(str.c_str(), str2) 

HRESULT Commands::pwd(vector<string> args)
{
	//currentpath.string() removes the double-quotes at the beginning and end
	std::cout << fs::current_path().string() << std::endl;

	return S_OK;
}

HRESULT Commands::clear(vector<string> args)
{
	COORD coOrigin = { 0, 0 };
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	GetConsoleScreenBufferInfo(hConsole, &csbInfo);

	DWORD dwNumWritten;

	if (FillConsoleOutputCharacterA(hConsole, ' ', csbInfo.dwSize.X * csbInfo.dwSize.Y, coOrigin, &dwNumWritten))
	{
		//FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE indicates white text on a black background.
		if (FillConsoleOutputAttribute(
			hConsole, 
			FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
			dwNumWritten, 
			coOrigin, 
			&dwNumWritten)) 
		{
			SetConsoleCursorPosition(hConsole, coOrigin);
			return S_OK;
		}

	}

	return E_FAIL;
}

HRESULT Commands::cd(vector<string> args)
{
	string sPath = Helpers::vecsum(1, args, true, ' ');

	//Replicate the behavior of cd in UNIX-like systems.
	if (sPath.empty())
		return E_INVALIDARG;

	try
	{
		if (fs::is_directory(sPath) && fs::exists(sPath))
		{
			fs::current_path(sPath);
			return S_OK;
		}

	}
	catch (const fs::filesystem_error& e)
	{
		if (e.code().value() == 5)
		{
			std::cout << "cd: permission denied" << std::endl;
			return E_ACCESSDENIED;
		}

		std::cout << "cd: filesystem error " << e.code().value() << std::endl;
		return E_FAIL;
	}
	

	printf("cd: %s is not a directory\n", sPath.c_str());
	return E_INVALIDARG;
}

void OnIterator(const fs::directory_entry& entry, bool bRecursive)
{
	using namespace Helpers; //Extends only to this scope

	string sFileName = entry.path().string();
	size_t lastSlash = sFileName.find_last_of('\\');

	//I have no idea how it could be npos, but I choose to leave it in for edge-cases.
	if (lastSlash == string::npos)
		return;

	sFileName.erase(0, lastSlash + 1);

	//Handle the colors :)

	if (entry.is_directory())
		SetPrintCol(Color::BLUE);
	if (entry._Is_symlink_or_junction() || entry.is_symlink())
		SetPrintCol(Color::LIGHTBLUE);

	if ((StringFind(sFileName, ".exe") ||
		StringFind(sFileName, ".zip") ||
		StringFind(sFileName, ".rar") ||
		StringFind(sFileName, ".tar") ||
		StringFind(sFileName, ".gz") ||
		StringFind(sFileName, ".iso") ||
		StringFind(sFileName, ".cmd") ||
		StringFind(sFileName, ".dll") ||
		StringFind(sFileName, ".bat") ||
		StringFind(sFileName, ".txt") ||
		StringFind(sFileName, ".ini") ||
		StringFind(sFileName, ".docx") ||
		StringFind(sFileName, ".xlsx") ||
		StringFind(sFileName, ".rtf") ||
		StringFind(sFileName, ".pdf") ||
		StringFind(sFileName, ".c") ||
		StringFind(sFileName, ".cpp") ||
		StringFind(sFileName, ".h") ||
		StringFind(sFileName, ".hpp") ||
		StringFind(sFileName, ".log") ||
		StringFind(sFileName, ".tlog")) && !entry.is_directory())
	{
		SetPrintCol(Color::GREEN);
	}

	if (bRecursive)
	{
		if (entry.is_directory())
		{
			std::cout << std::endl << sFileName << ": " << std::endl;
			SetPrintCol(Color::DEFAULT);
			return;
		}
	}

	std::cout << sFileName << std::endl;

	SetPrintCol(Color::DEFAULT);
}

//Please, if you know how to handle this better, make a pull request.
void HandleIterator(string path, bool recursive)
{
	if (recursive)
	{
		for (const auto& entry : fs::recursive_directory_iterator(path))
		{
			OnIterator(entry, recursive);
		}
	}
	else
	{
		for (const auto& entry : fs::directory_iterator(path))
		{
			OnIterator(entry, recursive);
		}
	}
}

HRESULT Commands::ls(vector<string> args)
{
	string sPath;

	try
	{
		bool bRecursive = false;

		if (args.size() < 2)
		{
			sPath = fs::current_path().string();
		}

		else
		{
			if (Helpers::StringCmp(args[1], "/R") || Helpers::StringCmp(args[1], "-R")) {
				bRecursive = true;
				if (args.size() == 2)
					sPath = fs::current_path().string();
			}
			
			string sArg = Helpers::vecsum(1 + bRecursive, args, true, ' ');

			if (fs::is_directory(sArg) && fs::exists(sArg))
				sPath = sArg;
		}
		HandleIterator(sPath, bRecursive);
	}

	catch (const fs::filesystem_error& e)
	{
		if (e.code().value() == 5)
		{
			std::cout << "ls: permission denied" << std::endl;
			return E_ACCESSDENIED;
		}

		std::cout << "ls: filesystem error " << e.code().value() << std::endl;
		return E_FAIL;
	}

	return S_OK;
}
