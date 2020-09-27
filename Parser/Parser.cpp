#include "Parser.hpp"

void ParseCommand(vector<string> vCommand)
{
	if (vCommand.empty())
		return;

	if (gFuncMap.Exists(vCommand[0]))
	{
		gFuncMap[vCommand[0]](vCommand);
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
