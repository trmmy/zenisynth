#include <windows.h>
#include <zenisynth.h>

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved) {
    return TRUE;
}

void _addLog(std::wstring&){
}

ZSLogFunction addLog=&_addLog;

ZSExport OnLoad(ZSLogFunction newAddLog) {
    addLog=newAddLog;  //assign log function
    return TRUE;
}
