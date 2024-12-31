#ifndef _MSGTYSUMMON_H
#define _MSGTYSUMMON_H

//--------------------------
// Common
//-------------------------
#include "PersonInfo.h"


//-------------------------------------------
// ��ȯ�� �̸� �ٲٱ�  
//-------------------------------------------
class cltGameMsgRequest_SummonNameChange
{
public:
	SI16	siCharUnique;
	SI32	siSummonID;
	TCHAR	strSummonName[ MAX_SUMMON_NAME ];
	cltGameMsgRequest_SummonNameChange( SI16 charunique, SI32 summonid, TCHAR *Name )
	{
		siCharUnique  = charunique;
		siSummonID = summonid;
		MStrCpy( strSummonName, Name , MAX_SUMMON_NAME );
	}
};

class cltGameMsgResponse_SummonNameChange
{
public:
	SI16	siCharUnique;
	SI32	siSummonID;
	TCHAR   strSummonName[ MAX_SUMMON_NAME ];

	cltGameMsgResponse_SummonNameChange( SI16 charunique, SI32 summonid, TCHAR *Name )
	{
		siCharUnique = charunique;
		siSummonID = summonid;
		MStrCpy( strSummonName, Name, MAX_SUMMON_NAME );
	}

};

//-------------------------------------------
// ��ȯ�� Ǯ���ֱ�. 
//-------------------------------------------
class cltGameMsgRequest_SummonFree{
public:
	SI16	siCharUnique;
	SI32	siSummonID;

	cltGameMsgRequest_SummonFree(SI16 charunique, SI32 summonid)
	{
		siCharUnique	= charunique;
		siSummonID		= summonid;
	}
};

class cltGameMsgResponse_SummonFree{
public:
	SI16	siCharUnique;
	SI32	siSummonID;

	cltGameMsgResponse_SummonFree(SI16 charunique, SI32 summonid)
	{
		siCharUnique	= charunique;
		siSummonID		= summonid;
	}
};

//-------------------------------------------
// ��ȯ�� ���� ��û 
//-------------------------------------------
class cltGameMsgRequest_Summon{
public:
	SI16	siCharUnique;
	SI32	siSummonID;

	cltGameMsgRequest_Summon(SI16 charunique, SI32 summonid)
	{
		siCharUnique	= charunique;
		siSummonID		= summonid;
	}
};


class cltGameMsgResponse_Summon{
public:
	SI16			siCharUnique;
	UI08			siSummonIndex;
	cltSummon		clSummon;
	
	cltGameMsgResponse_Summon(SI16 charunique, UI08 summonindex, cltSummon *summon)
	{
		siCharUnique	= charunique;
		siSummonIndex	= summonindex;
		clSummon.Set(summon);
	}
};
//-------------------------------------------
// Base ��ȯ�� ���� ��û 7����
//-------------------------------------------
class cltGameMsgRequest_BaseSummon{
public:
	SI32	siSummonID;

	cltGameMsgRequest_BaseSummon( SI32 summonid)
	{
		siSummonID		= summonid;
	}
};


class cltGameMsgResponse_BaseSummon{
public:
	SI16			siCharUnique;
	UI08			siSummonIndex;
	cltSimpleSummon		clSummonBase;

	cltGameMsgResponse_BaseSummon(SI16 charunique, UI08 summonindex, cltSimpleSummon *summon)
	{
		siCharUnique	= charunique;
		siSummonIndex	= summonindex;
		clSummonBase.Set(summon);
	}
};

//---------------------------------------------------------------------
// ��ȯ���� Base���� ����Ҽ� �ֵ��� 3���� ������ ���ϴ� ���Կ� �ִ´�
//---------------------------------------------------------------------
class cltGameMsgRequest_SlotIn{
public:
	SI32	siSummonID	;
	SI08	siSlotIndex	;

