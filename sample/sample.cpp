#include <windows.h>
#include <zenisynth.h>
#include <sstream>
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}
#pragma comment(lib,"lua5.1.lib")

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

void _addLog(std::wstring&){}
ZSLogFunction addLog=&_addLog;

#define out(expr) {\
	std::wstringstream str;\
	str<<__FILE__<<" : "<<__LINE__<<" > "<<expr<<"\r\n";\
	addLog(str.str());\
	}

ZSExport OnLoad(ZSLogFunction newAddLog)
{
	addLog=newAddLog;	//assign log function
	return TRUE;
}

ZSExport HelloWorld(lua_State* L)
{
	out("Hello World");
	return 0;
}