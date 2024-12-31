// [����] ���Žý��� ����

#pragma once

#include "../../InterfaceMgr/DialogController.h"

class CEdit;
class CButton;
class CStatic;
class COutLine;


class CNElectionStumpDlg : public CDialogController
{
	enum NELECTIONSTUMP_BUTTON
	{
		NELECTIONSTUMP_BUTTON_STUMP_START,	// ��������
		NELECTIONSTUMP_BUTTON_STUMP_END,	// ��������
		NELECTIONSTUMP_BUTTON_MINIMUM,		// â �ּ�ȭ
		NELECTIONSTUMP_BUTTON_MAXIMUM,		// â �ִ�ȭ

		//-------------------------------
		//	�� ���� �߰��� �ּ���
		//-------------------------------
		NELECTIONSTUMP_BUTTON_MAX
	};

	enum NELECTIONSTUMP_EDIT
	{
		NELECTIONSTUMP_EDIT_CANDIDATE,		// �ĺ��ڸ�
		NELECTIONSTUMP_EDIT_MAINTENANCE,	// ��������

		//-------------------------------
		//	�� ���� �߰��� �ּ���
		//-------------------------------
		NELECTIONSTUMP_EDIT_MAX
	};

	enum NELECTIONSTUMP_STATIC
	{
		NELECTIONSTUMP_STATIC_CANDIDATE,	// �ĺ��ڸ�
		NELECTIONSTUMP_STATIC_MAINTENANCE,	// ��������

		//-------------------------------
		//	�� ���� �߰��� �ּ���
		//-------------------------------
		NELECTIONSTUMP_STATIC_MAX
	};

	enum NELECTIONSTUMP_OUTLINE
	{
		NELECTIONSTUMP_OUTLINE_CANDIDATE,	// �ĺ��ڸ�
		NELECTIONSTUMP_OUTLINE_MAINTENANCE,	// ��������

		//-------------------------------
		//	�� ���� �߰��� �ּ���
		//-------------------------------
		NELECTIONSTUMP_OUTLINE_MAX
	};

	enum NELECTIONSTUMP_VARIABLE
	{
		NELECTIONSTUMP_DIALOG_MODE_MINIMUM		= 0		// ���̾�α� ��� �ּ�ȭ
		,NELECTIONSTUMP_DIALOG_MODE_MAXIMUM		= 1		// ���̾�α� ��� �ִ�ȭ

		,NELECTIONSTUMP_DIALOG_MININUM_WIDTH	= 120	// �ּ�ȭ �Ǿ��� �ִ�ȭ ��ư ��ġ X
		,NELECTIONSTUMP_DIALOG_MININUM_HEIGHT	= 19	// �ּ�ȭ �Ǿ��� �ִ�ȭ ��ư ��ġ X
	};


public:

	CNElectionStumpDlg();
	~CNElectionStumpDlg();

	void Init();
	void Destroy();

	void Create();
	void Action();

	static void CALLBACK StaticElectionStumpDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NElectionStumpDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

private:
	void StartElectionStump();
	void EndElectionStump();
	void PreLoadInformation();
	void SetDialogMode( bool bDialogMode );

private:
	CEdit*		m_pEdit[NELECTIONSTUMP_EDIT_MAX];
	CButton*	m_pButton[NELECTIONSTUMP_BUTTON_MAX];
	CStatic*	m_pStatic[NELECTIONSTUMP_STATIC_MAX];
	COutLine*	m_pOutLine[NELECTIONSTUMP_OUTLINE_MAX];

	SI16		m_siDialogWidth;
	SI16		m_siDialogHeight;

	bool		m_bDialogMode;		// ���� ������ ���

};