	cltGameMsgRequest_SlotIn( SI32 summonid, SI08 SlotIndex)
	{
		siSummonID		= summonid	;
		siSlotIndex		= SlotIndex	;
	}
};


class cltGameMsgResponse_SlotIn{
public:
	SI16				siCharUnique	;
	UI08				siSLotIndex	;
	cltSummon			clSummon		;
	cltSummonItemInfo	clSummonItem		;

	cltGameMsgResponse_SlotIn(SI16 charunique, UI08 SLotindex, cltSummon *summon, cltSummonItemInfo	*Summonitem )
	{
		siCharUnique	= charunique	;
		siSLotIndex		= SLotindex	;
		clSummon.Set( summon )			;
		clSummonItem.Set( Summonitem )	;
	}
};
//---------------------------------------------------------------------
// ��ȯ���� SLOT���� ������.
//---------------------------------------------------------------------
class cltGameMsgRequest_SlotOut{
public:
	SI08	siSummonIndex	;
	SI32	siSummonID	;

	cltGameMsgRequest_SlotOut( SI32 summonid, SI08 SummonIndex)
	{
		siSummonID			=	summonid	;
		siSummonIndex		=	SummonIndex	;
	}
};


class cltGameMsgResponse_SlotOut{
public:
	SI16				siCharUnique	;
	UI08				siSummonIndex	;

	cltGameMsgResponse_SlotOut(SI16 charunique, UI08 Summonindex)
	{
		siCharUnique		= charunique	;
		siSummonIndex		= Summonindex	;
	}
};
//-------------------------------------------
// ��ȯ�� TAKE IN OUT ��û 
//-------------------------------------------
class cltGameMsgRequest_SummonTakeInOut{
public:
	SI16	siCharUnique;
	SI32	siSummonID;
	SI16	siStatus;

	cltGameMsgRequest_SummonTakeInOut(SI16 charunique, SI32 summonid, SI16 statustype)
	{
		siCharUnique	= charunique;
		siSummonID		= summonid;
		siStatus		= statustype;
	}
};


class cltGameMsgResponse_SummonTakeInOut{
public:
	SI16	siCharUnique;
	SI32	siSummonID;
	SI16	siStatus;

	cltGameMsgResponse_SummonTakeInOut(SI16 charunique, SI32 summonid, SI16 statustype)
	{
		siCharUnique	= charunique;
		siSummonID		= summonid;
		siStatus		= statustype;
	}
};

//-------------------------------------------
// ��ȯ�� ���� Ÿ�� �ٲٱ� 
//-------------------------------------------
class cltGameMsgRequest_SummonAttackChange{
public:
	SI16	siCharUnique;
	SI32	siSummonID;
	SI16	siAttackType;

	cltGameMsgRequest_SummonAttackChange(SI16 charunique, SI32 summonid, SI16 attacktype)
	{
		siCharUnique	= charunique;
		siSummonID		= summonid;
		siAttackType	= attacktype; 
	}
};


class cltGameMsgResponse_SummonAttackChange{
public:
	SI16			siCharUnique;
	SI16			siResult;
	SI32			siSummonID;
	SI08			siAttackType;

	cltGameMsgResponse_SummonAttackChange(SI16 charunique, SI16 result, SI32 summonid, SI08 attacktype)
	{
		siCharUnique	= charunique;
		siResult		= result;
		siSummonID		= summonid;
		siAttackType	= attacktype; 
	}
};


//-------------------------------------------
// ��ȯ�� ���ʽ�����Ʈ ���
//-------------------------------------------
class cltGameMsgRequest_SummonUseBonusPoint{
public:
	SI16	siCharUnique;
	SI32	siSummonID;
	SI16	siBonusType;
	bool	bStatusInit;

	cltGameMsgRequest_SummonUseBonusPoint(SI16 charunique, SI32 summonid, SI16 bonustype,bool statusinit)
	{
		siCharUnique	= charunique;
		siSummonID		= summonid;
		siBonusType		= bonustype; 
		bStatusInit		= statusinit;
	}
};


