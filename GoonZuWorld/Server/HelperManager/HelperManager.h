#pragma once

#include "Directives.h"
#include "CommonLogic.h"

enum
{ 
	MAX_QUESTION_NUM	= 100,		// �ִ� ���� ����.
	ANSWER_LEVEL		= 50,		// �亯���� ���� ����.
	DAILY_QUESTION_NUM	= 5,		// �Ϸ� ���� ������ Ƚ��.
	TITLE_LETTER_NUM	= 48,		// ���� ���ڼ�.	( �ѱ�   64, ����  128. )
	CONTENTS_LETTER_NUM	= 2048,		// ������ ���ڼ�.	( �ѱ� 1024, ���� 2048. )
	SENDMSG_LIST_NUM	= 20,
};	

class cltQuestionInfo
{
public:
	cltQuestionInfo()															{   ZeroMemory( this, sizeof(*this));				}
	~cltQuestionInfo()															{													}

	void	Clear( void )														{	ZeroMemory(this, sizeof(*this));				}

	void	SetQuestionPersonID( SI32 _siQuestionPersonID )						{	m_siQuestionPersonID = _siQuestionPersonID;		}
	SI32	GetQuestionPersonID()												{	return	m_siQuestionPersonID;					}

	void	SetQuestionUnique( SI16 _siQuestionUnique )							{	m_siQuestionUnique = _siQuestionUnique;			}
	SI16	GetQuestionUnique()													{	return	m_siQuestionUnique;						}

	void	SetAnswerPersonID( SI32 _siAnswerPersonID )							{	m_siAnswerPersonID = _siAnswerPersonID;			}
	SI32	GetAnswerPersonID()													{	return	m_siAnswerPersonID;						}

	void	SetAnswerUnique( SI16 _siAnswerUnique )								{	m_siAnswerUnique = _siAnswerUnique;				}
	SI16	GetAnswerUnique()													{	return	m_siAnswerUnique;						}

	void	SetQuestionTile( TCHAR* _pszQuestionTile )							{	memcpy( m_szQuestionTitle, _pszQuestionTile, sizeof(m_szQuestionTitle) );				}
	TCHAR*	GetQuestionTile()													{	return	m_szQuestionTitle;															}	

	void	SetQuestionContents( TCHAR* _pszQuestionContents )					{	memcpy( m_szQuestionContents, _pszQuestionContents, sizeof(m_szQuestionContents) );	}
	TCHAR*	GetQuestionContents()												{	return	m_szQuestionContents;														}
																				
private:
	SI32	m_siQuestionPersonID;									// ������ personID
	SI16	m_siQuestionUnique;										// ������ Unique

	SI32	m_siAnswerPersonID;										// �亯�� personID
	SI16	m_siAnswerUnique;										// �亯�� Unique

	TCHAR	m_szQuestionTitle[ TITLE_LETTER_NUM ];					// ����
	TCHAR	m_szQuestionContents[ CONTENTS_LETTER_NUM ];			// ����.
};


class cltHelperManager
{
public:
	cltHelperManager();
	~cltHelperManager();

	void Init( void );
	void Action( void );
	void AddQuestion( cltQuestionInfo* _pcltQuestionInfo, SI32 id );
	void DelQuestion( cltCharServer* _pclchar, bool ReturnMsg = false );
	void DelQuestion( SI32 _siPersonID );
	bool PlusQuestion();	
	bool MinusQuestion();	

	void CheckQuestion( cltCharServer* _pclChar );
	void AddAnswer( cltCharServer* _pclchar, SI32 _siQuestionPersonID );
	void AddAnswerComplete( cltCharServer* _pclAnswerChar, SI32 _siQuestionPersonID, TCHAR* _pszQuestionTitle, TCHAR* _pszQuestionContents );
	void AddAnswerCompleteResult( bool _bResult, SI32 _siAnswerCharPersonID, SI32 _siQuestionCharID );
	void DelAnswer( cltCharServer* _pclAnswerChar );

public:
	void SendMsgQuestionTileList( SI32 _id );											// ���� ���� Ŭ�� ������.
	void SendMsgQuestionContents( SI32 _siPersonID, cltCharServer* _pclAnswerChar );	// ���� ���� Ŭ�� ������.

private:
	SI32			m_siQuestionNum;													// ���� ����Ʈ�� ��ϵ� ���� ��.
	
	cltQuestionInfo	m_cltHelperInfo[ MAX_QUESTION_NUM ];								// ���� ����.
};



