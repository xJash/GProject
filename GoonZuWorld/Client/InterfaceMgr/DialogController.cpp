#include "DialogController.h"

#include "ControllerBaseDefinition.h"
#include "ControllerResource.h"

#include "InterfaceMgr.h"
#include "Interface/Button.h"
#include "DLGPositionSave/DLGPositionSave.h"
#include <Client.h>
extern cltCommonLogic *pclClient;



	
CDialogController::CDialogController() : CControllerMgr()
{
//	m_pMinimizeButton = NULL;ww
	m_pCloseButton = NULL;
	m_bSavePosToFile = FALSE;
}

CDialogController::~CDialogController()
{
	SavePosToFile();

	if ( m_pCloseButton )
	{
		delete m_pCloseButton;
		m_pCloseButton = NULL;
	}
//	SAFE_DELETE(m_pMinimizeButton);
}

void CDialogController::SavePosToFile()
{
	if ( m_bSavePosToFile )
	{
		g_DlgPositionSave.SetPosition( this->GetDialogControllerID(), this->GetX(), this->GetY() );
	}
}


void CDialogController::Create( SI16 DialogControllerID, SI16 ControllerKind, CControllerMgr *pParent, GUICallBackEvent pCallBack, TCHAR *Title, TCHAR *FileName, SI16 FontIndex, bool BKTileImg, SI16 BKTileNum, SI16 XPos, SI16 YPos, SI16 Width, SI16 Height, bool Movable, bool HaveCaption, bool HaveCloseButton, bool SavePosToFile) //,bool HaveMinimizeButton)
{
	cltClient *pclclient = (cltClient*)pclClient;

	//SavePosToFile = true;

	m_bSavePosToFile = SavePosToFile;
	
	if(g_SoundOnOffDlg.m_bChatFixed == false)
		SavePosToFile = false;


	if(SavePosToFile == true) // [����] ���� ���Ͽ��� �о�;� �Ҷ�
	{
		SavePosToFile = g_DlgPositionSave.GetSaveState(DialogControllerID); // ���� ����Ǿ� �ֳ� üũ
		
		if(SavePosToFile == true) // �о�� ��ġ�� ��ȿ���� üũ
		{
			SI16 xPos = g_DlgPositionSave.GetPositionX(DialogControllerID);
 			SI16 yPos = g_DlgPositionSave.GetPositionY(DialogControllerID);
			SavePosToFile = pclclient->m_pInterfaceMgr->IsAvailableMove(xPos,yPos,Width,Height);
		}
	}
	

	if(SavePosToFile == false) // ��������.. ���� ���ڰ����� ��ġ�� ����!
	{
		CControllerMgr::Create( DialogControllerID, ControllerKind, pParent, pCallBack, Title, FileName, FontIndex, BKTileImg, BKTileNum, XPos, YPos, Width, Height, Movable, HaveCaption, HaveCloseButton); //,HaveMinimizeButton );
	}
	else // ���Ͽ��� ��ġ�� �о�� ����
	{
		SI16 xPos = g_DlgPositionSave.GetPositionX(DialogControllerID);
		SI16 yPos = g_DlgPositionSave.GetPositionY(DialogControllerID);
		CControllerMgr::Create( DialogControllerID, ControllerKind, pParent, pCallBack, Title, FileName, FontIndex, BKTileImg, BKTileNum, xPos, yPos, Width, Height, Movable, HaveCaption, HaveCloseButton); //,HaveMinimizeButton );
	}

	if ( HaveCloseButton )
	{	
		m_pCloseButton = new CButton( this );
		m_pCloseButton->Create( COMMON_DIALOG_CLOSEBUTTON, NULL, COMMON_DIALOG_CLOSEBUTTON_FILENAME, COMMON_DIALOG_CLOSEBUTTON_FONTINDEX, false, 0, Width - COMMON_CLOSE_BUTTON_OFFSETX, COMMON_CLOSE_BUTTON_OFFSETY, COMMON_CLOSE_BUTTON_WIDTH, COMMON_CLOSE_BUTTON_HEIGHT, COMMON_CLOSE_BUTTON_WIDTH, COMMON_CLOSE_BUTTON_HEIGHT );
	}
	/*
	if( HaveMinimizeButton )
	{
		m_pMinimizeButton = new CButton( this );
		m_pMinimizeButton->Create( COMMON_DIALOG_MINIMIZEBUTTON, COMMON_DIALOG_MINIMIZEBUTTON_FILENAME, COMMON_DIALOG_MINIMIZEBUTTON_FONTINDEX, false, 0, Width - COMMON_MINIMIZE_BUTTON_OFFSETX , COMMON_MINIMIZE_BUTTON_OFFSETY, COMMON_MINIMIZE_BUTTON_WIDTH,COMMON_MINIMIZE_BUTTON_HEIGHT,COMMON_MINIMIZE_BUTTON_WIDTH,COMMON_MINIMIZE_BUTTON_HEIGHT  );
		
	}*/
	if ( ControllerKind == CONTROLLER_KIND_POPUPDIALOG )
	{
		pclclient->m_pInterfaceMgr->Add( this );
	}

	return;
}
 


