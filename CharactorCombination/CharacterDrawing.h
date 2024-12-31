#ifndef _CHARACTERDRAWING_H_
#define _CHARACTERDRAWING_H_


#include <stdio.h>
#include <direct.h>
#include "./Graphic.h"

#include "BaseDefinition.h"

class CMinDataMgr;

struct stActionCode
{
	int cActionIndex;
	char strActionCode[ MAX_ACTIONCODE_LENGTH ];
	char strActionName[ MAX_ITEM_NAME ];				// MAX_ITEM_NAME �� ���� ���� ����. �׳� 24 �ְ�, �� ������ �ϱ� �׷��� �׳� ����.
	int cFrameNum;
	int cTotalFrameNum;
	int cDirection;
};

struct stArmorCode
{
	char strArmorName[ MAX_ITEM_NAME ];
	char strArmorCode[ MAX_ITEMCODE_LENGTH ];
	unsigned int uiArmorIndex;
};

struct stHelmetCode
{
	char strHelmetName[ MAX_ITEM_NAME ];
	char strHelmetCode[ MAX_ITEMCODE_LENGTH ];
	unsigned int uiHelmetIndex;
};

struct stWeaponCode
{
	char strWeaponName[ MAX_ITEM_NAME ];
	char strWeaponCode[ MAX_ITEMCODE_LENGTH ];	
	int cWeaponAction;
	char strWeaponActionCode[ MAX_ACTIONCODE_LENGTH ];
	unsigned int uiWeaponIndex;
};

struct stMantleCode
{
	char strMantleName[ MAX_ITEM_NAME ];
	char strMantleCode[ MAX_ITEMCODE_LENGTH ];
	unsigned int uiMantleIndex;
};

struct stHorseCode
{
	char strHorseName[ MAX_ITEM_NAME ];
	char strHorseCode[ MAX_ITEMCODE_LENGTH ];
	unsigned int uiHorseIndex;
};

struct stHorseHeadCode
{
	char strHorseHeadName[ MAX_ITEM_NAME ];
	char strHorseHeadCode[ MAX_ITEMCODE_LENGTH ];
	unsigned int uiHorseHeadIndex;
};

class CCharacterDrawing  
{
public:
	CCharacterDrawing();
	~CCharacterDrawing();

	void	ReadActionCode();
	void	ReadHelmetCode();
	void	ReadArmorCode();
	void	ReadWeaponCode();
	void	ReadMantleCode();
	void	ReadHorseCode();
	void	ReadHorseHeadCode();
	void	ReadMinFile();
	void	ReadFileList();

	void	LoadMinFileData();

	void	Initialize();
	void	Destroy();

	

	char	GetCurrentDirection();
	void	SetCurrentDirection( char cCurrentDirection, int *pDrawSequence );

	short	GetAnimationStartIndex();
	void	SetAnimationStartIndex( short ssAnimationStartIndex );

	short	GetAnimationEndIndex();
	void	SetAnimationEndIndex( short ssAnimationEndIndex );

	short	GetCurrentAnimationIndex();
	void	SetCurrentAnimationIndex( short ssCurrentAnimationIndex );

	char	*GetActionName( int cIndex );
	char	*GetActionCode( int cIndex );
	char	GetActionNum();

	char	*GetHelmetName( int cIndex );
	char	*GetHelmetCode( int cIndex );
	unsigned int GetHelmetNum();

	char	*GetArmorName( int cIndex );
	char	*GetArmorCode( int cIndex );
	unsigned int GetArmorNum();

	char	*GetWeaponName( int cIndex );
	char	*GetWeaponCode( int cIndex );
	char	GetWeaponActionIndex( int cIndex );
	unsigned int GetWeaponNum();

	char	*GetMantleName( int cIndex );
	char	*GetMantleCode( int cIndex );
	unsigned int GetMantleNum();

	char	*GetHorseName( int cIndex );
	char	*GetHorseCode( int cIndex );
	unsigned int GetHorseNum();

	char	*GetHorseHeadName( int cIndex );
	char	*GetHorseHeadCode( int cIndex );
	unsigned int GetHorseHeadNum();

		

