/*====================================

Ŭ���� : CNHappyBeanDlg
�ۼ��� : 07 .08 . 22
�ۼ���: �ռ���
�������:
�����۾�:
=====================================*/
#include "NChristmasEventDlg.h"
#include "../Client/NStructureDlg/StrBaseDlg/StrBaseDlg.h"
#include "../CommonLogic/StructureClass/StructureClass.h"
#include "../../CommonLogic/MsgType-Structure.h"

#include "../Client/UnderMouseObject/UnderMouseObject.h"

NChristmasEventDlg::NChristmasEventDlg()

{
	ZeroMemory(matitemunique,		sizeof(matitemunique));		//�ʿ��� ��� ����������ũ
	ZeroMemory(matitemnum,			sizeof(matitemnum));		//�ʿ��� �������� ����
	ZeroMemory(matitemEndunique,	sizeof(matitemEndunique));	//������ �ִ� �������� ����ũ
	ZeroMemory(matitemEndnum,		sizeof(matitemEndnum));		//������ �ִ� �������� ����

	Initialize();
}

NChristmasEventDlg::~NChristmasEventDlg()
{
	Destroy();
}

void NChristmasEventDlg::init()
{

}


void NChristmasEventDlg::Destroy()
{

}
void NChristmasEventDlg::Create()
{
	if ( IsCreate() )	return;
	
	CInterfaceFile file;
	cltClient *pclclient = (cltClient *)pclClient;
	SI32 id =pclclient->pclUnderMouseObject->GetUnderMouseID();//���콺 �Ʒ� �ִ� �� ī�ε尪�� ���� �´�.
	
	//[����] ������ ���� Ŭ�� �� â. => 2008-6-9
	if (   pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUEBASE"))
		|| pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUE"))) 
	{
		file.LoadFile(TEXT("NInterface/Data/NChristnasEventDlg/NChristnasEventDlg_PineTree.ddf"));
		file.CreatePopupDialog( this, NCHRISTMASEVENT_DLG,TEXT("dialog_christmasevent"), StaticSelectChristmasEventProc);
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_EXPLAIN , this )
							,NCHRISTMASEVENT_EDIT_EXPLAIN
							,"editbox_explain");//����Ʈ ����â

		TCHAR buffer[128] = "";
		for(SI32 Count = 0; Count < MATERIAL_ITEM_MAX_NUM; ++Count)
		{
			_stprintf(buffer, TEXT("listview_item%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM1+Count , this )
								,NCHRISTMASEVENT_LISTVIEW_ITEM1+Count
								,buffer);

			_stprintf(buffer, TEXT("editbox_itemname%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME1+Count , this ) 
								,NCHRISTMASEVENT_EDIT_ITEMNAME1+Count
								,buffer);

			_stprintf(buffer, TEXT("editbox_itemmaxnum%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX1+Count , this )
								,NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count
								,buffer);

			_stprintf(buffer, TEXT("editbox_itemnum%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count , this )
								,NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count
								,buffer);
		}

		file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL , this ), 
							NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL,   "button_donationmaterial");	//����ϱ� ��ư ����
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NCHRISTMASEVENT_BUTTON_MAKETREE , this ), 
							NCHRISTMASEVENT_BUTTON_MAKETREE,   "button_maketree");

		
		//������ ���� �ϼ� ����â
		TCHAR* pTextEditChristmas;
		pTextEditChristmas = GetTxtFromMgr(8458);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_EXPLAIN)->SetText(pTextEditChristmas);

		TCHAR* pmaketree = GetTxtFromMgr(8459);
		m_InterfaceFactory.GetButton(NCHRISTMASEVENT_BUTTON_MAKETREE)->SetText(pmaketree);
		m_InterfaceFactory.GetButton(NCHRISTMASEVENT_BUTTON_MAKETREE)->Enable(false);		//�⺻������ ������ ���� ��ư�� ��Ȱ��ȭ ��Ų��.
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//[����] �ҷ��� ȣ�� �д� Ŭ���� â
	if (   pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_HALLOWEENBASE"))
		|| pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_HALLOWEEN"))) 
	{
		file.LoadFile(TEXT("NInterface/Data/NChristnasEventDlg/NChristnasEventDlg_PineTree.ddf"));
		file.CreatePopupDialog( this, NCHRISTMASEVENT_DLG,TEXT("dialog_christmasevent"), StaticSelectChristmasEventProc);
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_EXPLAIN , this )
			,NCHRISTMASEVENT_EDIT_EXPLAIN
			,"editbox_explain");//����Ʈ ����â

		TCHAR buffer[128] = "";
		for(SI32 Count = 0; Count < MATERIAL_ITEM_MAX_NUM; ++Count)
		{
			_stprintf(buffer, TEXT("listview_item%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM1+Count , this )
				,NCHRISTMASEVENT_LISTVIEW_ITEM1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemname%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME1+Count , this ) 
				,NCHRISTMASEVENT_EDIT_ITEMNAME1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemmaxnum%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX1+Count , this )
				,NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemnum%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count , this )
				,NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count
				,buffer);
		}

		file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL , this ), 
			NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL,   "button_donationmaterial");	//����ϱ� ��ư ����
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NCHRISTMASEVENT_BUTTON_MAKETREE , this ), 
			NCHRISTMASEVENT_BUTTON_MAKETREE,   "button_maketree");


		//�ҷ��� �̺�Ʈ �� ����â.
		TCHAR* pTextEditChristmas;
		pTextEditChristmas = GetTxtFromMgr(8887);// �ؽ�Ʈ �־�� �Ѵ�.
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_EXPLAIN)->SetText(pTextEditChristmas);

		TCHAR* pmaketree = GetTxtFromMgr(8720);// �ؽ�Ʈ �־�� �Ѵ�.
		m_InterfaceFactory.GetButton(NCHRISTMASEVENT_BUTTON_MAKETREE)->SetText(pmaketree);
		m_InterfaceFactory.GetButton(NCHRISTMASEVENT_BUTTON_MAKETREE)->Enable(false);		//�⺻������ �ҷ��� �д� ���׷��̵� ������ ��Ȱ��ȭ
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	if (pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_PINE_TREE")))
	{
		file.LoadFile(TEXT("NInterface/Data/NChristnasEventDlg/NChristnasEventDlg_PineTree.ddf"));
		file.CreatePopupDialog( this, NCHRISTMASEVENT_DLG,TEXT("dialog_christmasevent"), StaticSelectChristmasEventProc);
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_EXPLAIN , this ), 
			NCHRISTMASEVENT_EDIT_EXPLAIN,   "editbox_explain");//����Ʈ ����â

		TCHAR buffer[128] = "";

		for(SI32 Count = 1; Count < MATERIAL_ITEM_MAX_NUM; ++Count)
		{
			_stprintf(buffer, TEXT("listview_item%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM1+Count , this )
				,NCHRISTMASEVENT_LISTVIEW_ITEM1+Count
				,buffer);
		}
		for(SI32 Count = 0; Count < MATERIAL_ITEM_MAX_NUM; ++Count)
		{
			_stprintf(buffer, TEXT("listview_item%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM1+Count , this )
				,NCHRISTMASEVENT_LISTVIEW_ITEM1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemname%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME1+Count , this ) 
				,NCHRISTMASEVENT_EDIT_ITEMNAME1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemmaxnum%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX1+Count , this )
				,NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemnum%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count , this )
				,NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count
				,buffer);
		}
		////-----------------------------------------------------------------------------------------------------------------
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM2 , this ), 
		//	NCHRISTMASEVENT_LISTVIEW_ITEM2,   "listview_item2");//������ �̹��� 2
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM3 , this ), 
		//	NCHRISTMASEVENT_LISTVIEW_ITEM3,   "listview_item3");//������ �̹��� 3
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM4 , this ), 
		//	NCHRISTMASEVENT_LISTVIEW_ITEM4,   "listview_item4");//������ �̹��� 4
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM5 , this ), 
		//	NCHRISTMASEVENT_LISTVIEW_ITEM5,   "listview_item5");//������ �̹��� 5
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM6 , this ), 
		//	NCHRISTMASEVENT_LISTVIEW_ITEM6,   "listview_item6");//������ �̹��� 6
		////-----------------------------------------------------------------------------------------------------------------
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME1 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMNAME1,   "editbox_itemname1");//�������̸�1
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME2 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMNAME2,   "editbox_itemname2");//�������̸�2
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME3 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMNAME3,   "editbox_itemname3");//�������̸�3
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME4 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMNAME4,   "editbox_itemname4");//�������̸�4
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME5 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMNAME5,   "editbox_itemname5");//�������̸�5
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME6 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMNAME6,   "editbox_itemname6");//�������̸�6
		////-----------------------------------------------------------------------------------------------------------------
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX1 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMAX1,   "editbox_itemmaxnum1");//�����۴�������1
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX2 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMAX2,   "editbox_itemmaxnum2");//�����۴�������2
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX3 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMAX3,   "editbox_itemmaxnum3");//�����۴�������3
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX4 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMAX4,   "editbox_itemmaxnum4");//�����۴�������4
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX5 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMAX5,   "editbox_itemmaxnum5");//�����۴�������5
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX6 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMAX6,   "editbox_itemmaxnum6");//�����۴�������6
		////-----------------------------------------------------------------------------------------------------------------
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM1 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMNUM1,   "editbox_itemnum1");//�����۱�ΰ���1
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM2 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMNUM2,   "editbox_itemnum2");//�����۱�ΰ���2
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM3 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMNUM3,   "editbox_itemnum3");//�����۱�ΰ���3
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM4 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMNUM3,   "editbox_itemnum4");//�����۱�ΰ���4
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM5 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMNUM5,   "editbox_itemnum5");//�����۱�ΰ���5
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM6 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMNUM6,   "editbox_itemnum6");//�����۱�ΰ���6
		////-----------------------------------------------------------------------------------------------------------------
	
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL , this ), 
			NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL,   "button_donationmaterial");//����ϱ� ��ư ����
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NCHRISTMASEVENT_BUTTON_MAKETREE , this ), 
			NCHRISTMASEVENT_BUTTON_MAKETREE,   "button_maketree");//Ʈ�� ����� ��ư����
		
		TCHAR* pmaketree = GetTxtFromMgr(7651);
		m_InterfaceFactory.GetButton(NCHRISTMASEVENT_BUTTON_MAKETREE)->SetText(pmaketree);
		//ũ�������� ����â
		TCHAR* pTextEditChristmas;
		pTextEditChristmas = GetTxtFromMgr(7655);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_EXPLAIN)->SetText(pTextEditChristmas);
		
		m_InterfaceFactory.GetButton(NCHRISTMASEVENT_BUTTON_MAKETREE)->Enable(false);//�⺻������ ����ũ Ʈ�� ��ư�� ��Ȱ��ȭ ��Ų��.
	}

	//KHY - 1113 - ũ�������� �̺�Ʈ - KIND_PINE_TREE , KIND_CHRISTMASTREEBASE = �ٲ�� ����
	if(pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREEBASE")) ) 
	{
		file.LoadFile(TEXT("NInterface/Data/NChristnasEventDlg/NChristnasEventDlg_PineTree.ddf"));
		file.CreatePopupDialog( this, NCHRISTMASEVENT_DLG,TEXT("dialog_christmasevent"), StaticSelectChristmasEventProc);
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_EXPLAIN , this ), 
			NCHRISTMASEVENT_EDIT_EXPLAIN,   "editbox_explain");//����Ʈ ����â

		TCHAR buffer[128] = "";
