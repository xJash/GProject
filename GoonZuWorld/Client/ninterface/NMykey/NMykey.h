/* ==========================================================================
Ŭ���� :		 

�ۼ��� :		 
�ۼ��� :		 

������� :		 

�����۾� :		
========================================================================*/
 
#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"

#define MYKEY_NUM		 5	// ���� ��� ������   Ű ����.
#define CHECKBOX_NUM	26	// ���� ��� ������ â�� ����.

class CControlMapping
{
public:
	CControlMapping()  { ZeroMemory(this, sizeof(*this) ); }
	CControlMapping(SI32 _siDialogIndex, SI32 _siTextNum)  
	{ 
		m_siDialogIndex  = _siDialogIndex;
		m_siTextNum		 = _siTextNum;
	}
	~CControlMapping() { }
	
	SI32 GetDialogIndex(void)  {	return m_siDialogIndex;		}
	SI32 GetTextNum(void)	   {	return m_siTextNum;			}
	
	void Set( SI32 _siDialogIndex, SI32 _siTextNum )
	{
		m_siDialogIndex  = _siDialogIndex;
		m_siTextNum		 = _siTextNum;
	}

private:
	SI32 m_siDialogIndex;	// ���̾�α� ��ȣ.			
	SI32 m_siTextNum;	    // �ؽ�Ʈ ��ȣ.
};

class CNMykeyDlg : public CDialogController
{
public:

	CNMykeyDlg();
	~CNMykeyDlg();

	void Init();

	void Create();
	void Destroy();

	static void CALLBACK StaticNMykeyDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NMykeyDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );
	
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

public:
	void SetDialogKind(SI32* _psiDialogKind);	
	void KeyAction( SI32 _KeyKind );

	void SaveFile();
	void LoadFile();
	void CheckControlMapping();
	SI32 FindTextNum( SI32 _DialogIndex );
	SI32 FindCotrolIndex( SI32 _DialogIndex );					
	void SetKey( void );										// üũ�ڽ��� üũ�� Ű�� m_siDialogKind�� ����.
	void SetKey( SI32 _DialogIndex );
	void LoadKey( void );										// m_siDialogKind�� ���õ� Ű�� üũ�ڽ� ����.
	bool IsDestroyWindow( SI32 _DialogIndex );					// Ű�� �߰��� â�� �����ǰ� �����Ǵ� â�ΰ�.
	bool IsFullSetkey( int _nControlID );									// ���� �����Ѱ�. ���� ����.
	void HomePage( void );

private:
	InterfaceFactory	m_InterfaceFactory;

	SI32				m_siDialogKind[MYKEY_NUM];				// ���̾�α� ����(��ȣ)�� ����.

	CControlMapping		m_clControlMapping[CHECKBOX_NUM];		// üũ�ڽ� ��Ʈ�Ѱ� ���̾�α� ����.

	bool				m_bCreateComplete;						// �����Ϸ�.
};
 