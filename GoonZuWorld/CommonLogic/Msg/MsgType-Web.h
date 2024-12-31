#ifndef _MSGTYPEWEB_H
#define _MSGTYPEWEB_H

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Web.h"

#define MAX_PUCHIKOMI_URL 516		// ���̵�( 256 )+ ��ȣ( 256 )+ ���̵�� ��ȣ�� �����ϴ� ����( 4 )


//-------------------------------------------
// ���� ���� �뺸. 
//-------------------------------------------
class cltGameMsgResponse_News{
public:
//	bool	bBroadcastSwitch;						// ����� ���������� ����. 
	
	TCHAR	szNewsTitle[MAX_NEWS_TITLE_LENGTH];		// ���� �Ӹ����. 
	TCHAR	szNewspaperName[MAX_NEWSPAPER_NAME_LENGTH];	// �Ź��� �̸�. 
	TCHAR	szNewURL[MAX_PATH];							// ���� ��ũ�Ǵ� URL

	SI32	siNewsKind;	// ������ ����

	cltGameMsgResponse_News(TCHAR* ptitle, TCHAR* pnewspaper, TCHAR* pnewsurl ,SI32 newskind )
	{
		MStrCpy( szNewsTitle, ptitle, MAX_NEWS_TITLE_LENGTH );
		MStrCpy( szNewspaperName, pnewspaper, MAX_NEWSPAPER_NAME_LENGTH );
		MStrCpy( szNewURL , pnewsurl, MAX_PATH );

//		bBroadcastSwitch	= bbroadcast;

		siNewsKind = newskind ;
	}
};


//-------------------------------------------
// Ǫġ�ڹ̿� �α��ε� �ּҸ� ���´�. (�ڽ�)
//-------------------------------------------
class cltGameMsgRequest_MyPuchikomiURL{
public:
	
	TCHAR				szAccountID[MAX_PLAYER_NAME] ; // �ڽ��� ���� ID
	TCHAR				szPassWord[FILE_NAME_SIZE] ;	// �ڽ��� ���� PASSWORD

	cltGameMsgRequest_MyPuchikomiURL(TCHAR* account, TCHAR* password)
	{
		MStrCpy(szAccountID,account,MAX_PLAYER_NAME);
		MStrCpy(szPassWord,password,FILE_NAME_SIZE);
	}
};

class cltGameMsgResponse_MyPuchikomiURL{
public:

	TCHAR	szMyPuchikomiURL[MAX_PUCHIKOMI_URL];
	
    cltGameMsgResponse_MyPuchikomiURL(TCHAR * myPuchikomiURL)
	{
		MStrCpy(szMyPuchikomiURL,myPuchikomiURL,MAX_PUCHIKOMI_URL);
	}

};



//-------------------------------------------
// �ٸ� ������ Ǫġ�ڹ� �ּҸ� �˾ƿ´�
//-------------------------------------------
class cltGameMsgRequest_UserPuchikomiURL{
public:
	SI32 siToPersonCharUnique;
	TCHAR szToPersonName[ MAX_PLAYER_NAME ];

	cltGameMsgRequest_UserPuchikomiURL( SI32 ToPersonCharUnique )
	{
		siToPersonCharUnique = ToPersonCharUnique;
		szToPersonName[ 0 ] = NULL;
	}

	cltGameMsgRequest_UserPuchikomiURL( TCHAR *szname )
	{
		siToPersonCharUnique = 0;
		MStrCpy( szToPersonName, szname, MAX_PLAYER_NAME );
		szToPersonName[ MAX_PLAYER_NAME - 1 ] = NULL;
	}
};


class cltGameMsgResponse_UserPuchikomiURL{
public:

	TCHAR	szUserPuchikomiURL[MAX_PUCHIKOMI_URL];

	cltGameMsgResponse_UserPuchikomiURL(TCHAR * userPuchikomiURL)
	{
		MStrCpy(szUserPuchikomiURL,userPuchikomiURL,MAX_PUCHIKOMI_URL);
	}

};


#endif
