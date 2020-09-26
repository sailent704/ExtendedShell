#include "Parser.hpp"

void ParseCommand(vector<string> vCommand)
{
	if (vCommand.empty())
		return;

	if (gFuncMap.Exists(vCommand[0]))
	{
		gFuncMap.GetFunction(vCommand[0])(vCommand);
	}
	else
	{
		printf("not found\n");
	}
}
