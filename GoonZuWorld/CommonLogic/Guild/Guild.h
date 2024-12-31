#ifndef _GUILD_H
#define _GUILD_H

#include <Directives.h>

#include "../../Common/CommonHeader.h"
#include "../StructureClass/StructureClass.h"



#define MAX_GUILD_NUM			500			// ���� ���� ��ü ��� ���Ѽ�
// ��� ���� �ѹ��� ���� ����Ʈ ���� ���� ��Ŷ����� ���� �ɼ� �־ ���Դϴ�.
// ���� ��� ������ �ø��� ��Ŷ����� Ȯ�� �ؾ� �մϴ�. 25 -> 10
#define MAX_GUILD_PER_DBLIST	10			// DB���� ������ �� �ѹ��� ������ �� �ִ� ����Ʈ������ ���Ѽ�	

#define MAX_GUILD_NAME			13			// ��� �̸� ����. 13����Ʈ������ ���������� 12����Ʈ ����

#define MAX_GUILD_MEMBER_NUM	35			// ��� �ִ� �ο���
#define MIN_GUILD_MEMBER_NUM	8			// ��� �ּ� �ο���

#define MAX_GUILD_PER_VILLAGE	50			// �ϳ��� ������ �ҼӵǴ� ����� �ִ��

#define MIN_GUILD_MASTER_LEVEL	40			// ��� ������ �ּ� ����

#define MIN_GUILD_CREATE_FEE	1000000		// ��� �������

#define MAX_GUILDHUNTWAR_REQUEST_NUM 100	// �ִ� ���ʼ����Ǻ��� ���� ���� ���<-���� ��� ����.
#define MAX_GUILDHUNTWAR_RANK_NUM 10		// ���� �����Ǻ��淩ũ

#define MAX_HUNTMAP_GUILDWAE_NUM	180			// ��� �ִ� �ο���


class cltGuildMember // ����
{
public:
	SI32			siPersonID;
	TCHAR			szCharName[MAX_PLAYER_NAME];
	SI08			siType;
	GMONEY			siMoney;
	SI32			siGP;	// ���� GP
	SI16			m_siLevel;	//[�߰� : Ȳ���� 2008. 2. 13 ���� ���� ���� �߰�.]

	cltGuildMember()
	{
		siPersonID = 0 ;
		ZeroMemory(szCharName,sizeof(TCHAR)* MAX_PLAYER_NAME);
		siType = 0 ;
		siMoney = 0 ;
		m_siLevel = 0;
	}
};
// �Ϸ絿�� �ο� ��� ����ũ�� ����Ѵ�.- ������ ������ �ο� �����
class cltHuntMapGuildWarEnemy
{
public:
	SI32 siEnemyGuildUnique;
	cltHuntMapGuildWarEnemy()
	{
		siEnemyGuildUnique = 0;
	}
	void init()
	{
		siEnemyGuildUnique	=	0;
	}
	void SetEnemy(SI32 EnemyGuild)
	{
		siEnemyGuildUnique	=	EnemyGuild	;
	}
	SI32 GetEnemy()
	{
		return siEnemyGuildUnique;
	}
};

class cltGuildStandingMemeber // ���� �����
{
public:
	SI32			siPersonID;
	TCHAR			szCharName[MAX_PLAYER_NAME];

	cltGuildStandingMemeber()
	{
		siPersonID = 0 ;
		ZeroMemory(szCharName,sizeof(TCHAR)* MAX_PLAYER_NAME);
	}
};

// ��� GP �� �� ����
class cltGuildPoint{
public:
	SI32			siLevel; // Guild Level
	SI32			siPoint; // GP(Guild Point)
	GMONEY			siMoney; // Guild Money

	cltDate			clDate; // ������ ������ ������ ����
	SI32			siFaultNum; // ������ �̳� Ƚ�� - 3�� �̳��ϸ� ��� ��ü

	SI32			siMarkIndex; // ��ũ �ε���

	SI32			siApplyMapIndex;	// ��û�� ������ ���ε���
	SI32			siBattleGP;				// ��������� ���� GP

	cltGuildPoint()
	{
		siLevel = 0 ;
		siPoint = 0 ;
		siMoney = 0 ;

		clDate.Set(0,0,0,0,0);
		siFaultNum = 0 ;

		siMarkIndex = 0 ;

		siApplyMapIndex = 0;
		siBattleGP = 0;
	}
};

// ��� �ɷ�ġ
class cltGuildStatus : public cltBasicAbility{
public:
/*
	SI32		siStr;		// ��
	SI32		siDex;		// ��ø
	SI32		siMag;		// ����
	SI32		siVit;		// ü��
	SI32		siHnd;		// ������
	SI32		siLuck;		// ��
*/
	SI32		siBonus;

	cltGuildStatus()
	{
		siBonus = 0 ;
	}

	SI32	GetTotalStatus()
	{
		return siStr+siDex+siMag+siVit+siHnd+siLuk+siBonus;
	}
};

