//---------------------------------
// 2003/5/17 ���°�
//---------------------------------
/* ==========================================================================
	Ŭ���� :		cltNSummonStatus

	�ۼ��� :		05/03/14
	�ۼ��� :		���뷡
	
	������� :		����

	�����۾� :		

   ========================================================================*/
//#if defined(__LEON_NCHARSTATUS__) && defined(_DEBUG)

#pragma once

#include <directives.h>

#include "CommonHeader.h"
#include "../../InterfaceMgr/DialogController.h"

#define MAX_CHARSTATUS_PAGE_NUMBER	5

#define WANTIED_ANIMAL_CHANGE_TYPE	2

class cltCharClient;
class cltParametaBox;
class cltSummonScroll;
class cltCharManager;
class cltItem;
class cltSummon;
class cltPItemInfo;

class CButton;
class CCheckBox;
class CComboBox;
class CEdit;
class CImageStatic;
class CList;
class CRadioButton;
class CStatic;
class COutLine;

//[�߰� : Ȳ���� 2008. 2. 19 => ��ȯ�� �ɷ�ġ ���� ��� ������ ���� ����.]
class Summon_Bonus_Use
{
public:
	enum{ TYPE_STR, TYPE_AGI, TYPE_WIS, TYPE_VIT, TYPE_WISDOM, TYPE_HAND };

	SI16	m_siTotalBunus;		// ��ü ��� ������ ���ʽ� ����.
	SI16	m_siUseBunus;		// ���� ��� ������ ���ʽ� ����.(���Ǽ� ���� ���� ���ʽ� ��.)
	
	SI16	m_siStr;
	SI16	m_siAgi;
	SI16	m_siWis;
	SI16	m_siVit;
	SI16	m_siWisdom;		// ����   ���� ����. �̸��� �ߺ��ǹ��ȴ�!!! ��~.
	SI16	m_siHand;		// ������ ���� ����. 

	SI16	m_siPreStr;
	SI16	m_siPreAgi;
	SI16	m_siPreWis;
	SI16	m_siPreVit;

	SI16	m_siPreWisdom;		// ����   ���� ����. �̸��� �ߺ��ǹ��ȴ�!!! ��~.
	SI16	m_siPreHand;		// ������ ���� ����. 

public:
	Summon_Bonus_Use()
	{
		ZeroMemory(this, sizeof(Summon_Bonus_Use));
	}
	~Summon_Bonus_Use()
	{
	}
	void Clear(void)
	{
		ZeroMemory(this, sizeof(Summon_Bonus_Use));
	}
	void SetUseBonus(SI16 _UseBonus)
	{
		m_siUseBunus   = 0;
		m_siTotalBunus = 0;

		m_siUseBunus   = _UseBonus;
		m_siTotalBunus = _UseBonus;
	}
	void SetPreStr(SI16 _siPreStr)
	{
		m_siPreStr = _siPreStr;
	}
	void SetPreAgi(SI16 _siPreAgi)
	{
		m_siPreAgi = _siPreAgi;
	}
	void SetPreWis(SI16 _siPreWis)
	{
		m_siPreWis = _siPreWis;
	}
	void SetPreVit(SI16 _siPreVit)
	{
		m_siPreVit = _siPreVit;
	}
	void SetPreWisdom(SI16 _siPreWisdom)
	{
		m_siPreWisdom = _siPreWisdom;
	}
	void SetPreHand(SI16 _siPreHand)
	{
		m_siPreHand = _siPreHand;
	}

	bool IsBouns(SI16 _Count)
	{
		if( 0 >= m_siTotalBunus )
		{
			return false;
		}

		if( m_siUseBunus - _Count > m_siTotalBunus )
		{
			//return false;
		}

		if( 0 > _Count && 0 == m_siUseBunus)
		{
			//return false;
		}

		SI16 Bonus = m_siUseBunus + ( -1 * _Count );
		if( Bonus < 0 )
		{
			return false;
		}

		return true;
	}
	
