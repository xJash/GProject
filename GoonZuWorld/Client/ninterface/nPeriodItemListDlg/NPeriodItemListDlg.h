//////////////////////////////////////////////////////////////////////////
//	090326	[����ȣ]	���� �Ⱓ ���õ� BUFF & Service���� ����Ʈ Dlg
//////////////////////////////////////////////////////////////////////////


#pragma once

#include <directives.h>

#include "CommonHeader.h"
#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../ninterface/NBuffStatus/NBuffstatus.h"

#define MAX_ITEMMALL_ITEM_PER_PAGE	5

class CButton;
class CImageStatic;

class CNPeriodItemListDlg : public CDialogController
{
public:
	//	Resource�󿡼� ȿ���� TextIndex �� �ش� Icon�� �����ϱ� ���� �Ⱓ�������� ���̾�α� â������ ���̴� buffEffect ȿ�����ε���
	//	!Warning : �ص� ���� �ε����� ���ҽ������� ���� ���� ���� �ε��� �Դϴ�. ������ �ڵ忡 �ִ� ���� �ε����� ȥ�� ����!
	enum BuffIndex_UseOnlyThis	
	{
		BuffIndex_BUF_PREMIUMEXPUP,
		BuffIndex_BUF_SUPEREXPUP,
		BuffIndex_BUF_SPECIALAMPUL_EXPUP300,
		BuffIndex_BUF_FARMINGNMININGFOREVER,
		BuffIndex_PremiumService_SpaceBox,
		BuffIndex_BUF_STATUE_UP_STR,
		BuffIndex_BUF_STATUE_UP_DEX,
		BuffIndex_BUF_STATUE_UP_MAG,
		BuffIndex_BUF_STATUE_UP_VIT,
		BuffIndex_BUF_STATUE_UP_HAND,
		BuffIndex_BUF_EXP_UP,
		BuffIndex_BUF_PREMIUMMAKEEXPUP,
		BuffIndex_PremiumService,
		BuffIndex_CombatService,
		BuffIndex_MakeItemService,
		BuffIndex_BulletService,
		BuffIndex_SummonStaminaService,
		BuffIndex_MarKetPremiumService,
		BuffIndex_NewMarketPremiumService,
		BuffIndex_BUF_ATTACKUP,
		BuffIndex_BUF_DEFENSEUP,
		BuffIndex_BUF_SPEEDUP,
		BuffIndex_BUF_MAKEEXPUP_20,
		BuffIndex_BUF_MAKEEXPUP_150,
		BuffIndex_BUF_NOFIRSTATTACK,
		BuffIndex_BUF_SUMMONATACUP,
		BuffIndex_BUF_LOVEPOWER,
		BuffIndex_BUF_FRIENDSHIP,
		BuffIndex_BUF_HINAMOCHI,
		BuffIndex_BUF_SUCCESS_MANUFACTURE,
		BuffIndex_BUF_MOFUMOFU_PERFUME,
		BuffIndex_BUF_FOURLEAF,
		BuffIndex_BUF_HAPPYBEAN,
		BuffIndex_BUF_ATTACKUP30DAY,
		BuffIndex_BUF_DEFENSEUP30DAY,
		BuffIndex_BUF_THANKSGIVING_DAY,
		BuffIndex_BUF_WATERMELON,
		BuffIndex_UseNoLimitTicketWarp,
		BuffIndex_BUF_OLYMPICMEDAL_GOLD,
		BuffIndex_BUF_OLYMPICMEDAL_SILVER,
		BuffIndex_BUF_OLYMPICMEDAL_BROLZE,
		BuffIndex_RIDE_ADDSTATUS,
		BuffIndex_BIKE_ADDDEX,
		BuffIndex_HORSE_ADDDEX,
		BuffIndex_BIKE_ADDSTR,
		BuffIndex_HORSE_ADDSTR,
		BuffIndex_BIKE_ADDMAG,
		BuffIndex_HORSE_ADDMAG,
		BuffIndex_BUF_STATUE_UP_WIS,
		BuffIndex_BUF_CHRISTMASEVENT_SNOWBLESS,
		BuffIndex_BUF_CHRISTMASEVENT_DECORATION,
		BuffIndex_BUF_RESIDENTS_EXPUP_10,
		BuffIndex_BUF_RESIDENTS_STRONG,
		BuffIndex_BUF_VALENTINE,

