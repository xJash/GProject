#ifndef _DBMSGGACHA_H
#define _DBMSGGACHA_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"
#include "../../GoonzuWorld/server/GachaManager/GachaManager.h"


//------------------------------------------
// ���� ����� �������� ������ ���� ��û. 
//------------------------------------------
class sDBRequest_GachaBuy
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;		// ���  Person
	cltItem				clKeyItem;		// ���� ������ (�Ҹ��)
	cltItem				clGetItem;		// ��� ������ (������)
	bool				bPileSwitch;	// ������ ���� ����. 	
	SI16				siKeyItemPos;	// ���� �������� �κ��� ��ġ.
	SI16				siGetItemPos;	// �������� ���� �κ��� ��ġ.
	UI16				uiGachaCnt;
	bool				bBestProduct;
	UI08				uiGachaCntAdd;	// uiGachaCnt�� +�� ����

	sDBRequest_GachaBuy()
	{
		ZeroMemory(this, sizeof(sDBRequest_GachaBuy));
	}

	sDBRequest_GachaBuy(SI32 id, SI32 personid, cltItem* pclkeyitem, cltItem* pclgetitem, bool bpilewitch,  SI16 keyitempos, SI16 getitempos, UI16 gachacnt, bool bestproduct, UI08 gachacntadd)
	{
		packetHeader.usSize	= sizeof( sDBRequest_GachaBuy);
		packetHeader.usCmd	= DBMSG_REQUEST_GACHABUY;
		usCharID			= id;
		siPersonID			= personid;

		clKeyItem.Set( pclkeyitem );
		clGetItem.Set( pclgetitem );

		bPileSwitch			= bpilewitch;	
		siKeyItemPos		= keyitempos;
		siGetItemPos		= getitempos;
		uiGachaCnt			= gachacnt;		
		bBestProduct		= bestproduct;
		uiGachaCntAdd		= gachacntadd;
	}
}; 


class sDBResponse_GachaBuy
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;		
	SI16				siKeyItemPos;		// ���� �������� �κ��� ��ġ.
	SI16				siGetItemPos;		// �������� ���� �κ��� ��ġ.
	cltItem				clKeyItem;
	cltItem				clGetItem;			// ���� ������.
	UI16				uiGachaCnt;			// ������ �����ߴٸ� + 1 �Ǿ� ���ƿ´�
	bool				bBestProduct;

	//[�߰� : Ȳ���� 2007. 10. 24 �α׿� �̿�]
	cltItem				clGachaGetItem;		// ������ �����ϰ� ���� ������.
	cltItem				clUseKeyItem;		// ���� ������ (�Ҹ��)

	UI08				uiGachaCntAdd;		// uiGachaCnt�� +�� ����

	sDBResponse_GachaBuy()
	{
		ZeroMemory(this, sizeof(sDBResponse_GachaBuy));
	}
};

#endif