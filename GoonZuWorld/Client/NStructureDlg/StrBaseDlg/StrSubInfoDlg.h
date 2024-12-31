#ifndef _STRSUBINFODLG_H
#define _STRSUBINFODLG_H

#include "StrSubBaseDlg.h"

// �ǹ� �⺻ ���� �� ���̾�α� 
class NStrSubInfoDlg : public NStrSubTabDlg
{
public:
	enum {
		EDITBOX_BENEFIT,
		EDITBOX_CAPITAL,
		EDITBOX_CHIEF,
		EDITBOX_EXP,
		EDITBOX_LEVEL,
//		LISTBOX_GUILDLIST,
		BUTTON_REFRESH,
	};
	NStrSubInfoDlg();
	virtual ~NStrSubInfoDlg();

	void InitDlg();

	void Action();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );

/*	// ���� ��� ������ ��û�Ѵ�.
	BOOL SendRequestGuildUnitInfo();

	void ShowGuildUnitListInfo();			// ���� ��� ������ List ����
	void ShowGuildUnitInfo();				// ���� ��� ����*/

public:
	BOOL					m_bShowTaxInfo;
	SI32					m_siVillageUnique;
//	SI32					m_siUnitSlot;	// ���� ��� ���� ��ȣ
//	cltGuildRankManager*	m_pGuildRank;
};


#endif