/*
		for(SI32 Count = 0; Count < MATERIAL_ITEM_MAX_NUM; ++Count)
		{
			_stprintf(buffer, TEXT("listview_item%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM1+Count , this )
				,NCHRISTMASEVENT_LISTVIEW_ITEM1+Count
				,buffer);
		}
*/
		for(SI32 Count = 0; Count < MATERIAL_ITEM_MAX_NUM; ++Count)
		{
			_stprintf(buffer, TEXT("listview_item%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM1+Count , this )
				,NCHRISTMASEVENT_LISTVIEW_ITEM1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemname%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME1+Count , this ) 
				,NCHRISTMASEVENT_EDIT_ITEMNAME1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemmaxnum%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX1+Count , this )
				,NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemnum%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count , this )
				,NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count
				,buffer);
		}

		file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL , this ), 
			NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL,   "button_donationmaterial");//����ϱ� ��ư ����
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NCHRISTMASEVENT_BUTTON_MAKETREE , this ), 
			NCHRISTMASEVENT_BUTTON_MAKETREE,   "button_maketree");//Ʈ�� ����� ��ư����
		
		TCHAR* pmaketree = GetTxtFromMgr(6654);
		m_InterfaceFactory.GetButton(NCHRISTMASEVENT_BUTTON_MAKETREE)->SetText(pmaketree);
		//ũ�������� ����â
		TCHAR* pTextEditChristmas;
		pTextEditChristmas = GetTxtFromMgr(7655);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_EXPLAIN)->SetText(pTextEditChristmas);
		
		m_InterfaceFactory.GetButton(NCHRISTMASEVENT_BUTTON_MAKETREE)->Enable(false);//�⺻������ ����ũ Ʈ�� ��ư�� ��Ȱ��ȭ ��Ų��.
	}
	
	// ��� - �ų��̺�ƮŬ������ ���
	if (   pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREEBASE"))) 
	{
		file.LoadFile(TEXT("NInterface/Data/NChristnasEventDlg/NChristnasEventDlg_PineTree.ddf"));
		file.CreatePopupDialog( this, NCHRISTMASEVENT_DLG,TEXT("dialog_christmasevent"), StaticSelectChristmasEventProc);
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_EXPLAIN , this )
			,NCHRISTMASEVENT_EDIT_EXPLAIN
			,"editbox_explain");//����Ʈ ����â

		TCHAR buffer[128] = "";
		for(SI32 Count = 0; Count < MATERIAL_ITEM_MAX_NUM; ++Count)
		{
			_stprintf(buffer, TEXT("listview_item%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM1+Count , this )
				,NCHRISTMASEVENT_LISTVIEW_ITEM1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemname%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME1+Count , this ) 
				,NCHRISTMASEVENT_EDIT_ITEMNAME1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemmaxnum%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX1+Count , this )
				,NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemnum%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count , this )
				,NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count
				,buffer);
		}

		file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL , this ), 
			NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL,   "button_donationmaterial");	//����ϱ� ��ư ����
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NCHRISTMASEVENT_BUTTON_MAKETREE , this ), 
			NCHRISTMASEVENT_BUTTON_MAKETREE,   "button_maketree");


		//�ų��̺�Ʈ ����â
		TCHAR* pTextEditChristmas;
		pTextEditChristmas = GetTxtFromMgr(9739);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_EXPLAIN)->SetText(pTextEditChristmas);

		TCHAR* pmaketree = GetTxtFromMgr(9673);
		m_InterfaceFactory.GetButton(NCHRISTMASEVENT_BUTTON_MAKETREE)->SetText(pmaketree);
		m_InterfaceFactory.GetButton(NCHRISTMASEVENT_BUTTON_MAKETREE)->Enable(false);		//�⺻������ ������ ���� ��ư�� ��Ȱ��ȭ ��Ų��.
	}

	if (pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE"))) 
	{
		//ũ�������� Ʈ���ϰ��
		file.LoadFile(TEXT("NInterface/Data/NChristnasEventDlg/NChristnasEventDlg_CHristmasTree.ddf"));
		file.CreatePopupDialog( this, NCHRISTMASEVENT_DLG,TEXT("dialog_christmasevent"), StaticSelectChristmasEventProc);
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_EXPLAIN , this ), 
			NCHRISTMASEVENT_EDIT_EXPLAIN,   "editbox_explain");//����Ʈ ����â

		TCHAR buffer[128] = "";
		for(SI32 Count = 0; Count < MATERIAL_ITEM_MAX_NUM; ++Count)
		{
			_stprintf(buffer, TEXT("listview_item%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM1+Count , this )
				,NCHRISTMASEVENT_LISTVIEW_ITEM1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemname%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME1+Count , this ) 
				,NCHRISTMASEVENT_EDIT_ITEMNAME1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemmaxnum%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX1+Count , this )
				,NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemnum%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count , this )
				,NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count
				,buffer);
		}
		//--------------------------------------------------------------------------------------------------------------
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM1 , this ), 
		//	NCHRISTMASEVENT_LISTVIEW_ITEM1,   "listview_item1");//������ �̹��� 1
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM2 , this ), 
		//	NCHRISTMASEVENT_LISTVIEW_ITEM2,   "listview_item2");//������ �̹��� 2
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM3 , this ), 
		//	NCHRISTMASEVENT_LISTVIEW_ITEM3,   "listview_item3");//������ �̹��� 3
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM4 , this ), 
		//	NCHRISTMASEVENT_LISTVIEW_ITEM4,   "listview_item4");//������ �̹��� 4
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM5 , this ), 
		//	NCHRISTMASEVENT_LISTVIEW_ITEM5,   "listview_item5");//������ �̹��� 5
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM6 , this ), 
		//	NCHRISTMASEVENT_LISTVIEW_ITEM6,   "listview_item6");//������ �̹��� 6

		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME1 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMNAME1,   "editbox_itemname1");//�������̸�1
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME2 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMNAME2,   "editbox_itemname2");//�������̸�2
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME3 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMNAME3,   "editbox_itemname3");//�������̸�3
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME4 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMNAME4,   "editbox_itemname4");//�������̸�4
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME5 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMNAME5,   "editbox_itemname5");//�������̸�5
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME6 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMNAME6,   "editbox_itemname6");//�������̸�6

		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX1 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMAX1,   "editbox_itemmaxnum1");//�����۴�������1
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX2 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMAX2,   "editbox_itemmaxnum2");//�����۴�������2
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX3 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMAX3,   "editbox_itemmaxnum3");//�����۴�������3
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX4 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMAX4,   "editbox_itemmaxnum4");//�����۴�������4
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX5 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMAX5,   "editbox_itemmaxnum5");//�����۴�������5
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX6 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMAX6,   "editbox_itemmaxnum6");//�����۴�������6

		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM1 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMNUM1,   "editbox_itemnum1");//�����۱�ΰ���1
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM2 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMNUM2,   "editbox_itemnum2");//�����۱�ΰ���2
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM3 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMNUM3,   "editbox_itemnum3");//�����۱�ΰ���3
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM4 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMNUM3,   "editbox_itemnum4");//�����۱�ΰ���4
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM5 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMNUM5,   "editbox_itemnum5");//�����۱�ΰ���5
		//file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM6 , this ), 
		//	NCHRISTMASEVENT_EDIT_ITEMMNUM6,   "editbox_itemnum6");//�����۱�ΰ���6
		//--------------------------------------------------------------------------------------------------------
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL , this ), 
			NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL,   "button_donationmaterial");//����ϱ� ��ư ����
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON,NCHRISTMASEVENT_BUTTON_HAVEITEM , this ), 
			NCHRISTMASEVENT_BUTTON_HAVEITEM,	"button_haveItem");//�����ޱ⸦ �����Ѵ�.
		//�����ޱ�
		TCHAR* phaveitem = GetTxtFromMgr(7663);
		m_InterfaceFactory.GetButton(NCHRISTMASEVENT_BUTTON_HAVEITEM)->SetText(phaveitem);
		TCHAR* pTextEditChristmas;
		pTextEditChristmas = GetTxtFromMgr(7661);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_EXPLAIN)->SetText(pTextEditChristmas);

		m_InterfaceFactory.GetButton(NCHRISTMASEVENT_BUTTON_HAVEITEM)->Enable(false);//�⺻�����δ� ��Ȱ��ȭ.
		
	}

	// [���] ũ�������� �̺�Ʈ - ���縮�� �տ� �ִ� ũ���� ���� Ʈ���� Ŭ�������� (09.10.21)
	if (pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASWORLDTREE01"))
		|| pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASWORLDTREE02"))) 
	{
		//ũ�������� Ʈ���ϰ��
		file.LoadFile(TEXT("NInterface/Data/NChristnasEventDlg/NChristnasEventDlg_CHristmasTree.ddf"));
		file.CreatePopupDialog( this, NCHRISTMASEVENT_DLG,TEXT("dialog_christmasevent"), StaticSelectChristmasEventProc);
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_EXPLAIN , this ), 
			NCHRISTMASEVENT_EDIT_EXPLAIN,   "editbox_explain");//����Ʈ ����â

		TCHAR buffer[128] = "";
		for(SI32 Count = 0; Count < MATERIAL_ITEM_MAX_NUM; ++Count)
		{
			_stprintf(buffer, TEXT("listview_item%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( LISTVIEW, NCHRISTMASEVENT_LISTVIEW_ITEM1+Count , this )
				,NCHRISTMASEVENT_LISTVIEW_ITEM1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemname%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMNAME1+Count , this ) 
				,NCHRISTMASEVENT_EDIT_ITEMNAME1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemmaxnum%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMAX1+Count , this )
				,NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count
				,buffer);

			_stprintf(buffer, TEXT("editbox_itemnum%d"), Count+1);
			file.CreateControl(  m_InterfaceFactory.CreateUserInterface( EDIT, NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count , this )
				,NCHRISTMASEVENT_EDIT_ITEMMNUM1+Count
				,buffer);
		}
	
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL , this ), 
			NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL,   "button_donationmaterial");//����ϱ� ��ư ����

		// ����ϱ� ��ư ��ġ ����
		m_InterfaceFactory.GetButton(NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL)->SetX(109);
		m_InterfaceFactory.GetButton(NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL)->SetY(307);
	}

	//���� ������ ��� ���� �⺻ 0���� ����
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM1)->SetText("0");
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM2)->SetText("0");
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM3)->SetText("0");
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM4)->SetText("0");
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM5)->SetText("0");
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM6)->SetText("0");

	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM1)->SetNumberMode(true);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM2)->SetNumberMode(true);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM3)->SetNumberMode(true);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM4)->SetNumberMode(true);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM5)->SetNumberMode(true);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM6)->SetNumberMode(true);

	//ũ�������� ����â
	/*TCHAR* pTextEditChristmas;
	pTextEditChristmas = GetTxtFromMgr(7655);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_EXPLAIN)->SetText(pTextEditChristmas);*/
	//ũ�������� Ʈ�� ī�ε� ã��.
	//ó�� ��������鼭 ������ ���� ������ Ʈ����� ������ ��û.
	////�ٽ� ���Ϲ޾Ƽ� �ش� ���Կ� �ִ´�.
	//����Ʈ�� �䱸�ϴ� ��Ŷ ������.
	//������ ��� ����
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME1)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_CENTER);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME2)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_CENTER);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME3)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_CENTER);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME4)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_CENTER);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME5)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_CENTER);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME6)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_CENTER);
	//������ ��������
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX1)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_RIGHT);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX2)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_RIGHT);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX3)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_RIGHT);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX4)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_RIGHT);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX5)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_RIGHT);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX6)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_RIGHT);

	//������ �Է°���
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM1)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_RIGHT);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM2)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_RIGHT);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM3)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_RIGHT);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM4)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_RIGHT);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM5)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_RIGHT);
	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM6)->SetTextPrintOption(DT_TOP | DT_SINGLELINE | DT_RIGHT);

	//����ϱ� ��ư�ؽ�Ʈ ����
	TCHAR * pinputmat = GetTxtFromMgr(7662);
	m_InterfaceFactory.GetButton(NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL)->SetText(pinputmat);	

	SI32 siVillageUnique = pclClient->pclCM->CR[1]->GetCurrentVillageUnique();//���� ����ũ
	cltEventStructureUnit* pEventNow = pclClient->pclEventStructure->GetEventStructure(EVENT_STRUCTURE_CHRISTMASTREE);//ũ��������Ʈ��
	cltEventStructureUnit* pEventStruct = pclClient->pclEventStructure->GetEventStructure(EVENT_STRUCTURE_TREE);//����Ʈ��
	stListViewItemData ListViewItemData;
	SI32 GlobalImageIndex = -1;
	SI32 GlobalImageFont = -1;

