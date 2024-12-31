#include "CushionCatEffect.h"
#include <Graphic.h>
#include "Graphic_Capsule.h"
#include "CommonLogic.h"
#include "../../../common/char/KindInfo/kindinfo.h"

CCushionCatEffect::CCushionCatEffect(TSpr *pEffect1 , TSpr *pEffect2 , TSpr * pEffect3 , TSpr * pEffect4,TSpr * pEffect5,TSpr * pEffect6,TSpr * pEffect7,TSpr * pEffect8 )
{
	m_pEffectTSPR[0] = pEffect1;
	m_pEffectTSPR[1] = pEffect2;
	m_pEffectTSPR[2] = pEffect3;
	m_pEffectTSPR[3] = pEffect4;
	m_pEffectTSPR[4] = pEffect5;
	m_pEffectTSPR[5] = pEffect6;
	m_pEffectTSPR[6] = pEffect7;
	m_pEffectTSPR[7] = pEffect8;


	m_siDelayFrame = 3;

	m_bEffect = false;

	m_siCurrentFrame = 0;

	m_Clock  = 0;

	m_siSelectedSpr = 0;
	m_siSelectedFont = 0;
	m_bReverse = false;

	m_siAdjustX = 0;
	m_siAdjustY = 0;

}
CCushionCatEffect::~CCushionCatEffect()
{

}

void CCushionCatEffect::Action( SI32 bEffect  , SI32 charkind)	// ����Ʈ�� �׷��� ���� ������ ���ڷ� ����
{
	m_bEffect = bEffect;

	if( m_bEffect == false ) return; // �׷����� �ʴ� ��Ȳ�̶�� ���� ����.

	m_siAdjustX = 0;
	m_siAdjustY = 0;


	switch( m_bEffect )
	{
		case ITEMUNIQUE(13608): // ���������  - ���糲
			m_siSelectedSpr = 0;
			break;
		case ITEMUNIQUE(13609): // �丣�þ� ����� - ���翩
			{
				m_siSelectedSpr = 1;
				m_siAdjustY = 25;
			}
			break;
		case ITEMUNIQUE(13610): // ��������� - ���糲
			{
				m_siSelectedSpr = 2;
				m_siAdjustX = -15;
				m_siAdjustY = 20;
			}
			break;
		case ITEMUNIQUE(13611): //�Ͼ����� - ���翩
			{
				m_siSelectedSpr = 3;
				m_siAdjustY = 35;
			}
			break;
		case ITEMUNIQUE(13617):// �ڽ���Ʈ - ���糲
			{
				m_siSelectedSpr = 4;
				m_siAdjustY = 28;
				m_siAdjustX = 25;
			}
			break;
		case ITEMUNIQUE(13618):// ���� - ���糲
			{
				m_siSelectedSpr = 5;
				m_siAdjustY = 29;
				m_siAdjustX = 40;
			}
			break;
		case ITEMUNIQUE(13619): // ����Ǫ�� - ���翩
			{
				m_siSelectedSpr = 6;
				m_siAdjustY = 29;
				m_siAdjustX = 37;
			}
			break;
		case ITEMUNIQUE(13620): // �ú����� �㽺ũ - ���翩
			{
				m_siSelectedSpr = 7;
				m_siAdjustY = 25;
				m_siAdjustX = 25;
			}
			break;
		default :
			m_bEffect = 0;
	}

	// �̺ҷ��� �׸��� �ʴ���.
	if( m_bEffect == 0 ) return;
	
  	if (TABS(pclClient->CurrentClock - m_Clock ) > 100)
	{
  		m_Clock = pclClient->CurrentClock;

		if( m_siCurrentFrame > m_pEffectTSPR[m_siSelectedSpr]->GetImageNum() - 3 )
		{
			m_siCurrentFrame = 0;
		}
		else
		{
			m_siCurrentFrame++;
		}
	}

}

void CCushionCatEffect::Draw( SI32 si32CenterXPos, SI32	si32CenterYPos  )
{
 	if ( m_bEffect == false )	return; // �׷����� �ʴ� ��Ȳ�̶��  �׸��� ����.

	if( m_siSelectedSpr < 0 || m_siSelectedSpr > 7 ) return;


	SI32 XPos = si32CenterXPos - m_pEffectTSPR[m_siSelectedSpr]->GetXSize() / 2 + 20;
	SI32 YPos = si32CenterYPos - m_pEffectTSPR[m_siSelectedSpr]->GetYSize() / 2 - 35;

		GP.PutSpr(m_pEffectTSPR[m_siSelectedSpr], XPos + m_siAdjustX, YPos + m_siAdjustY , m_siCurrentFrame );    
}


