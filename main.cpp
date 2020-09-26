#include "Helpers/Helpers.hpp"
#include <iostream>
#include "Parser/FuncMap.hpp"
#include "Parser/Parser.hpp"


int main(int arg_count, char** arg_vector)
{
	InitFuncMap(gFuncMap);
	//Do stuff with args here
	

	//Main loop
	while (1)
	{
		string sInput;
		std::cout << "> ";
		
		std::getline(std::cin, sInput);

		ParseCommand(Helpers::delimstr(' ', sInput));
	}
}