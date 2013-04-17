#pragma once
#pragma warning(disable:4311)

#include "ipu.h"

#define VMFunc(name) int name(lua_State* L)

namespace VMFuncs
{
	namespace general
	{
		VMFunc(_out);
		VMFunc(isIMEConverting);
		VMFunc(sendInput);
	};

	namespace intOp
	{
		VMFunc(and);
		VMFunc(or);
		VMFunc(xor);
		VMFunc(shr);
		VMFunc(shl);
	}

	namespace cdata
	{
		VMFunc(_new);
		VMFunc(size);
		VMFunc(getPtr);
		VMFunc(rawGet);	//rawGet(ptr,size=4)
		VMFunc(rawSet);	//rawSet(TNUMBER ptr,TNUMBER data,TNUMBER size=4)
	};

};