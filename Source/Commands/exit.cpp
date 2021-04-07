#include "Commands.hpp"

HRESULT Commands::exit(vector<wstring> args)
{
	std::exit(0);
}