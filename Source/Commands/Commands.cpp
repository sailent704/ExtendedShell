#include "Commands.hpp"
#include <iostream>

/*
File: Commands.cpp
Purpose: Stores commands that are not exposed to the user, like the one responsible for binary execution.
Author: Pin (https://github.com/sailent704)
*/

HRESULT Commands::_execute(vector<wstring> args)
{
	return S_OK;
}

std::error_code Commands::_iteratefolder(wstring wsPath, bool bRecursive, function<void(fs::directory_entry&, bool)> onIterator)
{
	std::error_code ec;

	//Capture by reference
	auto lFunc = [&](auto iterator) 
	{
		if (ec.value() != 0)
			return ec;

		for (auto entry : iterator)
			onIterator(entry, bRecursive);

		return std::error_code();
	};

	if (bRecursive)
		return lFunc(fs::recursive_directory_iterator(wsPath, ec));
	
	return lFunc(fs::directory_iterator(wsPath, ec));
}
