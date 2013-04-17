
#include "stdafx.h"
#include "ipu.h"


void IPU::run() {
    out("run");
    DialogBox(
        GetModuleHandle(NULL),
        MAKEINTRESOURCE(IDD_MAIN),
        m_hDummyWnd,
        (DLGPROC)mainWndProc);
}

IPU& IPU::getInstance() {
    static IPU ipu;
    return ipu;
}

void IPU::clearLog() {
    IPU::getInstance().m_logString.str(L"");
//  updateLog();
}

void IPU::createWindow() {
    {
        WNDCLASSEX wcex;

        wcex.cbSize = sizeof(WNDCLASSEX);		
        wcex.style  = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = DefWindowProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = GetModuleHandle(NULL);
        wcex.hIcon  = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ZS));
        wcex.hCursor  = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(IDC_MAIN);
        wcex.lpszClassName = strings::windowClass;
        wcex.hIconSm  = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ZS));

        RegisterClassEx(&wcex);
    }

    m_hDummyWnd
        = CreateWindowEx(
            WS_EX_TOOLWINDOW,
            strings::windowClass,
            strings::windowTitle,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,0,
            CW_USEDEFAULT,0,
            NULL,
            NULL,
            GetModuleHandle(NULL),
            NULL);

    if (!m_hDummyWnd) {
        MessageBox(
            NULL,
            _T("CreateWindowEx failed"),
            _T("CreateWindowEx failed"),
            MB_OK);
        ::exit(0);
    }

    out("Main window OK");
}

INT_PTR CALLBACK IPU::aboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK
            || LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    
    return (INT_PTR)FALSE;
}


INT_PTR CALLBACK IPU::keyEditorProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
        ShowWindow(hWnd,SW_SHOW);
        return (INT_PTR)TRUE;
    case WM_CLOSE:
        //EndDialog(hWnd, LOWORD(wParam));
        DestroyWindow(hWnd);
        break;
    }
    
    return (INT_PTR)FALSE;
}
