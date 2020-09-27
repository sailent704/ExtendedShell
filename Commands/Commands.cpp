#include "Commands.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

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
			std::cout << "cd: Permission denied" << std::endl;
			return E_ACCESSDENIED;
		}

		std::cout << "cd: Filesystem error " << e.code().value() << std::endl;
		return E_FAIL;
	}
	

	printf("cd: %s: No such file or directory\n", sPath.c_str());
	return E_INVALIDARG;
}

HRESULT Commands::cat(vector<string> args)
{
	if (args.size() < 2)
		return E_INVALIDARG;

	string sFileName = Helpers::vecsum(1, args, true, ' ');

	if (!fs::exists(sFileName))
	{
		printf("cat: %s: No such file or directory\n", sFileName.c_str());
		return E_INVALIDARG;
	}
		
	std::ifstream file(sFileName);

	if (!file.good())
	{
		std::cout << "cat: Failed to open file" << std::endl;
		return E_FAIL;
	}

	std::stringstream sStream; sStream << file.rdbuf();
		
	std::cout << sStream.str() << std::endl;

	return S_OK;
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
			std::cout << "ls: Permission denied" << std::endl;
			return E_ACCESSDENIED;
		}

		std::cout << "ls: Filesystem error " << e.code().value() << std::endl;
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Commands::mkdir(vector<string> args)
{
	string sDirectoryName = Helpers::vecsum(1, args, true, ' ');
	string sPath = fs::current_path().string();


	if (sDirectoryName.empty())
	{
		std::cout << "mkdir: Missing operand" << std::endl;
		return E_INVALIDARG;
	}

	try
	{
		if (!Helpers::StringFind(sDirectoryName, "\\"))
		{
			sDirectoryName = sPath + "\\" + sDirectoryName;
		}

		if (fs::create_directory(sDirectoryName))
		{
			return S_OK;
		}
	}
	catch (const fs::filesystem_error& e)
	{
		if (e.code().value() == 5)
		{
			std::cout << "mkdir: Permission denied" << std::endl;
			return E_ACCESSDENIED;
		}
		else if (e.code().value() == 267)
		{
			std::cout << "mkdir: Directory name invalid" << std::endl;
			return E_ACCESSDENIED;
		}

		std::cout << "mkdir: Filesystem error " << e.code().value() << std::endl;
		return E_FAIL;
	}

	std::cout << "mkdir: Failed to create directory" << std::endl;
	return E_FAIL;
}

HRESULT Commands::touch(vector<string> args)
{
	string sCompleteName = Helpers::vecsum(1, args, true);
	std::ofstream file(sCompleteName);

	if (file.good())
	{
		file << "";
		file.close();

		return S_OK;
	}

	std::cout << "touch: Failed to create file" << std::endl;
	return E_FAIL;
}

