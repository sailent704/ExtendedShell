#include "FuncMap.hpp"
#include "Commands/Commands.hpp"

/*
File: FuncMap.cpp
Purpose: Responsible for adding all the functions for the shell to support.
Author: Pin (https://github.com/sailent704)
*/

//Commands will be added here, so no need for long "if else" statements
void InitFuncMap(CFuncMap* map)
{
	map->AddRef(L"pwd", Commands::pwd);
	map->AddRef(L"cd", Commands::cd);
	map->AddRef(L"ls", Commands::ls);
	map->AddRef(L"clear", Commands::clear);
	map->AddRef(L"cat", Commands::cat);
	map->AddRef(L"mkdir", Commands::mkdir);
	map->AddRef(L"exit", Commands::exit);
	map->AddRef(L"touch", Commands::touch);
	//map->AddRef(L"rm", Commands::rm);
	//map->AddRef(L"./\t", Commands::RunFile); // '\t' is added for the command to not be recognized normally.
	map->AddRef(L"echo", Commands::echo);
}
