#pragma once

#include "Client.h"
#include "Resource.h"

#include "../../InterfaceMgr/DialogController.h"
#include "MsgType-System.h"

#define MAX_INPUT	10000	//���� ����â�� �ԷµǴ� �ִ밪

class CNMonsterCreateDlg : public CDialogController
{
public:
	CNMonsterCreateDlg();
	~CNMonsterCreateDlg();

	void Init();
	void Destroy();

	void Create();

	static void CALLBACK StaticCallBackDialogCNMonsterCreateProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK CallBackDialogCNMonsterCreateProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	void GetMonsterInfo(TCHAR* szText);		// ���� ������ ���� ���� ��������

	void AddCombo();

	void SetMonsterInfo();					// ���͸� ����

private:
	InterfaceFactory	m_InterfaceFactory;

	SI16				m_siSelectedIndex;

	SI32				m_siMonsterKind;

	SI32				m_siLevel;
	SI32				m_siMonCreateNum;
	SI32				m_siAggro;
	SI32				m_siMonAC;
	SI32				m_siMinDmg;
	SI32				m_siMaxDmg;
	SI32				m_siMonStr;
	SI32				m_siMonDex;
	SI32				m_siMonVit;
	SI32				m_siMonIntl;
	SI32				m_siMonHnd;
	SI32				m_siMonLuk;
	SI32				m_siMonWis;
	SI32				m_siCriRate;
	SI32				m_siAttInter;
	SI32				m_siFire;
	SI32				m_siWater;
	SI32				m_siLand;
	SI32				m_siWind;
	SI32				m_siNature;
};