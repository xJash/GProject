#ifndef _DBMSG_H
#define _DBMSG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\GoonZuWorld\Common\Item\ItemCommon\cltItem.h"
#include "..\..\GoonZuWorld\Common\Char\CharCommon\Char-EconomyInfo.h"
#include "..\..\GoonZuWorld\Common\Skill\Skill.h"
#include "..\..\GoonZuWorld\Server\Rank\Rank.h"
#include "..\..\GoonZuWorld\CommonLogic\StructureClass\StructureClass.h"
#include "..\..\GoonZuWorld\Common\Letter\Letter.h"
#include "..\..\GoonZuWorld\Common\Char\CharCommon\Char-Common.h"

#include "NDate.h"

enum {

	//-----------------------------------
	// Person���� ���� 
	//-----------------------------------
	// �� ���� ����. 
	DBMSG_REQUEST_SETHORSE	= 0,						//000[�°�]�� �Ѹ����� ������ �����Ѵ�.
	DBMSG_RESPONSE_SETHORSE,							//001[�°�]

	DBMSG_REQUEST_SETRIDEHORSE,							//002[�°�]Ÿ�� �ִ� ���� ������ �����Ѵ�. 
	DBMSG_RESPONSE_SETRIDEHORSE,						//003[�°�]

	DBMSG_REQUEST_SETAUTOFOOD,							//004[�°�]�ڵ� �Ա� ����� �����Ѵ�. 
	DBMSG_RESPONSE_SETAUTOFOOD,							//005[�°�]


	DBMSG_REQUEST_PERSONTOTALINFOCREATE,				//006[�°�] Person ���� [��û]
	DBMSG_RESPONSE_PERSONTOTALINFOCREATE,				//007[�°�] Person ���� [����]

	DBMSG_REQUEST_PERSONLISTINFOGET,					//008[�°�]Person ���� ��� [��û]
	DBMSG_RESPONSE_PERSONLISTINFOGET,					//009[�°�]Person ���� ��� [����]

	DBMSG_REQUEST_PERSONTOTALINFOGET,					//010[�°�]Person�� ��ü ������ �������� ��û�Ѵ�.(PersonID�� �ٰŷ�. ) 
	DBMSG_RESPONSE_PERSONTOTALINFOGET,					//011[�°�]

	DBMSG_REQUEST_PERSONTOTALINFOSET,					//012[�°�]Person�� ��ü ������ �����ϵ��� ��û�Ѵ�. 
	DBMSG_RESPONSE_PERSONTOTALINFOSET,					//013[�°�]

	DBMSG_REQUEST_PERSONTOTALINFOGETBYIDNUM,			//014[�°�]Person�� ��ü ������ �������� ��û�Ѵ�.(IDNum�� �ٰŷ�.) 
	DBMSG_RESPONSE_PERSONTOTALINFOGETBYIDNUM,			//015[�°�]	

	DBMSG_REQUEST_PERSONTOTALINFODELETE,				//016[�°�]Person�� ��ü ������ �����ϵ��� ��û�Ѵ�. 
	DBMSG_RESPONSE_PERSONTOTALINFODELETE,				//017[�°�]

	DBMSG_REQUEST_PERSONTOTALINFOPREDELETE,				//018[����]Person�� ��ü ������ �����ϱ��� ��⸦ ��û�Ѵ�. 
	DBMSG_RESPONSE_PERSONTOTALINFOPREDELETE,			//019[����]

	DBMSG_REQUEST_PERSONSTOCKACCOUNTGET,				//020[�°�]Person�� �ֽ� ���� ������ ��û�Ѵ�.
	DBMSG_RESPONSE_PERSONSTOCKACCOUNTGET,				//021[�°�]

	DBMSG_REQUEST_SETLEVELINFO,							//022[�°�]Level ���� ������ ����ϵ��� ��û�Ѵ�. 
	DBMSG_RESPONSE_SETLEVELINFO,						//023[�°�]

	DBMSG_REQUEST_SETBONUSINFO,							//024[�°�]���ʽ� �й� ���� ������ ����ϵ��� ��û�Ѵ�. 
	DBMSG_RESPONSE_SETBONUSINFO,						//025[�°�]

	DBMSG_REQUEST_SETPOSLIFEMANA,						//026[�°�]Pos, Life, Mana�� �����ϵ��� ��û�Ѵ�.
	DBMSG_RESPONSE_SETPOSLIFEMANA,						//027[�°�]

	DBMSG_REQUEST_SETHEALTH,							//028[�°�]�ǰ� ������ �����Ѵ�. 
	DBMSG_RESPONSE_SETHEALTH,							//029[�°�]

	DBMSG_REQUEST_SETQUESTINFO,							//030[�°�]����Ʈ ������ �����Ѵ�. 
	DBMSG_RESPONSE_SETQUESTINFO,						//031[�°�]

	DBMSG_REQUEST_SETSPECIALQUESTINFO,					//032[�°�]Ư�� ����Ʈ ������ �����Ѵ�. 
	DBMSG_RESPONSE_SETSPECIALQUESTINFO,					//033[�°�]

	DBMSG_REQUEST_SETHAPPYBEANQUESTINFO,				//034[��]�����ϰ� �ִ� ���Ǻ�����Ʈ ������ �����Ѵ�.
	DBMSG_RESPONSE_SETHAPPYBEANQUESTINFO,				//035KHY - 0822 - ���Ǻ� ����Ʈ �߰�.

	DBMSG_REQUEST_GETHAPPYBEANQUESTINFO,				//036[��]�����ϰ� �ִ� ���Ǻ� ����Ʈ ������ �����Ѵ�.
	DBMSG_RESPONSE_GETHAPPYBEANQUESTINFO,				//037KHY - 0822 - ���Ǻ� ����Ʈ �߰�.

	DBMSG_REQUEST_SETNAMINGQUESTINFO,					//038[����]�����ϰ� �ִ� ��Ī ����Ʈ ������ �����Ѵ�.
	DBMSG_RESPONSE_SETNAMINGQUESTINFO,					//039[����] 

	DBMSG_REQUEST_SETPERSONNAMINGINFO,					//040[����]������ ��Ī ���� ����
	DBMSG_RESPONSE_SETPERSONNAMINGINFO,					//041[����]

	DBMSG_REQUEST_GETPERSONNAMINGINFO,					//042[����]������ ��Ī ���� ������
	DBMSG_RESPONSE_GETPERSONNAMINGINFO,					//043[����]

	DBMSG_REQUEST_SETPERSONCURRENTNAMING,				//044[����]������ ���� ����ϴ� ���̹� ����
	DBMSG_RESPONSE_SETPERSONCURRENTNAMING,				//045[����]

	DBMSG_REQUEST_CHANGEMONEY,							//046[�°�]���ݾ��� ������Ų��. 
	DBMSG_RESPONSE_CHANGEMONEY,							//047[�°�]	

	DBMSG_REQUEST_CHANGEEXP,							//048[�°�]����ġ�� ������Ų��. 
	DBMSG_RESPONSE_CHANGEEXP,							//049[�°�]	

	DBMSG_REQUEST_CHANGEFAMEEXP,						//050[����]�� ����ġ�� ������Ų��. 
	DBMSG_RESPONSE_CHANGEFAMEEXP,						//051[����]

	DBMSG_REQUEST_SETCURRENTHORSEPRICE,					//052[���] ���� �ü��� ����
	DBMSG_RESPONSE_SETCURRENTHORSEPRICE,				//053[���]

	DBMSG_REQUEST_GETCURRENTHORSEPRICE,					//054[���] ���� �ü��� ���´�.
	DBMSG_RESPONSE_GETCURRENTHORSEPRICE,				//055[���]

	DBMSG_REQUEST_USERID,								//056[���] ĳ���� ���� �ƴ�, ���� ���̵� ��û�� ( �̴� Ȩ������ ����Ϸ���.. )
	DBMSG_RESPONSE_USERID,								//057[���] ����

	DBMSG_REQUEST_RECOMMENDPERSON,						//058[���]
	DBMSG_RESPONSE_RECOMMENDPERSON,						//059[���]

	DBMSG_REQUEST_HORSENAMECHANGE,						//060[���] �� �̸� ����
	DBMSG_RESPONSE_HORSENAMECHANGE,						//061[���]

	DBMSG_REQUEST_MOVEMONEY,							//062[�°�]���� A���Լ� B���Է� �ű���� ��û. 
	DBMSG_RESPONSE_MOVEMONEY,							//063[�°�]

	DBMSG_REQUEST_SETSCHOOL,							//064[�°�]�б����. 
	DBMSG_RESPONSE_SETSCHOOL,							//065[�°�]

	DBMSG_REQUEST_SETFATHER,							//066[�°�]���µ��. 
	DBMSG_RESPONSE_SETFATHER,							//067[�°�]


	DBMSG_REQUEST_PERSONSIMPLEINFO,						//068[�°�]ĳ������ ���� ���� ��û.  
	DBMSG_RESPONSE_PERSONSIMPLEINFO,					//069[�°�]

	DBMSG_REQUEST_INCREASECHILDNUMBER,					//070[�°�]�缺�� ���� ���� ���ϰ��� ��û. 
	DBMSG_RESPONSE_INCREASECHILDNUMBER,					//071[�°�]

	DBMSG_REQUEST_GETCHILDLIST,							//072[�°�]�������� ����Ʈ�� ���Ѵ�. 
	DBMSG_RESPONSE_GETCHILDLIST,						//073[�°�]

	DBMSG_REQUEST_INITSTATUS,							//074[�°�]�������ͽ� �ʱ�ȭ ��û. 
	DBMSG_RESPONSE_INITSTATUS,							//075[�°�]
 
	DBMSG_REQUEST_GUILTYINFORECORD,						//076[����]���� ���� ��� 
	DBMSG_RESPONSE_GUILTYINFORECORD,					//077[����]

	DBMSG_REQUEST_LOGOUTRECORD,							//078[���]�α׾ƿ� �ð��� ����ϱ� ���ؼ�.

	DBMSG_REQUEST_PRIZE_GAMEEVENT,						//079[�ؿ�] ���� �̺�Ʈ�� ���Ͽ�
	DBMSG_RESPONSE_PRIZE_GAMEEVENT,						//080

	DBMSG_REQUEST_COUNTATTACK_INFO,						//081[�ؿ�] ������ �ݰ� �̺�Ʈ
	DBMSG_RESPONSE_COUNTATTACK_INFO,					//082

	DBMSG_REQUEST_SETGREETING,							//083[����] �λ縻 ���� 
	DBMSG_RESPONSE_SETGREETING,							//084[����]

	DBMSG_REQUEST_GETGREETING,							//085[����] �λ縻 ������
	DBMSG_RESPONSE_GETGREETING,							//086[����]


	DBMSG_REQUEST_GETWARRANKINFO,						//087
	DBMSG_RESPONSE_GETWARRANKINFO,						//088

	DBMSG_REQUEST_SETWARRANKINFO,						//089
	DBMSG_RESPONSE_SETWARRANKINFO,						//090

	DBMSG_REQUEST_ITEMMAKERNAME,						//091
	DBMSG_RESPONSE_ITEMMAKERNAME,						//092

	DBMSG_REQUEST_CHANGERECOMMENDPOINT,					//093[����] ��õ���� ����Ʈ�� ������Ʈ ��.
	DBMSG_RESPONSE_CHANGERECOMMENDPOINT,				//094

	DBMSG_REQUEST_GETRECOMMENDPOINT,					//095
	DBMSG_RESPONSE_GETRECOMMENDPOINT,					//096

	DBMSG_REQUEST_SETCOUNTRY,							//097[����]���� �����Ѵ�.
	DBMSG_RESPONSE_SETCOUNTRY,							//098

	DBMSG_REQUEST_SETSHOWCOUNTRY,						//099[����]�������� ��������
	DBMSG_RESPONSE_SETSHOWCOUNTRY,						//100

	DBMSG_REQUEST_SETSHOWPUCHIKOMI,						//101
	DBMSG_RESPONSE_SETSHOWPUCHIKOMI,					//102

	DBMSG_REQUEST_GIVEFP,								//103
	DBMSG_RESPONSE_GIVEFP,								//104

	DBMSG_REQUEST_ADDBUF,								//105
	DBMSG_RESPONSE_ADDBUF,								//106
		
	DBMSG_REQUEST_DELETEBUF,							//107
	DBMSG_RESPONSE_DELETEBUF,							//108

	DBMSG_REQUEST_SETTEACHERPOINT,						//109[����]���������� ����ȴ�.
	DBMSG_RESPONSE_SETTEACHERPOINT,						//110

	DBMSG_REQUEST_GETITEM_FROM_TEACHERPOINT,			//111[����]���������� �������� ��´�.
	DBMSG_RESPONSE_GETITEM_FROM_TEACHERPOINT,			//112

	DBMSG_REQUEST_RENOUNCEPUPIL,						//113[����]������ ���ڿ��� ���踦 ���´�.
	DBMSG_RESPONSE_RENOUNCEPUPIL,						//114

	DBMSG_REQUEST_OVERTAKETEACHERLEVEL,					//115[����]���ڰ� ���·����� ������Ҵ°�?
	DBMSG_RESPONSE_OVERTAKETEACHERLEVEL,				//116

	DBMSG_REQUEST_PVPRESULT,							//117
	DBMSG_RESPONSE_PVPRESULT,							//118

	DBMSG_REQUEST_SYSTEMREWARDLIST,						//119[����] ������ ��û
	DBMSG_RESPONSE_SYSTEMREWARDLIST,					//120

	DBMSG_REQUEST_RECIEVESYSTEMREWARD,					//121[����] ���� ��û (����DB -> �κ��丮)
	DBMSG_RESPONSE_RECIEVESYSTEMREWARD,					//122

	DBMSG_REQUEST_GIVESYSTEMREWARD,						//123[����] ���� �ֱ�
	DBMSG_RESPONSE_GIVESYSTEMREWARD,					//124

	DBMSG_REQUEST_ATTEND,								//125[����] �⼮ �ϱ�
	DBMSG_RESPONSE_ATTEND,								//126[����]

	DBMSG_REQUEST_SETATTEND,							//127[����] ���� ��¥�� �⼮���� �����Ѵ�. - 2008.03.04
	DBMSG_RESPONSE_SETATTEND,							//128[����] 		

	DBMSG_REQUEST_GET_HOMEPAGE_URL,						//129[��] Ȩ������ URL ��������
	DBMSG_RESPONSE_GET_HOMEPAGE_URL,					//130[��]

	DBMSG_REQUEST_SET_HOMEPAGE_URL,						//131[��] Ȩ������ URL �����Ѵ�.
	DBMSG_RESPONSE_SET_HOMEPAGE_URL,					//132[��]

	DBMSG_REQUEST_SETMISSIONQUESTINFO,					//133[����] �̼� ����Ʈ ������ �����Ѵ�.
	DBMSG_RESPONSE_SETMISSIONQUESTINFO,					//134[����]

	DBMSG_REQUEST_SETREMOVEUNLUCKQUESTINFO,				//135[����] �ų��̺�Ʈ - �䱥�� ����Ǵ� ����Ʈ ������ �����Ѵ�. 
	DBMSG_RESPONSE_SETREMOVEUNLUCKQUESTINFO,			//136[����]

	DBMSG_REQUEST_BBB_SET_REWARD_MONEY,					//135[����] ���Һ� - ���Һ� ������ ���� ������� �����Ѵ�.
	DBMSG_RESPONSE_BBB_SET_REWARD_MONEY,				//136[����]

	DBMSG_REQUEST_BBB_GET_REWARD_MONEY,					//135[����] ���Һ� - ���Һ� ������ ���� ������� ���´�.
	DBMSG_RESPONSE_BBB_GET_REWARD_MONEY,				//136[����]

	//DBMSG_REQEUST_GETREMOVEUNLUCKQUESTINFO,			//137[����] �ų��̺�Ʈ - �䱥�� ����Ǵ� ����Ʈ ������ �����Ѵ�.
	//DBMSG_RESPONSE_GETREMOVEUNLUCKQUESTINFO,			//138[����]

	//-------------------------------
	// Skill
	//------------------------------
	DBMSG_REQUEST_INCREASESKILL	= 200,					//[�°�]��ų�� �ø���.
	DBMSG_RESPONSE_INCREASESKILL,						//[�°�]

	DBMSG_REQUEST_DECREASESKILL,						//[�°�]��ų�� �ٿ��ش�. 	
	DBMSG_RESPONSE_DECREASESKILL,						//[�°�]

	DBMSG_REQUEST_SETSKILLEXP,							//[����]��ų�� �����Ѵ�. (����� �����ϴ� �������ġ)
	DBMSG_RESPONSE_SETSKILLEXP,							//[����] 	

	DBMSG_REQUEST_INCREASEMASTERSKILL,					//[�ؿ�]��� ��ɾ�� �⺻��ų�� �ø���.
	DBMSG_RESPONSE_INCREASEMASTERSKILL,					//[�ؿ�]

	DBMSG_REQUEST_SET_WEAPONSKILL,						//[�ؿ�]�������� ��ų�� �ø���.
	DBMSG_RESPONSE_SET_WEAPONSKILL,

	//--------------------------------
	// ������ ���� �޽���. 
	//--------------------------------
	DBMSG_REQUEST_INPUTITEMTOPERSON = 300,				//300[�°�]Ư�� Person�� Ư�� ������ ��ġ�� �������� �־��� ���� ��û�Ѵ�. 
	DBMSG_RESPONSE_INPUTITEMTOPERSON,					//301[�°�]

	DBMSG_REQUEST_OUTPUTITEMFROMPERSON,					//302[�°�]Person���κ��� �������� ����. 
	DBMSG_RESPONSE_OUTPUTITEMFROMPERSON,				//303[�°�]

	DBMSG_REQUEST_MOVEITEM,								//304[�°�]Person�� ������ â���� �������� ��ġ�� �̵���ų ���� ��û�Ѵ�. (������..) 
	DBMSG_RESPONSE_MOVEITEM,							//305[�°�]

	DBMSG_REQUEST_MOVEITEMPERSON,						//306[�°�]Person���� ������ �̵�. 
	DBMSG_RESPONSE_MOVEITEMPERSON,						//307[�°�]

	DBMSG_REQUEST_USEITEM,								//308[�°�]Person�� �������� ����� ���� ��û. 
	DBMSG_RESPONSE_USEITEM,								//309[�°�]

	DBMSG_REQUEST_USE_SPACEBOX_ITEM,					//310[����]Person�� �������� �������� ����� ���� ��û. 
	DBMSG_RESPONSE_USE_SPACEBOX_ITEM,					//311[����]

	DBMSG_REQUEST_USE_TREASURE_ITEM,					//312[����]Person�� �������� �������� ����� ���� ��û. 
	DBMSG_RESPONSE_USE_TREASURE_ITEM,					//313[����]

	DBMSG_REQUEST_SELLNPC,								//314[�°�]NPC���� �������� �Ǹ��Ѵ�. 
	DBMSG_RESPONSE_SELLNPC,								//315[�°�]

	DBMSG_REQUEST_BUYNPC,								//316[�°�]NPC���Լ� �������� �����Ѵ�.
	DBMSG_RESPONSE_BUYNPC,								//317[�°�]

	DBMSG_REQUEST_WASTEDURABILITY,						//318[�°�]�������� �Ҹ��Ѵ�. 
	DBMSG_RESPONSE_WASTEDURABILITY,						//319[�°�]

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	DBMSG_REQUEST_CRYSTALDURABILITY,					//320[��] ����ü �������� �Ҹ��Ѵ�. 
	DBMSG_RESPONSE_CRYSTALDURABILITY,					//321[��] 

	DBMSG_REQUEST_UPGRADEITEM,							//322[���] ������ ������ �����Ѵ�. ( ��, ��ġ�� �ʴ� �����۸� �� ) - Ȥ�θ� ���� �̿���� ����ؼ�.
	DBMSG_RESPONSE_UPGRADEITEM,							//323[���]

	DBMSG_REQUEST_PERFORMANCEUPGRADEITEM,				//324[���] ���ɸ� ��� ��Ű�� �������� �����. ( ��, ������ ���̸�, �� �����ۿ� �ش��ϴ� ���� ������ ����Ѵ�. )
	DBMSG_RESPONSE_PERFORMANCEUPGRADEITEM,				//325[���]

	DBMSG_REQUEST_INVREPAIR,							//326[�°�]�κ��� �������� �����ϵ��� �Ѵ�. 
	DBMSG_RESPONSE_INVREPAIR,							//327[�°�]

	DBMSG_REQUEST_DROPITEM,								//328[�°�]�������� ���� ������. 
	DBMSG_RESPONSE_DROPITEM,							//329[�°�]


	DBMSG_REQUEST_MAKEITEMINV,							//330[�°�]�κ��丮���� ��ǰ�� �����. 
	DBMSG_RESPONSE_MAKEITEMINV,							//331[�°�]

	DBMSG_REQUEST_ENCHANTITEMINV,						//332[�¾�]�κ��丮���� ��ǰ��  ��æƮ ��Ų��. 
	DBMSG_RESPONSE_ENCHANTITEMINV,						//333[�¾�]

	DBMSG_REQUEST_ENCHANT,								//334[�°�]������ ��� ������Ų��. 
	DBMSG_RESPONSE_ENCHANT,								//335[�°�]

	DBMSG_RESPONSE_SETITEM,								//336[�°�]������ ������ �����Ѵ�.

	DBMSG_REQUEST_STARTPERSONALSHOP,					//337[����]���λ����� �����Ѵ�.Ƽ�� �Ҹ�
	DBMSG_RESPONSE_STARTPERSONALSHOP,					//338

	DBMSG_REQUEST_PERSONALSHOPBUYITEM,					//339[����]���λ������� �������� �����Ѵ�.
	DBMSG_RESPONSE_PERSONALSHOPBUYITEM,					//340

	DBMSG_REQUEST_PERSONALSHOPSELLITEM,					//341[����]���λ����� �������� �Ǹ��Ѵ�.
	DBMSG_RESPONSE_PERSONALSHOPSELLITEM,				//342

	//		DBMSG_REQUEST_DELETE_LIMITDATEITEM,					//[�ؿ�] �Ⱓ�� �������� �����Ѵ�.
	//		DBMSG_RESPONSE_DELETE_LIMITDATEITEM,

	DBMSG_REQUEST_SETSUMMON,							//343[����] ��ȯ�� �Ѹ����� ������ �����Ѵ�.
	DBMSG_RESPONSE_SETSUMMON,							//344[����]

	DBMSG_REQUEST_SUMMONREVIVE,							//345[����] ��ȯ���� ��Ȱ��Ű�����ؼ� ��ȯ������ �Һ��Ų��.
	DBMSG_RESPONSE_SUMMONREVIVE,						//346[����]

	DBMSG_REQUEST_SUMMONEVOLVE,							//347[����] ��ȯ���� ��ȭ��Ű�����ؼ� ��ȯ������ �Һ��Ų��.
	DBMSG_RESPONSE_SUMMONEVOLVE,						//348[����]

	DBMSG_REQUEST_SUMMONSCROLL,							//349[����] ��ȯ���� ��ȭ��Ű�����ؼ� ������ �Һ��Ų��.
	DBMSG_RESPONSE_SUMMONSCROLL,						//350[����] 

	DBMSG_REQUEST_SUMMON_STATUSINIT,					//351[�ؿ�] ��ȯ���� ���¸� �ʱ�ȭ�Ѵ�.
	DBMSG_RESPONSE_SUMMON_STATUSINIT,					//352[�ؿ�]

	DBMSG_REQUEST_SUMMON_SETAUTOHEAL,					//353[�ؿ�] ��ȯ���� �ڵ� ȸ���� �����Ѵ�.
	DBMSG_RESPONSE_SUMMON_SETAUTOHEAL,					//354[�ؿ�]

	//		DBMSG_REQUEST_GETLIMITUSEITEM,						//[�ؿ�] �Ⱓ�� �������� �ش�.
	//		DBMSG_RESPONSE_GETLIMITUSEITEM,						//[�ؿ�]

	DBMSG_REQUEST_SUMMONTRADE,							//355[�ؿ�,����] ��ȯ���� NPC���� �Ⱦƹ�����.
	DBMSG_RESPONSE_SUMMONTRADE,							//356[�ؿ�,����]

	DBMSG_REQUEST_SETPREMIUM,							//357[�ؿ�] �����̾� ���� �����Ѵ�.
	DBMSG_RESPONSE_SETPREMIUM,							//358[�ؿ�]

