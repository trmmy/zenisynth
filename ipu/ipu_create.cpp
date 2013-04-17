#include "stdafx.h"
#include "ipu.h"

void IPU::create()
{

    _wfreopen_s(&m_hLogFile,L"stdout.txt" , L"w+t" , stdout);

    m_logThreadExitSign=false;
    _beginthread(&updateLog,0,NULL);

    out("create");

    m_L=lua_open();
    if(m_L==NULL)
    {
        out("lua_open failed");
    }
    else
    {
        out("lua_open succeeded");
    }

    loadModules();

    if(luaL_dofile(m_L,"main.lua")!=0)
    {
        out("An error detected when loading main.lua");
        out("////////////////Error detail////////////////");
        out(lua_tostring(m_L,-1));
        out("////////////////////////////////////////////")
						
            }
    else
    {
        out("lua ok");
        m_isLuaOK=true;
    }

    m_hAccelTable = LoadAccelerators(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_IPU));
	
    createWindow();

#ifdef _x64
    out("starting x86 ime hook layer");
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&si,sizeof(si));
    si.cb=sizeof(si);

    CreateProcess(_T("zs_x86layer.exe"),NULL,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&si,&pi);

#endif
}
