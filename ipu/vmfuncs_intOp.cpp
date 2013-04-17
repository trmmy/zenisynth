#include "stdafx.h"
#include "vmfuncs.h"

namespace VMFuncs
{
	namespace intOp
	{
		VMFunc(and)
		{
			lua_pushinteger(L,lua_tointeger(L,1)&lua_tointeger(L,2));
			return 1;
		}
		VMFunc(or)
		{
			lua_pushinteger(L,lua_tointeger(L,1)|lua_tointeger(L,2));
			return 1;
		}
		VMFunc(xor)
		{
			lua_pushinteger(L,lua_tointeger(L,1)^lua_tointeger(L,2));
			return 1;
		}
		VMFunc(shr)
		{
			lua_pushinteger(L,lua_tointeger(L,1)>>lua_tointeger(L,2));
			return 1;
		}
		VMFunc(shl)
		{
			lua_pushinteger(L,lua_tointeger(L,1)<<lua_tointeger(L,2));
			return 1;
		}
	};
};