//==============================================================================
	//[����] ������ ���� Ŭ�� . => 2008-6-9
	if(	pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUEBASE")))
	{
		pEventStruct = NULL;
		pEventStruct = pclClient->pclEventStructure->GetEventStructure(EVENT_STRUCTURE_HERO_BRONZE);
		if(NULL == pEventStruct)
			return;

		EventTreeType = EVENT_STRUCTURE_HERO_BRONZE;
		cltGameMsgRequest_Event_MaterialList clMaterialList(siVillageUnique, EventTreeType);
		cltMsg clMaterialListMsg(GAMEMSG_REQUEST_EVENT_MATERIALLIST, sizeof(cltGameMsgRequest_Event_MaterialList), (BYTE*)&clMaterialList);
		
		//����Ʈ�� ������Ʈ �ϱ����� ��Ŷ
		pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMaterialListMsg);

		for(int i=0; i<MAX_MATERIAL_NUMBER; i++)
		{
			cltMaterialInfo* pclMaterialInfo = &pEventStruct->clMaterial[i];

			if(pclMaterialInfo == NULL)												
				continue;
			
			SI16 siUnique  = pclMaterialInfo->siUnique;
			SI16 siNeedNum = pclMaterialInfo->siNeedNum;
			if(siUnique <= 0 || siNeedNum <= 0)	
				continue;

			cltItem clItemMaterial;
			clItemMaterial.Init();

			SI16 brareswitch = 0;
			if(pclClient->pclItemManager->MakeRandItemUnique( pclMaterialInfo->siUnique, &clItemMaterial, 0, 0, &brareswitch,0,0,0,0,0,0) == true)//�������� ��Ḧ ���ؿ´�.
			{
				SI32 siControlID = NCHRISTMASEVENT_LISTVIEW_ITEM1 + i;
				if(siControlID <= NCHRISTMASEVENT_LISTVIEW_ITEM6)
				{
					clItemMaterial.SetItemNum( pclMaterialInfo->siNeedNum );

					char ToolTipMsg[ MAX_TOOLTIP_MSG_SIZE ] = "";
					char *ItemName = (char*)pclClient->pclItemManager->GetName(pclMaterialInfo->siUnique);
					pclClient->pclItemManager->GetItemGImageFileIndexAndFont( pclMaterialInfo->siUnique, &GlobalImageIndex, &GlobalImageFont );
					pclClient->pclItemManager->GetExplain(&clItemMaterial, ToolTipMsg);
					ListViewItemData.Set( GlobalImageIndex, GlobalImageFont, 0 ,pclMaterialInfo->siNeedNum, ItemName, ToolTipMsg );
					CListView* ItemImage1 = m_InterfaceFactory.GetListView(siControlID);
					ItemImage1->InsertItem(&ListViewItemData);
				}				
				
				//������������ũ�� ��� ������ ������ �迭�� ����� ��� ������.
				matitemunique[i]=pclMaterialInfo->siUnique;
				matitemnum[i]= pclMaterialInfo->siNeedNum;
			}
		}

		// ��� �̸�.
		const TCHAR* pitemname[MATERIAL_ITEM_MAX_NUM] = {NULL, }; 
		for(SI32 Count = 0; Count < MATERIAL_ITEM_MAX_NUM; Count++)
		{
			pitemname[Count] = pclClient->pclItemManager->GetName(matitemunique[Count]);
			m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME1+Count)->SetText((TCHAR*)pitemname[Count]);
			m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME1+Count)->ShowScrollBar(false);
		}
				
		SI32 invennum = 0;
		SI32 matnum	  = 0;
		// ��� ������ ���� ���� ������ ������ �� �Ѵ�.
		for( matnum = 0; matnum < MAX_MATERIAL_NUMBER; matnum++)
		{
			SI32 siMaterialUnique	= matitemunique[matnum];//��� ������
			SI32 siMaterialNum		= matitemnum[matnum];

			if( siMaterialUnique <= 0 || siMaterialNum <= 0 )		continue;

			// �κ����� �ش� ��Ḧ ã�´�. 
			for( invennum = PERSONITEM_INV0; invennum < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON; invennum++ )
			{
				cltItem* pclItem = &pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[invennum];
				if(pclItem == NULL)					continue;

				if( pclItem->siUnique == siMaterialUnique)
				{
					matitemEndunique[matnum] = pclItem->siItemNum;			//���� ������ �ִ� �����۵��� ����ũ�� ����
					
					SI32 siNum = pclItem->siItemNum;
					if(siNum > siMaterialNum)	
					{
						matitemEndnum[matnum]	= siMaterialNum;
						siNum					= matitemEndnum[matnum];
					}
					else
					{
						matitemEndnum[matnum]	= siNum;
					}

					if( (0 <= matnum) && (matnum < MATERIAL_ITEM_MAX_NUM) )	
					{
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM1+matnum)->SetText(itemnum);//itemnum);
						break;
					}
				}
			}
		}
	}
