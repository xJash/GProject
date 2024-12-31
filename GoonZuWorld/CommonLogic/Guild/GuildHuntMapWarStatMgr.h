#ifndef __GUILDHUNTMAPWARSTATMGR_H__
#define __GUILDHUNTMAPWARSTATMGR_H__

#include "guild.h"
#include "CommonHeader.h"
#include "../../Client/client.h"


class cltGuildHuntMapWarStatMgr
{
public:
	
	//	Home/Away ��� �̸�
	enum GuildHomeAway
	{
		GUILDTEAM_HOME,		//	Ȩ��
		GUILDTEAM_AWAY,		//	�����
		GUILDTEAM_END,		
	};

	enum GuildHuntMapDrawFlag
	{
		DRAWFLAG_NONE,	
		DRAWFLAG_START,	
		DRAWFLAG_WIN,	
		DRAWFLAG_LOSE,	
		DRAWFLAG_DRAW,	
		DRAWFLAG_END,	
	};

	TCHAR		m_szGuildName[GUILDTEAM_END][MAX_GUILD_NAME];				//	��� �̸�

	SI32		m_siBGP[GUILDTEAM_END];										//	BGP (battle guild point)
	SI32		m_siGuildPoint[GUILDTEAM_END];								//	��� ����Ʈ
	SI16		m_siGuildMarkIndex[GUILDTEAM_END];							//	��� ��ũ
   
	TCHAR		m_siKillUserName[MAX_PLAYER_NAME];							//	���� ����
	TCHAR		m_siDeathUserName[MAX_PLAYER_NAME];							//	���� ����

	bool		m_bGuildWarSwitch;											//	���� �����ȹ�� ������ΰ�

	SI32		m_siDrawFlag;												//	Draw����
	clock_t		m_noticeClock;												//	�ð����� üũ ����
	clock_t		m_endClock;													//	����� ���� �ð�
	SI32		m_siResult;													//	����?



public:
	cltGuildHuntMapWarStatMgr();
	~cltGuildHuntMapWarStatMgr();

	void	Init();		

	void	StartGuildWar(TCHAR* homename, TCHAR* awayname, SI16 homemark, SI16 awaymark);	//	�����ȹ�� ����� ����
	void	EndGuildWar(SI32 recvGP, SI32 siTeamIndex, TCHAR* szPlayerName, SI32  siKillNum, SI32  siDeathNum);														//	����� ����
	
	
	void	SetGuildName(SI32 siTeamIndex, TCHAR* szGuildName);								//	��� �̸� ����
	TCHAR*	GetGuildName(SI32 siTeamIndex){return m_szGuildName[siTeamIndex];}				


	void	SetGuildMarkIndex(SI32 siTeamIndex, SI16 siGuildMarkIndex);						//	��� ��ũ �ε��� ����
	SI16	GetGuildMarkIndex(SI32 siTeamIndex){return m_siGuildMarkIndex[siTeamIndex];}						


	void	SetBGP(SI32 siTeamIndex, SI32 siBGP);											//	BGP ����
	SI32	GetBGP(SI32 siTeamIndex){return m_siBGP[siTeamIndex];}							


	void	SetPersonKillInfo(TCHAR* szKillUserName, TCHAR* szDeathUserName, SI32 siTeamIndex);		//	�������� ų���� ����
	
	void	SetGuildPoint(SI32 siTeamIndex);												//	��� ����Ʈ ����
	SI32	GetGuildPoint(SI32 siTeamIndex){return m_siGuildPoint[siTeamIndex];}			

	void	SetDrawFlag(SI32 siDrawFlag);													// ��ο��÷��� ����
	SI32	GetDrawFlag(){return m_siDrawFlag;}		

	bool	IsGuildHuntMapWar(){return m_bGuildWarSwitch;}									//	���� ����� ��?

	SI32	GetResult(){return m_siResult;}													//	�� �� �� ���
    
	void	DrawStatus(LPDIRECTDRAWSURFACE7 lpsurface, SI32 rx, SI32 ry);

};


#endif