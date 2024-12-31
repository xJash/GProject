//---------------------------------
// 2003/5/25 ���°�
//---------------------------------

#include "..\KindInfo\KindInfo.h"
#include "EtcTool\EtcTool.h"
#include "Graphic.h"
#include "Graphic_Capsule.h"


//---------------------------------------------------------
// cltAniInfo
//---------------------------------------------------------

cltAniInfo::cltAniInfo()
{
	siAniStep		= 0;
	siAniDelay		= 0;
	siAniDelayor	= 0	;

	siAniInstant		= 0;

	dwElapsedClock		= 0;
	dwAniStartClock	= 0;

	siRetryNum		= 0;

}

cltAniInfo::~cltAniInfo()
{
}

void cltAniInfo::Init1()
{
	siAniDelayor	= 0;
	siAniStep		= 0;

	dwElapsedClock		= 0;
	dwAniStartClock	= 0;

	siRetryNum		= 0;

}

BOOL cltAniInfo::IsInstant() const
{
	if(siAniStep >= siAniInstant)return TRUE;
	return FALSE;
}

void cltAniInfo::SetAniStep(SI32 step)
{
	siAniStep = step;
}

SI32 cltAniInfo::GetAniStep() const
{
	return siAniStep;
}

void cltAniInfo::IncreaseAniStep(SI32 amount)
{
	siAniStep +=amount;
}

void cltAniInfo::DecreaseAniStep(SI32 amount)
{
	siAniStep -=amount;
}

BOOL cltAniInfo::IsLast() const
{
	if(siAniStep >= siAniInstant)return TRUE;
	return FALSE;
}

SI32 cltAniInfo::GetAniDelayor() const			
{
	return siAniDelayor;
}

void cltAniInfo::SetAniDelayor(SI32 delayor)
{
	siAniDelayor = delayor;
}

void cltAniInfo::IncreaseAniDelayor(SI32 amount)
{
	siAniDelayor += amount;
}

void cltAniInfo::SetAniDelay(SI32 delay)
{
	siAniDelay = delay;
}

SI32 cltAniInfo::GetAniDelay() const
{
	return siAniDelay;
}

void cltAniInfo::SetAniInstant(SI32 instant)
{
	siAniInstant = instant;
}

SI32 cltAniInfo::GetAniInstant() const
{
	return siAniInstant;
}

//---------------------------------------------------------
// cltCharAnimationManager
//---------------------------------------------------------
cltCharAnimationManager::cltCharAnimationManager()
{
	SI32 i;

	
	for(i = 0;i < MAX_IMG_FILE_PER_KIND;i++)
	{
		pszFileName[i]	= NULL;
		pSpr[i]			= NULL;
	}

	for(i = 0;i < MAX_ANINUM_PER_KIND;i++)
	{
		pclCharAni[i] = NULL;

	}
}

cltCharAnimationManager::~cltCharAnimationManager()
{
	SI32 i;


	for(i = 0;i < MAX_IMG_FILE_PER_KIND;i++)
	{
		if(pszFileName[i])
		{
			delete[] pszFileName[i];
			pszFileName[i] = NULL;
		}

		if(pSpr[i])
		{
			delete pSpr[i];
			pSpr[i] = NULL;
		}
	}

	for(i = 0;i < MAX_ANINUM_PER_KIND;i++)
	{
		if(pclCharAni[i])
		{
			delete pclCharAni[i];
			pclCharAni[i] = NULL;
		}
	}

}

SI32 cltCharAnimationManager::siLodedSize = 0;


BOOL cltCharAnimationManager::Add(SI32 Ani, BOOL DirSwitch, TCHAR* FileName, SI32 Font, SI32 Frame,
								  SI32 Instant, SI32 Delay, SI32 atb, SI32 EffectFont ,SI32 transmode,
								  SI08 alphavalue,SI32 ShadowAni,SI32 ShadowFont)
{
	
	if( pclCharAni[Ani] == NULL )
	{
		pclCharAni[Ani] = new cltCharAnimation(this);
		
		pclCharAni[Ani]->Set(Ani, DirSwitch, Frame, FileName, Font, Instant,
							 Delay, atb, EffectFont,transmode,alphavalue,ShadowAni,ShadowFont);
		return TRUE;
	}

	return FALSE;
}