	void NewSetBouns(SI16 _Count)
	{
		SI16 Bonus = m_siUseBunus + ( -1 * _Count );
		
		m_siUseBunus = Bonus;
	}

	void SetStr(SI16 _Count)
	{
		if(true == IsBouns(_Count))
		{
			if(0 > _Count)
			{
				if( 0 == m_siStr )
				{
					return;
				}
				if( m_siPreStr > m_siPreStr + m_siStr + _Count)	
				{
					return;
				}
				if( m_siStr != m_siPreStr && 0 >= abs( m_siStr - m_siPreStr ) )
					
				{
					return;
				}
			}

			m_siStr += _Count;
			NewSetBouns( _Count );
		}
	}

	void SetAgi(SI16 _Count)
	{
		if(true == IsBouns(_Count))
		{
			if(0 > _Count)
			{
				if( 0 == m_siAgi )
				{
					return;
				}
				
				if( m_siPreAgi > m_siPreAgi + m_siAgi + _Count)	
				{
					return;
				}

				if( m_siAgi != m_siPreAgi && 0 >= abs( m_siAgi - m_siPreAgi ) )
				{
					return;
				}
			}
			m_siAgi += _Count;
			NewSetBouns( _Count );
		}
	}

	void SetWis(SI16 _Count)
	{
		if(true == IsBouns(_Count))
		{
			if(0 > _Count)
			{
				if( 0 == m_siWis )
				{
					return;
				}
				if( m_siPreWis > m_siPreWis + m_siWis + _Count)	
				{
					return;
				}
				if( m_siWis != m_siPreWis && 0 >= abs( m_siWis - m_siPreWis ) )

				{
					return;
				}
			}
			m_siWis += _Count;
			NewSetBouns( _Count );
		}
	}
   
	void SetVit(SI16 _Count)
	{
		if(true == IsBouns(_Count))
		{
			if(true == IsBouns(_Count))
			{
				if(0 > _Count)
				{
					if( 0 == m_siVit )
					{
						return;
					}
					if( m_siPreVit > m_siPreVit + m_siVit + _Count)	
					{
						return;
					}
					if( m_siVit != m_siPreVit && 0 >= abs( m_siVit - m_siPreVit ) )

					{
						return;
					}
				}
			}
			m_siVit += _Count;
			NewSetBouns( _Count );
		}
	}

	void SetWisdom(SI16 _Count)
	{
		if(true == IsBouns(_Count))
		{
			if(0 > _Count)
			{
				if( 0 == m_siWisdom )
				{
					return;
				}
				if( m_siPreWisdom > m_siPreWisdom + m_siWisdom + _Count)	
				{
					return;
				}
				if( m_siWisdom != m_siPreWisdom && 0 >= abs( m_siWisdom - m_siPreWisdom ) )

				{
					return;
				}
			}

			m_siWisdom += _Count;
			NewSetBouns( _Count );
		}
	}
	void SetHand(SI16 _Count)
	{
		if(true == IsBouns(_Count))
		{
			if(0 > _Count)
			{
				if( 0 == m_siHand )
				{
					return;
				}
				if( m_siPreHand > m_siPreHand + m_siHand + _Count)	
				{
					return;
				}
				if( m_siHand != m_siPreHand && 0 >= abs( m_siHand - m_siPreHand ) )

				{
					return;
				}
			}

			m_siHand += _Count;
			NewSetBouns( _Count );
		}
	}

	SI16 GetDecreaseBonus(void)
	{
		return m_siTotalBunus - m_siUseBunus;	
	}

	bool IsZeroAbilityPoint( void )
	{
		if ( 0 != m_siStr )
		{
			return false;
		}

		if ( 0 != m_siAgi )
		{
			return false;
		}

		if ( 0 != m_siWis )
		{
			return false;
		}

		if ( 0 != m_siVit )
		{
			return false;
		}

		if ( 0 != m_siWisdom )
		{
			return false;
		}

		if ( 0 != m_siHand )
		{
			return false;
		}

		return true;
	}