	DBMSG_REQUEST_BUYRECOMMENDPRODUCT,					//359[����] ��õ ����Ʈ�� �������� �����Ѵ�.
	DBMSG_RESPONSE_BUYRECOMMENDPRODUCT,					//360

	DBMSG_REQUEST_EXCHANGEITEM,							//361[����] �κ��� �ش� ��ġ�� �������� �ٲ۴�.
	DBMSG_RESPONSE_EXCHANGEITEM,						//362[����]

	DBMSG_REQUEST_OPENTREASUREBOX,						//363[����] �������ڸ� �����Ѵ�.
	DBMSG_RESPONSE_OPENTREASUREBOX,						//364[����]

	DBMSG_REQUEST_GIVEVILLAGEITEM,						//365[����] ��� ���� ������� �������� �ش�.
	DBMSG_RESPONSE_GIVEVILLAGEITEM,						//366[����]

	DBMSG_REQUEST_ENCHANT_USEDAYPLUS,					//367[����] �������� �Ⱓ�� �����Ѵ�
	DBMSG_RESPONSE_ENCHANT_USEDAYPLUS,					//368

	DBMSG_REQUEST_CHANGEENCHANT,						//369[����] ������ �Ӽ� ���� ��û - 2008.02.20
	DBMSG_RESPONSE_CHANGEENCHANT,						//370[����] 

	DBMSG_REQUEST_KEEP_SPACE_BOX_MOVE_ITEM,				//371[�߰� : Ȳ���� 2008. 1. 30 => ���� ���ڿ� ����. S->DB
	DBMSG_RESPONSE_KEEP_SPACE_BOX_MOVE_ITEM,			//372[�߰� : Ȳ���� 2008. 1. 30 => ���� ���ڿ� ����. DB->S

	DBMSG_REQUEST_RECOVERY_SPACE_BOX_MOVE_ITEM,			//373[�߰� : Ȳ���� 2008. 1. 30 => ���� ���ڿ� ȸ��. S->DB
	DBMSG_RESPONSE_RECOVERY_SPACE_BOX_MOVE_ITEM,		//374[�߰� : Ȳ���� 2008. 1. 30 => ���� ���ڿ� ȸ��. DB->S

	DBMSG_REQUEST_SPACE_BOX_ITEM_LIST,					//375[�߰� : Ȳ���� 2008. 1. 30 => ���� ������ ����Ʈ. S->DB
	DBMSG_RESPONSE_SPACE_BOX_ITEM_LIST,					//376[�߰� : Ȳ���� 2008. 1. 30 => ���� ������ ����Ʈ. DB->S

	DBMSG_REQUEST_SUMMONPUSHITEM,						//377[����] ��ȯ�� ������� : ������� ��ȯ���� ������ �̵� ��û
	DBMSG_RESPONSE_SUMMONPUSHITEM,						//378[����] 

	DBMSG_REQUEST_SUMMONPOPITEM,						//379[����] ��ȯ�� ������� : ��ȯ������ ������� ������ �̵� ��û
	DBMSG_RESPONSE_SUMMONPOPITEM,						//390[����] 

	DBMSG_REQUEST_SUMMONUSEITEM,						//391[����] ��ȯ�� ������� : ��ȯ�� ����â�� �������� ����Ѵ�(�Ѿ�/ȭ��)
	DBMSG_RESPONSE_SUMMONUSEITEM,						//392[����] ��ȯ�� ������� : ��ȯ�� ����â�� �������� ����Ѵ�(�Ѿ�/ȭ��)

	DBMSG_REQUEST_SUMMONITEM_STATUSCHANGE,				//393[����] ��ȯ�� ������� : �������� ���¸� �����Ѵ�(��Ƽ��Ʈ ������ ����)
	DBMSG_RESPONSE_SUMMONITEM_STATUSCHANGE,				//394[����] ��ȯ�� ������� : �������� ���¸� �����Ѵ�(��Ƽ��Ʈ ������ ����)

	DBMSG_REQUEST_REPAIRITEM,							//395[����] ������ ������ ����
	DBMSG_RESPONSE_REPAIRITEM,							//396[����]

	//-------------------------------
	// Village ���� 
	//-------------------------------
	DBMSG_REQUEST_GETSTRUCTUREINFO = 400,				//[�°�]������ �ǹ� ������ ��û�Ѵ�. 
	DBMSG_RESPONSE_GETSTRUCTUREINFO,					//[�°�]

	DBMSG_REQUEST_GETVILLAGEINFO,						//[����] ������ ������ ��û�Ѵ� (��������, �θ���)
	DBMSG_RESPONSE_GETVILLAGEINFO,						//[����]

	DBMSG_REQUEST_SETPARENTVILLAGE,						//[����] �θ� ������ �����Ѵ� 
	DBMSG_RESPONSE_SETPARENTVILLAGE,					//[����]

	DBMSG_REQUEST_DECLAREWAR,							//[����]�������� �����Ѵ� 
	DBMSG_RESPONSE_DECLAREWAR,							//[����]

	DBMSG_REQUEST_CANCELDECLAREWAR,						//[����]�������� ��� 
	DBMSG_RESPONSE_CANCELDECLAREWAR,					//[����]

	DBMSG_REQUEST_SETVILLAGESYMBOL,						//[����]���� �ɺ�(��Ȳ��)�� ���� �� ���¸� ���� 
	DBMSG_RESPONSE_SETVILLAGESYMBOL,					//[����]

	DBMSG_REQUEST_SETSYMBOLSTATUS,						//[����]������� ����� �����ϰ� ���� �ɺ��� ��ġ�� �����Ѵ�
	DBMSG_RESPONSE_SETSYMBOLSTATUS,						//[����]

	DBMSG_REQUEST_SETVILLAGECASTLE,						//[����]���� ������ ���� 
	DBMSG_RESPONSE_SETVILLAGECASTLE,					//[����]

	DBMSG_REQUEST_SETCASTLESTATUS,						//[����]
	DBMSG_RESPONSE_SETCASTLESTATUS,						//[����]

	DBMSG_REQUEST_SETVILLAGEWARLOSS,					//[����]���� �й� ������ �ս� 
	DBMSG_RESPONSE_SETVILLAGEWARLOSS,					//[����]

	DBMSG_REQUEST_SETVILLAGELEVEL,						//[����]���� ������ �����Ѵ�
	DBMSG_RESPONSE_SETVILLAGELEVEL,						//[����]

	DBMSG_REQUEST_SETVILLAGEMARK,						//[����]���� ��ũ�� �����Ѵ� 
	DBMSG_RESPONSE_SETVILLAGEMARK,						//[����]

	DBMSG_REQUEST_SETVILLAGEMAP,						//[����]���� ���� �����Ѵ�
	DBMSG_RESPONSE_SETVILLAGEMAP,						//[����]

	DBMSG_REQUEST_SETINSTANCEPROFIT_VILLAGE,			//[�ؿ�]�ν��Ͻ� ���� ���ͱ� ������ ���� �����Ѵ�.
	DBMSG_RESPONSE_SETINSTANCEPROFIT_VILLAGE,

	DBMSG_REQUEST_CHANGE_INSTANCEPROFIT,				//[�ؿ�]�ν��Ͻ� ���� ���ͱ� ��ȭ��Ų��.
	DBMSG_RESPONSE_CHANGE_INSTANCEPROFIT,

	DBMSG_REQUEST_VILLAGEEVENTSUCCESS,					//[����]���� �̺�Ʈ ����(�Ұ��縮, ��ȭ��)
	DBMSG_RESPONSE_VILLAGEEVENTSUCCESS,

	DBMSG_REQUEST_VILLAGEWARKILLNUMBER,					//[����]���� �������� ������.
	DBMSG_RESPONSE_VILLAGEWARKILLNUMBER,

	DBMSG_REQUEST_VILLAGERESIDENTSVISITORSINFO,			//[����]���� �ֹμ��� ���� �湮�� ���� �־��ش�.
	DBMSG_RESPONSE_VILLAGERESIDENTSVISITORSINFO,

	DBMSG_REQUEST_VILLAGEJOINPLAYTIME,					//[����]���� ������ �÷��� �ð��� ������
	DBMSG_RESPONSE_VILLAGEJOINPLAYTIME,

	DBMSG_REQUEST_VILLAGEJOINLEVELUP,					//[����]���� ������ ������ Ƚ��
	DBMSG_RESPONSE_VILLAGEJOINLEVELUP,

	DBMSG_REQUEST_VILLAGEJOINWARKILLNUMBER,				//[����]���� ������ ������
	DBMSG_RESPONSE_VILLAGEJOINWARKILLNUMBER,

	DBMSG_REQUEST_VILLAGEJOINMAKERAREITEM,				//[����]���� ������ ��ǰ ���� Ƚ��
	DBMSG_RESPONSE_VILLAGEJOINMAKERAREITEM,

	DBMSG_REQUEST_VILLAGEJOINMAKEITEM,					//[����]���� ������ ������ ���� Ƚ��
	DBMSG_RESPONSE_VILLAGEJOINMAKEITEM,

	DBMSG_REQUEST_DONATEVILLAGEMONEY,					//[����]������ �� ����ϱ�
	DBMSG_RESPONSE_DONATEVILLAGEMONEY,

	DBMSG_REQUEST_DONATEMEMBERLIST,						//[����]����� ��� �ҷ�����
	DBMSG_RESPONSE_DONATEMEMBERLIST,

	DBMSG_REQUEST_EVENT_INSERTMATERIAL,					//[����]����� �̺�Ʈ ��� �ֱ�
	DBMSG_RESPONSE_EVENT_INSERTMATERIAL,

	DBMSG_REQUEST_EVENT_MATERIALLIST,					//[����]����� �̺�Ʈ ��� ���� ����
	DBMSG_RESPONSE_EVENT_MATERIALLIST,

	DBMSG_REQUEST_EVENT_MATERIALCOMPLETE,				//[����]����� �̺�Ʈ �ϼ� ó��
	DBMSG_RESPONSE_EVENT_MATERIALCOMPLETE,

	DBMSG_REQUEST_ADD_VILLAGE_SCORE,				//[����]����� �̺�Ʈ �ϼ� ó��
	DBMSG_RESPONSE_ADD_VILLAGE_SCORE,
	//----------------------------------------
	// WorldMoney ���� ( ��ť )
	//----------------------------------------
	DBMSG_REQUEST_DISTRIBUTION_WORLDMONEY  = 500 ,		//[�ؿ�] ��ť�� �ý��ۿ��Լ� �����Ѵ�.
	DBMSG_RESPONSE_DISTRIBUTION_WORLDMONEY,

	DBMSG_REQUEST_WORLDMONEY_TRADELIST,					//[�ؿ�] ������ ����Ʈ(��ť �Ǹ�)�� ��û�Ѵ�.
	DBMSG_RESPONSE_WORLDMONEY_TRADELIST,

	DBMSG_REQUEST_WORLDMONEY_SELLORDER,					//[�ؿ�] ��ť�� �ȷ��� ��û�Ѵ�.
	DBMSG_RESPONSE_WORLDMONEY_SELLORDER,

	DBMSG_REQUEST_WORLDMONEY_BUYORDER,					//[�ؿ�] ��ť�� ����� ��û�Ѵ�.
	DBMSG_RESPONSE_WORLDMONEY_BUYORDER,

	DBMSG_REQUEST_WORLDMONEY_CANCELORDER,				//[�ؿ�] ��ť �ǸŸ� ����Ѵ�.
	DBMSG_RESPONSE_WORLDMONEY_CANCELORDER,

	DBMSG_REQUEST_TRADESERVER_SETORDER,					//[�ؿ�] ���� ������ �ֹ��� �ø���
	DBMSG_RESPONSE_TRADESERVER_SETORDER,

	DBMSG_REQUEST_TRADESERVER_CANCELORDER,				//[�ؿ�] ���� ������ �ø� �ֹ��� ����Ѵ�.
	DBMSG_RESPONSE_TRADESERVER_CANCELORDER,

	DBMSG_REQUEST_TRADESERVER_BUYITEM,					//[�ؿ�] ���� �������� ������ ���.
	DBMSG_RESPONSE_TRADESERVER_BUYITEM,

	DBMSG_REQUEST_TRADESERVER_SET_SELLINFO,				//[�ؿ�] ���� �������� �ȸ� ���ǿ� ���� ������ �����Ѵ�.
	DBMSG_RESPONSE_TRADESERVER_SET_SELLINFO,

	DBMSG_REQUEST_TRADESERVER_GET_WITHDRAW_ACU,			//[����] ������������ ����� ��ť �ޱ�
	DBMSG_RESPONSE_TRADESERVER_GET_WITHDRAW_ACU,

	DBMSG_REQUEST_WORLDMONEY_SETAVERAGEPRICE,			//[�ؿ�] ��ť�� �ü��� �����Ѵ�.
	DBMSG_RESPONSE_WORLDMONEY_SETAVERAGEPRICE,

	DBMSG_REQUEST_WORLDMONEY_REDUCEPRICE,				//[�ؿ�] ��ť�� ������ ������.
	DBMSG_RESPONSE_WORLDMONEY_REDUCEPRICE,

	DBMSG_REQUEST_WORLDMONEY_SET_CHAR,					//[�ؿ�] ��ť�� �־��ش�.
	DBMSG_RESPONSE_WORLDMONEY_SET_CHAR,

	DBMSG_REQUEST_WORLDPASSPORT_SET,					//[����] ���������� �����Ѵ�
	DBMSG_RESPONSE_WORLDPASSPORT_SET,	

	DBMSG_REQUEST_WORLDPASSPORT_EXTEND,					//[����] ���������� �Ⱓ�� �����Ѵ�
	DBMSG_RESPONSE_WORLDPASSPORT_EXTEND,	

	//----------------------------------
	// ��û ���� 
	//----------------------------------
	DBMSG_REQUEST_INVESTLIST = 1100,					//[�°�]���� ������ ����� ���´�.
	DBMSG_RESPONSE_INVESTLIST,							//[�°�]

	DBMSG_REQUEST_CANDIDATE,							//[�°�]���ĺ� �� ���� ��û�Ѵ�. 
	DBMSG_RESPONSE_CANDIDATE,							//[�°�]	

	DBMSG_REQUEST_CANCELCANDIDATE,						//[�°�]���ĺ� �� ���� ����� ���� ��û�Ѵ�. 
	DBMSG_RESPONSE_CANCELCANDIDATE,						//[�°�]

	DBMSG_REQUEST_MANYCANDIDATEINFO,					//[�°�]�������� �ĺ��� ������ ���� ���� ��û�Ѵ�. 
	DBMSG_RESPONSE_MANYCANDIDATEINFO,					//[�°�]

	DBMSG_REQUEST_MANYRANK,								//[�°�]�������� �ź� ������ ���´�
	DBMSG_RESPONSE_MANYRANK,							//[�°�]

	DBMSG_REQUEST_RANKINFO,								//[�°�]
	DBMSG_RESPONSE_RANKINFO,							//[�°�]Ư��Person�� �ź� ������ ���´�. 

	DBMSG_REQUEST_BERANK,								//[�°�]Person�� Ư�� Rank�� ����� �� ���� ��û�Ѵ�. 
	DBMSG_RESPONSE_BERANK,								//[�°�]

	DBMSG_REQUEST_DELCANDIDATE,							//[�°�]��ϵ� �ĺ����� ��� �����Ѵ�. 
	DBMSG_RESPONSE_DELCANDIDATE,						//[�°�]

	DBMSG_REQUEST_RESIGN,								//[�°�]�ź����� �����Ѵ�.
	DBMSG_RESPONSE_RESIGN,								//[�°�]

	DBMSG_REQUEST_HIRENPC,								//[����] ������ �ֹ��� ����Ѵ� 
	DBMSG_RESPONSE_HIRENPC,								//[����]

	//
	DBMSG_REQUEST_APPLYRESIDENT,						//[����] �ֹε���� ��û�Ѵ� 
	DBMSG_RESPONSE_APPLYRESIDENT,						//[����]

	DBMSG_REQUEST_GETRESIDENTAPPLYERLIST,				//[����] �ֹε�Ͻ�û�� ����Ʈ�� ��û�Ѵ�
	DBMSG_RESPONSE_GETRESIDENTAPPLYERLIST,				//[����]

	DBMSG_REQUEST_GETRESIDENTLIST,						//[����] �ֹ� ����Ʈ�� ��û�Ѵ�
	DBMSG_RESPONSE_GETRESIDENTLIST,						//[����]	

	DBMSG_REQUEST_BERESIDENT,							//[����] �ֹ����� ��� �ϱ�
	DBMSG_RESPONSE_BERESIDENT,							//[����]

	DBMSG_REQUEST_CANCELRESIDENT,						//[����] �ֹε�Ͻ�û ��� or �ֹε�� ���� 
	DBMSG_RESPONSE_CANCELRESIDENT,						//[����]

	DBMSG_REQUEST_GETRESIDENTINFO,						//[����] �ֹ� �� ������ ��û�Ѵ�
	DBMSG_RESPONSE_GETRESIDENTINFO,						//[����]

	DBMSG_REQUEST_SETRESIDENTSCORE,						//[����] �ֹ� ������ �����Ѵ�
	DBMSG_RESPONSE_SETRESIDENTSCORE,					//[����]

	DBMSG_REQUEST_MANYRESIDENTOUT,						//[����] �������� ������ �ֹε��� ��� ��Ų�� 
	DBMSG_RESPONSE_MANYRESIDENTOUT,						//[����]

	DBMSG_REQUEST_CITYHALL_SETINOUTMONEY,				//[�°�]��� �ڱ� ����ݾ��� �����Ѵ�
	DBMSG_RESPONSE_CITYHALL_SETINOUTMONEY,				//[�°�]

	DBMSG_REQUEST_RESIDENTSHARE,						//[����] ���� �ֹο��� ���ͱ��� ����Ѵ�
	DBMSG_RESPONSE_RESIDENTSHARE,						//[����]

	DBMSG_REQUEST_BUILDSTRUCTURE,						//[����] ���� �ǹ��� �Ǽ��Ѵ�
	DBMSG_RESPONSE_BUILDSTRUCTURE,						//[����]

	DBMSG_REQUEST_DESTROYSTRUCTURE,						//[����] ���� �ǹ��� ��ü�Ѵ�
	DBMSG_RESPONSE_DESTROYSTRUCTURE,					//[����]

	DBMSG_REQUEST_CHANGECITYHALLPROFITMONEY,			//[����] ���ͱ� �ڱ� ����
	DBMSG_RESPONSE_CHANGECITYHALLPROFITMONEY,			//[����]

	DBMSG_REQUEST_PROFITTOCAPITALFUND,					//[����] ���ͱ� -> �ں��� 
	DBMSG_RESPONSE_PROFITTOCAPITALFUND,					//[����]

	DBMSG_REQUEST_GENERALMEETING_INFO,					//[����] �� ������ ������ȸ ������ ���´�
	DBMSG_RESPONSE_GENERALMEETING_INFO,					//[����]

	DBMSG_REQUEST_GENERALMEETING_SUGGEST_CHIEF,			//[����] ����� �Ӹ������ ������ȸ���� �����ϴ� 
	DBMSG_RESPONSE_GENERALMEETING_SUGGEST_CHIEF,		//[����]

	DBMSG_REQUEST_GENERALMEETING_VOTE,					//[����] ��ǥ�ϴ� 
	DBMSG_RESPONSE_GENERALMEETING_VOTE,					//[����]

	DBMSG_REQUEST_GENERALMEETING_ACCEPTCANDIDATE,		//[����] ����� �ĺ��� �����ϴ� 
	DBMSG_RESPONSE_GENERALMEETING_ACCEPTCANDIDATE,		//[����]

	DBMSG_REQUEST_GENERALMEETING_CLOSE_CHIEF,			//[����] ����� �Ӹ���� ������ȸ�� �����ϴ� 
	DBMSG_RESPONSE_GENERALMEETING_CLOSE_CHIEF,			//[����]

	DBMSG_REQUEST_SETVILLAGEWAR_RESULT,						//[����] ������ �������� ����� �����Ѵ�.
	DBMSG_RESPONSE_SETVILLAGEWAR_RESULT,					//[����]

	DBMSG_REQUEST_GENERALMEETING_SUGGEST_ON_OFF,			// [�߰� : Ȳ���� 2008. 2. 20 => ������ȸ ���� ���� ]
	DBMSG_RESPONSE_GENERALMEETING_SUGGEST_ON_OFF,

	DBMSG_REQUEST_GENERALMEETING_SUGGEST_ON_OFF_LIST,			// [�߰� : Ȳ���� 2008. 2. 20 => ������ȸ ���� ���� ����Ʈ ���.]
	DBMSG_RESPONSE_GENERALMEETING_SUGGEST_ON_OFF_LIST,

	//----------------------------------
	// ��� �Ļ� ����
	//----------------------------------
	//#if defined(_CITYHALL_BANKRUPTCY)
	DBMSG_REQUEST_CITYHALL_STATE_CHANGED,				//[�뷡] ��� ����(�Ļ��, �ʱ�ȭ��, ������, �����)�� ����Ǿ���.
	DBMSG_RESPONSE_CITYHALL_STATE_CHANGED,				//[�뷡]

	DBMSG_REQUEST_NOTIFY_CITYHALL_BANKRUPTCY,			//[�뷡] ��� ���°� �Ļ�Ǿ����� LETTER�� �˸���.
	DBMSG_RESPONSE_NOTIFY_CITYHALL_BANKRUPTCY,			//[�뷡]

	// �Ļ� �� ���� ���� ���� �ʱ�ȭ�� ���� ���˽� ���۾����� �Ѵ�.
	//DBMSG_REQUEST_VILLAGE_INITIALIZATION,				//[�뷡] ����� �Ļ� ������ ���� ���¸� �ʱ�ȭ �Ѵ�.
	//DBMSG_RESPONSE_VILLAGE_INITIALIZATION,				//[�뷡]
	//#endif

	DBMSG_REQUEST_GENERALMEETING_SETVOTERSTATE,			//[����] ���� ���� ���θ� �����Ѵ�
	DBMSG_RESPONSE_GENERALMEETING_SETVOTERSTATE,		//[����]

	//--------------------------------
	// ���� ���� �޽��� 
	//--------------------------------
	DBMSG_REQUEST_CREATEBANKACCOUNT= 1200,				//[�°�]���� ���� ���� ��û. 
	DBMSG_RESPONSE_CREATEBANKACCOUNT,					//[�°�]	 

	DBMSG_REQUEST_CLOSEBANKACCOUNT,						//[�°�]���� ���� ���� ��û.
	DBMSG_RESPONSE_CLOSEBANKACCOUNT,					//[�°�]

	DBMSG_REQUEST_INPUTMONEYTOBANK,						//[�°�]���࿡ ���� �Ա��� ���� ��û�Ѵ�. 
	DBMSG_RESPONSE_INPUTMONEYTOBANK,					//[�°�]

	DBMSG_REQUEST_OUTPUTMONEYFROMBANK,					//[�°�]�������κ��� ���� ����� ���� ��û�Ѵ�. 
	DBMSG_RESPONSE_OUTPUTMONEYFROMBANK,					//[�°�]

	DBMSG_REQUEST_SETBANKFEE,							//[�°�]���� �����Ḧ ���´�. 
	DBMSG_RESPONSE_SETBANKFEE,							//[�°�]

	//-------------------------------
	// ���� ���� �޽��� 
	//-------------------------------
	DBMSG_REQUEST_GETMANYSTOCKORDER = 1300,				//1300 [�°�]�������� �ֽ� �ֹ��� ��û�Ѵ�. 
	DBMSG_RESPONSE_GETMANYSTOCKORDER,					//1301 [�°�]

	DBMSG_REQUEST_TRADESTOCK,							//1302 [�°�]�ֽ��� �ŷ��� ���� ��û�Ѵ�. 
	DBMSG_RESPONSE_TRADESTOCK,							//1303 [�°�]

	DBMSG_REQUEST_ORDERSTOCK,							//1304 [�°�]�ֹ��� DB�� ���� ���� ��û�Ѵ�. 
	DBMSG_RESPONSE_ORDERSTOCK,							//1305 [�°�]

	DBMSG_REQUEST_CANCELSTOCKORDER,						//1306 [�°�]�ڽ��� �ֽ� �ֹ��� ����� ���� ��û�Ѵ�.
	DBMSG_RESPONSE_CANCELSTOCKORDER,					//1307 [�°�]

