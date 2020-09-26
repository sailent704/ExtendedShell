#pragma once
#include "../Helpers/Helpers.hpp"

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
};

inline CFuncMap gFuncMap;

void InitFuncMap(CFuncMap& map);