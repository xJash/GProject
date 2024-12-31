#include "Notice.h"
#include "..\Server.h"

#include "..\..\CommonLogic\CommonLogic.h"

#include "Char\CharManager\CharManager.h"


extern cltCommonLogic* pclClient;

cltNoticeManager::cltNoticeManager()
{
	bLoginNoticeSwitch	= false;
	//	strcpy(szLogInNotice, TEXT(""));
	for ( SI32 i = 0; i <MAX_NOTICE_NUM ; i++) 
	{
		Counting[i]	=	0	;
		Count[i]	=	0	;
	}

}

cltNoticeManager::~cltNoticeManager()
{

}


// ������ �߰��Ѵ�. 
void cltNoticeManager::Add(DWORD interval, TCHAR* ptext, SI32 siCount )
{
	SI32 i;

	if(interval  < 100 )		interval = 100;
	if(interval  >  1728000)	interval = 1728000;	// [��ȣ] 30��->24�ð� ����

	for(i = 0;i < MAX_NOTICE_NUM;i++)
	{
		if(clNotice[i].dwStartFrame == 0)
		{
			clNotice[i].Set(pclClient->GetFrame(), interval, ptext);
			Count[i]	=	siCount	;
			return ;
		}
	}

}


// ������ �����ش�. 
void cltNoticeManager::Action()
{
	SI32 i;

	cltServer* pclserver = (cltServer*)pclClient;

	for(i = 0;i < MAX_NOTICE_NUM;i++)
	{
		if(clNotice[i].dwStartFrame)
		{
			if((pclClient->GetFrame() - clNotice[i].dwStartFrame) % clNotice[i].dwInterval == 0)
			{
				if ( Count[i] > 0 && Count[i] >= 100 ) 
				{
					TCHAR* pText = GetTxtFromMgr(5482); 

					// ��ڰ� �ϴ°��̶�� ä��â���� ��Ÿ�����Ѵ�.
					//KHY - 0129 - �ϴ� ä��â�� ���� ��¿��θ� �����Ѵ�.
					cltGameMsgResponse_Notice clNotice(pText, clNotice[i].szNoticeText,true);
					cltMsg clMsg(	GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);

					pclClient->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);

					Counting[i]++;
				}
				else if( Count[i] > 0 )	// ī���� �ؼ� �Ѿ���� ���� ��Ų�� ī������ �ʱ�ȭ
				{
					//pclserver->SendNoticeMsg(-1, 0, 0, clNotice[i].szNoticeText);

					if ( Counting[i] >= Count[i] ) 
					{		
						Counting[i]	=	0	;
                        Count[i]	=	0	;
					}
					else
					{
						TCHAR* pText = GetTxtFromMgr(5482); 

						// ��ڰ� �ϴ°��̶�� ä��â���� ��Ÿ�����Ѵ�.
						//KHY - 0129 - �ϴ� ä��â�� ���� ��¿��θ� �����Ѵ�.
						cltGameMsgResponse_Notice clNotice(pText, clNotice[i].szNoticeText,true);
						cltMsg clMsg(	GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);

						pclClient->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);

						Counting[i]++;
					}				
				}
				else
				{
					// ī���� �ʱ�ȭ
					Counting[i]	=	0	;
					Count[i]	=	0	;

				}
			}
		}
	}
}


// ��� ������ �����. 
void cltNoticeManager::DelAllNotice()
{
	SI32 i;

	for(i = 0;i < MAX_NOTICE_NUM;i++)
	{
		clNotice[i].Init();
	}

}

// �α��� ������ on/ff
void cltNoticeManager::OnOffLogInNotice()
{
	if(bLoginNoticeSwitch)
	{
		bLoginNoticeSwitch = false;

	}
	else
	{
		bLoginNoticeSwitch = true;
		/*
		// ���� ������ �о�´�. 
		FILE* fp;
		TCHAR buffer[1024];

		strcpy(szLogInNotice , TEXT(""));

		fp = _tfopen(TEXT("Notice\\LogInNotice.txt"), TEXT("rt"));
		if(fp)
		{
		while(_fgetts(buffer, 1024, fp) != NULL)
		{
		for(SI32 i = 0; i < lstrlen(buffer);i++)
		{
		if(buffer[i] == '\n')
		{
		buffer[i] = ' ';
		}
		}

		strcat(szLogInNotice, buffer);
		strcat(szLogInNotice, TEXT("\r\n"));
		}

		fclose(fp);
		}

		*/		

	}
}
