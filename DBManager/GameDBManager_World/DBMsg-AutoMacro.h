#ifndef _DBMSG_AUTOMACRO_H_
#define _DBMSG_AUTOMACRO_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\GoonZuWorld\Common\Item\ItemCommon\cltItem.h"
#include "..\..\GoonZuWorld\Common\Char\CharCommon\Char-EconomyInfo.h"
#include "..\..\GoonZuWorld\Common\Skill\Skill.h"
#include "..\..\GoonZuWorld\Server\Rank\Rank.h"
#include "..\..\GoonZuWorld\CommonLogic\StructureClass\StructureClass.h"
#include "..\..\GoonZuWorld\Common\Letter\Letter.h"
#include "..\..\GoonZuWorld\Common\Char\CharCommon\Char-Common.h"
#include "DBMsg.h"

#include "NDate.h"

#define IP_STRING_SIZE	16

//[�߰� : Ȳ���� 2007. 12. 7 �������α׷� DB ���� �޽��� S -> DB]
class sDBRequest_AutoMacro
{
public:
	sPacketHeader		packetHeader;
	SI32				usCharID;								
	SI32				usCommandtype;							// ��� ����.
	SI32				siPersonID;								// person id
	TCHAR				szAutoProcessName[MAX_PLAYER_NAME];		// ������� ���α׷� �̸�
	TCHAR				szIP[IP_STRING_SIZE];					// ������.
	
	sDBRequest_AutoMacro(SI32 _Charid, SI32 _CommandType, SI32 _siPersonID, const TCHAR* _pname, const TCHAR* _IP)
	{
		packetHeader.usSize = sizeof( sDBRequest_AutoMacro );
		packetHeader.usCmd	= DBMSG_REQUEST_AUTOMACRO;
		
		usCharID	  = _Charid;
		usCommandtype = _CommandType;
		siPersonID	  = _siPersonID;
        
		MStrCpy(szAutoProcessName, _pname,  MAX_PLAYER_NAME);
		MStrCpy(szIP			 , _IP,		IP_STRING_SIZE);
	}
};

//[�߰� : Ȳ���� 2007. 12. 7 �������α׷� DB ���� �޽��� DB -> S]
class sDBResponse_AutoMacro
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	
	UI08				usCommandtype;							// ��� ����.
	UI08				uiAutoMacroCnt;							// �������α׷� ��� Ƚ��. 1:ù���, 2�̻�: 7�ϰ�. 
	SI32				siPersonID;								// ������� PersonID
		
	sDBResponse_AutoMacro()
	{
		ZeroMemory(this, sizeof(sDBResponse_AutoMacro));
	}
};


#endif