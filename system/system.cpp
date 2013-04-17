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
#include <imm.h>
#pragma comment(lib,"imm32.lib")

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

const int IMC_SETOPENSTATUS=0x0006;
const int IMC_GETOPENSTATUS=0x0005;
const int IMC_GETSENTENCEMODE=0x0001;
const int IMC_GETCONVERSIONMODE=0x0002;

void _addLog(std::wstring&){}
ZSLogFunction addLog=&_addLog;
#define out(expr) {                                             \
    std::wstringstream str;                                 \
    str<<__FILE__<<" : "<<__LINE__<<" > "<<expr<<"\r\n";    \
    addLog(str.str());                                      \
    }



#pragma data_seg("ZS_DATA")
HHOOK g_hook=NULL;
HHOOK g_msgHook=NULL;
bool g_isConverting=false;
HINSTANCE g_hModule=NULL;
#pragma data_seg()

const HWND getZeniSynthHWND()
{
    return FindWindowA("#32770","ZeniSynth");;
}

LRESULT CALLBACK hookMsgProc(
    int code,       // フックコード
    WPARAM wParam,  // 削除オプション
    LPARAM lParam   // メッセージ
    )
{

    MSG *msg=(MSG*)lParam;
    switch(msg->message)
    {
    case  WM_IME_STARTCOMPOSITION:
        if(g_isConverting==false)
        {
            SendMessage(getZeniSynthHWND(),WM_IME_STARTCOMPOSITION,wParam,lParam);
        }
        g_isConverting=true;
        break;
    case  WM_IME_ENDCOMPOSITION:
        if(g_isConverting==true)
        {
            SendMessage(getZeniSynthHWND(),WM_IME_ENDCOMPOSITION,wParam,lParam);
        }
        g_isConverting=false;
        break;
    }

    return CallNextHookEx(g_msgHook,code,wParam,lParam);
}

LRESULT CALLBACK hookWndProc(
    int code,       // フックコード
    WPARAM wParam,  // 削除オプション
    LPARAM lParam   // メッセージ
    )
{

    CWPSTRUCT* pStruct=(CWPSTRUCT*)lParam;
//		MSG *msg=(MSG*)lParam;
    switch(pStruct->message)
    {
    case  WM_IME_STARTCOMPOSITION:
        if(g_isConverting==false)
        {
            SendMessage(getZeniSynthHWND(),WM_IME_STARTCOMPOSITION,wParam,lParam);
        }
        g_isConverting=true;
        break;
    case  WM_IME_ENDCOMPOSITION:
        if(g_isConverting==true)
        {
            SendMessage(getZeniSynthHWND(),WM_IME_ENDCOMPOSITION,wParam,lParam);
        }
        g_isConverting=false;
        break;
    }

    return CallNextHookEx(g_hook,code,wParam,lParam);
}

ZSExport OnLoad(ZSLogFunction newAddLog)
{
    addLog=newAddLog;	//assign log function

    if(g_hook==NULL)
    {
        g_hook=SetWindowsHookEx(WH_CALLWNDPROC,hookWndProc,g_hModule,0);
    }
    if(g_msgHook==NULL)
    {
        g_msgHook=SetWindowsHookEx(WH_GETMESSAGE,&hookMsgProc,g_hModule,0);
    }
    return TRUE;
}

ZSExport OnFree()
{
    if(g_hook!=NULL)
    {
        UnhookWindowsHookEx(g_hook);
        g_hook=NULL;
    }
    if(g_msgHook!=NULL)
    {
        UnhookWindowsHookEx(g_msgHook);
        g_msgHook=NULL;
    }
    return TRUE;
}

BOOL APIENTRY DllMain( HINSTANCE hInstance,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
    )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if(g_hModule==NULL){
            timeBeginPeriod(1);
            g_hModule=hInstance;
        }
        break;
    case DLL_PROCESS_DETACH:
        if(g_hModule!=NULL)
        {
            g_hModule=NULL;
            timeEndPeriod(1);
        }
        break;
//		unHook();
    }
    return TRUE;
}
ZSExport forceKillActiveApp(lua_State* L)
{
    DWORD	PID;
    GetWindowThreadProcessId(GetForegroundWindow(),&PID);
    HANDLE	hProcess = OpenProcess(PROCESS_TERMINATE, false, PID);
    if(hProcess!=NULL)
    {
        TerminateProcess(hProcess , 0 );
        CloseHandle(hProcess);
    }
    return 0;
}

struct AutoAttach
{
    AutoAttach(HWND hWnd)
    :hThread(GetWindowThreadProcessId(hWnd,NULL))
    {
            AttachThreadInput(GetCurrentThreadId(),hThread,true);
    }
    ~AutoAttach()
    {
            AttachThreadInput(GetCurrentThreadId(),hThread,false);
    }
    DWORD hThread;
};

const HWND getFocusWindow()
{
    AutoAttach at(GetForegroundWindow());
    return GetFocus();
}
ZSExport setIMEStatus(lua_State* L)
{
    CheckArg(1)
    {
        ::SendMessage(getFocusWindow(), WM_IME_CONTROL, IMC_SETOPENSTATUS , lua_toboolean(L,1));
        ::SendMessage(GetForegroundWindow(), WM_IME_CONTROL, IMC_SETOPENSTATUS , lua_toboolean(L,1));
        ::SendMessage(ImmGetDefaultIMEWnd(getFocusWindow()), WM_IME_CONTROL, IMC_SETOPENSTATUS , lua_toboolean(L,1));
        ::SendMessage(ImmGetDefaultIMEWnd(GetForegroundWindow()), WM_IME_CONTROL, IMC_SETOPENSTATUS , lua_toboolean(L,1));

    }
    return 0;
}

ZSExport getIMEStatus(lua_State* L)
{
    bool ime=false;

    const HWND hWnd=getFocusWindow();
    const HWND hIMEWnd=ImmGetDefaultIMEWnd(hWnd);
    ime=static_cast<bool>(::SendMessage(hIMEWnd, WM_IME_CONTROL, IMC_GETOPENSTATUS , NULL));

    lua_pushboolean(L,ime);

    return 1;
}

ZSExport getActiveWindowName(lua_State* L)
{
    char pStr[256];
    GetWindowTextA(GetForegroundWindow(),pStr,255);

    lua_pushstring(L,pStr);
    return 1;
}

ZSExport getActiveWindowTopName(lua_State* L)
{
    HWND hCurrent=GetForegroundWindow();
    for(;;){
        const HWND hParent=GetParent(hCurrent);
        if(hParent==NULL){break;}
        if(hParent==hCurrent){break;}
        hCurrent=hParent;
    }
    char pStr[256];
    GetWindowTextA(hCurrent,pStr,255);

    lua_pushstring(L,pStr);
    return 1;
}

ZSExport getActiveWindowClassName(lua_State *L)
{
    char pStr[256];
    GetClassNameA(GetForegroundWindow(),pStr,255);

    lua_pushstring(L,pStr);
    return 1;
}

ZSExport getTime(lua_State *L)
{
    lua_pushinteger(L,timeGetTime());
    return 1;
}

ZSExport sleep(lua_State *L)
{
    CheckArg(1)
    {
        Sleep(lua_tointeger(L,1));
    }
    return 0;
}

/*
  const int WM_IS_IME_CONVERTING = WM_APP+0x1ec;

  ZSExport isIMEConverting(lua_State* L)
  {
  bool isConv=false;
  SendMessage(GetForegroundWindow(),WM_IS_IME_CONVERTING,(WPARAM)&isConv,(LPARAM)&isConv);
  lua_pushboolean(L,isConv);
  return 1;
  }
*/
