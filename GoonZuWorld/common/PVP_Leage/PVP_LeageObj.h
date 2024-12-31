//////////////////////////////////////////////////////////////////////////
//
//	PVP_League�� �Ҷ� ���� ����Ʈ�� ������ Ŭ������ ����� �д�.
//
//	��Ī ����Ʈ�� ����
//	
//////////////////////////////////////////////////////////////////////////
#ifndef _PVP_LEAGUEOBG_H_
#define _PVP_LEAGUEOBG_H_

#include "NDataTypes.h"

class CPVP_Leage_ListData
{
private:
	SI32 m_siPersonID	;	// ����� ��� PersonID
	SI08 m_siGrade	;		// ����� ��� ���
	SI08 m_siStatus	;		// ����Ʈ�� �ִ� ���� ���� 0: �Ϲ� ���� ����, 1: �������� ��Ī ������ ����
public:
	CPVP_Leage_ListData()
	{
		ZeroMemory( this, sizeof(CPVP_Leage_ListData) );
	}

	CPVP_Leage_ListData( CPVP_Leage_ListData* pList )
	{
		if ( pList )
		{
			memcpy( this, pList, sizeof(CPVP_Leage_ListData) )	;
		}
	}

	CPVP_Leage_ListData( SI32 siPersonID, SI08 siGrade, SI08 siStatus )
	{
		m_siPersonID	= siPersonID	;
		m_siGrade		= siGrade		;
		m_siStatus		= siStatus		;
	}

	~CPVP_Leage_ListData()
	{

	}
	//--
	void SetPersonID( SI32 siPersonID )	{	m_siPersonID = siPersonID	;	}
	SI32 GetPersonID( void )			{	return m_siPersonID		;		}

	void SetGrade( SI32 siGrade )		{	m_siGrade = siGrade		;		}
	SI32 GetGrade( void )				{	return m_siGrade		;		}

	void SetSatus( SI32 siSatus )		{	m_siStatus = siSatus	;		}
	SI32 GetSatus( void )				{	return m_siStatus		;		}
	//--

	// �����͸� �뤊�� �޾Ƽ� ����
	void SetPVP_LeagueData( CPVP_Leage_ListData* pList )
	{
		if ( pList )
		{
			memcpy( this,pList,sizeof(CPVP_Leage_ListData) )	;
		}
	}

	void SetPVP_LeagueData( SI32 siPersonID, SI08 siGrade, SI08 siStatus )
	{
		m_siPersonID	= siPersonID	;
		m_siGrade		= siGrade		;
		m_siStatus		= siStatus		;
	}
	// ������ �ʱ�ȭ
	void InitPVP_LeagueData( )
	{
		ZeroMemory(this, sizeof( CPVP_Leage_ListData ))	;
	}

	// ������� ���� �ʾҴ��� Ȯ��(personid�� �˻�)
	bool IsEmpty( void )
	{
		if ( 0 >= m_siPersonID )
		{
			return true	;
		}
		return false	;
	}

	// ���� PersonID���� Ȯ��
	bool IsSamePersonID( SI32 siPersonID )
	{
		if ( (siPersonID) && (siPersonID == m_siPersonID) )
		{
			return true;
		}

		return false;
	}

};

class CPVP_Leage_MatchingListData
{
private:
	SI32 m_siBattlePersonIDHome	;	// ��Ī ������ �Ǿ��� ����� personID
	SI32 m_siBattlePersonIDAway	;	// ��Ī �� personID

	SI32 m_siScore;					// ��� ��޿� ���� Ư���� ������ ���� �� ����� ���ǰ��� ���� �ִ´�

public:
	CPVP_Leage_MatchingListData()
	{
		ZeroMemory( this, sizeof(CPVP_Leage_MatchingListData) );
	}

	CPVP_Leage_MatchingListData( CPVP_Leage_MatchingListData* pList )
	{
		if ( pList )
		{
			memcpy( this, pList, sizeof(CPVP_Leage_MatchingListData) )	;
		}
	}

	CPVP_Leage_MatchingListData( SI32 siBattlePersonIDHome, SI32 siBattlePersonIDAway, SI32 siScore )
	{
		m_siBattlePersonIDHome	=	siBattlePersonIDHome	;
		m_siBattlePersonIDAway	=	siBattlePersonIDAway	;
		m_siScore				=	siScore;
	}

	~CPVP_Leage_MatchingListData()
	{

	}
	//--
	void SetBattlePersonIDHome( SI32 siBattlePersonIDHome )	{	m_siBattlePersonIDHome = siBattlePersonIDHome	;	}
	SI32 GetBattlePersonIDHome( void )						{	return m_siBattlePersonIDHome					;	}