class cltGameMsgResponse_SummonUseBonusPoint{
public:
	SI16			siCharUnique;
	SI16			siResult;
	SI32			siSummonID;

	cltGameMsgResponse_SummonUseBonusPoint(SI16 charunique, SI16 result, SI32 summonid)
	{
		siCharUnique	= charunique;
		siResult		= result;
		siSummonID		= summonid;
	}
};

// [�߰� : Ȳ���� 2008. 2. 19 => ��ȯ�� �ɷ�ġ ����� ������ ���� ��Ŷ.]
class cltGameMsgRequest_SummonUseBonus
{
public:
	SI16	m_siCharUnique;
	SI32	m_siSummonID;

	SI16	m_siStr;
	SI16	m_siAgi;
	SI16	m_siWis;
	SI16	m_siVit;
	SI16	m_siWisdom;
	SI16	m_sihand;
	SI16	m_siDecreaseBonus;

	cltGameMsgRequest_SummonUseBonus(SI16 _siCharunique, SI32 _summonid, SI16 _siStr, SI16 _siAgi, SI16 _siWis, SI16 _siVit, SI16 _siWisdom, SI16 _sihand, SI16 _siDecreaseBonus)
	{
		m_siCharUnique	  = _siCharunique;
		m_siSummonID	  = _summonid;
		m_siStr			  = _siStr;
		m_siAgi			  = _siAgi;
		m_siWis			  = _siWis;
		m_siVit			  = _siVit;
		m_siWisdom		  = _siWisdom;
		m_sihand		  = _sihand;	

		m_siDecreaseBonus = _siDecreaseBonus;
	}
};


class cltGameMsgResponse_SummonUseBonus{
public:
	SI16			siCharUnique;
	SI16			siResult;
	SI32			siSummonID;

	cltGameMsgResponse_SummonUseBonus(SI16 charunique, SI16 result, SI32 summonid)
	{
		siCharUnique	= charunique;
		siResult		= result;
		siSummonID		= summonid;
	}
};


//-------------------------------------------
// ��ȯ�� ��Ȱ ��û 
//-------------------------------------------
#define SUMMON_REVIVE_DOLL		1
#define SUMMON_REVIVE_TICKET	2

class cltGameMsgRequest_SummonRevive{
public:
	SI16	siCharUnique;
	SI32	siSummonID;
	SI16	siReviveType;

	cltGameMsgRequest_SummonRevive(SI16 charunique, SI32 summonid, SI16 type)
	{
		siCharUnique	= charunique;
		siSummonID		= summonid;
		siReviveType	= type;	
	}
};


class cltGameMsgResponse_SummonRevive{
public:
	SI16	siCharUnique;
	SI16	siResult;
	SI32	siSummonID;
	

	cltGameMsgResponse_SummonRevive(SI16 charunique, SI16 result, SI32 summonid)
	{
		siCharUnique	= charunique;
		siResult		= result;
		siSummonID		= summonid;
	}
};


//-------------------------------------------
// ��ȯ���� ��ȭ��Ų��.
//-------------------------------------------

class cltGameMsgRequest_SummonEvolve{
public:
	SI16	siCharUnique;
	SI32	siSummonID;
	SI32	siKind;

	SI16	siMode ; // 0 : ��ȭ , 1 : ��ȭ , 2 : ��ȯ

	cltGameMsgRequest_SummonEvolve(SI16 charunique, SI32 summonid, SI32 kind, SI16 mode=0)
	{
		siCharUnique	= charunique ;
		siSummonID		= summonid ;
		siKind			= kind ;
		siMode			= mode ;
	}
};

class cltGameMsgResponse_SummonEvolve{
public:
	SI16	siCharUnique;
	SI16	siResult;
	SI32	siSummonID;
	SI32	siKind;

