#include "FourLeafEffect.h"
#include <Graphic.h>
#include "Graphic_Capsule.h"
#include "CommonLogic.h"
#include "../common/Char/CharManager/CharManager.h"
#include "../common/Char/CharCommon/Char-Common.h"
#include "../common/Char/CharClient/Char-Client.h"

CFourLeafEffect::CFourLeafEffect( TSpr *pFourLeafEffect )
{
	m_pFourLeafEffectTSPR = pFourLeafEffect;

	m_siFourLeafSprImageNum = pFourLeafEffect->GetImageNum();

	m_siDelayFrame = 3;

	m_siCurrentFrame = 0;

	m_FourLeafClock  = 0;

	m_bFourLeafEffect = false;

}
CFourLeafEffect::~CFourLeafEffect()
{

}

void CFourLeafEffect::Action( bool bFourLeafEffect )	// ��Ʈ����Ʈ�� �׷��� ���� ������ ���ڷ� ����
{
	m_bFourLeafEffect = bFourLeafEffect;

	if( m_bFourLeafEffect == false ) return; // �׷����� �ʴ� ��Ȳ�̶�� ���� ����.

	if (TABS(pclClient->CurrentClock - m_FourLeafClock ) > 50)
	{
		m_FourLeafClock = pclClient->CurrentClock;

		if( m_siCurrentFrame > m_siFourLeafSprImageNum -1 )
		{
			m_siCurrentFrame = 0;
		}
		else
		{
			m_siCurrentFrame++;
		}
	}

}

void CFourLeafEffect::Draw( SI32 si32CenterXPos, SI32	si32CenterYPos )
{
	SI32 XPos= 0,YPos=0;
	if ( m_bFourLeafEffect == false )	return; // �׷����� �ʴ� ��Ȳ�̶��  �׸��� ����.
	
	XPos = si32CenterXPos - m_pFourLeafEffectTSPR->GetXSize() / 2+1;

//KHY - 1001 - ��µ��� 5���� ���� ����.
//	if (pclClient->pclCM->CR[1]->pclCI->clHorseInfo.siCurrentHorseIndex!= NULL) {//���� Ÿ�� �ִ� ���� �ε����� ������ ����ź�Ŵ�
	if (pclClient->pclCM->CR[1]->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE== true) {//���� Ÿ�� �ִ� ���� �ε����� ������ ����ź�Ŵ�
		YPos = si32CenterYPos - m_pFourLeafEffectTSPR->GetYSize() / 2-2;
	}
	else{
		YPos = si32CenterYPos - m_pFourLeafEffectTSPR->GetYSize() / 2-16;
	}//���ƾ� ��û�� ���ؼ� ���� ſ�� ��� ��ź��ŭ ����Ŭ�ι��� ��ġ�� ��ȭ��.[2007.07.26 �ռ���]
	
	GP.PutSpr(m_pFourLeafEffectTSPR, XPos, YPos, m_siCurrentFrame );    
}