	DBMSG_REQUEST_MANYSTOCKPRICE,						//1308 [�°�]�������� �ֽİ��� ������ ��û�Ѵ�. 
	DBMSG_RESPONSE_MANYSTOCKPRICE,						//1309 [�°�]

	DBMSG_REQUEST_SETSTOCKFEE,							//1310 [�°�]���� �����Ḧ ���´�. 
	DBMSG_RESPONSE_SETSTOCKFEE,							//1311 [�°�]

	DBMSG_REQUEST_GETSTOCKBIDVILLAGELIST,				//1312 [����]��� ���� ���� ������ ��û�Ѵ�
	DBMSG_RESPONSE_GETSTOCKBIDVILLAGELIST,				//1313 [����]

	DBMSG_REQUEST_SETSTOCKBIDVILLAGE,					//1314 [����]��� ������ �����Ѵ�
	DBMSG_RESPONSE_SETSTOCKBIDVILLAGE,					//1315 [����]

	DBMSG_REQUEST_GETSTOCKBIDDERLIST,					//1316 [����]������ ������ ��û�Ѵ�
	DBMSG_RESPONSE_GETSTOCKBIDDERLIST,					//1317 [����]

	DBMSG_REQUEST_BIDSTOCK,								//1318 [����]�ֽ� ��� ���� ��û�Ѵ� 
	DBMSG_RESPONSE_BIDSTOCK,							//1319 [����]

	DBMSG_REQUEST_CANCELBIDSTOCK,						//1320 [����]�ֽ� ������ ����Ѵ� 
	DBMSG_RESPONSE_CANCELBIDSTOCK,						//1321 [����]

	DBMSG_REQUEST_COMPLETESTOCKBIDVILLAGE,				//1322 [����]�ֽ� ��� ������ �Ϸ��Ѵ� 
	DBMSG_RESPONSE_COMPLETESTOCKBIDVILLAGE,				//1323 [����]

	DBMSG_REQUEST_SETBEGINNINGPRICE,					//1324 [����]���ڽ� ���� �ֽ��� ���� ���۰��� �����Ѵ� 
	DBMSG_RESPONSE_SETBEGINNINGPRICE,					//1325 [����]

	DBMSG_REQUEST_STOCKDISTRIBUTIONORDER,				//1326 [���] �ֽ� ���� ����
	DBMSG_RESPONSE_STOCKDISTRIBUTIONORDER,				//1327 [���]

	DBMSG_REQUEST_MAXSTOCKDISTRIBUTIONNUM,				//1328 [���] �ֽ� ���� �ֽļ� ����
	DBMSG_RESPONSE_MAXSTOCKDISTRIBUTIONNUM,				//1329 [���]

	DBMSG_REQUEST_RETURNSTOCKBIDVILLAGE,				//1330 [�뷡] ������ �Ļ��Ͽ� �ֽ� ��� ������ ��� �����ش�.
	DBMSG_RESPONSE_RETURNSTOCKBIDVILLAGE,				//1331 [�뷡]

	DBMSG_REQUEST_REQUSETINCREASESTOCK,					//1332 [����] ������� �ֽ����ڸ� ��û�Ѵ�
	DBMSG_RESPONSE_REQUSETINCREASESTOCK,				//1333 [����]

	DBMSG_REQUEST_BUYBIDSTOCK,							//1334 [����] ���� �ֽ��� ���
	DBMSG_RESPONSE_BUYBIDSTOCK,							//1335 [����]

	DBMSG_REQUEST_MYSTOCKINFO,							//1336 [����] ���� �ֽ� ������ �� �ֽ������� �ٽ� �ҷ��´�.
	DBMSG_RESPONSE_MYSTOCKINFO,							//1337 [����]

	DBMSG_REQUEST_GETSTOCKOFFERINGINFO,					//1338 [����] �ֽ� ���� ���� ���� ��û
	DBMSG_RESPONSE_GETSTOCKOFFERINGINFO,				//1339 [����]

	DBMSG_REQUEST_SETSTOCKOFFERING,						//1340 [����] �ֽ� ���� ���� ���� (����û�����)
	DBMSG_RESPONSE_SETSTOCKOFFERING,					//1341 [����]

	DBMSG_REQUEST_ENDSTOCKOFFERING,						//1342 [����] �ֽ� ���� û�� ����
	DBMSG_RESPONSE_ENDSTOCKOFFERING,					//1343 [����]

	DBMSG_REQUEST_STOCKOFFERINGORDER,					//1344 [����] �ֽ� ���� û�� �ֹ�
	DBMSG_RESPONSE_STOCKOFFERINGORDER,					//1345 [����]

	DBMSG_REQUEST_GETSTOCKOFFERINGORDERLIST,			//1346 [����] �ֽ� û���� ����Ʈ 
	DBMSG_RESPONSE_GETSTOCKOFFERINGORDERLIST,			//1347 [����]

	DBMSG_REQUEST_EXECUTESTOCKOFFERINGORDER,			//1348 [����] �ֽ� û�� �ֹ� ó��
	DBMSG_RESPONSE_EXECUTESTOCKOFFERINGORDER,			//1349 [����]

	DBMSG_REQUEST_RESETSTOCKOFFERINGORDERLIST,			//1350 [����] �ֽ� û���� ����Ʈ ��� ����
	DBMSG_RESPONSE_RESETSTOCKOFFERINGORDERLIST,			//1351 [����]

	DBMSG_REQUEST_EXCHANGEFROMSTOCK,					//1352 [����] �ֽ� 1�ִ� ���� �� 1�������� �ٲ��ش�.
	DBMSG_RESPONSE_EXCHANGEFROMSTOCK,					//1353 [����]

	DBMSG_REQUEST_GIVESTOCK,							//1354 [����] �ֽ��� �ش�
	DBMSG_RESPONSE_GIVESTOCK,							//1355 [����]

	//-------------------------------
	// ���� ���� ���� 
	//-------------------------------
	DBMSG_REQUEST_GETMANYMARKETORDER = 1400,			//[�°�]�������� ���� �ֹ��� ��û�Ѵ�. 
	DBMSG_RESPONSE_GETMANYMARKETORDER,					//[�°�]

	DBMSG_REQUEST_ORDERMARKET,							//[�°�]���ֿ��� �ֹ��� �ִ´� 
	DBMSG_RESPONSE_ORDERMARKET,							//[�°�]

	DBMSG_REQUEST_TRADEMARKET,							//[�°�]���ֿ��� ������ �� ���� ��û�Ѵ�. 
	DBMSG_RESPONSE_TRADEMARKET,							//[�°�]

	DBMSG_REQUEST_MARKETACCOUNT,						//[�°�]���� ���� ������ ��û�Ѵ�. 
	DBMSG_RESPONSE_MARKETACCOUNT,						//[�°�]

	DBMSG_REQUEST_GETITEMFROMMARKET,					//[�°�]���� â��κ��� �������� ���������� ��û�Ѵ�. 
	DBMSG_RESPONSE_GETITEMFROMMARKET,					//[�°�]

	DBMSG_REQUEST_MANYITEMPRICE,						//[�°�]�������� ������ ���� ������ ��û�Ѵ�.
	DBMSG_RESPONSE_MANYITEMPRICE,						//[�°�]

	DBMSG_REQUEST_SETITEMPRICE,							//[�°�]������ ������ �����Ѵ�. 
	DBMSG_RESPONSE_SETITEMPRICE,						//[�°�]

	DBMSG_REQUEST_REDUCEORDERPRICE,						//[�°�]�ֹ� ������ �����.
	DBMSG_RESPONSE_REDUCEORDERPRICE,					//[�°�]

	DBMSG_REQUEST_SETMARKETFEE,							//[�°�]���� �����Ḧ ���´�. 
	DBMSG_RESPONSE_SETMARKETFEE,						//[�°�]




	//-------------------------------
	// ���� ���� 
	//-------------------------------
	DBMSG_REQUEST_CHANGEHOUSECONTRACT = 1500,			//[�°�]������ ��� ������ �����Ѵ�. 
	DBMSG_RESPONSE_CHANGEHOUSECONTRACT,					//[�°�]

	DBMSG_REQUEST_MANYHOUSEUNIT,						//[�°�]���� ������ ������ ���´�. 
	DBMSG_RESPONSE_MANYHOUSEUNIT,						//[�°�]

	DBMSG_REQUEST_GETHOUSEAPPLYERLIST,					//[�°�]���� ����� ����� ���´�. 
	DBMSG_RESPONSE_GETHOUSEAPPLYERLIST,					//[�°�]

	DBMSG_REQUEST_HOUSERENTAPPLY,						//[�°�]���� ������ ��û�Ѵ�.
	DBMSG_RESPONSE_HOUSERENTAPPLY,						//[�°�]

	DBMSG_REQUEST_HOUSERENTAPPLYCANCEL,					//[�°�]���� ���� ��û�� ����Ѵ�. 
	DBMSG_RESPONSE_HOUSERENTAPPLYCANCEL,				//[�°�]

	DBMSG_REQUEST_HOUSERENT,							//[�°�]������ �Ӵ��Ѵ�. 
	DBMSG_RESPONSE_HOUSERENT,							//[�°�]

	DBMSG_REQUEST_MOVEITEMINVTOSTG,						//[�°�]�������� �κ��丮���� â��� �ű��. 
	DBMSG_RESPONSE_MOVEITEMINVTOSTG,					//[�°�]

	DBMSG_REQUEST_MOVEITEMSTGTOINV,						//[�°�]�������� â���� �κ��丮�� �ű��. 
	DBMSG_RESPONSE_MOVEITEMSTGTOINV,					//[�°�]

	DBMSG_REQUEST_MAKEITEM,								//[�°�]�������� ������ ���� ��û�Ѵ�. 
	DBMSG_RESPONSE_MAKEITEM,							//[�°�]

	DBMSG_REQUEST_GETHOUSESTGPOS,						//[�°�]Ư�� ��ġ�� ���ó� â���� ������ ��û�Ѵ�. 
	DBMSG_RESPONSE_GETHOUSESTGPOS,						//[�°�]

	DBMSG_REQUEST_DELHOUSEAPPLYER,						//[�°�]���� ��û���� ����� �����Ѵ�. 
	DBMSG_RESPONSE_DELHOUSEAPPLYER,						//[�°�]

	DBMSG_REQUEST_PAYRENTFEE,							//[�°�]�Ӵ�Ḧ �����Ѵ�. 
	DBMSG_RESPONSE_PAYRENTFEE,							//[�°�]

	DBMSG_REQUEST_RECALLHOUSE,							//[�°�]������ ȸ���Ѵ�. 
	DBMSG_RESPONSE_RECALLHOUSE,							//[�°�]������ ȸ���Ѵ�. 

	DBMSG_REQUEST_HOUSEUNITSTABLECREATE,				//[���] ������ ������ ����
	DBMSG_RESPONSE_HOUSEUNITSTABLECREATE,				//[���]	

	DBMSG_REQUEST_HOUSEUNITHORSEIN,						//[���] ������ ���� �ִ´�.
	DBMSG_RESPONSE_HOUSEUNITHORSEIN,					//[���]

	DBMSG_REQUEST_HOUSEUNITHORSEOUT,					//[���] �������� ���� ������.
	DBMSG_RESPONSE_HOUSEUNITHORSEOUT,					//[���]

	DBMSG_REQUEST_HOUSEUNITHORSEINFOSET,				//[���] ������ �� ������ ������Ʈ
	DBMSG_RESPONSE_HOUSEUNITHORSEINFOSET,				//[���]

	DBMSG_REQUEST_HOUSEUNITHORSEEATFOOD,				//[���] ���� ���� �Ա⸦ ��û
	DBMSG_RESPONSE_HOUSEUNITHORSEEATFOOD,				//[���]

	DBMSG_REQUEST_HOUSEUNITSHIPBUILDINGCREATE,			//[���] ������ ������ ����
	DBMSG_RESPONSE_HOUSEUNITSHIPBUILDINGCREATE,			//[���]

	DBMSG_REQUEST_HOUSEUNITSHIPBUILDINGUPGRADE,			//[���] ������ �ǹ��� ���׷��̵� ��Ų��.
	DBMSG_RESPONSE_HOUSEUNITSHIPBUILDINGUPGRADE,		//[���]

	DBMSG_REQUEST_HOUSEUNITSHIPSTEPMAKE,				//[���] ������ �� �ܰ躰 ���� ����
	DBMSG_RESPONSE_HOUSEUNITSHIPSTEPMAKE,				//[���]

	DBMSG_REQUEST_HOUSEUNITSHIPMAKE,					//[���] �� �����
	DBMSG_RESPONSE_HOUSEUNITSHIPMAKE,					//[���]

	DBMSG_REQUEST_HOUSEUNITSHIPMAKECANCEL,				//[���] �� ���� ���( �� ���� )
	DBMSG_RESPONSE_HOUSEUNITSHIPMAKECANCEL,				//[���]

	DBMSG_REQUEST_HOUSEUNITSHIPLAUNCHING,				//[���] �� ������ ����
	DBMSG_RESPONSE_HOUSEUNITSHIPLAUNCHING,				//[���]

	DBMSG_REQUEST_HOUSEUNITUSEDGOODSBUILDINGCREATE,		//[���] ������ ���� ����
	DBMSG_RESPONSE_HOUSEUNITUSEDGOODSBUILDINGCREATE,	//[���]

	DBMSG_REQUEST_HOUSEUNITMAKEITEMFROMUSEDGOODS,		//[���] ���� ���� �������� ����� ����.
	DBMSG_RESPONSE_HOUSEUNITMAKEITEMFROMUSEDGOODS,		//[���]

	DBMSG_REQUEST_HOUSEUNITSUMMONBUILDINGCREATE,		//[���] ��ȯ�� ���� �Ǽ�
	DBMSG_RESPONSE_HOUSEUNITSUMMONBUILDINGCREATE,		//[���] 

	DBMSG_REQUEST_HOUSEUNITSUMMONBUILDINGUPGRADE,		//[���] ��ȯ�� ���� Upgrade
	DBMSG_RESPONSE_HOUSEUNITSUMMONBUILDINGUPGRADE,		//[���]

	DBMSG_REQUEST_HOUSEUNITSUMMONIN,					//[���] ��ȯ�� �ֱ�
	DBMSG_RESPONSE_HOUSEUNITSUMMONIN,					//[���]

	DBMSG_REQUEST_HOUSEUNITSUMMONOUT,					//[���] ��ȯ�� ����
	DBMSG_RESPONSE_HOUSEUNITSUMMONOUT,					//[���]

	DBMSG_REQUEST_HOUSEUNITSUMMONEAT,					//[���] ��ȯ���� �Ա�
	DBMSG_RESPONSE_HOUSEUNITSUMMONEAT,					//[���]

	DBMSG_REQUEST_HOUSEUNITNAMECHANGE,					//[����] â�� �̸� ����
	DBMSG_RESPONSE_HOUSEUNITNAMECHANGE,					//[����]  


	//---------------------------
	// ��� ��� ���� ��� ��� ( Agriculture - ���� ��Ī )
	// �����
	//---------------------------
	DBMSG_REQUEST_AGRICULTUREGETPRODUCTS,				//[���] ��ǰ ȹ��
	DBMSG_RESPONSE_AGRICULTUREGETPRODUCTS,				//[���]

	DBMSG_REQUEST_AGRICULTUREPAYMONEYFORRENTLAND,			//[���] �Ӵ����� ���� ����� �ǹ��� ���� �����ϰ� ����Ȱ���� �ϵ��� �ϱ� ���Ѱ�
	DBMSG_RESPONSE_AGRICULTUREPAYMONEYFORRENTLAND,			//[���]

	DBMSG_REQUEST_GETAGRICULTURELEASEINFO,				//[����] �ӽ÷� �������� �ü��� ���� ������ ���´�.
	DBMSG_RESPONSE_GETAGRICULTURELEASEINFO,				//[����]
	DBMSG_REQUEST_EXPIREDAGRICULTERLEASE,				//[����] �ӽ� ��� �Ⱓ ���� �˸�
	DBMSG_RESPONSE_EXPIREDAGRICULTERLEASE,



	//------------------------
	// ����
	//------------------------
	DBMSG_REQUEST_FISHINGDECREASETOOLDURABILITY,		//[���] ���ø� �ϸ� ������ �Ҹ��ؾ� �ϹǷ�...
	DBMSG_RESPONSE_FISHINGDECREASETOOLDURABILITY,		//[���]

	DBMSG_REQUEST_FISHINGGETMARINEPRODUCTS,				//[���] �ػ깰 ȹ��
	DBMSG_RESPONSE_FISHINGGETMARINEPRODUCTS,			//[���]

	//------------------------
	// ���
	//------------------------
	DBMSG_REQUEST_FARMINGPAYMONEYFORRENTLAND,			//[���] �Ӵ����� ���� ����� ���忡 ���� �����ϰ� ����� �ϵ��� �ϱ� ���Ѱ�
	DBMSG_RESPONSE_FARMINGPAYMONEYFORRENTLAND,			//[���]

	//------------------------
	// ä��
	//------------------------
	DBMSG_REQUEST_MININGPAYMONEYFORRENTLAND,			//[���] �Ӵ����� ���� ����� ä���ǹ��� ���� �����ϰ� ����� �ϵ��� �ϱ� ���Ѱ�
	DBMSG_RESPONSE_MININGPAYMONEYFORRENTLAND,			//[���]



	//------------------------
	// ������
	//------------------------

	DBMSG_REQUEST_HUNTMONSTERFIELDLISTADD = 1700,			//[���]
	DBMSG_RESPONSE_HUNTMONSTERFIELDLISTADD,					//[���]

	DBMSG_REQUEST_HUNTMONSTERFIELDLISTDEL,					//[���]
	DBMSG_RESPONSE_HUNTMONSTERFIELDLISTDEL,					//[���]

	DBMSG_REQUEST_HUNTSTORAGEMONSTERIN,						//[���] ������ â�� ������ �ִ´�.
	DBMSG_RESPONSE_HUNTSTORAGEMONSTERIN,					//[���]

	DBMSG_REQUEST_HUNTSTORAGEMONSTEROUT,					//[���] ������ â���� ������ ������.
	DBMSG_RESPONSE_HUNTSTORAGEMONSTEROUT,					//[���]

	DBMSG_REQUEST_HUNTSTORAGEDECREASEDOLLITEMNUM,			//[���]	
	DBMSG_RESPONSE_HUNTSTORAGEDECREASEDOLLITEMNUM,			//[���]

	DBMSG_REQUEST_HUNTLEFTMONSTERSTGIN,						//[���]
	DBMSG_RESPONSE_HUNTLEFTMONSTERSTGIN,					//[���]




	//------------------------
	// ����
	//------------------------
	DBMSG_REQUEST_POSTOFFICE_SENDITEM = 1800,				//[����]��ǰ ������ ��û�Ѵ� 
	DBMSG_RESPONSE_POSTOFFICE_SENDITEM,						//[����]	

	DBMSG_REQUEST_POSTOFFICE_SENDMONEY,						//[����]�۱��� ��û�Ѵ� 
	DBMSG_RESPONSE_POSTOFFICE_SENDMONEY,					//[����]

	DBMSG_REQUEST_POSTOFFICE_SENDMSG,						//[����]�޽��� ������ ��û�Ѵ�
	DBMSG_RESPONSE_POSTOFFICE_SENDMSG,						//[����]

	DBMSG_REQUEST_POSTOFFICE_RECVITEMLIST,					//[����]���� ������ ����� ��û�Ѵ�
	DBMSG_RESPONSE_POSTOFFICE_RECVITEMLIST,					//[����]

	DBMSG_REQUEST_POSTOFFICE_RECVMONEYLIST,					//[����]���� ���� ����� ��û�Ѵ� 
	DBMSG_RESPONSE_POSTOFFICE_RECVMONEYLIST,				//[����]

	DBMSG_REQUEST_POSTOFFICE_RECVMSGLIST,					//[����]���� �޽��� ����� ��û�Ѵ�
	DBMSG_RESPONSE_POSTOFFICE_RECVMSGLIST,					//[����]

	DBMSG_REQUEST_POSTOFFICE_GETITEM,						//[����]���� �������� �κ��丮�� �ִ´�
	DBMSG_RESPONSE_POSTOFFICE_GETITEM,						//[����]

	DBMSG_REQUEST_POSTOFFICE_GETMONEY,						//[����]���� ���� ���������� �ִ´�
	DBMSG_RESPONSE_POSTOFFICE_GETMONEY,						//[����]

	DBMSG_REQUEST_POSTOFFICE_DELMSG,						//[����]���� �޽����� �����Ѵ� 
	DBMSG_RESPONSE_POSTOFFICE_DELMSG,						//[����]		

	DBMSG_REQUEST_POSTOFFICE_SETFEE,						//[����]���� �����Ḧ �����Ѵ�
	DBMSG_RESPONSE_POSTOFFICE_SETFEE,						//[����]

	DBMSG_REQUEST_POSTOFFICE_MASTERSENDITEM,				//[����]��ڰ� ��ǰ ������ ��û�Ѵ�
	DBMSG_RESPONSE_POSTOFFICE_MASTERSENDITEM,				//[����]

	DBMSG_REQUEST_POSTOFFICE_GETRECORD,						//[����]�ۼ��ų����� ��û�Ѵ�
	DBMSG_RESPONSE_POSTOFFICE_GETRECORD,					//[����]

	DBMSG_REQUEST_GET_SAVEUSERITEM,							//[����]���� ���� �ȵ� ������ �������� ���´�
	DBMSG_RESPONSE_GET_SAVEUSERITEM,

	DBMSG_REQUEST_GET_SAVEUSERITEMLIST,						//[����]���� ���� �ȵ� ������ ������ ����Ʈ�� ���´�
	DBMSG_RESPONSE_GET_SAVEUSERITEMLIST,

	//KHY - 1127 - Ŭ��� ��ǰ ���� ����
	DBMSG_REQUEST_GET_SAVEUSERHORSE,						//[��]���� ���� �ȵ� ������ ��µ����� ���´�
	DBMSG_RESPONSE_GET_SAVEUSERHORSE,

	
	DBMSG_REQUEST_CHAR_NAME_CHECK,							//[����] ��ü �޽���. ĳ���� �̸��� DB�� �����ϴ��� �˻�.
	DBMSG_RESPONSE_CHAR_NAME_CHECK,							//[����] ��ü �޽���. ĳ���� �̸��� DB�� �����ϴ��� �˻�.

	DBMSG_REQUEST_FRIEND_INFO,								//[����] ģ������ ���.(���ӿ��ο� ��� ����) 2008-8-6
	DBMSG_RESPONSE_FRIEND_INFO,								//[����] 

	DBMSG_REQUEST_GUILD_INFO,								//[����] ��� ���� ���.(���ӿ��ο� ��� ����) 2008-8-6
	DBMSG_RESPONSE_GUILD_INFO,								//[����] 

	DBMSG_REQUEST_VILLAGE_RESIDENT_INFO,					//[����] ���� �ֹ� ���� ���.(���ӿ��ο� ��� ����) 2008-8-6
	DBMSG_RESPONSE_VILLAGE_RESIDENT_INFO,					//[����] 

	//------------------------
	// �纹�� 
	//------------------------
	DBMSG_REQUEST_HORSEMARKET_GETMANYORDER = 1900,			//[����] �������� �纹�� �ֹ��� ��û�Ѵ�. 
	DBMSG_RESPONSE_HORSEMARKET_GETMANYORDER,				//[����]

	DBMSG_REQUEST_HORSEMARKET_ORDERSELL,					//[����]�纹�ÿ��� ���� �ֹ��� �ִ´� 
	DBMSG_RESPONSE_HORSEMARKET_ORDERSELL,					//[����]

	DBMSG_REQUEST_HORSEMARKET_BUYHORSE,						//[����]�纹�ÿ��� ���� ������ ���� ��û�Ѵ�. 
	DBMSG_RESPONSE_HORSEMARKET_BUYHORSE,					//[����]

	DBMSG_REQUEST_HORSEMARKET_MYACCOUNT,					//[����]�ú��� ���� ������ ��û�Ѵ�. 
	DBMSG_RESPONSE_HORSEMARKET_MYACCOUNT,					//[����]

	DBMSG_REQUEST_HORSEMARKET_OUTHORSE,						//[����]�纹�� â��κ��� ���� ���������� ��û�Ѵ�. 
	DBMSG_RESPONSE_HORSEMARKET_OUTHORSE,					//[����]

