#include "ValentineWarEffect.h"
#include <Graphic.h>
#include "Graphic_Capsule.h"
#include "CommonLogic.h"
#include "../common/Char/CharManager/CharManager.h"
#include "../common/Char/CharCommon/Char-Common.h"
#include "../common/Char/CharClient/Char-Client.h"

CValentineWarEffect::CValentineWarEffect( TSpr *pValentineWarEffect )
{
	m_pValentineWarEffectTSPR = pValentineWarEffect;

	m_siValentineWarSprImageNum = pValentineWarEffect->GetImageNum();

	m_siDelayFrame = 3;

	m_siCurrentFrame = 0;

	m_ValentineWarClock  = 0;

	siCouple = 0;

}
CValentineWarEffect::~CValentineWarEffect()
{

}

void CValentineWarEffect::Action( SI32 siCouple )	// ��Ʈ����Ʈ�� �׷��� ���� ������ ���ڷ� ����
{
	if( siCouple <= 0 ) return; // �׷����� �ʴ� ��Ȳ�̶�� �׼� ����.

	if (TABS(pclClient->CurrentClock - m_ValentineWarClock ) > 50)
	{
		m_ValentineWarClock = pclClient->CurrentClock;

		if( m_siCurrentFrame > m_siValentineWarSprImageNum -1 )
		{
			m_siCurrentFrame = 0;
		}
		else
		{
			m_siCurrentFrame++;
		}
	}

}

void CValentineWarEffect::Draw( SI32 si32CenterXPos, SI32	si32CenterYPos )
{
	SI32 XPos= 0,YPos=0;
	if( siCouple <= 0 ) return; // �׷����� �ʴ� ��Ȳ�̶�� ���� ����.
	
	XPos = si32CenterXPos - m_pValentineWarEffectTSPR->GetXSize() / 2+1;

	if (pclClient->pclCM->CR[1]->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE== true) {//���� Ÿ�� �ִ� ���� �ε����� ������ ����ź�Ŵ�
		YPos = si32CenterYPos - m_pValentineWarEffectTSPR->GetYSize() / 2-2;
	}
	else{
		YPos = si32CenterYPos - m_pValentineWarEffectTSPR->GetYSize() / 2-16;
	}	
	GP.PutSpr(m_pValentineWarEffectTSPR, XPos, YPos, m_siCurrentFrame );    
}