BOOL cltCharAnimationManager::SetShadowIndentXY(SI32 anitype ,SI32 psiX , SI32 psiY)
{
	if(pclCharAni[anitype])
	{
		pclCharAni[anitype]->SetShadowIndentXY(psiX,psiY);

		return TRUE ;
	}

	MsgBox(TEXT("cltCharAnimationManager::SetShadowIndentXY"), TEXT("%d"), anitype);
	return FALSE ;
}

BOOL cltCharAnimationManager::DecideDrawImg(SI32 anitype, SI32 dir, cltAniInfo claniinfo, DWORD currentclock,
 											TSpr** ppspr, int* pfont, bool * preverseswitch, SI32 *psiEffectFont ,
											SI32 * psiShadowAni,SI32 * psiShadowFont)
{
	if(pclCharAni[anitype])
	{
		pclCharAni[anitype]->DecideDrawImg(dir, claniinfo, currentclock, ppspr,
										   pfont, preverseswitch, psiEffectFont ,psiShadowAni,psiShadowFont);	
		
		return TRUE;
	}

	MsgBox(TEXT("cltCharAnimationManager::DecideDrawImg"), TEXT("%d %d %d"), anitype, dir, claniinfo.GetAniStep());
	return FALSE;
}

void cltCharAnimationManager::GetShadowIndentXY(SI32 anitype , SI32 * psiX , SI32 * psiY)
{
	if(pclCharAni[anitype])
	{
		pclCharAni[anitype]->GetShadowIndentXY(psiX,psiY);

		return ;
	}

	MsgBox(TEXT("cltCharAnimationManager::GetShadowIndentXY"), TEXT("%d"), anitype);
}

SI32 cltCharAnimationManager::GetFrameNum(SI32 ref)	
{
	if(pclCharAni[ref] == NULL)return 0;
	return pclCharAni[ref]->GetFrameNum();
}

SI32 cltCharAnimationManager::GetImageXsize(SI32 ref, DWORD currentclock )
{
	return pclCharAni[ref]->GetImageXsize(currentclock);
}

SI32 cltCharAnimationManager::GetImageYsize(SI32 ref, DWORD currentclock )
{
	return pclCharAni[ref]->GetImageYsize(currentclock);
}

// ������ �ʴ� ������ �����Ѵ�. 
void cltCharAnimationManager::DeleteIfNotUse(DWORD curclock)
{
	SI32 i;

	for(i = 0;i < MAX_ANINUM_PER_KIND;i++)
	{
		if(pclCharAni[i] == NULL)continue;
		if(pclCharAni[i]->pSpr == NULL)continue;
		if(pclCharAni[i]->pSpr->pImage == NULL)continue;
		
		// ��ȿ�� �̹����� �ִٸ�, 
		if(TABS(curclock - pclCharAni[i]->dwLastUseClock) < 300000)
		{
			return ;
		}
	}

	for(i = 0;i < MAX_ANINUM_PER_KIND;i++)
	{
		if(pclCharAni[i] == NULL)continue;
		if(pclCharAni[i]->pSpr == NULL)continue;
		if(pclCharAni[i]->pSpr->pImage == NULL)continue;
		
		siLodedSize -= pclCharAni[i]->pSpr->GetImageDataSize();
		
		GP.FreeSpr(*pclCharAni[i]->pSpr);
	}

}

BOOL cltCharAnimationManager::GetDirSwitch(SI32 anitype)
{
	if(anitype <= 0)return FALSE;

	if(pclCharAni[anitype])
	{
		return pclCharAni[anitype]->bDirSwitch ;
	}

	return FALSE;
}

SI32 cltCharAnimationManager::FindRefFromAnitype(SI32 anitype)
{
	if(anitype <= 0)return -1;

	if(pclCharAni[anitype])
	{
		return anitype;
	}

	return -1;
}

// ù��° �ִϸ��̼��� ã�´�. 
SI32 cltCharAnimationManager::FindFirstAni()
{
	for(SI32 i = 0;i < MAX_ANINUM_PER_KIND;i++)
	{
		if(pclCharAni[i])return i;
	}
	return -1;
}