void CDialogController::ReSizeDialog( SI16 XPos, SI16 YPos, SI16 Width, SI16 Height )
{
	SetDialogPos(XPos,YPos,Width,Height);
	
	TCHAR szTemp[MAX_PATH] = {'\0',	};

	StringCchCopy(szTemp,MAX_PATH,GetTitle());

	SetTitle(" ");

	SetTitle(szTemp); // Ÿ��Ʋ �̹��� ���۸� ���� ����� ���̾�α� ����� �°� ����
	
	m_pCloseButton->MoveControl(GetWidth()-COMMON_CLOSE_BUTTON_OFFSETX,COMMON_CLOSE_BUTTON_OFFSETY);
}

//***************************************************************************************************
// Function Name	: GetButton
//
// Last Modified 	: 2005 / 12 / 26
// Created			: �豤��
//
// Function			: CButton �������̽��� ã�Ƽ� �����Ѵ�.
//
// Inputs			: ã�� CButton�� �̸�
// Outputs			: 
// Returns			: 
//***************************************************************************************************
CButton* InterfaceFactory::GetButton( SI32 TypeID )
{
	IterMapInterface iter = m_mapInterfaceFactory_.find( TypeID );

	if( iter == m_mapInterfaceFactory_.end() )
	{
#ifdef _DEBUG
		char tempBuffer[256] = {'\0'};

		sprintf( tempBuffer, "%d ���� ������ �������̽��� �����ϴ�!!", TypeID );
		MessageBox(NULL, tempBuffer, "TypeID Error(Button)", MB_OK|MB_TOPMOST);
#endif
		return NULL;
	}

	return ((CButton*)iter->second);
}

//***************************************************************************************************
// Function Name	: GetStatic
//
// Last Modified 	: 2005 / 12 / 26
// Created			: �豤��
//
// Function			: CStatic �������̽��� ã�Ƽ� �����Ѵ�.
//
// Inputs			: ã�� CStatic�� �̸�
// Outputs			: 
// Returns			: 
//***************************************************************************************************
CStatic* InterfaceFactory::GetStatic( SI32 TypeID )
{
	IterMapInterface iter = m_mapInterfaceFactory_.find( TypeID );

	if( iter == m_mapInterfaceFactory_.end() )
	{
#ifdef _DEBUG
		char tempBuffer[256] = {'\0'};

		sprintf( tempBuffer, "%d ���� ������ �������̽��� �����ϴ�!!", TypeID );
		MessageBox(NULL, tempBuffer, "TypeID Error(Static)", MB_OK|MB_TOPMOST);
#endif
		return NULL;
	}

	return ((CStatic*)iter->second);
}

//***************************************************************************************************
// Function Name	: GetComboBox
//
// Last Modified 	: 2005 / 12 / 26
// Created			: �豤��
//
// Function			: CComboBox �������̽��� ã�Ƽ� �����Ѵ�.
//
// Inputs			: ã�� CComboBox�� �̸�
// Outputs			: 
// Returns			: 
//***************************************************************************************************
CComboBox* InterfaceFactory::GetComboBox( SI32 TypeID )
{
	IterMapInterface iter = m_mapInterfaceFactory_.find( TypeID );

	if( iter == m_mapInterfaceFactory_.end() )
	{
#ifdef _DEBUG
		char tempBuffer[256] = {'\0'};

		sprintf( tempBuffer, "%d ���� ������ �������̽��� �����ϴ�!!", TypeID );
		MessageBox(NULL, tempBuffer, "TypeID Error(ComboBox)", MB_OK|MB_TOPMOST);
#endif
		return NULL;
	}

	return ((CComboBox*)iter->second);
}

//***************************************************************************************************
// Function Name	: GetImageStatic
//
// Last Modified 	: 2005 / 12 / 26
// Created			: �豤��
//
// Function			: CImageStatic �������̽��� ã�Ƽ� �����Ѵ�.
//
// Inputs			: ã�� CImageStatic�� �̸�
// Outputs			: 
// Returns			: 
//***************************************************************************************************
CImageStatic* InterfaceFactory::GetImageStatic( SI32 TypeID )
{
	IterMapInterface iter = m_mapInterfaceFactory_.find( TypeID );

	if( iter == m_mapInterfaceFactory_.end() )
	{
#ifdef _DEBUG
		char tempBuffer[256] = {'\0'};

		sprintf( tempBuffer, "%d ���� ������ �������̽��� �����ϴ�!!", TypeID );
		MessageBox(NULL, tempBuffer, "TypeID Error(ImageStatic)", MB_OK|MB_TOPMOST);
#endif
		return NULL;
	}

	return ((CImageStatic*)iter->second);
}

