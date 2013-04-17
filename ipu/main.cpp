#include "stdafx.h"
#include "ipu.h"

#ifdef _DEBUG
#include <crtdbg.h>
	#define _CRTDBG_MAP_ALLOC
#endif

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	HANDLE hMutex=CreateMutex(NULL,TRUE,_T("ZeniSynth"));
	if(GetLastError()==ERROR_ALREADY_EXISTS){	return 0;	}

	IPU::getInstance().create();
	IPU::getInstance().run();

	ReleaseMutex(hMutex);

	return 0;
}