		BuffIndex_End,
	};


	enum PeriodTabNumber			//	090324[��ȣ]	Tabâ�� enum�� 
	{
		PERIOD_TAB_CHARACTER,
		PERIOD_TAB_BUFF,
		PERIOD_TAB_HORSE,
		PERIOD_TAB_END,
	};

	struct sPeriodItem											//	090320[��ȣ]	�Ⱓ�� ������ ����ü
	{
		SI32					siRefIndex;						
		string					strPeriodItemInfo;	
		SI32					siPeriodTime;						//	���� �Ⱓ������ ���� �ϱ� ���� data
	};

	static bool CompareForPeriodItem(const sPeriodItem& elem1, const sPeriodItem& elem2 )
	{
		if(elem1.siPeriodTime < elem2.siPeriodTime)
			return true;
		else
			return false;
	}

	InterfaceFactory			m_InterfaceFactory;

	SI32 						m_siCurrentPage;
	SI32 						m_siMaxPage;	
	SI32						m_siCurrentTabIndex;							//	090324[��ȣ]	tab�ε���
	
	SI32 						m_siImageType[MAX_ITEMMALL_ITEM_PER_PAGE];
	SI32 						m_siImageIndex[MAX_ITEMMALL_ITEM_PER_PAGE];

	CButton*					m_pButton_PeriodItem[PERIOD_TAB_END];			//	090324[��ȣ]	tab��ư

	TSpr						m_BuffImg;										//	090331[��ȣ]	���� �̹��� SPR

	vector<sPeriodItem>			m_vecPeriodItem[PERIOD_TAB_END];				//	090324[��ȣ]	�Ⱓ�� ������ ����Ʈ
	
	struct stTabTextInfo
	{
		CControllerObj	*st_pControllerObj;
		COLORREF	st_Color;
		SI16		st_siWeight;

		stTabTextInfo()
		{
			Init();
		}

		void Init()
		{
			memset( this, 0, sizeof( stTabTextInfo ));
		}

		void Set( CControllerObj* in_pControllerObj, COLORREF in_Color, SI16 in_siWeight )
		{
			st_pControllerObj = in_pControllerObj;
			st_Color = in_Color;
			st_siWeight = in_siWeight;
		}
	};

public:

	CNPeriodItemListDlg();
	~CNPeriodItemListDlg();

	void	Initialize();
	void	Destroy();

	void	Create();

	static	void CALLBACK StaticNPeriodItemListDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void	CALLBACK NPeriodItemListDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void	Action();	
	void	DrawDialogLast(SI32 ScreenRX, SI32 ScreenRY );

	void	SelectedTabBtn();		//	090323[��ȣ]	�� ��Ʈ�� ���¸� ����
	void	SetTabTextInfo(stTabTextInfo* in_SelectedText);

	void	SetPeriodItemList();	//	090323[��ȣ]	�Ⱓ������ ����Ʈ�� set
	void	ShowPeriodItemList();	//	090323[��ȣ]	�Ⱓ������ ����Ʈ�� Show

	
	cltDate		SetPeriodItemTime(bool bIsBuff, SI32 siTimeVary);
	void		SetPeriodItemInfo(cltDate pcldate, TCHAR* pchDataInfo, SI32 siTextFromMgr, SI32 siBuffPercent = 0);
	void		InputData(SI32 DataIndex, SI32 siKindOfList, TCHAR* pchDataInfo, SI32 siTime);
	
};