//=======================================================================================================

	//==============================================================================
	//[����] �ҷ��� �д� //Switch_HalloweenEvent
	if(	pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_HALLOWEENBASE")))
	{
		pEventStruct = NULL;
		pEventStruct = pclClient->pclEventStructure->GetEventStructure(EVENT_STRUCTURE_HALLOWEEN);
		if(NULL == pEventStruct)
			return;

		EventTreeType = EVENT_STRUCTURE_HALLOWEEN;
		cltGameMsgRequest_Event_MaterialList clMaterialList(siVillageUnique, EventTreeType);
		cltMsg clMaterialListMsg(GAMEMSG_REQUEST_EVENT_MATERIALLIST, sizeof(cltGameMsgRequest_Event_MaterialList), (BYTE*)&clMaterialList);

		//����Ʈ�� ������Ʈ �ϱ����� ��Ŷ
		pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMaterialListMsg);

		for(int i=0; i<MAX_MATERIAL_NUMBER; i++)
		{
			cltMaterialInfo* pclMaterialInfo = &pEventStruct->clMaterial[i];

			if(pclMaterialInfo == NULL)												
				continue;

			SI16 siUnique  = pclMaterialInfo->siUnique;
			SI16 siNeedNum = pclMaterialInfo->siNeedNum;
			if(siUnique <= 0 || siNeedNum <= 0)	
				continue;

			cltItem clItemMaterial;
			clItemMaterial.Init();

			SI16 brareswitch = 0;
			if(pclClient->pclItemManager->MakeRandItemUnique( pclMaterialInfo->siUnique, &clItemMaterial, 0, 0, &brareswitch,0,0,0,0,0,0) == true)//�������� ��Ḧ ���ؿ´�.
			{
				SI32 siControlID = NCHRISTMASEVENT_LISTVIEW_ITEM1 + i;
				if(siControlID <= NCHRISTMASEVENT_LISTVIEW_ITEM6)
				{
					clItemMaterial.SetItemNum( pclMaterialInfo->siNeedNum );

					char ToolTipMsg[ MAX_TOOLTIP_MSG_SIZE ] = "";
					char *ItemName = (char*)pclClient->pclItemManager->GetName(pclMaterialInfo->siUnique);
					pclClient->pclItemManager->GetItemGImageFileIndexAndFont( pclMaterialInfo->siUnique, &GlobalImageIndex, &GlobalImageFont );
					pclClient->pclItemManager->GetExplain(&clItemMaterial, ToolTipMsg);
					ListViewItemData.Set( GlobalImageIndex, GlobalImageFont, 0 ,pclMaterialInfo->siNeedNum, ItemName, ToolTipMsg );
					CListView* ItemImage1 = m_InterfaceFactory.GetListView(siControlID);
					ItemImage1->InsertItem(&ListViewItemData);
				}				

				//������������ũ�� ��� ������ ������ �迭�� ����� ��� ������.
				matitemunique[i]=pclMaterialInfo->siUnique;
				matitemnum[i]= pclMaterialInfo->siNeedNum;
			}
		}

		// ��� �̸�.
		const TCHAR* pitemname[MATERIAL_ITEM_MAX_NUM] = {NULL, }; 
		for(SI32 Count = 0; Count < MATERIAL_ITEM_MAX_NUM; Count++)
		{
			pitemname[Count] = pclClient->pclItemManager->GetName(matitemunique[Count]);
			m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME1+Count)->SetText((TCHAR*)pitemname[Count]);
			m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME1+Count)->ShowScrollBar(false);
		}

		SI32 invennum = 0;
		SI32 matnum	  = 0;
		// ��� ������ ���� ���� ������ ������ �� �Ѵ�.
		for( matnum = 0; matnum < MAX_MATERIAL_NUMBER; matnum++)
		{
			SI32 siMaterialUnique	= matitemunique[matnum];//��� ������
			SI32 siMaterialNum		= matitemnum[matnum];

			if( siMaterialUnique <= 0 || siMaterialNum <= 0 )		continue;

			// �κ����� �ش� ��Ḧ ã�´�. 
			for( invennum = PERSONITEM_INV0; invennum < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON; invennum++ )
			{
				cltItem* pclItem = &pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[invennum];
				if(pclItem == NULL)					continue;

				if( pclItem->siUnique == siMaterialUnique)
				{
					matitemEndunique[matnum] = pclItem->siItemNum;			//���� ������ �ִ� �����۵��� ����ũ�� ����

					SI32 siNum = pclItem->siItemNum;
					if(siNum > siMaterialNum)	
					{
						matitemEndnum[matnum]	= siMaterialNum;
						siNum					= matitemEndnum[matnum];
					}
					else
					{
						matitemEndnum[matnum]	= siNum;
					}

					if( (0 <= matnum) && (matnum < MATERIAL_ITEM_MAX_NUM) )	
					{
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM1+matnum)->SetText(itemnum);//itemnum);
						break;
					}
				}
			}
		}
		// ��ᰡ 4���� ���ϱ� 2���� �Ⱥ����ش�
		m_InterfaceFactory.GetListView(NCHRISTMASEVENT_LISTVIEW_ITEM5)->Show(false);
		m_InterfaceFactory.GetListView(NCHRISTMASEVENT_LISTVIEW_ITEM6)->Show(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME5)->Show(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME6)->Show(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM5)->Show(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM6)->Show(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX5)->Show(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX6)->Show(false);
	}
	//=======================================================================================================


	if(pEventStruct/*����Ʈ���̸�*/
		&& pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_PINE_TREE")))
	{
		EventTreeType = EVENT_STRUCTURE_TREE;
		cltGameMsgRequest_Event_MaterialList clMaterialList(siVillageUnique,EVENT_STRUCTURE_TREE);
		cltMsg clMaterialListMsg(GAMEMSG_REQUEST_EVENT_MATERIALLIST, sizeof(cltGameMsgRequest_Event_MaterialList), (BYTE*)&clMaterialList);
		pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMaterialListMsg);//����Ʈ�� ������Ʈ �ϱ����� ��Ŷ

		for(int i=0; i<MAX_MATERIAL_NUMBER; i++)
		{
			cltMaterialInfo* pclMaterialInfo = &pEventStruct->clMaterial[i];

			if(pclMaterialInfo == NULL)												continue;
			SI16 siUnique = pclMaterialInfo->siUnique;
			SI16 siNeedNum = pclMaterialInfo->siNeedNum;
			if(siUnique <= 0 || siNeedNum <= 0)	continue;

			cltItem clItemMaterial;
			clItemMaterial.Init();

			SI16 brareswitch = 0;
			if(pclClient->pclItemManager->MakeRandItemUnique( pclMaterialInfo->siUnique, &clItemMaterial, 0, 0, &brareswitch,0,0,0,0,0,0) == true)//�������� ��Ḧ ���ؿ´�.
			{
				SI32 siControlID = NCHRISTMASEVENT_LISTVIEW_ITEM1 + i;
				if(siControlID <= NCHRISTMASEVENT_LISTVIEW_ITEM6)
				{
					clItemMaterial.SetItemNum( pclMaterialInfo->siNeedNum );

					char ToolTipMsg[ MAX_TOOLTIP_MSG_SIZE ] = "";
					char *ItemName = (char*)pclClient->pclItemManager->GetName(pclMaterialInfo->siUnique);
					pclClient->pclItemManager->GetItemGImageFileIndexAndFont( pclMaterialInfo->siUnique, &GlobalImageIndex, &GlobalImageFont );
					pclClient->pclItemManager->GetExplain(&clItemMaterial, ToolTipMsg);
					ListViewItemData.Set( GlobalImageIndex, GlobalImageFont, 0 ,pclMaterialInfo->siNeedNum, ItemName, ToolTipMsg );
					CListView* ItemImage1 = m_InterfaceFactory.GetListView(siControlID);
					ItemImage1->InsertItem(&ListViewItemData);
				}				
				//������������ũ�� ��� ������ ������ �迭�� ����� ��� ������.
				matitemunique[i]=pclMaterialInfo->siUnique;
				matitemnum[i]= pclMaterialInfo->siNeedNum;
				//�������� �̸��� ������ �´�.
			}
		}//�������� �ݺ����� ��.
		//�������� �̸� ����
		const TCHAR* pitemname1 = pclClient->pclItemManager->GetName(matitemunique[0]);
		const TCHAR* pitemname2 = pclClient->pclItemManager->GetName(matitemunique[1]);
		const TCHAR* pitemname3 = pclClient->pclItemManager->GetName(matitemunique[2]);
		const TCHAR* pitemname4 = pclClient->pclItemManager->GetName(matitemunique[3]);
		const TCHAR* pitemname5 = pclClient->pclItemManager->GetName(matitemunique[4]);
		const TCHAR* pitemname6 = pclClient->pclItemManager->GetName(matitemunique[5]);
		//������ �̸� ����
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME1)->SetText((TCHAR*)pitemname1);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME2)->SetText((TCHAR*)pitemname2);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME3)->SetText((TCHAR*)pitemname3);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME4)->SetText((TCHAR*)pitemname4);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME5)->SetText((TCHAR*)pitemname5);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME6)->SetText((TCHAR*)pitemname6);
		//��ũ�ѹ� �ɼ��̸��� ������ �ʵ���
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME1)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME2)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME3)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME4)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME5)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME6)->ShowScrollBar(false);

		int		invennum, matnum;
		// ��� ������ ���� ���� ������ ������ �� �Ѵ�.
		for( matnum = 0;matnum < MAX_MATERIAL_NUMBER; matnum++)
		{
			SI32 siMaterialUnique	= matitemunique[matnum];//��� ������
			SI32 siMaterialNum		= matitemnum[matnum];

			if( siMaterialUnique <= 0 || siMaterialNum <= 0 )		continue;

			// �κ����� �ش� ��Ḧ ã�´�. 
			for( invennum = PERSONITEM_INV0; invennum < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON; invennum++ )
			{
				cltItem* pclItem = &pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[invennum];
				if(pclItem == NULL)					continue;

				if( pclItem->siUnique == siMaterialUnique)
				{
					matitemEndunique[matnum] = pclItem->siItemNum;//���� ������ �ִ� �����۵��� ����ũ�� ����
					SI32 siNum = pclItem->siItemNum;
					if(siNum > siMaterialNum)	{
						matitemEndnum[matnum]= siMaterialNum;
						siNum = matitemEndnum[matnum];}
					else{
						matitemEndnum[matnum]= siNum;
					}
					

					if (matnum == 0) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM1)->SetText(itemnum);//itemnum);
						break;
					}
					if (matnum == 1) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM2)->SetText(itemnum);
						break;
					}
					if (matnum == 2) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM3)->SetText(itemnum);
						break;
					}
					if (matnum == 3) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM4)->SetText(itemnum);
						break;
					}
					if (matnum == 4) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM5)->SetText(itemnum);
						break;
					}
					if (matnum == 5) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM6)->SetText(itemnum);
						break;
					}				
				}
			}
		}
	}

	//KHY - 1113 - ũ�������� �̺�Ʈ -
	if( pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREEBASE")))
	{
		pEventStruct = NULL;
		pEventStruct = pclClient->pclEventStructure->GetEventStructure(EVENT_STRUCTURE_CHRISTMASTREEBASE);
		if(NULL == pEventStruct)
			return;
	
		EventTreeType = EVENT_STRUCTURE_CHRISTMASTREEBASE;
		cltGameMsgRequest_Event_MaterialList clMaterialList(siVillageUnique,EVENT_STRUCTURE_CHRISTMASTREEBASE);
		cltMsg clMaterialListMsg(GAMEMSG_REQUEST_EVENT_MATERIALLIST, sizeof(cltGameMsgRequest_Event_MaterialList), (BYTE*)&clMaterialList);
		pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMaterialListMsg);//����Ʈ�� ������Ʈ �ϱ����� ��Ŷ

		for(int i=0; i<MAX_MATERIAL_NUMBER; i++)
		{
			cltMaterialInfo* pclMaterialInfo = &pEventStruct->clMaterial[i];

			if(pclMaterialInfo == NULL)												continue;
			SI16 siUnique = pclMaterialInfo->siUnique;
			SI16 siNeedNum = pclMaterialInfo->siNeedNum;
			if(siUnique <= 0 || siNeedNum <= 0)	continue;

			cltItem clItemMaterial;
			clItemMaterial.Init();

			SI16 brareswitch = 0;
			if(pclClient->pclItemManager->MakeRandItemUnique( pclMaterialInfo->siUnique, &clItemMaterial, 0, 0, &brareswitch,0,0,0,0,0,0) == true)//�������� ��Ḧ ���ؿ´�.
			{
				SI32 siControlID = NCHRISTMASEVENT_LISTVIEW_ITEM1 + i;
				if(siControlID <= NCHRISTMASEVENT_LISTVIEW_ITEM6)
				{
					clItemMaterial.SetItemNum( pclMaterialInfo->siNeedNum );

					char ToolTipMsg[ MAX_TOOLTIP_MSG_SIZE ] = "";
					char *ItemName = (char*)pclClient->pclItemManager->GetName(pclMaterialInfo->siUnique);
					pclClient->pclItemManager->GetItemGImageFileIndexAndFont( pclMaterialInfo->siUnique, &GlobalImageIndex, &GlobalImageFont );
					pclClient->pclItemManager->GetExplain(&clItemMaterial, ToolTipMsg);
					ListViewItemData.Set( GlobalImageIndex, GlobalImageFont, 0 ,pclMaterialInfo->siNeedNum, ItemName, ToolTipMsg );
					CListView* ItemImage1 = m_InterfaceFactory.GetListView(siControlID);
					ItemImage1->InsertItem(&ListViewItemData);
				}				
				//������������ũ�� ��� ������ ������ �迭�� ����� ��� ������.
				matitemunique[i]=pclMaterialInfo->siUnique;
				matitemnum[i]= pclMaterialInfo->siNeedNum;
				//�������� �̸��� ������ �´�.
			}
		}//�������� �ݺ����� ��.
		//�������� �̸� ����
		const TCHAR* pitemname1 = pclClient->pclItemManager->GetName(matitemunique[0]);
		const TCHAR* pitemname2 = pclClient->pclItemManager->GetName(matitemunique[1]);
		const TCHAR* pitemname3 = pclClient->pclItemManager->GetName(matitemunique[2]);
		const TCHAR* pitemname4 = pclClient->pclItemManager->GetName(matitemunique[3]);
		const TCHAR* pitemname5 = pclClient->pclItemManager->GetName(matitemunique[4]);
		const TCHAR* pitemname6 = pclClient->pclItemManager->GetName(matitemunique[5]);
		//������ �̸� ����
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME1)->SetText((TCHAR*)pitemname1);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME2)->SetText((TCHAR*)pitemname2);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME3)->SetText((TCHAR*)pitemname3);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME4)->SetText((TCHAR*)pitemname4);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME5)->SetText((TCHAR*)pitemname5);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME6)->SetText((TCHAR*)pitemname6);
		//��ũ�ѹ� �ɼ��̸��� ������ �ʵ���
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME1)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME2)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME3)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME4)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME5)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME6)->ShowScrollBar(false);

		int		invennum, matnum;
		// ��� ������ ���� ���� ������ ������ �� �Ѵ�.
		for( matnum = 0;matnum < MAX_MATERIAL_NUMBER; matnum++)
		{
			SI32 siMaterialUnique	= matitemunique[matnum];//��� ������
			SI32 siMaterialNum		= matitemnum[matnum];

			if( siMaterialUnique <= 0 || siMaterialNum <= 0 )		continue;

			// �κ����� �ش� ��Ḧ ã�´�. 
			for( invennum = PERSONITEM_INV0; invennum < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON; invennum++ )
			{
				cltItem* pclItem = &pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[invennum];
				if(pclItem == NULL)					continue;

				if( pclItem->siUnique == siMaterialUnique)
				{
					matitemEndunique[matnum] = pclItem->siItemNum;//���� ������ �ִ� �����۵��� ����ũ�� ����
					SI32 siNum = pclItem->siItemNum;
					if(siNum > siMaterialNum)	{
						matitemEndnum[matnum]= siMaterialNum;
						siNum = matitemEndnum[matnum];}
					else{
						matitemEndnum[matnum]= siNum;
					}
					

					if (matnum == 0) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM1)->SetText(itemnum);//itemnum);
						break;
					}
					if (matnum == 1) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM2)->SetText(itemnum);
						break;
					}
					if (matnum == 2) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM3)->SetText(itemnum);
						break;
					}
					if (matnum == 3) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM4)->SetText(itemnum);
						break;
					}
					if (matnum == 4) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM5)->SetText(itemnum);
						break;
					}
					if (matnum == 5) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM6)->SetText(itemnum);
						break;
					}				
				}
			}
		}
	}
	Show(true);

	// ��� - �ų��̺�Ʈ
	if( pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREEBASE")))
	{
		pEventStruct = NULL;
		pEventStruct = pclClient->pclEventStructure->GetEventStructure(EVENT_STRUCTURE_NEWYEARTREEBASE);
		if(NULL == pEventStruct)
			return;

		EventTreeType = EVENT_STRUCTURE_NEWYEARTREEBASE;
		cltGameMsgRequest_Event_MaterialList clMaterialList(siVillageUnique,EVENT_STRUCTURE_NEWYEARTREEBASE);
		cltMsg clMaterialListMsg(GAMEMSG_REQUEST_EVENT_MATERIALLIST, sizeof(cltGameMsgRequest_Event_MaterialList), (BYTE*)&clMaterialList);
		pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMaterialListMsg);//����Ʈ�� ������Ʈ �ϱ����� ��Ŷ

		for(int i=0; i<MAX_MATERIAL_NUMBER; i++)
		{
			cltMaterialInfo* pclMaterialInfo = &pEventStruct->clMaterial[i];

			if(pclMaterialInfo == NULL)												continue;
			SI16 siUnique = pclMaterialInfo->siUnique;
			SI16 siNeedNum = pclMaterialInfo->siNeedNum;
			if(siUnique <= 0 || siNeedNum <= 0)	continue;

			cltItem clItemMaterial;
			clItemMaterial.Init();

			SI16 brareswitch = 0;
			if(pclClient->pclItemManager->MakeRandItemUnique( pclMaterialInfo->siUnique, &clItemMaterial, 0, 0, &brareswitch,0,0,0,0,0,0) == true)//�������� ��Ḧ ���ؿ´�.
			{
				SI32 siControlID = NCHRISTMASEVENT_LISTVIEW_ITEM1 + i;
				if(siControlID <= NCHRISTMASEVENT_LISTVIEW_ITEM6)
				{
					clItemMaterial.SetItemNum( pclMaterialInfo->siNeedNum );

					char ToolTipMsg[ MAX_TOOLTIP_MSG_SIZE ] = "";
					char *ItemName = (char*)pclClient->pclItemManager->GetName(pclMaterialInfo->siUnique);
					pclClient->pclItemManager->GetItemGImageFileIndexAndFont( pclMaterialInfo->siUnique, &GlobalImageIndex, &GlobalImageFont );
					pclClient->pclItemManager->GetExplain(&clItemMaterial, ToolTipMsg);
					ListViewItemData.Set( GlobalImageIndex, GlobalImageFont, 0 ,pclMaterialInfo->siNeedNum, ItemName, ToolTipMsg );
					CListView* ItemImage1 = m_InterfaceFactory.GetListView(siControlID);
					ItemImage1->InsertItem(&ListViewItemData);
				}				
				//������������ũ�� ��� ������ ������ �迭�� ����� ��� ������.
				matitemunique[i]=pclMaterialInfo->siUnique;
				matitemnum[i]= pclMaterialInfo->siNeedNum;
				//�������� �̸��� ������ �´�.
			}
		}//�������� �ݺ����� ��.
		//�������� �̸� ����
		const TCHAR* pitemname1 = pclClient->pclItemManager->GetName(matitemunique[0]);
		const TCHAR* pitemname2 = pclClient->pclItemManager->GetName(matitemunique[1]);
		const TCHAR* pitemname3 = pclClient->pclItemManager->GetName(matitemunique[2]);
		const TCHAR* pitemname4 = pclClient->pclItemManager->GetName(matitemunique[3]);
		const TCHAR* pitemname5 = pclClient->pclItemManager->GetName(matitemunique[4]);
		const TCHAR* pitemname6 = pclClient->pclItemManager->GetName(matitemunique[5]);
		//������ �̸� ����
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME1)->SetText((TCHAR*)pitemname1);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME2)->SetText((TCHAR*)pitemname2);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME3)->SetText((TCHAR*)pitemname3);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME4)->SetText((TCHAR*)pitemname4);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME5)->SetText((TCHAR*)pitemname5);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME6)->SetText((TCHAR*)pitemname6);
		//��ũ�ѹ� �ɼ��̸��� ������ �ʵ���
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME1)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME2)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME3)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME4)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME5)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME6)->ShowScrollBar(false);

		int		invennum, matnum;
		// ��� ������ ���� ���� ������ ������ �� �Ѵ�.
		for( matnum = 0;matnum < MAX_MATERIAL_NUMBER; matnum++)
		{
			SI32 siMaterialUnique	= matitemunique[matnum];//��� ������
			SI32 siMaterialNum		= matitemnum[matnum];

			if( siMaterialUnique <= 0 || siMaterialNum <= 0 )		continue;

			// �κ����� �ش� ��Ḧ ã�´�. 
			for( invennum = PERSONITEM_INV0; invennum < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON; invennum++ )
			{
				cltItem* pclItem = &pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[invennum];
				if(pclItem == NULL)					continue;

				if( pclItem->siUnique == siMaterialUnique)
				{
					matitemEndunique[matnum] = pclItem->siItemNum;//���� ������ �ִ� �����۵��� ����ũ�� ����
					SI32 siNum = pclItem->siItemNum;
					if(siNum > siMaterialNum)	{
						matitemEndnum[matnum]= siMaterialNum;
						siNum = matitemEndnum[matnum];}
					else{
						matitemEndnum[matnum]= siNum;
					}


					if (matnum == 0) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM1)->SetText(itemnum);//itemnum);
						break;
					}
					if (matnum == 1) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM2)->SetText(itemnum);
						break;
					}
					if (matnum == 2) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM3)->SetText(itemnum);
						break;
					}
					if (matnum == 3) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM4)->SetText(itemnum);
						break;
					}
					if (matnum == 4) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM5)->SetText(itemnum);
						break;
					}
					if (matnum == 5) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM6)->SetText(itemnum);
						break;
					}				
				}
			}
		}
	}

	if(pEventNow/*ũ�������� Ʈ���϶�*/
		&&pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE")))
	{
		EventTreeType = EVENT_STRUCTURE_CHRISTMASTREE;
		cltGameMsgRequest_Event_MaterialList clMaterialList(siVillageUnique,EVENT_STRUCTURE_CHRISTMASTREE);
		cltMsg clMaterialListMsg(GAMEMSG_REQUEST_EVENT_MATERIALLIST, sizeof(cltGameMsgRequest_Event_MaterialList), (BYTE*)&clMaterialList);
		pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMaterialListMsg);//����Ʈ�� ������Ʈ �ϱ����� ��Ŷ

		for(int i=0; i<MAX_MATERIAL_NUMBER; i++)
		{
			cltMaterialInfo* pclMaterialInfo = &pEventNow->clMaterial[i];

			if(pclMaterialInfo == NULL)												continue;
			SI16 siUnique = pclMaterialInfo->siUnique;
			SI16 siNeedNum = pclMaterialInfo->siNeedNum;
			if(siUnique <= 0 || siNeedNum <= 0)	continue;

			cltItem clItemMaterial;
			clItemMaterial.Init();

			SI16 brareswitch = 0;
			if(pclClient->pclItemManager->MakeRandItemUnique( pclMaterialInfo->siUnique, &clItemMaterial, 0, 0, &brareswitch,0,0,0,0,0,0) == true)//�������� ��Ḧ ���ؿ´�.
			{
				SI32 siControlID = NCHRISTMASEVENT_LISTVIEW_ITEM1 + i;
				if(siControlID <= NCHRISTMASEVENT_LISTVIEW_ITEM6)
				{
					clItemMaterial.SetItemNum( pclMaterialInfo->siNeedNum );

					char ToolTipMsg[ MAX_TOOLTIP_MSG_SIZE ] = "";
					char *ItemName = (char*)pclClient->pclItemManager->GetName(pclMaterialInfo->siUnique);
					pclClient->pclItemManager->GetItemGImageFileIndexAndFont( pclMaterialInfo->siUnique, &GlobalImageIndex, &GlobalImageFont );
					pclClient->pclItemManager->GetExplain(&clItemMaterial, ToolTipMsg);
					ListViewItemData.Set( GlobalImageIndex, GlobalImageFont, 0 ,pclMaterialInfo->siNeedNum, ItemName, ToolTipMsg );
					CListView* ItemImage1 = m_InterfaceFactory.GetListView(siControlID);
					ItemImage1->InsertItem(&ListViewItemData);
				}				
				//�ش� �����۰� �ش�����۰����� ���������� �迭�� ����.;
				matitemunique[i]=pclMaterialInfo->siUnique;
				matitemnum[i]= pclMaterialInfo->siNeedNum;
				//�������� �̸��� ������ �´�.
			}
		}//�������� �ݺ����� ��.
		//������ �̸� ����
		const TCHAR* pitemname1 = pclClient->pclItemManager->GetName(matitemunique[0]);
		const TCHAR* pitemname2 = pclClient->pclItemManager->GetName(matitemunique[1]);
		const TCHAR* pitemname3 = pclClient->pclItemManager->GetName(matitemunique[2]);
		const TCHAR* pitemname4 = pclClient->pclItemManager->GetName(matitemunique[3]);
		const TCHAR* pitemname5 = pclClient->pclItemManager->GetName(matitemunique[4]);
		const TCHAR* pitemname6 = pclClient->pclItemManager->GetName(matitemunique[5]);

		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME1)->SetText((TCHAR*)pitemname1);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME2)->SetText((TCHAR*)pitemname2);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME3)->SetText((TCHAR*)pitemname3);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME4)->SetText((TCHAR*)pitemname4);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME5)->SetText((TCHAR*)pitemname5);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME6)->SetText((TCHAR*)pitemname6);

		//��ũ�ѹ� �ɼ��̸��� ������ �ʵ���
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME1)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME2)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME3)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME4)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME5)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME6)->ShowScrollBar(false);


		int		invennum, matnum;
		// ��� ������ ���� ���� ������ ������ �� �Ѵ�.
		for( matnum = 0;matnum < MAX_MATERIAL_NUMBER; matnum++)
		{
			SI32 siMaterialUnique	= matitemunique[matnum];
			SI32 siMaterialNum		= matitemnum[matnum];

			if( siMaterialUnique <= 0 || siMaterialNum <= 0 )		continue;

			// �κ����� �ش� ��Ḧ ã�´�. 
			for( invennum = PERSONITEM_INV0; invennum < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON; invennum++ )
			{
				cltItem* pclItem = &pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[invennum];
				if(pclItem == NULL)					continue;

				if( pclItem->siUnique == siMaterialUnique)
				{
					matitemEndunique[matnum] = pclItem->siUnique;//���� ������ �ִ� �����۵��� ����ũ�� ����
					SI32 siNum = pclItem->siItemNum;
					if(siNum > siMaterialNum)	{
						matitemEndnum[matnum]= siMaterialNum;
						siNum = matitemEndnum[matnum];}
					else{
						matitemEndnum[matnum]= siNum;
					}


					if (matnum == 0) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM1)->SetText(itemnum);//itemnum);
						break;
					}
					if (matnum == 1) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM2)->SetText(itemnum);
						break;
					}
					if (matnum == 2) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM3)->SetText(itemnum);
						break;
					}
					if (matnum == 3) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM4)->SetText(itemnum);
						break;
					}
					if (matnum == 4) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM5)->SetText(itemnum);
						break;
					}
					if (matnum == 5) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM6)->SetText(itemnum);
						break;
					}				
				}
			}
		}
	}

	// [���] ũ�������� �̺�Ʈ - ���縮�� �տ� �ִ� ũ���� ���� Ʈ�� (09.10.21)
	if(pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASWORLDTREE01"))
		|| pclClient->pclCM->CR[id]->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASWORLDTREE02")))
	{
		pEventNow = NULL;
		pEventNow = pclClient->pclEventStructure->GetEventStructure(EVENT_STRUCTURE_WORLDCHRISTMASTREE);
		if(NULL == pEventNow)
			return;

		EventTreeType = EVENT_STRUCTURE_WORLDCHRISTMASTREE;
		cltGameMsgRequest_Event_MaterialList clMaterialList(VILLAGE_NONE, EVENT_STRUCTURE_WORLDCHRISTMASTREE);
		cltMsg clMaterialListMsg(GAMEMSG_REQUEST_EVENT_MATERIALLIST, sizeof(cltGameMsgRequest_Event_MaterialList), (BYTE*)&clMaterialList);
		pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMaterialListMsg);//����Ʈ�� ������Ʈ �ϱ����� ��Ŷ

		for(int i=0; i<MAX_MATERIAL_NUMBER; i++)
		{
			cltMaterialInfo* pclMaterialInfo = &pEventNow->clMaterial[i];

			if(pclMaterialInfo == NULL)												continue;
			SI16 siUnique = pclMaterialInfo->siUnique;
			SI16 siNeedNum = pclMaterialInfo->siNeedNum;
			if(siUnique <= 0 || siNeedNum <= 0)	continue;

			cltItem clItemMaterial;
			clItemMaterial.Init();

			SI16 brareswitch = 0;
			if(pclClient->pclItemManager->MakeRandItemUnique( pclMaterialInfo->siUnique, &clItemMaterial, 0, 0, &brareswitch,0,0,0,0,0,0) == true)//�������� ��Ḧ ���ؿ´�.
			{
				SI32 siControlID = NCHRISTMASEVENT_LISTVIEW_ITEM1 + i;
				if(siControlID <= NCHRISTMASEVENT_LISTVIEW_ITEM6)
				{
					clItemMaterial.SetItemNum( pclMaterialInfo->siNeedNum );

					char ToolTipMsg[ MAX_TOOLTIP_MSG_SIZE ] = "";
					char *ItemName = (char*)pclClient->pclItemManager->GetName(pclMaterialInfo->siUnique);
					pclClient->pclItemManager->GetItemGImageFileIndexAndFont( pclMaterialInfo->siUnique, &GlobalImageIndex, &GlobalImageFont );
					pclClient->pclItemManager->GetExplain(&clItemMaterial, ToolTipMsg);
					ListViewItemData.Set( GlobalImageIndex, GlobalImageFont, 0 ,pclMaterialInfo->siNeedNum, ItemName, ToolTipMsg );
					CListView* ItemImage1 = m_InterfaceFactory.GetListView(siControlID);
					ItemImage1->InsertItem(&ListViewItemData);
				}				
				//�ش� �����۰� �ش�����۰����� ���������� �迭�� ����.;
				matitemunique[i]=pclMaterialInfo->siUnique;
				matitemnum[i]= pclMaterialInfo->siNeedNum;
				//�������� �̸��� ������ �´�.
			}
		}//�������� �ݺ����� ��.
		//������ �̸� ����
		const TCHAR* pitemname1 = pclClient->pclItemManager->GetName(matitemunique[0]);
		const TCHAR* pitemname2 = pclClient->pclItemManager->GetName(matitemunique[1]);
		const TCHAR* pitemname3 = pclClient->pclItemManager->GetName(matitemunique[2]);
		const TCHAR* pitemname4 = pclClient->pclItemManager->GetName(matitemunique[3]);
		const TCHAR* pitemname5 = pclClient->pclItemManager->GetName(matitemunique[4]);
		const TCHAR* pitemname6 = pclClient->pclItemManager->GetName(matitemunique[5]);

		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME1)->SetText((TCHAR*)pitemname1);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME2)->SetText((TCHAR*)pitemname2);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME3)->SetText((TCHAR*)pitemname3);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME4)->SetText((TCHAR*)pitemname4);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME5)->SetText((TCHAR*)pitemname5);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME6)->SetText((TCHAR*)pitemname6);

		//��ũ�ѹ� �ɼ��̸��� ������ �ʵ���
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME1)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME2)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME3)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME4)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME5)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMNAME6)->ShowScrollBar(false);


		int		invennum, matnum;
		// ��� ������ ���� ���� ������ ������ �� �Ѵ�.
		for( matnum = 0;matnum < MAX_MATERIAL_NUMBER; matnum++)
		{
			SI32 siMaterialUnique	= matitemunique[matnum];
			SI32 siMaterialNum		= matitemnum[matnum];

			if( siMaterialUnique <= 0 || siMaterialNum <= 0 )		continue;

			// �κ����� �ش� ��Ḧ ã�´�. 
			for( invennum = PERSONITEM_INV0; invennum < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON; invennum++ )
			{
				cltItem* pclItem = &pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[invennum];
				if(pclItem == NULL)					continue;

				if( pclItem->siUnique == siMaterialUnique)
				{
					matitemEndunique[matnum] = pclItem->siUnique;//���� ������ �ִ� �����۵��� ����ũ�� ����
					SI32 siNum = pclItem->siItemNum;
					if(siNum > siMaterialNum)	{
						matitemEndnum[matnum]= siMaterialNum;
						siNum = matitemEndnum[matnum];}
					else{
						matitemEndnum[matnum]= siNum;
					}


					if (matnum == 0) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM1)->SetText(itemnum);//itemnum);
						break;
					}
					if (matnum == 1) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM2)->SetText(itemnum);
						break;
					}
					if (matnum == 2) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM3)->SetText(itemnum);
						break;
					}
					if (matnum == 3) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM4)->SetText(itemnum);
						break;
					}
					if (matnum == 4) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM5)->SetText(itemnum);
						break;
					}
					if (matnum == 5) {
						TCHAR itemnum[128]= TEXT("") ;
						StringCchPrintf(itemnum, 128, TEXT("%d"), siNum);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM6)->SetText(itemnum);
						break;
					}				
				}
			}
		}
	}
}

