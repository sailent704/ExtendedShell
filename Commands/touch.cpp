#include "Commands.hpp"
#include <fstream>
#include <iostream>

/*
File: touch.cpp
Purpose: Responsible for creating new files.
Author: Pin (https://github.com/sailent704)
*/

HRESULT Commands::touch(vector<wstring> args)
{
	std::wofstream wStream(Helpers::vecsum(1, args, true));
	if (wStream.good())
	{
		wStream << "";
		wStream.close();

		return S_OK;
	}

	return E_FAIL;
}