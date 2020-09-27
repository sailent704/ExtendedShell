#include "Parser.hpp"
#include <iostream>
/*
File: Parser.cpp
Purpose: Responsible for determining and subsequently calling whatever function is associated with the issued command.
Author: Pin (https://github.com/sailent704)
*/

void ParseCommand(vector<string> vCommand)
{
	if (vCommand.empty())
		return;

	if (gFuncMap.Exists(vCommand[0]))
	{
		try
		{
			gFuncMap[vCommand[0]](vCommand);
		}
		catch (...)
		{
			std::cout << "[ExtendedShell] Unhandled exception caught, stopping operation to prevent a crash." << std::endl;
		}
		
	}
	else if (vCommand[0].starts_with("./"))
	{
		gFuncMap["./\t"](vCommand);
	}
	else
	{
		printf("%s: not found\n", vCommand[0].c_str());
	}
}