#ifdef _SAFE_MEMORY
	SI32 cltCharAnimationManager::GetDelay(SI32 ref)
#else
	SI32 cltCharAnimationManager::GetDelay(SI32 ref)		const
#endif
{
	return pclCharAni[ref]->siDelay;
}

#ifdef _SAFE_MEMORY
	SI32 cltCharAnimationManager::GetInstant(SI32 ref)
#else
	SI32 cltCharAnimationManager::GetInstant(SI32 ref)	const
#endif
{
	return pclCharAni[ref]->siInstant;
}

//---------------------------------------------------------
// cltCharAnimation
//---------------------------------------------------------
cltCharAnimation::cltCharAnimation(cltCharAnimationManager* pclanimng)
{
	ZeroMemory(this, sizeof(cltCharAnimation));

	pclAniMng = pclanimng;

}

cltCharAnimation::~cltCharAnimation()
{

}

SI32 cltCharAnimation::GetAniType() const
{
	return siAniType;
};


void cltCharAnimation::Set(SI32 sianitype, BOOL dirswitch, SI32 framenum, TCHAR* filename,
						   SI32 font, SI32 instant, SI32 delay, SI32 atb, SI32 EffectFont,SI32 transmode,
						   SI08 alphavalue, SI32 ShadowAni,SI32 ShadowFont)
{
	SI32 i;

	siAniType		= sianitype;
	bDirSwitch		= dirswitch;
    siFrameNum		= framenum;
	siFont			= font;
	siInstant		= instant;
	siDelay			= delay;
	siAtb			= atb;
	siEffectFont	= EffectFont;
	siTransMode		= transmode ;
	siAlphaValue	= alphavalue ;
	siShadowAni		= ShadowAni ;
	siShadowFont	= ShadowFont ;

	pSpr			= NULL;
	siRef			= -1;

	// ���� �̸��� ���� �̹����� �̹� �ִ��� Ȯ���Ѵ�. 
	for(i = 0;i < MAX_IMG_FILE_PER_KIND;i++)
	{
		if(pclAniMng->pszFileName[i] && _tcscmp(filename, pclAniMng->pszFileName[i]) == 0)
		{
			pSpr	= pclAniMng->pSpr[i];
			siRef	= i;
			break;
		}
	}

	// ������ ��ϵ� ���� �ƴ϶�� �� ������ �ִ��� Ȯ���Ѵ�.
	if(siRef == -1)
	{
		for(i = 0;i < MAX_IMG_FILE_PER_KIND;i++)
		{
			if(pclAniMng->pszFileName[i] == NULL)
			{
				// ���� �̸��� ���� ������ ����� ������ �����Ѵ�. 
				pclAniMng->pszFileName[i]	= new TCHAR[lstrlen(filename) + 1];
				pclAniMng->pSpr[i]			= new TSpr;

				if(pclAniMng->pszFileName[i] && pclAniMng->pSpr[i])
				{
					StringCchCopy(pclAniMng->pszFileName[i], lstrlen(filename) + 1, filename);
					pSpr	= pclAniMng->pSpr[i];
					siRef	= i;
					break;
				}
				else
				{
					MsgBox(TEXT("vcecxd"), TEXT("Vdfsd:%s"), filename);
				}
			}
		}
	}

	if(siRef == -1)
	{
#ifdef _DEBUG
		MsgBox("ERROR", "���̻� �̹����� �Ҵ��� �� �����ϴ�.");
#endif
	}

}


SI32 cltCharAnimation::GetFrameNum()
{
	if(siFrameNum == 0)return 0;

	if(siAtb & ANIATB_SINGLEFRAME)
	{
		return 1;
	}

	return siFrameNum;
}

BOOL cltCharAnimation::IsReady(SI32 step)
{
	if(step >= siInstant)
	{
		return TRUE;
	}
	return FALSE;
}

SI32 cltCharAnimation::GetImageXsize(DWORD currentclock)
{
	// �̹����� ���� �غ���� ���� ���¶�� �غ��Ѵ�. 
	Load(currentclock);
	if(pSpr == NULL || pSpr->pImage == NULL)return 0;

	return pSpr->GetXSize();
}

