//------------------------------------------------------------------------------
//	���� : ���� �ý���
//	���� : �������迡 ���� ������ ���� class
//	���� �ۼ��� : 2009-05-20
//	�ۼ��� : �� ����
//
//------------------------------------------------------------------------------
#pragma once

#include "../common/CommonHeader.h"
#define MAX_CHILDREN_NUM	10	// �����ȿ��� ������ �ִ� �ڽĵ��� ��
#define MAX_PARENT_NUM		2	// �����ȿ��� ������ �ִ� �θ��� ��
#define MAX_MONTH_FAMILY			12	// �ִ� ������
#define MAX_DAY_FOR_FAMILY			31	// �ִ� ��¥

enum	// ���������� �ڽ��� �ź��� ���Ѵ�.
{
	MYCLASS_IN_FAMILY_NONE	=	0,			// �������� ����.
	MYCLASS_IN_FAMILY_PARANTS,				// �� �θ��� �θ��߿� �Ѹ��̴�.
	MYCLASS_IN_FAMILY_CHILDREN,				// �� ������ �������� ���̵��̴� 
};
enum	// ���Ŀ� ��Ű ȿ�� ����
{
	USE_COOKIE_LEVEL_NONE	=	0,			// ���Ŀ� ��Ű ��� ����
	USE_COOKIE_LEVEL_1,			// ���Ŀ� ��Ű ���� 1 
	USE_COOKIE_LEVEL_2,			// ���Ŀ� ��Ű ���� 2
	USE_COOKIE_LEVEL_3,			// ���Ŀ� ��Ű ���� 3
	USE_COOKIE_LEVEL_4,			// ���Ŀ� ��Ű ���� 4
	USE_COOKIE_LEVEL_5,			// ���Ŀ� ��Ű ���� 5
};
#define  COOKIE_TIME	24	// datavary�� 24�� ���ϸ� ���ǽð� 48
#define  COOKIE_COOLTIME	24	// datavary�� 10�� ���ϸ� ���ǽð� 20
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CChildrenData
{
public:
	CChildrenData()		{	ZeroMemory(this, sizeof(CChildrenData));	}
	~CChildrenData()	{ };
	void	Init( void ){	ZeroMemory(this, sizeof(CChildrenData));	}
	void	Set( CChildrenData* pclParentData )
	{
		if ( pclParentData )	{	memcpy( this, pclParentData, sizeof(CChildrenData) );	}
	}

	void	Set_Children_PersonID( SI32 siPersonID_Children )		{	m_siPersonID_Children = siPersonID_Children;			}
	SI32	Get_Children_PersonID( void )							{	return m_siPersonID_Children;					}
	void	Set_Children_Name( TCHAR* szName_Children )				{	if ( szName_Children ) StringCchCopy( m_szName_Children, sizeof(m_szName_Children), szName_Children );	}
	TCHAR*	Get_Children_Name( void )								{	return m_szName_Children;						}
	//	�Ⱓüũ�� �����ϰ� �ϱ� ���ؼ� ���� 
	void	SetFamilyEffectTime( SYSTEMTIME stFamilyEffectTime)		{m_stFamilyEffectTiem = stFamilyEffectTime;};/*{ memcpy( &m_stFamilyEffectTiem, &stFamilyEffectTime, sizeof( SYSTEMTIME) ) ; }*/
	SYSTEMTIME GetFamilyEffectTime()								{	return m_stFamilyEffectTiem		;			}

	void	InGame(){ m_bOnGame = true; };
	void	OutGame(){ m_bOnGame = false; };
	bool	GetGame(){ return m_bOnGame; };
	bool	GetOnePlayer(){ return m_bOnGame; };

	void	SetCookie( SI32 siPerson, SI32 siCookieLevel, SI32 EndDatevary, SI32 siUseLimitDateVary)	;	// ��Ű�� ��� ����
	void	DelCookie();
	SI32	GetCookieLevel(){ return m_siFamilyEffectLevel; }	;
	void	LoseCookieLevel(){ m_siFamilyEffectLevel = m_siFamilyEffectLevel -1 ;}	;
	SI32	GetCookie_Effect_EndTime(){ return m_siFamilyEffectDate_EndDateVary; }	;
	SI32	GetCookieEffect_LimitTime(){ return m_siFamilyEffectDate_LimitDateVary; }	;
protected:
private:
	bool	m_bOnGame		;		//��������

	SI32	m_siPersonID_Children ;					// �ڽ� personID
	TCHAR	m_szName_Children[MAX_PLAYER_NAME] ;	// �ڽ� �̸�
	SYSTEMTIME m_stFamilyEffectTiem	;				// ����ȿ��


	SI16	m_siFamilyEffectLevel;								// ���Ŀ� ��Ű ��� ����
	SI32	m_siFamilyEffectDate_EndDateVary;					// ���Ŀ� ��Ű ��� ����ð� �ܰ躰�� 48�� 
	SI32	m_siFamilyEffectDate_LimitDateVary;					// ���Ŀ� ��Ű ���� ��� ���ѽð� 20��
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CParentData
{
public:
	CParentData()	{ ZeroMemory( this, sizeof( CParentData) ); }
	~CParentData()	{ };
	void	Init( void ){	ZeroMemory(this, sizeof(CParentData));	}
	void	Set( CParentData* pclChildrenData )
	{
		if ( pclChildrenData )	{	memcpy( this, pclChildrenData, sizeof(CChildrenData) );	}
	}

	void	SetParent_PersonID( SI32 siPersonID_Children )				{	m_siParant_PersonID = siPersonID_Children;			}
	SI32	GetParent_PersonID( void )								{	return m_siParant_PersonID;					}
	void	SetParent_Name( TCHAR* szParant_Name )					{	if ( szParant_Name ) StringCchCopy( m_szParant_Name, sizeof(m_szParant_Name), szParant_Name );	}
	TCHAR*	GetParent_Name( void )									{	return m_szParant_Name;						}

	void	InGame(){ m_onGame = true; };
	void	OutGame(){ m_onGame = false; };
	bool	GetGame(){ return m_onGame; };
protected:
private:
	SI32	m_siParant_PersonID ;	
	TCHAR	m_szParant_Name[MAX_PLAYER_NAME];
	bool	m_onGame	;

};

class CFamily
{
private:
	SI32			m_MyClass_In_Family ;					// ���� �ź��� ������ �ְ� ������ ��ü ������ ������ �ִ´�.	
	CParentData		pclParentData[ MAX_PARENT_NUM ]		;	//�θ� �ɸ��� ����
	CChildrenData	pclChildrenData[MAX_CHILDREN_NUM]	;	//�ڽ� �ɸ��� ����
	SI32			m_NowParentNum		;					// ���� ������ �θ� ��
	SI32			m_NowChildrenNum	;					// ���� ������ �ڽ� ��

public:
	CFamily( void )		{	ZeroMemory(this, sizeof(CFamily));	}
	~CFamily( void )		{	}
	void	Init( void ){	ZeroMemory(this, sizeof(CFamily));	}
	void	Set( CFamily* pclFamily ){		if ( pclFamily )	{	memcpy( this, pclFamily, sizeof(CFamily) );	}	}
	void	Set( SI32 siMyFamilyClass , CParentData* pclParentData, CChildrenData*	pclChildrenData )
	{
		m_MyClass_In_Family	=	siMyFamilyClass	;
		memcpy( pclParentData, pclParentData, sizeof(CParentData) );	
		memcpy( pclChildrenData, pclChildrenData, sizeof(CChildrenData) );
	}
	void SetMyClass_InFamily( SI32 siClass ){  m_MyClass_In_Family = siClass; }	// �����ȿ��� ���� ��ġ�� ��Ÿ����.
	SI32 GetMyClass_InFamily( void ){ return m_MyClass_In_Family; }				// �����ȿ��� ���� ��ġ�� ���� �Ѵ�.
	
	void	GetParentName( TCHAR* pParentName_SLot1 , TCHAR* pParentName_SLot2 )	;
	TCHAR*	GetChildrenName( SI32 siSLot ) ;
	
	SYSTEMTIME GetChild_Add_Date(SI32 siSLot )	;
	SYSTEMTIME FInd_Add_Date( SI32 PersonID )	;

	void	SetChildren( SI32 siPersonID, TCHAR* szCharName,SYSTEMTIME stFamilyEffectDate);
	void	SetParent( SI32 siPersonID, TCHAR* szCharName)	;

	SI32	GetParent_1()	;
	SI32	GetParent_2()	;

	SI32	GetMatePersonID ( SI32 siParentID)	;	// �ش� �θ��� ����� ���̵� ������ �´�
	SI32	GetChildPersonID( SI32 siSLot)	;

	SI32	GetChildPersonIDfromName( TCHAR* charname)	;	// �ڽ��̸����� personId�� ã�´�.
	SI32	GetParentPersonIDfromName( TCHAR* charname)	;	// �θ� �̸����� personID�� ã�´�.

	void	DelFamilyMember( SI32 siParentID )	;		// �ش� personid�� �����ɹ��� �����.

	SI32	GetParent_PersonId(SI32 siSlot)	;
	TCHAR*	GetParent_Name(SI32 siSlot)	;
	SI32	IsParent( SI32 siPersonID)	;

	void	AddOnParentNum(){ m_NowParentNum = m_NowParentNum + 1	;}	;		/// �����ϸ� ���Լ��� �����ο��� �ø���	- �θ�
	void	LoseOnParentNum(){ m_NowParentNum = m_NowParentNum - 1	; }	;		/// ���������ϸ� ���Լ��� �����ο��� ���δ�.- �θ�

	void	AddOnChildrenNum(){ m_NowChildrenNum = m_NowChildrenNum + 1	;}	;		/// �����ϸ� ���Լ��� �����ο��� �ø��� - �ڽ�
	void	LoseOnChildrenNum(){ m_NowChildrenNum = m_NowChildrenNum - 1	; }	;	/// ���������ϸ� ���Լ��� �����ο��� ���δ�. -�ڽ�

	SI32	GetOnParentNum(){ return m_NowParentNum; }	;					/// ���� ������ �θ��� ��
	SI32	GetOnChildrenNum(){ return m_NowChildrenNum; }	;				/// ���� ������ �ڽĵ��� ��

	void	ConnectIn( SI32 siPersonID , SI32 siFamilyClass )	;	// �ش� �ɸ��Ͱ� ���� �ߴ�
	void	ConnectOut( SI32 siPersonID ,SI32 siFamilyClass )	;	// �ش� �ɸ��Ͱ� ������ ������.

	bool	IsConnectParent( SI32 siSLot)	{ return pclParentData[siSLot].GetGame(); }; // �ش� �θ� ���� ���ִ���
	bool	IsConnectChildren( SI32 siSLot)	{ return pclChildrenData[siSLot].GetGame(); }; // �ش� �ڽ��� ���� ���ִ���

	// ��Ű ����� ���� ������.
	void	SetCookie(  SI32 siPersonID , SI32 siCookelevel, SI32 EndDatevary, SI32 siUseLimitDateVary, SI32 siMyClass )		;	// ��Ű�� ��� �ߴ�
	void	LoseCookieLevel( SI32 siPersonID )	;	// ��Ű ������ 1�ܰ� ���δ�.
	SI32	GetMyCookieLevel(SI32 siPersonID)	;	// ���� ��Ű ������ ������ �´�.
	SI32	GetMyCookie_EndTime(SI32 siPersonID)	;	// ���� ��Ű ���� Ÿ��
	SI32	GetMyCookie_Limitime(SI32 siPersonID)	;	// ���� ��Ű ��� ���� Ÿ��

	bool	GetOnGame_Children( SI32 siSlot )	;			// ���ӿ� ���� �ߴ��� Ȯ��
	bool	GetOnGame_Parent( SI32 siSlot )	;				// ���ӿ� ���� �ߴ��� Ȯ�� 

	SI32	GetCookieEffect( SI32 siCookieLevel )	;		// ��Ű ȿ�� �� ������ �´�.

};