	void	LoadImageDataFromList( char *strHelmet, char *strArmor, char *strWeapon, char *strMantle, char *strHorse, char *strHorseHead );

	void	LoadItemCodeData( char cSex, char *strHelmet, char *strArmor, char *strWeapon, char *strMantle, char *strHorse, char *strHorseHead );
	void	DrawCharacter( char *strAction, char cDirection, short ssAnimationIndex, short ssBottomX, short ssBottomY );

	
	// �Ʒ��� 2���� ���� ���� ����
	void	GetDrawingInfo( char *strFilePath );	
	void	DrawCharacter( int *pDrawSequence, char cActionIndex, char cDirection, short ssBottomX, short ssBottomY );

	void	DrawPreFrame();
	void	DrawNextFrame();

	void	SaveMinFile( int siDelayTime );
	void	ReloadMinFileList();
	void	LoadMinFile( char *strFileName, int **ppSequence, char *pActionIndex, char *pSex, char *pDelayTime );

	char	*FileName( int siIndex );

	
	
private:

	CMinDataMgr	*m_pMinDataMgr;

	short	m_ssAnimationNum;
	char	m_cCurrentDirection;
	
	short	m_ssAnimationStartIndex;
	short	m_ssAnimationEndIndex;

	short	m_ssCurrentAnimationIndex;

	char	m_cCurrentActionIndex;

	bool	m_bReverse;

	int		m_siDrawingSequence[ 5 ][ MAX_DRAWING_SEQUENCE_NUM ];								// ���� 5�� �ټ� ������ ���ϰ�, ���� 5�� ��� ������( �Ӹ�, ����, �޼�, ������, ����, �� )

	
	
	char	m_cSex;														// ���� = 1, ���� = 2 ����
	bool	m_bIsTakeHorse;
	bool	m_bIsTakeMantle;
	bool	m_bIsTakeEquipment;
	bool	m_bIsTakeHorseHead;
	char	m_strSex[ 4 ];												// ����(TP1), ����(TP2)
	char	m_strTempSex[ 4 ];												// ����(TP1), ����(TP2)
	char	m_strHelmet[ MAX_ITEMCODE_LENGTH ];							// ��� ������ �ڵ�
	char	m_strArmor[ MAX_ITEMCODE_LENGTH ];							// ���� ������ �ڵ�
	char	m_strWeapon[ MAX_ITEMCODE_LENGTH ];							// ���� ������ �ڵ�
	char	m_strMantle[ MAX_ITEMCODE_LENGTH ];							// ���� ���� �ڵ�
	char	m_strEquipment[ MAX_ITEMCODE_LENGTH ];						// ��� ������ �ڵ�
	char	m_strHorse[ MAX_ITEMCODE_LENGTH ];							// �� ���� �ڵ�
	char	m_strHorseHead[ MAX_ITEMCODE_LENGTH ];							// ���Ӹ� ���� �ڵ�

	char	m_strFileName[ 5 ][ MAX_DRAWING_SEQUENCE_NUM ][ MAX_PATH ];						// ��ü �ϼ��� ���ϸ�( 5����� �� ���⺰ ��� ������ ���� ��� ���ϸ��� ������ ���� )

	char	m_strImageFileNameList[ MAX_FILE_NUM ][ MAX_PATH ];			// ���� �ִ� �̸��� 128 byte
	
	int		m_siImageFileNum;
	int		m_siMinFileNum;

	stActionCode	*m_pstAction;
	int		m_cActionNum;

	stArmorCode		*m_pstArmor;
	unsigned int	m_uiArmorNum;

	stHelmetCode	*m_pstHelmet;
	unsigned int	m_uiHelmetNum;

	stWeaponCode	*m_pstWeapon;
	unsigned int	m_uiWeaponNum;

	stMantleCode	*m_pstMantle;
	unsigned int	m_uiMantleNum;

	stHorseCode		*m_pstHorse;
	unsigned int	m_uiHorseNum;

	stHorseHeadCode	*m_pstHorseHead;
	unsigned int	m_uiHorseHeadNum;

	short	i, j;

	

};

#endif