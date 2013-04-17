#pragma once

#include <boost/foreach.hpp>
#define foreach(var,col) BOOST_FOREACH(var,col)

#include <sstream>
#include <iostream>
#include <shellapi.h>

#include "resource.h"

#include "strings.h"
#include	<vector>

extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}
#pragma comment(lib,"lua5.1.lib")
#pragma warning(disable:4098)	//cast LPARAM to int

#include <process.h>	//_beginthread

#include <zenisynth.h>

#define out(expr) {\
	std::wstringstream str;\
	str<<__FILE__<<" : "<<__LINE__<<" > "<<expr<<"\r\n";\
	IPU::addLog(str.str());\
	}

struct Error
{
	explicit Error(wchar_t* m)
		:msg(m)
	{
	}
	std::wstring msg;
};
struct AutoCS
{
	AutoCS(CRITICAL_SECTION* pCS):m_pCS(pCS){}
	~AutoCS(){::LeaveCriticalSection(m_pCS);}
	CRITICAL_SECTION* m_pCS;
};
class IPU
{

public:
	void create();
	void loadModules();
	void run();
	static IPU& getInstance();
	std::wstringstream m_logString;

	static void addLog(std::wstring& str);


	bool m_isConverting;

private:

	IPU()
		:m_isConverting(false)
		,m_isLuaOK(false)
		,m_hHook(NULL)
	{
		::InitializeCriticalSection(&m_csLog);
		::InitializeCriticalSection(&m_csKeyHook);
	}	//Make this class a singleton
	~IPU()
	{
		m_logThreadExitSign=true;
		for(;IPU::getInstance().m_logThreadActive;){}
		//MessageBox(NULL,L"Log Destructor Completed",L"",MB_OK);

		lua_close(m_L);
		unHook();
		Shell_NotifyIcon( NIM_DELETE, &IPU::getInstance().m_nIcon);
		::DeleteCriticalSection(&m_csLog);
		::DeleteCriticalSection(&m_csKeyHook);
		foreach(HMODULE h,m_hLoadedModules)
		{
typedef int(*ZSFreeFunction)(void);
			ZSFreeFunction f =(ZSFreeFunction)GetProcAddress(h,"OnFree");
			if(f){	f(); }
//			FreeLibrary(h);	//this line causes unhandled exeption when DLL thread is still running
		}
	}

	void registerVMFunctions();

	CRITICAL_SECTION m_csLog;
	CRITICAL_SECTION m_csKeyHook;

	lua_State *m_L;

	FILE* m_hLogFile;

	bool m_isLuaOK;

	bool m_logThreadExitSign;
	bool m_logThreadActive;
	HWND m_hDummyWnd;
	HWND m_hMainWnd;

	NOTIFYICONDATA m_nIcon;

	void createWindow();
		
	HACCEL m_hAccelTable;

	void tryHook()
	{
		if(m_isLuaOK==true)
		{
			if(m_hHook==NULL)
			{
				out("Main Hook Procedure Activating");
				IPU::getInstance().m_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyHookProc, GetModuleHandle(NULL),0);
				EnableMenuItem(GetMenu(m_hMainWnd), ID_HOOK_HOOK, MF_BYCOMMAND | MF_GRAYED);
				EnableMenuItem(GetMenu(m_hMainWnd), ID_HOOK_UNHOOK, MF_BYCOMMAND | MF_ENABLED);
			}
			else
			{
				out("Main Hook Procedure is already activated");
			}
		}
		else
		{
			out("Can not start hooking because of lua failure")
		}
	}
	void unHook()
	{
		if(m_hHook!=NULL)
		{
			out("DeActivating Main Hook Procedure");
			UnhookWindowsHookEx(m_hHook);
			m_hHook=NULL;
			EnableMenuItem(GetMenu(m_hMainWnd), ID_HOOK_HOOK, MF_BYCOMMAND | MF_ENABLED);
			EnableMenuItem(GetMenu(m_hMainWnd), ID_HOOK_UNHOOK, MF_BYCOMMAND | MF_GRAYED);
		}
		else
		{
			out("Main Hook Procedure is already DeActivated");
		}
	}

	std::vector<HMODULE>	m_hLoadedModules;

	static void IPU::clearLog();
	static void IPU::updateLog(void*);

	bool m_busy;
	HHOOK m_hHook;
	HWND m_hLog;
	HWND m_hConsole;
	static LRESULT CALLBACK mainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK keyHookProc(int nCode, WPARAM wp, LPARAM lp);

	static INT_PTR CALLBACK aboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static INT_PTR CALLBACK keyEditorProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

};



