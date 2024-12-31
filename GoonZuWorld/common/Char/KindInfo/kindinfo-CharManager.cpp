//---------------------------------
// 2004/4/17 ���°�
//---------------------------------

#include "../../../CommonLogic/CommonLogic.h"

#include "../../Client/Music/Music.h"

#include "KindInfo.h"
#include "../../../CommonLogic/AttackType/AttackType.h"
#include "../../../CommonLogic/MagicMgr/MagicMgr.h"
#include "../../../CommonLogic/MagicMgr/MagicAttribute/MagicAttribute.h"
#include "../../../CommonLogic/CityHall/CityHall.h"
#include "../../../common/Skill/Skill-Manager.h"
#include "Char/CharCommon/Char-Common.h"
#include "Char/CharClient/Char-Client.h"

//--------------------------------------
// Common
//--------------------------------------
#include "PersonInfo.h"
#include "../CharManager/CharManager.h"

#include "NDataLoader.h"
#include "NHashTableString.h"

extern cltCommonLogic* pclClient;

void cltKindInfoSet::AddCharKindInfoSetFromFile()
{
	cltKIDrawInfo				clKIDrawInfo;
	cltKIEffectInfo				clKIEffectInfo;
	cltKindHireCondition		clHireCond;
	cltBossItemInfo				clbossitem;

	NDataAtbParser  atbparser, blockatbparser, saatbparser;

	// Char ATB ���
	atbparser.AddAtbInfo( TEXT("ATB_MOVE"), ATB_MOVE);
	atbparser.AddAtbInfo( TEXT("ATB_HERO"), ATB_HERO);
	atbparser.AddAtbInfo( TEXT("ATB_ATTACK"), ATB_ATTACK);
	atbparser.AddAtbInfo( TEXT("ATB_WEAKENEMYNOATTACK"), ATB_WEAKENEMYNOATTACK);
	atbparser.AddAtbInfo( TEXT("ATB_FISH"), ATB_FISH);
	atbparser.AddAtbInfo( TEXT("ATB_NOJJIM"), ATB_NOJJIM);
	//atbparser.AddAtbInfo( TEXT("ATB_MINRANGE"), ATB_MINRANGE);
	atbparser.AddAtbInfo( TEXT("ATB_HORSE"), ATB_HORSE);
	atbparser.AddAtbInfo( TEXT("ATB_SYSTEMNPC"), ATB_SYSTEMNPC);
	atbparser.AddAtbInfo( TEXT("ATB_SELFBOMB"), ATB_SELFBOMB);
	atbparser.AddAtbInfo( TEXT("ATB_WAITSELFBOMB"), ATB_WAITSELFBOMB);
	atbparser.AddAtbInfo( TEXT("ATB_NONPCLIST"), ATB_NONPCLIST);
	atbparser.AddAtbInfo( TEXT("ATB_COWORK"), ATB_COWORK);
	atbparser.AddAtbInfo( TEXT("ATB_MONSTER"), ATB_MONSTER);
	atbparser.AddAtbInfo( TEXT("ATB_GOD"), ATB_GOD);
	atbparser.AddAtbInfo( TEXT("ATB_DEFAULTGOD"), ATB_DEFAULTGOD);
	atbparser.AddAtbInfo( TEXT("ATB_DEFAULTCASTLE"), ATB_DEFAULTCASTLE);
	atbparser.AddAtbInfo( TEXT("ATB_DAILYQUEST"), ATB_DAILYQUEST);
	atbparser.AddAtbInfo( TEXT("ATB_WARMONSTER"), ATB_WARMONSTER);
	atbparser.AddAtbInfo( TEXT("ATB_EVENTXBOX"), ATB_EVENTXBOX);
	atbparser.AddAtbInfo( TEXT("ATB_CLONE"), ATB_CLONE);
	atbparser.AddAtbInfo( TEXT("ATB_DEFAULTSUMMON"), ATB_DEFAULTSUMMON);
	atbparser.AddAtbInfo( TEXT("ATB_HIREABLE"), ATB_HIREABLE);
	atbparser.AddAtbInfo( TEXT("ATB_BOSS"), ATB_BOSS);
	atbparser.AddAtbInfo( TEXT("ATB_FARM"), ATB_FARM);
	atbparser.AddAtbInfo( TEXT("ATB_DAMAGELIMIT"), ATB_DAMAGELIMIT);
	atbparser.AddAtbInfo( TEXT("ATB_MINE"), ATB_MINE);
	atbparser.AddAtbInfo( TEXT("ATB_NOHEALTHBAR"), ATB_NOHEALTHBAR);
	atbparser.AddAtbInfo( TEXT("ATB_NOICE"), ATB_NOICE);
	atbparser.AddAtbInfo( TEXT("ATB_TRANSFORM"), ATB_TRANSFORM);		// [���� : Ȳ���� 2007. 12. 28 => ���� ATB]
	atbparser.AddAtbInfo( TEXT("ATB_EVENT"), ATB_EVENT);
	atbparser.AddAtbInfo( TEXT("ATB_DAILYQUEST2"), ATB_DAILYQUEST2);	// ���ϸ�����Ʈ2 ATB�߰�.
	atbparser.AddAtbInfo( TEXT("ATB_SUMMONSTAMINASTATIC"), ATB_SUMMONSTAMINASTATIC);	// ��ȯ�� ���¹̳� �߰�.

	// ServiceArea ATB ���
	saatbparser.AddAtbInfo( TEXT("SERVICEAREA_ATB_KOREA"),		SERVICEAREA_ATB_KOREA);
	saatbparser.AddAtbInfo( TEXT("SERVICEAREA_ATB_CHINA"),		SERVICEAREA_ATB_CHINA);
	saatbparser.AddAtbInfo( TEXT("SERVICEAREA_ATB_JAPAN"),		SERVICEAREA_ATB_JAPAN);
	saatbparser.AddAtbInfo( TEXT("SERVICEAREA_ATB_ENGLISH"),	SERVICEAREA_ATB_ENGLISH);
	saatbparser.AddAtbInfo( TEXT("SERVICEAREA_ATB_TAIWAN"),		SERVICEAREA_ATB_TAIWAN);
	saatbparser.AddAtbInfo( TEXT("SERVICEAREA_ATB_USA"),		SERVICEAREA_ATB_USA);
	saatbparser.AddAtbInfo( TEXT("SERVICEAREA_ATB_NHNCHINA"),	SERVICEAREA_ATB_NHNCHINA);
	saatbparser.AddAtbInfo( TEXT("SERVICEAREA_ATB_EUROPE"),		SERVICEAREA_ATB_EUROPE);

	// BLock ATB ���
	blockatbparser.AddAtbInfo( TEXT("BLOCK_NONE"), BLOCK_NONE);
	blockatbparser.AddAtbInfo( TEXT("BLOCK_DEEPWATER"), BLOCK_DEEPWATER);
	blockatbparser.AddAtbInfo( TEXT("BLOCK_SHALLOWWATER"), BLOCK_SHALLOWWATER);
	blockatbparser.AddAtbInfo( TEXT("BLOCK_NORMAL"), BLOCK_NORMAL);
	blockatbparser.AddAtbInfo( TEXT("BLOCK_LAND"), BLOCK_LAND);
	blockatbparser.AddAtbInfo( TEXT("BLOCK_CUSTOM"), BLOCK_CUSTOM);
	blockatbparser.AddAtbInfo( TEXT("BLOCK_EVENT1"), BLOCK_EVENT1);
	blockatbparser.AddAtbInfo( TEXT("BLOCK_EVENT2"), BLOCK_EVENT2);
	blockatbparser.AddAtbInfo( TEXT("BLOCK_EVENT3"), BLOCK_EVENT3);
	blockatbparser.AddAtbInfo( TEXT("BLOCK_EVENT4"), BLOCK_EVENT4);
	blockatbparser.AddAtbInfo( TEXT("BLOCK_EVENT5"), BLOCK_EVENT5);
	blockatbparser.AddAtbInfo( TEXT("BLOCK_EVENT6"), BLOCK_EVENT6);
	blockatbparser.AddAtbInfo( TEXT("BLOCK_EVENT7"), BLOCK_EVENT7);

	NDataLoader dataloader;
	BOOL bLoadFile = FALSE;
  
	//KHY - 0810 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/KindInfo_Create.txt") );
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/KindInfo_Create.txt") );
	}


	if (!bLoadFile)
		MsgBox(TEXT("Error"),TEXT("Not Found KindInfo_Create.txt"));

	TCHAR transparent[128]=TEXT(""), hiteffect[128]=TEXT(""), attackeffect[128]=TEXT("");
	TCHAR attackeffect1[128]=TEXT(""), dyingeffect[128]=TEXT("");
	TCHAR selecteffect1[128]=TEXT(""), selecteffect2[128]=TEXT(""), selecteffect3[128]=TEXT("");
	TCHAR kindtype[128]=TEXT(""), szcode[128]=TEXT(""), siblock[128]=TEXT(""), catb[128]=TEXT(""), csaAtb[256]=TEXT(""),
		defenceatb[128]=TEXT(""), country[128]=TEXT("");
	TCHAR *pText;

	int itransparent, ihiteffect, iattackeffect, iattackeffect1, idyingeffect;
	int iseleceeffect1, iseleceeffect2, iseleceeffect3;
	int iKindType, isiblock, idefenceatb, icountry;
	DWORD datb, saAtb, blockatb;

	int portrait=0, headnamefont=0, bottomindent=0, xpercent=0, ypercent=0, hideshadow=0, alphavalue=0;
	int movespeed=0,sisize=0, vibrateswitch=0, name=0, basicmoney=0, minvillage=0, sex=0;
	int swordop=0, spearop=0, axeop=0, bowop=0, gunop=0, staffop=0, cannonop=0;

	BOOL bFind;

	SI32 siSortNum;			// ��ȹ�ʿ��� ����ϴ� �����ͷ� ���α׷����� ������� ����

	NDataTypeInfo pCreateInfo [] =
	{
		//KI_Create
			NDATA_MBSTRING,	kindtype,			128,
			NDATA_MBSTRING,	szcode,				128,
			NDATA_INT32,	&siSortNum, 		4,	// ��ȹ�ʿ��� ����ϴ� �����ͷ� ���α׷����� ������� ����
			NDATA_INT32,	&movespeed, 		4,
			NDATA_INT32,	&sisize,			4,
			NDATA_MBSTRING,	siblock,			128,
			NDATA_MBSTRING,	catb,				128,
			NDATA_MBSTRING,	csaAtb,				256,
			NDATA_MBSTRING,	defenceatb, 		128,
			NDATA_INT32,	&vibrateswitch,		4,
			NDATA_INT32,	&name,				4,
			NDATA_MBSTRING,	country,			128,
			NDATA_INT32,	&basicmoney,		4,
			NDATA_INT32,	&minvillage,		4,
			NDATA_INT32,	&sex,				4,
			NDATA_INT32,	&swordop,			4,
			NDATA_INT32,	&spearop,			4,
			NDATA_INT32,	&axeop,				4,
			NDATA_INT32,	&bowop,				4,
			NDATA_INT32,	&gunop,				4,
			NDATA_INT32,	&staffop,			4,
			NDATA_INT32,	&cannonop,			4,
			//KI_Draw_Effect
			NDATA_INT32,	&portrait,			4,
			NDATA_INT32,	&headnamefont,		4,
			NDATA_INT32,	&bottomindent,		4,
			NDATA_INT32,	&xpercent,			4,
			NDATA_INT32,	&ypercent,			4,
			NDATA_MBSTRING, transparent,		128,
			NDATA_INT32,	&hideshadow,		4,
			NDATA_INT32,	&alphavalue,		4,
			NDATA_MBSTRING, hiteffect,			128,
			NDATA_MBSTRING, attackeffect,		128,
			NDATA_MBSTRING,	attackeffect1,		128,
			NDATA_MBSTRING, dyingeffect,		128,
			NDATA_MBSTRING, selecteffect1,		128,
			NDATA_MBSTRING, selecteffect2,		128,
			NDATA_MBSTRING, selecteffect3,		128,
			0,0,0
	};

	dataloader.RegDataType(pCreateInfo);

	while (!dataloader.IsEndOfData()) 
	{
		itransparent=0; ihiteffect=0; iattackeffect=0; iattackeffect1=0; idyingeffect=0; 
		iseleceeffect1=0; iseleceeffect2=0; iseleceeffect3=0; iKindType=0; isiblock=0; datb=0; idefenceatb=0; icountry=0;

		if (dataloader.ReadData( true ))
		{
			if (!kindtype[ 0 ] == NULL)
			{
				bFind = pclClient->pclHashTableString->Find(kindtype, iKindType);

				if (!bFind)
					MsgBox(TEXT("Error"), TEXT("Not Found KindInfo_DrawEffect(%s) in HashTable"), kindtype);

				blockatb = blockatbparser.GetValueByString(siblock);
				isiblock = blockatb;

				datb = atbparser.GetValueByString(catb);
				saAtb = saatbparser.GetValueByString(csaAtb);

				//KI_create
				pclClient->pclHashTableString->Find(defenceatb, idefenceatb);
				pclClient->pclHashTableString->Find(country, icountry);

				//KI_Draw_Effect
				pclClient->pclHashTableString->Find(transparent, itransparent);
				pclClient->pclHashTableString->Find(hiteffect, ihiteffect);
				pclClient->pclHashTableString->Find(attackeffect, iattackeffect);
				pclClient->pclHashTableString->Find(attackeffect1, iattackeffect1);
				pclClient->pclHashTableString->Find(dyingeffect, idyingeffect);
				pclClient->pclHashTableString->Find(selecteffect1, iseleceeffect1);
				pclClient->pclHashTableString->Find(selecteffect2, iseleceeffect2);
				pclClient->pclHashTableString->Find(selecteffect3, iseleceeffect3);

				clKIDrawInfo.Set(portrait, headnamefont, bottomindent, PERCENT(xpercent), PERCENT(ypercent), itransparent, DATA_TO_BOOL(hideshadow));
				clKIEffectInfo.Set(ihiteffect, iattackeffect, iattackeffect1, idyingeffect, iseleceeffect1, iseleceeffect2, iseleceeffect3);
				clHireCond.Init(basicmoney, minvillage);
				clbossitem.Init();
				
				if (name != 0)
					pText = GetTxtFromMgr(name);
				else
					pText = TEXT("�׽�Ʈ");

				// ���⿡�� �޸𸮰� ���ٰ� ���� �Ǹ� KindInfo_Create.txt�� �ش� ī�ε尡 2���̻� ���ǵǾ� �ִ��� ���� Ȯ������ -kkm
				pclKI[ iKindType ] = new cltKindInfo(szcode, &clKIDrawInfo, &clKIEffectInfo,&clHireCond, &clbossitem,
					MOVESPEED(movespeed), SIZE(sisize), isiblock, datb, saAtb, idefenceatb, vibrateswitch, pText, icountry);

				pclKI[ iKindType ]->siSex = sex;

				// pclGMCommandKindInfo new�� ����.
				pclGMCommandKindInfo[ iKindType ] = new cltGMCommandKindInfo();

				if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
				{
#ifdef _DEBUG
					if( pclSummonKI[ iKindType ] != NULL )
					{
						NTCHARStringBuilder	build;
						build.SetFormat("[KindInfo_Create.txt]�� ������ �����. KIND={1}") << szcode;
						MessageBox(NULL, build, "ERROR", MB_OK);
					}
#else
					pclSummonKI[ iKindType ] = NULL;
#endif
					pclSummonKI[ iKindType ] = new cltKindInfo(	szcode, 
																&clKIDrawInfo, 
																&clKIEffectInfo,
																&clHireCond, 
																&clbossitem,
																MOVESPEED(movespeed), 
																SIZE(sisize), 
																isiblock,
																datb,
																saAtb,
																idefenceatb,
																vibrateswitch,
																pText,
																icountry);
					if(pclSummonKI[ iKindType ])
						pclSummonKI[ iKindType ]->siSex = sex;
				}
			}
		}
	}

	//KHY - 0810 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/KindInfo_BossItem.txt") );
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/KindInfo_BossItem.txt") );
	}



	if (!bLoadFile)
		MsgBox(TEXT("Error"),TEXT("Not Found KindInfo_BossItem.txt"));

	int itemunique=0, rate=0;

	// ���� ������ �߰�
	NDataTypeInfo pBossItem[] =
	{
			NDATA_MBSTRING,	kindtype,		128,
			NDATA_INT32,	&itemunique,	4,
			NDATA_INT32,	&rate,			4,
			0,0,0
	};

	dataloader.RegDataType(pBossItem);

	while (!dataloader.IsEndOfData()) 
	{
		if (dataloader.ReadData())
		{
			if (!kindtype[ 0 ] == NULL)
			{
				bFind = pclClient->pclHashTableString->Find(kindtype, iKindType);

				if (!bFind)
					MsgBox(TEXT("Error"), TEXT("Not Found KindInfo_BossItem(%s) in HashTable"), kindtype);

				pclKI[ iKindType ]->clBossItemInfo.Add(itemunique, rate);

				if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
				{
					if(pclSummonKI[ iKindType ])
						pclSummonKI[ iKindType ]->clBossItemInfo.Add(itemunique, rate);
				}
			}
		}
	}

	//KHY - 0810 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/KindInfo_Chat.txt") );
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/KindInfo_Chat.txt") );
	}
    
	if (!bLoadFile)
		MsgBox(TEXT("Error"),TEXT("Not Found KindInfo_Chat.txt"));

	TCHAR mapindex[128]=TEXT("");
	int chatnum = 0, chatgubun = 0;
	int imapindex;

	// �ɸ��� Chat �߰�
	NDataTypeInfo pChat[] =
	{
		NDATA_MBSTRING, kindtype,	128,
			NDATA_INT32,	&chatnum,	4,
			NDATA_MBSTRING, mapindex,	128,
			NDATA_INT32,	&chatgubun,	4,
			0,0,0
	};

	dataloader.RegDataType(pChat);

	while (!dataloader.IsEndOfData()) 
	{
		imapindex = 0;
		if (dataloader.ReadData())
		{
			if (!kindtype[ 0 ] == NULL)
			{
				bFind = pclClient->pclHashTableString->Find(kindtype, iKindType);
				if (!bFind)
					MsgBox(TEXT("Error"), TEXT("Not Found KindInfo_Chat(%s) in HashTable"), kindtype);

				pclClient->pclHashTableString->Find(mapindex, imapindex);

				switch (chatgubun)
				{
				case 0 : pclKI[ iKindType ]->AddChat(GetTxtFromMgr(chatnum));
						 if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
						 {
							 if(pclSummonKI[ iKindType ])
								pclSummonKI[ iKindType ]->AddChat(GetTxtFromMgr(chatnum));
						 }
					break;
				case 1 : pclKI[ iKindType ]->AddWarChat(GetTxtFromMgr(chatnum), imapindex);
						 if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
						 {
							 if(pclSummonKI[ iKindType ])
						 		pclSummonKI[ iKindType ]->AddWarChat(GetTxtFromMgr(chatnum), imapindex);
						 }
						 break;
				case 2 : pclKI[ iKindType ]->AddWarWinChat(GetTxtFromMgr(chatnum), imapindex);
						 if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
						 {
							 if(pclSummonKI[ iKindType ])
								 pclSummonKI[ iKindType ]->AddWarWinChat(GetTxtFromMgr(chatnum), imapindex);
						 }
						break;
				}
			}
		}
	}

	//KHY - 0810 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/KindInfo_SetFile.txt") );
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/KindInfo_SetFile.txt") );
	}

	if (!bLoadFile)
		MsgBox(TEXT("Error"),TEXT("Not Found KindInfo_SetFile.txt"));

	TCHAR anitype[128] = TEXT(""), filename[128] = TEXT(""), transmode[128] = TEXT(""), shadowani[128] = TEXT("");
	int dirswitch=0, font=0, frame=0, instrant=0, delay=0, atb=0, effectfont=0 
		, attacktype=0, shadowfont=0;

	int iAniType	= 0;
	int iTransmode	= 0;
	int iShadowani	= 0;

	// SetFile ����
	NDataTypeInfo pSetFileInfo[] =
	{
			NDATA_MBSTRING, kindtype,	128,
			NDATA_MBSTRING, anitype,	128,
			NDATA_INT32,	&dirswitch,	4,
			NDATA_MBSTRING, filename,	128,
			NDATA_INT32,	&font,		4,
			NDATA_INT32,	&frame,		4,
			NDATA_INT32,	&instrant,	4,
			NDATA_INT32,	&delay,		4,
			NDATA_INT32,	&atb,		4,
			NDATA_INT32,	&effectfont,	4,
			NDATA_MBSTRING, transmode,		128,
			NDATA_INT32,	&alphavalue,	4,
			NDATA_INT32,	&attacktype,	4,
			NDATA_MBSTRING, shadowani,		128,
			NDATA_INT32,	&shadowfont,		4,
			0,0,0
	};

	dataloader.RegDataType(pSetFileInfo);

	while (!dataloader.IsEndOfData()) 
	{
		iKindType=0; iAniType=0; iTransmode=0; iShadowani=0;

		if (dataloader.ReadData())
		{
			if (!kindtype[ 0 ] == NULL)
			{
				bFind = pclClient->pclHashTableString->Find(kindtype, iKindType);
				bFind = bFind && pclClient->pclHashTableString->Find(anitype, iAniType);

				if (!bFind)
					MsgBox(TEXT("Error"), TEXT("Not Found KindInfo_SetFile(%s) in HashTable"), kindtype);

				pclClient->pclHashTableString->Find(shadowani, iShadowani);
				pclClient->pclHashTableString->Find(transmode, iTransmode);

				pclKI[ iKindType ]->SetFile(iAniType,	DATA_TO_BOOL(dirswitch),	filename,	font,	frame,  instrant, delay, 
					atb, effectfont, iTransmode, alphavalue, DATA_TO_BOOL(attacktype), iShadowani, shadowfont);

				if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
				{
					if(pclSummonKI[ iKindType ])
						pclSummonKI[ iKindType ]->SetFile(	iAniType,	
															DATA_TO_BOOL(dirswitch),	
															filename,	
															font,	
															frame,  
															instrant, 
															delay, 
															atb, 
															effectfont, 
															iTransmode, 
															alphavalue, 
															DATA_TO_BOOL(attacktype), 
															iShadowani, 
															shadowfont	);
				}

			}
		}
	}

	//KHY - 0810 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/KindInfo_SetShadow.txt") );
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/KindInfo_SetShadow.txt") );
	}


	if (!bLoadFile)
		MsgBox(TEXT("Error"),TEXT("Not Found KindInfo_SetShadow.txt"));

	int locx=0, locy=0;

	// SetShadow ����
	NDataTypeInfo pSetShadow[] =
	{
		NDATA_MBSTRING, kindtype,	128,
			NDATA_MBSTRING, anitype,	128,
			NDATA_INT32,	&locx,		4,
			NDATA_INT32,	&locy,		4,
			0,0,0
	};

	dataloader.RegDataType(pSetShadow);

	while (!dataloader.IsEndOfData()) 
	{
		imapindex = 0;
		if (dataloader.ReadData())
		{
			if (!kindtype[ 0 ] == NULL)
			{
				bFind = pclClient->pclHashTableString->Find(kindtype, iKindType);
				bFind = bFind && pclClient->pclHashTableString->Find(anitype, iAniType);
				if (!bFind)
					MsgBox(TEXT("Error"), TEXT("Not Found KindInfo_Shadow(%s) in HashTable"), kindtype);

				pclKI [ iKindType]->SetShadowIndentXY(iAniType, locx, locy);
				
				if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
				{
					if(pclSummonKI[ iKindType ])
						pclSummonKI[iKindType]->SetShadowIndentXY(iAniType, locx, locy);
				}
			}
		}
	}
}