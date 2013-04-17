#include "stdafx.h"
#include "vmfuncs.h"

namespace VMFuncs
{
    namespace general
    {
        VMFunc(_out)
        {
            CheckArg(1)
            {
                switch(lua_type(L,1))
                {
                case LUA_TSTRING:
                    out(lua_tostring(L,1));
                    break;
                case LUA_TNUMBER:
                    out(lua_tonumber(L,1));
                    break;
                case LUA_TBOOLEAN:
                    out(lua_toboolean(L,1));
                    break;
                case LUA_TUSERDATA:
                case LUA_TLIGHTUSERDATA:
                    out((unsigned int)lua_touserdata(L,1));
                default:
                    out("unknown type: "<<lua_typename(L,lua_type(L,1)));
                    break;
                }
            }
            return 0;
        }

        VMFunc(isIMEConverting)
        {
            lua_pushboolean(L,IPU::getInstance().m_isConverting);
            return 1;
        }

        VMFunc(sendInput)
        {
            CheckArg(2)
            {
                const WORD VK=static_cast<WORD>(lua_tonumber(L,1));
                INPUT i;

                i.type=INPUT_KEYBOARD;
                KEYBDINPUT k;
                ZeroMemory(&k,sizeof(k));
                k.wVk=VK;


                if(lua_gettop(L)==3)
                {
                    k.wScan=static_cast<WORD>(lua_tointeger(L,2));
                    k.dwFlags=static_cast<WORD>(lua_tointeger(L,3));
                }
                else
                {
                    k.dwFlags=static_cast<WORD>(KEYEVENTF_KEYUP*lua_toboolean(L,2));
                }

                i.ki=k;

                SendInput(1,&i,sizeof(i));


            }
            return 0;
        }
    };
};
