#include "stdafx.h"
#include "ipu.h"

#undef out
#define out2(expr) {                                            \
	std::wstringstream str;                                 \
	str<<__FILE__<<" : "<<__LINE__<<" > "<<expr<<"\r\n";    \
	IPU::addLog(str.str());                                 \
    }

#include "boost/filesystem.hpp"
#include "boost/regex.hpp"

namespace fs=boost::filesystem;

typedef int(*OnLoadFunc)(ZSLogFunction);
typedef int(*OnLoadFuncEx)(ZSLogFunction,lua_State*);

void IPU::loadModules()
{
    luaopen_base(m_L);
    luaopen_debug(m_L);
    luaopen_os(m_L);
    luaopen_string(m_L);
    luaopen_math(m_L);

    registerVMFunctions();
    std::string modulePath="modules";

    fs::directory_iterator end_itr;
    for(	fs::directory_iterator itr( modulePath );
                itr != end_itr;
                ++itr )
    {
        std::string filename=itr->path().filename();
        if(boost::regex_match(filename,boost::regex("[^.]*[.]dll")))
        {
            out2("loading "<<filename.c_str());
            const HMODULE hDLL=LoadLibraryA((modulePath+"\\"+filename).c_str());
            if(hDLL==NULL){
                out2("LoadLibrary failed"<< " with GetLastError=" <<GetLastError());
                continue;
            }


            {
                OnLoadFunc pOnLoadFunc=(OnLoadFunc)GetProcAddress(hDLL,"OnLoad");
                if(pOnLoadFunc==NULL){
                    out2("LoadLibrary failed"<< " with GetLastError=" <<GetLastError());
                    FreeLibrary(hDLL);
                    continue;
                }
                pOnLoadFunc(&IPU::addLog);
            }

            m_hLoadedModules.push_back(hDLL);

            OnLoadFuncEx pOnLoadFuncEx=(OnLoadFuncEx)GetProcAddress(hDLL,"OnLoadEx");
            if(pOnLoadFuncEx){	pOnLoadFuncEx(&IPU::addLog,m_L);	}

            boost::smatch m;
            std::string moduleName;
            boost::regex_search(filename,m,boost::regex("([^.]+)[.]dll"));
            moduleName=m.str(1);
            const BYTE* hMod=(BYTE*)GetModuleHandleA(filename.c_str());
            const IMAGE_NT_HEADERS *pnt=(IMAGE_NT_HEADERS*)&hMod[PIMAGE_DOS_HEADER(hMod)->e_lfanew];
            const IMAGE_EXPORT_DIRECTORY *exp=(IMAGE_EXPORT_DIRECTORY*)&hMod[pnt->OptionalHeader.DataDirectory->VirtualAddress];
            const DWORD *dwFunctions=(DWORD*)&hMod[exp->AddressOfNames];
			
            lua_newtable(m_L);	//TABLE
            lua_setglobal(m_L,moduleName.c_str());	//TABLE=NAME
            lua_getglobal(m_L,moduleName.c_str());	//TABLE
            for(DWORD ctr=0;ctr<exp->NumberOfNames;ctr++)
            {
                const std::string funcName=(char*)&hMod[dwFunctions[ctr]];
                if(boost::regex_match(funcName,boost::regex("[?].*")))
                {
                    out2(funcName.c_str()<<" is a C++ function. skipping");
                    continue;
                }

                if(funcName!="OnLoad")
                {
                    lua_pushstring(m_L,funcName.c_str());	//TABLE|STRING
                    lua_pushcfunction(m_L,(lua_CFunction)GetProcAddress((HMODULE)hMod,funcName.c_str()));	//TABLE|STRING|FUNCTION
                    lua_settable(m_L,-3);	//TABLE
                    out2("importing "<<moduleName.c_str()<<"."<<funcName.c_str());
                }
            }
            lua_pop(m_L,1);//
        }
    }

}

#undef out2
#define out(expr) {                                             \
	std::wstringstream str;                                 \
	str<<__FILE__<<" : "<<__LINE__<<" > "<<expr<<"\r\n";    \
	IPU::addLog(str.str());                                 \
    }