	void SetBattlePersonIDAway( SI32 siBattlePersonIDAway )	{	m_siBattlePersonIDAway = siBattlePersonIDAway	;	}
	SI32 GetBattlePersonIDAway( void )						{	return m_siBattlePersonIDAway					;	}

	void SetScore( SI32 siScore )							{	m_siScore = siScore;								}
	SI32 GetScore( void )									{	return m_siScore;									}
	//--

	// �����͸� �뤊�� �޾Ƽ� ����
	void SetPVP_Leage_MatchingListData( CPVP_Leage_MatchingListData* pList )
	{
		if ( pList )
		{
			memcpy( this, pList, sizeof(CPVP_Leage_MatchingListData) )	;
		}
	}

	void SetPVP_Leage_MatchingListData( SI32 siBattlePersonIDHome, SI32 siBattlePersonIDAway, SI32 siScore )
	{
		m_siBattlePersonIDHome	=	siBattlePersonIDHome	;
		m_siBattlePersonIDAway	=	siBattlePersonIDAway	;
		m_siScore				=	siScore;

	}
	// ������ �ʱ�ȭ
	void InitPVP_Leage_MatchingListData( )
	{
		ZeroMemory( this, sizeof(CPVP_Leage_MatchingListData) )	;
	}

	// ������� ���� �ʾҴ��� Ȯ��
	bool IsEmpty( void )
	{
		if ( (0 >= m_siBattlePersonIDHome) && (0 >= m_siBattlePersonIDAway) )
		{
			return true	;
		}
		return false	;
	}

	bool IsMatch( SI32 siSourcePersonID, SI32 siDestPersonID )
	{
		if( siSourcePersonID < 0 || siDestPersonID < 0 )		return false;
		if( siSourcePersonID == siDestPersonID )				return false;

		if( m_siBattlePersonIDHome == siSourcePersonID && m_siBattlePersonIDAway == siDestPersonID )		return true;
		if( m_siBattlePersonIDHome == siDestPersonID && m_siBattlePersonIDAway == siSourcePersonID )		return true;

		return false;
	}	
};

class CPVP_Leage_EndGameListData
{
private:
	SI32 m_siBattlePersonIDHome	;	// ��Ī ������ �Ǿ��� ����� personID
	SI32 m_siBattlePersonIDAway	;	// ��Ī �� personID

public:
	CPVP_Leage_EndGameListData()
	{
		ZeroMemory( this, sizeof(CPVP_Leage_EndGameListData) );
	}

	CPVP_Leage_EndGameListData( CPVP_Leage_EndGameListData* pList )
	{
		if ( pList )
		{
			memcpy( this, pList, sizeof(CPVP_Leage_EndGameListData) )	;
		}
	}

	CPVP_Leage_EndGameListData( SI32 siBattlePersonIDHome, SI32 siBattlePersonIDAway, SI32 siScore )
	{
		m_siBattlePersonIDHome	=	siBattlePersonIDHome	;
		m_siBattlePersonIDAway	=	siBattlePersonIDAway	;
	}

	~CPVP_Leage_EndGameListData()
	{

	}
	//--
	void SetBattlePersonIDWin( SI32 siBattlePersonIDHome )	{	m_siBattlePersonIDHome = siBattlePersonIDHome	;	}
	SI32 GetBattlePersonIDWin( void )						{	return m_siBattlePersonIDHome					;	}

	void SetBattlePersonIDLose( SI32 siBattlePersonIDAway )	{	m_siBattlePersonIDAway = siBattlePersonIDAway	;	}
	SI32 GetBattlePersonIDLose( void )						{	return m_siBattlePersonIDAway					;	}
	//--

	// �����͸� �뤊�� �޾Ƽ� ����
	void SetPVP_Leage_EndGameListData( CPVP_Leage_EndGameListData* pList )
	{
		if ( pList )
		{
			memcpy( this, pList, sizeof(CPVP_Leage_EndGameListData) )	;
		}
	}

	void SetPVP_Leage_EndGameListData( SI32 siBattlePersonIDHome, SI32 siBattlePersonIDAway, SI32 siScore )
	{
		m_siBattlePersonIDHome	=	siBattlePersonIDHome	;
		m_siBattlePersonIDAway	=	siBattlePersonIDAway	;
	}
	// ������ �ʱ�ȭ
	void InitPVP_Leage_EndGameListData( )
	{
		ZeroMemory( this, sizeof(CPVP_Leage_EndGameListData) )	;
	}

	// ������� ���� �ʾҴ��� Ȯ��
	bool IsEmpty( void )
	{
		if ( (0 >= m_siBattlePersonIDHome) && (0 >= m_siBattlePersonIDAway) )
		{
			return true	;
		}
		return false	;
	}
};

#endif