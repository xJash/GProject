//---------------------------------
// 2003/5/17 ���°�
//---------------------------------
/* ==========================================================================
	Ŭ���� :		cltNHorseTypeChange

	�ۼ��� :		05/03/14
	�ۼ��� :		���뷡
	
	������� :		����

	�����۾� :		

   ========================================================================*/
//#if defined(__LEON_NCHARSTATUS__) && defined(_DEBUG)

#pragma once

#include <directives.h>

#include "CommonHeader.h"
#include "../../InterfaceMgr/DialogController.h"

#define MAX_CHARSTATUS_PAGE_NUMBER	5

#define WANTIED_ANIMAL_CHANGE_TYPE	2

class cltCharClient;
class cltParametaBox;
class cltSummonScroll;
class cltCharManager;
class cltItem;

class CButton;
class CCheckBox;
class CComboBox;
class CEdit;
class CImageStatic;
class CList;
class CRadioButton;
class CStatic;

// ǰ�� ���� â
class cltNHorseTypeChange : public CDialogController
{
public:
	BOOL m_DlgRectInitSwitch;
	RECT m_DlgRect;

	SI32 m_siSelectedUnique;
	SI32 m_siOriUnique;
	SI32 m_siMaxUnique;

	CButton 			*m_pButton_left;
	CImageStatic 		*m_pImagestatic_portrait;
	CButton 			*m_pButton_right;
	CStatic				*m_pStatictext_name;
	CButton 			*m_pButton_change;
	CButton 			*m_pButton_cancel;

	cltNHorseTypeChange();
	~cltNHorseTypeChange();

	void Create();
	void SetOriUnique( SI32 in_siOriUnique );
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	static void CALLBACK NHorseTypeChangeStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NHorseTypeChangeProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void SetHorsePortrait();
	void Close();

};

//#endif
