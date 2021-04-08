#pragma once
#include "Helpers/Helpers.hpp"

/*
File: FuncMap.hpp
Purpose: Contains the definition of the CFuncMap class, responsible for storing pointers to all command-functions.
Author: Pin (https://github.com/sailent704)
*/

using tFunction = long(__cdecl*)(vector<wstring>);

class CFuncMap
{
	//Default visibility is private
	std::map<wstring, tFunction> funcMap;
public:
	tFunction GetFunction(wstring key)
	{
		return funcMap[key];
	}

	void AddRef(wstring key, tFunction func)
	{
		funcMap[key] = func;
	}

	bool Exists(wstring key)
	{
		return ((funcMap.count(key) != 0) ? true : false);
	}

	tFunction operator[](wstring key)
	{
		if (funcMap.count(key))
			return funcMap.at(key);
		return nullptr;
	}
};

inline CFuncMap gFuncMap;

void InitFuncMap(CFuncMap* map);
