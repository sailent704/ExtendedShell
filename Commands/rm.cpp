#include "Commands.hpp"
#include <iostream>
#include <fstream>

/*
File: rm.cpp
Purpose: Responsible for removing files
Author: Pin (https://github.com/sailent704)

Known bugs:
	rm can't remove files that are in-use (make them unlinked)
*/

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
			std::cout << "rm: cannot remove '" << sRemovePath << "': " << Helpers::GetErrorMessage(ecRemove);
		}

		return S_OK;
	}

	//RECURSIVE BEGIN
	if (rmRecurse)
	{
		std::error_code ecIterator;

		for (const auto& entry : fs::recursive_directory_iterator(sRemovePath, ecIterator))
		{
			std::error_code ecChecks;
			std::error_code ecRemove;
			std::error_code ecIsEmpty;

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
				std::cout << "rm: cannot remove '" << entry.path().filename().string() << "': " << Helpers::GetErrorMessage(ecRemove);
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
			std::cout << "rm: cannot remove leftover folders: " << Helpers::GetErrorMessage(ecRemoveAll);
		}
	}
	//RECURSIVE END

	//NONRECURSIVE BEGIN
	else
	{
		std::error_code ecIterator;

		for (const auto& entry : fs::directory_iterator(sRemovePath, ecIterator))
		{

		}
	}
	//NONRECURSIVE END
	return S_OK;
}