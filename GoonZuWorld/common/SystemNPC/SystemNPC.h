
#ifndef _SYSTEMNPC_H
#define _SYSTEMNPC_H

#include <Directives.h>

#define MAX_SYSTEM_NPC_NUMBER		90

//-------------------------------------
// �ý��� NPC �޽���. 
//-------------------------------------

#define SYSTEMNPC_SUCCESS_BUY								1	// NPC���� ���� ����. 
#define SYSTEMNPC_FAIL_BUY_REASPON_MONEY_INSUFFICIENTY		2	// �� �������� ���� ����
#define	SYSTEMNPC_SUCCESS_SELL								3	// NPC���� �Ǹ� ����
#define SYSTEMNPC_FAIL_SELL_BULLETITEM						4	// NPC���� źȯ�� ������ �Ǹ��Ҽ� ����
#define SYSTEMNPC_FAIL_SELL_ITEMMALLITEM					5	// NPC���� �����۸� ������ �Ǹ��Ҽ� ����
#define SYSTEMNPC_FAIL_SELL_QUESTITEM						6	// NPC���� �����۸� ������ �Ǹ��Ҽ� ����
#define SYSTEMNPC_SUCCESS_BUY_ARROW							7	// NPC���� ȭ�� ���� ����.
#define SYSTEMNPC_SUCCESS_BUY_BULLET						8	// NPC���� �Ѿ� ���� ����.
#define SYSTEMNPC_SUCCESS_BUY_FOOD							9	// NPC���� ���� ���� ����.
#define SYSTEMNPC_SUCCESS_BUY_HEAL							10	// NPC���� �� ���� ����.
#define SYSTEMNPC_FAIL_BUY_SOLDOUT							11	// �԰� ��ǰ�� ��� �ǸŵǾ� ����
/*
class cltSystemNPC{
public:
	SI32 siKind;
	SI32 siQuestType;
	TCHAR szExplain[512];

	cltSystemNPC()
	{
		siKind		= 0;
		siQuestType	= 0;
		szExplain[ 0 ] = NULL;
	}

	void Set(cltSystemNPC* pclinfo)
	{
		Set(pclinfo->siKind, pclinfo->siQuestType, pclinfo->szExplain);
	}

	void Set(SI32 kind, SI32 questtype, TCHAR* explain)
	{
		siKind		= kind;
		siQuestType	= questtype;

		StringCchCopy(szExplain, 512, explain);
	}
};

class cltSystemNPCManager{
public:
	cltSystemNPC clSystemNPC[MAX_SYSTEM_NPC_NUMBER];

	cltSystemNPCManager();
	~cltSystemNPCManager();

	bool Add(SI32 kind, SI32 questtype, TCHAR* explain);
	bool FindSystemNPCInfo(SI32 unique, cltSystemNPC* pclinfo);
	bool FindSystemNPCInfoFromQuestType(SI32 questtype, cltSystemNPC* pclinfo);
};
*/

class cltSystemNPC
{
public:
	SI32 m_siKind;
	SI16 m_siQuestType;
	SI32 m_siExplainNum;		// NPC Infoâ�� ������ NPC����
	SI16 m_siCategory;			// �� ����Ʈ�� �з�
	SI32 m_siSimpleExplainNum;	// �� ����Ʈ�� ���� ����
	SI32 m_siLocationNum;		// NPC��ġ Text Number
	SI16 m_siShowNotice;		// ����Ʈ �˸�â�� ǥ�õ��� ����(0=ǥ�þȵ� 0<�˻�����)
	SI32 m_siNoticeExplainNum;	// ����Ʈ �˸�â ����
	SI32 m_siNoticeLocationNum;	// ����Ʈ �˸�â ���� ����
	SI16 m_siMapIndex;			// NPC�� �ִ� ��ġ
	SI16 m_siImageDisplayMode;	// ����Ʈ �ο� �̹��� ����

public:
	cltSystemNPC();
	cltSystemNPC( cltSystemNPC* pclSystemNPC );
	~cltSystemNPC();

	void Init( void );
	void Set( cltSystemNPC* pclSystemNPC );
	void Set( SI32 siKind, SI16 siQuestType, SI32 siExplainNum, SI32 siLocationNum, SI16 siCategory, SI32 siSimpleExplainNum, SI16 siShowNotice, SI32 siNoticeExplainNum, SI32 siNoticeLocationNum, SI16 siMapIndex, SI16 siImageDisplayMode );

	bool GetExplainText( TCHAR* pszBuffer, SI32 siBufferSize );

};

enum QUEST_CATEGORY
{
	CATEGORY_NONE			= 0
	,CATEGORY_BEGINNER
	,CATEGORY_MANUFACTURE
	,CATEGORY_WORLD

	//---------------------------
	// �� ���� �߰��� �ּ���
	//---------------------------
	,CATEGORY_MAX
};

enum QUESTDISPLAY_MARK
{
	QUESTDISPLAY_MODE_NONE = 0
	,QUESTDISPLAY_MODE_ALL			// ������ ǥ����
	,QUESTDISPLAY_MODE_CONDITION	// ������ ��ġ�ϸ� ǥ����
	,QUESTDISPLAY_MODE_GOING		// �����߿��� ǥ����

	,QUESTDISPLAY_MODE_MAX
};

class cltSystemNPCManager
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltSystemNPC, MAX_SYSTEM_NPC_NUMBER>		clSystemNPC;
#else
	cltSystemNPC clSystemNPC[ MAX_SYSTEM_NPC_NUMBER ];
#endif

public:
	cltSystemNPCManager();
	~cltSystemNPCManager();
	
	void Init( void );

	bool LoadSystemNPCInfo( void );
	bool Add( cltSystemNPC* pclSystemNPC );

	SI16 ConvertCategoryTextToNum( TCHAR* pszCategory );

	bool GetSystemNPCListFormCategory( IN SI16 siCategory, OUT cltSystemNPC* pclSystemNPCList, IN SI32 siListCount );
	bool GetSystemNPCListForShowNotice( OUT cltSystemNPC* pclSystemNPCList, IN SI32 siListCount );

	bool FindSystemNPCInfoFromNPCKind( IN SI32 siKind, OUT cltSystemNPC* pclSystemNPC );
	bool FindSystemNPCInfoFromQuestType( IN SI32 siQuestType, OUT cltSystemNPC* pclSystemNPC );
};

#endif
