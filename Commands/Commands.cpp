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
		std::cout << "ls: filesystem error " << e.code().value() << std::endl;
		return E_FAIL;
	}
	

	printf("cd: %s is not a directory\n", sPath.c_str());
	return E_INVALIDARG;
}

HRESULT Commands::ls(vector<string> args)
{
	string sPath;

	//If no directory is specified, use the working directory.
	if (args.size() < 2)
	{
		sPath = fs::current_path().string();
	}

	else
	{
		string sArg = Helpers::vecsum(1, args, true, ' ');

		try
		{
			if (fs::is_directory(sArg) && fs::exists(sArg))
				sPath = sArg;
		}

		//Filesystem errors can be raised by stuff like "Access Denied" etc.
		catch (const std::filesystem::filesystem_error& e)
		{
			std::cout << "ls: filesystem error " << e.code().value() << std::endl;
			return E_FAIL;
		}
	}
	try
	{
		for (const auto& entry : fs::directory_iterator(sPath))
		{
			string sFileName = entry.path().string();
			size_t lastSlash = sFileName.find_last_of('\\');

			//I have no idea how it could be npos, but I choose to leave it in for edge-cases.
			if (lastSlash == string::npos)
				continue;

			sFileName.erase(0, lastSlash + 1);

			if (entry.is_directory())
				std::cout << "dir: " << sFileName << std::endl;
			else
				std::cout << sFileName << std::endl;
		}
	}

	catch (const fs::filesystem_error& e)
	{
		std::cout << "ls: filesystem error " << e.code().value() << std::endl;
		return E_FAIL;
	}
	

	return S_OK;
}
