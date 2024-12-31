//---------------------------------
// 2003/10/2 ���°�
//---------------------------------
#include "../../Client/client.h"
#include "Item-ManagerClient.h"
#include "../../CommonLogic/CommonLogic.h"
#include "../../Skill/Skill-Manager.h"
#include "../../char/Kindinfo/Kindinfo.h"
#include "../../char/CharCommon/Char-Common.h"
#include "../../char/CharManager/CharManager.h"
#include "../../char/CharClient/Char-Client.h"
#include "../Client/InterfaceMgr/ControllerBaseDefinition.h"
#include "NDate.h"

#include "../../CommonLogic/MagicMgr/MagicMgr.h"
#include "../../CommonLogic/MagicMgr/MagicAttribute/MagicAttribute.h"

extern cltCommonLogic* pclClient;
extern SI32 hDrag;
extern SI32 hotx, hoty;
extern BOOL g_bDrag;
extern SI32 siDragFrom;

#include "../../Resource.h"

// �ӽ� ���� ũ��
const SI32 ConstTmpBufSize = 64;

// �������� ���� ������ ���� ������ ���´�. 
BOOL cltItemManagerClient::GetProductionExplain(SI32 siunique, cltPSkillInfo* pclskillinfo, cltPItemInfo* pclcharitem, TCHAR* ptext, SI16 txtSize)
{
	TCHAR buffer[1024] = TEXT("");
	TCHAR temp[256];
	TCHAR* pText = GetTxtFromMgr(3526);

	if(ptext == NULL)return FALSE;

	//---------------------------------------------
	// �������� ������ Ȯ���Ѵ�. 
	//---------------------------------------------
	SI32 ref = FindItemRefFromUnique(siunique);
	if(ref <= 0)return FALSE;

	SI32 type = pclItemInfo[ref]->siType;
	if(type == 0)return FALSE;

	//---------------------------------------------
	// ���� ���� 
	//---------------------------------------------
	pText = GetTxtFromMgr(3524);
	StringCchPrintf(buffer, 1024, pText, 
		pclItemInfo[ref]->clProductionInfo.siProductUnit);

	// ���꿡 �ʿ��� ����� �� ������ ���ǵǾ� �ִ� ��쿡�� 
	SI32 skillunique	= pclItemInfo[ref]->clSkillInfo.siSkill;
	SI32 skilllevel		= pclItemInfo[ref]->clSkillInfo.siSkillLevel;
	if( skillunique && skilllevel)
	{
		//--------------------------------------------
		// �ʿ� ���. 
		//--------------------------------------------
		TCHAR skillname[128];
		if(pclClient->pclSkillManager->GetSkillName(skillunique, skillname) == true)
		{
			pText = GetTxtFromMgr(3525);
			StringCchPrintf(temp,256, pText, skillname, skilllevel);
			StringCchCat(buffer, 1024, temp);
		}

		//-------------------------------------------
		// ���� ���ɼ�. 
		//-------------------------------------------
		SI32 personskilllevel = pclskillinfo->GetTotalSkillLevel(skillunique, 0, 0, &pclcharitem->clItem[0]);

		float rate; 
		if( personskilllevel < skilllevel)
		{
			rate	= 0.0f;
		}
		else
		{
			rate = pclItemInfo[ref]->GetTotalMakePbt( personskilllevel );
		}
		pText = GetTxtFromMgr(3526);
		StringCchPrintf(temp,256, pText, rate, '%');
		StringCchCat(buffer, 1024, temp);

	}
	
	//----------------------------------------
	// �ʿ� ����. 
	//----------------------------------------
	if(pclItemInfo[ref]->clSkillInfo.siMag)
	{
		pText = GetTxtFromMgr(3527);
		StringCchPrintf(temp, 256, pText, pclItemInfo[ref]->clSkillInfo.siMag);
		StringCchCat(buffer, 1024, temp);

	}
	//----------------------------------------
	// �ʿ� ������ or ���
	//----------------------------------------
	if(pclItemInfo[ref]->clSkillInfo.siHnd)
	{
		// [����] ����� ������ ����
		if ( pclClient->IsCountrySwitch(Switch_ManufactureInfluenceLuck) )
		{
			pText = GetTxtFromMgr(9861);
		}
		else
		{
			pText = GetTxtFromMgr(3528);
		}
		
		StringCchPrintf(temp, 256, pText, pclItemInfo[ref]->clSkillInfo.siHnd);
		StringCchCat(buffer, 1024, temp);

	}

	/*
	//------------------------------------
	// ������. 
	//------------------------------------

	StringCchPrintf(temp, 1024,  "--- ���� ----\r\n");
	StringCchCat(buffer, 1024, temp);

	for(i = 0;i < MAX_MATERIAL_NUMBER;i++)
	{
		SI32 materialunique = pclItemInfo[ref]->clProductionInfo.clMaterial[i].siUnique;

		if(materialunique)
		{
			SI32 materialref = FindRefFromUnique(materialunique);
			if(materialref > 0)
			{
				StringCchPrintf(temp, 1024,  TEXT("%s(%d)\r\n"), pclItemInfo[materialref]->GetName(), pclItemInfo[ref]->clProductionInfo.clMaterial[i].siNeedNum);
				StringCchCat(buffer, 1024, temp);
			}
		}
	}

	//------------------------------------
	// ������. 
	//------------------------------------
	StringCchPrintf(temp, 1024,  "--- ���� ----\r\n");
	StringCchCat(buffer, 1024, temp);

	for(i = 0;i < MAX_TOOL_NUMBER;i++)
	{
		SI32 toolunique = pclItemInfo[ref]->clProductionInfo.clTool[i].siUnique;

		if(toolunique)
		{
			SI32 toolref = FindRefFromUnique(toolunique);
			if(toolref > 0)
			{
				StringCchPrintf(temp, 1024,  TEXT("%s\r\n"), pclItemInfo[toolref]->GetName());
				StringCchCat(buffer, 1024, temp);
			}
		}
	}
	*/

	StringCchCopy(ptext, txtSize, buffer);

	return TRUE;
}

// �������� ���� ������ ���� ��ǰ ������ ���´�.
BOOL cltItemManagerClient::GetProductionItemExplain(SI32 siunique, cltPSkillInfo* pclskillinfo, cltPItemInfo* pclcharitem, cltMaterialExplain *pMaterial, SI32 *totalcount)
{

	//---------------------------------------------
	// �������� ������ Ȯ���Ѵ�. 
	//---------------------------------------------
	SI32 ref = FindItemRefFromUnique(siunique);
	if(ref <= 0)return FALSE;

	SI32 type = pclItemInfo[ref]->siType;
	if(type == 0)return FALSE;


	//------------------------------------
	// ������. 
	//------------------------------------
	SI32 siIndex = 0;
	pMaterial[siIndex].siUnique = 0;
	TCHAR* pText = GetTxtFromMgr(5062);
	StringCchCopy(pMaterial[siIndex].szName, MAX_ITEM_NAME_LENGTH, pText);	
	StringCchCopy(pMaterial[siIndex].szCount, 20, TEXT(""));
	siIndex++;

	for(SI32 i = 0;i < MAX_MATERIAL_NUMBER;i++)
	{
		SI32 materialunique = pclItemInfo[ref]->clProductionInfo.clMaterial[i].siUnique;
		if(materialunique)
		{
			SI32 materialref = FindItemRefFromUnique(materialunique);
			if(materialref > 0)
			{
				pMaterial[siIndex].siUnique = materialunique;
				StringCchCopy(pMaterial[siIndex].szName, MAX_ITEM_NAME_LENGTH, pclItemInfo[materialref]->GetName());	
				_itot(pclItemInfo[ref]->clProductionInfo.clMaterial[i].siNeedNum,pMaterial[siIndex].szCount, 10);
				siIndex++;
			}
		}
	}

	//------------------------------------
	// ������. 
	//------------------------------------
	pMaterial[siIndex].siUnique = 0;
	pText = GetTxtFromMgr(5063);
	StringCchCopy(pMaterial[siIndex].szName, MAX_ITEM_NAME_LENGTH, pText);	
	StringCchCopy(pMaterial[siIndex].szCount, 20, TEXT(""));
	siIndex++;

	for(i = 0;i < MAX_TOOL_NUMBER;i++)
	{
		SI32 toolunique = pclItemInfo[ref]->clProductionInfo.clTool[i].siUnique;

		if(toolunique)
		{
			SI32 toolref = FindItemRefFromUnique(toolunique);
			if(toolref > 0)
			{
				pMaterial[siIndex].siUnique = toolunique;
				StringCchCopy(pMaterial[siIndex].szName, MAX_ITEM_NAME_LENGTH, pclItemInfo[toolref]->GetName());	
				StringCchCopy(pMaterial[siIndex].szCount, 20, TEXT("1"));
				siIndex++;
			}
		}
	}

	*totalcount= siIndex;
	return TRUE;
}

BOOL cltItemManagerClient::GetProductionMakeItemExplain(SI32 siunique, cltMakeItem* pMakeItem, SI32 *totalcount)
{
	//---------------------------------------------
	// �������� ������ Ȯ���Ѵ�. 
	//---------------------------------------------
	SI32 ref = FindItemRefFromUnique(siunique);
	if(ref <= 0)return FALSE;

	SI32 type = pclItemInfo[ref]->siType;
	if(type == 0)return FALSE;

	SI32 siIndex = 0;
	SI32 siItemCount = 0;
	for(SI32 i = 0; i <MAX_ITEMINFO_NUMBER; ++i)
	{
		if(pclClient->pclItemManager->pclItemInfo[i])
		{
			if(pclClient->pclItemManager->pclItemInfo[i]->IsThereMaterialAndTool(siunique, &siItemCount) == true)
			{
				StringCchCopy(pMakeItem[siIndex].szName, MAX_ITEM_NAME_LENGTH, pclItemInfo[i]->GetName());	
				if(siItemCount>0)	_itot(siItemCount,pMakeItem[siIndex].szItemNum, 10);
				else				StringCchCopy(pMakeItem[siIndex].szItemNum	, 20, TEXT("1"));

				siIndex++;
				if(siIndex >= *totalcount) break;
			}
		}
	}

	*totalcount = siIndex;
	return TRUE;
}
//KHY - 0410 - ��������â ���� ����.
// ����ü�� �������� ���� ������ ���´�. (unique�� �ٰŷ�.) - ��������â �����̴�. 
bool cltItemManagerClient::GetExplainCrystalClient(SI32 itemunique, TCHAR* ptext)
{
	SI32 ref = FindItemRefFromUnique(itemunique);
	if(ref <= 0)return false;

	TCHAR buffer[1024] = TEXT("");
	TCHAR temp[1024] = TEXT("");
	TCHAR szcondition[1024]=TEXT("");
	TCHAR* pText = GetTxtFromMgr(3529);

	cltItem* pclitem = &pclItemInfo[ref]->clItem;

	// �������� Ÿ�� ȹ��. 
	SI32 type = pclitem->GetType(this);
	if(type == 0)return false;

	// �������� ����
	SI32 weight = pclitem->GetWeight(this, false); //����ü�� ��ġ�� �ʴ´�.

	TCHAR SkillName[ 64 ] = TEXT("");

	if(type == ITEMTYPE_CRYSTAL)
	{
		TCHAR* pText1 = GetTxtFromMgr(8061); //�ɷ�.
		TCHAR* pText11 = GetTxtFromMgr(8350); // �Ʒ��ɷ��� 1��.
		TCHAR* pText12 = GetTxtFromMgr(8352); // %s\r		
		TCHAR* pText2 = GetTxtFromMgr(804); // ������.

		TCHAR buf[64] = {'\0'};
		TCHAR buf1[128] = {'\0'};
		TCHAR buf2[128] = {'\0'};
		TCHAR buf3[128] = {'\0'};
		TCHAR buf4[128] = {'\0'};

		SI16 cAbliltyType = 0;
		SI16 cAbliltyTypeNum =0;
		TCHAR CrystalReturnString[50] = {'\0'};


		if((IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_CRYSTAL_REMOVE	) == true)||
			(IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_CRYSTAL_SLOT_CREATE) == true) )
		{
			if(IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_CRYSTAL_REMOVE	) == true) 				
				pText1 = GetTxtFromMgr(8233); //������ ����ü
			else if(IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_CRYSTAL_SLOT_CREATE) == true) 
				pText1 = GetTxtFromMgr(8232); //���� ����ü.
			StringCchPrintf(temp,1024,pText1);
			StringCchCat(buffer, 1024 ,temp);			
		}
		else if(IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_CRYSTAL_AVATAR) == true)
		{
			cAbliltyType = pclItemInfo[ref]->CrystalData[0].siCrystalType;
			cAbliltyTypeNum = pclItemInfo[ref]->CrystalData[0].siMinValue;
			GetCrystalAbilityTypeName(buf4, cAbliltyType, cAbliltyTypeNum, CrystalReturnString);
			StringCchPrintf(temp,1024, pText1, CrystalReturnString);
			StringCchCat(buffer, 1024 ,temp);			
		}
		else
		{
			StringCchPrintf(buf,64,pText11);
			//StringCchPrintf(buf2,128,TEXT("%s%s%s"),TEXT("<C05>"),buf,TEXT("</C>") );	
			StringCchPrintf(buf2,128,TEXT("%s"),buf);	

			StringCchPrintf(temp,1024,pText1,buf2);
			StringCchCat(buffer, 1024 ,temp);
		}

		// �ƹ�Ÿ ����ü�� �ƴ� ��� ����
		if(IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_CRYSTAL_AVATAR) != true)
		{
			for(SI16 i = 0; i <MAX_CAN_CRYSTALABILITY_NUM ; i++)
			{
				if((pclItemInfo[ref]->CrystalData[i].siCrystalType) > 0)			
				{
					cAbliltyType = pclItemInfo[ref]->CrystalData[i].siCrystalType;
					cAbliltyTypeNum = pclItemInfo[ref]->CrystalData[i].siMinValue;

					GetCrystalAbilityTypeName(buf1, cAbliltyType, cAbliltyTypeNum, CrystalReturnString);	 //buf1�� �Ⱦ���.
					
					StringCchPrintf(temp,1024,pText12,CrystalReturnString);
					StringCchCat(buffer, 1024 ,temp);
				}
			}
		}
		// ������.
		SI16 MaxDub = 100; // �⺻ �������� �׻� 100�̴�.
		
		if((IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_CRYSTAL_REMOVE	) == true)||
			(IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_CRYSTAL_SLOT_CREATE) == true) ||
			(IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_CRYSTAL_AVATAR) == true))
		{
			pText2 = GetTxtFromMgr(8254); //������ ����.

			StringCchPrintf(temp,1024,pText2);
			StringCchCat(buffer, 1024 ,temp);
		}
		else
		{
			StringCchPrintf(temp,1024,pText2,MaxDub,MaxDub);
			StringCchCat(buffer, 1024 ,temp);
		}

		// ����.
		pText = GetTxtFromMgr(805); 
		StringCchPrintf(temp, 1024,  pText, (float)weight/10.0); 
		StringCchCat(buffer, 1024, temp);

		///������ �̸��� ǰ��,  ������ ����
		TCHAR itemname[128];
		if(pclitem->GetFullName(this, itemname, 128) == true)
		{
			pText = GetTxtFromMgr(807);
			StringCchPrintf(ptext, 512, pText, itemname, pclItemTypeInfo[type]->szName, buffer);
			ptext[511] = '\0';		// �޸� ���� �ڵ� - by LEEKH 2008-02-04
				
		}

		return true;

	}

	return false;
	//return GetExplain(&pclItemInfo[ref]->clItem, ptext, FALSE, TRUE);
}


// �������� ���� ������ ���´�. (unique�� �ٰŷ�.) 
BOOL cltItemManagerClient::GetExplain(SI32 itemunique, TCHAR* ptext)
{
	SI32 ref = FindItemRefFromUnique(itemunique);
	if(ref <= 0)return FALSE;

	return GetExplain(&pclItemInfo[ref]->clItem, ptext, FALSE, TRUE);
}