//***************************************************************************************************
// Function Name	: GetTree
//
// Last Modified 	: 2005 / 12 / 26
// Created			: �豤��
//
// Function			: CTree �������̽��� ã�Ƽ� �����Ѵ�.
//
// Inputs			: ã�� CTree�� �̸�
// Outputs			: 
// Returns			: 
//***************************************************************************************************
CTree* InterfaceFactory::GetTree( SI32 TypeID )
{
	IterMapInterface iter = m_mapInterfaceFactory_.find( TypeID );

	if( iter == m_mapInterfaceFactory_.end() )
	{
#ifdef _DEBUG
		char tempBuffer[256] = {'\0'};

		sprintf( tempBuffer, "%d ���� ������ �������̽��� �����ϴ�!!", TypeID );
		MessageBox(NULL, tempBuffer , "TypeID Error(Tree)", MB_OK|MB_TOPMOST);
#endif
		return NULL;
	}

	return ((CTree*)iter->second);
}

//***************************************************************************************************
// Function Name	: GetOutLine
//
// Last Modified 	: 2005 / 12 / 26
// Created			: �豤��
//
// Function			: COutLine �������̽��� ã�Ƽ� �����Ѵ�.
//
// Inputs			: ã�� COutLine�� �̸�
// Outputs			: 
// Returns			: 
//***************************************************************************************************
COutLine* InterfaceFactory::GetOutLine( SI32 TypeID )
{
	IterMapInterface iter = m_mapInterfaceFactory_.find( TypeID );

	if( iter == m_mapInterfaceFactory_.end() )
	{
#ifdef _DEBUG
		char tempBuffer[256] = {'\0'};

		sprintf( tempBuffer, "%d ���� ������ �������̽��� �����ϴ�!!", TypeID );
		MessageBox(NULL, tempBuffer, "TypeID Error(OutLine)", MB_OK|MB_TOPMOST);
#endif
		return NULL;
	}

	return ((COutLine*)iter->second);
}

//***************************************************************************************************
// Function Name	: GetControl
//
// Last Modified 	: 2008 / 2 / 28
// Created			: Ȳ����
//
// Function			: Control �������̽��� ã�Ƽ� �����Ѵ�.
//
// Inputs			: ã�� Control�� �̸�
// Outputs			: ��� Control ������
// Returns			: 
//***************************************************************************************************
void* InterfaceFactory::GetControl( SI32 TypeID )
{
	IterMapInterface iter = m_mapInterfaceFactory_.find( TypeID );

	if( iter == m_mapInterfaceFactory_.end() )
	{
#ifdef _DEBUG
		char tempBuffer[256] = {'\0'};

		sprintf( tempBuffer, "%d ���� ������ �������̽��� �����ϴ�!!", TypeID );
		MessageBox(NULL, tempBuffer , "TypeID Error(ListView)", MB_OK|MB_TOPMOST);
#endif
		return NULL;
	}

	return ((void*)iter->second);
}


//***************************************************************************************************
// Function Name	: GetListView
//
// Last Modified 	: 2005 / 12 / 26
// Created			: �豤��
//
// Function			: CListView �������̽��� ã�Ƽ� �����Ѵ�.
//
// Inputs			: ã�� CListView�� �̸�
// Outputs			: 
// Returns			: 
//***************************************************************************************************
CListView* InterfaceFactory::GetListView( SI32 TypeID )
{
	IterMapInterface iter = m_mapInterfaceFactory_.find( TypeID );

	if( iter == m_mapInterfaceFactory_.end() )
	{
#ifdef _DEBUG
		char tempBuffer[256] = {'\0'};

		sprintf( tempBuffer, "%d ���� ������ �������̽��� �����ϴ�!!", TypeID );
		MessageBox(NULL, tempBuffer , "TypeID Error(ListView)", MB_OK|MB_TOPMOST);
#endif
		return NULL;
	}

	return ((CListView*)iter->second);
}