	DBMSG_REQUEST_HORSEMARKET_SETFEE,						//[����]�纹�� �����Ḧ �����Ѵ�. 
	DBMSG_RESPONSE_HORSEMARKET_SETFEE,						//[����]

	DBMSG_REQUEST_REDUCEHORSEORDERPRICE,					//[����]�ֹ� ������ ����� 
	DBMSG_RESPONSE_REDUCEHORSEORDERPRICE,					//[����]


	//------------------------
	// �Ű�
	//------------------------
	DBMSG_REQUEST_REALESTATEMARKET_GETMANYORDER = 2000,			//[����] �������� �Ű� �ֹ��� ��û�Ѵ�. 
	DBMSG_RESPONSE_REALESTATEMARKET_GETMANYORDER,				//[����]

	DBMSG_REQUEST_REALESTATEMARKET_ORDERSELL,					//[����] �Ű����� ���� �ֹ��� �ִ´� 
	DBMSG_RESPONSE_REALESTATEMARKET_ORDERSELL,					//[����]

	DBMSG_REQUEST_REALESTATEMARKET_BUY,							//[����] �Ű����� �ε����� ������ ���� ��û�Ѵ�. 
	DBMSG_RESPONSE_REALESTATEMARKET_BUY,						//[����]

	DBMSG_REQUEST_REALESTATEMARKET_MYORDER,						//[����] �Ű� �� �ֹ� ������ ��û�Ѵ�. 
	DBMSG_RESPONSE_REALESTATEMARKET_MYORDER,					//[����]

	DBMSG_REQUEST_REALESTATEMARKET_CANCELORDER,					//[����] �Ű� �ֹ��� ����Ѵ� 
	DBMSG_RESPONSE_REALESTATEMARKET_CANCELORDER,				//[����]

	DBMSG_REQUEST_REALESTATEMARKET_DELORDER,
	DBMSG_RESPONSE_REALESTATEMARKET_DELORDER,

	DBMSG_REQUEST_REALESTATEMARKET_SETFEE,						//[����] �Ű� �����Ḧ �����Ѵ�. 
	DBMSG_RESPONSE_REALESTATEMARKET_SETFEE,						//[����]

	DBMSG_REQUEST_REDUCEREALESTATEORDERPRICE,					//[����] �ֹ� ������ ����� 
	DBMSG_RESPONSE_REDUCEREALESTATEORDERPRICE,					//[����]


	//------------------------
	// �忹��
	//------------------------
	DBMSG_REQUEST_SUMMONMARKET_GETMANYORDER = 2100,			//[����] �������� �忹�� �ֹ��� ��û�Ѵ�. 
	DBMSG_RESPONSE_SUMMONMARKET_GETMANYORDER,				//[����]

	DBMSG_REQUEST_SUMMONMARKET_ORDERSELL,					//[����] �忹������ ���� �ֹ��� �ִ´� 
	DBMSG_RESPONSE_SUMMONMARKET_ORDERSELL,					//[����]

	DBMSG_REQUEST_SUMMONMARKET_BUY,							//[����] �忹������ ��ȯ���� ������ ���� ��û�Ѵ�. 
	DBMSG_RESPONSE_SUMMONMARKET_BUY,						//[����]

	DBMSG_REQUEST_SUMMONMARKET_MYORDER,						//[����] �忹�� �� �ֹ� ������ ��û�Ѵ�. 
	DBMSG_RESPONSE_SUMMONMARKET_MYORDER,					//[����]

	DBMSG_REQUEST_SUMMONMARKET_CANCELORDER,					//[����] �忹�� �ֹ��� ����Ѵ� 
	DBMSG_RESPONSE_SUMMONMARKET_CANCELORDER,				//[����]

	DBMSG_REQUEST_SUMMONMARKET_SETFEE,						//[����] �忹�� �����Ḧ �����Ѵ�. 
	DBMSG_RESPONSE_SUMMONMARKET_SETFEE,						//[����]

	DBMSG_REQUEST_REDUCESUMMONORDERPRICE,					//[����] �ֹ� ������ ����� 
	DBMSG_RESPONSE_REDUCESUMMONORDERPRICE,					//[����]

	//------------------------
	// ���Ի�
	//------------------------
	DBMSG_REQUEST_SHIPMARKET_GETMANYORDER = 2200,			//[����] �������� ���Ի� �ֹ��� ��û�Ѵ�. 
	DBMSG_RESPONSE_SHIPMARKET_GETMANYORDER,					//[����]

	DBMSG_REQUEST_SHIPMARKET_ORDERSELL,						//[����] ���Ի翡�� ���� �ֹ��� �ִ´� 
	DBMSG_RESPONSE_SHIPMARKET_ORDERSELL,					//[����]

	DBMSG_REQUEST_SHIPMARKET_BUY,							//[����] ���Ի翡�� �踦 ������ ���� ��û�Ѵ�. 
	DBMSG_RESPONSE_SHIPMARKET_BUY,							//[����]

	DBMSG_REQUEST_SHIPMARKET_MYORDER,						//[����] ���Ի� �� �ֹ� ������ ��û�Ѵ�. 
	DBMSG_RESPONSE_SHIPMARKET_MYORDER,						//[����]

	DBMSG_REQUEST_SHIPMARKET_CANCELORDER,					//[����] ���Ի� �ֹ��� ����Ѵ� 
	DBMSG_RESPONSE_SHIPMARKET_CANCELORDER,					//[����]

	DBMSG_REQUEST_SHIPMARKET_SETFEE,						//[����] ���Ի� �����Ḧ �����Ѵ�. 
	DBMSG_RESPONSE_SHIPMARKET_SETFEE,						//[����]

	DBMSG_REQUEST_REDUCESHIPORDERPRICE,						//[����] �ֹ� ������ ����� 
	DBMSG_RESPONSE_REDUCESHIPORDERPRICE,					//[����]


	//------------------------
	// ����
	//------------------------
	DBMSG_REQUEST_MANYLANDUNIT = 2300,						//[����]���� �������� ������ ���´�. 
	DBMSG_RESPONSE_MANYLANDUNIT,							//[����]

	DBMSG_REQUEST_LAND_CHANGECONTRACT,						//[����]�������� ��� ������ �����Ѵ�. 
	DBMSG_RESPONSE_LAND_CHANGECONTRACT,						//[����]

	DBMSG_REQUEST_LAND_RENTAPPLY,							//[����]�������� ���� ��û�Ѵ�.
	DBMSG_RESPONSE_LAND_RENTAPPLY,							//[����]

	DBMSG_REQUEST_LAND_CANCELRENTAPPLY,						//[����]������ ���� ��û�� ����Ѵ�. 
	DBMSG_RESPONSE_LAND_CANCELRENTAPPLY,					//[����]

	DBMSG_REQUEST_LAND_APPLYERLIST,							//[����]���� ����� ����� ���´�. 
	DBMSG_RESPONSE_LAND_APPLYERLIST,						//[����]

	DBMSG_REQUEST_LAND_DELAPPLYER,							//[����]���� ��û���� ����� �����Ѵ�. 
	DBMSG_RESPONSE_LAND_DELAPPLYER,							//[����]

	DBMSG_REQUEST_LAND_RENT,								//[����]�������� �Ӵ��Ѵ�. 
	DBMSG_RESPONSE_LAND_RENT,								//[����]

	DBMSG_REQUEST_LAND_PAYRENTFEE,							//[����]�Ӵ�Ḧ �����Ѵ�. 
	DBMSG_RESPONSE_LAND_PAYRENTFEE,							//[����]

	DBMSG_REQUEST_LAND_RECALL,								//[����]�������� ȸ���Ѵ� 
	DBMSG_RESPONSE_LAND_RECALL,								//[����]

	//------------------------
	// ���ڽ�
	//------------------------
	DBMSG_REQUEST_FEAST_RESERVE = 2400,						//[����] ��ȸ ���� ��û�� �Ѵ� 
	DBMSG_RESPONSE_FEAST_RESERVE,							//[����]

	DBMSG_REQUEST_FEAST_OPEN,								//[����] ��ȸ�� �����Ѵ�
	DBMSG_RESPONSE_FEAST_OPEN,								//[����]

	DBMSG_REQUEST_FEAST_CLOSE,								//[����] ��ȸ�� �����Ѵ� 
	DBMSG_RESPONSE_FEAST_CLOSE,								//[����]

	DBMSG_REQUEST_FEAST_SETCOST,							//[����] ���� �����Ѵ�
	DBMSG_RESPONSE_FEAST_SETCOST,							//[����]

	DBMSG_REQUEST_FEAST_ADDPRESENTLIST,						//[����] ���ڽ� ����� ���� �׸��� �߰��Ѵ� 
	DBMSG_RESPONSE_FEAST_ADDPRESENTLIST,					//[����]

	DBMSG_REQUEST_FEAST_DELPRESENTLIST,						//[����] ���ڽ� ����� ���� �׸��� �����Ѵ� 
	DBMSG_RESPONSE_FEAST_DELPRESENTLIST,					//[����]

	DBMSG_REQUEST_FEAST_STGITEMIN,							//[����] ���ڽ� ����� ��ǰ�� â�� �ִ´� 
	DBMSG_RESPONSE_FEAST_STGITEMIN,							//[����]

	DBMSG_REQUEST_FEAST_STGITEMOUT,							//[����] ���ڽ� ����� â���� ��ǰ�� �����´� 
	DBMSG_RESPONSE_FEAST_STGITEMOUT,						//[����]

	DBMSG_REQUEST_FEAST_GIVEITEM,							//[����] ��ȸ �����ڰ� ������ �ٸ� �����鿡�� �й��Ѵ� 
	DBMSG_RESPONSE_FEAST_GIVEITEM,							//[����]

	//#if defined(_LEON_FEAST_EFFECT)
	DBMSG_REQUEST_FEAST_USEEFFECT,							//[�뷡] ��ȸ �����ڰ� �����̿���� ����Ѵ�
	DBMSG_RESPONSE_FEAST_USEEFFECT,							//[�뷡]
	//#endif

	DBMSG_REQUEST_PARTYHALL_RESERVATION,					//[����] ��ƼȦ. ��Ƽ�� ����.		 => 2008. 3. 13
	DBMSG_RESPONSE_PARTYHALL_RESERVATION,

	DBMSG_REQUEST_PARTYHALL_ADD_PRESENT,					//[����] ��ƼȦ. ���� �߰�.			 => 2008. 3. 13
	DBMSG_RESPONSE_PARTYHALL_ADD_PRESENT,
		
	DBMSG_REQUEST_PARTYHALL_ADD_DECORATION,					//[����] ��ƼȦ. ���ǰ �߰�.		 => 2008. 3. 12
	DBMSG_RESPONSE_PARTYHALL_ADD_DECORATION,

	DBMSG_REQUEST_PARTYHALL_CLOSE,							//[����] ��ƼȦ. ����.				 => 2008. 3. 12
	DBMSG_RESPONSE_PARTYHALL_CLOSE,							

	DBMSG_REQUEST_PARTYHALL_GIVEITEM,						//[����] ��ƼȦ. ������ �ֱ�.		 => 2008. 3. 12
	DBMSG_RESPONSE_PARTYHALL_GIVEITEM,

	DBMSG_REQUEST_PARTYHALL_RESERVELIST,					//[����] ��ƼȦ. ����Ʈ ��û. 
	DBMSG_RESPONSE_PARTYHALL_RESERVELIST,

	DBMSG_REQUEST_PARTYHALL_DECORATION_LIST,					//[����] ��ƼȦ. ��Ĺ� ����Ʈ ��û.
	DBMSG_RESPONSE_PARTYHALL_DECORATION_LIST,

	
	//------------------------
	// �񺯻�
	//------------------------
	DBMSG_REQUEST_SUMMONHEROMARKET_GETMANYORDER = 2500,			//[����] �������� �񺯻� �ֹ��� ��û�Ѵ�. 
	DBMSG_RESPONSE_SUMMONHEROMARKET_GETMANYORDER,				//[����]

	DBMSG_REQUEST_SUMMONHEROMARKET_ORDERSELL,					//[����] �񺯻翡�� ���� �ֹ��� �ִ´� 
	DBMSG_RESPONSE_SUMMONHEROMARKET_ORDERSELL,					//[����]

	DBMSG_REQUEST_SUMMONHEROMARKET_BUY,							//[����] �񺯻翡�� ��ȯ������ ������ ���� ��û�Ѵ�. 
	DBMSG_RESPONSE_SUMMONHEROMARKET_BUY,						//[����]

	DBMSG_REQUEST_SUMMONHEROMARKET_MYORDER,						//[����] �񺯻� �� �ֹ� ������ ��û�Ѵ�. 
	DBMSG_RESPONSE_SUMMONHEROMARKET_MYORDER,					//[����]

	DBMSG_REQUEST_SUMMONHEROMARKET_CANCELORDER,					//[����] �񺯻� �ֹ��� ����Ѵ� 
	DBMSG_RESPONSE_SUMMONHEROMARKET_CANCELORDER,				//[����]

	DBMSG_REQUEST_SUMMONHEROMARKET_SETFEE,						//[����] �񺯻� �����Ḧ �����Ѵ�. 
	DBMSG_RESPONSE_SUMMONHEROMARKET_SETFEE,						//[����]

	DBMSG_REQUEST_REDUCESUMMONHEROORDERPRICE,					//[����] �ֹ� ������ ����� 
	DBMSG_RESPONSE_REDUCESUMMONHEROORDERPRICE,					//[����]


	//------------------------
	// ����
	//------------------------
	DBMSG_REQUEST_MANYMINEUNIT = 2600,						//[����]���� ä������ ������ ���´�. 
	DBMSG_RESPONSE_MANYMINEUNIT,							//[����]

	DBMSG_REQUEST_MINE_CHANGECONTRACT,						//[����]ä������ ��� ������ �����Ѵ�. 
	DBMSG_RESPONSE_MINE_CHANGECONTRACT,						//[����]

	DBMSG_REQUEST_MINE_RENTAPPLY,							//[����]ä������ ���� ��û�Ѵ�.
	DBMSG_RESPONSE_MINE_RENTAPPLY,							//[����]

	DBMSG_REQUEST_MINE_CANCELRENTAPPLY,						//[����]ä���� ���� ��û�� ����Ѵ�. 
	DBMSG_RESPONSE_MINE_CANCELRENTAPPLY,					//[����]

	DBMSG_REQUEST_MINE_APPLYERLIST,							//[����]���� ����� ����� ���´�. 
	DBMSG_RESPONSE_MINE_APPLYERLIST,						//[����]

	DBMSG_REQUEST_MINE_DELAPPLYER,							//[����]���� ��û���� ����� �����Ѵ�. 
	DBMSG_RESPONSE_MINE_DELAPPLYER,							//[����]

	DBMSG_REQUEST_MINE_RENT,								//[����]ä������ �Ӵ��Ѵ�. 
	DBMSG_RESPONSE_MINE_RENT,								//[����]

	DBMSG_REQUEST_MINE_PAYRENTFEE,							//[����]�Ӵ�Ḧ �����Ѵ�. 
	DBMSG_RESPONSE_MINE_PAYRENTFEE,							//[����]

	DBMSG_REQUEST_MINE_RECALL,								//[����]ä������ ȸ���Ѵ� 
	DBMSG_RESPONSE_MINE_RECALL,								//[����]

	//------------------------------
	// Guild
	//-------------------------------
	DBMSG_REQUEST_GUILD_CREATEGUILD = 2700,					//[�ؿ�] ��� ������ ��û�Ѵ�.
	DBMSG_RESPONSE_GUILD_CREATEGUILD,

	DBMSG_REQUEST_GUILD_DESTROYGUILD,						//[�ؿ�] ��� ��ü�� ��û�Ѵ�.
	DBMSG_RESPONSE_GUILD_DESTROYGUILD,

	DBMSG_REQUEST_GUILD_JOINGUILD,							//[�ؿ�] ��� ������ ��û�Ѵ�.
	DBMSG_RESPONSE_GUILD_JOINGUILD,

	DBMSG_REQUEST_GUILD_CONFIRMJOINGUILD,					//[�ؿ�] ��� ������ �㰡�Ѵ�.
	DBMSG_RESPONSE_GUILD_CONFIRMJOINGUILD,

	DBMSG_REQUEST_GUILD_LEAVEGUILD,							//[�ؿ�] ��� Ż�� ��û�Ѵ�.
	DBMSG_RESPONSE_GUILD_LEAVEGUILD,

	DBMSG_REQUEST_GUILD_CHANGEVILLAGE,						//[�ؿ�] ��� ������ �̵��� ��û�Ѵ�.
	DBMSG_RESPONSE_GUILD_CHANGEVILLAGE,

	DBMSG_REQUEST_GUILD_CHANGEGUILDPOINT,					//[�ؿ�] GP(Guild Point)�� ��ȭ�Ǿ���.
	DBMSG_RESPONSE_GUILD_CHANGEGUILDPOINT,

	DBMSG_REQUEST_GUILD_GETGUILDINFO,						//[�ؿ�] ����� ������ ��û�Ѵ�.
	DBMSG_RESPONSE_GUILD_GETGUILDINFO,

	DBMSG_REQUEST_GUILD_CONFIRMCREATEGUILD,					//[�ؿ�] ��� ������ �㰡�Ѵ�.
	DBMSG_RESPONSE_GUILD_CONFIRMCREATEGUILD,

	DBMSG_REQUEST_GUILD_SETSECONDMASTER,					//[�ؿ�] �α������ �����Ѵ�.
	DBMSG_RESPONSE_GUILD_SETSECONDMASTER,

	DBMSG_REQUEST_GUILD_GIVEGUILDMONEY,						//[�ؿ�] ��� �ڱ��� �����Ѵ�.
	DBMSG_RESPONSE_GUILD_GIVEGUILDMONEY,

	DBMSG_REQUEST_GUILD_GIVE_FEE,							//[�ؿ�] ����� �����Ḧ �ǹ��� �����Ѵ�.
	DBMSG_RESPONSE_GUILD_GIVE_FEE,

	DBMSG_REQUEST_GUILD_CHANGESTATUS,						//[�ؿ�] ��� �ɷ�ġ�� �����Ѵ�.
	DBMSG_RESPONSE_GUILD_CHANGESTATUS,

	DBMSG_REQUEST_GUILD_SETSTRFEERATE,						//[�ؿ�] ��� �ǹ��� �����Ḧ �����Ѵ� - ���
	DBMSG_RESPONSE_GUILD_SETSTRFEERATE,

	DBMSG_REQUEST_GUILD_LEVELUP,							//[�ؿ�] ��尡 �������� �Ͽ���.
	DBMSG_RESPONSE_GUILD_LEVELUP,

	DBMSG_REQUEST_GUILD_SETMARK,							//[�ؿ�] ��� ��ũ ����
	DBMSG_RESPONSE_GUILD_SETMARK,

	DBMSG_REQUEST_GUILD_CHANGENAME,							//[�ؿ�] ��� �̸� ����
	DBMSG_RESPONSE_GUILD_CHANGENAME,

	DBMSG_REQUEST_GUILD_CHANGEMASTER,						//[����] ��� ������ ����
	DBMSG_RESPONSE_GUILD_CHANGEMASTER,				

	DBMSG_REQUEST_GUILD_CLOSEGUILD,							//[����] ��� ���
	DBMSG_RESPONSE_GUILD_CLOSEGUILD,

	DBMSG_REQUEST_GUILDWAR_ADDRESERVE,						//[����] ����� ����
	DBMSG_RESPONSE_GUILDWAR_ADDRESERVE,

	DBMSG_REQUEST_GUILDWAR_RESERVELIST,						//[����] ����� ���� ����Ʈ �޾ƿ���
	DBMSG_RESPONSE_GUILDWAR_RESERVELIST,

	DBMSG_REQUEST_GUILDDUNGEON_APPLY,						//[����] ����� ������ ��û
	DBMSG_RESPONSE_GUILDDUNGEON_APPLY,						

	DBMSG_REQUEST_GUILDDUNGEON_SAVESTATUS,
	DBMSG_RESPONSE_GUILDDUNGEON_SAVESTATUS,

	DBMSG_REQUEST_GUILDDUNGEON_LOADSTATUS,
	DBMSG_RESPONSE_GUILDDUNGEON_LOADSTATUS,

	DBMSG_REQUEST_GUILDDUNGEON_TRANSFEROWNERSHIP,			//[����] ��� ������ ����
	DBMSG_RESPONSE_GUILDDUNGEON_TRANSFEROWNERSHIP,

	//DBMSG_REQUEST_GUILD_CHANGEVILLAGELIST,					//[����] ��� ���� ��⸮��Ʈ
	//DBMSG_RESPONSE_GUILD_CHANGEVILLAGELIST,


	//------------------------
	// �ý��� 
	//------------------------
	DBMSG_REQUEST_SETUSERNUM	= 5000,						//[�°�] ����� ���� �����Ѵ�. 

	DBMSG_REQUEST_SETTIME,									//[�°�] �ð��� DB�� �����ϵ��� �Ѵ�. 
	DBMSG_RESPONSE_SETTIME,									//[�°�]

	DBMSG_REQUEST_GETTIME,									//[�°�] �ð��� DB���� �ҷ������� �Ѵ�. 
	DBMSG_RESPONSE_GETTIME,									//[�°�]

	DBMSG_REQUEST_BLOCK,									//[�°�] ������� �α����� ���´�.
	DBMSG_RESPONSE_BLOCK,									//[�°�]


	DBMSG_REQUEST_PRIVATETRADE,								//[���] ���� �ŷ�
	DBMSG_RESPONSE_PRIVATETRADE,							//[���]

	DBMSG_REQUEST_USERCHARINFO,								//[�°�] ����� ĳ������ ���� ��û. 
	DBMSG_RESPONSE_USERCHARINFO,							//[�°�]	

	DBMSG_REQUEST_ACCOUNTINFO,								//[����]
	DBMSG_RESPONSE_ACCOUNTINFO,								//[����]

	DBMSG_REQUEST_BLOCKUSER,								//[�°�]
	DBMSG_RESPONSE_BLOCKUSER,								//[�°�] Ư�� ������ Person�� ��ó���Ѵ�. 

	DBMSG_REQUEST_STARTGAME,								//[�°�] �Խ� ����. 
	DBMSG_RESPONSE_STARTGAME,								//[�°�]

	DBMSG_REQUEST_PING,										//[�°�] DB�Ŵ��� ���� Ȯ��
	DBMSG_RESPONSE_PING,									//[�°�]

	DBMSG_REQUEST_MAPTYPEINFO,								//[�°�] ���� Ÿ�� ���� ��û.  
	DBMSG_RESPONSE_MAPTYPEINFO,								//[�°�]

	DBMSG_REQUEST_WARPVILLAGE,								//[����] ������ Warp ��û 
	DBMSG_RESPONSE_WARPVILLAGE,								//[����]

	DBMSG_REQUEST_MASTERGIVEITEM,							//[����]��ڰ� Ư�� ������ ������ �������� �������� �������� �����Ѵ�.
	DBMSG_RESPONSE_MASTERGIVEITEM,							//[����]

	DBMSG_REQUEST_GIVEITEM,									//[����]��ڰ� Ư�� ������ ������ �������� �������� �������� �����Ѵ�.
	DBMSG_RESPONSE_GIVEITEM,								//[����]

	DBMSG_REQUEST_DBSYSTEMINFO,								//[����]DB ������ ���´�.
	DBMSG_RESPONSE_DBSYSTEMINFO,							//[����]

	DBMSG_REQUEST_DBSTARTINFO,								//[���]���� �ӽÿ� �ʿ��� ������ �޾ƿ�
	DBMSG_RESPONSE_DBSTARTINFO,								//[���]

	DBMSG_REQUEST_ACCOUNTINFOFORHANXNOTI,					//[����]�������� ĳ���� ������ ��û�Ѵ� - HanXNoti ��
	DBMSG_RESPONSE_ACCOUNTINFOFORHANXNOTI,					//[����]

	DBMSG_REQUEST_CHARINFOFORHANXNOTI,						//[����]ĳ���� ������ ��û�Ѵ� - HanXNoti ��
	DBMSG_RESPONSE_CHARINFOFORHANXNOTI,						//[����]

	DBMSG_REQUEST_USERCHARITEMINFO,							//[����] ĳ���� ������ ������ ��û
	DBMSG_RESPONSE_USERCHARITEMINFO,						//[����]
	DBMSG_RESPONSE_USERCHARITEMINFO2,						//[����] �뷮������ 2���� �и�

	DBMSG_REQUEST_SETFOURLEAF,								//[����] ���� ����� ����Ŭ�ι� ����ũ ����. => 2008-8-14
	DBMSG_RESPONSE_SETFOURLEAF,

	//---------------------------
	// ���� ���� 
	//---------------------------
	DBMSG_REQUEST_PUSHLETTER = 5100,						//[�°�]������ DB�� �����Ѵ�. 
	DBMSG_RESPONSE_PUSHLETTER,								//[�°�]

	DBMSG_REQUEST_POPLETTER,								//[�°�]������ DB���� �����´�.
	DBMSG_RESPONSE_POPLETTER,								//[�°�]

	//---------------------------
	// ������ ������� �� ���� ���� 
	//---------------------------
	DBMSG_REQUEST_PUSHACCOUNTLETTER,
	DBMSG_RESPONSE_PUSHACCOUNTLETTER,
	DBMSG_REQUEST_POPACCOUNTLETTER,
	DBMSG_RESPONSE_POPACCOUNTLETTER,	

	//---------------------------
	// ��ǥ ����
	//---------------------------
	DBMSG_REQUEST_VOTEKINGSELECTION,						//[���]
	DBMSG_RESPONSE_VOTEKINGSELECTION,						//[���]

	DBMSG_REQUEST_VOTEKINGAGGREGATE,						//[����] ���� ��ǥ ��踦 ��û
	DBMSG_RESPONSE_VOTEKINGAGGREGATE,						//[����] 

	DBMSG_REQUEST_VOTEINIT,									//[���]
	DBMSG_RESPONSE_VOTEINIT,								//[���]


	//---------------------------
	// Daily quest
	//---------------------------
	DBMSG_REQUEST_DAILYQUESTADD,							//[���]
	DBMSG_RESPONSE_DAILYQUESTADD,							//[���]

	DBMSG_REQUEST_DAILYQUESTDEL,							//[���]
	DBMSG_RESPONSE_DAILYQUESTDEL,							//[���]

	DBMSG_REQUEST_DAILYQUESTCHANGE,							//[���]
	DBMSG_RESPONSE_DAILYQUESTCHANGE,						//[���]

	//-------------------------
	// �ε��� ���� 
	//-------------------------
	DBMSG_REQUEST_EXTENDCONTRACT	= 5200,					//[�°�]�ε��� ����� �����Ѵ�. 
	DBMSG_RESPONSE_EXTENDCONTRACT,							//[�°�]

	//-------------------------
	// �ǹ� ���� �޽���. 
	//-------------------------
	DBMSG_REQUEST_SETSTRINFO	= 5300,						//[�°�]�ǹ� ������ ������ ���� ��û�Ѵ�.. 
	DBMSG_RESPONSE_SETSTRINFO,								//[�°�]

	DBMSG_REQUEST_GETSTRINFO,								//[�°�]�ǹ� ������ ������ ���� ��û�Ѵ�.. 
	DBMSG_RESPONSE_GETSTRINFO,								//[�°�]

	DBMSG_REQUEST_SETTAX,									//[����] �ǹ� ������ �����Ѵ� 
	DBMSG_RESPONSE_SETTAX,									//[����]

	DBMSG_REQUEST_PAYTAX,									//[����] �ǹ� ������ �����Ѵ�
	DBMSG_RESPONSE_PAYTAX,									//[����]

	DBMSG_REQUEST_PAYDIVIDEND,								//[����] ������� ���ֵ鿡�� ����� �Ѵ� 
	DBMSG_RESPONSE_PAYDIVIDEND,								//[����]		

	DBMSG_REQUEST_AUTOPAYDIVIDEND,							//[����] �ڵ����� ���ͱ��� ����Ѵ�.
	DBMSG_RESPONSE_AUTOPAYDIVIDEND,							//[����]	

	DBMSG_REQUEST_PAYFEE,									//[����] �ǹ��� �����Ḧ �����Ѵ� 
	DBMSG_RESPONSE_PAYFEE,									//[����]

	DBMSG_REQUEST_CHANGESTRMONEY,							//[����] �ǹ� �ڱ� ����
	DBMSG_RESPONSE_CHANGESTRMONEY,							//[����]

	DBMSG_REQUEST_SETSTRUCTUREMESSAGE,						//[����] �ǹ� �ȳ��� ���� 
	DBMSG_RESPONSE_SETSTRUCTUREMESSAGE,						//[����]

	DBMSG_REQUEST_CHIEFINFO,								//[����] �ǹ��� ��������� ��û�Ѵ�.
	DBMSG_RESPONSE_CHIEFINFO,								//[����]

	DBMSG_REQUEST_REPAIRSTRUCTURE,							//[����] �ǹ��� �����Ѵ�
	DBMSG_RESPONSE_REPAIRSTRUCTURE,							//[����]

	DBMSG_REQUEST_SETSTRREPAIRITEM,							//[����] �ǹ� ������ �ʿ��� �������� �����Ѵ� 
	DBMSG_RESPONSE_SETSTRREPAIRITEM,						//[����]

	DBMSG_REQUEST_SETSTRDURA,								//[����] �ǹ� �������� �����Ѵ� 
	DBMSG_RESPONSE_SETSTRDURA,								//[����]

	DBMSG_REQUEST_CHANGESTRDURA,							//[����] �ǹ� �������� ����/���� ��Ų��
	DBMSG_RESPONSE_CHANGESTRDURA,							//[����]

	DBMSG_REQUEST_CHANGESTRBASEMONEY,						//[����] �ǹ� �ں���(������ �ʿ��� ��) ����
	DBMSG_RESPONSE_CHANGESTRBASEMONEY,						//[����]

	DBMSG_REQUEST_SETSTRREPAIRAMOUNT,						//[����] �ǹ� ������ �ʿ��� �������� �ٽ� �ʱ�ȭ
	DBMSG_RESPONSE_SETSTRREPAIRAMOUNT,						//[����]

	//----------------------
	// NPC �޽���. 
	//----------------------
	DBMSG_REQUEST_SETFOREIGNMERCHANTNPCINFO	= 5400,			//[���] ���� ������ ������ �V��
	DBMSG_RESPONSE_SETFOREIGNMERCHANTNPCINFO,				//[���] ���� ������ ������ ����

	DBMSG_REQUEST_GETFOREIGNMERCHANTNPCINFO,				//[���] ���� ������ ������ �V��
	DBMSG_RESPONSE_GETFOREIGNMERCHANTNPCINFO,				//[���] ���� ������ ������ ����

	DBMSG_REQUEST_FOREIGNMERCHANTBUYCASHITEM,				//[���] ���� ������ ĳ�� �������� ����
	DBMSG_RESPONSE_FOREIGNMERCHANTBUYCASHITEM,				//[���]

	DBMSG_REQUEST_TRADEMERCHANTSET,							//[���] ���� ������ �⺻ ������ ����
	DBMSG_RESPONSE_TRADEMERCHANTSET,						//[���] 

	DBMSG_REQUEST_TRADEMERCHANTBUYITEMFROMPERSON,			//[���] ������ ���� ���ο��� ������ �Ǹ�
	DBMSG_RESPONSE_TRADEMERCHANTBUYITEMFROMPERSON,			//[���] 

	DBMSG_REQUEST_TRADEMERCHANTBUYSHIPFROMPERSON,			//[���] ���� ����(�ϸ�)�� �踦 �����Ѵ�. ( ���� ���� ���ΰ��� Ʋ�� ������ )
	DBMSG_RESPONSE_TRADEMERCHANTBUYSHIPFROMPERSON,			//[���]

	DBMSG_REQUEST_TRADEMERCHANTBUYHORSEFROMPERSON,			//[���] ������ ���� ���ο��� ���� �Ǹ�
	DBMSG_RESPONSE_TRADEMERCHANTBUYHORSEFROMPERSON,			//[���]

	DBMSG_REQUEST_TRADEMERCHANTBUYITEM,						//[���] ������ ��ǰ�� ����
	DBMSG_RESPONSE_TRADEMERCHANTBUYITEM,					//[���]

	//KHY - 0530 ���� ���� ��������.
	DBMSG_REQUEST_SET_FOREIGNMERCHANTNOWMONEY,				//[��] ���� ������ ���رⰣ���� ������ �׼�.
	DBMSG_RESPONSE_SET_FOREIGNMERCHANTNOWMONEY,				//[��] 

	DBMSG_REQUEST_GET_FOREIGNMERCHANTNOWMONEY,				//[��] ���� ������ ���رⰣ���� ������ �׼�.
	DBMSG_RESPONSE_GET_FOREIGNMERCHANTNOWMONEY,				//[��] 

	DBMSG_REQUEST_SET_FOREIGNMERCHANTBUYLIMIT,				//[��] ���� ������ ���� �Ⱓ���� ������ �� �ִ� �ݾ� ���Ѿ׼�
	DBMSG_RESPONSE_SET_FOREIGNMERCHANTBUYLIMIT,				//[��] 

	DBMSG_REQUEST_GET_FOREIGNMERCHANTBUYLIMIT,				//[��] ���� ������ ���� �Ⱓ���� ������ �� �ִ� �ݾ� ���Ѿ׼�
	DBMSG_RESPONSE_GET_FOREIGNMERCHANTBUYLIMIT,				//[��] 

	//---------------------------
	// ģ�� �߰� ���� ����
	//---------------------------
	DBMSG_REQUEST_FRIENDADD = 5500,							//[���]
	DBMSG_RESPONSE_FRIENDADD,								//[���]

	DBMSG_REQUEST_FRIENDDEL,								//[���]
	DBMSG_RESPONSE_FRIENDDEL,								//[���]

	DBMSG_REQUEST_FRIENDADDLIST,							//[���]
	DBMSG_RESPONSE_FRIENDADDLIST,							//[���]

	DBMSG_REQUEST_FRIENDDELLIST,							//[���]
	DBMSG_RESPONSE_FRIENDDELLIST,							//[���]

	DBMSG_REQUEST_FRIENDMEMO,								
	DBMSG_RESPONSE_FRIENDMEMO,

	DBMSG_REQUEST_FRIENDMEMOSET,
	DBMSG_RESPONSE_FRIENDMEMOSET,	

	DBMSG_REQUEST_FRIENDCHANGEGROUP,						//[����]
	DBMSG_RESPONSE_FRIENDCHANGEGROUP,						//[����]

	DBMSG_REQUEST_FRIENDCHANGEGROUPNAME,					//[����]
	DBMSG_RESPONSE_FRIENDCHANGEGROUPNAME,					//[����]

	DBMSG_REQUEST_FRIENDALLLIST,							//[����]
	DBMSG_RESPONSE_FRIENDALLLIST,							//[����]

	//----------------------
	// �� �޽���. 
	//----------------------
	DBMSG_REQUEST_NEWS	= 5600,								//[�°�]���� �Ź��� ������ ��û. 
	DBMSG_RESPONSE_NEWS,									//[�°�]

	//-----------------------------
	// ������ ��
	//----------------------------------
	DBMSG_REQUEST_ITEMMALLEXISTENCE = 5700,					//[�ؿ�]������ ������ �� ������ ���� ���� ��û
	DBMSG_RESPONSE_ITEMMALLEXISTENCE,

	DBMSG_REQUEST_ITEMMALLITEMLIST,							//[�ؿ�]������ ������ �� ������ ��û
	DBMSG_RESPONSE_ITEMMALLITEMLIST,

	DBMSG_REQUEST_ITEMMALLGETITEM,							//[�ؿ�]������ ������ �� �������� �κ��丮�� �̵� ��û
	DBMSG_RESPONSE_ITEMMALLGETITEM,

	DBMSG_REQUEST_CHANGENAME,								//[�ؿ�] �̸� ������ ��û�Ѵ�.
	DBMSG_RESPONSE_CHANGENAME,

	DBMSG_REQUEST_CHANGE_CHARKIND,							//[�ؿ�] ĳ���� ������ �����Ѵ�.
	DBMSG_RESPONSE_CHANGE_CHARKIND,

	DBMSG_REQUEST_GIVECASH,									//[����] ���ʽ� ĳ���� �����Ѵ�
	DBMSG_RESPONSE_GIVECASH,								//[����]

	DBMSG_REQUEST_NEWSCHATADDMISSION,						//[�ؿ�] �ڸ����� ������ ��û�Ѵ�.
	DBMSG_RESPONSE_NEWSCHATADDMISSION,

	DBMSG_REQUEST_NOLIMITTICKET_WARP,						//[�ؿ�] �����̵����ױ����� ���ѿ����� �����Ѵ�.(�Ⱓ��)
	DBMSG_RESPONSE_NOLIMITTICKET_WARP,

	DBMSG_REQUEST_GET_SEL_PGLIST,							//[�ؿ�] ��ǰ ��� �ҷ�����
	DBMSG_RESPONSE_GET_SEL_PGLIST,

	DBMSG_REQUEST_GET_ITEMMALL_ITEMINFO,					//[�ؿ�] ��ǰ�� ������ ��û�Ѵ�.
	DBMSG_RESPONSE_GET_ITEMMALL_ITEMINFO,

	DBMSG_REQUEST_GET_MYCASH_INFO,							//[�ؿ�] �� ĳ�� ������ ��û�Ѵ�.
	DBMSG_RESPONSE_GET_MYCASH_INFO,

	DBMSG_REQUEST_ITEMMALL_BUYITEM,							//[�ؿ�] ������ ������ ������ ���
	DBMSG_RESPONSE_ITEMMALL_BUYITEM,

	DBMSG_REQUEST_ITEMMALL_GIFTITEM,						//[�ؿ�] ������ ������ ������ �����ϱ�
	DBMSG_RESPONSE_ITEMMALL_GIFTITEM,

	DBMSG_REQUEST_CHECK_ACCOUNTID,							//[�ؿ�] ���̵� ��ȸ
	DBMSG_RESPONSE_CHECK_ACCOUNTID,

	DBMSG_REQUEST_SET_BAGITEM,								//[�ؿ�] ���ָӴ� ������ �����ϱ�
	DBMSG_RESPONSE_SET_BAGITEM,

	DBMSG_REQUEST_SET_CHANGEHERO,							//[�ؿ�] �������� �����ϴ� ���� �����Ѵ�.
	DBMSG_RESPONSE_SET_CHANGEHERO,

	DBMSG_REQUEST_GET_PRESENT_ITEMDATA,						//[����] �������� �������� ������ �����´�.
	DBMSG_RESPONSE_GET_PRESENT_ITEMDATA,

	DBMSG_REQUEST_ITEMMALL_BUYITEM_GLOBAL,					//[����] �۷ι��� ������ ������ ������ ���
	DBMSG_REQUEST_ITEMMALL_GIFTITEM_GLOBAL,					//[����] �۷ι��� ������ ������ ������ �����ϱ�
	DBMSG_REQUEST_GET_MYCASH_INFO_GLOBAL,					//[����] �۷ι��� �� ĳ�� ������ ��û�Ѵ�.
	DBMSG_REQUEST_ITEMMALLGETITEM_GLOBAL,					//[����] �����۸�->�κ��丮(�۷ι�)

	DBMSG_REQUEST_ITEMMALL_BUYITEM_CHINA,					//[����] �߱��� ������ ������ ������ ���
	DBMSG_REQUEST_ITEMMALL_GIFTITEM_CHINA,					//[����] �߱��� ������ ������ ������ �����ϱ�
	DBMSG_REQUEST_GET_MYCASH_INFO_CHINA,					//[����] �߱��� �� ĳ�� ������ ��û�Ѵ�.
	DBMSG_REQUEST_ITEMMALLGETITEM_CHINA,					//[����] �����۸�->�κ��丮(�߱�)

	DBMSG_REQUEST_ITEMMALL_BUYITEM_KOREA,					//[����] ����S�� ������ �� ������ ���
	DBMSG_REQUEST_ITEMMALL_GIFTITEM_KOREA,					//[����] ����S�� ������ �� ������ ����
	DBMSG_REQUEST_GET_MYCASH_INFO_KOREA,					//[]
	DBMSG_REQUEST_ITEMMALLGETITEM_KOREA,

	DBMSG_REQUEST_ITEMMALL_BUYITEM_FORXNOTI,				//[����] ����S�� ������ �� ������ ���� For XNoti - �� ����
	DBMSG_RESPONSE_ITEMMALL_BUYITEM_FORXNOTI,				//[����] ����S�� ������ �� ������ ���� ���� For XNoti - �� ����
	DBMSG_REQUEST_ITEMMALL_GIFTITEM_FORXNOTI,				//[����] ����S�� ������ �� ������ ���� For XNoti - �� ����
	DBMSG_RESPONSE_ITEMMALL_GIFTITEM_FORXNOTI,				//[����] ����S�� ������ �� ������ ���� ���� For XNoti - �� ����
	DBMSG_REQUEST_ITEMMALL_CANCELORDER_XNOTI,				//[����] ����S�� ������ �� ������ ������� FOR XNOTI - �� ����

	DBMSG_REQUEST_ITEMMALLGETITEM_TAIWAN,					//[����] �����۸�->�κ��丮(�븸)

	DBMSG_REQUEST_ITEMMALL_BUYITEM_USA,						//[����] Luminary�� ������ �� ������ ���
	DBMSG_REQUEST_ITEMMALL_GIFTITEM_USA,					//[����] Luminary�� ������ �� ������ ����
	DBMSG_REQUEST_GET_MYCASH_INFO_USA,						//[����] Luminary�� ĳ�� ������ ��û�Ѵ�.
	DBMSG_REQUEST_ITEMMALLGETITEM_USA,						//[]

	//KHY - 0304 - �߱� NHNChinaBilling - 
	DBMSG_REQUEST_ITEMMALL_BUYITEM_NHNCHINA,					//[��] �߱��� ������ ������ ������ ���
	DBMSG_REQUEST_ITEMMALL_GIFTITEM_NHNCHINA,					//[��] �߱��� ������ ������ ������ �����ϱ�
	DBMSG_REQUEST_GET_MYCASH_INFO_NHNCHINA,					//[��] �߱��� �� ĳ�� ������ ��û�Ѵ�.
	DBMSG_REQUEST_ITEMMALLGETITEM_NHNCHINA,					//[��] �����۸�->�κ��丮(�߱�)


	DBMSG_REQUEST_GET_MYCASH_INFO_GERMANY,					//	[��ȣ] ���� �����۸����� �ܾ� ��ȸ
	DBMSG_RESPONSE_GET_MYCASH_INFO_GERMANY,
	DBMSG_REQUEST_ITEMMALL_BUYITEM_GERMANY,					//	[��ȣ] ���Ͽ� �����۸����� ������ ���
	DBMSG_RESPONSE_ITEMMALL_BUYITEM_GERMANY,
	DBMSG_REQUEST_ITEMMALL_GIFTITEM_GERMANY,				//	[��ȣ] ���Ͽ� �����۸����� ������ �����ϱ�
	DBMSG_RESPONSE_ITEMMALL_GIFTITEM_GERMANY,
	DBMSG_REQUEST_ITEMMALLGETITEM_GERMANY,					//	[��ȣ] ���Ͽ� ������ ��������
	DBMSG_RESPONSE_ITEMMALLGETITEM_GERMANY,

	DBMSG_REQUEST_GET_MYCASH_INFO_NDOORS_KOREA,				// [��ȣ_NHN->NDOORS] �ݾ����� REQ
	DBMSG_REQUEST_ITEMMALL_BUYITEM_NDOORS_KOREA,			// [��ȣ_NHN->NDOORS] ���� REQ
	DBMSG_REQUEST_ITEMMALL_GIFTITEM_NDOORS_KOREA,			// [��ȣ_NHN->NDOORS] ���� REQ

	


	//-------------------------------
	// ���� �� 6�� �Ǽ� 
	//-----------------------------
	DBMSG_REQUEST_GETBYUNGZOINFO = 5800,					//[�ؿ�] ���� �Ǽ��� ������ ��û�Ѵ�.
	DBMSG_RESPONSE_GETBYUNGZOINFO,							//[�ؿ�]

	DBMSG_REQUEST_GETGONGZOINFO,							//[�ؿ�]
	DBMSG_RESPONSE_GETGONGZOINFO,							//[�ؿ�]

	DBMSG_REQUEST_GETHYUNGZOINFO,							//[�ؿ�]
	DBMSG_RESPONSE_GETHYUNGZOINFO,							//[�ؿ�]

	DBMSG_REQUEST_GETHOZOINFO,								//[�ؿ�]
	DBMSG_RESPONSE_GETHOZOINFO,								//[�ؿ�]

	DBMSG_REQUEST_GETIZOINFO,								//[�ؿ�]
	DBMSG_RESPONSE_GETIZOINFO,								//[�ؿ�]

	DBMSG_REQUEST_GETYEZOINFO,								//[�ؿ�] ���� �Ǽ��� ������ ��û�Ѵ�.
	DBMSG_RESPONSE_GETYEZOINFO,								//[�ؿ�]

	DBMSG_REQUEST_GETGOONZUINFO,							//[�ؿ�] ������ ������ ��û�Ѵ�.
	DBMSG_RESPONSE_GETGOONZUINFO,							//[�ؿ�]

	DBMSG_REQUEST_SETBYUNGZOINFO,							//[�ؿ�] ���� �Ǽ��� ������ �����Ѵ�.
	DBMSG_RESPONSE_SETBYUNGZOINFO,							//[�ؿ�]
	
    DBMSG_REQUEST_SETBYUNGZOINFO_VILLAGEWARTIME,			//[����] ���� �Ǽ��� ������ �ð��� �����Ѵ�.
	DBMSG_RESPONSE_SETBYUNGZOINFO_VILLAGEWARTIME,			//[����]

	DBMSG_REQUEST_SETGONGZOINFO,							//[�ؿ�]
	DBMSG_RESPONSE_SETGONGZOINFO,							//[�ؿ�]

	DBMSG_REQUEST_SETHYUNGZOINFO,							//[�ؿ�]
	DBMSG_RESPONSE_SETHYUNGZOINFO,							//[�ؿ�]

	DBMSG_REQUEST_SETHOZOINFO,								//[�ؿ�]
	DBMSG_RESPONSE_SETHOZOINFO,								//[�ؿ�]	

	DBMSG_REQUEST_SETIZOINFO,								//[�ؿ�]
	DBMSG_RESPONSE_SETIZOINFO,								//[�ؿ�]

	DBMSG_REQUEST_SETYEZOINFO,								//[�ؿ�]���� �Ǽ��� ������ �����Ѵ�.
	DBMSG_RESPONSE_SETYEZOINFO,								//[�ؿ�]

	DBMSG_REQUEST_SETGOONZUINFO,							//[�ؿ�]������ ������ �����Ѵ�.
	DBMSG_RESPONSE_SETGOONZUINFO,							//[�ؿ�]

	DBMSG_REQUEST_SETGOONZUFINANCES,						//[�ؿ�]������ ������ �����Ѵ�.
	DBMSG_RESPONSE_SETGOONZUFINANCES,						//[�ؿ�]

	DBMSG_REQUEST_GETANGELAPPLYERLIST,						//[�ؿ�] ��ȣõ�� ��û�� ����Ʈ�� �����´�.
	DBMSG_RESPONSE_GETANGELAPPLYERLIST,						//[�ؿ�]

	DBMSG_REQUEST_GETANGELLIST,								//[�ؿ�] ��ȣõ�� ����Ʈ�� �����´�.
	DBMSG_RESPONSE_GETANGELLIST,							//[�ؿ�]

	DBMSG_REQUEST_SETANGELAPPLYER,							//[�ؿ�] ��ȣõ�� ��û�Ѵ�.
	DBMSG_RESPONSE_SETANGELAPPLYER,							//[�ؿ�]

	DBMSG_REQUEST_SETANGEL,									//[�ؿ�] ��ȣõ�� ����̳� �����Ѵ�.
	DBMSG_RESPONSE_SETANGEL,								//[�ؿ�]

	DBMSG_REQUEST_GETPOLICELIST,							//[����] ���� ����Ʈ ������
	DBMSG_RESPONSE_GETPOLICELIST,							//[����]

	DBMSG_REQUEST_SETPOLICE,								//[����] ���� ����
	DBMSG_RESPONSE_SETPOLICE,			

	DBMSG_REQUEST_GETCRIMINALLIST,							//[����] ����� ���
	DBMSG_RESPONSE_GETCRIMINALLIST,							//[����]

	DBMSG_REQUEST_SETCRIMINAL,								//[����] ����� ����
	DBMSG_RESPONSE_SETCRIMINAL,			

