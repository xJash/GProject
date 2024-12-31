#pragma once 

#include <Directives.h>
#include "..\..\Common\CommonHeader.h"


#define MAX_KOINOBORYFAMILY_MAKE_POS	42

enum KOINOBORYFAMILY_KIND
{
	KOINOBORYFAMILY_KIND_NONE	= -1,

	KOINOBORYFAMILY_KIND_YELLOW	= 0,
	KOINOBORYFAMILY_KIND_RED,
	KOINOBORYFAMILY_KIND_BLUE,

	KOINOBORYFAMILY_KIND_MAX
};

class cltKoinoboryFamilyPosition
{
private:
	// ���̳뺸�� ��� ��ġ
	cltCharPos	m_clPos[MAX_KOINOBORYFAMILY_MAKE_POS];

	// ���̳뺸�� ��� ��ġ�� �����ϰ� ���� ���� �ϱ����� ����
	// ���� �����ǰ�ü�� �����ϰ� �ϴ°ͺ��� �ӵ��� �̵��� ��������
	SI32		m_siRandIndex[MAX_KOINOBORYFAMILY_MAKE_POS];

public:
	cltKoinoboryFamilyPosition( void );
	~cltKoinoboryFamilyPosition( void );

	void		Init( void );

public:
	void		SetPosition( void );
	void		RandomMixUpIndex( void );
	
	cltCharPos*	GetRandomPosition( const SI32 siIndex );

};

class cltKoinoboryFamilyManager
{
public:
	cltKoinoboryFamilyManager();
	~cltKoinoboryFamilyManager();

	void Action();

	void StartEvent();
	void EndEvent();

public:
	//	175	KIND_KOINOBORYYELLOW	���̳뺸�� - ���
	//	176	KIND_KOINOBORYRED		���̳뺸�� - ����
	//	177	KIND_KOINOBORYBLUE		���̳뺸�� - �Ķ�
	SI32 GetKoinoboryYellowKind();
	SI32 GetKoinoboryRedKind();
	SI32 GetKoinoboryBlueKind();

private:
	void MakeKoinoboryFamily( void );
	void NoticeKoinoboryFamily( void );

	bool CreateKoinobory( const SI32 siIndex );
	bool DeleteKoinobory( const SI32 siIndex );

	SI32 GetKoinoboryKind( const SI32 siIndex );


private:
	SI16						m_siStartHour;

	SI32						m_siKonoboryIndex[KOINOBORYFAMILY_KIND_MAX];

	cltKoinoboryFamilyPosition	m_clPos;

};