	void InitForAbilityPoint( void )
	{
		m_siStr		= 0;
		m_siAgi		= 0;
		m_siWis		= 0;
		m_siVit		= 0;
		m_siWisdom	= 0;
		m_siHand	= 0;
	}
};

// ��ȯ�� ���� â
class cltNSummonStatus : public CDialogController
{
	enum CHARSTATUS_VARIABLE
	{
		 CHARSTATUS_HP_NUM			= 0		
		,CHARSTATUS_MP_NUM			= 4		
		,CHARSTATUS_EXP_NUM			= 8		

		// �������� ���� ����		  
		,CHARSTATUS_BAR_WIDTH		= 144
		// ���� �� ����(�������� �ٿ� �ܺ��������̽� ���� ������ �Ǵ� ����)
		,BASE_BAR_WIDTH				= 200		
		// HP ������ ������ġ		 
		,CHARSTATUS_HP_START_X		= 123	
		,CHARSTATUS_HP_START_Y		= 46	
		// MP ������ ������ġ		 
		,CHARSTATUS_MP_START_X		= 123	
		,CHARSTATUS_MP_START_Y		= 58	
		// EXP ������ ������ġ		 
		,CHARSTATUS_EXP_START_X		= 123	
		,CHARSTATUS_EXP_START_Y		= 70	
		
		// ��ȯ�� ���� ���¹̳� ������ ������ġ		 
		,CHARSTATUS_TRANSFORM_STAMINA_START_X		= 97	
		,CHARSTATUS_TRANSFORM_STAMINA_START_Y		= 94
		,CHARSTATUS_TRANSFORM_STAMINA_BAR_WIDTH		= 170
	};
public:
	CImageStatic	*m_pImagestatic_portrait;
	CStatic			*m_pStatictext_level;
	CButton			*m_pButton_takeinout;
	CStatic			*m_pStatictext_exp;
	CStatic			*m_pStatictext_expvalue;
	CStatic			*m_pStatictext_magic1;
	CStatic			*m_pStatictext_magic1value;
	CStatic			*m_pStatictext_name;
	CStatic			*m_pStatictext_life;
	CStatic			*m_pStatictext_lifevalue;
	CStatic			*m_pStatictext_life2;
	CStatic			*m_pStatictext_strength;
	CStatic			*m_pStatictext_dex;
	CStatic			*m_pStatictext_magic;
	CStatic			*m_pStatictext_bonus;
	CEdit			*m_pEditbox_life2;
	CEdit			*m_pEditbox_strength;
	CEdit			*m_pEditbox_dex;
	CEdit			*m_pEditbox_magic;
	CEdit			*m_pEditbox_bonus;
	CButton			*m_pButton_life2_plus;
	CButton			*m_pButton_strength_plus;
	CButton			*m_pButton_dex_plus;
	CButton			*m_pButton_magic_plus;
	CButton			*m_pButton_free;
	CButton			*m_pButton_explain;
	CButton			*m_pButton_init;
	CEdit			*m_pEditbox_health_explain;
	CStatic			*m_pStatictext_levelvalue;
	CStatic			*m_pStatictext_attackattribute;
	CButton			*m_pButton_revive;
	CButton			*m_pButton_strength_minus;
	CButton			*m_pButton_dex_minus;
	CButton			*m_pButton_magic_minus;
	CButton			*m_pButton_life2_minus;
	
	//[�߰� : Ȳ���� 2008. 2. 19 => ��ȯ�� �ɷ�ġ ���뿡 ����� ��ư.]
	CButton			*m_pButton_Ability_Ok;
	CButton			*m_pButton_Ability_Cancel;
	