	DBMSG_REQUEST_GETCHANGEDNAME,							//[�ؿ�] ����� �̸� ����� �����´�.
	DBMSG_RESPONSE_GETCHANGEDNAME,							//[�ؿ�]

	DBMSG_REQUEST_GETDAILYNEWCHAR,							//[�ؿ�] �Ϸ��� ������ ĳ���͸� �����´�.
	DBMSG_RESPONSE_GETDAILYNEWCHAR,							//[�ؿ�]

	DBMSG_REQUEST_PRISONUSER,								//[�ؿ�]Ư�� ����ڸ� �������� ������.
	DBMSG_RESPONSE_PRISONUSER,								//[�ؿ�]

	DBMSG_REQUEST_SETMINISTER,								//[�ؿ�] ���� �� 6���� �Ӹ��Ѵ�.
	DBMSG_RESPONSE_SETMINISTER,

	DBMSG_REQUEST_WRITELOG,									//[����] �α׳����
	DBMSG_RESPONSE_WRITELOG,								//[����]

	DBMSG_REQUEST_PERSONITEMINFOGET,						//[����] ���������� �������� ��û
	DBMSG_RESPONSE_PERSONITEMINFOGET,						//[����] ���������� �������� ����

	DBMSG_REQUEST_WENNYOLDMAN_SAVEINVENTORY,				//[����] Ȥ�θ�(2ȣ��) �κ��丮�� ���� ��û
	DBMSG_RESPONSE_WENNYOLDMAN_SAVEINVENTORY,				//[����] Ȥ�θ�(2ȣ��) �κ��丮�� ���� ����
	DBMSG_REQUEST_WENNYOLDMAN_MOVEITEMSTGTOINV,				//[����] Ȥ�θ�(2ȣ��) �κ��丮���� ����� �κ��丮�� �̵� ��û
	DBMSG_RESPONSE_WENNYOLDMAN_MOVEITEMSTGTOINV,			//[����] Ȥ�θ�(2ȣ��) �κ��丮���� ����� �κ��丮�� �̵� ����
	DBMSG_REQUEST_WENNYOLDMAN_INVENTORYLIST,				//[����] Ȥ�θ�(2ȣ��) �κ��丮 ����Ʈ ��û
	DBMSG_RESPONSE_WENNYOLDMAN_INVENTORYLIST,				//[����] Ȥ�θ�(2ȣ��) �κ��丮 ����Ʈ ����

	DBMSG_REQUEST_SETLIQUIDATION,							//[����] ���ְ� ���� ������ �����Ѵ�
	DBMSG_RESPONSE_SETLIQUIDATION,

	DBMSG_REQUEST_RECOMMENDPOINT_LIST,						//[����] �ڽ��� ��õ������ ����� ĳ������ ����� �����´�.
	DBMSG_RESPONSE_RECOMMENDPOINT_LIST,

	DBMSG_REQUEST_GOONZU_SETBONUSTIME,							//[����] ���ְ� ���ʽ� Ÿ���� �����Ѵ�.
	DBMSG_RESPONSE_GOONZU_SETBONUSTIME,	

	DBMSG_REQUEST_WRITELOG_PCROOM,							//[����] �Ѱ��� PC�� ���� ��ǥ �α�

	DBMSG_REQUEST_VILLAGEBANKRUPTCY,						//[����] ��� ��ɾ�� �Ļ��� ������ �����Ѵ�.
	DBMSG_RESPONSE_VILLAGEBANKRUPTCY,

	DBMSG_REQUEST_WRITELOGTODB,								//[����] �α׳���� - by LEEKH 2007.08.13
	DBMSG_RESPONSE_WRITELOGTODB,							//[����]

	DBMSG_REQUEST_LOG_GETHAPPYBEANQUESTINFO,				//[����] ���Ǻ� ���� �α׷� ����

	DBMSG_REQUEST_VILLAGEGENERALMEETING,					//[����] ������ȸ �ߵ� ���� ���� DB�� ����.

	//-------------------------------
	// ����
	//-----------------------------
	DBMSG_REQUEST_GACHABUY = 6000,							//[����] ���� ����� ������ ��ȯ
	DBMSG_RESPONSE_GACHABUY,	

	//-------------------------------
	// ���ĸ��� �̺�Ʈ
	//-----------------------------
	DBMSG_REQUEST_MOFUMOFUEVENT_RESERVE = 6100,				//[����] ���ĸ��� �̺�Ʈ ����
	DBMSG_RESPONSE_MOFUMOFUEVENT_RESERVE,	

	DBMSG_REQUEST_MOFUMOFUEVENT_RESERVELIST,				//[����] ���ĸ��� �̺�Ʈ ���� ����Ʈ
	DBMSG_RESPONSE_MOFUMOFUEVENT_RESERVELIST,	

	//-------------------------------
	// �̺�Ʈ ����. //KHY - 0906 - ���ӹ� �̺�Ʈ ����.
	//-----------------------------
	DBMSG_REQUEST_LOG_GETEVENTCOUPONINFO = 6200,  //KHY - 0906 - ���ӹ� �̺�Ʈ ����.
	DBMSG_RESPONSE_GETEVENTCOUPONINFO,

	//-------------------------------
	// ����
	//-----------------------------
	DBMSG_REQUEST_CREATEEMPIRE = 6300,						//[����] ������ �����
	DBMSG_RESPONSE_CREATEEMPIRE,

	DBMSG_REQUEST_DESTROYEMPIRE,							//[����] ������ ��ü�Ѵ�.
	DBMSG_RESPONSE_DESTROYEMPIRE,

	DBMSG_REQUEST_JOINEMPIRE,								//[����] ������ �� �Ѵ�.
	DBMSG_RESPONSE_JOINEMPIRE,

	DBMSG_REQUEST_SECEDEEMPIRE,								//[����] �������� Ż���Ѵ�.
	DBMSG_RESPONSE_SECEDEEMPIRE,

	DBMSG_REQUEST_ALLEMPIREINFO,							//[����] ��� ������ ������ ��û�Ѵ�.
	DBMSG_RESPONSE_ALLEMPIREINFO,

	DBMSG_REQUEST_SETEMPIREMONEY,							//[����] ���� �ں����� �����Ѵ�.
	DBMSG_RESPONSE_SETEMPIREMONEY,

	DBMSG_REQUEST_CHANGEEMPEROR,							//[����] ���� ���ְ� �ٲ��( ����, ������ �ٲ�� )
	DBMSG_RESPONSE_CHANGEEMPEROR,

	//-------------------------------
	//KHY - 1220 - ���Žý���.
	//-----------------------------
	DBMSG_REQUEST_TRANSFORM_SET = 6400,						//[��] ���� ĳ���͸� �����Ѵ�. 
	DBMSG_RESPONSE_TRANSFORM_SET,							//[��]

	DBMSG_REQUEST_GETTRANSFORM,								//[��] ���� ĳ���� ������ �޾ƿ´�. 
	DBMSG_RESPONSE_GETTRANSFORM,							//[��]

	DBMSG_REQUEST_TRANSFORM_ADDCHAR,						//[����] ���� ĳ���� ���
	DBMSG_RESPONSE_TRANSFORM_ADDCHAR,					//[��]

	DBMSG_REQUEST_TRANSFORM_ADDTIME,						//[����] ���� ĳ���� ���ð� ����
	DBMSG_RESPONSE_TRANSFORM_ADDTIME,					//[��]

	//-------------------------------
	// ������ �ý��� - by LEEKH 2007.12.27
	//-----------------------------
	DBMSG_REQUEST_TIMEMETERRATE_ADDTIME = 6450,				//[����] ������ �ð� ����
	DBMSG_RESPONSE_TIMEMETERRATE_ADDTIME,					//[����]

	DBMSG_REQUEST_TIMEMETERRATE_USETIME,					//[����] ������ �ð� ����
	DBMSG_RESPONSE_TIMEMETERRATE_USETIME,					//[����]

	//-------------------------------------------------
	//GMTOOL
	//-------------------------------------------------
	DBMSG_REQUEST_GMTOOL_CHARBASICINFO = 8900,					//[����] GMTOOL ĳ���� ����
	DBMSG_RESPONSE_GMTOOL_CHARBASICINFO,

	DBMSG_REQUEST_GMTOOL_SKILLINFO,								//[����] GMTOOL ��ų ����
	DBMSG_RESPONSE_GMTOOL_SKILLINFO,	

	DBMSG_REQUEST_GMTOOL_ANIMALLINFO,							//[����] GMTOOL ���� ����
	DBMSG_RESPONSE_GMTOOL_ANIMALINFO,	

	DBMSG_REQUEST_GMTOOL_INVENTORYINFO,							//[����] GMTOOL �κ��丮 ����
	DBMSG_RESPONSE_GMTOOL_INVENTORYINFO,

	DBMSG_REQUEST_GMTOOL_REALESTATEINFO,						//[����] GMTOOL �ε��� ����
	DBMSG_RESPONSE_GMTOOL_REALESTATEINFO,

	DBMSG_REQUEST_GMTOOL_SUMMONINFO,							//[����] GMTOOL ��ȯ�� ����
	DBMSG_RESPONSE_GMTOOL_SUMMONINFO,

	//DBMSG_REQUEST_GMTOOL_TRADINGINFO,							//[����] GMTOOL �ŷ� ����
	//DBMSG_RESPONSE_GMTOOL_TRADINGINFO,

	//-------------------------------------------------
	//	AUTOMACRO [�߰� : Ȳ���� 2007. 12. 6 �������α׷� ������.]
	//-------------------------------------------------
	DBMSG_REQUEST_AUTOMACRO,							
	DBMSG_RESPONSE_AUTOMACRO,

	//-------------------------------------------------
	//	[�߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ DB �޽���.]
	//-------------------------------------------------
	DBMSG_REQUEST_ARTIFACT_INVENTORYLIST,		//8914		
	DBMSG_RESPONSE_ARTIFACT_INVENTORYLIST,	
	DBMSG_REQUEST_ARTIFACT_SAVEINVENTORY,				
	DBMSG_RESPONSE_ARTIFACT_SAVEINVENTORY,				
	DBMSG_REQUEST_ARTIFACT_MOVEITEMSTGTOINV,				
	DBMSG_RESPONSE_ARTIFACT_MOVEITEMSTGTOINV,			
	
	DBMSG_REQUEST_ARTIFACT_MIXTURE,				//8920		
	DBMSG_RESPONSE_ARTIFACT_MIXTURE,	
	DBMSG_REQUEST_ARTIFACT_REMOVE,				
	DBMSG_RESPONSE_ARTIFACT_REMOVE,	
	DBMSG_REQUEST_ARTIFACT_SLOT_CREATE,				
	DBMSG_RESPONSE_ARTIFACT_SLOT_CREATE,	

	//-----------------------------------------------------------------
	// ���� ���� ����Ʈ
	//-------------------------------------------------------------------
	DBMSG_REQUEST_HOFLIST,										//[����] ���� ���� ����Ʈ
	DBMSG_RESPONSE_HOFLIST,

	DBMSG_REQUEST_YEARRANKING,
	DBMSG_RESPONSE_YEARRANKING,

	DBMSG_REQUEST_INSTANCEMAPPOINT_INSERT,
	DBMSG_RESPONSE_INSTANCEMAPPOINT_INSERT,


	//----------------------
	// DB�ʱ�ȭ �Ϸ� �޽���
	//----------------------
	DBMSG_REQUEST_DBINITCOMPLETE = 9000,
	DBMSG_RESPONSE_DBINITCOMPLETE,

	DBMSG_REQUEST_INITSTATISTICS,
	DBMSG_RESPONSE_INITSTATISTICS,

	DBMSG_REQUEST_WRITESTATISTICS,


	//---------------------------
	// Daily quest2
	//---------------------------
	DBMSG_REQUEST_DAILYQUEST2ADD,							
	DBMSG_RESPONSE_DAILYQUEST2ADD,							

	DBMSG_REQUEST_DAILYQUEST2DEL,							
	DBMSG_RESPONSE_DAILYQUEST2DEL,							

	DBMSG_REQUEST_DAILYQUEST2CHANGE,						
	DBMSG_RESPONSE_DAILYQUEST2CHANGE,						

	//---------------------------
	// Daily quest3
	//---------------------------
	DBMSG_REQUEST_DAILYQUEST3ADD,							
	DBMSG_RESPONSE_DAILYQUEST3ADD,							

	DBMSG_REQUEST_DAILYQUEST3DEL,							
	DBMSG_RESPONSE_DAILYQUEST3DEL,							

	DBMSG_REQUEST_DAILYQUEST3CHANGE,						
	DBMSG_RESPONSE_DAILYQUEST3CHANGE,	

	//[����] �ǰ������� ���� ��Ų��. => 2008-4-6 : �ּ�ó�� 2008-6-20
	//DBMSG_REQUEST_HEALTH_CHANGE,	
	//DBMSG_RESPONSE_HEALTH_CHANGE,

	// [ ���� ]ä��â ������ �Ѵ�.
	DBMSG_REQUEST_CHAR_OPTION,							//[����] �ɸ��� �ɼ����� ����
	DBMSG_RESPONSE_CHAR_OPTION,							//[����]
	DBMSG_REQUEST_CHAR_GET_OPTION,						//[����] �ɸ��� �ɼ������� ���´�.
	DBMSG_RESPONSE_CHAR_GET_OPTION,						//[����]

	//[����] ���� �̺�Ʈ => 2008-6-19
	DBMSG_REQUEST_SERVER_EVENT_RANK_INFO,				//[����] ���� �̺�Ʈ�� ���õ� ������ DB�� ��û ��Ŷ. => 2008-6-19
	DBMSG_RESPONSE_SERVER_EVENT_RANK_INFO,
	
	DBMSG_REQUEST_SERVER_EVENT_SERVER_INFO,				//[����] ���� �̺�Ʈ�� ������������ ������ DB�� ��û ��Ŷ. => 2008-6-19
	DBMSG_RESPONSE_SERVER_EVENT_SERVER_INFO,
	
	DBMSG_REQUEST_SERVER_EVENT_DAILY_SERVER_INFO,		//[����] ���� �̺�Ʈ�� �Ϸ� ������������ ������ DB�� ��û ��Ŷ. => 2008-6-19
	DBMSG_RESPONSE_SERVER_EVENT_DAILY_SERVER_INFO,

	DBMSG_REQUEST_SERVER_EVENT_PERSONAL_INFO,			//[����] ���� �̺�Ʈ�� ������������ ������ DB�� ��û ��Ŷ. => 2008-6-19
	DBMSG_RESPONSE_SERVER_EVENT_PERSONAL_INFO,

	DBMSG_REQUEST_SERVER_EVENT_SERVER_SCORE_ADD,		//[����] ���� �̺�Ʈ�� �������� ����.		=> 2008-6-19
	DBMSG_REQUEST_SERVER_EVENT_SERVER_DAILY_SCORE_ADD,	//[����] ���� �̺�Ʈ�� �Ϸ� �������� ����.  => 2008-6-19
	
	DBMSG_REQUEST_SERVER_EVENT_SERVER_BUF_KIND,			//[����] ���� �̺�Ʈ�� �������� ����.		=> 2008-6-19
	DBMSG_RESPONSE_SERVER_EVENT_SERVER_BUF_KIND,		//[����] ���� �̺�Ʈ�� �������� ����.		=> 2008-6-19

	DBMSG_REQUEST_SERVER_EVENT_CLEAR,					//[����] ���� ���� �̺�Ʈ ���� �̺�Ʈ ��� ����.				=> 2009-12-30
	
	
	DBMSG_REQUEST_SERVER_EVENT_QUEST_INFO_SET,			// [����] ���� �̺�Ʈ ����Ʈ ���� ���� ��û
	DBMSG_RESPONSE_SERVER_EVENT_QUEST_INFO_SET,			// [����] ���� �̺�Ʈ ����Ʈ ���� ���� ����

	DBMSG_REQUEST_SERVER_EVENT_QUEST_INFO_GET,			// [����] ���� �̺�Ʈ ����Ʈ ���� �ޱ� ��û
	DBMSG_RESPONSE_SERVER_EVENT_QUEST_INFO_GET,			// [����] ���� �̺�Ʈ ����Ʈ ���� �ޱ� ���� 

	DBMSG_REQUEST_SERVER_EVENT_PERSON_SCORE_SET,		// [����] ���� �̺�Ʈ ����Ʈ ���� ���� ���� ��û
	DBMSG_REQUEST_SERVER_EVENT_PERSON_SCORE_GET,		// [����] ���� �̺�Ʈ ����Ʈ ���� ��û
	DBMSG_RESPONSE_SERVER_EVENT_PERSON_SCORE_GET,		// [����] ���� �̺�Ʈ ����Ʈ ���� ��û ����

	DBMSG_REQUEST_SUMMONUSESTON,							//	[����] ��ȯ�� ���� ������ ���
	DBMSG_RESPONSE_SUMMONUSESTON,							//	[����]
	
	DBMSG_REQUEST_GUILD_CHECKDESTROY_MONTH,					//	[����] �Ѵ޿� �ѹ� ��Ȱ�� ��� ����
	DBMSG_RESPONSE_GUILD_CHECKDESTROY_MONTH,				//	[����]

	DBMSG_REQUEST_GUILD_NOTCONNECT_CHANGEMASTER,			//	[����] �Ѵ޵��� ������ ����� ����
	DBMSG_RESPONSE_GUILD_NOTCONNECT_CHANGEMASTER,				

	DBMSG_RESPONSE_SETSPECIALQUEST_CHANGE,					// PCK : ����� ����Ʈ �Ϸ� (�α׿�)
	
	DBMSG_REQUEST_SUMMONSLOTIN,								//	[����] Base���� �ش� �������� ��ȯ���� �ִ´�
	DBMSG_RESPONSE_SUMMONSLOTIN,							//	[����]

	DBMSG_REQUEST_SUMMONSLOTOUT,							//	[����] Slot���� �ش� ��ȯ���� ���� �Ѵ�.
	DBMSG_RESPONSE_SUMMONSLOTOUT,							//	[����]

	DBMSG_REQUEST_SET_SYSTEMBUYITEMNOWMONEY,				//[��] �ý��ۿ��� ������ �������� �ݾ��� �����Ѵ�.
	DBMSG_RESPONSE_SET_SYSTEMBUYITEMNOWMONEY,				//[��] 

	DBMSG_REQUEST_GET_SYSTEMBUYITEMNOWMONEY,				//[��] �ý��ۿ��� ������� ������ �������� ���ž׼� ������ �����´�.
	DBMSG_RESPONSE_GET_SYSTEMBUYITEMNOWMONEY,				//[��] 
	//----------------------------------
	//[����] ȣ�ڻ���.
	//----------------------------------
	DBMSG_REQUEST_AMBER_BOX_SELECT_ITEM_LIST,			//[����] ȣ�ڻ��� ���� ������ ������ ����Ʈ. Ŭ�� �� ����� ������.  
	DBMSG_RESPONSE_AMBER_BOX_SELECT_ITEM_LIST,			//[����] 

	DBMSG_REQUEST_AMBER_BOX_SELECT_ITEM_ADD,            //[����] ���� ������ �߰�.
	//DBMSG_RESPONSE_AMBER_BOX_SELECT_ITEM_LIST,		//[����] ���� ������ �߰��Ǹ� ���þ����� ����Ʈ �� �ֱ�.

	DBMSG_REQUEST_AMBER_BOX_SELECT_ITEM_GET,			//[����] ���� ������ ȹ��.
	DBMSG_RESPONSE_AMBER_BOX_SELECT_ITEM_GET,			//[����] 
	
	// ===================================================================================== //
	//[����] �����
	// ===================================================================================== //
	DBMSG_REQUEST_QUESTION_DAILY_COUNT_SET,
	DBMSG_RESPONSE_QUESTION_DAILY_COUNT_SET,
	
	DBMSG_REQUEST_QUESTION_DAILY_COUNT_GET,
	DBMSG_RESPONSE_QUESTION_DAILY_COUNT_GET,
		
	DBMSG_REQUEST_QUESTION_DAILY_COUNT_DEL,				//[����] ����� ���� �����.
	DBMSG_RESPONSE_QUESTION_DAILY_COUNT_DEL,			//[����] 

	DBMSG_REQUEST_PVP_LEAGUE_BATTLE_END,				//[����] PVP_League ��Ⱑ ������ ��� ��� ���
	DBMSG_RESPONSE_PVP_LEAGUE_BATTLE_END,				//[����] 

	// [����] PVP ���Ѵ��� ������û
	DBMSG_REQUEST_PVP_LEAGUE_INFOGET,
	DBMSG_RESPONSE_PVP_LEAGUE_INFOGET,
	
	// [����] PVP ���Ѵ��� ���̾�α� ���� ��û
	DBMSG_REQUEST_PVP_LEAGUE_UI_INFOGET,
	DBMSG_RESPONSE_PVP_LEAGUE_UI_INFOGET,

	DBMSG_REQUEST_SETMUTETIME,							//[����] ä�ú�� �ð� ����
	DBMSG_RESPONSE_SETMUTETIME,

	DBMSG_REQUEST_GETMUTETIME,							//[����] ä�ú�� �ð� ���
	DBMSG_RESPONSE_GETMUTETIME,

	DBMSG_REQUEST_PVP_LEAGUE_BATTLE_CHANGEGRADE,				//[����] PVP_League ��Ⱑ ������ ��� ��� ���
	DBMSG_RESPONSE_PVP_LEAGUE_BATTLE_CHANGEGRADE,				//[����] 

	// [����]�߷�Ÿ�ε��� ���� ��û
	DBMSG_REQUEST_VALANTINE_INFO_GET,
	DBMSG_RESPONSE_VALANTINE_INFO_GET,
	// [����]�߷�Ÿ�ε��ַ̼����� Ŀ������ ���� ����
	DBMSG_REQUEST_VALANTINE_REQUEST,
	DBMSG_RESPONSE_VALANTINE_REQUEST,
	// [����]�߷�Ÿ�ε��������� ���� ��ǰ�� �޾Ҵ�.
	DBMSG_REQUEST_VALANTINE_GET_PRIZE,
	DBMSG_RESPONSE_VALANTINE_GET_PRIZE,

	// [����] ������ 
	DBMSG_REQUEST_ELIXIR_SET,							// [����] ������ ����.
	DBMSG_RESPONSE_ELIXIR_SET,

	DBMSG_REQUEST_ELIXIR_GET,							// [����] ������ ���� ���.
	DBMSG_RESPONSE_ELIXIR_GET,

	DBMSG_REQUEST_NEWSELECTBOX_ITEM_GET,				// [����] ���� ���� ���ؼ� ���� ������ ��� - 2008.12.17
	DBMSG_RESPONSE_NEWSELECTBOX_ITEM_GET,				// [����]

	//=======================================================================
	// [����] ���ո���.
	//-----------------------------------------------------------------------
	DBMSG_REQUEST_NEWMARKETACCOUNT,						//[����]���հ��� ���� ������ ��û�Ѵ�. 
	DBMSG_RESPONSE_NEWMARKETACCOUNT,					//[����]

	DBMSG_REQUEST_NEWORDERMARKET,						//[����]���հ��ֿ��� �ֹ��� �ִ´� 
	DBMSG_RESPONSE_NEWORDERMARKET,						//[����]

	DBMSG_REQUEST_NEWTRADEMARKET,						//[����]���հ��ֿ��� ������ �� ���� ��û�Ѵ�. 
	DBMSG_RESPONSE_NEWTRADEMARKET,						//[����]

	DBMSG_REQUEST_GETITEMFROMNEWARKET,					//[����]���հ��� â��κ��� �������� ���������� ��û�Ѵ�. 
	DBMSG_RESPONSE_GETITEMFROMNEWMARKET,				//[����]

	DBMSG_REQUEST_NEWMARKETITEMLIST,					//[����]���հ��ֿ��� �÷��� ��ǰ ������ ���´�
	DBMSG_RESPONSE_NEWMARKETITEMLIST,					//[����]

	DBMSG_REQUEST_SETNEWMARKETFEE,	
	DBMSG_RESPONSE_SETNEWMARKETFEE,					

	DBMSG_REQUEST_NEWMARKETRESULT,						//[����]���հ��ֿ��� �ȸ� ������ ������Ʈ�Ѵ�.. 
	DBMSG_RESPONSE_NEWMARKETRESULT,						//[����]

	DBMSG_REQUEST_NEWMARKET_SETITEMPRICE,				//[����]���� ���� ������ �ü� ����
	DBMSG_RESPONSE_NEWMARKET_SETITEMPRICE,				//[����]