void CALLBACK NChristmasEventDlg ::StaticSelectChristmasEventProc(CControllerMgr *pControllerMgr,UINT nEvent, int nControlID,CControllerObj *pControl)
{
	NChristmasEventDlg *pThis = (NChristmasEventDlg*)pControllerMgr;
	pThis->NSelectChristmasEventProc(nEvent, nControlID, pControl);
}


void CALLBACK NChristmasEventDlg ::NSelectChristmasEventProc(UINT nEvent, int nControlID,CControllerObj* pControl)
{
	cltClient *pclclient = (cltClient *)pclClient;
	SI32 siVillageUnique = pclClient->pclCM->CR[1]->GetCurrentVillageUnique();

	switch(nControlID)
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			if (EVENT_BUTTON_CLICKED == nEvent)
			{
				DeleteDialog();
			}
		}
		break;
	case NCHRISTMASEVENT_EDIT_ITEMMNUM1:
	case NCHRISTMASEVENT_EDIT_ITEMMNUM2:
	case NCHRISTMASEVENT_EDIT_ITEMMNUM3:
	case NCHRISTMASEVENT_EDIT_ITEMMNUM4:
	case NCHRISTMASEVENT_EDIT_ITEMMNUM5:
	case NCHRISTMASEVENT_EDIT_ITEMMNUM6:
		{
			if (EVENT_EDITBOX_CHANGE == nEvent) {//10000�̻� ���� ���ϵ��� ���������� �־����� ����. ���� �ʿ���� �� �ִ� ���� �ִ´�,
				//���� ���� ���� ����� �ִ� �ʿ� ������ ã�� �´�(�������� ��  �ִ� ����)
				TCHAR* MaxMatNum1 = m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX1)->GetText();
				TCHAR* MaxMatNum2 = m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX2)->GetText();
				TCHAR* MaxMatNum3 = m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX3)->GetText();
				TCHAR* MaxMatNum4 = m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX4)->GetText();
				TCHAR* MaxMatNum5 = m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX5)->GetText();
				TCHAR* MaxMatNum6 = m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX6)->GetText();
				//�ʿ��ִ밹���� ����� ���� �ʱ�ȭ
				SI16 NeedMaxItemNum1 = 0;
				SI16 NeedMaxItemNum2 = 0;
				SI16 NeedMaxItemNum3 = 0;
				SI16 NeedMaxItemNum4 = 0;
				SI16 NeedMaxItemNum5 = 0;
				SI16 NeedMaxItemNum6 = 0;
				//�ɸ��� ���̹Ƿ� ���������� ��ȯ�Ѵ�.
				NeedMaxItemNum1 = atoi(MaxMatNum1);
				NeedMaxItemNum2 = atoi(MaxMatNum2);
				NeedMaxItemNum3 = atoi(MaxMatNum3);
				NeedMaxItemNum4 = atoi(MaxMatNum4);
				NeedMaxItemNum5 = atoi(MaxMatNum5);
				NeedMaxItemNum6 = atoi(MaxMatNum6);
				//������ ���� ������ �����´�.
				TCHAR* Num1 = m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM1)->GetText();
				TCHAR* Num2 = m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM2)->GetText();
				TCHAR* Num3 = m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM3)->GetText();
				TCHAR* Num4 = m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM4)->GetText();
				TCHAR* Num5 = m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM5)->GetText();
				TCHAR* Num6 = m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM6)->GetText();
				//������������ ����� �ʱ�ȭ

				SI16 ItemNum1 = 0;
				SI16 ItemNum2 = 0;
				SI16 ItemNum3 = 0;
				SI16 ItemNum4 = 0;
				SI16 ItemNum5 = 0;			
				SI16 ItemNum6 = 0;	
				//������ ���� ��� ������ �ɸ��� ���̹Ƿ� ���������� ��ȯ
				ItemNum1 = atoi(Num1);
				ItemNum2 = atoi(Num2);
				ItemNum3 = atoi(Num3);
				ItemNum4 = atoi(Num4);
				ItemNum5 = atoi(Num5);
				ItemNum6 = atoi(Num6);
				//���� �κ��丮�� ������ �ִ� ������ ����
				SI16 MaxMatItemNum1 = matitemEndnum[0];
				SI16 MaxMatItemNum2 = matitemEndnum[1];
				SI16 MaxMatItemNum3 = matitemEndnum[2];
				SI16 MaxMatItemNum4 = matitemEndnum[3];
				SI16 MaxMatItemNum5 = matitemEndnum[4];
				SI16 MaxMatItemNum6 = matitemEndnum[5];
				//���� ���̹Ƿ� �ɸ��������� ��ȯ
				TCHAR LastTTputMatNum1[10] = "";
				TCHAR LastTTputMatNum2[10] = "";
				TCHAR LastTTputMatNum3[10] = "";
				TCHAR LastTTputMatNum4[10] = "";
				TCHAR LastTTputMatNum5[10] = "";
				TCHAR LastTTputMatNum6[10] = "";
				//���� �κ��丮�� ������ �ִ� �ִ� ����
				itoa(MaxMatItemNum1, LastTTputMatNum1, 10);
				itoa(MaxMatItemNum2, LastTTputMatNum2, 10);
				itoa(MaxMatItemNum3, LastTTputMatNum3, 10);
				itoa(MaxMatItemNum4, LastTTputMatNum4, 10);
				itoa(MaxMatItemNum5, LastTTputMatNum5, 10);
				itoa(MaxMatItemNum6, LastTTputMatNum6, 10);
                //����Ʈ ���ڿ� �����Ѵ�
				if (ItemNum1 >= NeedMaxItemNum1 
					&& MaxMatItemNum1<=NeedMaxItemNum1)	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM1)->SetText(LastTTputMatNum1);
				else if (ItemNum1 >= NeedMaxItemNum1 
					&& MaxMatItemNum1>NeedMaxItemNum1)	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM1)->SetText(MaxMatNum1);
				else if (ItemNum1 < NeedMaxItemNum1
					&& ItemNum1>= MaxMatItemNum1)		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM1)->SetText(LastTTputMatNum1);
				
				if (ItemNum2 >= NeedMaxItemNum2 
					&& MaxMatItemNum2<=NeedMaxItemNum2)	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM2)->SetText(LastTTputMatNum2);
				else if (ItemNum2 >= NeedMaxItemNum2 
					&& MaxMatItemNum2>NeedMaxItemNum2)	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM2)->SetText(MaxMatNum2);
				else if (ItemNum2 < NeedMaxItemNum2
					&& ItemNum2>= MaxMatItemNum2)		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM2)->SetText(LastTTputMatNum2);
				
				if (ItemNum3 >= NeedMaxItemNum3 
					&& MaxMatItemNum1<=NeedMaxItemNum1)	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM3)->SetText(LastTTputMatNum3);
				else if (ItemNum3 >= NeedMaxItemNum3 
					&& MaxMatItemNum3>NeedMaxItemNum3)	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM3)->SetText(MaxMatNum3);
				else if (ItemNum3 < NeedMaxItemNum3
					&& ItemNum3>= MaxMatItemNum3)		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM3)->SetText(LastTTputMatNum3);
				
				if (ItemNum4 >= NeedMaxItemNum4
					&& MaxMatItemNum4<=NeedMaxItemNum4)	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM4)->SetText(LastTTputMatNum4);
				else if (ItemNum4 >= NeedMaxItemNum4 
					&& MaxMatItemNum4>NeedMaxItemNum4)	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM4)->SetText(MaxMatNum4);
				else if (ItemNum4 < NeedMaxItemNum4
					&& ItemNum4>= MaxMatItemNum4)		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM4)->SetText(LastTTputMatNum4);
				
				if (ItemNum5 >= NeedMaxItemNum5
					&& MaxMatItemNum5<=NeedMaxItemNum5)	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM5)->SetText(LastTTputMatNum5);
				else if (ItemNum5 >= NeedMaxItemNum5 
					&& MaxMatItemNum5>NeedMaxItemNum5)	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM5)->SetText(MaxMatNum5);
				else if (ItemNum5 < NeedMaxItemNum5
					&& ItemNum5>= MaxMatItemNum5)		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM5)->SetText(LastTTputMatNum5);
				
				if (ItemNum6 >= NeedMaxItemNum6 
					&& MaxMatItemNum6<=NeedMaxItemNum6)	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM6)->SetText(LastTTputMatNum6);
				else if (ItemNum6 >= NeedMaxItemNum6 
					&& MaxMatItemNum6>NeedMaxItemNum6)	m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM6)->SetText(MaxMatNum6);
				else if (ItemNum6 < NeedMaxItemNum6
					&& ItemNum6>= MaxMatItemNum6)		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM6)->SetText(LastTTputMatNum6);
			}
		}
		break;
	case NCHRISTMASEVENT_BUTTON_DONATIONOFMATERIAL://��� �ֱ� ��ư.
		{
			if (EVENT_BUTTON_CLICKED == nEvent)
			{
				//���� ���� ����� ��� ���.
				// [���] ConstructType�� ����Ʈ���̸� �ֹο��� �����Ѵ�. (09.10.23)
				if(EventTreeType != EVENT_STRUCTURE_WORLDCHRISTMASTREE)
				{
					if(pclClient->pclCM->CR[1]->GetCurrentVillageUnique() != pclClient->pclCM->CR[1]->pclCI->clBI.siHomeVillage)
					{
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_EXPLAIN)->SetText(GetTxtFromMgr(8464));
						return;
					}
				}

				//������ ��� 6���� �޵��� �Ͽ���.���� ���Ը� �ø��� MAX_MATERIAL_NUMBER�� �÷� �����ٸ� 
				//�ٸ� �̺�Ʈ�μ� �̿뵵 �����ϴ�.
				SI16	slot1 =_tstoi( m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM1)->GetText());//TCHAR* ���� 16���� �����´�
				SI16	slot2 =_tstoi( m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM2)->GetText());//���� �̺��丮�� ������ �ִ� ����
				SI16	slot3 =_tstoi( m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM3)->GetText());
				SI16	slot4 =_tstoi( m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM4)->GetText());
				SI16	slot5 =_tstoi( m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM5)->GetText());
				SI16	slot6 =_tstoi( m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM6)->GetText());
				if (slot1 == 0 && slot2 == 0 && slot3 == 0 && slot4 == 0 && slot5 == 0 && slot6 == 0) {
					cltClient *pclclient = (cltClient *)pclClient;
					TCHAR* pText;
					TCHAR* pTitle;
					pText = GetTxtFromMgr(7700);//��� ���� 0�̰ų� ���ڸ��� ������ ������ ����
					pTitle = GetTxtFromMgr(7651);//��� ���� 0�̰ų� ���ڸ��� ������ ������ ����
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);
					DeleteDialog();
					break;
				}
				SI16	itemnum[MAX_MATERIAL_NUMBER] = {slot1,slot2,slot3,slot4,slot5,slot6, 0};//������ 6�������� �������� ���� ���Ը� �ø����.

				// [���] ���縮���� ���� Ʈ���� ��쿡�� ��������ũ ���� ��Ḧ �ִ´�.
				if(EventTreeType == EVENT_STRUCTURE_WORLDCHRISTMASTREE)
				{
					//��Ḧ ������
					cltGameMsgRequest_Event_InsertMaterial clMaterial(VILLAGE_NONE, EventTreeType, matitemunique, itemnum, NULL);
					cltMsg clMaterialMsg(GAMEMSG_REQUEST_EVENT_INSERTMATERIAL,sizeof(cltGameMsgRequest_Event_InsertMaterial), (BYTE*)&clMaterial);
					pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMaterialMsg);
				}
				else
				{
					//��Ḧ ������
					cltGameMsgRequest_Event_InsertMaterial clMaterial(siVillageUnique, EventTreeType, matitemunique, itemnum, NULL);
					cltMsg clMaterialMsg(GAMEMSG_REQUEST_EVENT_INSERTMATERIAL,sizeof(cltGameMsgRequest_Event_InsertMaterial), (BYTE*)&clMaterial);
					pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMaterialMsg);
				}


				DeleteDialog();
			}
		}
		break;
	case NCHRISTMASEVENT_BUTTON_MAKETREE :// ũ�������� Ʈ�� ����� ��ư�� ������
		{
			if (EVENT_BUTTON_CLICKED == nEvent)
			{
				// �ڽ��� (��)����� �̹� ��ϵǾ� �־��  �Ѵ�. 
				{
					cltSimpleRank clrank(pclClient->pclCM->CR[1]->pclCI->clCharRank.siType ,siVillageUnique);

					if (pclClient->pclCM->CR[1]->pclCI->clCharRank.siType == 1 &&
						pclClient->pclCM->CR[1]->pclCI->clCharRank.IsSame(&clrank) == TRUE) 
					{
						cltGameMsgRequest_Event_MaterialComplete cllChangeTree( siVillageUnique, EventTreeType );//ũ�������� Ʈ�� ���� �޼����� ������. 
						cltMsg clChangetreeMsg( GAMEMSG_REQUEST_EVENT_MATERIALCOMPLETE, sizeof(cltGameMsgRequest_Event_MaterialComplete), (BYTE*)&cllChangeTree );
						pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clChangetreeMsg);
					}
					else
					{
						TCHAR* pText;
						pText = GetTxtFromMgr(7658);
						m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_EXPLAIN)->SetText(pText);				
						return;
					}
				}
				//DoMsg_GAMEMSG_REQUEST_EVENT_MATERIALCOMPLETE ��Ŷ�� ��� �Ѵ�.
				//ũ�������� Ʈ�� ����� �̺�Ʈ �ϼ� �������� ������ �� ��Ŷ �̿��Ѵ�.
				//SI32 PineTreeKind = pclClient->GetUniqueFromHash(TEXT("KIND_PINE_TREE"));//������ ������ ����
				//SI32 ChristmastreeKind = pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE"));//ũ�������� Ʈ�� ī�ε� ã��.
				//�̰ɷ� ������ �ϸ� �ɵ� EVENT_STRUCTURE_TREE, EVENT_STRUCTURE_CHRISTMASTREE
				//�ϼ� �ߴٰ� Ʈ������ �޼����� ������.				
				/*������ �����ڴ� ��Ŷ�� ������� ���̾�α׸� ������� �Ѵ�. �׽�Ʈ �ÿ��� �ּ����� ó���ϰ�
				���� �������� Ǯ� ��������.*/
				DeleteDialog();
			}
		}
		break;
	case NCHRISTMASEVENT_BUTTON_HAVEITEM :// ũ�������� Ʈ�� ��ư��  ������� �������� �޴� ��ư�� ��������.
		{
			if (EVENT_BUTTON_CLICKED == nEvent)
			{
				//�����ۺ���� �˻�
				SI16 i;
				cltItem clitem;
				SI32 rtnvalue;
				if(pclClient->pclCM->CR[1]->pclCI->clCharItem.CanAddInv(pclClient->pclItemManager, INVMODE_ALL,
						&pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[0], NULL, &i, &clitem, &rtnvalue)== false)
				{//�κ��丮�� ������ ���� �ڸ��� ���ٰ� ǥ��
					TCHAR* pTitle = GetTxtFromMgr(422);
					TCHAR* pText = GetTxtFromMgr(6981);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
					DeleteDialog();
				}

				//DoMsg_GAMEMSG_REQUEST_EVENT_MATERIALCOMPLETE ��Ŷ�� ��� �Ѵ�.
				//ũ�������� Ʈ�� ����� �̺�Ʈ �ϼ� �������� ������ �� ��Ŷ �̿��Ѵ�.
				//SI32 PineTreeKind = pclClient->GetUniqueFromHash(TEXT("KIND_PINE_TREE"));//������ ������ ����
				//SI32 ChristmastreeKind = pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE"));//ũ�������� Ʈ�� ī�ε� ã��.
				//�̰ɷ� ������ �ϸ� �ɵ� EVENT_STRUCTURE_TREE, EVENT_STRUCTURE_CHRISTMASTREE
				//�ϼ� �ߴٰ� Ʈ������ �޼����� ������.
				cltGameMsgRequest_Event_MaterialComplete cllChangeTree( siVillageUnique,EventTreeType/*EVENT_STRUCTURE_TREE*/ );//ũ�������� Ʈ�� ���� �޼����� ������. 
				cltMsg clHAveItemMsg( GAMEMSG_REQUEST_EVENT_MATERIALCOMPLETE, sizeof(cltGameMsgRequest_Event_MaterialComplete), (BYTE*)&cllChangeTree );
				pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clHAveItemMsg);
				/*������ �����ڴ� ��Ŷ�� ������� ���̾�α׸� ������� �Ѵ�. �׽�Ʈ �ÿ��� �ּ����� ó���ϰ�
				���� �������� Ǯ� ��������.*/
				DeleteDialog();
			}
		}
		break;
	}
}
void NChristmasEventDlg::changeEditbox(SI16 *itemUnique, SI16* sitemNum, SI16 m_siConstructType)
{
	cltClient *pclclient = (cltClient *)pclClient;
	cltEventStructureUnit* pEventPine = pclClient->pclEventStructure->GetEventStructure(m_siConstructType);
	cltEventStructureUnit* pEventChrisrmas = pclClient->pclEventStructure->GetEventStructure(m_siConstructType);
	SI32 id =pclclient->pclUnderMouseObject->GetUnderMouseID();//���콺 �Ʒ� �ִ� �� ī�ε尪�� ���� �´�.
	if (   m_siConstructType == EVENT_STRUCTURE_TREE 
		|| m_siConstructType == EVENT_STRUCTURE_HERO_BRONZE 
		|| m_siConstructType == EVENT_STRUCTURE_HALLOWEEN
		|| m_siConstructType == EVENT_STRUCTURE_CHRISTMASTREEBASE
		|| m_siConstructType == EVENT_STRUCTURE_NEWYEARTREEBASE) 
	{
		//�ϴ��� �밡�ٷ�..������...
		TCHAR Incomeitem1[10] = "" ;
		TCHAR Incomeitem2[10] = "" ;
		TCHAR Incomeitem3[10] = "" ;
		TCHAR Incomeitem4[10] = "" ;
		TCHAR Incomeitem5[10] = "" ;
		TCHAR Incomeitem6[10] = "" ;

		SI16 ItemNum1 = matitemnum[0]-sitemNum[0];
		SI16 ItemNum2 = matitemnum[1]-sitemNum[1];
		SI16 ItemNum3 = matitemnum[2]-sitemNum[2];
		SI16 ItemNum4 = matitemnum[3]-sitemNum[3];
		SI16 ItemNum5 = matitemnum[4]-sitemNum[4];
		SI16 ItemNum6 = matitemnum[5]-sitemNum[5];

		if (ItemNum1 <= 0)	ItemNum1 = 0;
		if (ItemNum2 <= 0)	ItemNum2 = 0;
		if (ItemNum3 <= 0)	ItemNum3 = 0;
		if (ItemNum4 <= 0)	ItemNum4 = 0;
		if (ItemNum5 <= 0)	ItemNum5 = 0;
		if (ItemNum6 <= 0)	ItemNum6 = 0;

		if(ItemNum1 == 0 && ItemNum2 == 0 && ItemNum3 == 0 && ItemNum4 == 0 && ItemNum5 == 0 && ItemNum6 == 0)
		{
			m_InterfaceFactory.GetButton(NCHRISTMASEVENT_BUTTON_MAKETREE)->Enable(true);//���������� �� ���� 0�� �Ǹ� Ȱ��ȭ ��Ų��
		}

		// ���� ä���� �ִ� ����
		itoa(ItemNum1,Incomeitem1 ,10);
		itoa(ItemNum2,Incomeitem2 ,10);
		itoa(ItemNum3,Incomeitem3 ,10);
		itoa(ItemNum4,Incomeitem4 ,10);
		itoa(ItemNum5,Incomeitem5 ,10);
		itoa(ItemNum6,Incomeitem6 ,10);

		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX1)->SetText(Incomeitem1);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX2)->SetText(Incomeitem2);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX3)->SetText(Incomeitem3);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX4)->SetText(Incomeitem4);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX5)->SetText(Incomeitem5);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX6)->SetText(Incomeitem6);

		// ������ ���� ����
		if(ItemNum1 > matitemEndnum[0])		ItemNum1 = matitemEndnum[0];
		if(ItemNum2 > matitemEndnum[1])		ItemNum2 = matitemEndnum[1];
		if(ItemNum3 > matitemEndnum[2])		ItemNum3 = matitemEndnum[2];
		if(ItemNum4 > matitemEndnum[3])		ItemNum4 = matitemEndnum[3];
		if(ItemNum5 > matitemEndnum[4])		ItemNum5 = matitemEndnum[4];
		if(ItemNum6 > matitemEndnum[5])		ItemNum6 = matitemEndnum[5];

		itoa(ItemNum1,Incomeitem1 ,10);
		itoa(ItemNum2,Incomeitem2 ,10);
		itoa(ItemNum3,Incomeitem3 ,10);
		itoa(ItemNum4,Incomeitem4 ,10);
		itoa(ItemNum5,Incomeitem5 ,10);
		itoa(ItemNum6,Incomeitem6 ,10);

		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM1)->SetText(Incomeitem1);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM2)->SetText(Incomeitem2);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM3)->SetText(Incomeitem3);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM4)->SetText(Incomeitem4);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM5)->SetText(Incomeitem5);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM6)->SetText(Incomeitem6);

		return;
	}
	else if(m_siConstructType == EVENT_STRUCTURE_WORLDCHRISTMASTREE)
	{
		TCHAR Incomeitem1[10] = "" ;
		TCHAR Incomeitem2[10] = "" ;
		TCHAR Incomeitem3[10] = "" ;
		TCHAR Incomeitem4[10] = "" ;
		TCHAR Incomeitem5[10] = "" ;
		TCHAR Incomeitem6[10] = "" ;

		SI16 ItemNum1 = matitemnum[0]-sitemNum[0];
		SI16 ItemNum2 = matitemnum[1]-sitemNum[1];
		SI16 ItemNum3 = matitemnum[2]-sitemNum[2];
		SI16 ItemNum4 = matitemnum[3]-sitemNum[3];
		SI16 ItemNum5 = matitemnum[4]-sitemNum[4];
		SI16 ItemNum6 = matitemnum[5]-sitemNum[5];

		if (ItemNum1 <= 0)	ItemNum1 = 0;
		if (ItemNum2 <= 0)	ItemNum2 = 0;
		if (ItemNum3 <= 0)	ItemNum3 = 0;
		if (ItemNum4 <= 0)	ItemNum4 = 0;
		if (ItemNum5 <= 0)	ItemNum5 = 0;
		if (ItemNum6 <= 0)	ItemNum6 = 0;

		// ���� ä���� �ִ� ����
		itoa(ItemNum1,Incomeitem1 ,10);
		itoa(ItemNum2,Incomeitem2 ,10);
		itoa(ItemNum3,Incomeitem3 ,10);
		itoa(ItemNum4,Incomeitem4 ,10);
		itoa(ItemNum5,Incomeitem5 ,10);
		itoa(ItemNum6,Incomeitem6 ,10);

		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX1)->SetText(Incomeitem1);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX2)->SetText(Incomeitem2);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX3)->SetText(Incomeitem3);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX4)->SetText(Incomeitem4);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX5)->SetText(Incomeitem5);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMAX6)->SetText(Incomeitem6);

		// ������ ���� ����
		if(ItemNum1 > matitemEndnum[0])		ItemNum1 = matitemEndnum[0];
		if(ItemNum2 > matitemEndnum[1])		ItemNum2 = matitemEndnum[1];
		if(ItemNum3 > matitemEndnum[2])		ItemNum3 = matitemEndnum[2];
		if(ItemNum4 > matitemEndnum[3])		ItemNum4 = matitemEndnum[3];
		if(ItemNum5 > matitemEndnum[4])		ItemNum5 = matitemEndnum[4];
		if(ItemNum6 > matitemEndnum[5])		ItemNum6 = matitemEndnum[5];

		itoa(ItemNum1,Incomeitem1 ,10);
		itoa(ItemNum2,Incomeitem2 ,10);
		itoa(ItemNum3,Incomeitem3 ,10);
		itoa(ItemNum4,Incomeitem4 ,10);
		itoa(ItemNum5,Incomeitem5 ,10);
		itoa(ItemNum6,Incomeitem6 ,10);

		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM1)->SetText(Incomeitem1);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM2)->SetText(Incomeitem2);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM3)->SetText(Incomeitem3);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM4)->SetText(Incomeitem4);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM5)->SetText(Incomeitem5);
		m_InterfaceFactory.GetEdit(NCHRISTMASEVENT_EDIT_ITEMMNUM6)->SetText(Incomeitem6);

		return;
	}
}