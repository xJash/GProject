#include "stdafx.h"
#include "VillageManager.h"
#define MAX_VILLAGE_COUNT 100
#define MAX_ITEM_FILE 100


CVillageManager::CVillageManager()
{
	strcpy(village_name,"");

}


CVillageManager::~CVillageManager()
{
	strcpy(village_name,"");

}



char* CVillageManager::Set(char *VillageUnique)
{
	FindVillage(VillageUnique);
	return village_name;	
    
}

void CVillageManager::FindVillage(char *VillageUnique)
{
	char buffer[256]="";

	BYTE	szGoonzuPath[MAX_PATH] = "";
	char	szVillageInfo[512] = "";
	DWORD	dwSize = sizeof(szGoonzuPath);
	HKEY	hKey;
	LONG	lReturn;
	CString	szError;

	lReturn = RegOpenKey(HKEY_CURRENT_USER, "Software\\Intizen\\Goonzu", &hKey);
	if(lReturn != ERROR_SUCCESS)
	{
		szError.Find("������Ʈ���� �� �� �����ϴ�\nErrorCode : %d", lReturn);
		AfxMessageBox(szError);
		return;
	}
	lReturn = RegQueryValueEx(hKey, "PATH", NULL, NULL, szGoonzuPath, &dwSize);
	if(lReturn != ERROR_SUCCESS)
	{
		szError.Find("���ְ� ��ġ�� ������ ã�� �� �����ϴ�\nErrorCode : %d", lReturn);
		AfxMessageBox(szError);
		return;
	}

	RegCloseKey(hKey);

	sprintf(szVillageInfo, "%sVillage\\VillageInfo.txt", szGoonzuPath);

	FILE* fp = fopen(szVillageInfo, "rt");

	if(fp == NULL)
	{
		AfxMessageBox( buffer);		
		return ;
	}

	// 5���� �����Ѵ�.
	for(int i = 0;i < 6;i++)
		fgets(buffer, 1024, fp);


	i=0;
	while( fgets(buffer, 1024, fp) != NULL)
	{
		if ( i >= MAX_VILLAGE_COUNT ) break ;

		char * szname;
		char * szkind;	

		szkind = strtok(buffer, "\t");
		strtok(NULL,"\t");
		szname = strtok(NULL,"\t");

		if ( !szkind || !szname ) break ;
		{
			// �Է��� �����ΰ�� �����̸���, �����ΰ�� ��������ũ�� ã�´�.
			if(IsNumber(VillageUnique) == true)
			{
				if(strcmp(VillageUnique,szkind)==0)
				{
					strcpy(village_name,szname);
					return;
				}		
			}
			else
			{
				if(strcmp(VillageUnique,szname)==0)
				{
					strcpy(village_name,szkind);
					return;
				}		
			}
		}		
		i ++ ;
	}

	fclose(fp);

}

bool CVillageManager::IsNumber(LPCTSTR pszText)
{
	for( int i = 0; i < lstrlen( pszText ); i++ )
		if( !_istdigit( pszText[ i ] ) )
			return false;

	return true;
}
