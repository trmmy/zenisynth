#include <windows.h>
#include <tchar.h>
#pragma data_seg("ZS_DATA")
HHOOK g_hook=NULL;
HHOOK g_msgHook=NULL;
HMODULE g_hModule=NULL;
bool g_isConverting=false;
#pragma data_seg()

//const int WM_IS_IME_ON = WM_APP+0x1e;
//const int WM_IS_IME_CONVERTING = WM_APP+0x1ec;
//const int WM_DLL_CALL = WM_APP+0xddd;

const HWND getZeniSynthHWND()
{

	return FindWindow(_T("#32770"),_T("ZeniSynth"));
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
		case		WM_IME_STARTCOMPOSITION:
			if(g_isConverting==false)
			{
				SendMessage(getZeniSynthHWND(),WM_IME_STARTCOMPOSITION,wParam,lParam);
			}
			g_isConverting=true;
			break;
		case		WM_IME_ENDCOMPOSITION:
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
		case		WM_IME_STARTCOMPOSITION:
			if(g_isConverting==false)
			{
				SendMessage(getZeniSynthHWND(),WM_IME_STARTCOMPOSITION,wParam,lParam);
			}
			g_isConverting=true;
			break;
		case		WM_IME_ENDCOMPOSITION:
			if(g_isConverting==true)
			{
				SendMessage(getZeniSynthHWND(),WM_IME_ENDCOMPOSITION,wParam,lParam);
			}
			g_isConverting=false;
			break;
/*		case	WM_IS_IME_CONVERTING:
			bool* bResult=(bool*)pStruct->wParam;
			if(bResult!=NULL){
				*bResult=g_isConverting;
			}
			break;*/

	}

	return CallNextHookEx(g_hook,code,wParam,lParam);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  reason,
                       LPVOID lpReserved
					 )
{
	if(g_hModule==NULL){g_hModule=hModule;}
    return TRUE;
}

void setHook()
{
	if(g_hook==NULL)
	{
		g_hook=SetWindowsHookEx(WH_CALLWNDPROC,&hookWndProc,g_hModule,0);
	}
	if(g_msgHook==NULL)
	{
		g_msgHook=SetWindowsHookEx(WH_GETMESSAGE,&hookMsgProc,g_hModule,0);
	}
}

void unHook()
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
}