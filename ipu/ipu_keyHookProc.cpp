#include "stdafx.h"
#include "ipu.h"

#pragma warning(disable:4244)	//cast LPARAM to int

LRESULT CALLBACK IPU::keyHookProc(int nCode, WPARAM wp, LPARAM lp) {
    AutoCS(&IPU::getInstance().m_csKeyHook);

    if( (nCode<0) || (IPU::getInstance().m_busy==true) ) {
        return
            CallNextHookEx(
                IPU::getInstance().m_hHook,
                nCode,
                wp,
                lp);
    }

    IPU::getInstance().m_busy=true;
    {

        lua_getglobal(IPU::getInstance().m_L, "debug");        // push debug-table on the stack
        lua_getfield(IPU::getInstance().m_L,-1, "traceback");

        KBDLLHOOKSTRUCT* pDHStruct =  (KBDLLHOOKSTRUCT*)lp;

        lua_pushstring(IPU::getInstance().m_L,"main");
        lua_gettable(IPU::getInstance().m_L,LUA_GLOBALSINDEX);
        lua_pushinteger(IPU::getInstance().m_L,pDHStruct->vkCode);
        lua_pushinteger(IPU::getInstance().m_L,pDHStruct->scanCode);

        {
            DWORD flags=0;

            if(pDHStruct->flags&LLKHF_UP){
                flags|=KEYEVENTF_KEYUP;
            }
            
            if(pDHStruct->flags&LLKHF_EXTENDED){
                flags|=KEYEVENTF_EXTENDEDKEY;
            }
            
            lua_pushinteger(IPU::getInstance().m_L,flags);
        }

        {
            lua_pushinteger(IPU::getInstance().m_L, pDHStruct->flags&LLKHF_ALTDOWN ? 1 : 0);
        }
        if(lua_pcall(IPU::getInstance().m_L,4,1,-5)) {
            out("[SCRIPT ERROR]\n"<<lua_tostring(IPU::getInstance().m_L,-1));
        } else if(lua_tointeger(IPU::getInstance().m_L, -1)){
            LRESULT result = CallNextHookEx(IPU::getInstance().m_hHook, nCode,wp,lp);
            IPU::getInstance().m_busy=false;
            return result;			
        }

    }
    IPU::getInstance().m_busy=false;
    return true;

}
