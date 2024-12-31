//---------------------------------
// 2004/11/8 ���°�
//---------------------------------

//--------------------------------------
// Common
//--------------------------------------
#include "Char/CharServer/Char-Server.h"
#include "Char/CharManager/CharManager.h"
#include "PersonInfo.h"
#include "Order/Order.h"

//--------------------------------------
// CommonLogic
//---------------------------------------
#include "MagicMgr/MagicMgr.h"
#include "MagicMgr/MagicAttribute/MagicAttribute.h"

//--------------------------------------
// Server
//--------------------------------------
#include "../../Server/Server.h"


extern cltCommonLogic* pclClient;

// ���� ������ ������ �������� �����Ѵ�. 
void cltCharServer::CheckCurrentMagic( SI32 _siPrevActiveWeapon )
{
	if(GetCurrentMagic())
	{		
		//[����] Ȱ��ȭ�� ���⸸ üũ�ϸ� �ȴ�.
		SI32 siWeaponType	= pclCI->clCharItem.clItem[ActiveWeapon].GetType(pclClient->pclItemManager);
		SI32 siCurWeapon	= pclCI->clCharItem.clItem[ActiveWeapon].siUnique;
			

		CMagicAttribute *pMagicAttributePtr = pclClient->pclMagicManager->GetMagicAttributePtr();
		SI32 magictype = pMagicAttributePtr->GetMagicType(GetCurrentMagic());
		
		// ����� �ش��ϴ� ����Ÿ���� �˾Ƴ���. 
		bool bfailswitch = false;
		switch(magictype)
		{
		case MAGIC_TYPE_SWORD:
			if(siWeaponType != ITEMTYPE_SWORD )bfailswitch = true;
			break;
			
		case MAGIC_TYPE_SPEAR:
			if(siWeaponType != ITEMTYPE_SPEAR )bfailswitch = true;
			break;
			
		case MAGIC_TYPE_AXE:
			if(siWeaponType != ITEMTYPE_AXE)bfailswitch = true;
			break;
			
		case MAGIC_TYPE_STAFF:	
			if(siWeaponType != ITEMTYPE_STAFF )bfailswitch = true;
			break;
			
		case MAGIC_TYPE_BOW:
			if(siWeaponType != ITEMTYPE_BOW )bfailswitch = true;
			break;
			
		case MAGIC_TYPE_GUN:	
			if(siWeaponType != ITEMTYPE_GUN )bfailswitch = true;
			break;

		case MAGIC_TYPE_MON:		bfailswitch = true;	break;
		case MAGIC_TYPE_SOULGUARD:	bfailswitch = true; break;
		case MAGIC_TYPE_SKILL_BOOK:	
			{
				switch( siWeaponType )
				{
					case ITEMTYPE_SWORD:
					case ITEMTYPE_SPEAR:
					case ITEMTYPE_AXE:
					case ITEMTYPE_STAFF:
					case ITEMTYPE_BOW:
					case ITEMTYPE_GUN:	
						{
							_siPrevActiveWeapon == siCurWeapon ? bfailswitch = false 
															   : bfailswitch = true; 
							break;
						}
						
	
					default:			
						bfailswitch = true; break;
				}
			}
			break;
		default:	bfailswitch = true;	break;
		}		
		
		// ������ ���Ⱑ �������� �ʴٸ� ������ Magic�� �ʱ�ȭ �Ѵ�.
		if(bfailswitch)
		{
			SetCurrentMagic(0, 0);
			m_clMagicBufMgr.Init();
		}		
	}
	// Client���� �˷��ش�.
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGEMAGIC, GetCurrentMagic());
	SendNetMsg((sPacketHeader*)&clMsg);
}


// ������ ���� ������ ���� ����. 
bool cltCharServer::MagicInAttackAction()
{
	if(IsNPC(GetCharUnique()) == false && IsInstanceNPC(GetCharUnique()) == false )return false;
	if(IsNPC(GetCharUnique()) == false && IsInstanceNPC(GetCharUnique()) == false )return false;

	// ��ȯ���ΰ�쿡�� ���� ������� �ʴ´�. 
	if(GetSummonParentID())
	{
		if(rand() % 5)return false;
	}
	else
	{
		if(rand() % 2)return false;
	}

	SI32 magickind = pclKI->siMagic;
	switch(magickind)
	{
	case 0:
		{
			// ��ȯ���ΰ�쿡 ���������� ������� �ʴ´�.
			SI32 parentid = GetSummonParentID() ;
			if ( pclCM->IsValidID(parentid) )
				return false ;
		}
		break;
		// ġ���ϱ� ����� �ִٸ�, 
		// �ֺ����� ġ���� ĳ���͸� ã�´�. 
	case MAGIC_MON_HEAL:
		{
			if(HealAI() == true)
			{
				return true;
			}
		}
		break;
	default:
		SI32 returnval = 0;

		// �ɵ������� ��쿡�� ����Ѵ�.
		if ( MAGIC_CASTTYPE_ACTIVE == GetCurrentMagicCastType() )
		{
			if(CanMagic(clAttackTarget.GetAttackID(), magickind, &returnval) == true)
			{
				bBusySwitch = false;
				
				pclClient->pclOrderManager->OrderMagic(GetID(), clAttackTarget.GetAttackID(), magickind, BY_COMPUTER);
				
				return true;		
			}
		}
	}

	return false;
}

void cltCharServer::SetMagicDelay(SI32 delay)
{
	siMagicDelay = delay;
}

SI32 cltCharServer::GetMagicDelay()
{
	return siMagicDelay ;
}