	SI16	siMode ;

	cltGameMsgResponse_SummonEvolve(SI16 charunique, SI16 result, SI32 summonid, SI32 kind,SI16 mode)
	{
		siCharUnique = charunique;
		siResult	 = result;
		siSummonID	 = summonid;
		siKind		 = kind;

		siMode		 = mode;
	}
};


//-------------------------------------------
// ��ȯ�� ��ȭ ��û 
//-------------------------------------------
class cltGameMsgRequest_SummonScroll{
public:
	SI16	siCharUnique;
	SI32	siSummonID;
	SI32	siScrollUnique;

	cltGameMsgRequest_SummonScroll(SI16 charunique, SI32 summonid, SI32 scroll)
	{
		siCharUnique	= charunique;
		siSummonID		= summonid;
		siScrollUnique	= scroll;
	}
};


class cltGameMsgResponse_SummonScroll{
public:
	SI16	siCharUnique;
	SI16	siResult;
	SI32	siSummonID;

	cltGameMsgResponse_SummonScroll(SI16 charunique, SI16 result, SI32 summonid)
	{
		siCharUnique	= charunique;
		siResult		= result;
		siSummonID		= summonid;
	}
};

// ��ȯ�� ���� �ʱ�ȭ
class cltGameMsgRequest_Summon_StatusInit{
public:
	SI16	siCharUnique;
	SI32	siSummonID;

	cltGameMsgRequest_Summon_StatusInit(SI16 charunique, SI32 summonid)
	{
		siCharUnique	= charunique;
		siSummonID		= summonid;
	}
};

// ��ȯ�� �ڵ� ȸ�� ����
class cltGameMsgRequest_Summon_SetAutoHeal{
public:
	SI16	siCharUnique;
	SI16	siSelectAutoHeal;			// 30%�� 50%�� 70%��
	bool	bAutoHeal;			// �� ���ΰ� �� ���ΰ�

	cltGameMsgRequest_Summon_SetAutoHeal(SI16 charunique, SI16 selectautoheal, bool autoheal)
	{
		siCharUnique		= charunique;
		siSelectAutoHeal	= selectautoheal;
		bAutoHeal			= autoheal;
	}
};

// ��ȯ�� �ڵ� ȸ�� ����
class cltGameMsgResponse_Summon_SetAutoHeal{
public:
	SI16	siCharUnique;
	SI16	siResult;
	SI16	siSelectAutoHeal;			// 30%�� 50%�� 70%��
	bool	bAutoHeal;			// �� ���ΰ� �� ���ΰ�

	cltGameMsgResponse_Summon_SetAutoHeal(SI16 charunique,SI16 result,SI16 selectautoheal , bool autoheal)
	{
		siCharUnique = charunique ;
		siResult = result;
		siSelectAutoHeal = selectautoheal ;
		bAutoHeal = autoheal ;
	}
};

// �������׼� �� ��ȯ�� ���� ��û
class cltGameMsgRequest_TradeMerchantBuySummonInfo
{
public:
	SI32 siSummonID;

	cltGameMsgRequest_TradeMerchantBuySummonInfo( SI32 summonid )
	{
		siSummonID = summonid;		
	}
};

class cltGameMsgResponse_TradeMerchantBuySummonInfo
{
public:
	SI32 siSummonID;
	GMONEY siSummonPrice;

	cltGameMsgResponse_TradeMerchantBuySummonInfo( SI32 summonid, GMONEY SummonPrice )
	{
		siSummonID		= summonid;
		siSummonPrice	= SummonPrice;
	}
};

// �������׼� ��ȯ���� ���
class cltGameMsgRequest_TradeMerchantBuySummon{
public:
	SI16	siCharUnique;
	SI32	siSummonID;
	SI16	siSummonRank;
	GMONEY	siSummonPrice;


