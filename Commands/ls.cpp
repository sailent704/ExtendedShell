#include "Commands.hpp"
#include <iostream>

/*
File: ls.cpp
Purpose: Responsible for listing the files in a given directory.
Author: Pin (https://github.com/sailent704)

Known bugs: 
	[FIXED] Completely breaks when displaying a folder like TestFolder\* (created through WSL)
	'file.exe.other.extension' still highlighted green, as if ended with .exe
*/

bool IsArchive(const wstring& filename)
{
	return (
		Helpers::StringFind(filename, L".tar")
		|| Helpers::StringFind(filename, L".gz")
		|| Helpers::StringFind(filename, L".zip")
		|| Helpers::StringFind(filename, L".rar")
		|| Helpers::StringFind(filename, L".7z")
		|| Helpers::StringFind(filename, L".iso"));
}

void Print(fs::directory_entry& file, bool recursive)
{
	//Billion if statements or unhandled exceptions - I'd rather choose the ifs.
	std::error_code ec;

	if (file.is_directory(ec))
	{
		Helpers::SetPrintCol(Helpers::Color::DARKBLUE);
	}
	else if (ec.value() != 0)
	{
		Helpers::SetPrintCol(Helpers::Color::DEFAULT);
		std::wcout << "ls: cannot access '" << file.path().filename().wstring() << "': " << Helpers::GetErrorMessage(ec) << std::endl;
		return;
	}

	if (file.is_character_file(ec) || file.is_block_file(ec))
	{
		Helpers::SetPrintCol(Helpers::Color::YELLOW);
	}
	else if (ec.value() != 0)
	{
		Helpers::SetPrintCol(Helpers::Color::DEFAULT);
		std::wcout << "ls: cannot access '" << file.path().filename().wstring() << "': " << Helpers::GetErrorMessage(ec) << std::endl;
		return;
	}

	if (file.is_symlink(ec))
	{
		Helpers::SetPrintCol(Helpers::Color::CYAN);
	}
	else if (ec.value() != 0)
	{	
		Helpers::SetPrintCol(Helpers::Color::DEFAULT);
		std::wcout << "ls: cannot read symbolic link '" << file.path().filename().wstring() << "': " << Helpers::GetErrorMessage(ec) << std::endl;
		return;
	}

	if (file.is_socket(ec))
	{
		Helpers::SetPrintCol(Helpers::Color::PINK);
	}
	else if (ec.value() != 0)
	{
		Helpers::SetPrintCol(Helpers::Color::DEFAULT);
		std::wcout << "ls: cannot access '" << file.path().filename().wstring() << "': " << Helpers::GetErrorMessage(ec) << std::endl;
		return;
	}

	if (file.is_regular_file())
	{
		auto fn = file.path().filename().wstring();

		if (IsArchive(fn))
		{
			Helpers::SetPrintCol(Helpers::Color::RED);
		}
		else
		{
			if (Helpers::StringFind(fn, L".exe") ||
				Helpers::StringFind(fn, L".cmd") ||
				Helpers::StringFind(fn, L".dll") ||
				Helpers::StringFind(fn, L".bat") ||
				Helpers::StringFind(fn, L".txt") ||
				Helpers::StringFind(fn, L".ini") ||
				Helpers::StringFind(fn, L".docx") ||
				Helpers::StringFind(fn, L".xlsx") ||
				Helpers::StringFind(fn, L".rtf") ||
				Helpers::StringFind(fn, L".pdf") ||
				Helpers::StringFind(fn, L".c") ||
				Helpers::StringFind(fn, L".cpp") ||
				Helpers::StringFind(fn, L".h") ||
				Helpers::StringFind(fn, L".hpp") ||
				Helpers::StringFind(fn, L".py") ||
				Helpers::StringFind(fn, L".obj") ||
				Helpers::StringFind(fn, L".html") ||
				Helpers::StringFind(fn, L".ipch") ||
				Helpers::StringFind(fn, L".odt") ||
				Helpers::StringFind(fn, L".json") ||
				Helpers::StringFind(fn, L".md") ||
				Helpers::StringFind(fn, L".log") ||
				Helpers::StringFind(fn, L".tlog"))
			{
				Helpers::SetPrintCol(Helpers::Color::GREEN);
			}
		}
	}
	
	if (recursive && file.is_directory())
	{
		Helpers::SetPrintCol(Helpers::Color::DEFAULT);
		if (fs::is_empty(file.path()))
		{
			return;
		}
		
		std::wcout << std::endl << file.path().wstring() << ": \n";
		return;
	}
	std::wcout << file.path().filename().wstring() << std::endl;


}

HRESULT Commands::ls(vector<wstring> args)
{
	bool bRecursive = false;
	wstring path;

	if (args.size() > 1
		&& (!_wcsicmp(args[1].c_str(), L"-r") || !_wcsicmp(args[1].c_str(), L"/r")))
	{
		bRecursive = true;
	}

	if (args.size() == 1 + bRecursive)
	{
		std::error_code ec;
		path = fs::current_path(ec);

		if (ec.value() != 0) 
		{
			std::wcout << "ls: " << Helpers::GetErrorMessage(ec) << std::endl;
			return E_FAIL;
		}
	}
	else
	{
		//1 + bRecursive = Start from the second argument if -R was specified, else start with the first
		path = Helpers::vecsum(1 + bRecursive, args, true);
	}

	auto ec = Commands::_iteratefolder(path, bRecursive, Print);
	if (ec.value() != 0)
	{
		std::wcout << "ls: " << Helpers::GetErrorMessage(ec) << std::endl;
		return E_FAIL;
	}

	return S_OK;
}