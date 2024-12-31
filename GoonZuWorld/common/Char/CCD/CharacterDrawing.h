#ifndef _CHARACTERDRAWING_H_
#define _CHARACTERDRAWING_H_

// GameMode - 1 : ����, 2 : Ŭ���̾�Ʈ

#include <stdio.h>
#include <direct.h>
#include "../../../Lib/Graphic/Graphic.h"

#include "BaseDefinition.h"
#include "TSpr.h"

enum { CCD_GAMEMODE_SERVER = 1, CCD_GAMEMODE_CLIENT = 2 };

#define EFFECT_SCROLL_NUM 4	// ������ ���ο� ȿ���� 4���̻��϶� ��������
class CXSPRMgr;
extern	CXSPRMgr	g_XSPRMgr;

class CCharacterDrawing  
{
public:
	CCharacterDrawing();
	CCharacterDrawing( char cGameMode );
	~CCharacterDrawing();

	void	ReadActionCode();
	void	ReadHelmetCode();
	void	ReadArmorCode();
	void	ReadWeaponCode();
	void	ReadMantleCode();
	void	ReadHorseCode();
	void	ReadMinFile();
	void	ReadFileList();

	void	LoadMinFileData();

	void	Initialize();
	void	Destroy();
	
	char	GetCurrentDirection();
	void	SetCurrentDirection( char cCurrentDirection, short *pDrawSequence );

	short	GetAnimationStartIndex();
	void	SetAnimationStartIndex( short ssAnimationStartIndex );

	short	GetAnimationEndIndex();
	void	SetAnimationEndIndex( short ssAnimationEndIndex );

	short	GetCurrentAnimationIndex();
	void	SetCurrentAnimationIndex( short ssCurrentAnimationIndex );

	
	
	TCHAR	*GetHelmetCode();
	TCHAR	*GetArmorCode();
	TCHAR	*GetWeaponCode();	
	TCHAR	*GetMantleCode();
	TCHAR	*GetEquipmentCode();	
	TCHAR	*GetHorseCode();
	TCHAR	*GetEffectCode();

	void	LoadItemCodeData( SI16 CharacterKind, TCHAR *strHelmet, TCHAR *strArmor, TCHAR *strWeapon, TCHAR *strMantle, TCHAR *strHorse, SI32 EffectKind, void *pEffectParam );
	void	DrawCharacter( short ssActionIndex, char cDirection, short ssAnimationIndex, 
						   short ssBottomX, short ssBottomY, SI32 JewelWeapon = 0, SI32 JewelHelmet = 0,SI32 JewelArmor = 0,
						   SI32 JewelMantle = 0 ,bool JewelHorse = false, bool AttackScroll = false , SI08 AttackScrollNum = 0,
						   bool* Reverse = false,SI32* EffectX = 0,SI32* EffectY = 0 ,SI32* EffectFont = 0,SI32* AttackImg = 0
						   ,SI32 siPremiumpartsUnique_Slot1 = 0 ,SI32 siPremiumpartsUnique_Slot2 = 0 , SI32 siPremiumpartsUnique_Slot3 = 0 ,SI16 siHorseUnique = 0);

	// ���� ����ȭ�鿡�� �׷��ֱ�
	void	DrawCharacterSelectMode( short ssActionIndex, char cDirection, short ssAnimationIndex, 
		short ssBottomX, short ssBottomY, SI32 JewelWeapon = 0, SI32 JewelHelmet = 0,SI32 JewelArmor = 0,
		SI32 JewelMantle = 0 ,bool JewelHorse = false, bool AttackScroll = false , SI08 AttackScrollNum = 0,
		bool* Reverse = false,SI32* EffectX = 0,SI32* EffectY = 0 ,SI32* EffectFont = 0,SI32* AttackImg = 0 );
	
	void	DrawPreFrame( short ssBottomX, short ssBottomY );
	void	DrawNextFrame( short ssBottomX, short ssBottomY );

	char	GetFrameNum( int siActionIndex );
	char	GetAttackFrameNum( int siActionIndex );
	short	GetCurrentFrameIndex();
	char	GetDelayTime( int siActionIndex, int CharacterKind );

	short	GetCharacterXSize();
	short	GetCharacterYSize();

	int		GetLoadedImageNum();	

