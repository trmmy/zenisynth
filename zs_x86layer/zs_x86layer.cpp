#include <windows.h>
#include <tchar.h>

const HWND getMainZeniSynthHWND() {
    return
        FindWindow(
            _T("ZeniSynth"),
            _T("ZeniSynth main window"));
}

int APIENTRY _tWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow) {
    
    const HANDLE hMutex=CreateMutex(NULL,TRUE,_T("ZeniSynth_x86HookLayer"));
    if(GetLastError()==ERROR_ALREADY_EXISTS){  return 0;  }

    const HMODULE hHookDLL=LoadLibraryA("zs_x86hook.dll");
    if(hHookDLL==NULL) {
        return 1;
    }
    
    typedef void(*PFUNC)(void);

    const PFUNC pSetHook=(PFUNC)GetProcAddress(hHookDLL,"setHook");
    if(pSetHook==NULL) {
        return 1;
    }
    
    const PFUNC pUnHook=(PFUNC)GetProcAddress(hHookDLL,"unHook");
    if(pUnHook==NULL) {
        return 1;
    }

    pSetHook();

    for(;;) {
        Sleep(10000);
        if(getMainZeniSynthHWND()==NULL) {
            break;
        }
    }

    pUnHook();

    FreeLibrary(hHookDLL);

    return 0;
}