	DBMSG_REQUEST_NEWMARKET_INCREASEBANKMONEY,			//[����]���� ���� ������ �ȸ� �ݾ��� ������Ʈ
	DBMSG_RESPONSE_NEWMARKET_INCREASEBANKMONEY,			//[����]

	DBMSG_REQUEST_MANYITEMNEWPRICE,						//[����]�������� ������ ���� ������ ��û�Ѵ�.
	DBMSG_RESPONSE_MANYITEMNEWPRICE,					//[����]

	DBMSG_RESPONSE_MANYITEMNEWPRICE_COMPLETED,			//[����]�������� ������ ���� ������ ��û �Ϸ�

	DBMSG_REQUEST_SETITEMNEWPRICE,						//[����]������ ������ �����Ѵ�. 
	DBMSG_RESPONSE_SETITEMNEWPRICE,						//[����]

	DBMSG_REQUEST_NEWMARKETREDUCEPRICENOTICE,			//[����]���� �϶������� ��û
	DBMSG_RESPONSE_NEWMARKETREDUCEPRICENOTICE,			//[����]

	DBMSG_REQUEST_ITEMMAKERNAMENEW,						//[����] �������� �ø��� ��ȣ�� ������ �̸� ���.
	DBMSG_RESPONSE_ITEMMAKERNAMENEW,					//[����] 

	DBMSG_REQUEST_CELLULAR_PHONE_AUTH,					//[����] �ڵ��� ���� ����.
	DBMSG_RESPONSE_CELLULAR_PHONE_AUTH,					//[����] 
	
	DBMSG_REQUEST_GUILDHUNTMAPWAR_REGLIST,				//[����] ����� ��û
	DBMSG_RESPONSE_GUILDHUNTMAPWAR_REGLIST,

	DBMSG_REQUEST_GUILDHUNTMAPWAR_GET_REGLIST,			//[����] ����� ��û ����Ʈ�� ��û�Ѵ�.
	DBMSG_RESPONSE_GUILDHUNTMAPWAR_GET_REGLIST,
	
	DBMSG_REQUEST_GUILDHUNTMAPWAR_RANK_GET,				//[����] ����� �ʺ� BGP��ũ
	DBMSG_RESPONSE_GUILDHUNTMAPWAR_RANK_GET,
	
	DBMSG_REQUEST_GUILDHUNTMAPWAR_RESULT,				//[����] ����� ���
	DBMSG_RESPONSE_GUILDHUNTMAPWAR_RESULT,

	DBMSG_REQUEST_GUILDHUNTMAPWAR_END,					//[����] ����� ���
	DBMSG_RESPONSE_GUILDHUNTMAPWAR_End,

	DBMSG_REQUEST_SET_MARRY,							//[����] ��ȥ �ý��� : ��ȥ�Ѵ�
	DBMSG_RESPONSE_SET_MARRY,							//[����]

	DBMSG_REQUEST_GET_MARRY_INFO,						//[����] ��ȥ �ý��� : ��ȥ������ ��û�Ѵ�
	DBMSG_RESPONSE_GET_MARRY_INFO,						//[����]

	DBMSG_REQUEST_MARRY_ITEMGET_SET,					//[����] ��ȥ �ý��� : ��ȥ ����� �������� ������¥ ����
	DBMSG_RESPONSE_MARRY_ITEMGET_SET,					//[����]

	DBMSG_REQUEST_MARRY_LOVE_SET,						//[����] ��ȥ �ý��� : ������ ���� ����
	DBMSG_RESPONSE_MARRY_LOVE_SET,						//[����]

	DBMSG_REQUEST_PROMOTER_INFO_GET,					//[����] ���θ��� ĳ�� ����.
	DBMSG_RESPONSE_PROMOTER_INFO_GET,

	DBMSG_REQUEST_WEDDING_RESERVE_LIST_GET,				//[����] ��ȥ �ý��� : ���� ����Ʈ �ޱ�
	DBMSG_RESPONSE_WEDDING_RESERVE_LIST_GET,			//[����]

	DBMSG_REQUEST_WEDDING_RESERVE,						//[����] ��ȥ �ý��� : ���� �ϱ�
	DBMSG_RESPONSE_WEDDING_RESERVE,						//[����]

	DBMSG_REQUEST_WEDDING_RESERVE_CANCEL,				//[����] ��ȥ �ý��� : ���� ���
	DBMSG_RESPONSE_WEDDING_RESERVE_CANCEL,				//[����]

	DBMSG_REQUEST_FAMILY_ADD_CHILDREN,					//[����] ���� �ý��� : �ڳ� ��� 
	DBMSG_RESPONSE_FAMILY_ADD_CHILDREN,					//[����]

	DBMSG_REQUEST_FAMILY_DEL_CHILDREN,					//[����] ���� �ý��� : �ڳ� ��� 
	DBMSG_RESPONSE_FAMILY_DEL_CHILDREN,					//[����]

	DBMSG_REQUEST_GET_FAMILYINFO,						//[����] ���� �ý��� : ���������� ��û�Ѵ�
	DBMSG_RESPONSE_GET_FAMILYINFO,						//[����]

	DBMSG_REQUEST_SETBALANCECANUSECURRENCY,				//[��ȣ] ��ȭ�� ���� - ��밡�� �ݾ� ����
	DBMSG_RESPONSE_SETBALANCECANUSECURRENCY,			//[��ȣ]

	DBMSG_REQUEST_GETBALANCECANUSECURRENCY,				//[��ȣ] ��ȭ�� ���� - ��밡�� �ݾ� ��������
	DBMSG_RESPONSE_GETBALANCECANUSECURRENCY,			//[��ȣ]

	DBMSG_REQUEST_SOULGUARD_CREATE,						//[����] ��ȣ���� : ��ȣ���� �����ϱ�
	DBMSG_RESPONSE_SOULGUARD_CREATE,					//[����]

	DBMSG_REQUEST_SOULGUARD_GET,						//[����] ��ȣ���� : ĳ���Ϳ� �ִ� ��ȣ���� ��������
	DBMSG_RESPONSE_SOULGUARD_GET,						//[����]

	DBMSG_REQUEST_SOULGUARD_FELLOWSHIP_SET,				//[����] ��ȣ���� : ĳ���Ϳ� �ִ� ��ȣ������ ģȭ�� ����
	DBMSG_RESPONSE_SOULGUARD_FELLOWSHIP_SET,			//[����]

	DBMSG_REQUEST_SOULGUARD_CHANGE_NAME,				//[����] ��ȣ���� : ĳ���Ϳ� �ִ� ��ȣ������ �̸� ����
	DBMSG_RESPONSE_SOULGUARD_CHANGE_NAME,				//[����]

	DBMSG_REQUEST_SOULGUARD_DEAD,						//[����] ��ȣ���� : ĳ���Ϳ� �ִ� ��ȣ������ ������ ���ؼ� �״´�
	DBMSG_RESPONSE_SOULGUARD_DEAD,						//[����]

	DBMSG_REQUEST_FAMILY_PLUS_ADD_DATE,					//[����] ���� �ý��� : ���� ȿ�� ����
	DBMSG_RESPONSE_FAMILY_PLUS_ADD_DATE,				//[����]

	DBMSG_REQUEST_FAMILY_SET_COOKIE_EFFECT,				//[����] ���� �ý��� : ��Ű�� ����ߴ�. ��Ű ȿ���� ��´�.
	DBMSG_RESPONSE_FAMILY_SET_COOKIE_EFFECT,			//[����]

	DBMSG_REQUEST_SOULGUARD_HOUSE_GET,					//[����] ��ȣ���� : ������ ������ ���´�
	DBMSG_RESPONSE_SOULGUARD_HOUSE_GET,					//[����]

	DBMSG_REQUEST_SOULGUARD_HOUSE_CHANGE,				//[����] ��ȣ���� : �����ҿ� �ִ� ��ȣ���ɰ� ĳ���Ϳ� �ִ� ��ȣ������ �±�ȯ��
	DBMSG_RESPONSE_SOULGUARD_HOUSE_CHANGE,				//[����]

	DBMSG_REQUEST_SOULGUARD_HOUSE_CREATE,				//[����] ��ȣ���� : �����ҿ� ���� ������ �ø�
	DBMSG_RESPONSE_SOULGUARD_HOUSE_CREATE,				//[����]

	DBMSG_REQUEST_DORMANCY_POINTITEM_BUY,				//[����] �޸���� :  ����Ʈ ������ ����
	DBMSG_RESPONSE_DORMANCY_POINTITEM_BUY,				//[����]  

	DBMSG_REQUEST_DORMANCY_POINTINFO_SET,				//[����] �޸���� :  ����Ʈ ���� ���� ����
	DBMSG_RESPONSE_DORMANCY_POINTINFO_SET,				//[����]  

	DBMSG_REQUEST_DORMANCY_STATE_CHANGE,				//[����] �޸���� :  �޸� ���� ����
	DBMSG_RESPONSE_DORMANCY_STATE_CHANGE,				//[����] 

	DBMSG_REQUEST_PERSONSLOTNUMCHANGE,					//[����] ĳ���� �����ҿ��� ĳ���͸� �����´� 
	DBMSG_RESPONSE_PERSONSLOTNUMCHANGE,					//[����] 

	DBMSG_REQUEST_GOONZURACCOONEVENT_SETINFO,			//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����	-	 �����͸� ���� �Ѵ� 
	DBMSG_RESPONSE_GOONZURACCOONEVENT_SETINFO,			//[����] 

	DBMSG_REQUEST_GOONZURACCOONEVENT_GETINFO,			//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����	-	 �����͸� ������ �´� 
	DBMSG_RESPONSE_GOONZURACCOONEVENT_GETINFO,			//[����] 

	DBMSG_REQUEST_SKILLBOOK_MAGIC_ADD,
	DBMSG_RESPONSE_SKILLBOOK_MAGIC_ADD,

	DBMSG_REQUEST_SKILLBOOK_MAGIC_DEL,
	DBMSG_RESPONSE_SKILLBOOK_MAGIC_DEL,

	DBMSG_REQUEST_SKILLBOOK_MAGICINFO_GET,
	DBMSG_RESPONSE_SKILLBOOK_MAGICINFO_GET,

	DBMSG_REQUEST_SKILLBOOK_SUBMAGIC_ADD,
	DBMSG_RESPONSE_SKILLBOOK_SUBMAGIC_ADD,

	DBMSG_REQUEST_SKILLBOOK_SUBMAGIC_DEL,
	DBMSG_RESPONSE_SKILLBOOK_SUBMAGIC_DEL,

	DBMSG_REQUEST_WARP_TARGETWORLD,						//[����] Ƽ���� �̿��Ͽ� ��ǥ �������� �ٷ� ���󰣴�
	DBMSG_RESPONSE_WARP_TARGETWORLD,

	DBMSG_REQUEST_CONTRIBUTION_ITEM_LIST_INPUT,			//[����] ��� �� �������� �߰� ����Ѵ�.
	DBMSG_RESPONSE_CONTRIBUTION_ITEM_LIST_INPUT,

	DBMSG_REQUEST_CONTRIBUTION_ITEM_LIST_DELETE,		//[����] ��� �� �������� �߰� ����Ѵ�.
	DBMSG_RESPONSE_CONTRIBUTION_ITEM_LIST_DELETE,

	DBMSG_REQUEST_CONTRIBUTION_MAKE_NPC,
	DBMSG_RESPONSE_CONTRIBUTION_MAKE_NPC,

	DBMSG_REQUEST_GOONZUDAYMISSIONINFO_SET,				// [����] ���ֵ��̹̼� : �̼� �ο� ������ ��� ����
	DBMSG_REQUEST_GOONZUDAYMISSIONINFO_GET,				// [����] ���ֵ��̹̼� : �̼� �ο� ������ ��� ��û
	DBMSG_RESPONSE_GOONZUDAYMISSIONINFO_GET,			// [����] ���ֵ��̹̼� : ��񿡼� �̼� �ο� ������ ������ �뺸

	//=======================================================================


	DBMSG_END
};

#define HOUSERECALL_REASON_FEEDELAY			1	// ��ü�� ���� ȸ�� .
#define HOUSERECALL_REASON_CONTRACTEND		2	// ��� ����� ���� ȸ��. 
#define HOUSERECALL_REASON_CANCELLATION		3	// ������ ��û���� ���� �Ӵ� ���.

//-----------------------------------------
// ���� �ǹ� ������ ��û�Ѵ�.
//-----------------------------------------
class sDBRequest_GetStructureInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// Where
	SI32				siVillageUnique;			// ����� �Ǵ� ����. 


	sDBRequest_GetStructureInfo(SI32 id, SI32 villageunique)
	{
		packetHeader.usSize = sizeof( sDBRequest_GetStructureInfo );
		packetHeader.usCmd = DBMSG_REQUEST_GETSTRUCTUREINFO;
		usCharID		= id;

		siVillageUnique		= villageunique;
	}
};

class sDBResponse_GetStructureInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// result
	SI32				siResult;			// �����.

	// where
	SI32				siVillageUnique;

	// info
	SI16 siVillageStructureInfo[MAX_CONSTRUCTION_NUM];


	sDBResponse_GetStructureInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetStructureInfo));
	}
};





//-----------------------------------------
// Person�� �ź��� ���´�. 
//-----------------------------------------
class sDBRequest_RankInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// who
	SI32				siPersonID;

	sDBRequest_RankInfo()
	{
		ZeroMemory(this, sizeof(sDBRequest_RankInfo));
	}
	sDBRequest_RankInfo(SI32 charid, SI32 personid)
	{
		ZeroMemory(this, sizeof(sDBRequest_RankInfo));
		packetHeader.usSize = sizeof( sDBRequest_RankInfo );
		packetHeader.usCmd = DBMSG_REQUEST_RANKINFO;

		usCharID	= charid;
		siPersonID	= personid;
	}
};

class sDBResponse_RankInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;					// �����.

	cltRank				clRank;						// �ź������� ���� ����. 				

	sDBResponse_RankInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_RankInfo));
	}
};


//-----------------------------------------
// �������� �ź� ������ ���� ���� ��û�Ѵ�. 
//-----------------------------------------
class sDBRequest_ManyRank
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_ManyRank()
	{
		ZeroMemory(this, sizeof(sDBRequest_ManyRank));
		packetHeader.usSize = sizeof( sDBRequest_ManyRank );
		packetHeader.usCmd = DBMSG_REQUEST_MANYRANK;
	}
};

#define GET_MANY_RANK_NUM	20
class sDBResponse_ManyRank
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;					// �����.

	cltRank				clRank[GET_MANY_RANK_NUM];	// �ź������� ���� ����. 				

	sDBResponse_ManyRank()
	{
		ZeroMemory(this, sizeof(sDBResponse_ManyRank));
	}
};



//-----------------------------------------
// ���� ������ ����Ʈ�� ���´�. 
//-----------------------------------------
class sDBRequest_InvestList
{
public:
	sPacketHeader		packetHeader;

	SI32				siVillageUnique;		// ����� �Ǵ� ������ VillageUnique

	sDBRequest_InvestList()
	{
		ZeroMemory(this, sizeof(sDBRequest_InvestList));
	}

	sDBRequest_InvestList(SI32 villageunique)
	{
		packetHeader.usSize = sizeof( sDBRequest_InvestList );
		packetHeader.usCmd = DBMSG_REQUEST_INVESTLIST;

		siVillageUnique	= villageunique;

	}
};


class sDBResponse_InvestList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	cltVillageInvestInfo	clInvestList;	// ������ ����Ʈ�� ������. (�ش� ������ VillageUnique�� �� �ȿ� �־�� �Ѵ�.) 

	sDBResponse_InvestList()
	{
		ZeroMemory(this, sizeof(sDBResponse_InvestList));
	}
};





//-----------------------------------------------------
// ������ DB�� �����Ѵ�. 
//-----------------------------------------------------
class sDBRequest_PushLetter
{
public:
	sPacketHeader		packetHeader;

	// who
	SI32				siPersonID;			// ������ ���� ���. 

	cltLetterUnit		clLetterUnit;		// ���� ����. 

	sDBRequest_PushLetter()
	{
		ZeroMemory(this, sizeof(sDBRequest_PushLetter));
	}

	sDBRequest_PushLetter(SI32 personid, cltLetterUnit* pclletter)
	{
		packetHeader.usSize = sizeof( sDBRequest_PushLetter );
		packetHeader.usCmd	= DBMSG_REQUEST_PUSHLETTER;

		siPersonID		= personid;

		clLetterUnit.Set(pclletter);
	}
};


class sDBResponse_PushLetter
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	SI32				siPersonID;			// ������ ���� ���. 

	SI32				siLetterNum;		// ������ ������ ����. 


	sDBResponse_PushLetter()
	{
		ZeroMemory(this, sizeof(sDBResponse_PushLetter));
	}
};



//-----------------------------------------------------
// ������ DB���� �����´�. 
//-----------------------------------------------------
class sDBRequest_PopLetter
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// who
	SI32				siPersonID;			// ������ ���� ���. 

	sDBRequest_PopLetter()
	{
		ZeroMemory(this, sizeof(sDBRequest_PopLetter));
	}

	sDBRequest_PopLetter(SI32 id, SI32 personid)
	{
		packetHeader.usSize = sizeof( sDBRequest_PopLetter );
		packetHeader.usCmd	= DBMSG_REQUEST_POPLETTER;

		usCharID		= id;
		siPersonID		= personid;

	}
};


class sDBResponse_PopLetter
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siPersonID;			// ������ ���� ���. 

	cltLetterUnit		clLetterUnit;		// ���� ����. 

	sDBResponse_PopLetter()
	{
		ZeroMemory(this, sizeof(sDBResponse_PopLetter));
	}
};


//-----------------------------------------------------
// Ư�� ������ ������� ������ DB�� �����Ѵ�. 
//-----------------------------------------------------
class sDBRequest_PushAccountLetter
{
public:
	sPacketHeader		packetHeader;

	// who
	TCHAR				szAccountID[MAX_PLAYER_NAME];			// ������ ���� ����. 

	cltAccountLetterUnit		clLetterUnit;		// ���� ����. 

	sDBRequest_PushAccountLetter()
	{
		ZeroMemory(this, sizeof(sDBRequest_PushAccountLetter));
	}

	sDBRequest_PushAccountLetter(TCHAR * AccountID, cltAccountLetterUnit* pclletter)
	{
		packetHeader.usSize = sizeof( sDBRequest_PushAccountLetter );
		packetHeader.usCmd	= DBMSG_REQUEST_PUSHACCOUNTLETTER;

		MStrCpy(szAccountID, AccountID ,MAX_PLAYER_NAME);

		clLetterUnit.Set(pclletter);
	}
};


class sDBResponse_PushAccountLetter
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	TCHAR				szAccountID[MAX_PLAYER_NAME];			// ������ ���� ����. 

	SI32				siLetterNum;		// ������ ������ ����. 


	sDBResponse_PushAccountLetter()
	{
		ZeroMemory(this, sizeof(sDBResponse_PushAccountLetter));
	}
};


//-----------------------------------------------------
// ������ ������� �� ������ DB���� �����´�. 
//-----------------------------------------------------
class sDBRequest_PopAccountLetter
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// who
	TCHAR				szAccountID[MAX_PLAYER_NAME];			// ������ ���� ���. 

	sDBRequest_PopAccountLetter()
	{
		ZeroMemory(this, sizeof(sDBRequest_PopAccountLetter));
	}

	sDBRequest_PopAccountLetter(SI32 id ,TCHAR*	AccountID)
	{
		packetHeader.usSize = sizeof( sDBRequest_PopAccountLetter );
		packetHeader.usCmd	= DBMSG_REQUEST_POPACCOUNTLETTER;

		MStrCpy(szAccountID, AccountID ,MAX_PLAYER_NAME);

		usCharID		= id;	
	}
};


class sDBResponse_PopAccountLetter
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	TCHAR				szAccountID[MAX_PLAYER_NAME];			// ������ ���� ����. 

	cltAccountLetterUnit		clLetterUnit;		// ���� ����. 

	sDBResponse_PopAccountLetter()
	{
		ZeroMemory(this, sizeof(sDBResponse_PopAccountLetter));
	}
};


//------------------------------------------
// ������ ���θ� ��û�Ѵ� 
//------------------------------------------
class sDBRequest_PayFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;	

	SI32				siPersonID;					// ������

	SI32				siVillageUnique;			// �ǹ��� ��ġ�� ���� VillageUnique
	SI32				siStrType;					// �ǹ��� Ÿ��. 

	SI32				siFeeType;					// ������ Ÿ��
	cltMoney			clFeeMoney;					// ������


	sDBRequest_PayFee( SI32 id, SI32 personID, SI32 villageUnique, SI32 strType, SI32 feeType, cltMoney *pclMoney )
	{

		packetHeader.usSize = sizeof( sDBRequest_PayFee );
		packetHeader.usCmd = DBMSG_REQUEST_PAYFEE;
		usCharID		= id;

		siPersonID		= personID;

		siVillageUnique	= villageUnique;
		siStrType		= strType;

		siFeeType		= feeType;
		clFeeMoney.Set( pclMoney );

	}

};


//------------------------------------------
// ������ ���� ��û�� �����Ѵ�
//------------------------------------------
class sDBResponse_PayFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;	

	SI32				siResult;					// ���: 1���� 0����

	SI32				siPersonID;					// ������

	SI32				siVillageUnique;			// �ǹ��� ��ġ�� ���� VillageUnique
	SI32				siStrType;					// �ǹ��� Ÿ��. 

	SI32				siFeeType;					// ������ Ÿ��
	cltMoney			clFeeMoney;					// ������

	cltMoney			clPersonMoney;				// �������� ���� �ܾ�
	cltMoney			clStructureMoney;			// �ǹ��� �����ڱ�


	sDBResponse_PayFee()
	{
		ZeroMemory( this, sizeof( sDBResponse_PayFee ) );
	}

};

//------------------------------------------
// �θ� ������ �����Ѵ� 
//------------------------------------------
class sDBRequest_SetParentVillage
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;			// ���� ����ũ
	SI32				siParentVillage;			// �θ� ����
	SI32				siMasterVillage;			// �ְ� �θ� ���� 

	sDBRequest_SetParentVillage( SI32 villageUnique, SI32 parentVillage, SI32 masterVillage )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetParentVillage );
		packetHeader.usCmd = DBMSG_REQUEST_SETPARENTVILLAGE;

		siVillageUnique = villageUnique;

		siParentVillage = parentVillage;
		siMasterVillage = masterVillage;
	}

};

class sDBResponse_SetParentVillage
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;					// 1:���� 0:����

	SI32				siVillageUnique;			// ���� ����ũ 
	SI32				siParentVillage;			// �θ� ����
	SI32				siMasterVillage;			// �ְ� �θ� ���� 

	sDBResponse_SetParentVillage()
	{
		ZeroMemory( this, sizeof( sDBResponse_SetParentVillage ) );
	}


};


//------------------------------------------
// �������� �����Ѵ� 
//------------------------------------------
class sDBRequest_DeclareWar
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	SI32				siTargetVillage;
	//	cltDate				clDate;
	NDate				clDate;

	sDBRequest_DeclareWar( UI16 id, SI32 villageUnique, SI32 targetVillage, NDate *pclDate )
	{
		packetHeader.usSize = sizeof( sDBRequest_DeclareWar );
		packetHeader.usCmd = DBMSG_REQUEST_DECLAREWAR;

		usCharID = id;
		siVillageUnique = villageUnique;
		siTargetVillage = targetVillage;
		clDate.Set( pclDate );
	}

};

class sDBResponse_DeclareWar
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;
	SI32				siTargetVillage;
	NDate				clDate;

	sDBResponse_DeclareWar()
	{
		ZeroMemory( this, sizeof( sDBResponse_DeclareWar ) );
	}

};

//---------------------------------------------------
// ���� ���� ����Ѵ� 
//---------------------------------------------------
class sDBRequest_CancelDeclareWar
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	SI32				siTargetVillage;
	NDate				clDate;

	sDBRequest_CancelDeclareWar( UI16 id, SI32 villageUnique, SI32 targetVillage, NDate *pclDate  )
	{
		packetHeader.usCmd = DBMSG_REQUEST_CANCELDECLAREWAR;
		packetHeader.usSize = sizeof( sDBRequest_CancelDeclareWar );

		usCharID = id;
		siVillageUnique = villageUnique;
		siTargetVillage = targetVillage;
		clDate.Set( pclDate );
	}
};

