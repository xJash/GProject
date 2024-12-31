#ifndef _FEAST_H
#define _FEAST_H

#include <Directives.h>

#include "..\..\Common\CommonHeader.h"
#include "..\StructureClass\StructureClass.h"
#include "..\..\Server\Time\MyTime.h"

#include "..\..\Common\Item\ItemCommon\ItemUnit.h"

#define MAX_FEAST_TAB_NUMBER								7

class cltTaxPaymentListDlg;

//--------------------------------------
// �� �������� �����ϴ� ���ڽ� ��ü 
//--------------------------------------
class cltFeast : public cltStructureBasic{
public:
	cltFeast(SI32 sivillageunique);
	~cltFeast();
};

#define MAX_PARTYHALL_MAP									5		//[����] ��ƼȦ. ���� ������ ���� ����. => 2008. 3. 10
#define MAX_PARTYHALL_RESERVATION_INFO_LIST					24		//[����] ��ƼȦ. �ʴ� �ִ� ���� ������ ����. => 2008. 3. 10
#define	PARTYHALL_START_MAP_INDEX							335		//[����] ��ƼȦ. ��Ƽ�� ���� ���� �ε�����ȣ. 
//--------------------------------------
// ���ڽ� ������. 
//--------------------------------------
class cltFeastManager : public cltStructureMngBasic{
public:
	enum {

		MAX_FEAST_EFFECT_NUM = 11, // ���� ����
	};



	cltFeastManager( cltCharManager* pclcm, SI32 gamemode, SI32 ranktype, TCHAR *strFileName );
	~cltFeastManager();

	// ���� ȯ�� �λ縻ǥ�� . 
	void GreetingMsg(HWND hDlg);
	void Do_WM_INITDIALOG(SI32 charunique);

	// ���ڽ��� �ż��Ѵ�.
	SI32 CreateFeast(SI32 siunique);

	void Action();

	void PartyhallEnd();										// [����] ��ƼȦ. ��Ƽ�� ����Ǹ� ����Ʈ���� ��������.
 	
	SI32 GetReveIndex( SI32 _PartyHallIndex, SI32 _PersonID );	// �ش� ��Ƽ�忡 ����� ��ġ�� ��´�.
	void GiveReward(void);										// ��Ƽ�忡 ��Ĺ��� ������ ���� �������� ���ݸ� ����.
	void GiveItem(void);										// ������ �����ֱ�.
	bool IsPartyHallMap( SI32 MapIndex );

public:
	BOOL						IsMyInventoryChanged();
	BOOL						IsStgChanged();
	
	HIMAGELIST					m_hImageList;

	cltItem						*m_pclMyItem;				// �� �κ��丮 üũ
	cltFeastStg					*m_pclStgItem;
	
	HWND						m_hUserInventory;
	HWND						m_hFeastStg;
	
	SI32						m_siInventorySelectedIndex;
	SI32						m_siStgSelectedIndex;
/*
	void						ShowFeastInfo( HWND hDlg );
	void						ShowPresentInfo( HWND hDlg );
	void						ShowEffectInfo( HWND hDlg );	// ����Ʈ ����Ʈ�� ����Ʈ �߰�

	void						SetDateCombo( HWND hDlg );

	void						ShowPresentList( HWND hDlg );
*/
	SI32						siChiefPresentSelectIndex;
	SI32						siUserPresentSelectIndex;

	SI16						siChiefEffectSelectIndex;	// ��ȸ �� ������ ����Ʈ ��ȣ

	BOOL						bUpdateUser;
	BOOL						bUpdateChief2;

#ifdef _SAFE_MEMORY
	NSafeTArray<PartyHall_Decoration, MAX_PARTYHALL_DECORATION_ITEM>		clDecoration;

	NSafeTArray< NSafeTArray<cltPatyHallResvInfo, MAX_PARTYHALL_RESERVATION_INFO_LIST>, MAX_PARTYHALL_MAP>		clPartyHallResvInfo;

	NSafeTArray<SI32, MAX_PARTYHALL_MAP>	m_siGatePositionID;
	NSafeTArray<POINT, MAX_PARTYHALL_MAP>	m_DecorationPos;
	NSafeTArray<POINT, MAX_PARTYHALL_MAP>	m_PartyHallUserPos;
#else
	PartyHall_Decoration		clDecoration[MAX_PARTYHALL_DECORATION_ITEM];	// ��Ĺ�.

	//[����] ��ƼȦ. ��������. => 2008. 3. 13
	cltPatyHallResvInfo			clPartyHallResvInfo[MAX_PARTYHALL_MAP][MAX_PARTYHALL_RESERVATION_INFO_LIST];

	//[����] ��ƼȦ. ��Ĺ��� ���̵� ����. ���ſ� �ֺ� ĳ������ ������ �� �� ����. => 2008-4-6
	SI32						m_siGatePositionID[MAX_PARTYHALL_MAP];
	POINT						m_DecorationPos[MAX_PARTYHALL_MAP];			// ��Ĺ� ���� ��ġ.
	POINT						m_PartyHallUserPos[MAX_PARTYHALL_MAP];		// ���� ���� ��ġ.
#endif
};

#endif