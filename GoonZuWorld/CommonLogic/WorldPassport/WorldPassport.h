#pragma once

#include <Directives.h>

const SI32 Const_Max_WorldPassport_Name = 20;

// DB��Ŷ�� Class
// DB���� �����͸� �޾ƿ� ���� ����Ѵ�
class cltWorldPassportForDB
{
public:
	// �����̸�
	TCHAR	m_szPassportName[Const_Max_WorldPassport_Name];
	// ��������
	SI32	m_siIssueDateVary;
	// ������
	SI32	m_siExpireDateVary;

	cltWorldPassportForDB()
	{
		ZeroMemory( this, sizeof(cltWorldPassportForDB) );
	}
	~cltWorldPassportForDB()
	{
	}
};


// �������� ����
class cltWorldPassport
{
//== Variable Area Start ==
private:
	// �����̸�
	TCHAR	m_szPassportName[Const_Max_WorldPassport_Name];
	// ��������
	SI32	m_siIssueDateVary;
	// ������
	SI32	m_siExpireDateVary;

public:
//== Variable Area End ==

//== Function Area Start ==
private:
public:
	cltWorldPassport()
	{
		Init();
	}

	~cltWorldPassport()
	{
	}

	void	Init( void )
	{
		ZeroMemory( this, sizeof(cltWorldPassport) );
	}

	void	Set( cltWorldPassport* pclWorldPassport );
	void	Set( cltWorldPassportForDB* pclWorldPassportForDB );
	void	Set( TCHAR* pszPassportName, SI32 siIssueDateVary, SI32 siExpireDateVary );

	TCHAR*	GetPassportName( void );
	void	SetPassportName( TCHAR* pszPassportName );

	SI32	GetIssueDateVary( void );
	void	SetIssueDateVary( SI32 siIssueDateVary );

	SI32	GetExpireDateVary( void );
	void	SetExpireDateVary( SI32 siExpireDateVary );

	// X�� X�� X�� ������ ���ڿ��� �Ѱ��ش�
	void	GetIssueRealDateText( TCHAR* pszBuffer, SI32 siSize );
	// X�� X�� X�� ������ ���ڿ��� �Ѱ��ش�
	void	GetExpireRealDateText( TCHAR* pszBuffer, SI32 siSize );

	// ���� �̸��� ��ȿ�� �̸����� üũ(�������� �ƴ���)
	// ���ο� �ִ� ���� üũ�ϴ� ���� �ƴϰ� �μ��� ���� ���� üũ�ϴ� ���̴�
	bool	IsCorrectPassportName( TCHAR* pszPassportName );
	bool	IsHavePassport( void );


//== Function Area End ==

};