//***************************************************************************************************
// Function Name	: GetRadioButton
//
// Last Modified 	: 2005 / 12 / 26
// Created			: �豤��
//
// Function			: CRadioButton �������̽��� ã�Ƽ� �����Ѵ�.
//
// Inputs			: ã�� CRadioButton�� �̸�
// Outputs			: 
// Returns			: 
//***************************************************************************************************
CRadioButton* InterfaceFactory::GetRadioButton( SI32 TypeID )
{
	IterMapInterface iter = m_mapInterfaceFactory_.find( TypeID );

	if( iter == m_mapInterfaceFactory_.end() )
	{
#ifdef _DEBUG
		char tempBuffer[256] = {'\0'};

		sprintf( tempBuffer, "%d ���� ������ �������̽��� �����ϴ�!!", TypeID );
		MessageBox(NULL, tempBuffer, "TypeID Error(RadioButton)", MB_OK|MB_TOPMOST);
#endif
		return NULL;
	}

	return ((CRadioButton*)iter->second);
}

//***************************************************************************************************
// Function Name	: GetList
//
// Last Modified 	: 2005 / 12 / 26
// Created			: �豤��
//
// Function			: CList �������̽��� ã�Ƽ� �����Ѵ�.
//
// Inputs			: ã�� CList�� �̸�
// Outputs			: 
// Returns			: 
//***************************************************************************************************
CList* InterfaceFactory::GetList( SI32 TypeID )
{
	IterMapInterface iter = m_mapInterfaceFactory_.find( TypeID );

	if( iter == m_mapInterfaceFactory_.end() )
	{
#ifdef _DEBUG
		char tempBuffer[256] = {'\0'};

		sprintf( tempBuffer, "%d ���� ������ �������̽��� �����ϴ�!!", TypeID );
		MessageBox(NULL, tempBuffer, "TypeID Error(List)", MB_OK|MB_TOPMOST);
#endif
		return NULL;
	}

	return ((CList*)iter->second);
}

//***************************************************************************************************
// Function Name	: GetChatEdit
//
// Last Modified 	: 2005 / 12 / 26
// Created			: �豤��
//
// Function			: ChatEdit �������̽��� ã�Ƽ� �����Ѵ�.
//
// Inputs			: ã�� ChatEdit�� �̸�
// Outputs			: 
// Returns			: 
//***************************************************************************************************
CChatEdit* InterfaceFactory::GetChatEdit( SI32 TypeID )
{
	IterMapInterface iter = m_mapInterfaceFactory_.find( TypeID );

	if( iter == m_mapInterfaceFactory_.end() )
	{
#ifdef _DEBUG
		char tempBuffer[256] = {'\0'};

		sprintf( tempBuffer, "%d ���� ������ �������̽��� �����ϴ�!!", TypeID );
		MessageBox(NULL, tempBuffer, "TypeID Error(ChatEdit)", MB_OK|MB_TOPMOST);
#endif
		return NULL;
	}

	return ((CChatEdit*)iter->second);
}

//***************************************************************************************************
// Function Name	: GetCheckBox
//
// Last Modified 	: 2005 / 12 / 26
// Created			: �豤��
//
// Function			: CCheckBox �������̽��� ã�Ƽ� �����Ѵ�.
//
// Inputs			: ã�� CCheckBox�� �̸�
// Outputs			: 
// Returns			: 
//***************************************************************************************************
CCheckBox* InterfaceFactory::GetCheckBox( SI32 TypeID )
{
	IterMapInterface iter = m_mapInterfaceFactory_.find( TypeID );

	if( iter == m_mapInterfaceFactory_.end() )
	{
#ifdef _DEBUG
		char tempBuffer[256] = {'\0'};

		sprintf( tempBuffer, "%d ���� ������ �������̽��� �����ϴ�!!", TypeID );
		MessageBox(NULL, tempBuffer, "TypeID Error(CheckBox)", MB_OK|MB_TOPMOST);
#endif
		return NULL;
	}

	return ((CCheckBox*)iter->second);
}

//***************************************************************************************************
// Function Name	: GetEdit
//
// Last Modified 	: 2005 / 12 / 26
// Created			: �豤��
//
// Function			: CEdit �������̽��� ã�Ƽ� �����Ѵ�.
//
// Inputs			: ã�� CEdit�� �̸�
// Outputs			: 
// Returns			: 
//***************************************************************************************************
CEdit* InterfaceFactory::GetEdit( SI32 TypeID )
{
	IterMapInterface iter = m_mapInterfaceFactory_.find( TypeID );

	if( iter == m_mapInterfaceFactory_.end() )
	{
#ifdef _DEBUG
		char tempBuffer[256] = {'\0'};

		sprintf( tempBuffer, "%d ���� ������ �������̽��� �����ϴ�!!", TypeID );
		MessageBox(NULL, tempBuffer, "TypeID Error(Edit)", MB_OK|MB_TOPMOST);
#endif
		return NULL;
	}

	return ((CEdit*)iter->second);
}
