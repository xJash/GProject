//---------------------------------
// 2004/2/5 ���°�
//---------------------------------

#ifndef _VILLAGEDETAILINFO_H
#define _VILLAGEDETAILINFO_H

#include <Windows.h>
#include <Directives.h>

#define VILLAGEDETAILINFOTYPE_VILLAGELIST		1		// ������� 
#define VILLAGEDETAILINFOTYPE_VILLAGELEVEL		2		// �������� ��ȸ 
#define VILLAGEDETAILINFOTYPE_VISITORNUM		3		// �����湮�ڼ� ��ȸ
#define VILLAGEDETAILINFOTYPE_VILLAGEMONEY		4		// ������ ���� �ڱ�. 
#define VILLAGEDETAILINFOTYPE_VILLAGEPROFIT		5		// ������ ���� �ڱ�(���ͱ�) 
#define VILLAGEDETAILINFOTYPE_VILLAGESTOCK		6		// ���� �� �ֽļ�.
#define VILLAGEDETAILINFOTYPE_GENERALMEETING	7		// ������ȸ���ึ�� 
#define VILLAGEDETAILINFOTYPE_WAR				8		// ���� ��� ǥ��. 
#define VILLAGEDETAILINFOTYPE_WARPERRESIDENT	9		// ���� ��� ǥ��. (�ֹ� 100���)
#define VILLAGEDETAILINFOTYPE_PEOPLE			10		// �ֹμ�  ǥ��. 
#define VILLAGEDETAILINFOTYPE_USER				11		// ���� ����ڼ� 
#define VILLAGEDETAILINFOTYPE_PREVYEARDBID		12		// ���⵵ ����. 
#define VILLAGEDETAILINFOTYPE_HUNT				13		// ������
#define VILLAGEDETAILINFOTYPE_DECLAREWAR		14		// ������ ���� ����. 
#define VILLAGEDETAILINFOTYPE_HORSEMARKET		15		// �纹�� 
#define VILLAGEDETAILINFOTYPE_STOCK				16		// ���� 
#define VILLAGEDETAILINFOTYPE_REALESTATEMARKET	17		// �Ű�
#define VILLAGEDETAILINFOTYPE_SUMMONMARKET		18		// �忹��
#define VILLAGEDETAILINFOTYPE_SUMMONHEROMARKET	19		// �񺯻�
#define VILLAGEDETAILINFOTYPE_PORT				20		// ����
#define VILLAGEDETAILINFOTYPE_SHIPMARKET		21		// ���Ի�
#define VILLAGEDETAILINFOTYPE_FARM				22		// ����
#define VILLAGEDETAILINFOTYPE_FEAST				23		// ���ڽ�
#define VILLAGEDETAILINFOTYPE_MINE				24		// ����
#define VILLAGEDETAILINFOTYPE_GUILD				25		// ���(���)
#define VILLAGEDETAILINFOTYPE_CITYHALLSTATE		26		// ��û��������( �����, �Ļ��, ������, �ʱ�ȭ�� ��..)



class cltGameMsgResponse_VillageDetailInfo;

class cltVillageDetailData{
public:
	SI32	siType;
	char	szTypeText[64];
	char	szExplainText[256];
};

class cltVillageDetailInfoManager{
public:
	HWND m_hDlg;					// ������ ����. 

	RECT DlgRect;
	bool bDlgRectInitSwitch;
	bool bCheckSortVillage;			// ���� ���� üũ ��ư�� ���� 01/18 �߰�

	SI32 siCurrentType;
	SI32 siOldCurrentType;
	SI32 siOldViliage;
	
	HBRUSH	m_hEditBrush;
	HBITMAP m_hWarpBitmap;


	cltVillageDetailInfoManager();
	~cltVillageDetailInfoManager();
	

	BOOL CreateDlg(HINSTANCE hinst, HWND hwnd);
	static BOOL CALLBACK StaticDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

	// �޺��� ������ Ÿ���� �ִ´�. 
	void SetDataTypeInCombo(HWND hDlg, SI32 dlgitem);

	// Ÿ���� �ٰŷ� ���� �����͸� ���Ѵ�. 
	cltVillageDetailData* GetVillageDetailData(SI32 type);

	// �ؽ�Ʈ�� �ٰŷ� ���� �� ���� �ڵ带 ���Ѵ�. 
	SI32 GetVillageDetailType(char* ptext);

	// ������ ���� ���� ������ ǥ���Ѵ�. 
	void ShowInfo(cltGameMsgResponse_VillageDetailInfo* pclinfo);
	
	// �ǹ� �� ������ ǥ���Ѵ�. 
	void ShowStrInfo(char*  ptext);


	// ������������ �����Ѵ�. 
	SI32 Sort(SI32 sisortdata[], SI32* pvillageunique);
	SI32 Sort(char* pSortname[], SI32* pvillageunique);
	
};

#endif
