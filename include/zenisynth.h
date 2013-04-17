#pragma once
#include <string>
#define CheckArg(numArgs)                                       \
    const int n = lua_gettop(L);                                \
    if(n<numArgs){    out("lack of argument");    }else

#define ZSExport extern "C" __declspec(dllexport) int
typedef void(*ZSLogFunction)(std::wstring& str);
