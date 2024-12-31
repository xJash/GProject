#ifndef _NPVPMAP_H_
#define _NPVPMAP_H_

#include "../Client/InterfaceMgr/DialogController.h"

#include <Directives.h>
#include <stdio.h>

#include "../../Resource.h"

#include "../Common/Map/MapManager/MapManager.h"
#include <Graphic.h>
#include <Graphic_Capsule.h>
#include "TSpr.h"
//#define LEAST_COMMON_MULTILPLE	30
//
class CImageStatic;
class CButton;
class CComboBox;
class CListView;
class CEdit;
class CStatic;
class CList;
//const SI32 MAX_MAP_NPCNUMBER = 25;

#define MAX_PVP_MAPINDEXNUM	100	// ����Ʈ�� �ִ�� ���� ���ε���
class CNPVPMapDlg : public CDialogController
{
public:

	CNPVPMapDlg();
	~CNPVPMapDlg();

	void Create();

	static void CALLBACK StaticCallBackDialogCNPVPMapDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogCNPVPMapDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Action();
	void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY )	;	// ������ ������( ������ �����ش� )
	void SetList()	;	// �ʸ���Ʈ ����
	void LoadMapData()	;	// �������� �о� �´�.
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )	;
	InterfaceFactory m_InterfaceFactory;

private:
	

	TSpr	m_SprMap;	// ������ �� �׸�.
	
	SI32	m_siSprMode;				// 0 : ����Ʈ 1: ��
	SI32	m_siSelectGateIndex;		// ���õ� ����Ʈ 
	SI32	m_siSelectMapIndex;		// ���õ� ��
	SI32	m_siSelectMonsterIndex;
	SI32	m_siMapIndex;


	SI32	m_ListData_MapIndex[MAX_PVP_MAPINDEXNUM]	;	// ����Ʈ ������ ���ε���
};

#endif _NPVPMAP_H_
