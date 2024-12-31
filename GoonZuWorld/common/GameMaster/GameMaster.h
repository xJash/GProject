//---------------------------------
// 2004/5/18 ���°�
//---------------------------------
#ifndef _GAMEMASTER_H
#define _GAMEMASTER_H

#include <Directives.h>
#include "../Item/ItemCommon/ItemUnit.h"
#include "../NLib/NUpdateTimer.h"

#define MAX_GMINFO_NUMBER			200
#define MAX_GM_ORDER_NAME_LENGTH	256
#define MAX_GM_EXPLAIN_LENGTH		128

#define GM_ATB_NONE							0x00000000
#define GM_ATB_CHARUNIQUE					0x00000001		
#define GM_ATB_MONSTER						0x00000002		
#define GM_ATB_ITEM							0x00000004		
#define GM_ATB_SKILL						0x00000010  	
#define GM_ATB_VILLAGE						0x00000020  	
#define GM_ATB_HUNTMAP						0x00000040		
#define GM_ATB_ETC							0x00000080

class cltGameMasterInfo{
public:
	
	SI32 siUnique;
	SI32 siNeedGMLevel;
	TCHAR szOrder[MAX_GM_ORDER_NAME_LENGTH];
	TCHAR* pExplain;
	TCHAR* pSampleUse;

	SI32 mGMatb;

	cltGameMasterInfo(SI32 unique, SI32 gmlevel, TCHAR* porder, TCHAR* pexplain, TCHAR* psampleuse, SI32 aAtb);
	~cltGameMasterInfo();

};

class cltGameMasterManager{

private :
	SI32	m_siGMInfoCount;			// ��� ��� ����

	cltItem	m_clSupplyItem;		// �� �ð����� �������� ����ϴ� ������ ����ũ
	TCHAR	m_szSupplyMsg[256];				// �� �ð����� �������� ������ ����ϸ� �������� �޽���

	//KHY -0702- �������� ��� �����鿡��, ������ �ð��� �������� �����Ѵ�. 
	SI32 time_hour;
	SI32 time_min;
	SI32 itemunique;
	SI32 num;
	UI16 usedate;

	NUpdateTimer kUpdateTimer;
	
public:
	bool timeSwitch;
	///////////////////////////////////////////

#ifdef _SAFE_MEMORY
	NSafeTArray<cltGameMasterInfo*, MAX_GMINFO_NUMBER>		pclGMInfo;
#else
	cltGameMasterInfo* pclGMInfo[MAX_GMINFO_NUMBER];
#endif

	cltGameMasterManager();
	~cltGameMasterManager();

	// ��� ������ �߰��Ѵ�. 
	void Add(SI32 gmlevel, TCHAR* porder, TCHAR* pexplain, TCHAR* psampleuse, SI32 aAtb);

	// ����� �ٰŷ� ����ũ�� ã�´�. 
	SI32 FindUniqueFromOrder(TCHAR* porder);

	// ��� ��ɿ� ���� ���� ������ ���´� (2K�� �ؽ�Ʈ ����� Ȯ���ؼ� �Ѱܾ� �Ѵ�) 
	bool GetText(TCHAR* porder, TCHAR* ptext, SI16 txtSize);

	bool SetSupplyItem(IN const cltItem * pclitem);
	bool GetSupplyItem(OUT cltItem * pclitem);
	void SetSupplyMsg(const TCHAR * msg);
	TCHAR * GetSupplyMsg();

	//KHY -0702- �������� ��� �����鿡��, ������ �ð��� �������� �����Ѵ�. 
	void giveItemTime(UI32 time_hour,UI32 time_min,SI32 itemunique,SI32 num,UI16 usedate );
	void Action( );
	
};
#endif


