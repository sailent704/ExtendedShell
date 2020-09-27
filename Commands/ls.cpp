#include "Commands.hpp"
#include <iostream>

/*
File: ls.cpp
Purpose: Responsible for listing the files in a given directory.
Author: Pin (https://github.com/sailent704)

Known bugs: 
	Completely breaks when displaying a folder like TestFolder\* (created through WSL)
*/

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
		std::error_code ec;

		try
		{
			for (const auto& entry : fs::recursive_directory_iterator(path, ec))
			{
				if (ec.value() == 0)
					OnIterator(entry, recursive);
				else
					std::cout << "ls: " << Helpers::GetErrorMessage(ec) << std::endl;
			}
		}
		catch (fs::filesystem_error& e)
		{
			std::cout << "ls: " << Helpers::GetErrorMessage(e.code()) << std::endl;
		}
	}
	else
	{
		std::error_code ec;
		for (const auto& entry : fs::directory_iterator(path, ec))
		{
			if (ec.value() == 0)
				OnIterator(entry, recursive);
			else
				std::cout << "ls: " << Helpers::GetErrorMessage(ec) << std::endl;
		}
	}
}

HRESULT Commands::ls(vector<string> args)
{
	string sPath;

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

		//No argument supplied to recursive ls
		if (sArg.empty())
			sArg = fs::current_path().string();

		std::error_code c;

		if (fs::is_directory(sArg, c) && fs::exists(sArg, c))
		{
			sPath = sArg;
		}
		else
		{
			std::cout << "ls: " << Helpers::GetErrorMessage(c) << std::endl;
			return E_FAIL;
		}
	}
	HandleIterator(sPath, bRecursive);

	return S_OK;
}