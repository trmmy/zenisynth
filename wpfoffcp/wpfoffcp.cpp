#define WIN32_LEAN_AND_MEAN
#define STRICT

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

typedef DWORD (WINAPI *PDISWFP)(DWORD dwA, WCHAR *szFile, DWORD dwB);

int main(int argc, char *argv[])
{
    if(argc < 3){
        printf("%s [src file] [dest file]\n", argv[0]);
        return 1;
    }
    
    char *srcfile  = argv[1];
    char *destfile = argv[2];
    
    HMODULE hMod = NULL; // sfc_os.dll handle
    PDISWFP pWfp = NULL; // function ptr
    
    try{
        if((hMod = LoadLibraryA("sfc_os.dll")) == NULL)
            throw 1;

        if((pWfp = (PDISWFP)GetProcAddress(hMod, (LPCSTR)5)) == NULL)
            throw 2;

        WCHAR wdestfile[1024];
        MultiByteToWideChar(CP_ACP, 0, 
                            destfile, -1, wdestfile, 1024 * sizeof(WCHAR));
        
        if(pWfp(0, wdestfile, -1))
            throw 3;

        CopyFileA(srcfile, destfile, FALSE);
        printf("Copy \"%s\" to \"%s\" successed!\n", srcfile, destfile);

    }catch(int err){
        printf("Error: %d\n", err);
    }
    
    FreeLibrary(hMod);
    return 0;
}
