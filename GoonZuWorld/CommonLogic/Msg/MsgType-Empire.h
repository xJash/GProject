#ifndef _MSGTYPE_EMPIRE_H
#define _MSGTYPE_EMPIRE_H

#include "../../common/CommonHeader.h"
#include "../../Server/Empire/EmpireManager.h"

//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_InviteEmpire
//
// Last Modified 	: 2007 / 10 / 19 
// Created		 	: �豤��
//
// Function			: [��û]������ �ʴ��Ѵ�.
//
//*************************************************************************************************** 
class cltGameMsgRequest_InviteEmpire
{
public:

	enum { VILLAGE = 0, GUILD };
	/// �������� �ʴ��ϴ� ���� 
	SI08	siInviteType;
	/// �������� �ʴ��� ����� �̸�
	TCHAR	szUserName[MAX_PLAYER_NAME];
	
	cltGameMsgRequest_InviteEmpire( SI08 InviteType , TCHAR* UserName )
	{
		siInviteType = InviteType;
		StringCchCopy( szUserName, MAX_PLAYER_NAME, UserName );
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgResponse_InviteEmpire
//
// Last Modified 	: 2007 / 10 / 19 
// Created		 	: �豤��
//
// Function			: [��û]������ �ʴ��Ѵ�.
//
//*************************************************************************************************** 
class cltGameMsgResponse_InviteEmpire
{
public:

	enum { VILLAGE = 0, GUILD, EMPEROR };
	/// �������� �ʴ��ϴ� ���� 
	SI08	siInviteType;
	/// �ʴ�޽����� ���� ���� ����ũ
	SI32	siEmpireUnique;
	/// �ʴ�޽����� ������ ���� ���� �̸�
	SI32	siEmproerVillageUnique;
	/// �ʴ븦 ���� ����� PersonID
	SI32	siFromPersonID;

	cltGameMsgResponse_InviteEmpire( SI08 InviteType , SI32 EmpireUnique, SI32 FromPersonID, SI32 EmproerVillageUnique )
	{
		siInviteType = InviteType;
		siEmpireUnique = EmpireUnique;
		siFromPersonID = FromPersonID;
		siEmproerVillageUnique = EmproerVillageUnique;
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_JoinEmpire
//
// Last Modified 	: 2007 / 10 / 24 
// Created		 	: �豤��
//
// Function			: [��û] ���� �ʴ뿡 ���Ѵ�.
//
//*************************************************************************************************** 
class cltGameMsgRequest_JoinEmpire
{
public:

	enum { VILLAGE = 0, GUILD };
	/// �������� �ʴ�Ǵ� ���� 
	SI08	siInviteType;
	/// �ʴ��� ��� PersonID
	SI32	siFromPersonID;
	/// �ʴ�޽����� ���� ���� ����ũ
	SI32	siEmpireUnique;


	cltGameMsgRequest_JoinEmpire( SI08 InviteType , SI32 FromPersonID, SI32 EmpireUnique )
	{
		siInviteType = InviteType;
		siFromPersonID = FromPersonID;
		siEmpireUnique = EmpireUnique;
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgResponse_JoinEmpire
//
// Last Modified 	: 2007 / 10 / 24 
// Created		 	: �豤��
//
// Function			: [����] ���� �ʴ뿡 ���Ѵ�.
//
//*************************************************************************************************** 
class cltGameMsgResponse_JoinEmpire
{
public:

	enum { EMPEROR = 0, OTHERUSER };
	/// �ʴ��� ����� �ʴ�� ����� �����ϱ� ����
	SI08	siSendType;
	/// �ʴ�� ��������ũ
	SI32	siEmpireUnique;
	/// �ʴ�� ��������ũ
	SI32	siVillageUnique;
	/// �ʴ�� �������ũ
	SI32	siGuildUnique;
	

	cltGameMsgResponse_JoinEmpire( SI08 SendType , SI32 EmpireUnique, SI32 VillageUnique, SI32 GuildUnique )
	{
		siSendType = SendType;
		siEmpireUnique = EmpireUnique;
		siVillageUnique = VillageUnique;
		siGuildUnique = GuildUnique;
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgResponse_UpdateEmpireInfo
//
// Last Modified 	: 2007 / 10 / 22 
// Created		 	: �豤��
//
// Function			: [����] Ŭ���̾�Ʈ�� �� �ڽ��� ���� ������ ������Ʈ ��Ų��.
//
//*************************************************************************************************** 
class cltGameMsgResponse_UpdateEmpireInfo
{
public:

	enum { VILLAGE = 0, GUILD };
	// ���� ������ ������Ʈ �� ���
	SI16		siCharUnique;		
	SI08		siUpdateType;
	CEmpireInfo clEmpireInfo;

	cltGameMsgResponse_UpdateEmpireInfo( SI16 CharUnique, SI08 UpdateType, SI08 RankType, SI32 EmpireUnique )
	{
		siCharUnique = CharUnique;
		siUpdateType = UpdateType;
		clEmpireInfo.SetEmpireInfo( RankType, EmpireUnique );
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_EmpireInfo
//
// Last Modified 	: 2007 / 10 / 22 
// Created		 	: �豤��
//
// Function			: [��û] ���� ������ ��û�Ѵ�.
//
//*************************************************************************************************** 
class cltGameMsgRequest_EmpireInfo
{
public:

	/// ��û�� ó���ΰ�?( ó�� ��û�Ҷ��� bRequestFirst = true, ��������ũ�� 0
	bool bRequestFirst;
	/// �Ϲ� ������ ��û�ΰ�, ������� ��û�ΰ�?
	bool bVillageChief;
	/// ��û�� ��������ũ
	SI32 siVillageUnique;

	cltGameMsgRequest_EmpireInfo( bool RequestFirst, bool VillageChief, SI32 VillageUnique )
	{
		bRequestFirst = RequestFirst;
		bVillageChief = VillageChief;
		siVillageUnique = VillageUnique;
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgResponse_EmpireInfo
//
// Last Modified 	: 2007 / 10 / 22 
// Created		 	: �豤��
//
// Function			: [����] ���� ������ ��û�Ѵ�.
//
//*************************************************************************************************** 
class cltGameMsgResponse_EmpireInfo
{
public:
	bool bRequestFirst;
	bool bVillageChief;
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_EMPIRENUMBER>				siEmperprVillageUnique;
#else
	SI32 siEmperprVillageUnique[MAX_EMPIRENUMBER];
#endif
	CEmpireUnitInfo clEmpireInfo;
	TCHAR szVillageChiefName[MAX_EMPIRE_IN_VILLAGE][MAX_PLAYER_NAME];
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_EMPIRE_IN_VILLAGE>		siVillageMemberNumber;
#else
	SI32 siVillageMemberNumber[MAX_EMPIRE_IN_VILLAGE];
#endif
	TCHAR szGuildChiefName[MAX_EMPIRE_IN_GUILD][MAX_PLAYER_NAME];
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_EMPIRE_IN_GUILD>			siGuildMemberNumber;
#else
	SI32 siGuildMemberNumber[MAX_EMPIRE_IN_GUILD];
#endif

	cltGameMsgResponse_EmpireInfo( bool RequestFirst, bool VillageChief, SI32* EmperprVillageUnique, CEmpireUnitInfo* EmpireInfo,
		                           TCHAR VillageChiefName[][MAX_PLAYER_NAME], SI32* VillageMemberNumber,
								   TCHAR GuildChiefName[][MAX_PLAYER_NAME], SI32* GuildMemberNumber )
	{
		bRequestFirst = RequestFirst;
		bVillageChief = VillageChief;

		SI32 i;
		if( NULL == EmperprVillageUnique )
		{
			for( i = 0; i < MAX_EMPIRENUMBER; ++i )
			{
				siEmperprVillageUnique[i] = 0;
			}
		}
		else
		{
			for( i = 0; i < MAX_EMPIRENUMBER; ++i )
			{
				siEmperprVillageUnique[i] = EmperprVillageUnique[i];
			}
		}

		if( NULL == EmpireInfo )
		{
			clEmpireInfo.InitEmpireUnitInfo();
		}
		else
		{
			clEmpireInfo.SetEmpireUnitInfo( EmpireInfo );
		}

		for( i = 0; i < MAX_EMPIRE_IN_VILLAGE; ++i )
		{
			if( NULL == VillageChiefName )
			{
				StringCchCopy( szVillageChiefName[i], MAX_PLAYER_NAME, "" );
			}
			else
			{
				StringCchCopy( szVillageChiefName[i], MAX_PLAYER_NAME, VillageChiefName[i] );
			}

			if( NULL == VillageMemberNumber )
			{
				siVillageMemberNumber[i] = 0;
			}
			else
			{
				siVillageMemberNumber[i] = VillageMemberNumber[i];
			}
		}

		for( i = 0; i < MAX_EMPIRE_IN_GUILD; ++i )
		{
			if( NULL == GuildChiefName )
			{
				StringCchCopy( szGuildChiefName[i], MAX_PLAYER_NAME, "" );
			}
			else
			{
				StringCchCopy( szGuildChiefName[i], MAX_PLAYER_NAME, GuildChiefName[i] );
			}

			if( NULL == GuildMemberNumber )
			{
				siGuildMemberNumber[i] = 0;
			}
			else
			{
				siGuildMemberNumber[i] = GuildMemberNumber[i];
			}
		}
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_SecedeEmpire
//
// Last Modified 	: 2007 / 10 / 25 
// Created		 	: �豤��
//
// Function			: [��û]�������� Ż���Ѵ�.
//
//*************************************************************************************************** 
class cltGameMsgRequest_SecedeEmpire
{
public:

	enum { EMPEROR = 0, VILLAGE_CHIEF, GUILD_CHIEF };
	/// �������� Ż���ҷ��� ��û�� ���
	SI08 siSecedeType;
	/// �������� Ż���� ��������ũ 
	SI32 siVillageUnique;
	/// �������� Ż���� ��������ũ
	SI32 siGuildUnique;

	cltGameMsgRequest_SecedeEmpire( SI08 SecedeType , SI32 VillageUnique, SI32 GuildUnique  )
	{
		siSecedeType = SecedeType;
		siVillageUnique = VillageUnique;
		siGuildUnique = GuildUnique;
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgResponse_SecedeEmpire
//
// Last Modified 	: 2007 / 10 / 19 
// Created		 	: �豤��
//
// Function			: [����]�������� Ż���Ѵ�.
//
//*************************************************************************************************** 
class cltGameMsgResponse_SecedeEmpire
{
public:

	enum { VILLAGE = 0, GUILD, EMPEROR };
	/// �������� �ʴ��ϴ� ���� 
	SI08	siInviteType;
	/// �ʴ�޽����� ���� ���� ����ũ
	SI32	siEmpireUnique;
	/// �ʴ�޽����� ������ ���� ���� �̸�
	SI32	siEmproerVillageUnique;
	/// �ʴ븦 ���� ����� PersonID
	SI32	siFromPersonID;

	cltGameMsgResponse_SecedeEmpire( SI08 InviteType , SI32 EmpireUnique, SI32 FromPersonID, SI32 EmproerVillageUnique )
	{
		siInviteType = InviteType;
		siEmpireUnique = EmpireUnique;
		siFromPersonID = FromPersonID;
		siEmproerVillageUnique = EmproerVillageUnique;
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_SetEmpireMoney
//
// Last Modified 	: 2007 / 10 / 25 
// Created		 	: �豤��
//
// Function			: [��û]���� �ں����� �����Ѵ�.( ���� ���ͱ����� ���� )
//
//*************************************************************************************************** 
class cltGameMsgRequest_SetEmpireMoney
{
public:

	/// ���� �ں��ݿ� ���� ��
	SI64 siInputMoney;
	
	cltGameMsgRequest_SetEmpireMoney( SI64 InputMoney ) : siInputMoney( InputMoney ) {}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_SetEmpireMoney
//
// Last Modified 	: 2007 / 10 / 25 
// Created		 	: �豤��
//
// Function			: [����]���� �ں����� �����Ѵ�.( ���� ���ͱ����� ���� )
//
//*************************************************************************************************** 
class cltGameMsgResponse_SetEmpireMoney
{
public:

	/// ���� �ں��ݿ� ���� ��
	SI64 siInputMoney;

	cltGameMsgResponse_SetEmpireMoney( SI64 InputMoney ) : siInputMoney( InputMoney ) {}
};

#endif 