SI32 cltCharAnimation::GetImageYsize(DWORD currentclock)
{
	// �̹����� ���� �غ���� ���� ���¶�� �غ��Ѵ�. 
	Load(currentclock);
	if(pSpr == NULL || pSpr->pImage == NULL)return 0;

	return pSpr->GetYSize();
}

// ����� �̹����� �׷��� ������ ȹ���Ѵ�. 
void cltCharAnimation::DecideDrawImg(SI32 dir, cltAniInfo claniinfo, DWORD currentclock, TSpr** ppspr,
									 int* return_font, bool * return_reverseswitch, SI32 *psiEffectFont,
									 SI32 * psiShadowAni , SI32 * psiShadowFont)
{
	SI32 font = 0;
	bool reverseswitch = FALSE;

	if (claniinfo.GetAniStep() >= GetFrameNum())
	{
		claniinfo.SetAniStep( claniinfo.GetAniStep() % GetFrameNum() );
	}


	if(bDirSwitch==TRUE)
	{
		if(siAtb & ANIATB_DIR16)
		{
			switch(dir)
			{
			case SOUTH:
				reverseswitch=FALSE;
				font=siFont+siFrameNum * 2 + claniinfo.GetAniStep();
				break;
			case SOUTH|WEST:
				reverseswitch=FALSE;
				font=siFont+siFrameNum * 4 + claniinfo.GetAniStep();
				break;
			case WEST:
				reverseswitch=FALSE;
				font=siFont+siFrameNum * 6 + claniinfo.GetAniStep();
				break;
			case NORTH|WEST:
				reverseswitch=FALSE;
				font=siFont+siFrameNum * 8 + claniinfo.GetAniStep();
				break;
			case NORTH:
				reverseswitch=TRUE;
				font=siFont+siFrameNum * 6 + claniinfo.GetAniStep();
				break;
			case NORTH|EAST:
				reverseswitch=TRUE;
				font=siFont+siFrameNum * 4 + claniinfo.GetAniStep();
				break;
			case EAST:
				reverseswitch=TRUE;
				font=siFont+siFrameNum * 2 + claniinfo.GetAniStep();
				break;
			case EAST|SOUTH:
				reverseswitch=FALSE;
				font=siFont+siFrameNum * 0 + claniinfo.GetAniStep();
				break;
			case SSW:
				reverseswitch=FALSE;
				font=siFont+siFrameNum * 3 + claniinfo.GetAniStep();
				break;
			case EEN:
				reverseswitch=TRUE;
				font=siFont+siFrameNum * 3 + claniinfo.GetAniStep();
				break;
			case WWS:
				reverseswitch=FALSE;
				font=siFont+siFrameNum * 5 + claniinfo.GetAniStep();
				break;
			case NNE:
				reverseswitch=TRUE;
				font=siFont+siFrameNum * 5 + claniinfo.GetAniStep();
				break;
			case WWN:
				reverseswitch=FALSE;
				font=siFont+siFrameNum * 7 + claniinfo.GetAniStep();
				break;
			case NNW:
				reverseswitch=TRUE;
				font=siFont+siFrameNum * 7 + claniinfo.GetAniStep();
				break;
			case SSE:
				reverseswitch=FALSE;
				font=siFont+siFrameNum * 1 + claniinfo.GetAniStep();
				break;
			case EES:
				reverseswitch=TRUE;
				font=siFont+siFrameNum * 1 + claniinfo.GetAniStep();
				break;
			default:
				font=claniinfo.GetAniStep();
				break;
			}
		}
		else if(siAtb & ANIATB_DIR2)
		{
			switch(dir)
			{
			case SOUTH:
			case WEST:
			case SOUTH|WEST:
			case NORTH|WEST:
				reverseswitch=FALSE; 
				font = siFont + siFrameNum * 0 + claniinfo.GetAniStep();     
				break;
			case NORTH:
			case EAST:
			case EAST|SOUTH:
			case EAST|NORTH:
				reverseswitch=TRUE;  
				font=siFont+siFrameNum * 0 + claniinfo.GetAniStep();
				break;
			default:
				break;
			}

				/*TCHAR buffer[256];
				sprintf(buffer, TEXT("%d"), claniinfo.GetAniStep());
				pclClient->pclMessage->SetMsg(buffer);
				*/
				
			

		}
		else
		{
			switch(dir)
			{
			case SOUTH:
				reverseswitch=FALSE;
				font=siFont + siFrameNum*1+claniinfo.GetAniStep();
				break;
			case SOUTH|WEST:
				reverseswitch=FALSE;
				font=siFont+siFrameNum*2+claniinfo.GetAniStep();
				break;
			case WEST:
				reverseswitch=FALSE;
				font=siFont+siFrameNum*3+claniinfo.GetAniStep();
				break;
			case NORTH|WEST:
				reverseswitch=FALSE;
				font=siFont+siFrameNum*4+claniinfo.GetAniStep();
				break;
			case NORTH:
				reverseswitch=TRUE;
				font=siFont+siFrameNum*3+claniinfo.GetAniStep();
				break;
			case NORTH|EAST:
				reverseswitch=TRUE;
				font=siFont+siFrameNum*2+claniinfo.GetAniStep();
				break;
			case EAST:
				reverseswitch=TRUE;
				font=siFont+siFrameNum*1+claniinfo.GetAniStep();
				break;
			case EAST|SOUTH:
				reverseswitch=FALSE;
				font=siFont+siFrameNum*0+claniinfo.GetAniStep();
				break;
			default:
				font=0;
				break;
			}
		}
	}
	else
	{
		reverseswitch=FALSE;
		font = siFont + claniinfo.GetAniStep();
	}	

	// �̹����� ���� �غ���� ���� ���¶�� �غ��Ѵ�. 
	Load(currentclock);

	*ppspr					= pSpr;
	*return_font			= font;
	*return_reverseswitch	= reverseswitch;
	

	//------------ Ư�� ȿ���� �ִٸ� Ư�� ȿ���� ���� ��ġ�� ���� �ش�.	
	if ( siEffectFont >= 0 )
	{
		*psiEffectFont = (siEffectFont - siFont) + font;
	}
	//------------ Ư�� ȿ���� ���ٸ� -1�� �����ش�.
	else
	{
		*psiEffectFont = -1;
	}

	// SJY
	//------------- ���� �׷��� ����(ShadowAni)�� �ִٸ� ���� ��ġ�� ���� �׷��� ������ �����ش�.
	if ( psiShadowAni != NULL && psiShadowFont != NULL )
	{
		if ( siShadowAni > 0 && siShadowFont >= 0 )
		{
			*psiShadowAni = siShadowAni ;
			*psiShadowFont = (siShadowFont - siFont) + font;
		}
		else // ������ 0�� -1�� �����ش�.
		{
			*psiShadowAni = 0 ;
			*psiShadowFont = -1 ;
		}
	}
}

