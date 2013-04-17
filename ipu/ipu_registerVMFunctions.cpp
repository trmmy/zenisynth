#include "stdafx.h"
#include "vmfuncs.h"

using namespace VMFuncs;



void IPU::registerVMFunctions()
{
	lua_register(m_L,"out",general::_out);
	lua_register(m_L,"sendInput",general::sendInput);
	lua_register(m_L,"isIMEConverting",general::isIMEConverting);

	lua_register(m_L,"AND",intOp::and);
	lua_register(m_L,"OR",intOp::or);
	lua_register(m_L,"XOR",intOp::xor);
	lua_register(m_L,"SHR",intOp::shr);
	lua_register(m_L,"SHL",intOp::shr);

	luaL_reg cdata[]=
	{
		{"new",cdata::_new},
		{"size",cdata::size},
		{"getPtr",cdata::getPtr},
		{"rawGet",cdata::rawGet},
		{"rawSet",cdata::rawSet},
		{NULL,NULL}
	};
	luaL_register(m_L, "cdata",cdata);

	luaL_newmetatable(m_L,"cdata");	//METAT|REGT
	lua_pushstring(m_L,"__index");		//STRING|METAT|REGT
	lua_pushvalue(m_L,-3);				//REGT|STRING|METAT|REGT
	lua_rawset(m_L,-3);					//METAT|REGT
//	lua_pushstring(m_L,"__metatable");		//STRING|METAT|REGT
//	lua_pushvalue(m_L,-3);				//REGT|STRING|METAT|REGT
//	lua_rawset(m_L,-3);					//METAT|REGT
	lua_pop(m_L,1);
}