// �������� ���� ������ ���´�. 
BOOL cltItemManagerClient::GetExplain(cltItem* pclitem, TCHAR* ptext, bool numbswitch, bool basicswitch  , bool bcolorswitch , SI32 siKind, bool bweightswitch)
{
	// ������ ���� ���⿡�ٰ� ������ 100%��°� �߰� ���ָ� �ȴ�
	const SI32 ConstEntireTmpBufSize = 1024;

	TCHAR buffer[1024] = TEXT("");
	TCHAR temp[1024] = TEXT("");
	TCHAR szcondition[1024]=TEXT("");
	TCHAR* pText = GetTxtFromMgr(3529);

	numbswitch = pclitem->CanPile(this);

	if(ptext == NULL)return FALSE;

	// �������� Ÿ�� ȹ��. 
	SI32 type = pclitem->GetType(this);
	if(type == 0)return FALSE;

	// �������� ����
	SI32 weight = pclitem->GetWeight(this, numbswitch);
	// ������. 
	SI32 maxdur	= pclitem->clItemCommon.clCommonInfo.uiMaxDurability;
	SI32 curdur	= pclitem->clItemCommon.clCommonInfo.uiDurability;

	SI32 ref = FindItemRefFromUnique(pclitem->siUnique);
	if(ref <= 0)return FALSE;

	TCHAR SkillName[ 64 ] = TEXT("");

	SI32 siForeverDurability  = (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
	SI32 siForeverDurability2 = (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );

	switch(type)
	{
	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�
	case ITEMTYPE_CRYSTAL:
		{
			SI16 cAbliltyType = pclitem->clItemCrystal.GetCrystalAblilty();
			SI16 cAbliltyTypeNum = pclitem->clItemCrystal.GetCrystalAbilityNum();

			SI16 cConditionLevel = pclItemInfo[ref]->clCondition.siLevel;

			TCHAR CrystalConditionReturnString[128] = {'\0'};

	
			// ����ü���� ���� ���� �߰�.
			if((IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_CRYSTAL_REMOVE	) == false) 
				&& (IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_CRYSTAL_SLOT_CREATE	) == false)) 	
			{
				if(cAbliltyType <= 0) // ���� �ɷ��� ���� ��Ʈ��Ʈ�� ���.
				{
					GetCrystalAbilityTypeCondition(cAbliltyType,cConditionLevel , CrystalConditionReturnString);
				}
			}

			StringCchPrintf(temp,1024,CrystalConditionReturnString);	
			StringCchCat(buffer, 1024 ,temp);
			
			SI16 MaxDub = (SI16)((pclitem->clItemCrystal.GetMaxDurability()*100) /30000);// �ִ� ������ �� - 30000 ����.

			// test
			//cltCrystalItem* pCastedCrystal = (cltCrystalItem*)(&(pclitem->cltItemCrytal));
			//SI16 curDur = (SI16)((pCastedCrystal->GetDurability()*100) /30000);// �ִ� ������ �� - 30000 ����.
			//SI16 MaxDub = (SI16)((pclitem->clItemCrystal.GetMaxDurability()*100) /30000);// �ִ� ������ �� - 30000 ����.
			
			///////////////////////////////
			//SI16 curdur	= (SI16)((pclitem->clItemCrystal[ref].GetDurability(//((pclitem->clItemCommon.clCommonInfo.uiDurability;
			//cltClient *pClient = (cltClient*)pclClient;

			//SI16 curdur = pClient->m_pDialog[ARTIFACT_MIXTURE_DLG].m_clArtifactItem[_siSlot].GetDurability()
			//pClient->m_pDialog[ARTIFACT_MIXTURE_DLG]->GetDialogControllerID()

					
			TCHAR buf[64] = {'\0'};
			TCHAR buf1[128] = {'\0'};
			TCHAR buf2[64] = {'\0'};
			TCHAR buf3[128] = {'\0'};
			TCHAR CrystalReturnString[50] = {'\0'};

			TCHAR* pText1 = GetTxtFromMgr(8061); //�ɷ�.
			TCHAR* pText2 = GetTxtFromMgr(804); // ������.

			//StringCchPrintf(temp, 1024,  pText, curdur, maxdur);
			//StringCchCat(buffer, 1024, temp);

						
			if(IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_CRYSTAL_REMOVE	) == true || 
				IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_CRYSTAL_SLOT_CREATE	) == true ||
				(cAbliltyType <= 0) )// ���� �ɷ��� ���� ��Ʈ��Ʈ�� ���.
			{
			
				if(IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_CRYSTAL_REMOVE	) == true) 				
					pText1 = GetTxtFromMgr(8233); //������ ����ü
				else if(IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_CRYSTAL_SLOT_CREATE) == true) 
					pText1 = GetTxtFromMgr(8232); //���� ����ü.
				else if(cAbliltyType <= 0)
					pText1 = GetTxtFromMgr(8679); //�ɷ� �ο�.

					pText2 = GetTxtFromMgr(8254); //������ ����.
					
				if(bcolorswitch)
				{
					StringCchPrintf(buf,64,pText1);	
					StringCchPrintf(buf1,128,TEXT("%s%s%s"),TEXT("<C05>"),buf, TEXT("</C>") );	

					StringCchPrintf(buf2,64,pText2);
					StringCchPrintf(buf3,128,TEXT("%s%s%s"),TEXT("<C05>"),buf2, TEXT("</C>") );	
				}
				else
				{
					StringCchPrintf(buf1,128,pText1);	
					StringCchPrintf(buf3,128,pText2);
				}								
			}
			// �߰�: �ڱ��� 2009.6.15 
			// �ƹ�Ÿ ����ü�� ��� �������� �����Ƿ� ������ ���� ���� ����
			else if(IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_CRYSTAL_AVATAR ) == true)
			{
				GetCrystalAbilityTypeName(buf, cAbliltyType, cAbliltyTypeNum, CrystalReturnString);
				if(bcolorswitch)
				{
					StringCchPrintf(buf,64,pText1,CrystalReturnString);	
					StringCchPrintf(buf1,128,TEXT("%s%s%s"),TEXT("<C05>"),buf, TEXT("</C>") );	
				}
				else
				{
					StringCchPrintf(buf1,128,pText1,CrystalReturnString);	
				}
			}
			else
			{
				GetCrystalAbilityTypeName(buf, cAbliltyType, cAbliltyTypeNum, CrystalReturnString);

				if(bcolorswitch)
				{
					StringCchPrintf(buf,64,pText1,CrystalReturnString);	
					StringCchPrintf(buf1,128,TEXT("%s%s%s"),TEXT("<C05>"),buf, TEXT("</C>") );	

					StringCchPrintf(buf2,64,pText2,MaxDub,MaxDub);
					StringCchPrintf(buf3,128,TEXT("%s%s%s"),TEXT("<C05>"),buf2, TEXT("</C>") );	
				}
				else // [����] �ŵ� ���̾�α� �ڽ��� ���̴� ���� �ɷ�ġ�� ������ �Ⱥ��̵��� �ּ� ó��.
				{
					//StringCchPrintf(buf1,128,pText1,CrystalReturnString);	
					//StringCchPrintf(buf3,128,pText2,MaxDub,MaxDub);
				}			
			}

			StringCchPrintf(temp,1024,TEXT("%s%s"),buf1 , buf3);	
			StringCchCat(buffer, 1024 ,temp);			
		}
		break;
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_AXE:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_SWORD:
		{			
			SI32 skill = 0;

			switch(type)
			{
			case ITEMTYPE_BOW:	skill = SKILL_USEBOW1;		break;
			case ITEMTYPE_GUN:	skill = SKILL_USEGUN1;		break;
			case ITEMTYPE_AXE:	skill = SKILL_USEAXE1;		break;
			case ITEMTYPE_STAFF:skill = SKILL_USESTAFF1;	break;
			case ITEMTYPE_SPEAR:skill = SKILL_USESPEAR1;	break;
			case ITEMTYPE_SWORD:skill = SKILL_USESWORD1;	break;
			case ITEMTYPE_CANNON: skill = 0;				break;
			case ITEMTYPE_TORPEDO: skill = 0;				break;
			default: skill = 0; MsgBox(TEXT("fdf83jfd"), TEXT("Fd3fd:%d"), type);
			}
			
			// ���⸦ ����ϴµ� �־ �ʿ� ����� �̸��� ���Ѵ�.
			if(pclClient->pclSkillManager->GetSkillName( skill, SkillName ) ==  false)return false;

			// ������ Ȯ���Ѵ�. 
			if(bcolorswitch)
				if(pclItemInfo[ref]->clCondition.GetCheckedText(szcondition, 1024, SkillName, skill, pclClient->pclCM->CR[1] ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}
			else
				if(pclItemInfo[ref]->clCondition.GetText(szcondition, 1024, SkillName, skill ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}

			pText = GetTxtFromMgr(3529);
			StringCchPrintf(temp, 1024, pText, 
				pclitem->clItemWeapon.uiMinDamage, 
				pclitem->clItemWeapon.uiMaxDamage,
				GetAttackRange(pclitem->siUnique));
			
			StringCchCat(buffer, 1024, temp);

			if(pclitem->clItemWeapon.uiMag)
			{
				pText = GetTxtFromMgr(3530);
				StringCchPrintf(temp,1024, pText, pclitem->clItemWeapon.uiMag);
				StringCchCat(buffer, 1024, temp);
			}
		}
		break;
	case ITEMTYPE_CANNON:
		{	
			pText = GetTxtFromMgr(3531);
			StringCchPrintf(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
			
			// ������ Ȯ���Ѵ�. 
			if(bcolorswitch)
				if(pclItemInfo[ref]->clCondition.GetCheckedText(szcondition, 1024, SkillName, 0 , pclClient->pclCM->CR[1] ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}
			else
				if(pclItemInfo[ref]->clCondition.GetText(szcondition, 1024, SkillName, 0  ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}

			pText = GetTxtFromMgr(3532);
			StringCchPrintf(temp, 1024, pText, 
				pclitem->clItemWeapon.uiMinDamage, 
				pclitem->clItemWeapon.uiMaxDamage,
				GetAttackRange(pclitem->siUnique));
			
			StringCchCat(buffer, 1024, temp);
		}
		break;

	case ITEMTYPE_TORPEDO:
		{
			pText = GetTxtFromMgr(3533);
			StringCchPrintf(temp,1024, pText, 
				pclitem->clItemWeapon.uiMinDamage, 
				pclitem->clItemWeapon.uiMaxDamage);
			
			StringCchCat(buffer, 1024, temp);
		}
		break;


	case ITEMTYPE_FOOD:
	case ITEMTYPE_SEAFOOD:
		{
			
			// ������ Ȯ���Ѵ�. 
			TCHAR SkillName[ 64 ] =TEXT("");
			TCHAR *pskillname = NULL;

			SI32 skillunique	= pclItemInfo[ref]->clCondition.siSkillKind;
			if(skillunique)
			{
				if(pclClient->pclSkillManager->GetSkillName( skillunique, SkillName ) ==  true)
				{
					pskillname = SkillName;
				}
			}
			
			if(bcolorswitch)
				if(pclItemInfo[ref]->clCondition.GetCheckedText(szcondition, 1024, pskillname, skillunique, pclClient->pclCM->CR[1]  ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}
			else
				if(pclItemInfo[ref]->clCondition.GetText(szcondition, 1024, pskillname, skillunique  ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}

			//cyj �ػ����� ȿ�ɼ���
			if( pclitem->siUnique == ITEMUNIQUE(3865) || pclitem->siUnique == ITEMUNIQUE(3870) || pclitem->siUnique == ITEMUNIQUE(3860))
			{
				pText = GetTxtFromMgr(5607);
				// �ػ����ڴ� ���ӽð� 1�ϰ� ȿ��
				StringCchPrintf(temp, 1024, pText, 1);
				StringCchCat(buffer, 1024, temp);
			}
			//else if(pclitem->siUnique == ITEMUNIQUE(3860))			// 3860 �����۵� ǥ�ô� �׳� 1�Ϸ� ǥ�õǵ��� �䱸�� �ͼ� ����. 3865�� 3860 ������ ���� �������� ����Ǵ� �ð��� 2��
			//{
			//	pText = GetTxtFromMgr(5607);
			//	// �ػ����ڴ� ���ӽð� 1�ϰ� ȿ��
			//	StringCchPrintf(temp, 1024, pText, 2);
			//	StringCchCat(buffer, 1024, temp);
			//}
			// ���� �����ΰ�. 
			else if(pclItemInfo[ref]->siHorseFoodSwitch > 0 )
			{
				pText = GetTxtFromMgr(3534);
				StringCchPrintf(temp, 1024, pText, 
					(float)weight/10.0);

				StringCchCat(buffer, 1024, temp);
			}
			else
			{
				if(pclitem->GetHungry(this))
				{
					pText = GetTxtFromMgr(3535);
					StringCchPrintf(temp, 1024, pText, 	pclitem->GetHungry(this));
					StringCchCat(buffer, 1024, temp);
				}
				if(pclItemInfo[ref]->siOrg1Penalty)
				{
					pText = GetTxtFromMgr(3536);
					StringCchPrintf(temp, 1024, pText, (float)pclItemInfo[ref]->siOrg1Penalty / 10.0);
					StringCchCat(buffer, 1024, temp);
				}
				if(pclItemInfo[ref]->siOrg2Penalty)
				{
					pText = GetTxtFromMgr(3537);
					StringCchPrintf(temp, 1024, pText, (float)pclItemInfo[ref]->siOrg2Penalty / 10.0);
					StringCchCat(buffer, 1024, temp);
				}
				if(pclItemInfo[ref]->siOrg3Penalty)
				{
					pText = GetTxtFromMgr(3538);
					StringCchPrintf(temp, 1024, pText, (float)pclItemInfo[ref]->siOrg3Penalty / 10.0);
					StringCchCat(buffer, 1024, temp);
				}
				if(pclItemInfo[ref]->siOrg4Penalty)
				{
					pText = GetTxtFromMgr(3539);
					StringCchPrintf(temp, 1024, pText, (float)pclItemInfo[ref]->siOrg4Penalty / 10.0);
					StringCchCat(buffer, 1024, temp);
				}


			}
		
		}
		break;

	case ITEMTYPE_HEAL:
		StringCchCopy(buffer, 1024, TEXT(""));
		
		if(pclItemInfo[ref]->siAdapt == ADAPT_SUMMON)
		{
			pText = GetTxtFromMgr(3540);
			StringCchPrintf(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
		}

		if(pclitem->GetLife(this))
		{
			pText = GetTxtFromMgr(3541);
			StringCchPrintf(temp, 1024, pText, pclitem->GetLife(this));
			StringCchCat(buffer, 1024, temp);
		}
		if(pclitem->GetMana(this))
		{
			pText = GetTxtFromMgr(3542);
			StringCchPrintf(temp, 1024, pText, pclitem->GetMana(this));
			StringCchCat(buffer, 1024, temp);
		}
		if(pclItemInfo[ref]->siDiseaseUnique)
		{
			pText = GetTxtFromMgr(3543);
			StringCchPrintf(temp, 1024, pText, pclItemInfo[ref]->szDiseaseName);
			StringCchCat(buffer, 1024, temp);
		}
		if(pclItemInfo[ref]->siHealEft == HEALEFT_NOFIRSTATTACK)
		{
			pText = GetTxtFromMgr(3544);
			StringCchPrintf(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
		}
		if(pclItemInfo[ref]->siHealEft == HEALEFT_UNFREEZE)
		{
			pText = GetTxtFromMgr(3545);
			StringCchPrintf(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
		}
		if(pclItemInfo[ref]->siHealEft == HEALEFT_PREMIUM)
		{
			pText = GetTxtFromMgr(5607);
			// HEALEFT_PREMIUM�� ���ӽð� 1�ϰ� ȿ��
			StringCchPrintf(temp, 1024, pText, 1);
			StringCchCat(buffer, 1024, temp);
		}
		if(pclItemInfo[ref]->siHealEft == HEALEFT_HEROATTACKUP30)
		{
			pText = GetTxtFromMgr(5607);
			// ������ ������ 30�ϰ� [2007.08 30 �ռ���]
			StringCchPrintf(temp, 1024, pText, 30);
			StringCchCat(buffer, 1024, temp);
		}
		if(pclItemInfo[ref]->siHealEft == HEALEFT_HERODEFENSEUP30)
		{
			pText = GetTxtFromMgr(5607);
			//���� ������ 30�ϰ�[2007.08.30 �ռ���]
			StringCchPrintf(temp, 1024, pText, 30);
			StringCchCat(buffer, 1024, temp);
		}
		if(pclItemInfo[ref]->siHealEft == HEALEFT_FOURLEAF)
		{
			// [���� : Ȳ���� 2008. 1. 31 => �߰��� ����� Ŭ�ι� �⺻�� ������ ���̰�.]
			if(2756 == pclitem->siUnique)
			{
				
			}
			else
			{
				pText = GetTxtFromMgr(7082);			
				StringCchPrintf(temp, 1024, pText, 1);
				StringCchCat(buffer, 1024, temp);
			}
		}
		if(pclItemInfo[ref]->siHealEft == HEALEFT_PREMIUMEXPUP )
		{
		
		}
		//if(pclItemInfo[ref]->siHealEft == HEALEFT_SPECIALAMPUL)
		//{
		//	pText = GetTxtFromMgr(2790); // ����� ����
		//	// ���� ����ġ ���� �� - ���ӽð� 1�ϰ�(�� 48��) [2009.02.26]
		//	StringCchPrintf(temp, 1024, pText, 1);
		//	StringCchCat(buffer, 1024 temp);
		//}
		//���� EXP ĸ��
		if(pclItemInfo[ref]->siHealEft == HEALEFT_SUPEREXPUP )
		{

		}
		if(pclItemInfo[ref]->siHealEft == HEALEFT_HAPPYBEAN)
		{	
			pText = GetTxtFromMgr(7135);			
			//StringCchPrintf(temp, 1024, pText, 1);
			StringCchCat(buffer, 1024, pText);
		}//���Ǻ� ����Ÿ�� [2007.08.22 �ռ���]
		if(pclItemInfo[ref]->siHealEft == HEALEFT_COMBAT)
		{

		}
		if(pclItemInfo[ref]->siHealEft == HEALEFT_DIGESTIVE )
		{
			pText = GetTxtFromMgr(6046);
			//StringCchPrintf(temp, 1024, pText, 30);
			StringCchCat(buffer, 1024, pText);
		}
		if(pclItemInfo[ref]->siHealEft == HEALEFT_ALLDESEASE )
		{
			pText = GetTxtFromMgr(6047);
			//StringCchPrintf(temp, 1024, pText, 30);
			StringCchCat(buffer, 1024, pText);
		}
		if(pclItemInfo[ref]->siHealEft == HEALEFT_BULLET )
		{
			pText = GetTxtFromMgr(6277);
			TCHAR tmpbuf[1024];
			StringCchPrintf(tmpbuf, 1024, pText, 365);

			StringCchCat(buffer, 1024, tmpbuf);
		}
		if(pclItemInfo[ref]->siOrg1Penalty)
		{
			pText = GetTxtFromMgr(3546);
			StringCchPrintf(temp, 1024, pText, (float)pclItemInfo[ref]->siOrg1Penalty / 10.0);
			StringCchCat(buffer, 1024, temp);
		}
		if(pclItemInfo[ref]->siOrg2Penalty)
		{
			pText = GetTxtFromMgr(3547);
			StringCchPrintf(temp, 1024, pText, (float)pclItemInfo[ref]->siOrg2Penalty / 10.0);
			StringCchCat(buffer, 1024, temp);
		}
		if(pclItemInfo[ref]->siOrg3Penalty)
		{
			pText = GetTxtFromMgr(3548);
			StringCchPrintf(temp, 1024, pText, (float)pclItemInfo[ref]->siOrg3Penalty / 10.0);
			StringCchCat(buffer, 1024, temp);
		}
		if(pclItemInfo[ref]->siOrg4Penalty)
		{
			pText = GetTxtFromMgr(3549);
			StringCchPrintf(temp, 1024, pText, (float)pclItemInfo[ref]->siOrg4Penalty / 10.0);
			StringCchCat(buffer, 1024, temp);
		}
		break;

	//case ITEMTYPE_AVATAR_DRESS:
	//case ITEMTYPE_AVATAR_HAT:
	case ITEMTYPE_BELT:
	case ITEMTYPE_HELMET:
	case ITEMTYPE_ARMOUR:
		// ������ Ȯ���Ѵ�. 
		if(bcolorswitch)
			if(pclItemInfo[ref]->clCondition.GetCheckedText(szcondition, 1024, NULL, 0 , pclClient->pclCM->CR[1] ) == true)
			{
				StringCchCopy(buffer, 1024, szcondition);
			}
			else
			{
				StringCchCopy(buffer, 1024, TEXT(""));
			}
		else
			if(pclItemInfo[ref]->clCondition.GetText(szcondition, 1024, NULL, 0  ) == true)
			{
				StringCchCopy(buffer, 1024, szcondition);
			}
			else
			{
				StringCchCopy(buffer, 1024, TEXT(""));
			}

		// �źп� ���� ���� ����, 
		if(pclItemInfo[ref]->siNeedRank == 1)
		{
			pText = GetTxtFromMgr(3550);
			StringCchCopy(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
		}
		else if(pclItemInfo[ref]->siNeedRank == 2)
		{
			pText = GetTxtFromMgr(3551);
			StringCchCopy(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
		}
		else if(pclItemInfo[ref]->siNeedRank == 3)
		{
			pText = GetTxtFromMgr(3552);
			StringCchCopy(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
		}
		else if(pclItemInfo[ref]->siNeedRank == 4)
		{
			pText = GetTxtFromMgr(3553);
			StringCchCopy(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
		}
		else if(pclItemInfo[ref]->siNeedRank == 5)
		{
			pText = GetTxtFromMgr(3554);
			StringCchCopy(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
		}
		else if(pclItemInfo[ref]->siNeedRank == 6)
		{
			pText = GetTxtFromMgr(3555);
			StringCchCopy(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
		}
		else if(pclItemInfo[ref]->siNeedRank == 7)
		{
			pText = GetTxtFromMgr(6411);
			StringCchCopy(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
		}

		pText = GetTxtFromMgr(3556);
		StringCchPrintf(temp, 1024, pText, 
			pclitem->clItemArmour.uiAC);

		StringCchCat(buffer, 1024, temp);

		/*
		if(type == ITEMTYPE_DRESS)
		{
			pText = GetTxtFromMgr(3557);
			StringCchPrintf(temp, 1024, pText, pclitem->clItemArmour.uiAC / DRESS_ADD_DPOWER_RATE);
			StringCchCat(buffer, 1024, temp);
		}*/
		/*
		if(type == ITEMTYPE_HAT)
		{
			pText = GetTxtFromMgr(3558);
			StringCchPrintf(temp, 1024, pText, pclitem->clItemArmour.uiAC / DRESS_ADD_DPOWER_RATE);
			StringCchCat(buffer, 1024, temp);
		}*/


		// �� 
		if(pclitem->clItemArmour.uiLuck)
		{
			pText = GetTxtFromMgr(3559);
			StringCchPrintf(temp, 1024, pText, 
				pclitem->clItemArmour.uiLuck);
			
			StringCchCat(buffer, 1024, temp);
		}

		// ��� ���. 
		if (pclitem->clItemArmour.uiSkillUp)
		{
			// ������ ���� ����� ���Ǿ�� �� ��, 
			{
				SI32 skilltype = pclItemInfo[ref]->siUpgradeSkillType;
				if(skilltype & UPGRADESKILLTYPE_MAKE)
				{
					pText = GetTxtFromMgr(3560);
					StringCchPrintf(temp, 1024, pText, pclitem->clItemArmour.uiSkillUp);
					StringCchCat(buffer, 1024, temp);
				}
				if(skilltype & UPGRADESKILLTYPE_USEWEAPON)
				{
					pText = GetTxtFromMgr(3561);
					StringCchPrintf(temp, 1024, pText, pclitem->clItemArmour.uiSkillUp);
					StringCchCat(buffer, 1024, temp);
				}
			}

			// ������ ��� ����� ������ ��, 
			if( pclItemInfo[ref]->siUpgradeSkillUnique)
			{
				SI32 SkillUnique = pclItemInfo[ ref ]->siUpgradeSkillUnique;
				if(pclClient->pclSkillManager->GetSkillName( SkillUnique, SkillName ) ==  true)
				{
					pText = GetTxtFromMgr(3564);
					StringCchPrintf(temp, 1024, pText, SkillName, pclitem->clItemArmour.uiSkillUp);
					StringCchCat(buffer, 1024, temp);
				}
				else if ( SkillUnique == MAX_SKILL_NUMBER )
				{
				}
				else if ( SkillUnique == ALL_MAKESKILL_UNIQUE )
				{
					pText = GetTxtFromMgr(5685);
					StringCchPrintf(temp, 1024, pText, pclitem->clItemArmour.uiSkillUp);
					StringCchCat(buffer, 1024, temp);
				}
				else if ( SkillUnique == ALL_WEAPONSKILL_UNIQUE )
				{
					pText = GetTxtFromMgr(5679);
					StringCchPrintf(temp, 1024, pText, pclitem->clItemArmour.uiSkillUp);
					StringCchCat(buffer, 1024, temp);
				}
				else if ( SkillUnique == ALL_PRODUCTSKILL_UNIQUE )
				{
					pText = GetTxtFromMgr(6140);
					StringCchPrintf(temp, 1024, pText, pclitem->clItemArmour.uiSkillUp);
					StringCchCat(buffer, 1024, temp);
				}
				else if ( SkillUnique == ALL_ALLSKILL_UNIQUE )
				{
					pText = GetTxtFromMgr(6266);
					StringCchPrintf(temp, 1024, pText, pclitem->clItemArmour.uiSkillUp);
					StringCchCat(buffer, 1024, temp);
				}


			}
		}
	
		break;

	// �������� �κ� Ȯ�� �� �߰� ������ �ʿ� �� �� ����.
	case ITEMTYPE_AVATAR_DRESS:
	case ITEMTYPE_AVATAR_HAT:
		{
			// ������ Ȯ���Ѵ�. 
			if(bcolorswitch)
				if(pclItemInfo[ref]->clCondition.GetCheckedText(szcondition, 1024, NULL, 0 , pclClient->pclCM->CR[1] ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}
			else
				if(pclItemInfo[ref]->clCondition.GetText(szcondition, 1024, NULL, 0  ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}
		}
		break;


	case ITEMTYPE_HAT:		
	case ITEMTYPE_DRESS:
		// ������ Ȯ���Ѵ�. 
		if(bcolorswitch)
			if(pclItemInfo[ref]->clCondition.GetCheckedText(szcondition, 1024, NULL, 0 , pclClient->pclCM->CR[1] ) == true)
			{
				StringCchCopy(buffer, 1024, szcondition);
			}
			else
			{
				StringCchCopy(buffer, 1024, TEXT(""));
			}
		else
			if(pclItemInfo[ref]->clCondition.GetText(szcondition, 1024, NULL, 0  ) == true)
			{
				StringCchCopy(buffer, 1024, szcondition);
			}
			else
			{
				StringCchCopy(buffer, 1024, TEXT(""));
			}

			// �źп� ���� ���� ����, 
			if(pclItemInfo[ref]->siNeedRank == 1)
			{
				pText = GetTxtFromMgr(3550);
				StringCchCopy(temp, 1024, pText);
				StringCchCat(buffer, 1024, temp);
			}
			else if(pclItemInfo[ref]->siNeedRank == 2)
			{
				pText = GetTxtFromMgr(3551);
				StringCchCopy(temp, 1024, pText);
				StringCchCat(buffer, 1024, temp);
			}
			else if(pclItemInfo[ref]->siNeedRank == 3)
			{
				pText = GetTxtFromMgr(3552);
				StringCchCopy(temp, 1024, pText);
				StringCchCat(buffer, 1024, temp);
			}
			else if(pclItemInfo[ref]->siNeedRank == 4)
			{
				pText = GetTxtFromMgr(3553);
				StringCchCopy(temp, 1024, pText);
				StringCchCat(buffer, 1024, temp);
			}
			else if(pclItemInfo[ref]->siNeedRank == 5)
			{
				pText = GetTxtFromMgr(3554);
				StringCchCopy(temp, 1024, pText);
				StringCchCat(buffer, 1024, temp);
			}
			else if(pclItemInfo[ref]->siNeedRank == 6)
			{
				pText = GetTxtFromMgr(3555);
				StringCchCopy(temp, 1024, pText);
				StringCchCat(buffer, 1024, temp);
			}
			else if(pclItemInfo[ref]->siNeedRank == 7)
			{
				pText = GetTxtFromMgr(6411);
				StringCchCopy(temp, 1024, pText);
				StringCchCat(buffer, 1024, temp);
			}

			//pText = GetTxtFromMgr(3556);
			//StringCchPrintf(temp, 1024, pText, 
			//	pclitem->clItemStatusArmour.uiAC);

			//StringCchCat(buffer, 1024, temp);

			if(pclitem->clItemStatusArmour.uiStr)
			{
				pText = GetTxtFromMgr(3565);
				StringCchPrintf(temp, 1024, pText, 	pclitem->clItemStatusArmour.uiStr);
				StringCchCat(buffer, 1024, temp);
			}

			if(pclitem->clItemStatusArmour.uiDex)
			{
				pText = GetTxtFromMgr(3566);
				StringCchPrintf(temp, 1024, pText, 	pclitem->clItemStatusArmour.uiDex);
				StringCchCat(buffer, 1024, temp);
			}

			if(pclitem->clItemStatusArmour.uiVit)
			{
				pText = GetTxtFromMgr(3567);
				StringCchPrintf(temp, 1024, pText, 	pclitem->clItemStatusArmour.uiVit);
				StringCchCat(buffer, 1024, temp);
			}

			if(pclitem->clItemStatusArmour.uiMag)
			{
				pText = GetTxtFromMgr(6064);
				StringCchPrintf(temp, 1024, pText, 	pclitem->clItemStatusArmour.uiMag);
				StringCchCat(buffer, 1024, temp);
			}

			if(pclitem->clItemStatusArmour.uiLuk)
			{
				pText = GetTxtFromMgr(6065);
				StringCchPrintf(temp, 1024, pText, 	pclitem->clItemStatusArmour.uiLuk);
				StringCchCat(buffer, 1024, temp);
			}

			if(pclitem->clItemStatusArmour.uiHnd)
			{
				pText = GetTxtFromMgr(6108);
				StringCchPrintf(temp, 1024, pText, 	pclitem->clItemStatusArmour.uiHnd);
				StringCchCat(buffer, 1024, temp);
			}

			/*
			if(type == ITEMTYPE_DRESS)
			{
			pText = GetTxtFromMgr(3557);
			StringCchPrintf(temp, 1024, pText, pclitem->clItemArmour.uiAC / DRESS_ADD_DPOWER_RATE);
			StringCchCat(buffer, 1024, temp);
			}*/
			/*
			if(type == ITEMTYPE_HAT)
			{
			pText = GetTxtFromMgr(3558);
			StringCchPrintf(temp, 1024, pText, pclitem->clItemArmour.uiAC / DRESS_ADD_DPOWER_RATE);
			StringCchCat(buffer, 1024, temp);
			}*/


			//// �� 
			//if(pclitem->clItemArmour.uiLuck)
			//{
			//	pText = GetTxtFromMgr(3559);
			//	StringCchPrintf(temp, 1024, pText, 
			//		pclitem->clItemArmour.uiLuck);
			//	
			//	StringCchCat(buffer, 1024, temp);
			//}

			// ��� ���. 
			if (pclitem->clItemStatusArmour.uiSkillUp)
			{
				// ������ ���� ����� ���Ǿ�� �� ��, 
				//{
				//	SI32 skilltype = pclItemInfo[ref]->siUpgradeSkillType;
				//	if(skilltype & UPGRADESKILLTYPE_MAKE)
				//	{
				//		pText = GetTxtFromMgr(3560);
				//		StringCchPrintf(temp, 1024, pText, pclitem->clItemStatusArmour.uiSkillUp);
				//		StringCchCat(buffer, 1024, temp);
				//	}
				//	if(skilltype & UPGRADESKILLTYPE_USEWEAPON)
				//	{
				//		pText = GetTxtFromMgr(3561);
				//		StringCchPrintf(temp, 1024, pText, pclitem->clItemStatusArmour.uiSkillUp);
				//		StringCchCat(buffer, 1024, temp);
				//	}
				//}

				// ������ ��� ����� ������ ��, 
				if( pclItemInfo[ref]->siUpgradeSkillUnique)
				{
					SI32 SkillUnique = pclItemInfo[ ref ]->siUpgradeSkillUnique;
					if(pclClient->pclSkillManager->GetSkillName( SkillUnique, SkillName ) ==  true)
					{
						pText = GetTxtFromMgr(3564);
						StringCchPrintf(temp, 1024, pText, SkillName, pclitem->clItemStatusArmour.uiSkillUp);
						StringCchCat(buffer, 1024, temp);
					}
					else if ( SkillUnique == MAX_SKILL_NUMBER ) // ��ų�� �ִ� �� ��
					{
					}
					else if ( SkillUnique == ALL_MAKESKILL_UNIQUE ) // ������ų ���θ� ����Ŵ
					{
						pText = GetTxtFromMgr(5685);
						StringCchPrintf(temp, 1024, pText, pclitem->clItemStatusArmour.uiSkillUp);
						StringCchCat(buffer, 1024, temp);
					}
					else if ( SkillUnique == ALL_WEAPONSKILL_UNIQUE ) // ���⽺ų ����
					{
						pText = GetTxtFromMgr(5679);
						StringCchPrintf(temp, 1024, pText, pclitem->clItemStatusArmour.uiSkillUp);
						StringCchCat(buffer, 1024, temp);
					}
					else if ( SkillUnique == ALL_PRODUCTSKILL_UNIQUE ) // ���꽺ų ����
					{
						pText = GetTxtFromMgr(6140);
						StringCchPrintf(temp, 1024, pText, pclitem->clItemStatusArmour.uiSkillUp);
						StringCchCat(buffer, 1024, temp);
					}
					else if ( SkillUnique == ALL_ALLSKILL_UNIQUE ) // ��� ��ų
					{
						pText = GetTxtFromMgr(6266);
						StringCchPrintf(temp, 1024, pText, pclitem->clItemStatusArmour.uiSkillUp);
						StringCchCat(buffer, 1024, temp);
					}


				}
			}

			break;



	case ITEMTYPE_BAG:
		// ������ Ȯ���Ѵ�. 
		if(bcolorswitch)
			if(pclItemInfo[ref]->clCondition.GetCheckedText(szcondition, 1024, NULL, 0 , pclClient->pclCM->CR[1] ) == true)
			{
				StringCchCopy(buffer, 1024, szcondition);
			}
			else
			{
				StringCchCopy(buffer, 1024, TEXT(""));
			}
		else
			if(pclItemInfo[ref]->clCondition.GetText(szcondition, 1024, NULL, 0  ) == true)
			{
				StringCchCopy(buffer, 1024, szcondition);
			}
			else
			{
				StringCchCopy(buffer, 1024, TEXT(""));
			}

		if(pclItemInfo[ref]->BagUseItemType >= 0)
		{
			
		}
		
		if(pclitem->clItemBag.uiAC)
		{
			pText = GetTxtFromMgr(3562);
			StringCchPrintf(temp,1024,pText, pclitem->clItemBag.uiAC);
			StringCchCat(buffer, 1024, temp);
		}

		if(pclitem->GetDurability() != siForeverDurability)
		{
			pText = GetTxtFromMgr(3563);
			StringCchPrintf(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);		
		}

		break;

	// �ƹ�Ÿ ����
	case ITEMTYPE_AVATAR_MANTLE:
		{
			if(bcolorswitch)
				if(pclItemInfo[ref]->clCondition.GetCheckedText(szcondition, 1024, NULL, 0 , pclClient->pclCM->CR[1] ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}
			else
				if(pclItemInfo[ref]->clCondition.GetText(szcondition, 1024, NULL, 0  ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}

				if(pclitem->clItemAvatarMantle.uiAC)
				{
					pText = GetTxtFromMgr(3556);
					StringCchPrintf(temp, 1024, pText, 	pclitem->clItemAvatarMantle.uiAC);
					StringCchCat(buffer, 1024, temp);
				}

			/*	if(pclitem->clItemMantle.uiStr)
				{
					pText = GetTxtFromMgr(3565);
					StringCchPrintf(temp, 1024, pText, 	pclitem->clItemMantle.uiStr);
					StringCchCat(buffer, 1024, temp);
				}

				if(pclitem->clItemMantle.uiDex)
				{
					pText = GetTxtFromMgr(3566);
					StringCchPrintf(temp, 1024, pText, 	pclitem->clItemMantle.uiDex);
					StringCchCat(buffer, 1024, temp);
				}

				if(pclitem->clItemMantle.uiVit)
				{
					pText = GetTxtFromMgr(3567);
					StringCchPrintf(temp, 1024, pText, 	pclitem->clItemMantle.uiVit);
					StringCchCat(buffer, 1024, temp);
				}*/
		}
		break;
	case ITEMTYPE_MANTLE:
		// ������ Ȯ���Ѵ�. 
		
		if(bcolorswitch)
			if(pclItemInfo[ref]->clCondition.GetCheckedText(szcondition, 1024, NULL, 0 , pclClient->pclCM->CR[1] ) == true)
			{
				StringCchCopy(buffer, 1024, szcondition);
			}
			else
			{
				StringCchCopy(buffer, 1024, TEXT(""));
			}
		else
			if(pclItemInfo[ref]->clCondition.GetText(szcondition, 1024, NULL, 0  ) == true)
			{
				StringCchCopy(buffer, 1024, szcondition);
			}
			else
			{
				StringCchCopy(buffer, 1024, TEXT(""));
			}

		// �źп� ���� ���� ����, 
		if(pclItemInfo[ref]->siNeedRank == 1)
		{
			pText = GetTxtFromMgr(3550);
			StringCchCopy(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
		}
		else if(pclItemInfo[ref]->siNeedRank == 2)
		{
			pText = GetTxtFromMgr(3551);
			StringCchCopy(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
		}
		else if(pclItemInfo[ref]->siNeedRank == 3)
		{
			pText = GetTxtFromMgr(3552);
			StringCchCopy(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
		}
		else if(pclItemInfo[ref]->siNeedRank == 4)
		{
			pText = GetTxtFromMgr(3553);
			StringCchCopy(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
		}
		else if(pclItemInfo[ref]->siNeedRank == 5)
		{
			pText = GetTxtFromMgr(3554);
			StringCchCopy(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
		}
		else if(pclItemInfo[ref]->siNeedRank == 6)
		{
			pText = GetTxtFromMgr(3555);
			StringCchCopy(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
		}
		else if(pclItemInfo[ref]->siNeedRank == 7)
		{
			pText = GetTxtFromMgr(6411);
			StringCchCopy(temp, 1024, pText);
			StringCchCat(buffer, 1024, temp);
		}


		if(pclitem->clItemMantle.uiAC)
		{
			pText = GetTxtFromMgr(3556);
			StringCchPrintf(temp, 1024, pText, 	pclitem->clItemMantle.uiAC);
			StringCchCat(buffer, 1024, temp);
		}

		if(pclitem->clItemMantle.uiStr)
		{
			pText = GetTxtFromMgr(3565);
			StringCchPrintf(temp, 1024, pText, 	pclitem->clItemMantle.uiStr);
			StringCchCat(buffer, 1024, temp);
		}
		
		if(pclitem->clItemMantle.uiDex)
		{
			pText = GetTxtFromMgr(3566);
			StringCchPrintf(temp, 1024, pText, 	pclitem->clItemMantle.uiDex);
			StringCchCat(buffer, 1024, temp);
		}

		if(pclitem->clItemMantle.uiVit)
		{
			pText = GetTxtFromMgr(3567);
			StringCchPrintf(temp, 1024, pText, 	pclitem->clItemMantle.uiVit);
			StringCchCat(buffer, 1024, temp);
		}
		break;

	case ITEMTYPE_SHOES:

		// 2003.10.23
	
		if(bcolorswitch)
			if(pclItemInfo[ref]->clCondition.GetCheckedText(szcondition, 1024, NULL, 0 , pclClient->pclCM->CR[1] ) == true)
			{
				StringCchCopy(buffer, 1024, szcondition);
			}
			else
			{
				StringCchCopy(buffer, 1024, TEXT(""));
			}
		else
			if(pclItemInfo[ref]->clCondition.GetText(szcondition, 1024, NULL, 0  ) == true)
			{
				StringCchCopy(buffer, 1024, szcondition);
			}
			else
			{
				StringCchCopy(buffer, 1024, TEXT(""));
			}


		pText = GetTxtFromMgr(3568);
		StringCchPrintf(temp, 1024, pText, 
			pclitem->clItemShoes.uiAC,
			pclitem->clItemShoes.uiMoveSpeed);

		StringCchCat( buffer , 1024,temp );

		break;

	// �ƹ�Ÿ �����
	case ITEMTYPE_AVATAR_NECK:
		{
			// ���׷��̵� ��ų ������ Ȯ���Ѵ�. 
			TCHAR SkillName[ 64 ] = TEXT("");
			SI32 SkillUnique = pclitem->clItemAvatarNeck.uiUpgradeSkillUnique;

			if(bcolorswitch)
			{
				if(pclItemInfo[ref]->clCondition.GetCheckedText(szcondition, 1024, NULL, 0 , pclClient->pclCM->CR[1] ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}
			}
			else
			{
				if(pclItemInfo[ref]->clCondition.GetText(szcondition, 1024, NULL, SkillUnique  ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}
			}

			if(SkillUnique > 0)
			{
				SI32 Ref = pclClient->pclItemManager->FindItemRefFromUnique( pclitem->siUnique );
				if(ref > 0)
				{
					if(pclClient->pclSkillManager->GetSkillName(SkillUnique, SkillName)  == true)
					{
						// �ش罺ų�� 1��ŭ ���� => "%s ��ų�� %d ��ŭ ����\r"
						pText = GetTxtFromMgr(30042);

						StringCchPrintf(temp, 1024, pText, SkillName, pclitem->clItemAvatarNeck.uiSkillValue);
						StringCchCat(buffer, 1024, temp);
					}
				}
			}
		}
		break;
	case ITEMTYPE_NECK:
		{

			// ������ Ȯ���Ѵ�. 
			if(bcolorswitch)
				if(pclItemInfo[ref]->clCondition.GetCheckedText(szcondition, 1024, NULL, 0 , pclClient->pclCM->CR[1] ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}
			else
				if(pclItemInfo[ref]->clCondition.GetText(szcondition, 1024, NULL, 0  ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}


			// ���׷��̵� ��ų ������ Ȯ���Ѵ�. 
			TCHAR SkillName[ 64 ] = TEXT("");

			//cyj ����̴� �к����϶��� �ɷ���� �Ⱥ���
			if ( pclitem->clItemNeck.uiSkillPointUp && pclitem->IsSealingUp(pclClient->pclItemManager) == false)
			{
				SI32 Ref = pclClient->pclItemManager->FindItemRefFromUnique( pclitem->siUnique );
				if(ref > 0)
				{
					SI32 SkillUnique = pclItemInfo[ Ref ]->siUpgradeSkillUnique;		// pclitem->cltItemAvatarNeck.uiSkillType;
					if(pclClient->pclSkillManager->GetSkillName( SkillUnique, SkillName ) ==  true)
					{
						pText = GetTxtFromMgr(3564);
						StringCchPrintf(temp, 1024, pText, SkillName, pclitem->clItemNeck.uiSkillPointUp);
						StringCchCat(buffer, 1024, temp);
					}
					else if ( SkillUnique == MAX_SKILL_NUMBER )
					{
					}
					else if ( SkillUnique == ALL_MAKESKILL_UNIQUE )
					{
						pText = GetTxtFromMgr(5685);
						StringCchPrintf(temp, 1024, pText, pclitem->clItemNeck.uiSkillPointUp);
						StringCchCat(buffer, 1024, temp);
					}
					else if ( SkillUnique == ALL_WEAPONSKILL_UNIQUE )
					{
						pText = GetTxtFromMgr(5679);
						StringCchPrintf(temp, 1024, pText, pclitem->clItemNeck.uiSkillPointUp);
						StringCchCat(buffer, 1024, temp);
					}
					else if ( SkillUnique == ALL_PRODUCTSKILL_UNIQUE )
					{
						pText = GetTxtFromMgr(6140);
						StringCchPrintf(temp, 1024, pText, pclitem->clItemNeck.uiSkillPointUp);
						StringCchCat(buffer, 1024, temp);
					}
					else if ( SkillUnique == ALL_ALLSKILL_UNIQUE)
					{
						pText = GetTxtFromMgr(6266);
						StringCchPrintf(temp, 1024, pText, pclitem->clItemNeck.uiSkillPointUp);
						StringCchCat(buffer, 1024, temp);
					}


				}
			}
		}
		break;

	case ITEMTYPE_BOOK:
		{
			TCHAR skillname[128];
			
			if(pclClient->pclSkillManager->GetSkillName(pclitem->GetSkillUnique(this), skillname) == false)
			{
				StringCchCopy(skillname, 128, TEXT("NOSKILLNAME"));
			}

			// ��� ������ �󸶳� ���� �ټ� �ִ��� Ȯ���Ѵ�. 
			SI32 skilllevellimit = 0;
			SI32 skillup = 0;
			SI32 Ref = pclClient->pclItemManager->FindItemRefFromUnique( pclitem->siUnique );
			if(ref > 0)
			{
				skilllevellimit = pclClient->pclItemManager->pclItemInfo[ Ref ]->GetSkillLevelLimit();
				skillup = pclClient->pclItemManager->pclItemInfo[ref]->GetSkillUnique();//å ���� ���� �Ǵ� ��ų����ũ�� ������ �´�.[2007.08.09 �ռ���]
			}			

			//if(pclClient->pclItemManager->pclItemInfo[ref]->siUpgradeSkillType == UPGRADESKILLTYPE_MAKE)			
			if( true == pclClient->pclSkillManager->IsManufactureSkill(skillup) == true ) // �ش�å�� ������� ���� ��ų�� ���� ��ų����Ʈ1�����ٴ¹��������ؽ�Ʈ������ - [2007.08.09 �ռ���]
			{	
				pText = GetTxtFromMgr(3607);
				StringCchPrintf(buffer, 1024, pText, skillname,skilllevellimit );
			}
			else if( true == pclClient->pclItemManager->IsItemInfoAtb( pclitem->siUnique, ITEMINFOATB_SKILLBOOK ) ) // ��ų���̸� ��ų����Ʈ�� ������ �����ϱ� �̰� ������. 																
			{
				CMagicAttribute*	  pMagicAttributePtr	= pclClient->pclMagicManager->GetMagicAttributePtr();
				SI32				  siParentKind			= pclSkillBookManager->GetSkillBookParentMagicFromItemUnique( pclitem->siUnique );
				stMagicAttributeData* pMagicAttributeData	= pMagicAttributePtr->GetMagicAttribute( siParentKind );
				
				// ���� ����
				if( 0 < siParentKind && pMagicAttributeData ) 
				{
					NTCHARString128 szBuf  = "";
					TCHAR szSkillname[128] = "";
					pclClient->pclSkillManager->GetSkillName( pclitem->GetSkillUnique( pclClient->pclItemManager ), szSkillname );
					StringCchPrintf(szBuf, 1024, GetTxtFromMgr(683), szSkillname, pclitem->GetSkillLevelLimit( pclClient->pclItemManager ) );
					StringCchCat(buffer, 1024, szBuf);

					szBuf = GetTxtFromMgr(30532);
					szBuf.Replace("#text#", pMagicAttributeData->strMagicName );
					StringCchCat(buffer, 1024, szBuf);
				}
				// ��ų�� ����.
				else
				{
					NTCHARString128 szBuf = "";
					StringCchPrintf(szBuf, 1024, GetTxtFromMgr(683), GetTxtFromMgr(30258), pclitem->GetSkillLevelLimit( pclClient->pclItemManager ) );
					StringCchCat(buffer, 1024, szBuf);
				}
			}
			else
			{
				pText = GetTxtFromMgr(3608);
				StringCchPrintf(buffer, 1024, pText, skillname );
			}
			

			// ������ Ȯ���Ѵ�. 
			if(bcolorswitch)
			{
				if(pclItemInfo[ref]->clCondition.GetCheckedText(szcondition, 1024, NULL, 0 , pclClient->pclCM->CR[1] ) == true)
				{
					StringCchCopy(temp, 1024, szcondition);
					StringCchCat(buffer, 1024, temp);
				}
			}
			else
			{
				if(pclItemInfo[ref]->clCondition.GetText(szcondition, 1024, NULL, 0  ) == true)
				{
					StringCchCopy(temp, 1024, szcondition);
					StringCchCat(buffer, 1024, temp);
				}
			}


		}
		break;

	case ITEMTYPE_MINERAL:
	case ITEMTYPE_TREE:
	case ITEMTYPE_CLOTH:
		break;

	case ITEMTYPE_SCROLL:
		{
			StringCchCopy(buffer, 1024, TEXT(""));

			// ���� ����� ������ �ִ°�. 
			switch(pclItemInfo[ref]->siScrollFunction)
			{
			case SCROLL_UNIQUE_FUNCTION_UPHITRATE:
				pText = GetTxtFromMgr(3569);
				StringCchPrintf(temp, 1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0, '%');
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_REDUCEDAMAGE:
				pText = GetTxtFromMgr(3570);
				StringCchPrintf(temp, 1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0, '%');
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_UPCRITICAL:
				pText = GetTxtFromMgr(3571);
				StringCchPrintf(temp, 1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0, '%');
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_POISON:
				pText = GetTxtFromMgr(3572);
				StringCchPrintf(temp,  1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0, '%');
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_ICE:
				pText = GetTxtFromMgr(3573);
				StringCchPrintf(temp,  1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0, '%');
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_DRAIN:
				pText = GetTxtFromMgr(3574);
				StringCchPrintf(temp,  1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0, '%');
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPAXE:
				pText = GetTxtFromMgr(3575);
				StringCchPrintf(temp,  1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPSPEAR:
				pText = GetTxtFromMgr(3576);
				StringCchPrintf(temp, 1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPSWORD:
				pText = GetTxtFromMgr(3577);
				StringCchPrintf(temp,  1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPBOW:
				pText = GetTxtFromMgr(3578);
				StringCchPrintf(temp,  1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPSTAFF:
				pText = GetTxtFromMgr(3579);
				StringCchPrintf(temp, 1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPGUN:
				pText = GetTxtFromMgr(3580);
				StringCchPrintf(temp, 1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPARMOUR:
				pText = GetTxtFromMgr(3581);
				StringCchPrintf(temp, 1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPHELMET:
				pText = GetTxtFromMgr(3582);
				StringCchPrintf(temp,  1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPDRESS:
				pText = GetTxtFromMgr(3583);
				StringCchPrintf(temp, 1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPHAT:
				pText = GetTxtFromMgr(3584);
				StringCchPrintf(temp,  1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPSHOES:
				pText = GetTxtFromMgr(3585);
				StringCchPrintf(temp,  1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPBELT:
				pText = GetTxtFromMgr(3586);
				StringCchPrintf(temp,  1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPNECK:
				pText = GetTxtFromMgr(3587);
				StringCchPrintf(temp,  1024, pText, pclItemInfo[ref]->siScrollAbility / 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			/*cyj �������ۼ� ����
			case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPRING:
				pText = GetTxtFromMgr(3588);
				StringCchPrintf(temp, 1024,  pText, pclItemInfo[ref]->siScrollAbility / 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			*/
			case SCROLL_UNIQUE_FUNCTION_UPMAXDURABILITY:
				pText = GetTxtFromMgr(3589);
				StringCchPrintf(temp, 1024, pText, pclItemInfo[ref]->siScrollAbility);
				StringCchCat(buffer, 1024, temp);
				break;				
			// ������� 
			case SCROLL_UNIQUE_FUNCTION_USESKILLUP_SWORD:
				pText = GetTxtFromMgr(3590);
				StringCchPrintf(temp,  1024, pText, pclItemInfo[ref]->siScrollAbility/ 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_USESKILLUP_SPEAR:
				pText = GetTxtFromMgr(3591);
				StringCchPrintf(temp,  1024, pText, pclItemInfo[ref]->siScrollAbility/ 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_USESKILLUP_AXE:
				pText = GetTxtFromMgr(3592);
				StringCchPrintf(temp, 1024, pText, pclItemInfo[ref]->siScrollAbility/ 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_USESKILLUP_BOW:
				pText = GetTxtFromMgr(3593);
				StringCchPrintf(temp, 1024, pText, pclItemInfo[ref]->siScrollAbility/ 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_USESKILLUP_GUN:
				pText = GetTxtFromMgr(3594);
				StringCchPrintf(temp,  1024, pText, pclItemInfo[ref]->siScrollAbility/ 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_USESKILLUP_STAFF:
				pText = GetTxtFromMgr(3595);
				StringCchPrintf(temp,  1024, pText, pclItemInfo[ref]->siScrollAbility/ 10.0);
				StringCchCat(buffer, 1024, temp);
				break;
			case SCROLL_UNIQUE_FUNCTION_MAKESKILLUPATIFACT:
				pText = GetTxtFromMgr(3592);
				StringCchPrintf(temp, 1024, pText, pclItemInfo[ref]->siScrollAbility/ 10.0);
				StringCchCat(buffer, 1024, temp);
				break;

			default:
				MsgBox(TEXT("vcd972"), TEXT("fd3:%d"), pclItemInfo[ref]->siScrollFunction);
				break;
			}
			
			// ��� ����Ǵ°� 
			if(pclItemInfo[ref]->siScrollAdaptAttach & ITEMATTACH_BELT)
			{
				pText = GetTxtFromMgr(3596);
				StringCchPrintf(temp,  1024, pText);
				StringCchCat(buffer, 1024, temp);
			}
			else if(pclItemInfo[ref]->siScrollAdaptAttach & ITEMATTACH_UPARMOUR)
			{
				pText = GetTxtFromMgr(3597);
				StringCchPrintf(temp, 1024, pText);
				StringCchCat(buffer, 1024, temp);
			}
			else if(pclItemInfo[ref]->siScrollAdaptAttach & ITEMATTACH_NEARWEAPON)
			{
				pText = GetTxtFromMgr(3598);
				StringCchPrintf(temp,  1024, pText);
				StringCchCat(buffer, 1024, temp);
			}
			else if(pclItemInfo[ref]->siScrollAdaptAttach & ITEMATTACH_FARWEAPON)
			{
				pText = GetTxtFromMgr(3599);
				StringCchPrintf(temp, 1024,  pText);
				StringCchCat(buffer, 1024, temp);
			}
			else if(pclItemInfo[ref]->siScrollAdaptAttach & ITEMATTACH_SHOES)
			{
				
				pText = GetTxtFromMgr(3600);
				StringCchPrintf(temp, 1024,   pText);
				StringCchCat(buffer, 1024, temp);
			}
			else if(pclItemInfo[ref]->siScrollAdaptAttach & ITEMATTACH_WEAPON)
			{
				pText = GetTxtFromMgr(3601);
				StringCchPrintf(temp, 1024,   pText);
				StringCchCat(buffer, 1024, temp);
			}
			else if(pclItemInfo[ref]->siScrollAdaptAttach & ITEMATTACH_ARMOUR)
			{
				pText = GetTxtFromMgr(3602);
				StringCchPrintf(temp, 1024,   pText);
				StringCchCat(buffer, 1024, temp);
			}
			else if(pclItemInfo[ref]->siScrollAdaptAttach & ITEMATTACH_SKILLUPDRESS)
			{
				pText = GetTxtFromMgr(3603);
				StringCchPrintf(temp, 1024,   pText);
				StringCchCat(buffer, 1024, temp);
			}
			else if(pclItemInfo[ref]->siScrollAdaptAttach & ITEMATTACH_USEWEAPONUPDRESS)
			{
				pText = GetTxtFromMgr(3604);
				StringCchPrintf(temp, 1024,  pText);
				StringCchCat(buffer, 1024, temp);
			}
			else if(pclItemInfo[ref]->siScrollAdaptAttach & ITEMATTACH_DURABLE)
			{
				pText = GetTxtFromMgr(3605);
				StringCchPrintf(temp, 1024,   pText);
				StringCchCat(buffer, 1024, temp);
			}
			//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ����ü Ÿ��.
/*			else if(pclItemInfo[ref]->siScrollAdaptAttach & ITEMATTACH_ATIFACT)
			{
				pText = GetTxtFromMgr(3604);
				StringCchPrintf(temp, 1024,  pText);
				StringCchCat(buffer, 1024, temp);
			}
*/
			else
			{
				MsgBox(TEXT("vc3fd"), TEXT("Vfed:%d %d"), pclitem->siUnique, pclItemInfo[ref]->siScrollAdaptAttach);
			}
			
			// ������ �Ҹ�. 
			if(pclItemInfo[ref]->siScrollDecDuration)
			{
				pText = GetTxtFromMgr(3606);
				StringCchPrintf(temp, 1024,   pText, pclItemInfo[ref]->siScrollDecDuration);
				StringCchCat(buffer, 1024, temp);
			}
		}
		break;

	case ITEMTYPE_ANIMAL:
		{
			SI32 skill = SKILL_HORSETRAINING;

			if(ref > 0)
			{
				if(pclClient->pclSkillManager->GetSkillName( skill, SkillName ) ==  true)
				{
					// ������ Ȯ���Ѵ�. 
				if(bcolorswitch)
					if(pclItemInfo[ref]->clCondition.GetCheckedText(szcondition, 1024, SkillName, skill , pclClient->pclCM->CR[1]  ) == true)
					{
						StringCchCopy(buffer, 1024, szcondition);
					}
					else
					{
						StringCchCopy(buffer, 1024, TEXT(""));
					}
				else
					if(pclItemInfo[ref]->clCondition.GetText(szcondition, 1024, SkillName, skill   ) == true)
					{
						StringCchCopy(buffer, 1024, szcondition);
					}
					else
					{
						StringCchCopy(buffer, 1024, TEXT(""));
					}

				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}
			}			
		}
		break;

	// �ƹ�Ÿ ����
	case ITEMTYPE_AVATAR_RING:
		{			

			// ������ Ȯ���Ѵ�. 
			if(bcolorswitch)
				if(pclItemInfo[ref]->clCondition.GetCheckedText(szcondition, 1024, NULL, 0 , pclClient->pclCM->CR[1] ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}
			else
				if(pclItemInfo[ref]->clCondition.GetText(szcondition, 1024, NULL, 0  ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}

				if(pclitem->clItemAvatarRing.uiAC)
				{
					pText = GetTxtFromMgr(3556);
					StringCchPrintf(temp, 1024, pText, 	pclitem->clItemAvatarRing.uiAC);
					StringCchCat(buffer, 1024, temp);
				}

				if(pclitem->clItemAvatarRing.uiStr)
				{
					pText = GetTxtFromMgr(799);
					StringCchPrintf(temp, 1024,  pText, pclitem->clItemAvatarRing.uiStr);
					StringCchCat(buffer, 1024, temp);
				}				
				if(pclitem->clItemAvatarRing.uiDex)
				{
					pText = GetTxtFromMgr(800);
					StringCchPrintf(temp, 1024,  pText, pclitem->clItemAvatarRing.uiDex);
					StringCchCat(buffer, 1024, temp);
				}
				if(pclitem->clItemAvatarRing.uiVit)
				{
					pText = GetTxtFromMgr(801);
					StringCchPrintf(temp, 1024,  pText, pclitem->clItemAvatarRing.uiVit);
					StringCchCat(buffer, 1024, temp);
				}
				if(pclitem->clItemAvatarRing.uiMag)
				{
					pText = GetTxtFromMgr(3530);
					StringCchPrintf(temp, 1024,  pText, pclitem->clItemAvatarRing.uiMag);
					StringCchCat(buffer, 1024, temp);
				}
				if(pclitem->clItemAvatarRing.uiLuk)
				{
					pText = GetTxtFromMgr(6453);
					StringCchPrintf(temp, 1024,  pText, pclitem->clItemAvatarRing.uiLuk);
					StringCchCat(buffer, 1024, temp);
				}
				if(pclitem->clItemAvatarRing.uiHnd)
				{
					pText = GetTxtFromMgr(6454);
					StringCchPrintf(temp, 1024,  pText, pclitem->clItemAvatarRing.uiHnd);
					StringCchCat(buffer, 1024, temp);
				}
				if(pclitem->clItemAvatarRing.uiWis)
				{
					pText = GetTxtFromMgr(10346);
					StringCchPrintf(temp, 1024,  pText, pclitem->clItemAvatarRing.uiWis);
					StringCchCat(buffer, 1024, temp);
				}

		}
		break;
	case ITEMTYPE_RING:
		{			

			// ������ Ȯ���Ѵ�. 
			if(bcolorswitch)
				if(pclItemInfo[ref]->clCondition.GetCheckedText(szcondition, 1024, NULL, 0 , pclClient->pclCM->CR[1] ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}
			else
				if(pclItemInfo[ref]->clCondition.GetText(szcondition, 1024, NULL, 0  ) == true)
				{
					StringCchCopy(buffer, 1024, szcondition);
				}
				else
				{
					StringCchCopy(buffer, 1024, TEXT(""));
				}

			if(pclitem->clItemRing.uiStr)
			{
				pText = GetTxtFromMgr(799);
				StringCchPrintf(temp, 1024,  pText, pclitem->clItemRing.uiStr);
				StringCchCat(buffer, 1024, temp);
			}
			if(pclitem->clItemRing.uiDex)
			{
				pText = GetTxtFromMgr(800);
				StringCchPrintf(temp, 1024,  pText, pclitem->clItemRing.uiDex);
				StringCchCat(buffer, 1024, temp);
			}
			if(pclitem->clItemRing.uiVit)
			{
				pText = GetTxtFromMgr(801);
				StringCchPrintf(temp, 1024,  pText, pclitem->clItemRing.uiVit);
				StringCchCat(buffer, 1024, temp);
			}
			if(pclitem->clItemRing.uiMag)
			{
				pText = GetTxtFromMgr(3530);
				StringCchPrintf(temp, 1024,  pText, pclitem->clItemRing.uiMag);
				StringCchCat(buffer, 1024, temp);
			}
			if(pclitem->clItemRing.uiLuk)
			{
				pText = GetTxtFromMgr(6453);
				StringCchPrintf(temp, 1024,  pText, pclitem->clItemRing.uiLuk);
				StringCchCat(buffer, 1024, temp);
			}
			if(pclitem->clItemRing.uiHnd)
			{
				pText = GetTxtFromMgr(6454);
				StringCchPrintf(temp, 1024,  pText, pclitem->clItemRing.uiHnd);
				StringCchCat(buffer, 1024, temp);
			}

		}
		break;
	case ITEMTYPE_ETC:
		{
			//[�߰� : Ȳ���� 2007. 12. 12 => �ų� �̺�Ʈ ���� ��ø ���� ����.]
			SI32 TextNum = 0;
			
			switch(pclitem->siUnique)
			{
				case 13033:	TextNum = 7713;	break;
				case 13034:	TextNum = 7714;	break;
				case 13035:	TextNum = 7715;	break;
				case 13036:	TextNum = 7716;	break;
				case 13037:	TextNum = 7717;	break;
				case 13038:	TextNum = 7718;	break;
			}
			if(TextNum)
			{
				pText = GetTxtFromMgr(TextNum);
				StringCchCat(buffer, 1024, pText);
			}
		}
		break;

	case ITEMTYPE_DOLL:	// ������ Ȯ���Ѵ�. 
		{
			SI32 kind = pclItemInfo[ref]->siMakeKind;
			if(pclClient->pclKindInfoSet->pclKI[kind]->IsAtb(ATB_DEFAULTSUMMON))
			{
				pText = GetTxtFromMgr(802);
				StringCchPrintf(temp, 1024,  pText, LIMIT_LEVEL_HATCH_DOLL);
				StringCchCopy(buffer, 1024, temp);
			}
		}
		break;
		
	case ITEMTYPE_TICKET:
		{
			// [����] �����߰�
			SI32 siToolTipTextNumber = 0;

			switch ( pclitem->siUnique )
			{
				case 24082:
				case 24084:
					{
						siToolTipTextNumber = 8379;
					}
					break;

			}

			if ( siToolTipTextNumber > 0 )
			{
				pText = GetTxtFromMgr( siToolTipTextNumber );
				StringCchCat( buffer, 1024, pText );
			}
		}
		break;

	case ITEMTYPE_IRON:
	case ITEMTYPE_DISH:
	case ITEMTYPE_PAPER:
	case ITEMTYPE_FISHINGROD:
	case ITEMTYPE_QUEST:
		break;
	case ITEMTYPE_COMPOSITIONMATERIAL:
		{
		}break;
	case ITEMTYPE_EVENTITEM:
		{
		}break;
	case ITEMTYPE_BOX:
		{
		}break;
	case ITEMTYPE_PREMIUM:
		{
		}break;
	default:
		MsgBox(TEXT("GetExplain()"), TEXT("238304:%d"), type);
		return FALSE;
	}

	// �ɼ� ������ �ִٸ�. 
	if(pclitem->clItemCommon.clOptionInfo.GetText(temp, 1024) == true)
	{
		StringCchCat(buffer, 1024, temp);
	}

	if ( true == pclClient->IsCountrySwitch( Switch_NewDurability ) )
	{
		// ������ ǥ��.
		/*if(maxdur == siForeverDurability && type == ITEMTYPE_BAG)
		{
			pText = GetTxtFromMgr(3609);
			StringCchPrintf(temp, 1024,  pText);
			StringCchCat(buffer, 1024, temp);
		}*/
		/*else if(maxdur && type == ITEMTYPE_BAG)
		{
		pText = GetTxtFromMgr(804);
		StringCchPrintf(temp, 1024,  pText, curdur, maxdur);
		StringCchCat(buffer, 1024, temp);
		}*/
		if ( maxdur == siForeverDurability )
		{
			// ���� �������̱⶧���� ǥ�ø� ���� �ʴ´�.
		}
		else if ( maxdur == siForeverDurability2 )
		{
			// ���� �������̱⶧���� ǥ�ø� ���� �ʴ´�.
		}
		else if( maxdur )
		{
			//pText = GetTxtFromMgr(804);
			//StringCchPrintf(temp, 1024,  pText, curdur, maxdur);
			//StringCchCat(buffer, 1024, temp);
			NTCHARString64 kDurExplain;
			GetDurabilityExplain( curdur, maxdur, kDurExplain, bcolorswitch );
			StringCchCat(buffer, 1024, kDurExplain);
		}
	}

	// Ÿ�Ժ� ������ ǥ��
	if ( true == pclClient->IsCountrySwitch( Switch_Durability ) )
	{
		if(pclitem != NULL && pclitem->IsSealingUp( pclClient->pclItemManager )	==false )
		{
			switch ( type )
			{
			case ITEMTYPE_SWORD:	// ��
			case ITEMTYPE_SPEAR:	// â 
			case ITEMTYPE_AXE:		// ����
			case ITEMTYPE_BOW:		// Ȱ
			case ITEMTYPE_GUN:		// ��
			case ITEMTYPE_STAFF:	// ������
			case ITEMTYPE_ARMOUR:	// ���� 
			case ITEMTYPE_HELMET:	// ���� 
			case ITEMTYPE_BELT:		// ��Ʈ
			case ITEMTYPE_SHOES:	// �Ź�
			case ITEMTYPE_MANTLE:	// ����
			case ITEMTYPE_DRESS:	// �Ǻ�
			case ITEMTYPE_HAT:		// ����
			case ITEMTYPE_RING:		// ����
			case ITEMTYPE_NECK:		// �����
			case ITEMTYPE_IRON:		// ö��
			case ITEMTYPE_PAPER:	// ����
			case ITEMTYPE_DISH:		// ����
			case ITEMTYPE_FISHINGROD:	// �
				//-----���Ӱ� �߰��� �ƹ�Ÿ ���ǵ�
			case ITEMTYPE_AVATAR_MANTLE:// �ƹ�Ÿ ����
			case ITEMTYPE_AVATAR_DRESS:	// �ƹ�Ÿ �Ǻ�
			case ITEMTYPE_AVATAR_HAT:	// �ƹ�Ÿ ����
			case ITEMTYPE_AVATAR_NECK:	// �ƹ�Ÿ �����
			case ITEMTYPE_AVATAR_RING:	// �ƹ�Ÿ ����
				{

					static TCHAR tmpbuf[256]  = {'\0'};
					static TCHAR tmpbuf2[256] = {'\0'};

					pText = GetTxtFromMgr(30277);

					TCHAR * szDurability = SI32ToString( MAX_DURABILITY_PERCENT_IN_CHINA )	;

					if(bcolorswitch)
					{
						StringCchPrintf(tmpbuf2,sizeof(tmpbuf2),TEXT("%s %s %s"),TEXT("<C05>"),szDurability,TEXT("</C>") );

						StringCchPrintf(tmpbuf, sizeof(tmpbuf), pText, tmpbuf2);
					}
					else
					{
						StringCchPrintf(tmpbuf, sizeof(tmpbuf), pText, szDurability);
					}

					StringCchCat(buffer, sizeof(buffer), tmpbuf);
				}
				break;
			}
		}
		
	}
	
	// ���԰� �߰��ȴ�


	if(bweightswitch)
	{
		pText = GetTxtFromMgr(805); 
		StringCchPrintf(temp, 1024,  pText, (float)weight/10.0);
	 
		StringCchCat(buffer, 1024, temp);
	}

/*	TCHAR usedate[128] = TEXT("") ;
	cltCharCommon* pclchar = (cltCharCommon*)pclClient->pclCM->CR[1] ;
	if ( pclchar->pclCI->clBI.uiKind )
	{
		for ( SI32 i = 0 ; i < MAX_ITEMNUM_PER_LIMITDATEITEM ; i ++ )
		{
			if ( pclchar->pclCI->clLimitDateItem.siItemUnique[i] == pclitem->siUnique )
			{
				cltDate cldate ;
				cldate.MakeFullDateFromDateVary(pclchar->pclCI->clLimitDateItem.siItemLimitDate[i]);
				if(cldate.GetDateText(usedate) == TRUE )
				{
					StringCchCat(buffer, 1024, usedate);
				}
			}
		}
	}*/


//////////////////////// �Ӽ� ǥ�� ////////////////////////////////


	// [����] �ƹ�Ÿ �Ǻ�, ���ڴ� �Ӽ� ���� ǥ�� �����ش�. �׿ܿ� ǥ�� ���Ұ͵鵵 ���⿡ �߰�.
	bool bElementInfoException = false;
	bElementInfoException = ( ITEMTYPE_AVATAR_DRESS == type || ITEMTYPE_AVATAR_HAT == type );


 	if(pclitem->Element.siType && true != bElementInfoException)
	{
		TCHAR buf[64] = {'\0'};
		TCHAR buf2[64] = {'\0'};

		SI32 siElementGrade = pclitem->Element.siPower;
		
		if(bcolorswitch)
		{
			StringCchPrintf(buf,64,TEXT("%s%s%s"),TEXT("<C13>"),GetEnchantTypeName(buf, pclitem->Element.siType), TEXT("</C>") );
			StringCchPrintf(buf2,64,TEXT("%s%d%s"),TEXT("<C13>[ "), siElementGrade , TEXT(" ]</C>") ); // ��������� 
						
		}
		else
		{
			StringCchCopy(buf,64, GetEnchantTypeName(buf, pclitem->Element.siType));
			StringCchPrintf(buf2,64,TEXT("[ %d ]"), siElementGrade );
		}
						
		pText = GetTxtFromMgr(5901);
		StringCchPrintf(temp,1024,pText,buf , buf2);
	
		StringCchCat(buffer, sizeof(buffer) ,temp);


		// ������ �Ӽ� ���ݷ�, ����� �Ӽ� ������ ǥ�����ش�
		switch( type )
		{
			case ITEMTYPE_SWORD:
			case ITEMTYPE_SPEAR:
			case ITEMTYPE_STAFF:
			case ITEMTYPE_AXE:
			case ITEMTYPE_BOW:
			case ITEMTYPE_GUN:
			
			{
					SI32 EnchantDamage = GetEnchantDamageFromGrade( pclitem->Element.siPower );
					pText = GetTxtFromMgr(7013);

					if(bcolorswitch)
					{
						StringCchPrintf( buf2 , 64 , TEXT("<C13>%d</C>") , EnchantDamage );// ��������� 
					}
					else
					{
						StringCchPrintf( buf2 , 64 , TEXT("%d") , EnchantDamage );
					}

					StringCchPrintf( buf , 64 , pText , buf2 );					
					StringCchCat(buffer, sizeof(buffer) ,buf);
				}
				break;
			default:
				{
					SI32 EnchantDef = pclitem->GetEnchantACFrom( this , true , pclitem->Element.siType );
				
					pText = GetTxtFromMgr(7014);

					if(bcolorswitch)
					{
						StringCchPrintf( buf2 , 64 , TEXT("<C13>%d</C>") , EnchantDef ); // ��������� 
					}
					else
					{
						StringCchPrintf( buf2 , 64 , TEXT("%d") , EnchantDef );
					}

					StringCchPrintf( buf , 64 , pText , buf2 );

					StringCchCat(buffer, sizeof(buffer) ,buf);
				}
				break;
		}

	}

///////////////////////////////////////////////////////////////////


	//cyj �Ⱓ ����
	SI32 siItemStatus = 0 ;

	// �Ⱓ��
	if ( pclitem->uiDateYear > 0 && pclitem->uiDateMonth > 0 && pclitem->uiDateDay > 0 && pclitem->uiDateUseDay > 0 )
	{
		TCHAR usedate[128] = TEXT("") ;
		pText = GetTxtFromMgr(5600) ;
		StringCchPrintf(usedate, 128, pText,pclitem->uiDateYear+2000,pclitem->uiDateMonth,pclitem->uiDateDay) ;
		StringCchCat(buffer, sizeof(buffer), usedate);

		NDate ndate;
		ndate.SetDate(pclitem->uiDateYear+2000,pclitem->uiDateMonth,pclitem->uiDateDay);
		ndate.AddDays(pclitem->uiDateUseDay);

		memset(usedate,0,128);
		pText = GetTxtFromMgr(5601) ;
		StringCchPrintf(usedate, 128, pText,ndate.m_uiYear,ndate.m_uiMonth,ndate.m_uiDay);
		StringCchCat(buffer, sizeof(buffer), usedate);
	}
	else if ( pclitem->uiDateYear == 0 && pclitem->uiDateMonth == 0 && pclitem->uiDateDay == 0 && pclitem->uiDateUseDay > 0 &&
		IsItemInfoAtb(pclitem->siUnique,ITEMINFOATB_ITEMMALL) == true )
	{
		TCHAR usedate[128] = TEXT("") ;
		pText = GetTxtFromMgr(5658) ;
		StringCchPrintf(usedate, 128, pText,pclitem->uiDateUseDay) ;
		StringCchCat(buffer, sizeof(buffer), usedate);
	}
	else if ( pclitem->uiDateYear == 0 && pclitem->uiDateMonth == 0 && pclitem->uiDateDay == 0 && pclitem->uiDateUseDay > 0 &&
		IsItemInfoAtb(pclitem->siUnique,ITEMINFOATB_ITEMMALL) == false &&//�����۸� ��ǰ�̸� �ڵ����� ���� ��¥ ���
		( GetItemAtb(pclitem->siUnique) & ITEMATB_OBJECT) 
		)
	{
		
		TCHAR usedate[128] = TEXT("") ;
		if ( basicswitch )
		{
			// ���ǰ�� ǰ�������Ⱓ�� �������� �ʴ´�.
			if( pclitem->clItemCommon.clCommonInfo.uiRareInfo != RARELEVEL_5 )
			{
				pText = GetTxtFromMgr(5615) ;
				StringCchPrintf(usedate, 128, pText,pclitem->uiDateUseDay);
				StringCchCat(buffer, sizeof(buffer), usedate);
			}
		}
		else
		{

			// cyj ����̴� �к�Ǯ�� ���� ǰ�������Ⱓ �������� �ʴ´�.
			// LeeKH ���ǰ�� ǰ�������Ⱓ�� �������� �ʴ´�.
			if (type != ITEMTYPE_NECK &&
				pclitem->clItemCommon.clCommonInfo.uiRareInfo != RARELEVEL_5)
			{
				pText = GetTxtFromMgr(5615); // ǰ�������Ⱓ %d 
				StringCchPrintf(usedate, 128, pText,pclitem->uiDateUseDay);
				StringCchCat(buffer, sizeof(buffer), usedate);
			}
			

			pText = GetTxtFromMgr(5895) ; // ���� : �к���
			
			if(bcolorswitch)
			{
				StringCchCat(buffer, sizeof(buffer), TEXT("<C08>"));
				StringCchCat(buffer, sizeof(buffer), pText);
				StringCchCat(buffer, sizeof(buffer), TEXT("</C>"));
			}
			else
			{
				StringCchCat(buffer, sizeof(buffer), pText);
			}
		}
	}
	else if ( pclitem->IsSealingUp(this) )
	{
		if( !basicswitch)
		{
			pText = GetTxtFromMgr(5895) ; // ���� : �к���

			if(bcolorswitch)
			{
				StringCchCat(buffer, sizeof(buffer), TEXT("<C08>"));
				StringCchCat(buffer, sizeof(buffer), pText);
				StringCchCat(buffer, sizeof(buffer), TEXT("</C>"));
			}
			else
			{
				StringCchCat(buffer, sizeof(buffer), pText);
			}
		}			
	}

	if ( pclitem->IsBelonging(this) )
	{	
			pText = GetTxtFromMgr(5898) ; // ���� : �ͼ�
			StringCchCat(buffer, sizeof(buffer), pText);
	
	}

	// �⺻���� �� ���϶�
	if ( type == ITEMTYPE_BOW    || type == ITEMTYPE_GUN    || type == ITEMTYPE_AXE   || 
		 type == ITEMTYPE_STAFF  || type == ITEMTYPE_SPEAR  || type == ITEMTYPE_SWORD || 
		 type == ITEMTYPE_ARMOUR || type == ITEMTYPE_HELMET || type == ITEMTYPE_BELT	)
	{
		// ����, ���� ������ ��� ǥ��
		if ( pclItemInfo[ref]->IsItemInfoAtb(CANUSEITEM_TYPE_EAST) == true)
		{
			pText = GetTxtFromMgr(6029);

			if ( bcolorswitch && pclitem->IsCorrectPrivateEquip(this, siKind) == false)
			{
				StringCchCat(buffer, sizeof(buffer), TEXT("<C08>"));
				StringCchCat(buffer, sizeof(buffer), pText);
				StringCchCat(buffer, sizeof(buffer), TEXT("</C>"));
			}
			else
			{
				StringCchCat(buffer, sizeof(buffer), pText);
			}
		}
		else if ( pclItemInfo[ref]->IsItemInfoAtb(CANUSEITEM_TYPE_WEST) == true)
		{
			pText = GetTxtFromMgr(6030);

			if ( bcolorswitch && pclitem->IsCorrectPrivateEquip(this, siKind) == false)
			{
				StringCchCat(buffer, sizeof(buffer), TEXT("<C08>"));
				StringCchCat(buffer, sizeof(buffer), pText);
				StringCchCat(buffer, sizeof(buffer), TEXT("</C>"));
			}
			else
			{
				StringCchCat(buffer, sizeof(buffer), pText);
			}

		}
		else 
		{
			pText = GetTxtFromMgr(6028);
			StringCchCat(buffer, sizeof(buffer), pText);
		}
	}

	
	// [����] ���ո��� �߰� �� ������ �̸� ��� ��� ��ü. 
	if (   (pclitem->GetRareType() == RARELEVEL_1)	  // ��ǰ
		|| (pclitem->GetRareType() == RARELEVEL_2)	  // ȣǰ
		|| (pclitem->GetRareType() == RARELEVEL_5)	) // �ű�
	{
		static TCHAR tmpbuf[256]  = {'\0'};
		static TCHAR tmpbuf2[256] = {'\0'};

		// ������ �۽� ���̵� �����ۿ� ���� �ִٸ�!
		if( pclitem->siMakerPersonID > 0 )
		{
			TCHAR name[MAX_PLAYER_NAME];

			if (GetMadePersonName(pclitem->siMakerPersonID, name, MAX_PLAYER_NAME))
			{
				pText = GetTxtFromMgr(5894);

				if(bcolorswitch)
				{
					StringCchPrintf(tmpbuf2,sizeof(tmpbuf2),TEXT("%s%s%s"),TEXT("<C05>"),name,TEXT("</C>") );

					StringCchPrintf(tmpbuf, sizeof(tmpbuf), pText, tmpbuf2);
				}
				else
				{
					StringCchPrintf(tmpbuf, sizeof(tmpbuf), pText, name);
				}

				StringCchCat(buffer, sizeof(buffer), tmpbuf);
			}
		}
		else
		{
			cltPersonNameInfo clPersonInfo;
			if( GetMadePersonNameNew( pclitem->siSID, &clPersonInfo, MAX_PLAYER_NAME ) )
			{
				// [����] '[NONAME]' �̶�� �������� ǥ�õ��� �ʾƾ� �ϴ� �̸���
				if ( _tcscmp(clPersonInfo.szPersonName, TEXT("[NONAME]")) != 0 )
				{
					pText = GetTxtFromMgr(5894);

					if(bcolorswitch)
					{
						StringCchPrintf(tmpbuf2, sizeof(tmpbuf2), TEXT("%s%s%s"), TEXT("<C05>"), clPersonInfo.szPersonName, TEXT("</C>") );

						StringCchPrintf(tmpbuf, sizeof(tmpbuf), pText, tmpbuf2);
					}
					else
					{
						StringCchPrintf(tmpbuf, sizeof(tmpbuf), pText, clPersonInfo.szPersonName);
					}

					StringCchCat(buffer, sizeof(buffer), tmpbuf);
				}
			}
		}
	}



	//-------------------------------------
	// ���� ���� ����
	//--------------------------------------
	if (pclClient->siServiceArea == ConstServiceArea_English)
	{	
		if ( pclItemInfo[ref]->siTradeServerMinNum > 0 )
		{
			TCHAR *pText = GetTxtFromMgr(6201);
			StringCchCat(buffer, sizeof(buffer), pText);
		}
		else
		{
			TCHAR *pText = GetTxtFromMgr(6202);
			StringCchCat(buffer, sizeof(buffer), pText);
		}
	}

	/*
	if (pclClient->siServiceArea == ConstServiceArea_NHNChina)
	{	
		if ( pclItemInfo[ref]->siTradeServerMinNum > 0 )
		{
			TCHAR *pText = GetTxtFromMgr(6201);
			StringCchCat(buffer, sizeof(buffer), pText);
		}
		else
		{
			TCHAR *pText = GetTxtFromMgr(6202);
			StringCchCat(buffer, sizeof(buffer), pText);
		}
	}
	*/

	//Ư��ǰ ǥ��
	if (IsItemInfoAtb(pclitem->siUnique,ITEMINFOATB_SPECIAL_GLOBAL))
	{
		TCHAR* pText = GetTxtFromMgr(6645);
		StringCchCat(buffer, sizeof(buffer), pText);
	}
	if (IsItemInfoAtb(pclitem->siUnique,ITEMINFOATB_SPECIAL_JAPAN))
	{
		TCHAR* pText = GetTxtFromMgr(6644);
		StringCchCat(buffer, sizeof(buffer), pText);
	}
	if (IsItemInfoAtb(pclitem->siUnique,ITEMINFOATB_SPECIAL_KOREA))
	{
		TCHAR* pText = GetTxtFromMgr(6643);
		StringCchCat(buffer, sizeof(buffer), pText);
	}

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	//�ڱ��� - 2009615 - �����ۿ� �Ϲ� ����ü ���� �� �ƹ�Ÿ ����ü ������ ���� 
	TCHAR usedCrystalNum[128] = TEXT("") ;
	if( pclitem->GetUseCrystalNum() > 0) //������ �ִ�.  = ������ ���� �� �ִ� �������̴�.
	{

		switch(type)
		{
		case ITEMTYPE_AVATAR_MANTLE:
		case ITEMTYPE_AVATAR_DRESS:
		case ITEMTYPE_AVATAR_HAT:
		case ITEMTYPE_AVATAR_NECK:
		case ITEMTYPE_AVATAR_RING:
			{
				// �ƹ�Ÿ ����ü ��ȭ ���� ���� ó��
				GetExplainEnhanceAvatarItem(buffer,ConstEntireTmpBufSize,type,pclitem);
				break;
			}
		default:
			{
				TCHAR* pText = GetTxtFromMgr(7999);

				TCHAR buf1[50] = TEXT("") ;

				StringCchPrintf(buf1, 50,pText,pclitem->GetUseCrystalNum());

				if(bcolorswitch)
					StringCchPrintf(usedCrystalNum, 1024, TEXT("%s%s%s"),TEXT("<C05>"),buf1,TEXT("</C>"));
				else
					StringCchPrintf(usedCrystalNum, 1024, TEXT("%s"),buf1);					

				StringCchCat(buffer, sizeof(buffer), usedCrystalNum);

				for(int i= 0; i < MAX_CRYSTAL_NUM;i++)
				{
					SI16 cAbliltyType = pclitem->cltItemCrytal[i].GetCrystalAblilty();
					SI16 cAbliltyTypeNum = pclitem->cltItemCrytal[i].GetCrystalAbilityNum();

					if(cAbliltyType>0) // �������� �ϴ� �ɷ��� �ִ�.
					{			
						TCHAR buf[64] = TEXT("") ;
						TCHAR buf2[128] = TEXT("") ;
						TCHAR CrystalReturnString[50] = TEXT("") ;

						SI16 nowDub = (SI16)((pclitem->cltItemCrytal[i].GetDurability()*100) / 30000); // �ִ� ������ �� - 30000 ����.
						SI16 MaxDub = (SI16)((pclitem->cltItemCrytal[i].GetMaxDurability()*100) /30000);

						GetCrystalAbilityTypeName(buf, cAbliltyType,cAbliltyTypeNum, CrystalReturnString);

						if(bcolorswitch)
						{
							StringCchPrintf(buf,64,TEXT("%s%d%s%d%s"),TEXT("<C05>["), nowDub ,TEXT("/"),MaxDub, TEXT("]") ); // �Ķ���. 
							StringCchPrintf(buf2,128,TEXT("%s%s"),CrystalReturnString, TEXT("\r </C>"));							
						}
						else
						{
							StringCchPrintf(buf,64,TEXT("%s%d%s%d%s"),TEXT("["), nowDub ,TEXT("/"),MaxDub, TEXT("]") );  
							StringCchPrintf(buf2,128,TEXT("%s%s"),CrystalReturnString,TEXT("\r "));							
						}								
						StringCchPrintf(temp,1024,TEXT("%s %s"),buf , buf2);	
						StringCchCat(buffer, 1024 ,temp);
					}
				}		

				break;
			}
		}

		
	}

	
	//-----------------------------------
	
	///������ �̸��� ǰ��,  ������ ����

	TCHAR itemname[128];
	if(pclitem->GetFullName(this, itemname, 128) == true)
	{
		if(numbswitch == true)
		{
			pText = GetTxtFromMgr(806);
			StringCchPrintf(ptext, MAX_TOOLTIP_MSG_SIZE, pText, itemname, pclitem->GetItemNum(), pclItemTypeInfo[type]->szName, buffer);
			ptext[MAX_TOOLTIP_MSG_SIZE-1] = '\0';		// �޸� ���� �ڵ� - by LEEKH 2008-02-04
		}
		else
		{
			if( bcolorswitch && pclitem->Element.siType)
			{
				pText = GetTxtFromMgr(807);
				TCHAR szBuffer[256];
				szBuffer[0] = 0;
   				StringCchPrintf(szBuffer, 256 , TEXT("<C13><B1>%s</B></C>") , itemname);
				StringCchPrintf(ptext, MAX_TOOLTIP_MSG_SIZE, pText, szBuffer , pclItemTypeInfo[type]->szName, buffer);
                ptext[MAX_TOOLTIP_MSG_SIZE-1] = '\0';		// �޸� ���� �ڵ� - by LEEKH 2008-02-04
			}
			else
			{
				pText = GetTxtFromMgr(807);
				StringCchPrintf(ptext, MAX_TOOLTIP_MSG_SIZE, pText, itemname, pclItemTypeInfo[type]->szName, buffer);
				ptext[MAX_TOOLTIP_MSG_SIZE-1] = '\0';		// �޸� ���� �ڵ� - by LEEKH 2008-02-04
			}
			
		}
	}

	return TRUE;
}

TCHAR* cltItemManagerClient::GetEnchantTypeName(TCHAR* szEnchantName, SI32 siEnchantType)
{
	TCHAR* pText = NULL;

	switch(siEnchantType)
	{
	case ENCHANT_TYPE_FIRE_A:
		pText = GetTxtFromMgr(5902);
		break;
	case ENCHANT_TYPE_FIRE_D:
		pText = GetTxtFromMgr(5903);
		break;
	case ENCHANT_TYPE_WATER_A:
		pText = GetTxtFromMgr(5904);
		break;
	case ENCHANT_TYPE_WATER_D:
		pText = GetTxtFromMgr(5905);
		break;
	case ENCHANT_TYPE_WIND_A:
		pText = GetTxtFromMgr(5906);
		break;
	case ENCHANT_TYPE_WIND_D:
		pText = GetTxtFromMgr(5907);
		break;
	case ENCHANT_TYPE_GROUND_A:
		pText = GetTxtFromMgr(5908);
		break;
	case ENCHANT_TYPE_GROUND_D:
		pText = GetTxtFromMgr(5909);
		break;
	default:
		pText = GetTxtFromMgr(5910);
		break;		
	}

	return pText;
}

COLORREF cltItemManagerClient::GetItemNameColor(cltItem * pclItem)
{
	// �Ӽ� Ÿ���� �ִ� �༮�̶�� �̸��� ���������
	if( pclItem->Element.siType > 0 )
	{
		return GetChatEditColor(CHATEDIT_COLOR_VIOLET);
	}
	

	return GetChatEditColor(CHATEDIT_COLOR_BLACK);;
}

//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
void cltItemManagerClient::GetCrystalAbilityTypeName(TCHAR* szCrystalAbilityName, SI16 siCrystalAbilityType ,SI16 cAbliltyTypeNum,TCHAR* szCrystalReturnString)
{
	TCHAR* pText = NULL;
	TCHAR tembuf[50] = {'\0'};

	switch(siCrystalAbilityType)
	{
	case CRYSTALABILITY_STATE_STR: 
	case CRYSTALABILITY_AVATAR_STATE_STR:
		{
			pText = GetTxtFromMgr(1785);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_STATE_DEX:
	case CRYSTALABILITY_AVATAR_STATE_DEX:
		{
			pText = GetTxtFromMgr(1786);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_STATE_MAG:
	case CRYSTALABILITY_AVATAR_STATE_MAG:
		{
			pText = GetTxtFromMgr(1787);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_STATE_VIT:
	case CRYSTALABILITY_AVATAR_STATE_VIT:
		{
			pText = GetTxtFromMgr(1788);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_STATE_LUK:
	case CRYSTALABILITY_AVATAR_STATE_LUK:
		{
			pText = GetTxtFromMgr(10016);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_STATE_HND:
	case CRYSTALABILITY_AVATAR_STATE_HND:
		{
			pText = GetTxtFromMgr(3100);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_SUMMON:
		{
			pText = GetTxtFromMgr(2878);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_FARM:
		{
			pText = GetTxtFromMgr(2883);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_MINE:
		{
			pText = GetTxtFromMgr(2884);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_FISH:
		{
			pText = GetTxtFromMgr(2881);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_MAKEFOOD:
		{
			pText = GetTxtFromMgr(2842);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_CAPTURE:
		{
			pText = GetTxtFromMgr(2877);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_HORSETRAINING:
		{
			pText = GetTxtFromMgr(2876);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_MAKEIRON1:
		{
			pText = GetTxtFromMgr(2871);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_MAKETOOL1:
		{
			pText = GetTxtFromMgr(5774);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;		
	case CRYSTALABILITY_SKILL_MAKEMED:
		{
			pText = GetTxtFromMgr(2851);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_MAKESWORD1:
		{
			pText = GetTxtFromMgr(2854);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_MAKESPEAR1:
		{
			pText = GetTxtFromMgr(2855);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_MAKEAXE1:
		{
			pText = GetTxtFromMgr(2856);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_MAKESTAFF1:
		{
			pText = GetTxtFromMgr(2857);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_MAKEBOW1:
		{
			pText = GetTxtFromMgr(2858);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_MAKEGUN1:
		{
			pText = GetTxtFromMgr(2859);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_MAKEARMOUR1:
		{
			pText = GetTxtFromMgr(2852);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_MAKEHELMET1:
		{
			pText = GetTxtFromMgr(2853);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_MAKESHOES1:
		{
			pText = GetTxtFromMgr(2861);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_MAKEBELT1:
		{
			pText = GetTxtFromMgr(2862);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_ARTIFACT:
		{
			pText = GetTxtFromMgr(8225);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_USESWORD1:
		{
			pText = GetTxtFromMgr(2865);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_USESPEAR1:
		{
			pText = GetTxtFromMgr(2866);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_USEAXE1:
		{
			pText = GetTxtFromMgr(2867);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_USESTAFF1:
		{
			pText = GetTxtFromMgr(2868);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_USEBOW1:
		{
			pText = GetTxtFromMgr(2869);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_USEGUN1:
		{
			pText = GetTxtFromMgr(2870);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_STATE_WIS:
	case CRYSTALABILITY_AVATAR_STATE_WIS:
		{
			pText = GetTxtFromMgr(8000);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;

	// %�� �ٴ´�. 
	case CRYSTALABILITY_EFFECT_PHYSICAL_ATTACK:
		{
			pText = GetTxtFromMgr(8001);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_EFFECT_MAGICAL_ATTACK:
		{
			pText = GetTxtFromMgr(8002);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_EFFECT_PHYSICAL_HITRATE:
		{
			pText = GetTxtFromMgr(8003);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_EFFECT_MAGICAL_HITRATE:
		{
			pText = GetTxtFromMgr(8004);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_EFFECT_PHYSICAL_DODGERATE:
		{
			pText = GetTxtFromMgr(8005);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_EFFECT_MAGICAL_DODGERATE:
		{
			pText = GetTxtFromMgr(8006);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_EFFECT_PHYSICAL_DEFENSIVERATE:
		{
			pText = GetTxtFromMgr(8007);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_EFFECT_MAGICAL_DEFENSIVERATE:
		{
			pText = GetTxtFromMgr(8008);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_EFFECT_HITPOINT:
		{
			pText = GetTxtFromMgr(8009);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_EFFECT_MANAPOINT:
		{
			pText = GetTxtFromMgr(8010);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_EFFECT_WEIGHT:
		{
			pText = GetTxtFromMgr(8011);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_ATTRIBUTE_FIREATTACK:
		{
			pText = GetTxtFromMgr(8012);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_ATTRIBUTE_WATERATTACK:
		{
			pText = GetTxtFromMgr(8013);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_ATTRIBUTE_WINDATTACK:
		{
			pText = GetTxtFromMgr(8014);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_ATTRIBUTE_EARTHATTACK:
		{
			pText = GetTxtFromMgr(8015);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_ATTRIBUTE_FIREDEFENCE:
		{
			pText = GetTxtFromMgr(8016);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_ATTRIBUTE_WATERDEFENCE:
		{
			pText = GetTxtFromMgr(8017);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_ATTRIBUTE_WINDDEFENCE:
		{
			pText = GetTxtFromMgr(8018);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_ATTRIBUTE_EARTHDEFENCE:
		{
			pText = GetTxtFromMgr(8019);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;

	case CRYSTALABILITY_SKILL_ALLMAKESKILL:	
		{
			pText = GetTxtFromMgr(8020);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_ALLAVATARSKILL:	
	case CRYSTALABILITY_AVATAR_SKILL_ALLAVATARSKILL:
		{
			pText = GetTxtFromMgr(40171);  // ��� �ƹ�Ÿ ���  - 
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_AVATAR_ALLMAKESKILL:
		{
			pText = GetTxtFromMgr(30262);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_ALLWEAPONSKILL:
	case CRYSTALABILITY_AVATAR_ALLWEAPONSKILL:
		{
			pText = GetTxtFromMgr(8021);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_ALLPRODUCTSKILL:
	case CRYSTALABILITY_AVATAR_ALLPRODUCTSKILL:
		{
			pText = GetTxtFromMgr(8022);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;
	case CRYSTALABILITY_SKILL_ALLSKILL:
		{
			pText = GetTxtFromMgr(8023);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;

	case CRYSTALABILITY_EFFECT_PHYSICAL_MIN_ATTACK:
		{
			pText = GetTxtFromMgr(8374);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_EFFECT_PHYSICAL_MAX_ATTACK:
		{
			pText = GetTxtFromMgr(8375);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_EFFECT_MAGICAL_MIN_ATTACK:
		{
			pText = GetTxtFromMgr(8376);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_EFFECT_MAGICAL_MAX_ATTACK:
		{
			pText = GetTxtFromMgr(8377);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;
	case CRYSTALABILITY_SPECIAL_DEATHBLOW:
		{
			pText = GetTxtFromMgr(8765);
			StringCchPrintf(tembuf,50,TEXT("%s+%d%s"),pText,cAbliltyTypeNum ,TEXT("%"));
		}
		break;

	default:
		{
			pText = GetTxtFromMgr(5910);
			StringCchPrintf(tembuf,50,TEXT("%s+%d"),pText,cAbliltyTypeNum );
		}
		break;		
	}

	StringCchCopy(szCrystalReturnString, 50, tembuf);

	//return szCrystalReturnString;
}

//�ڱ��� - 20090615 - �ƹ�Ÿ ����ü ���� ���ڿ�( ���� ���ڿ� ��ü ���� ������, ���� ���ڿ� ũ��, ������ Ÿ��, ������ ���� ��)
BOOL	cltItemManagerClient::GetExplainEnhanceAvatarItem(TCHAR* pszExplain,SI32 siExplainSize, SI32 siItemType, cltItem* pclitem)
{
	// ���� ó��
	if( NULL == pszExplain)
	{
		return FALSE;
	}
	if(siExplainSize <= 0)
	{
		return FALSE;
	}
	if((siItemType !=ITEMTYPE_AVATAR_MANTLE)
		&& (siItemType !=ITEMTYPE_AVATAR_DRESS)
		&& (siItemType !=ITEMTYPE_AVATAR_HAT)
		&& (siItemType !=ITEMTYPE_AVATAR_NECK)
		&& (siItemType !=ITEMTYPE_AVATAR_RING))
	{
		return FALSE;
	}
	if (NULL == pclitem)
	{
		return FALSE;
	}

	// �ӽ� ���ҽ� ���ڿ� ������
	TCHAR* pszTmpText = GetTxtFromMgr(30253);
	// �ӽ� ���� - ��� �� Ȱ��
	TCHAR szTmpszExplain[ConstTmpBufSize];
	ZeroMemory(szTmpszExplain, ConstTmpBufSize * sizeof(TCHAR));

	//// 1. ����ü ��ȭ ���� ���� ���ڿ�
	StringCchPrintf(szTmpszExplain, ConstTmpBufSize, TEXT("%s%s"), pszTmpText,TEXT("\r "));
	StringCchCat(pszExplain, siExplainSize ,szTmpszExplain);

	//// 2. ��ȭ ���� �ɷ�ġ ���� �ִ� ��
	const int ConstAbilityTypeNum = 4;

	//	��� ������ ����ü�� ���� �ε��� ����Ʈ => ���� 0�� �����ʹ� ��� ���� �ʴ´�.
	SI32   siUsableCrystalNumList[ConstAbilityTypeNum];
	ZeroMemory(siUsableCrystalNumList, ConstAbilityTypeNum * sizeof(SI32));


	//	��ȭ ������ ����ü�� ���� �ε��� ����
	SI32 siCanEnhanceCrystalNumListCount = 0;
	SI16 siMaxAvatarCrystalAbility = 0;
	for(SI32 siUsableCrystalNumListIndex = CRYSTALABILITY_AVATAR_STATE_WIS; siUsableCrystalNumListIndex <= CRYSTALABILITY_AVATAR_ALLPRODUCTSKILL;siUsableCrystalNumListIndex++)
	{
		// �ִ�� ���� �� �� �ִ� ����ü �ɷ�ġ ��
		siMaxAvatarCrystalAbility = pclClient->pclItemManager->GetMaxAbatarCrystalAbilityNum(siItemType, siUsableCrystalNumListIndex);

		if(siMaxAvatarCrystalAbility > 0 ) // 0���� ũ�� �ش� �������� ��ȭ ���� 
		{	
			siUsableCrystalNumList[siCanEnhanceCrystalNumListCount] = siUsableCrystalNumListIndex;
			++siCanEnhanceCrystalNumListCount;
		}

		// �迭�� ���� �ʰ��� 
		if(siCanEnhanceCrystalNumListCount == ConstAbilityTypeNum)
		{
			break;
		}
	}	

	// 3. ���� ��ȭ ���� ���ڿ� 
	SI32 siAddedCrystalNum = 0;
	SI32 siCompareType = 0;
	SI16 siAbliltyType = 0;
	SI16 siAbliltyTypeNum = 0;
	for(SI32 siSocketIndex = 0; siSocketIndex < MAX_CRYSTAL_NUM;siSocketIndex++)
	{
		ZeroMemory(szTmpszExplain, ConstTmpBufSize * sizeof(TCHAR));

		siAbliltyType = pclitem->cltItemCrytal[siSocketIndex].GetCrystalAblilty();
		siAbliltyTypeNum = pclitem->cltItemCrytal[siSocketIndex].GetCrystalAbilityNum();
		siMaxAvatarCrystalAbility = pclClient->pclItemManager->GetMaxAbatarCrystalAbilityNum(siItemType, siAbliltyType);

		if(siAbliltyType>0) // �������� �ϴ� �ɷ��� �ִ�.
		{			
			GetAvatarCrystalAbilityTypeName(siMaxAvatarCrystalAbility,siAbliltyType,siAbliltyTypeNum, szTmpszExplain, ConstTmpBufSize);

			StringCchCat(pszExplain, siExplainSize ,szTmpszExplain);
			++siAddedCrystalNum;

			switch(siAbliltyType)
			{
			case CRYSTALABILITY_AVATAR_STATE_STR:
			case CRYSTALABILITY_AVATAR_STATE_DEX:
			case CRYSTALABILITY_AVATAR_STATE_MAG:
			case CRYSTALABILITY_AVATAR_STATE_VIT:
			case CRYSTALABILITY_AVATAR_STATE_LUK:
			case CRYSTALABILITY_AVATAR_STATE_HND:
			case CRYSTALABILITY_AVATAR_STATE_WIS:
				{
					siCompareType = CRYSTALABILITY_AVATAR_STATE_WIS; 
					break;
				}
			default :
				{
					siCompareType = siAbliltyType;
					break;
				}
			}
		}
	}	

	// 4. ��� ���� ����ü ��
	SI32 siUseableCrystalCount = pclitem->GetUseCrystalNum() - siAddedCrystalNum;
	ZeroMemory(szTmpszExplain, ConstTmpBufSize * sizeof(TCHAR));
	pszTmpText = GetTxtFromMgr(30254);

	StringCchPrintf(szTmpszExplain, ConstTmpBufSize,TEXT("%s:%d%s"),pszTmpText,siUseableCrystalCount,TEXT("\r "));
	StringCchCat(pszExplain, siExplainSize ,szTmpszExplain);

	// 5. ��� ���� �ɷ�ġ ���ڿ�
	TCHAR szUseableCrystalText[ConstTmpBufSize];
	ZeroMemory(szUseableCrystalText, ConstTmpBufSize * sizeof(TCHAR));
	StringCchCat(szUseableCrystalText, ConstTmpBufSize ,TEXT("("));
	for(SI32 siUsableCrystalNumListIndex= 0; siUsableCrystalNumListIndex < siCanEnhanceCrystalNumListCount;siUsableCrystalNumListIndex++)
	{
		ZeroMemory(szTmpszExplain, ConstTmpBufSize * sizeof(TCHAR));

		switch(siUsableCrystalNumList[siUsableCrystalNumListIndex])
		{
		case CRYSTALABILITY_AVATAR_STATE_WIS:
			{
				pszTmpText = GetTxtFromMgr(30255);
				break;
			}
		case CRYSTALABILITY_AVATAR_ALLMAKESKILL:
			{
				pszTmpText = GetTxtFromMgr(30260);
				break;
			}
		case CRYSTALABILITY_AVATAR_ALLWEAPONSKILL:
			{
				pszTmpText = GetTxtFromMgr(30258);
				break;
			}
		case CRYSTALABILITY_AVATAR_ALLPRODUCTSKILL:
			{
				pszTmpText = GetTxtFromMgr(30259);
				break;
			}
		default:
			{
				continue;
			}
		}

		if((siUsableCrystalNumListIndex + 1) == siCanEnhanceCrystalNumListCount)
			StringCchPrintf(szTmpszExplain, ConstTmpBufSize,TEXT("%s"),pszTmpText);
		else
			StringCchPrintf(szTmpszExplain, ConstTmpBufSize,TEXT("%s,"),pszTmpText);

		StringCchCat(szUseableCrystalText, ConstTmpBufSize ,szTmpszExplain);
	}	
	StringCchCat(szUseableCrystalText, ConstTmpBufSize ,TEXT(")\r\n "));
	StringCchCat(pszExplain, siExplainSize ,szUseableCrystalText);
	
	return TRUE;
}

//�ڱ��� - 20090615 - �ƹ�Ÿ ����ü ���� ��ȭ ���� ���ڿ�(����ü�� �ִ� ���� �� �� �ִ� ��, ����ü �ɷ� Ÿ��, ������ �ɷ�ġ ��ġ, ���� ���� ����, ���� ���� ���� ũ��)
BOOL cltItemManagerClient::GetAvatarCrystalAbilityTypeName(SI16 siMaxCrystalAbility, SI16 siCrystalAbilityType ,SI16 siAbliltyTypeNum,TCHAR* pszCrystalReturnString,SI32 siCrystalReturnStringSize)
{
	// ���� ó��
	if ( NULL == pszCrystalReturnString )
	{
		return FALSE;
	}
	if (siCrystalReturnStringSize <= 0)
	{
		return FALSE;
	}
	
	// �ӽ� ����
	TCHAR* pszTmpText = NULL;
	TCHAR* pszTmpTextSub = NULL;
	TCHAR szTmpBuf[ConstTmpBufSize];
	ZeroMemory(szTmpBuf, ConstTmpBufSize * sizeof(TCHAR));

	//����ü �ɷ�ġ ������ ���� ���ڿ� ó��
	switch(siCrystalAbilityType)
	{
	case CRYSTALABILITY_AVATAR_STATE_STR: //str ��
		{
			pszTmpText = GetTxtFromMgr(1785);
			pszTmpTextSub = GetTxtFromMgr(30257);
		}
		break;
	case CRYSTALABILITY_AVATAR_STATE_DEX: //agi ���߷�
		{
			pszTmpText = GetTxtFromMgr(1786);
			pszTmpTextSub = GetTxtFromMgr(30257);
		}
		break;
	case CRYSTALABILITY_AVATAR_STATE_MAG: //wiz ����
		{
			pszTmpText = GetTxtFromMgr(1787);
			pszTmpTextSub = GetTxtFromMgr(30257);
		}
		break;
	case CRYSTALABILITY_AVATAR_STATE_VIT: //vit �����
		{
			pszTmpText = GetTxtFromMgr(1788);
			pszTmpTextSub = GetTxtFromMgr(30257);
		}
		break;
	case CRYSTALABILITY_AVATAR_STATE_LUK: //luk ���
		{
			pszTmpText = GetTxtFromMgr(10016);
			pszTmpTextSub = GetTxtFromMgr(30257);
		}
		break;
	case CRYSTALABILITY_AVATAR_STATE_HND: //dex ������
		{
			pszTmpText = GetTxtFromMgr(4502);
			pszTmpTextSub = GetTxtFromMgr(30257);
		}
		break;
	case CRYSTALABILITY_AVATAR_STATE_WIS: //int ����
		{
			pszTmpText = GetTxtFromMgr(8000);
			pszTmpTextSub = GetTxtFromMgr(30257);
		}
		break;
	case CRYSTALABILITY_AVATAR_ALLMAKESKILL:		
		{
			pszTmpText = GetTxtFromMgr(30262);
			pszTmpTextSub = GetTxtFromMgr(30256);
		}
		break;
	case CRYSTALABILITY_AVATAR_ALLWEAPONSKILL:		
		{
			pszTmpText = GetTxtFromMgr(30258);
			pszTmpTextSub = GetTxtFromMgr(30256);
		}
		break;
	case CRYSTALABILITY_AVATAR_ALLPRODUCTSKILL:
		{
			pszTmpText = GetTxtFromMgr(30259);
			pszTmpTextSub = GetTxtFromMgr(30256);
		}
		break;

	default:
		{
			return FALSE;
		}
	}
	
	StringCchPrintf(szTmpBuf,ConstTmpBufSize,TEXT("%s %s: %s%d/%d%s"),pszTmpText,pszTmpTextSub,TEXT("<C05>"),siAbliltyTypeNum,siMaxCrystalAbility,TEXT("</C>\r "));
	StringCchCopy(pszCrystalReturnString, siCrystalReturnStringSize, szTmpBuf);

	return TRUE;
}


//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
void cltItemManagerClient::GetCrystalAbilityTypeCondition(SI16 siCrystalAbilityType ,SI16 conditionLevel ,TCHAR* szCrystalReturnString)
{
	TCHAR* pText1 = NULL;
	TCHAR* pText2 = NULL;
	TCHAR* pText3 = NULL;

	TCHAR buf1[128] = {'\0'};
	TCHAR tembuf[128] = {'\0'};

	// ���� ���� 
	pText1 = GetTxtFromMgr(8381); //��������
	StringCchPrintf(buf1,128,pText1,conditionLevel);
	StringCchCat(tembuf, 128 ,buf1);
	// ----------------------------------------------------------------------------------
	//KHY - 0805 - ��Ʈ�彺 ����. - ���հ��� ����.
	/*
	// ���� ���� 
	pText1 = GetTxtFromMgr(8382); // ���� ���� 
	pText2 = GetTxtFromMgr(8388); //��
	pText3 = GetTxtFromMgr(8389); //����
	
	switch(siCrystalAbilityType)
	{
		case CRYSTALABILITY_STATE_STR: 
		case CRYSTALABILITY_STATE_DEX: 
		case CRYSTALABILITY_STATE_MAG: 
		case CRYSTALABILITY_STATE_VIT: 
		case CRYSTALABILITY_STATE_LUK: 
		case CRYSTALABILITY_STATE_HND: 
		case CRYSTALABILITY_STATE_WIS:

		case CRYSTALABILITY_ATTRIBUTE_FIREDEFENCE: 
		case CRYSTALABILITY_ATTRIBUTE_WATERDEFENCE: 
		case CRYSTALABILITY_ATTRIBUTE_WINDDEFENCE: 
		case CRYSTALABILITY_ATTRIBUTE_EARTHDEFENCE: 

		case CRYSTALABILITY_SKILL_SUMMON	:
		case CRYSTALABILITY_SKILL_FARM	:
		case CRYSTALABILITY_SKILL_MINE	:
		case CRYSTALABILITY_SKILL_FISH	:
		case CRYSTALABILITY_SKILL_MAKEFOOD	:
		case CRYSTALABILITY_SKILL_CAPTURE	:
		case CRYSTALABILITY_SKILL_HORSETRAINING	:
		case CRYSTALABILITY_SKILL_MAKEIRON1	:
		case CRYSTALABILITY_SKILL_MAKETOOL1	:
		case CRYSTALABILITY_SKILL_MAKEMED	:
		case CRYSTALABILITY_SKILL_MAKESWORD1	:
		case CRYSTALABILITY_SKILL_MAKESPEAR1	:
		case CRYSTALABILITY_SKILL_MAKEAXE1	:
		case CRYSTALABILITY_SKILL_MAKESTAFF1	:
		case CRYSTALABILITY_SKILL_MAKEBOW1	:
		case CRYSTALABILITY_SKILL_MAKEGUN1	:
		case CRYSTALABILITY_SKILL_MAKEARMOUR1	:
		case CRYSTALABILITY_SKILL_MAKEHELMET1	:
		case CRYSTALABILITY_SKILL_MAKESHOES1	:
		case CRYSTALABILITY_SKILL_MAKEBELT1	:
		case CRYSTALABILITY_SKILL_USESWORD1	:
		case CRYSTALABILITY_SKILL_USESPEAR1	:
		case CRYSTALABILITY_SKILL_USEAXE1	:
		case CRYSTALABILITY_SKILL_USESTAFF1	:
		case CRYSTALABILITY_SKILL_USEBOW1	:
		case CRYSTALABILITY_SKILL_USEGUN1	:
		case CRYSTALABILITY_SKILL_ARTIFACT	:

		case CRYSTALABILITY_EFFECT_PHYSICAL_HITRATE	:
		case CRYSTALABILITY_EFFECT_MAGICAL_HITRATE	:
		case CRYSTALABILITY_EFFECT_PHYSICAL_DODGERATE	:
		case CRYSTALABILITY_EFFECT_MAGICAL_DODGERATE	:
		case CRYSTALABILITY_EFFECT_PHYSICAL_DEFENSIVERATE	:
		case CRYSTALABILITY_EFFECT_MAGICAL_DEFENSIVERATE	:
		case CRYSTALABILITY_EFFECT_HITPOINT	:
		case CRYSTALABILITY_EFFECT_MANAPOINT	:
		case CRYSTALABILITY_EFFECT_WEIGHT	:
			{
				StringCchPrintf(buf1,128,pText1,pText2); // �� ����.
			}
			break;			
		case CRYSTALABILITY_EFFECT_PHYSICAL_ATTACK	:
		case CRYSTALABILITY_EFFECT_MAGICAL_ATTACK	:
		case CRYSTALABILITY_EFFECT_PHYSICAL_MIN_ATTACK	:
		case CRYSTALABILITY_EFFECT_PHYSICAL_MAX_ATTACK	:
		case CRYSTALABILITY_EFFECT_MAGICAL_MIN_ATTACK	:
		case CRYSTALABILITY_EFFECT_MAGICAL_MAX_ATTACK	:

		case CRYSTALABILITY_ATTRIBUTE_FIREATTACK	:
		case CRYSTALABILITY_ATTRIBUTE_WATERATTACK	:
		case CRYSTALABILITY_ATTRIBUTE_WINDATTACK	:
		case CRYSTALABILITY_ATTRIBUTE_EARTHATTACK	:
			{
				StringCchPrintf(buf1,128,pText1,pText3); // ���� ����.
			}
			break;

	}

	StringCchCat(tembuf, 128 ,buf1);
	*/
	// ----------------------------------------------------------------------------------
	
	// �ߺ� ����. 
	pText1 = GetTxtFromMgr(8383); // �ߺ� ����
	pText2 = GetTxtFromMgr(1617); // ����
	//pText3 = GetTxtFromMgr(1618); // �Ұ�
	/*
	switch(siCrystalAbilityType)
	{
		case CRYSTALABILITY_STATE_STR: 
		case CRYSTALABILITY_STATE_DEX: 
		case CRYSTALABILITY_STATE_MAG: 
		case CRYSTALABILITY_STATE_VIT: 
		case CRYSTALABILITY_STATE_LUK: 
		case CRYSTALABILITY_STATE_HND: 
		case CRYSTALABILITY_STATE_WIS	:

		case CRYSTALABILITY_ATTRIBUTE_FIREDEFENCE: 
		case CRYSTALABILITY_ATTRIBUTE_WATERDEFENCE: 
		case CRYSTALABILITY_ATTRIBUTE_WINDDEFENCE: 
		case CRYSTALABILITY_ATTRIBUTE_EARTHDEFENCE: 

		case CRYSTALABILITY_SKILL_SUMMON	:
		case CRYSTALABILITY_SKILL_FARM	:
		case CRYSTALABILITY_SKILL_MINE	:
		case CRYSTALABILITY_SKILL_FISH	:
		case CRYSTALABILITY_SKILL_MAKEFOOD	:
		case CRYSTALABILITY_SKILL_CAPTURE	:
		case CRYSTALABILITY_SKILL_HORSETRAINING	:
		case CRYSTALABILITY_SKILL_MAKEIRON1	:
		case CRYSTALABILITY_SKILL_MAKETOOL1	:
		case CRYSTALABILITY_SKILL_MAKEMED	:
		case CRYSTALABILITY_SKILL_MAKESWORD1	:
		case CRYSTALABILITY_SKILL_MAKESPEAR1	:
		case CRYSTALABILITY_SKILL_MAKEAXE1	:
		case CRYSTALABILITY_SKILL_MAKESTAFF1	:
		case CRYSTALABILITY_SKILL_MAKEBOW1	:
		case CRYSTALABILITY_SKILL_MAKEGUN1	:
		case CRYSTALABILITY_SKILL_MAKEARMOUR1	:
		case CRYSTALABILITY_SKILL_MAKEHELMET1	:
		case CRYSTALABILITY_SKILL_MAKESHOES1	:
		case CRYSTALABILITY_SKILL_MAKEBELT1	:
		case CRYSTALABILITY_SKILL_USESWORD1	:
		case CRYSTALABILITY_SKILL_USESPEAR1	:
		case CRYSTALABILITY_SKILL_USEAXE1	:
		case CRYSTALABILITY_SKILL_USESTAFF1	:
		case CRYSTALABILITY_SKILL_USEBOW1	:
		case CRYSTALABILITY_SKILL_USEGUN1	:
		case CRYSTALABILITY_SKILL_ARTIFACT	:

		case CRYSTALABILITY_EFFECT_PHYSICAL_HITRATE	:
		case CRYSTALABILITY_EFFECT_MAGICAL_HITRATE	:
		case CRYSTALABILITY_EFFECT_PHYSICAL_DODGERATE	:
		case CRYSTALABILITY_EFFECT_MAGICAL_DODGERATE	:
		case CRYSTALABILITY_EFFECT_PHYSICAL_DEFENSIVERATE	:
		case CRYSTALABILITY_EFFECT_MAGICAL_DEFENSIVERATE	:
		case CRYSTALABILITY_EFFECT_HITPOINT	:
		case CRYSTALABILITY_EFFECT_MANAPOINT	:
		case CRYSTALABILITY_EFFECT_WEIGHT	:
			{
				StringCchPrintf(buf1,128,pText1,pText3); // �Ұ�
			}
			break;

		case CRYSTALABILITY_EFFECT_PHYSICAL_ATTACK	:
		case CRYSTALABILITY_EFFECT_MAGICAL_ATTACK	:
		case CRYSTALABILITY_EFFECT_PHYSICAL_MIN_ATTACK	:
		case CRYSTALABILITY_EFFECT_PHYSICAL_MAX_ATTACK	:
		case CRYSTALABILITY_EFFECT_MAGICAL_MIN_ATTACK	:
		case CRYSTALABILITY_EFFECT_MAGICAL_MAX_ATTACK	:
			
		case CRYSTALABILITY_ATTRIBUTE_FIREATTACK	:
		case CRYSTALABILITY_ATTRIBUTE_WATERATTACK	:
		case CRYSTALABILITY_ATTRIBUTE_WINDATTACK	:
		case CRYSTALABILITY_ATTRIBUTE_EARTHATTACK	:
			{
				StringCchPrintf(buf1,128,pText1,pText2); // ����.
			}
			break;

	}
*/
	StringCchPrintf(buf1,128,pText1,pText2); // ����.
	StringCchCat(tembuf, 128 ,buf1);		

	// ----------------------------------------------------------------------------------

	//�ɷ���ø

	pText1 = GetTxtFromMgr(8384);//�ɷ���ø
	//pText2 = GetTxtFromMgr(1617); // ����
	pText3 = GetTxtFromMgr(1618); // �Ұ�
/*	
	switch(siCrystalAbilityType)
	{
		case CRYSTALABILITY_STATE_STR: 
		case CRYSTALABILITY_STATE_DEX: 
		case CRYSTALABILITY_STATE_MAG: 
		case CRYSTALABILITY_STATE_VIT: 
		case CRYSTALABILITY_STATE_LUK: 
		case CRYSTALABILITY_STATE_HND: 
		case CRYSTALABILITY_STATE_WIS:

		case CRYSTALABILITY_EFFECT_PHYSICAL_HITRATE	:
		case CRYSTALABILITY_EFFECT_MAGICAL_HITRATE	:
		case CRYSTALABILITY_EFFECT_PHYSICAL_DODGERATE	:
		case CRYSTALABILITY_EFFECT_MAGICAL_DODGERATE	:
		case CRYSTALABILITY_EFFECT_PHYSICAL_DEFENSIVERATE	:
		case CRYSTALABILITY_EFFECT_MAGICAL_DEFENSIVERATE	:
		case CRYSTALABILITY_EFFECT_HITPOINT	:
		case CRYSTALABILITY_EFFECT_MANAPOINT	:
		case CRYSTALABILITY_EFFECT_WEIGHT	:

		case CRYSTALABILITY_ATTRIBUTE_FIREDEFENCE: 
		case CRYSTALABILITY_ATTRIBUTE_WATERDEFENCE: 
		case CRYSTALABILITY_ATTRIBUTE_WINDDEFENCE: 
		case CRYSTALABILITY_ATTRIBUTE_EARTHDEFENCE: 
			{
				StringCchPrintf(buf1,128,pText1,pText2); // ���� 
			}
			break;
		case CRYSTALABILITY_SKILL_SUMMON	:
		case CRYSTALABILITY_SKILL_FARM	:
		case CRYSTALABILITY_SKILL_MINE	:
		case CRYSTALABILITY_SKILL_FISH	:
		case CRYSTALABILITY_SKILL_MAKEFOOD	:
		case CRYSTALABILITY_SKILL_CAPTURE	:
		case CRYSTALABILITY_SKILL_HORSETRAINING	:
		case CRYSTALABILITY_SKILL_MAKEIRON1	:
		case CRYSTALABILITY_SKILL_MAKETOOL1	:
		case CRYSTALABILITY_SKILL_MAKEMED	:
		case CRYSTALABILITY_SKILL_MAKESWORD1	:
		case CRYSTALABILITY_SKILL_MAKESPEAR1	:
		case CRYSTALABILITY_SKILL_MAKEAXE1	:
		case CRYSTALABILITY_SKILL_MAKESTAFF1	:
		case CRYSTALABILITY_SKILL_MAKEBOW1	:
		case CRYSTALABILITY_SKILL_MAKEGUN1	:
		case CRYSTALABILITY_SKILL_MAKEARMOUR1	:
		case CRYSTALABILITY_SKILL_MAKEHELMET1	:
		case CRYSTALABILITY_SKILL_MAKESHOES1	:
		case CRYSTALABILITY_SKILL_MAKEBELT1	:
		case CRYSTALABILITY_SKILL_USESWORD1	:
		case CRYSTALABILITY_SKILL_USESPEAR1	:
		case CRYSTALABILITY_SKILL_USEAXE1	:
		case CRYSTALABILITY_SKILL_USESTAFF1	:
		case CRYSTALABILITY_SKILL_USEBOW1	:
		case CRYSTALABILITY_SKILL_USEGUN1	:
		case CRYSTALABILITY_SKILL_ARTIFACT	:
			
		case CRYSTALABILITY_EFFECT_PHYSICAL_ATTACK	:
		case CRYSTALABILITY_EFFECT_MAGICAL_ATTACK	:
		case CRYSTALABILITY_EFFECT_PHYSICAL_MIN_ATTACK	:
		case CRYSTALABILITY_EFFECT_PHYSICAL_MAX_ATTACK	:
		case CRYSTALABILITY_EFFECT_MAGICAL_MIN_ATTACK	:
		case CRYSTALABILITY_EFFECT_MAGICAL_MAX_ATTACK	:

		case CRYSTALABILITY_ATTRIBUTE_FIREATTACK	:
		case CRYSTALABILITY_ATTRIBUTE_WATERATTACK	:
		case CRYSTALABILITY_ATTRIBUTE_WINDATTACK	:
		case CRYSTALABILITY_ATTRIBUTE_EARTHATTACK	:
			{
				StringCchPrintf(buf1,128,pText1,pText3); // �Ұ�
			}
			break;

	}
*/
	StringCchPrintf(buf1,128,pText1,pText3); // �Ұ�.
	StringCchCat(tembuf, 128 ,buf1);		

	// ----------------------------------------------------------------------------------

	StringCchCopy(szCrystalReturnString, 128, tembuf);

	//return szCrystalReturnString;
}

void cltItemManagerClient::GetDurabilityExplain( UI16 curdur, UI16 maxdur,  NTCHARString64& kDurExplain, bool bcolorwitch )
{
	NTCHARString64	kDurText( GetTxtFromMgr(1805) ); 
	kDurExplain += "";

	kDurExplain += kDurText;
	kDurExplain += " :";

	if		(   0 >= curdur )
	{
		// TRUERED
		if( bcolorwitch )	kDurExplain += "<C8> ";
	}
	if		(   1 <= curdur && curdur <= 100 )
	{
		// TRUERED
		if( bcolorwitch )	kDurExplain += "<C8> ";
	}
	else if ( 101 <= curdur && curdur <= 200 )
	{
		// LIGHTREDYELLOW
		if( bcolorwitch )	kDurExplain += "<C14> ";
	}
	else if ( 201 <= curdur )
	{
		// TRUEBLUE
		if( bcolorwitch )	kDurExplain += "<C15> ";
	}

    kDurExplain += UI16ToString( curdur );
	if( bcolorwitch )	kDurExplain += "</C>";

	if( bcolorwitch )	kDurExplain += "<C15>";
	kDurExplain += "/";
	kDurExplain += UI16ToString( maxdur );
	if( bcolorwitch )	kDurExplain += "</C>";

	kDurExplain += "\r ";
}