#include "stdafx.h"
#include "ipu.h"

#pragma warning(disable:4244)  //cast LPARAM to int

const int WM_NOTIFYICON = WM_USER+100;

LRESULT CALLBACK IPU::mainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    IPU& This=IPU::getInstance();

    switch (message)
    {
    case WM_IME_STARTCOMPOSITION:
//        out("START COMPOSITION");
        This.m_isConverting=true;
        break;
    case WM_IME_ENDCOMPOSITION:
//        out("END COMPOSITION");
        This.m_isConverting=false;
        break;
    case WM_INITDIALOG:

        SendMessage(hWnd,WM_SETICON,ICON_SMALL,(LPARAM)LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ZS)));


        IPU::getInstance().m_hMainWnd=hWnd;
        IPU::getInstance().m_hLog=GetDlgItem(hWnd,IDC_LOG);
        IPU::getInstance().m_hConsole=GetDlgItem(hWnd,IDC_COMBO);
        SendMessage(IPU::getInstance().m_hLog,EM_SETLIMITTEXT,1024*1024*8,0);

        out("Window OK");


        {
            IPU::getInstance().m_nIcon.cbSize = sizeof( NOTIFYICONDATA) ;
            IPU::getInstance().m_nIcon.uID = 1 ;
            IPU::getInstance().m_nIcon.hWnd = hWnd ;
            IPU::getInstance().m_nIcon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP ;
            IPU::getInstance().m_nIcon.hIcon = LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ZS));
            IPU::getInstance().m_nIcon.uCallbackMessage = WM_NOTIFYICON ;

            lstrcpy(IPU::getInstance().m_nIcon.szTip,_T("ZeniSynth"));

            ::Shell_NotifyIcon( NIM_ADD, &IPU::getInstance().m_nIcon);
        }

        MoveWindow(hWnd,0,0,640,480,TRUE);

        out("Tasktray OK");

        This.tryHook();

        if(This.m_isLuaOK)
        {
            out(strings::version<<" Ready");
            SetTimer(hWnd,0,2000,0);
        }
        else
        {
            out("/// Detected one or more error(s) ///");
        }
		

        return TRUE;

    case WM_SIZE:
    {
        int width=LOWORD(lParam);
        int height=HIWORD(lParam);

        RECT rConsole;
        GetWindowRect(This.m_hConsole,&rConsole);

        MoveWindow(This.m_hConsole
                   ,0
                   ,height-(rConsole.bottom-rConsole.top)
                   ,width
                   ,16,TRUE);
        MoveWindow(This.m_hLog,0,0,width,height-20,TRUE);

        if(wParam==SIZE_MINIMIZED){    ShowWindow(hWnd,SW_HIDE);    }

        break;
    }

    case WM_NOTIFYICON:
    {
        const int wmTray=lParam;
        switch(wmTray)
        {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
				
            if(IsWindowVisible(This.m_hMainWnd)==TRUE)
            {
                ShowWindow(This.m_hMainWnd,SW_HIDE);
            }
            else
            {
                ShowWindowAsync(This.m_hMainWnd,SW_SHOWNORMAL);
                SetForegroundWindow(This.m_hMainWnd);
            }

            break;
        case WM_RBUTTONDOWN:
        {
            POINT pos;
            GetCursorPos(&pos);

            TrackPopupMenu
                (
                    GetSubMenu
                    (
                        LoadMenu(GetModuleHandle(NULL),MAKEINTRESOURCE(IDP_TRAY))
                        ,0
                        )
                    ,TPM_LEFTALIGN|TPM_RIGHTBUTTON,pos.x,pos.y,0,hWnd,NULL
                    );
            break;
        }
        }
    }
    break;

    case WM_COMMAND:
    {
        const int wmId    = LOWORD(wParam);
        const int wmEvent = HIWORD(wParam);

        switch (wmId)
        {
        case ID_FILE_RELOAD:
            out("RELOAD");
            This.unHook();
            This.m_isLuaOK=false;
            lua_close(This.m_L);
            This.m_L=lua_open();

            This.loadModules();

            if(luaL_dofile(This.m_L,"main.lua")!=0)
            {
                out("////////////////Error detail////////////////");
                out(lua_tostring(This.m_L,-1));
                out("////////////////////////////////////////////")
                    }
            else
            {
                out("lua ok");
                This.m_isLuaOK=true;
                This.tryHook();
            }
            break;
        case IDM_SHOWKEYEDITOR:
            CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_KEYEDITOR), hWnd, keyEditorProc);
            break;
        case IDM_ABOUT:
            DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, aboutProc);
            break;
        case IDM_EXIT:
            This.unHook();
            EndDialog(hWnd,NULL);
            break;
        case ID_HOOK_HOOK:
            This.tryHook();
            break;
        case ID_HOOK_UNHOOK:
            This.unHook();
            break;
        case IDC_LOG:
            break;
        case IDC_COMBO:
            /*    switch(wmEvent)
                  {
                      case CBN_KILLFOCUS
                  }*/
            //out(wmEvent);
					
            break;
        case 1:	//Default ID
            TCHAR buff[513];
            GetWindowText(GetDlgItem(hWnd,IDC_COMBO),buff,512);
            out(buff);
            SetWindowText(IPU::getInstance().m_hConsole,_T(""));
//          updateLog();

            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_TIMER:
        KillTimer(hWnd,0);
    case WM_CLOSE:
    {
        ShowWindow(hWnd,SW_HIDE);
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc;
        hdc = BeginPaint(hWnd, &ps);
        // TODO: •`‰æƒR[ƒh‚ð‚±‚±‚É’Ç‰Á‚µ‚Ä‚­‚¾‚³‚¢...
        EndPaint(hWnd, &ps);
    }
    break;
/*    case WM_DESTROY:
        PostQuitMessage(0);
        break;*/
    default:
        return false;
    }
    return 0;
}