	cltGameMsgRequest_TradeMerchantBuySummon(SI16 charunique, SI32 summonid, SI16 summonrank, GMONEY summonprice)
	{
		siCharUnique	= charunique;
		siSummonID		= summonid;
		siSummonRank	= summonrank;
		siSummonPrice	= summonprice;
	}
};

class cltGameMsgResponse_TradeMerchantBuySummon{
public:

	SI16	siCharUnique;
	SI16	siResult;
	SI32	siSummonID;
	GMONEY	siSummonPrice;
	GMONEY	siLeftMoney;


	cltGameMsgResponse_TradeMerchantBuySummon(SI16 charunique, SI16 result, SI32 summonid , GMONEY summonprice, GMONEY leftmoney)
	{
		siCharUnique	= charunique;
		siResult		= result;
		siSummonID		= summonid;
		siSummonPrice	= summonprice;
		siLeftMoney		= leftmoney;
	}
};

class cltGameMsgRequest_Select_SummonChar
{
public:
	SI16	siSelectIndex;	// -1�� ����char

	cltGameMsgRequest_Select_SummonChar(SI16 index )
	{
		siSelectIndex = index ;
	}
};

class cltGameMsgResponse_Select_SummonChar
{
public:
	SI16	siSelectIndex;	// -1�� ����char

	cltGameMsgResponse_Select_SummonChar(SI16 index )
	{
		siSelectIndex = index ;
	}
};
#define STON_WEAPONE	1
#define STON_ARMOR		2
//���� ������ ��û.
class cltGameMsgRequest_SummonEquipston{
public:
	SI32	siSummonID;		// ��ȯ�� ID
	SI32	siStonType;		// ����� �� Ÿ��
	SI16	siStonNum;		// ����� �� ����

	cltGameMsgRequest_SummonEquipston(SI16 charunique, SI32 summonid, SI32 StonType, SI16 StonNum)
	{
		siSummonID		= summonid;
		siStonType		= StonType;
		siStonNum		= StonNum;
	}
};


class cltGameMsgResponse_SummonEquipston{
public:
	SI16	siResult;
	SI32	siSummonID;
	cltSummon *pclSummon;	// ��ȯ�� ���� ���� �޴´�.

	cltGameMsgResponse_SummonEquipston(SI16 charunique, SI16 result, SI32 summonid ,cltSummon *clSummon )
	{
		siResult		= result;
		siSummonID		= summonid;
		memcpy(pclSummon,clSummon,sizeof(cltSummon));
	}
};

// PCK - ��ȯ�� ���¹̳� ������ ��� (08.07.16)
class cltGameMsgRequest_Summon_ChargeStamina
{
public:
	SI32	siSummonID;

	cltGameMsgRequest_Summon_ChargeStamina(SI32 summonid)
	{
		siSummonID = summonid;
	}
};

class cltGameMsgResponse_Summon_ChargeStamina
{
public:
	SI32	siSummonID;

	cltGameMsgResponse_Summon_ChargeStamina(SI32 summonid)
	{
		siSummonID = summonid;
	}
};

//[����] ��ȯ�� ����
class cltGameMsgRequest_Summon_Transform
{
public:
	SI16	siCharUnique;
	SI32	siSummonID;
	SI16	siStatus;

	cltGameMsgRequest_Summon_Transform()
	{

	}
	cltGameMsgRequest_Summon_Transform(SI16 charunique, SI32 summonid, SI16 statustype)
	{
		siCharUnique	= charunique;
		siSummonID		= summonid;
		siStatus		= statustype;
	}
};

class cltGameMsgResponse_Summon_Transform
{
public:
	SI16	siCharUnique;
	SI32	siSummonID;
	SI16	siStatus;

	cltGameMsgResponse_Summon_Transform(SI16 charunique, SI32 summonid, SI16 statustype)
	{
		siCharUnique	= charunique;
		siSummonID		= summonid;
		siStatus		= statustype;
	}
};


#endif