HRESULT Commands::rm(vector<string> args)
{
	string sComplete = Helpers::vecsum(1, args, true);
	bool rmRecurse = false, rmForce = false, rmVerbose = false;
	int nLastArgument = 0;

	if (args.size() < 2) 
	{
		std::cout << "rm: Missing operand" << std::endl;
		return E_INVALIDARG;
	}

	if (Helpers::StringFind(sComplete, "/r") 
		|| Helpers::StringFind(sComplete, "-r") 
		|| Helpers::StringFind(sComplete, "--recursive")
		|| Helpers::StringFind(sComplete, "-fr")
		|| Helpers::StringFind(sComplete, "/fr")
		|| Helpers::StringFind(sComplete, "-vr")
		|| Helpers::StringFind(sComplete, "/vr")
		|| Helpers::StringFind(sComplete, "-vfr")
		|| Helpers::StringFind(sComplete, "/vfr"))
	{
		rmRecurse = true;
	}

	if (Helpers::StringFind(sComplete, "/f") 
		|| Helpers::StringFind(sComplete, "-f") 
		|| Helpers::StringFind(sComplete, "--force")
		|| Helpers::StringFind(sComplete, "-rf")
		|| Helpers::StringFind(sComplete, "/rf")
		|| Helpers::StringFind(sComplete, "-rvf")
		|| Helpers::StringFind(sComplete, "/rvf")
		|| Helpers::StringFind(sComplete, "-vrf")
		|| Helpers::StringFind(sComplete, "/vrf")
		|| Helpers::StringFind(sComplete, "-vf")
		|| Helpers::StringFind(sComplete, "/vf"))
	{
		rmForce = true;
	}

	if (Helpers::StringFind(sComplete, "/v")
		|| Helpers::StringFind(sComplete, "-v")
		|| Helpers::StringFind(sComplete, "--verbose")
		|| Helpers::StringFind(sComplete, "-rv")
		|| Helpers::StringFind(sComplete, "/rv")
		|| Helpers::StringFind(sComplete, "-fv")
		|| Helpers::StringFind(sComplete, "/fv")
		|| Helpers::StringFind(sComplete, "-rfv")
		|| Helpers::StringFind(sComplete, "/rfv")
		)
	{
		rmVerbose = true;
	}

	string sRemovePath;

	sRemovePath = Helpers::vecsum(Helpers::VectorFind("-", args) + 1, args, true);

	if (!fs::exists(sRemovePath))
	{
		std::cout << "rm: cannot remove '" << sRemovePath << "': No such file or directory" << std::endl;

		return E_INVALIDARG;
	}
	
	std::error_code ecIsDir; ecIsDir.clear();

	//Handle things that are not directories
	if (!fs::is_directory(sRemovePath, ecIsDir))
	{
		std::error_code ecRemove; ecRemove.clear();

		if (fs::remove(sRemovePath, ecRemove))
		{
			if (rmVerbose)
				std::cout << "rm: removed '" << sRemovePath << "'" << std::endl;
		}
		else
		{
			std::cout << "rm: cannot remove '" << sRemovePath << "': ";
			if (ecRemove.value() == ERROR_ACCESS_DENIED)
				std::cout << "Permission denied" << std::endl;
			else if (ecRemove.value() != ERROR_DIR_NOT_EMPTY)
				std::cout << "Error " << ecRemove.value() << std::endl;
		}

		return S_OK;
	}

	//RECURSIVE BEGIN
	if (rmRecurse)
	{

		std::error_code ecIterator; ecIterator.clear();

		for (const auto& entry : fs::recursive_directory_iterator(sRemovePath, ecIterator))
		{
			std::error_code ecChecks; ecChecks.clear();
			std::error_code ecRemove; ecRemove.clear();
			std::error_code ecIsEmpty; ecIsEmpty.clear();

			if (fs::remove(entry.path(), ecRemove))
			{
				if (rmVerbose)
				{
					if (!entry.is_directory())
						std::cout << "rm: removed '" << entry.path().filename().string() << "'" << std::endl;
					else
						std::cout << "rm: removed directory '" << entry.path().filename().string() << "'" << std::endl;
				}
					
			}
			else
			{
				
				if (ecRemove.value() == ERROR_ACCESS_DENIED)
				{
					std::cout << "rm: cannot remove '" << entry.path().filename().string() << "': Permission denied" << std::endl;
				}
				else if (ecRemove.value() != ERROR_DIR_NOT_EMPTY)
				{
					std::cout << "rm: cannot remove '" << entry.path().filename().string() << "': Error " << ecRemove.value() << std::endl;
				}
					
			}
		}
		std::error_code ecRemoveAll; ecRemoveAll.clear();

		int n = fs::remove_all(sRemovePath, ecRemoveAll);

		if (n != -1)
		{
			std::cout << "rm: removed " << n << " leftover folders" << std::endl;
		}
		else
		{
			if (ecRemoveAll.value() == ERROR_ACCESS_DENIED)
			{
				std::cout << "rm: cannot remove leftover folders: Permission denied" << std::endl;
			}
			
			else if (ecRemoveAll.value() == ERROR_DIR_NOT_EMPTY)
			{
				std::cout << "rm: cannot remove leftover folders: Directory not empty" << std::endl;
			}
			else
			{
				std::cout << "rm: cannot remove leftover folders: Error " << ecRemoveAll.value() << std::endl;
			}
		}
	}
	//RECURSIVE END

	return S_OK;
}

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
