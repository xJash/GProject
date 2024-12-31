/*
//---------------------------------
// 2004/2/10 ���°�
//---------------------------------
#include "CommonLogic.h"
#include "..\..\Client\Client.h"

#include "School.h"
#include "Char\CharManager\CharManager.h"

#include "..\..\Resource.h"
#include "MsgType-Person.h"

extern cltCommonLogic* pclClient;

// ��ü �̸��� ���Ѵ�. 
bool cltSchool::GetFullName(cltSchoolManager* pchoolmanager, char* pname)
{
	sprintf(pname, "%s %s%s", pchoolmanager->clSchoolArea[siAreaCode].szName, szName, pchoolmanager->clSchoolGrade[ siGradeCode ].szName) ;

	return true;
}

cltSchoolManager::cltSchoolManager()
{
	m_hDlg	= NULL;					// ������ ����. 

	bDlgRectInitSwitch	= false;

	siCurrentSchoolArea		= 0;
	siCurrentSchoolGrade	= 0;

	siSchoolIndex		= 0;

	siCurrentSchoolUnique	= -1;
	bShowUserNumSwitch		= false;
	siUserNum				= 0;

	//-----------------------------
	// �б� ����� ����Ѵ�. 
	//-----------------------------
	cltSchoolGrade* pclgrade;

	char* pText = GetTxtFromMgr(3102);
	pclgrade = new cltSchoolGrade(pText);
	AddGrade(SCHOOLGRADE_PRI,	pclgrade);
	delete pclgrade;

	pText = GetTxtFromMgr(3103);
	pclgrade = new cltSchoolGrade(pText);
	AddGrade(SCHOOLGRADE_MID,	pclgrade);
	delete pclgrade;

	pText = GetTxtFromMgr(3104);
	pclgrade = new cltSchoolGrade(pText);
	AddGrade(SCHOOLGRADE_HIG,	pclgrade);
	delete pclgrade;

	pText = GetTxtFromMgr(3105);
	pclgrade = new cltSchoolGrade(pText);
	AddGrade(SCHOOLGRADE_UNV,	pclgrade);
	delete pclgrade;

	pclgrade = new cltSchoolGrade("Secondary");
	AddGrade(SCHOOLGRADE_SECON,	pclgrade);
	delete pclgrade;

	pclgrade = new cltSchoolGrade("InternationalSchool");
	AddGrade(SCHOOLGRADE_INTER,	pclgrade);
	delete pclgrade;

	pclgrade = new cltSchoolGrade("HighSchool");
	AddGrade(SCHOOLGRADE_HIGH,	pclgrade);
	delete pclgrade;

	//-----------------------------
	//�б� ������ ����Ѵ�. 
	//-----------------------------
	cltSchoolArea* pclarea;

	pText = GetTxtFromMgr(3106);
	pclarea = new cltSchoolArea(pText);  //����
	AddArea(SCHOOLAREA_SEOUL,	pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3107);
	pclarea = new cltSchoolArea(pText); //������
	AddArea(SCHOOLAREA_KANGWON, pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3108);
	pclarea = new cltSchoolArea(pText);//���ϵ�
	AddArea(SCHOOLAREA_KYOUNGBOOK, pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3109);
	pclarea = new cltSchoolArea(pText); // ����
	AddArea(SCHOOLAREA_KWANGJU, pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3110);
	pclarea = new cltSchoolArea(pText); //�뱸
	AddArea(SCHOOLAREA_DAIGU, pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3111);
	pclarea = new cltSchoolArea(pText); //�λ�
	AddArea(SCHOOLAREA_BOOSAN, pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3112);
	pclarea = new cltSchoolArea(pText); //���󳲵�
	AddArea(SCHOOLAREA_JOUNNAM, pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3113);
	pclarea = new cltSchoolArea(pText);  //��û�ϵ�
	AddArea(SCHOOLAREA_CHOONGBOOK, pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3114);
	pclarea = new cltSchoolArea(pText); //��⵵
	AddArea(SCHOOLAREA_KYOUNGKI, pclarea);
	delete pclarea;
	
	pText = GetTxtFromMgr(3115);
	pclarea = new cltSchoolArea(pText); //��󳲵�
	AddArea(SCHOOLAREA_KYOUNGNAM, pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3116);
	pclarea = new cltSchoolArea(pText);  //�߱�
	AddArea(SCHOOLAREA_CHINA, pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3117);
	pclarea = new cltSchoolArea(pText);  //���
	AddArea(SCHOOLAREA_WOOLSAN, pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3118);
	pclarea = new cltSchoolArea(pText); //��û����
	AddArea(SCHOOLAREA_CHOONGNAM, pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3119);
	pclarea = new cltSchoolArea(pText); //����ϵ�
	AddArea(SCHOOLAREA_JOUNBOOK, pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3120);
	pclarea = new cltSchoolArea(pText);   //��õ
	AddArea(SCHOOLAREA_INCHEON, pclarea);
	delete pclarea;
	
	pText = GetTxtFromMgr(3121);
	pclarea = new cltSchoolArea(pText);  //���ֵ�
	AddArea(SCHOOLAREA_ZEJU, pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3122);
	pclarea = new cltSchoolArea(pText);   //����
	AddArea(SCHOOLAREA_DAIJEON, pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3123);
	pclarea = new cltSchoolArea(pText);  //����
	AddArea(SCHOOLAREA_WONJU,pclarea);
	delete pclarea;
	
	pText = GetTxtFromMgr(3124);
	pclarea = new cltSchoolArea(pText);  //ĳ����
	AddArea(SCHOOLAREA_CANADA,pclarea);
	delete pclarea;
	
	pText = GetTxtFromMgr(3125);
	pclarea = new cltSchoolArea(pText);  //õ��
	AddArea(SCHOOLAREA_CHEONAN,pclarea); 
	delete pclarea;

	pText = GetTxtFromMgr(3126);
	pclarea = new cltSchoolArea(pText); //�̰�����
	AddArea(SCHOOLAREA_SINGAPORE,pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3127);
	pclarea = new cltSchoolArea(pText); //��������
	AddArea(SCHOOLAREA_NEWZEALAND,pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3128);
	pclarea = new cltSchoolArea(pText);  //�̱�
	AddArea(SCHOOLAREA_USA,pclarea);
	delete pclarea;

	pText = GetTxtFromMgr(3129);
	pclarea = new cltSchoolArea(pText); //��õ
	AddArea(SCHOOLAREA_CHUNCHEON,pclarea);
	delete pclarea;

	//----------------------------
	// �б��� ����Ѵ�. 
	//----------------------------
//	SetSchoolList();



}

cltSchoolManager::~cltSchoolManager()
{

}

// ����ũ�� �ٰŷ� ref�� ���Ѵ�. 
SI32 cltSchoolManager::GetRefFromUnique(SI32 unique)
{
	SI32 i;

	for(i = 0;i < siSchoolIndex;i++)
	{
		if(clSchool[i].siUnique == unique)return i;
	}
	return -1;
}

// �б������ ����Ѵ�. 
bool cltSchoolManager::AddGrade(SI32 areacode, cltSchoolGrade* pclgrade)
{
	clSchoolGrade[areacode].Set(pclgrade);
	return true;
}

// ��޸��� �ٰŷ� ��� �ڵ带 ��´�. 
SI32 cltSchoolManager::GetGradeCode(char* pname)
{
	SI32 i;

	for(i = 0;i < MAX_SCHOOL_GRADE;i++)
	{
		if(strcmp(clSchoolGrade[i].szName, pname) == 0)
		{
			return i;
		}
	}

	return 0;
}

// �б������� ����Ѵ�. 
bool cltSchoolManager::AddArea(SI32 areacode, cltSchoolArea* pclarea)
{
	clSchoolArea[areacode].Set(pclarea);
	return true;
}

// �������� �ٰŷ� ���� �ڵ带 ��´�. 
SI32 cltSchoolManager::GetAreaCode(char* pname)
{
	SI32 i;

	for(i = 0;i < MAX_SCHOOL_AREA;i++)
	{
		if(strcmp(clSchoolArea[i].szName, pname) == 0)
		{
			return i;
		}
	}

	return 0;
}

// �б��� ����Ѵ�. 
bool cltSchoolManager::Add(cltSchool* pclschool)
{
	if(siSchoolIndex >= MAX_SCHOOL_NUMBER)return false;

	clSchool[siSchoolIndex].Set(pclschool);
	siSchoolIndex++;

	return true;

}


BOOL cltSchoolManager::CreateDlg(HINSTANCE hinst, HWND hwnd)
{
	// ��ȭ���ڰ� ���� ���¶�� �����. 
	if(!IsWindow(m_hDlg))
	{

		m_hDlg = CreateDialog(hinst, MAKEINTRESOURCE(IDD_DIALOG_SCHOOL), hwnd, StaticDlgProc);

		if(bDlgRectInitSwitch == true)
		{
			MoveWindow(m_hDlg, 
				DlgRect.left, DlgRect.top, 
				DlgRect.right - DlgRect.left, 
				DlgRect.bottom - DlgRect.top, FALSE);
		}

		ShowWindow(m_hDlg, SW_SHOW);

		return TRUE;
	}
	else
	{
		DestroyWindow(m_hDlg);
	}


	return 0;
}

BOOL CALLBACK cltSchoolManager::StaticDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	return pclClient->pclSchoolManager->DlgProc(hDlg, iMsg, wParam, lParam);
}

//�б������ �����ش�.  
void cltSchoolManager::ShowSchoolList()
{
	SI32 i;
	char buffer[256] ="";

	// ������ ����Ʈ�� �����Ѵ�. 
	ListDelete(m_hDlg, IDC_LIST_SCHOOL);

	for(i = 0;i < siSchoolIndex;i++)
	{
		if(siCurrentSchoolArea	 && clSchool[i].siAreaCode != siCurrentSchoolArea)continue;
		if(siCurrentSchoolGrade  && clSchool[i].siGradeCode != siCurrentSchoolGrade)continue;
		
		sprintf(buffer, "[%s %s]", clSchool[i].szName, clSchoolGrade[ clSchool[i].siGradeCode ].szName) ;
		
		//clSchool[i]->GetFullName();

		SI32 index = ListAddString(m_hDlg, IDC_LIST_SCHOOL, (LPARAM)buffer);
		
		// ����Ʈ �׸� �����͸� �����Ѵ�. 
		ListSetItemData(m_hDlg, IDC_LIST_SCHOOL, index, (LPARAM)clSchool[i].siUnique);
	}

}


BOOL CALLBACK cltSchoolManager::DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	SI32 i;
	SI32 id = 1;
	static SI32 siLastUpdateSchoolUnique = -1;

	switch(iMsg)
	{
	case WM_INITDIALOG:
		{
			siCurrentSchoolArea		= 0;
			siCurrentSchoolGrade	= 0;

			// �������� ����Ѵ�. 
			for(i = 0;i < MAX_SCHOOL_AREA;i++)
			{
				if(strcmp(clSchoolArea[i].szName, "") == 0)continue;

				ComboAddString(hDlg, IDC_COMBO_SCHOOLAREA, (LPARAM)clSchoolArea[i].szName);
			}

			// ����� ����Ѵ�. 
			for(i = 0;i < MAX_SCHOOL_GRADE;i++)
			{
				if(strcmp(clSchoolGrade[i].szName, "") == 0)continue;

				ComboAddString(hDlg, IDC_COMBO_SCHOOL_GRADE, (LPARAM)clSchoolGrade[i].szName);
			}

			SetTimer(hDlg, 1, 1000, NULL);
		}
		return TRUE;

	case WM_NOTIFY:
		return TRUE;

	case WM_TIMER:
		{
			// ������ �б� ����� ���� ��û�Ѵ�. 
			if(siCurrentSchoolUnique > 0)
			{
				if(siCurrentSchoolUnique != siLastUpdateSchoolUnique)
				{
					siLastUpdateSchoolUnique = siCurrentSchoolUnique;
					
					cltGameMsgRequest_SchoolUserNum clinfo(siCurrentSchoolUnique);
					cltMsg clMsg(GAMEMSG_REQUEST_SCHOOLUSERNUM, sizeof(clinfo), (BYTE*)&clinfo);
					pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
				}
			}
		
			if(bShowUserNumSwitch)
			{
				bShowUserNumSwitch = false;
				
				char buffer[256];
				sprintf(buffer, "%d", siUserNum);
				SetDlgItemText(hDlg, IDC_EDIT_SCHOOLUSERNUM, buffer);
				
			}
		}
		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_LIST_SCHOOL:
			switch(HIWORD(wParam))
			{
			case LBN_SELCHANGE:
				// ���� ���õ� �б���  Ȯ���Ѵ�. 
				SI32 index = ListGetCurrentSel(hDlg, IDC_LIST_SCHOOL);
				if(index < 0)break;
				
				siCurrentSchoolUnique = SendDlgItemMessage(hDlg, IDC_LIST_SCHOOL, LB_GETITEMDATA,	index, 0);
				
				if(siCurrentSchoolUnique > 0)
				{
					// �б� �ΰ� �׸���. 
					DrawLogo(siCurrentSchoolUnique);
				}
				break;
			}
			return TRUE;
		case IDC_COMBO_SCHOOLAREA:
			{
				switch(HIWORD(wParam))
				{
				case CBN_SELCHANGE:
					{
						
						char szarea[128] = "NULL";
						ComboGetString(hDlg, IDC_COMBO_SCHOOLAREA, (LPARAM)szarea);
						
						siCurrentSchoolArea	= GetAreaCode(szarea);

						//�б������ �����ش�.  
						ShowSchoolList();
						
					}
					break;
				}
			}
			return TRUE;

		case IDC_COMBO_SCHOOL_GRADE:
			{
				switch(HIWORD(wParam))
				{
				case CBN_SELCHANGE:
					{
						
						char szgrade[128] = "NULL";
						ComboGetString(hDlg, IDC_COMBO_SCHOOL_GRADE, (LPARAM)szgrade);
						
						siCurrentSchoolGrade	= GetGradeCode(szgrade);

						//�б������ �����ش�.  
						ShowSchoolList();
						
					}
					break;
				}
			}
			return TRUE;

		case IDC_BUTTON_CANCELSCHOOL:
			{
				if(pclClient->pclCM->CR[1]->pclCI->clBI.siSchoolUnique <= 0)
				{
					char* pTitle = GetTxtFromMgr(3131);
					char* pText = GetTxtFromMgr(3132);

					MsgBox(pTitle, pText);
					break;
				}

				char* pTitle = GetTxtFromMgr(3134);
				char* pText = GetTxtFromMgr(3133);


				if(MessageBox(hDlg, pText, pTitle, MB_ICONQUESTION | MB_YESNO) == IDYES)
				{
					// ������ �б� �������� ���� ��û�Ѵ�. 
					cltGameMsgRequest_SetSchool clinfo(0);
					cltMsg clMsg(GAMEMSG_REQUEST_SETSCHOOL, sizeof(clinfo), (BYTE*)&clinfo);
					pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
				}

			}
			return TRUE;

		
		case IDOK:
			{
				// ���� ���õ� �б���  Ȯ���Ѵ�. 
				SI32 index = ListGetCurrentSel(hDlg, IDC_LIST_SCHOOL);
				if(index < 0)break;

				SI32 schoolunique = SendDlgItemMessage(hDlg, IDC_LIST_SCHOOL, LB_GETITEMDATA,	index, 0);
				if(schoolunique <= 0)break;

				char* pTitle = GetTxtFromMgr(3136);
				char* pText = GetTxtFromMgr(3135);

				if(MessageBox(hDlg, pText, pTitle, MB_ICONQUESTION | MB_YESNO) == IDYES)
				{
					
					// ������ �б���  ����� ���� ��û�Ѵ�. 
					cltGameMsgRequest_SetSchool clinfo(schoolunique);
					cltMsg clMsg(GAMEMSG_REQUEST_SETSCHOOL, sizeof(clinfo), (BYTE*)&clinfo);
					pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
				}

				
			}
			return TRUE;
			
		case IDCANCEL:
			DestroyWindow(m_hDlg);
			return TRUE;
			
			
	}
	return TRUE;
	
	case WM_DESTROY:
		// Ÿ�̸Ӹ� �����Ѵ�. 
		KillTimer(hDlg, 1);

		// �������� ��ġ�� ����Ѵ�. 
		GetWindowRect(hDlg, &DlgRect);
		bDlgRectInitSwitch = true;

		m_hDlg = NULL;
		return TRUE;

	}

	return FALSE;
}


// �б� ����Ʈ�� ����Ѵ�. 
void cltSchoolManager::SetSchoolList()
{
	SI32 i;
	char buffer[1024];

	FILE* fp;

	fp = fopen("School\\School.txt", "rt");

	if(fp == NULL)
	{
		MsgBox("fds982jf", "fdsf932:%s", "School.txt");
		return ;
	}

	// 6�� �ǳʶ��. 
	for(i = 0;i < 6;i++)
	{
		fgets(buffer, 1024, fp);
	}


	SI32 unique;
	SI32 file;
	SI32 icon;
	char area[128];
	char grade[128];
	char name[128];

	cltSchool* pclschool;

	while( fgets(buffer, 1024, fp) != NULL)
	{
		sscanf(buffer, "%d %s %s %s %d %d", &unique, area, grade, name, &file, &icon);

		// ���� �ؽ�Ʈ�� ������� ���� �ڵ带 ���´�. 
		SI32 areacode = GetAreaCode(area);
		if(areacode <= 0)
		{
			MsgBox("AreaCode", "%s", area);
			return ;
		}

		SI32 gradecode = GetGradeCode(grade);
		if(gradecode <= 0)
		{
			MsgBox("GradeCode", "%s", grade);
			return ;
		}
		pclschool = new cltSchool(unique, areacode, gradecode, name, file, icon);
		Add(pclschool);
		delete pclschool;
	
	}	

	fclose(fp);

}

// �б� �ΰ� ����Ѵ�. 
void cltSchoolManager::DrawLogo(SI32 schoolunique)
{

	cltClient* pclclient = (cltClient*)pclClient;
	LPDIRECTDRAWSURFACE7 psurface = pclclient->lpBackScreen;

	// �ΰ� ���ǽ��� ����Ѵ�. 
	SI32 ref	= GetRefFromUnique(schoolunique);
	if(ref < 0)return ;
	

	SI32 file		= clSchool[ref].siFile;
	TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_SCHOOL1 + file);

	if(pspr == NULL)return ;


	SI32 icon	= clSchool[ref].siIconIndex;

	if(GP.LockSurface(psurface) == TRUE)
	{
		GP.PutSpr(pspr, 0, 0, clSchool[icon].siIconIndex);

		GP.UnlockSurface(psurface);
	}

	//----------------------------------------------
	// �׷��� �̹����� ���̾�α� �ڽ��� �ű��. 
	//----------------------------------------------
	HWND hwnd = GetDlgItem(m_hDlg, IDC_STATIC_SCHOOLLOGO);

	RECT rect;
	RECT rect2;
	GetClientRect( hwnd, &rect );
	rect2 = rect;
	
	// ���� Ŭ���̾�Ʈ ��ǥ 2���� ��ũ�� ��ǥ�� �����Ѵ�.
	ClientToScreen( hwnd, (POINT*)&rect );
	ClientToScreen( hwnd, (POINT*)&rect + 1);

	HDC srchdc;
	HDC desthdc = GetDC(hwnd);
	if(desthdc )
	{
		if(psurface->GetDC(&srchdc) == DD_OK)
		{
			
			BitBlt(desthdc, 0, 0, 
				pspr->GetXSize(), pspr->GetYSize(),
				srchdc, 0, 0, SRCCOPY);

			psurface->ReleaseDC(srchdc);
			
		}
		
		ReleaseDC(hwnd, desthdc);
	}

}
*/