	CComboBox		*m_pCombobox_strength;
	CComboBox		*m_pCombobox_dex;
	CComboBox		*m_pCombobox_magic;
	CComboBox		*m_pCombobox_life2;
	CStatic			*m_pStatictext_totaldamage;
	CStatic			*m_pStatictext_armourdefense;
	CEdit			*m_pEditbox_totaldamage;
	CEdit			*m_pEditbox_armourdefense;
	CComboBox		*m_pCombobox_apowername;
	CComboBox		*m_pCombobox_dpowername;
	CEdit			*m_pEditbox_name;
	CButton			*m_pButton_changename;
	CComboBox		*m_pCombobox_summons;
	CCheckBox		*m_pCheckbox_autoheal;
	CRadioButton	*m_pRadiobutton_autoheal30;
	CRadioButton	*m_pRadiobutton_autoheal50;
	CRadioButton	*m_pRadiobutton_autoheal70;
	CRadioButton	*m_pRadiobutton_attack;
	CRadioButton	*m_pRadiobutton_wait;
	CComboBox		*m_pCombobox_scroll;
	CStatic			*m_pStatictext_summon;

	COutLine		*m_pOutline_noname1	;
	COutLine		*m_pOutline_noname2	;

	//[����] ��ȯ�� ���� �߰��� �ɷ�ġ ǥ�ú� ��Ʈ��.
	CStatic*		m_pStatictext_hand;
	CEdit*			m_pEditbox_hand;
	CStatic*		m_pStatictext_Wisdom;
	CEdit*			m_pEditbox_Wisdom;
		
	CStatic*		m_pStatictext_physical_attack; 		
	CEdit*			m_pEditbox_physical_attack;			
	CStatic*		m_pStatictext_pysical_defense;		
	CEdit*			m_pEditbox_pysical_defense;			
	CStatic*		m_pStatictext_masic_attack;			
	CEdit*			m_pEditbox_magic_attack;			
	CStatic*		m_pStatictext_magic_defense;		
	CEdit*			m_pEditbox_magic_defense;			
	CStatic*		m_pStatictext_pysical_hit_rank;		
	CEdit*			m_pEditbox_pysical_hit_rank;		
	CStatic*		m_pStatictext_pysical_dodge_rank;	
	CEdit*			m_pEditbox_pysical_dodge_rank;		
	CStatic*		m_pStatictext_magic_hit_rank;		
	CEdit*			m_pEditbox_magic_hit_rank;			
	CStatic*		m_pStatictext_magic_dodge_rank;		
	CEdit*			m_pEditbox_magic_dodge_rank;		
	CStatic*		m_pStatictext_move_speed;				
	CEdit*			m_pEditbox_move_speed;	
	COutLine*		m_pOutline_noname3;					// ����3�� �߰�.
	COutLine*		m_pOutline_noname4;
	COutLine*		m_pOutline_noname5;
	COutLine*		m_pOutline_noname6;
	

	CStatic*		m_pStatictext_HP;		
	CStatic*		m_pStatictext_MP;
	CStatic*		m_pStatictext_EXP;		
	CStatic*		m_pStatictext_FULL_EXP;	
	CStatic*		m_pStatictext_TransformStamina;	

	CButton*		m_pButton_hand_plus;
	CButton*		m_pButton_hand_minus;
	CButton*		m_pButton_wisdom_plus;
	CButton*		m_pButton_wisdom_minus;

	CImageStatic*	m_pImageStatic_bonus;

	CEdit*			m_pEdit_life2_new;
	CEdit*			m_pEdit_strength_new;
	CEdit*			m_pEdit_dex_new;
	CEdit*			m_pEdit_magic_new;
	CEdit*			m_pEdit_hand_new;
	CEdit*			m_pEdit_Wisdom_new;
	
	// PCK - ��ȯ�� ���¹̳� ���� ��ư �߰� (08.07.16)
	CButton*		m_pButton_SPTCharge;

	// ��ȯ�� ���� ��Ʈ�� ��ư �߰�
	CButton*		m_pButton_Mysummon;

	//[����] ��ȯ�� ���� ��ư.
	CButton			*m_pButton_Summon_Transform;

	Summon_Bonus_Use	m_clSummon_Use_Bonus;		// [�߰� : Ȳ���� 2008. 2. 19 => ��ȯ�� �ɷ�ġ ���濡 ��� �� ����ü]
	
