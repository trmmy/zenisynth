#include "stdafx.h"
#include "vmfuncs.h"
namespace VMFuncs
{
    namespace cdata
    {
        VMFunc(_new)
        {
            int size=(int)lua_tointeger(L,1);
            int* newData=(int*)lua_newuserdata(L,4+size);
            newData[0]=size;
            luaL_getmetatable(L,"cdata");
            lua_setmetatable(L,-2);

            return 1;
        }

        VMFunc(size)
        {
            int* pData=(int*)lua_touserdata(L,1);
            lua_pushinteger(L,pData[0]);
            return 1;
        }

        VMFunc(getPtr)
        {
            lua_pushinteger(L,(int)lua_touserdata(L,1));
            return 1;
        }

        VMFunc(rawGet)	//rawGet(ptr,size=4)
        {
            const void* const ptr=(void*)(lua_tointeger(L,1)+sizeof(int));
            const int size=
                2<=lua_gettop(L)	?
                lua_tointeger(L,2)
                :
                4;

            unsigned char actualData[4]={0,0,0,0};
            for(int i=0;i<4;i++)
            {
                if(size<=i){break;}
                actualData[i]=((unsigned char*)ptr)[i];
            }
            lua_pushinteger(L,*((int*)actualData));
            return 1;
        }

        VMFunc(rawSet)	//rawSet(TNUMBER ptr,TNUMBER data,TNUMBER size=4)
        {
            unsigned char* const ptr=(unsigned char*)(lua_tointeger(L,1)+sizeof(int));
            const unsigned int actualData=lua_tointeger(L,2);
            const int size=
                3<=lua_gettop(L)	?
                lua_tointeger(L,3)
                :
                4;

            for(int i=0;i<4;i++)
            {
                if(size<=i){break;}
                ptr[i]=((unsigned char*)&actualData)[i];
            }
            return 1;
        }
    };
};
