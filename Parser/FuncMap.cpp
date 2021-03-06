#include "FuncMap.hpp"
#include "../Commands/Commands.hpp"

/*
File: FuncMap.cpp
Purpose: Responsible for adding all the functions for the shell to support.
Author: Pin (https://github.com/sailent704)
*/

//Commands will be added here, so no need for long "if else" statements
void InitFuncMap(CFuncMap& map)
{
	map.AddRef("pwd", Commands::pwd);
	map.AddRef("cd", Commands::cd);
	map.AddRef("ls", Commands::ls);
	map.AddRef("clear", Commands::clear);
	map.AddRef("cat", Commands::cat);
	map.AddRef("mkdir", Commands::mkdir);
	map.AddRef("touch", Commands::touch);
	map.AddRef("rm", Commands::rm);
	map.AddRef("./\t", Commands::RunFile); // '\t' is added for the command to not be recognized normally.
}
