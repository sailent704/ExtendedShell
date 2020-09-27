#pragma once
#include "../Helpers/Helpers.hpp"

/*
File: FuncMap.hpp
Purpose: Contains the definition of the CFuncMap class, responsible for storing pointers to all command-functions.
Author: Pin (https://github.com/sailent704)
*/

using tFunction = long(__cdecl*)(vector<string>);

class CFuncMap
{
	//Default visibility is private
	std::map<string, tFunction> funcMap;
public:
	tFunction GetFunction(string key)
	{
		return funcMap[key];
	}

	void AddRef(string key, tFunction func)
	{
		funcMap[key] = func;
	}

	bool Exists(string key)
	{
		return funcMap.contains(key);
	}

	tFunction operator[](string key)
	{
		if (funcMap.contains(key))
			return funcMap.at(key);
	}
};

inline CFuncMap gFuncMap;

void InitFuncMap(CFuncMap& map);