#define GUILDSTATUS_STANDING			0	// ���� �����
#define GUILDSTATUS_NORMAL				1	// ���� Ȱ����
#define GUILDSTATUS_CHANGEVILLAGE		2	// ������ �̵���
#define MAX_GUUILDENEMYINFO_TODAY			72	// �Ϸ絿�� �ִ�� ������ �ִ� ����� ������� ���� 
// ����� �⺻����
class cltGuildInfo{
public:
	SI32					siUnique; // ��� ����ũ
	TCHAR					szName[MAX_GUILD_NAME]; // ��� �̸�

	SI32					siVillageUnique;			// ��尡 �ִ� �ǹ� �Ҽ� ����
	SI32					siMoveVillageUnique;		// ������ �̵��� ����

	SI32					siMasterPersonID; // ��� ������ personid

	cltGuildPoint			clGPoint;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltGuildMember, MAX_GUILD_MEMBER_NUM>				clMember;
	NSafeTArray<cltGuildStandingMemeber, MAX_GUILD_MEMBER_NUM>		clStandingMember;
	NSafeTArray<cltHuntMapGuildWarEnemy, MAX_GUUILDENEMYINFO_TODAY>				clHuntguildEnemy;// ���ʼ�����ĺ����������ο����
#else
	cltGuildMember			clMember[MAX_GUILD_MEMBER_NUM]; // ��� ȸ�� ����
	cltGuildStandingMemeber	clStandingMember[MAX_GUILD_MEMBER_NUM]; // ��� ���� ��û�� ����
	cltHuntMapGuildWarEnemy	clHuntguildEnemy[MAX_GUUILDENEMYINFO_TODAY]; // ���ʼ�����ĺ����������ο������
#endif

	cltDate					clDate; // ��� ������
	GMONEY					siFee; // �Ӵ��
	UI08					uiConfirm; // ���� ����. true�� ����. false�� �����(��Ȱ��)

	cltGuildStatus			clStatus;	// ��� �ɷ�ġ

	cltGuildInfo()
	{
		Init();
	}

	void Init()
	{
		siUnique = 0 ;
		ZeroMemory(szName,sizeof(TCHAR)*MAX_GUILD_NAME);

		siVillageUnique = 0 ;
		siMoveVillageUnique = 0;

		siMasterPersonID = 0 ;

		ZeroMemory(&clGPoint,sizeof(cltGuildPoint));

		for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
		{
			ZeroMemory(&clMember[i],sizeof(cltGuildMember));
			ZeroMemory(&clStandingMember[i],sizeof(cltGuildMember));
		}
		/*for ( SI32 i = 0 ; i < MAX_HUNTMAP_GUILDWAE_NUM ; i ++ )
		{
			ZeroMemory(&clHuntguildEnemy[i],sizeof(cltHuntMapGuildWarEnemy));
		}*/

		clDate.Set(0,0,0,0,0);
		siFee = 0 ;
		uiConfirm = GUILDSTATUS_STANDING ;

		ZeroMemory(&clStatus,sizeof(cltGuildStatus));
		ZeroMemory(&clStatus,sizeof(cltGuildStatus));
	}

	void Set(cltGuildInfo* pclinfo)
	{
		memcpy(this,pclinfo,sizeof(cltGuildInfo));
	}

	SI32 GetMemberNum();
	SI32 GetLimitMemberNum();
	bool IsSecondMaster();
	TCHAR* GetName();
	
	// ���� ������ĺ��� ����� ���� ���
	void setHuntWarEnemy(SI32 enemyGuildunique);
	SI32 findEmptySlot();
	bool FindBeforeEnemyGuild(SI32 siGuildUnique);// ������ �ο� ���
};

//-------------------------------------------------
// �������� �纹��
//-------------------------------------------------
class cltGuild : public cltStructureBasic{
private:

public:
	cltGuild(SI32 sivillageunique);
	~cltGuild();

};

//--------------------------------------
// ����� ������. 
//--------------------------------------
class cltGuildManager : public cltStructureMngBasic{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltGuildInfo, MAX_GUILD_NUM>		clUnit;
#else
	cltGuildInfo clUnit[MAX_GUILD_NUM]; // ����� ����
#endif
	cltGuildInfo clCommonUnit;			// �ҷ��� ��� ����(Client������ ���)

	HIMAGELIST	hImageList;

	// �ν��Ͻ����� ž ��� ����
	SI32			siTopClearPoint;				//ȹ�� ����	- ���� �⵵
	SI32			siBeforeYearTopGuildUnique;		//��� ����ũ - �� �⵵
	// �Ϸ翡 3������ �Ҽ� �ִ�.
	cltGuildManager( cltCharManager* pclcm, SI32 gamemode, SI32 ranktype, TCHAR *strFileName );
	~cltGuildManager();

	cltGuildInfo* GetGuildInfo(SI32 guildunique);
	cltGuildInfo* GetGuildInfo(TCHAR* guildname );
	TCHAR*	GetGuildName(SI32 guildunique);

	// ���� ȯ�� �λ縻ǥ�� . 
	void GreetingMsg(HWND hDlg);
	void Do_WM_INITDIALOG(SI32 charunique);

	BOOL CreateGuild(SI32 siunique);

	bool AddGuildInfo(cltGuildInfo* pclinfo);
	bool DeleteGuildInfo(SI32 guildunique);
	
	void Action(bool bdaychangedswitch);
};

#endif