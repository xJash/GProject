//---------------------------------
// 2008/12/02 �̰���
//---------------------------------

#include "CommonLogic.h"

#include "../common/char/CharManager/CharManager.h"

bool cltCommonLogic::InitLua()
{
	// C�Լ� ���
	LUA_RegisterCFunction( m_clLua, GetCharIDFromName );
	LUA_RegisterCFunction( m_clLua, GetCharNameFromID );
	LUA_RegisterCFunction( m_clLua, MoveChar );
	LUA_RegisterCFunction( m_clLua, WarpChar );
	LUA_RegisterCFunction( m_clLua, GetCharHaveItemNum );
	LUA_RegisterCFunction( m_clLua, GetCharEquipItemNum );

	return true;
}