class sDBResponse_CancelDeclareWar
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;
	SI32				siTargetVillage;
	NDate				clDate;

	sDBResponse_CancelDeclareWar()
	{
		ZeroMemory( this, sizeof( sDBResponse_CancelDeclareWar ) );
	}
};

//---------------------------------------------------
// ������ �������� ���� �� �θ� ���� ������ ��û�Ѵ�  
//---------------------------------------------------
class sDBRequest_GetVillageInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;

	sDBRequest_GetVillageInfo( SI32 villageUnique )
	{
		packetHeader.usSize = sizeof( sDBRequest_GetVillageInfo );
		packetHeader.usCmd = DBMSG_REQUEST_GETVILLAGEINFO;

		siVillageUnique = villageUnique;
	}

};


class sDBResponse_GetVillageInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;

	SI32				siMasterVillage;
	SI32				siParentVillage;

	SI32				siVillageMark;
	SI32				siTotalVillageScore;
	SI32				siNewYearEventScore;

	bool				m_bGeneralMeetingSuggest;	//[�߰� : Ȳ���� 2008. 2. 21 => ������ȸ �ߵ� �÷���, ��� ��ɾ�� ���� ����.]

	sDBResponse_GetVillageInfo()
	{
		ZeroMemory( this, sizeof( sDBResponse_GetVillageInfo ) );
	}
};


class sDBRequest_SetVillageWarLoss
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	SI32				siWinVillage;

	SI32				siLossStockAmount;
	SI32				siLossPersent;

	sDBRequest_SetVillageWarLoss( SI32 villageunique, SI32 winvillage, SI32 lossStockAmount, SI32 lossPersent )
	{
		packetHeader.usCmd = DBMSG_REQUEST_SETVILLAGEWARLOSS;
		packetHeader.usSize = sizeof( sDBRequest_SetVillageWarLoss );

		siVillageUnique = villageunique;
		siWinVillage = winvillage;

		siLossStockAmount = lossStockAmount;
		siLossPersent = lossPersent;
	}
};

class sDBResponse_SetVillageWarLoss
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;									// ��������ũ 
	SI32				siWinVillage;										// �¸� ���� 

	SI32				siTotalVillageStockAmount;							// �Ұ� �� ���� �� �ֽ� ���� 
	SI32				siTotalLossStockAmount;								// �Ұ� �� �ֽ� ���� 

	SI32				siLossPersent;										// �ֽ� �Ұ� ����

	UI16				usCount;											// �Ұ� �ֽ� ���� ���� 

	SI32				siStockHolderPersonID[ 30 ];						// �Ұ� �ֽ� ������ personid
	SI32				siStockAmount[ 30 ];								// �Ұ� �ֽ� ������ �Ұ��� �ֽ� ���� 

	sDBResponse_SetVillageWarLoss()
	{
		ZeroMemory( this, sizeof( sDBResponse_SetVillageWarLoss ) );
	}

};

class sDBRequest_SetVillageMark
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	SI32				siVillageMark;

	cltDate				clDate;

	sDBRequest_SetVillageMark( UI16 id, SI32 villageunique, SI32 villagemark, cltDate *pclDate )
	{
		packetHeader.usCmd = DBMSG_REQUEST_SETVILLAGEMARK;
		packetHeader.usSize = sizeof( sDBRequest_SetVillageMark );

		usCharID = id;

		siVillageUnique = villageunique;
		siVillageMark = villagemark;
		clDate.Set( pclDate );
	}


};

class sDBResponse_SetVillageMark
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;
	SI32				siVillageMark;

	sDBResponse_SetVillageMark()
	{
		ZeroMemory( this, sizeof( sDBResponse_SetVillageMark ) );
	}

};

class DBStructMaterialInfo{
public:
	SI16 siStgPos;		// â�� ��ġ. 
	SI16 siItemUnique;	// ��� �������� ����ũ 
	SI16 siUseItemNum;	// ���Ǵ� �������� ����. 
	SI16 siNeedNum;		// ä���� �ϴ� ��ü ����

	DBStructMaterialInfo()
	{
		Init();
	}
	void Init()
	{
		siStgPos		= 0;
		siItemUnique	= 0;
		siUseItemNum	= 0;
		siNeedNum		= 0;
	}

	void Set(DBStructMaterialInfo* pclinfo)
	{
		siStgPos		= pclinfo->siStgPos;
		siItemUnique	= pclinfo->siItemUnique;
		siUseItemNum	= pclinfo->siUseItemNum;
		siNeedNum		= pclinfo->siNeedNum;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_Event_InsertMaterial
//
// Last Modified 	: 2007 / 11 / 21
// Created		 	: �̰���
//
// Function			: [���� -> DB�Ŵ���] ����� �̺�Ʈ ��� �ֱ�
//
//***************************************************************************************************
class sDBRequest_Event_InsertMaterial
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	// Person
	SI32				m_siPersonID;			// ��Ḧ �ִ� ���

	SI32				m_siVillageUnique;		// ���� ����ũ
	SI16				m_siConstructType;		// ����� �� �ĺ���	( >= 1000�� ���ο�), EVENT_STRUCTURE_HERO_BRONZE...

	// DBStructMaterialInfo 
	DBStructMaterialInfo	m_clMaterial[MAX_MATERIAL_NUMBER];

	sDBRequest_Event_InsertMaterial(UI16 charid, SI32 personid, SI32 villageunique, SI16 constructtype, DBStructMaterialInfo* pMaterial)
	{
		m_packetHeader.usCmd = DBMSG_REQUEST_EVENT_INSERTMATERIAL;
		m_packetHeader.usSize = sizeof( sDBRequest_Event_InsertMaterial );

		m_usCharID			= charid;
		m_siPersonID		= personid;

		m_siVillageUnique	= villageunique;
		m_siConstructType	= constructtype;
		
		for(int i=0; i<MAX_MATERIAL_NUMBER; i++)		m_clMaterial[i].Init();

		if(pMaterial)
		{
			for(int i=0; i<MAX_MATERIAL_NUMBER; i++)		m_clMaterial[i].Set(&pMaterial[i]);
		}
	}
};

class sDBResponse_Event_InsertMaterial
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	// Person
	SI32				siPersonID;				// ��Ḧ �ִ� ���

	SI32				m_siVillageUnique;		// ���� ����ũ
	SI16				m_siConstructType;		// ����� �� �ĺ���	( >= 1000�� ���ο�)

	// DBStructMaterialInfo 
	DBStructMaterialInfo		clMaterial[MAX_MATERIAL_NUMBER];		// For LOG - request���� ����

	sDBResponse_Event_InsertMaterial()
	{
		ZeroMemory(this, sizeof(sDBResponse_Event_InsertMaterial));
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_Event_MaterialList
//
// Last Modified 	: 2007 / 11 / 21
// Created		 	: �̰���
//
// Function			: [���� -> DB�Ŵ���] ����� �̺�Ʈ ��� ���� ����
//
//***************************************************************************************************
class sDBRequest_Event_MaterialList
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	// Person
	SI32				m_siPersonID;			// ��û�� ���

	SI32				m_siVillageUnique;		// ���� ����ũ
	SI16				m_siConstructType;		// ����� �� �ĺ���	( >= 1000�� ���ο�)

	sDBRequest_Event_MaterialList(UI16 charid, SI32 personid, SI32 villageunique, SI16 constructtype)
	{
		m_packetHeader.usCmd = DBMSG_REQUEST_EVENT_MATERIALLIST;
		m_packetHeader.usSize = sizeof( sDBRequest_Event_MaterialList );

		m_usCharID			= charid;
		m_siPersonID		= personid;

		m_siVillageUnique	= villageunique;
		m_siConstructType	= constructtype;
	}
};

class sDBResponse_Event_MaterialList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	// Person
	SI32				siPersonID;				// ��û�� ��� 

	SI32				m_siVillageUnique;		// ���� ����ũ
	SI16				m_siConstructType;		// ����� �� �ĺ���	( >= 1000�� ���ο�)

	// Material 
	SI16				m_siItemUnique[MAX_MATERIAL_NUMBER];	// ���� ��� ����
	SI16				m_siItemNum[MAX_MATERIAL_NUMBER];		// ���� ��� ����

	sDBResponse_Event_MaterialList()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_Event_MaterialComplete
//
// Last Modified 	: 2007 / 11 / 21
// Created		 	: �̰���
//
// Function			: [���� -> DB�Ŵ���] ����� �̺�Ʈ �ϼ� ó��
//
//***************************************************************************************************
class sDBRequest_Event_MaterialComplete
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	// Person
	SI32				m_siPersonID;			// ��û�� ���

	SI32				m_siVillageUnique;		// ���� ����ũ
	SI16				m_siConstructType;		// ����� �� �ĺ���	( >= 1000�� ���ο�)

	SI16				m_siItemUnique[MAX_MATERIAL_NUMBER];	// �Ǽ� ��� ����
	SI16				m_siItemNum[MAX_MATERIAL_NUMBER];		// �Ǽ� ��� ����

	SI16				m_siOutputPos;				// �޴� ������ ��ġ�� ����. 
	cltItem				m_clItem;					// �޴� ������ ����. (���� ����. ) 
	bool				m_bCanPileSwitch;			// �޴� ������ ���������Ѱ� ?

	sDBRequest_Event_MaterialComplete(UI16 charid, SI32 personid, SI32 villageunique, SI16 constructtype, 
									  SI16* psiItemUnique, SI16* psiItemNum,
									  SI16 siOutPos, cltItem* pclItem, bool bCanPileSwitch )
	{
		m_packetHeader.usCmd = DBMSG_REQUEST_EVENT_MATERIALCOMPLETE;
		m_packetHeader.usSize = sizeof( sDBRequest_Event_MaterialComplete );

		m_usCharID			= charid;
		m_siPersonID		= personid;

		m_siVillageUnique	= villageunique;
		m_siConstructType	= constructtype;

		ZeroMemory(m_siItemUnique, sizeof(m_siItemUnique));
		if(psiItemUnique)
		{
			memcpy(m_siItemUnique, psiItemUnique, sizeof(m_siItemUnique));
		}

		ZeroMemory(m_siItemNum, sizeof(m_siItemNum));
		if(psiItemNum)
		{
			memcpy(m_siItemNum, psiItemNum, sizeof(m_siItemNum));
		}

		m_siOutputPos		= siOutPos;
		m_clItem.Set(pclItem);
		m_bCanPileSwitch	= bCanPileSwitch;
	}
};

class sDBResponse_Event_MaterialComplete
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	// Person
	SI32				siPersonID;				// ��û�� ��� 

	SI32				m_siVillageUnique;		// ���� ����ũ
	SI16				m_siConstructType;		// ����� �� �ĺ���	( >= 1000�� ���ο�)

	SI16				siOutputPos;			// �޴� ������ ��ġ�� ����. 
	SI16				siAddedNum;				// �߰��� ������ ����. 
	cltItem				clItem;					// �޴� ������ ����. (���� ����. ) 

	sDBResponse_Event_MaterialComplete()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

class sDBRequest_DBInitComplete
{
public:
	sPacketHeader		packetHeader;
	SI32				siSelect;
	SI16				siStep;

	sDBRequest_DBInitComplete( SI32 select, SI16 step )
	{
		packetHeader.usCmd = DBMSG_REQUEST_DBINITCOMPLETE;
		packetHeader.usSize = sizeof( sDBRequest_DBInitComplete );

		siSelect	= select;
		siStep		= step;
	}
};


class sDBResponse_DBInitComplete
{
public:
	sPacketHeader		packetHeader;
	SI32				siSelect;
	SI16				siStep;

	sDBResponse_DBInitComplete( SI32 select, SI16 step )
	{
		packetHeader.usCmd = DBMSG_RESPONSE_DBINITCOMPLETE;
		packetHeader.usSize = sizeof( sDBResponse_DBInitComplete );

		siSelect	= select;
		siStep		= step;
	}
};

class sDBRequest_WriteLog
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI32				siDestPersonID;

	SI32				siItemUnique;

	TCHAR				szCmd[ 50 ];

	UI16				usStrSize;
	TCHAR				szStr[ 256 ];

	sDBRequest_WriteLog( SI32 personid, SI32 destPersonid, SI32 itemunique, TCHAR *cmd, TCHAR *str )
	{

		packetHeader.usCmd = DBMSG_REQUEST_WRITELOG;

		StringCchCopy( szCmd, 50, cmd );
		StringCchCopy( szStr, 256, str );

		usStrSize = _tcslen( szStr ) + 1;

		siPersonID = personid;
		siDestPersonID = destPersonid;

		siItemUnique = itemunique;

		packetHeader.usSize = sizeof( packetHeader ) + 50 + 22 + usStrSize;
	}

};

class sDBResponse_WriteLog
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	sDBResponse_WriteLog()
	{
		ZeroMemory( this, sizeof( sDBResponse_WriteLog ) );
	}

};

// �α׷� �ű�
// LEEKH - 0831 - ���Ǻ� ����Ʈ �߰�. �̺�Ʈ ���� ������ DB�� ���� ���� ���θ�Ȯ���Ѵ�.
class sDBRequest_Log_SetHappyBeanClearInfo
{
public:
	sPacketHeader		packetHeader;

	TCHAR				szServerName[50];
	TCHAR				szAccountID[MAX_PLAYER_NAME];
	TCHAR				szCharName[MAX_PLAYER_NAME];
	SI32				siPersonID;
	SI32				siQuestType; // QUEST_TYPE_HAPPYBEAN
	SI32				siQuestState; // QUEST_HAPPYBEAN_STEP_NON, QUEST_HAPPYBEAN_STEP_START, QUEST_HAPPYBEAN_STEP_COMPLETE

	sDBRequest_Log_SetHappyBeanClearInfo(TCHAR* servername, TCHAR* accountid, TCHAR* charname, SI32 personid, SI32 questtype, SI32 QuestState )
	{
		packetHeader.usSize = sizeof( sDBRequest_Log_SetHappyBeanClearInfo );
		packetHeader.usCmd	= DBMSG_REQUEST_LOG_GETHAPPYBEANQUESTINFO;

		szServerName[0] = '\0';
		szAccountID[0] = '\0';
		szCharName[0] = '\0';

		if(servername)		StringCchCopy(szServerName, sizeof(szServerName), servername);
		if(accountid)		StringCchCopy(szAccountID, sizeof(szAccountID), accountid);
		if(charname)		StringCchCopy(szCharName, sizeof(szCharName), charname);

		siPersonID	= personid;
		siQuestType = questtype;
		siQuestState = QuestState;
	}
};

// �α׷� �ű�
// LEEKH - 0831 - ���Ǻ� ����Ʈ �߰�. �̺�Ʈ ������� ������ DB�� ���� ���� �޾� Ȯ���Ѵ�.
class sDBResponse_Log_GetHappyBeanClearInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siQuestType; // QUEST_TYPE_HAPPYBEAN
	SI32				siQuest_StartCount; //  QUEST_HAPPYBEAN_STEP_START �� ī����. �ʱ�ȭ ��Ű�� ����.
	SI32				siQuest_CompleteCount; //  QUEST_HAPPYBEAN_STEP_COMPLETE �� ī����. 1�Ͽ� �ѹ� �ʱ�ȭ.

	//	SI32				siResult;			// �����. 0 = ����Ʈ ����. 1= ����Ʈ ���� �㰡. 2= ����Ʈ �Ϸᰡ ���������� ���� �Ǿ���.


	sDBResponse_Log_GetHappyBeanClearInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_Log_GetHappyBeanClearInfo));
	}
};


// �α׷� �ű�
// KHY - 0906 -  �̺�Ʈ ���� ������ DB�� ���� ���� ���θ�Ȯ���Ѵ�.
class sDBRequest_Log_SetEventCouponInfo
{
public:
	sPacketHeader		packetHeader;

	TCHAR				szServerName[50];
	TCHAR				szAccountID[MAX_PLAYER_NAME];
	TCHAR				szCharName[MAX_PLAYER_NAME];
	SI32				siPersonID;
	SI32				siEventType; //GAMEROOM_COUPON_EVENT = 1, AUCTION_COUPON_EVENT = 2 ,GOSTOP_POKER_EVENT = 4, HAN_GAME_VIP_EVENT = 5,
	SI32 			siPara; //�߰� �ʿ� ������. 0 = ����. 1 �̻� ���ʹ� �� �̺�Ʈ���� ���� ����. 

	//HAN_GAME_VIP_EVENT (5) : siPara = 1  //ù��°�� ������� ĳ������.
	//						    siPara = 2  //5���� �޼� �̺�Ʈ Ŭ����.

	//NOW_COM_EVENT (6) 	:   siPara = 1  //�ű� ĳ���� ù ����.
	//						    siPara = 2  //10���� �޼� �̺�Ʈ Ŭ����.
	//						    siPara = 3  //������ ������. = ���ڰ� �Ǿ���.



	sDBRequest_Log_SetEventCouponInfo(TCHAR* servername, TCHAR* accountid, TCHAR* charname, SI32 personid, SI32 eventtype , SI32 para)
	{
		packetHeader.usSize = sizeof( sDBRequest_Log_SetHappyBeanClearInfo );
		packetHeader.usCmd	= DBMSG_REQUEST_LOG_GETEVENTCOUPONINFO;

		szServerName[0] = '\0';
		szAccountID[0] = '\0';
		szCharName[0] = '\0';

		if(servername)		StringCchCopy(szServerName, sizeof(szServerName), servername);
		if(accountid)		StringCchCopy(szAccountID, sizeof(szAccountID), accountid);
		if(charname)		StringCchCopy(szCharName, sizeof(szCharName), charname);

		siPersonID	= personid;
		siEventType = eventtype;
		siPara	= para;
	}
};

////���� �̺�Ʈ �̺�Ʈ ���� ������ DB�� ���� ���� ���� Ȯ��.
//class sDBRequest_Log_SetAUCTIONEventCouponInfo
//{
//public:
//	sPacketHeader		packetHeader;
//
//	TCHAR				szServerName[50];
//	TCHAR				szAccountID[MAX_PLAYER_NAME];
//	TCHAR				szCharName[MAX_PLAYER_NAME];
//	SI32				siPersonID;
//	SI32				siEventType; //GAMEROOM_COUPON_EVENT = 1,
//
//	sDBRequest_Log_SetAUCTIONEventCouponInfo(TCHAR* servername, TCHAR* accountid, TCHAR* charname, SI32 personid, SI32 eventtype )
//	{
//		packetHeader.usSize = sizeof( sDBRequest_Log_SetHappyBeanClearInfo );
//		packetHeader.usCmd	= DBMSG_REQUEST_LOG_GETEVENTCOUPONINFO;
//
//		szServerName[0] = '\0';
//		szAccountID[0] = '\0';
//		szCharName[0] = '\0';
//
//		if(servername)		StringCchCopy(szServerName, sizeof(szServerName), servername);
//		if(accountid)		StringCchCopy(szAccountID, sizeof(szAccountID), accountid);
//		if(charname)		StringCchCopy(szCharName, sizeof(szCharName), charname);
//
//		siPersonID	= personid;
//		siEventType = eventtype;
//	}
//};

// �α׷� �ű�
// KHY - 0906 - �̺�Ʈ ������� ������ DB�� ���� ���� �޾� Ȯ���Ѵ�.
class sDBResponse_Log_GetEventCouponInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siEventType; //GAMEROOM_COUPON_EVENT = 1,

	SI32				siResult;// �����. 0 =����. 1= ����.


	sDBResponse_Log_GetEventCouponInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_Log_GetEventCouponInfo));
	}
};
////���� �̺�Ʈ [2007.09.10 �ռ���]
//class sDBResponse_Log_GetAUCTIONEventCouponInfo
//{
//public:
//	sPacketHeader		packetHeader;
//
//	SI32				siPersonID;
//	SI32				siEventType; //AUCTION_CUPON_EVENT
//
//	SI32				siResult;// �����. 0 =����. 1~10���� ���� ����.
//
//
//	sDBResponse_Log_GetAUCTIONEventCouponInfo()
//	{
//		ZeroMemory(this, sizeof(sDBResponse_Log_GetEventCouponInfo));
//	}
//};


#define NEWLOG_USE_ITEM			0x00000001
#define NEWLOG_USE_SUMMON		0x00000002
#define NEWLOG_USE_HEALTHINFO	0x00000004
#define NEWLOG_USE_SIPARAM1		0x00000008
#define NEWLOG_USE_SIPARAM2		0x00000010
#define NEWLOG_USE_SIPARAM3		0x00000020
#define NEWLOG_USE_SIPARAM4		0x00000040
#define NEWLOG_USE_SIPARAM5		0x00000080
#define NEWLOG_USE_CHARPARAM1	0x00000100
#define NEWLOG_USE_CHARPARAM2	0x00000200

class sDBRequest_WriteLogToDB
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;
    
	SI32				m_siUseLog;
	TCHAR				m_szServerName[50];

	//TCHAR				m_szDate[20];
	SYSTEMTIME			m_stTime;
	TCHAR				m_szIP[32];
	SI16				m_siCommandType;
	SI16				m_siCommandIndex;
	UI08				m_uiReason;
    SI32				m_siIDNum;
	TCHAR				m_szPersonName[MAX_PLAYER_NAME];
	SI32				m_siPersonID;
	SI32				m_siLevel;
	SI64				m_siExp;// sI32-> Si64 �� �����ϸ鼭 ������ ������ ���� ��������
	GMONEY				m_siMoney;
	GMONEY				m_siMoneySum;
	cltItem				m_clItem;
	SI32				m_siItemSum;
	cltSummon			m_clSummon;
	SI32				m_siMonKind;
	SI32				m_siTargetPersonID;
	SI32				m_siVillageUnique;
	SI16				m_siNpcKind;
	cltHealthInfo		m_clHealthInfo;
	SI32				m_siRPPoint;
	SI32				m_siFameExp;
	SI64				m_siParam1;
	SI64				m_siParam2;
	SI64				m_siParam3;
	SI64				m_siParam4;
	SI64				m_siParam5;
	TCHAR				m_szCharParam1[50];
	TCHAR				m_szCharParam2[50];

	sDBRequest_WriteLogToDB()
	{
		ZeroMemory( this, sizeof( sDBRequest_WriteLogToDB ) );

		m_packetHeader.usCmd = DBMSG_REQUEST_WRITELOGTODB;
		m_packetHeader.usSize = sizeof( sDBRequest_WriteLogToDB );
	}
};

class sDBResponse_WriteLogToDB
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	sDBResponse_WriteLogToDB()
	{
		ZeroMemory( this, sizeof( sDBResponse_WriteLogToDB ) );
	}

};


// PC�� ���� PC�� �̿� �α� 
class sDBRequest_PCRoom_Log

{
public:
	sPacketHeader		packetHeader;

	SI32				siServerID;
	char				szGameID[20];
	char				szAccountID[MAX_PLAYER_NAME];
	char				szCharName[MAX_PLAYER_NAME];
	_SYSTEMTIME			sTime_Login;
	_SYSTEMTIME			sTime_LogOut;	
	char				szIP[64];
	char				szCRMcode[16];
	SI32				siLevel_LogIn;
	SI32				siLevel_LogOut;
	SI32				siPlayMinute;
	GMONEY				siGameMoney;
	char				sPCRoomGrade;

	sDBRequest_PCRoom_Log( SI32 serverid , char * gameid ,
		char * accountid , char * charname, _SYSTEMTIME * time_login ,  
		_SYSTEMTIME * time_logout  , char * ip , char * crmcode , SI32 lv_login , SI32 lv_logout , 
		SI32 playminute , GMONEY gamemoney , char pcroomgrade )
	{

		packetHeader.usSize = sizeof( sDBRequest_PCRoom_Log );
		packetHeader.usCmd = DBMSG_REQUEST_WRITELOG_PCROOM;

		siServerID = serverid;
		MStrCpy( szGameID ,gameid , 20 );
		MStrCpy( szAccountID , accountid , MAX_PLAYER_NAME );
		MStrCpy( szCharName , charname , MAX_PLAYER_NAME );
		memcpy( &sTime_Login , time_login , sizeof(_SYSTEMTIME) );
		memcpy( &sTime_LogOut , time_logout , sizeof(_SYSTEMTIME) );
		MStrCpy( szIP , ip , 64 );
		MStrCpy( szCRMcode , crmcode , 16 );
		siLevel_LogIn = lv_login;
		siLevel_LogOut = lv_logout;
		siPlayMinute = playminute;
		siGameMoney = gamemoney;
		sPCRoomGrade = pcroomgrade;
	}
};


#endif