	// PCK - ������ ���� �߰�
	cltPItemInfo*	m_pPersonItemInfo;

	cltNSummonStatus(cltCharManager* pclcm);
	~cltNSummonStatus();

	void Create( CControllerMgr *pParent );
	bool IsShow();
	void Show();
	void Hide();
	void Action();
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	void InitSummonStatusInfo();
	void UpdateSummonStatusInfo();
	void UpdateSummonPortrait();
	void SendSummonAutoHealMessageToServer(SI16 data,bool autoheal);
	void ShowDetailScrollInfo(IN cltSummonScroll *pScroll , OUT TCHAR* pszScrollInfo, SI32	siTextSize);
	void SendUseSummonBonusMessageToServer( SI16 data,bool bInit = false );
	void SendSummonStatusInitMessageToServer();
	void SendSummonAttackTypeMessageToServer( SI32 siAttackType );
	void SendSummonChangeNameMessageToServer();
	void SendSummonTakeInOutMessageToServer(SI32 siSummonUnique = 0);
	void SendSummonFreeMessageToServer();
	void SendSummonReviveMessageToServer();
	BOOL GetComboSummonNameIndex( TCHAR *CurrSummonName, SI16 txtSize, SI32 *siSummonIndex);
	void ShowDetailStrInfo( cltParametaBox* pclPB );
	void ShowDetailMagInfo( cltParametaBox* pclPB );
	void ShowDetailDexInfo( cltParametaBox* pclPB );
	void ShowDetailVitInfo( cltParametaBox* pclPB );
	void ShowDetailDamageInfo( cltParametaBox* pclPB, cltItem* pclitemlist, SI32 activesweapon, cltSummon* pclSummon );
	void ShowDetailArmourInfo( cltParametaBox* pclPB );
	void ShowDetailHndInfo( cltParametaBox* pclPB );
	void ShowDetailWisdomInfo( cltParametaBox* pclPB );
	
	void SendUseSummonBonus(void);					// [�߰� : Ȳ���� 2008. 2. 19 => ��ȯ�� �ɷ�ġ ����� ������ ���� ����� �Լ�.]
	void StatusChangeClick( SI16 _type );			// [�߰� : Ȳ���� 2008. 2. 20 => ��ȯ�� �ɷ�ġ ���� ���v�� ���� �� ���� ����.]
	void SetBaseStatusToolTip(void);
	void UpdateSummon_Hp_Mp_Exp( void );

	bool 				m_bShow;
	BOOL 				BonusSummonButtonEnableSwitch;		// ��ȯ�� ���ʽ� �÷��ִ� ��ư�� Ȱ��ȭ �Ǿ� �ִ��� Ȯ���ϴ� ����. 
	BOOL 				m_bChangedInitSummonStatus;
	BOOL 				m_siLastSummonComboList;			// ���������� Combo List�� ������ ��ȯ�� 
	cltCharManager* 	pclCM;
	TCHAR				strSummonName[ MAX_SUMMON_NAME ];
	SI32				CharUnique;
	clock_t				m_LastTakeInOutTime;
	SI32				m_siPortraitSummonKind;

	//[����] ������ �̹��� �׸���. 2008-3-24
	TSpr 				m_sprGageBack;
	TSpr 				m_sprGage;	
	
	//[����] ��ȯ�� ���� ���� �̹���. 2008-3-24
	TSpr 				m_sprTTime;	
	TSpr 				m_sprTGage1;	

	bool 				BufStatusChange;

	static void CALLBACK NSummonStatusStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NSummonStatusProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Close();

    
	//[����] ĳ���� ����â ���� �̹��� �׸���. 2008-3-24
	void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY );
	void DrawCharStatus( SI32 ScreenRX, SI32 ScreenRY );

	//[����] ���ο� �ɷ�ġ �����ֱ�.
	void SetNewAbility( cltParametaBox* pclPB );
};


//#endif