	void	SetScrollEffect( TSpr *pImgSpr, short ssBottomX, short ssBottomY, SI08 siNum, bool bHaveHorse, 
							 bool* Reverse, SI32* EffectX, SI32* EffectY,SI32* EffectFont,SI32* AttackImg);	// ���� ����Ʈ ����

	// ��æƮ ����Ʈ ���ϸ��� ��ȯ���ִ� �Լ�
	void	GetEnchantEffectFileName(TCHAR* pszWeaponCode, UI32	uiJewelEffect, TCHAR* pszActionCode, TCHAR* FileName, SI32 siFileNameLen);
	//// �� �����̾� ���� ����Ʈ ���ϸ��� ��ȯ ���ִ� �Լ�
	//void	GetPremiumPartsEffectFileName(TCHAR* pszWeaponCode,SI32 siPremiumpartsUnique, TCHAR* pszActionCode, TCHAR* FileName, SI32 siFileNameLen);
	// �� �����̾� ���� ����Ʈ ���ϸ��� ��ȯ ���ִ� �Լ�
	void	GetPremiumPartsEffectFileName_Horse(TCHAR* pszWeaponCode,SI32 siPremiumpartsUnique, TCHAR* pszActionCode, TCHAR* FileName, SI32 siFileNameLen);
	// �� �����̾� ���� ����Ʈ ���ϸ��� ��ȯ ���ִ� �Լ�
	void	GetPremiumPartsEffectFileName_Motor(TCHAR* pszWeaponCode,SI32 siPremiumpartsUnique, TCHAR* pszActionCode, TCHAR* FileName, SI32 siFileNameLen);
	// �� �����̾� ���� Ǯ ����Ʈ ���ϸ��� ��ȯ ���ִ� �Լ�
	void	GetPremiumPartsFullEffectFileName(TCHAR* pszWeaponCode,SI32 siPremiumpartsUnique1,SI32 siPremiumpartsUnique2,SI32 siPremiumpartsUnique3, TCHAR* pszActionCode, TCHAR* FileName, SI32 siFileNameLen);

private:
	char	m_cGameMode;

	short	m_ssAnimationNum;
	char	m_cCurrentDirection;
	
	short	m_ssAnimationStartIndex;
	short	m_ssAnimationEndIndex;

	short	m_ssCurrentAnimationIndex;

	char	m_cCurrentActionIndex;

	bool	m_bReverse;

	int		m_siDrawingSequence[ 5 ][ MAX_DRAWING_SEQUENCE_NUM ];								// ���� 5�� �ټ� ������ ���ϰ�, ���� 5�� ��� ������( �Ӹ�, ����, �޼�, ������, �� )

	
	
	SI16	m_siCharacterKind;
	SI16	m_siTempCharacterKind;
	bool	m_bIsTakeMantle;
	bool	m_bIsTakeEquipment;
	bool	m_bIsTakeHorse;	
	bool	m_bIsEffect;
	TCHAR	m_strCharacterKind[ 4 ];
	TCHAR	m_strTempCharacterKind[ 4 ];
	TCHAR	m_strHelmet[ MAX_ITEMCODE_LENGTH ];							// ��� ������ �ڵ�
	TCHAR	m_strArmor[ MAX_ITEMCODE_LENGTH ];							// ���� ������ �ڵ�
	TCHAR	m_strWeapon[ MAX_ITEMCODE_LENGTH ];							// ���� ������ �ڵ�
	TCHAR	m_strMantle[ MAX_ITEMCODE_LENGTH ];							// ���� ������ �ڵ�
	TCHAR	m_strEquipment[ MAX_ITEMCODE_LENGTH ];						// ��� ������ �ڵ�
	TCHAR	m_strHorse[ MAX_ITEMCODE_LENGTH ];							// �� ���� �ڵ�
	TCHAR	m_strEffect[ MAX_ITEMCODE_LENGTH ];							// ����Ʈ �ڵ�
	SI32	m_siEffectKind;

	TCHAR	m_strFileName[ 5 ][ MAX_DRAWING_SEQUENCE_NUM ][ _MAX_PATH ];						// ��ü �ϼ��� ���ϸ�( 5����� �� ���⺰ ��� ������ ���� ��� ���ϸ��� ������ ���� )

	short	i, j;
 
};

#endif