// ����� �̹����� �׷��� ������ ȹ���Ѵ�. 
void cltCharAnimation::GetShadowIndentXY(SI32 * psiX , SI32 * psiY)
{
	if ( psiX != NULL && psiY != NULL )
	{
		*psiX = siShadowXIndent ;
		*psiY = siShadowYIndent ;
	}
}

void cltCharAnimation::SetShadowIndentXY(SI32 psiX , SI32 psiY)
{
	siShadowXIndent	= psiX ;
	siShadowYIndent	= psiY ;
}

// �̹����� �ε��Ѵ�. �̹� �ε��� ��쿡�� �ε����� �ʴ´�. 
BOOL cltCharAnimation::Load(DWORD currentclock)
{
	if(pSpr == NULL)
	{
		MsgBox(TEXT("cltCharAnimation::Load"),TEXT("13975:anitype:%d ref:%d"), siAniType, siRef);
		return FALSE;
	}

	// ���� �ð��� ����Ѵ�. 
	dwLastUseClock = currentclock;

	if(pSpr->pImage == NULL && pclAniMng->pszFileName[siRef])
	{
		BOOL brtn = GP.LoadSprFromFile(pclAniMng->pszFileName[siRef], pSpr);
		cltCharAnimationManager::siLodedSize += pSpr->GetImageDataSize();
		return brtn;
	}

	return FALSE;
}
