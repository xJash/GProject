//---------------------------------
// 2003/6/9 ���°�
//---------------------------------
#ifndef _MSGTYPE_H
#define _MSGTYPE_H

#include "../NetworkLib/ITZNetLib/ITZBase.h"
#include "../../CommonLogic/Market/Market.h"

// ��Ŷ �����͸� ������ ����Ϸ��� ��
// ��> cltMsg clMsg( GAMEMSG_REQUEST_SKILLBOOK_BUYITEM, sizeof(clSkillBookBuyItem), (BYTE*)&clSkillBookBuyItem );
//     -> cltMsg clMsg( GAMEMSG_REQUEST_SKILLBOOK_BUYITEM, PACKET(clSkillBookBuyItem) );
#define PACKET(DATA) sizeof(DATA), (BYTE*)&DATA
#define PACKET_EMPTY NULL, NULL

// ������ Ŭ���̾�Ʈ���� �޽���. 
enum eGameNetworkMsg{

	//-------------------------------
	// �α��� 
	//-------------------------------
	GAMEMSG_RESPONSE_CLIENTCHARUNIQUE	= 1, //[�°�]
	GAMEMSG_REQUEST_LOGIN		,			//[�°�]
	GAMEMSG_RESPONSE_CHARLIST	,			//[�°�] ������ ĳ���� ����Ʈ�� Ŭ���̾�Ʈ���� ������. (ĳ���� ���� �и��ؼ� ������. )

	GAMEMSG_REQUEST_SELECTCHAR	,			//[�°�] ĳ���͸� �����Ѵٴ� �޽���. 
	GAMEMSG_RESPONSE_LOGIN		,			//[�°�]
	GAMEMSG_RESPONSE_LOGINMANY	,			//[�°�] ���� ĳ������ �α��� ������ ������. 

	GAMEMSG_REQUEST_MAKENEWCHAR	,			//[�°�] ���ο� ĳ���͸� ����ٴ� �޽���. 
	GAMEMSG_RESPONSE_MAKENEWCHAR,			//[�°�] ���ο� ĳ���͸� ���� Ŭ���̾�Ʈ�� �뺸. 	

	GAMEMSG_REQUEST_DELUSERCHAR	,			//[����] �ɸ��� ����.
	GAMEMSG_RESPONSE_DELUSERCHAR,			//[����]

	GAMEMSG_RESPONSE_LOGOUT		,			//[�°�]

	GAMEMSG_REQUEST_APEXDATA = 77,			//[����] APEX-
	GAMEMSG_RESPONSE_APEXDATA,				//[����] APEX-

	GAMEMSG_REQUEST_HANAUTH_LOGIN = 80,		//[����] NHN HANAUTH �α���
	GAMEMSG_REQUEST_TAIWAN_LOGIN,			//[����] TAIWAN �α���

	GAMEMSG_REQUEST_HANAUTH_GAMERUNAUTH,	//[����] NHN HANAUTH �α���

	GAMEMSG_REQUEST_PREDELUSERCHAR	,		//[����] �ɸ��� ���������޼���.
	GAMEMSG_RESPONSE_PREDELUSERCHAR,		//[����]

	GAMEMSG_REQUEST_PERSONSLOTNUMCHANGE,	//[����] ĳ���� �����ҿ��� �����´�


	//--------------------------------
	// �ý��� 
	//--------------------------------
	// �ý��� 
	GAMEMSG_REQUEST_HEARTBEAT		= 100,	//100[�°�] Ŭ���̾�Ʈ�� ��� �ִٴ� �޽���. 

	GAMEMSG_RESPONSE_USERNUM,				//101[�°�] ����/�ִ� ����� ���ڸ� �뺸. 		

	GAMEMSG_REQUEST_USERCHARINFO,			//102[�°�] GM�� ����� ĳ���Ϳ� ���� ������ ��û�Ѵ�. 
	GAMEMSG_RESPONSE_USERCHARINFO,			//103[�°�]

	GAMEMSG_REQUEST_ACCOUNTINFO,			//104[����] GM�� ����� ������ ���� ������ ��û�Ѵ�.
	GAMEMSG_RESPONSE_ACCOUNTINFO,			//105[����]

	GAMEMSG_RESPONSE_SERVERINFO,			//106[�°�] ������ �Ϲ����� �������� �뺸  

	GAMEMSG_REQUEST_HOPETOQUIT,				//107[�°�] ���Ḧ �����. 
	GAMEMSG_RESPONSE_HOPETOQUIT,			//108[�ؿ�] ���� ����� ���� ����

	GAMEMSG_REQUEST_HOPETOFRONT,				//109[�ؿ�] ����Ʈ�� �ǵ��ư��⸦ ���Ѵ�.
	GAMEMSG_RESPONSE_HOPETOFRONT,				//110

	GAMEMSG_RESPONSE_SERVEREVENTINFO,			//111[�°�] ���� �̺�Ʈ ������ ������. 

	// ���� 
	GAMEMSG_RESPONSE_NOTICE		,				//112[�°�] �����˸�. 
	GAMEMSG_RESPONSE_NOTICELOGIN,				//113[�°�] �α��ν� ����. 
	GAMEMSG_RESPONSE_GIFTNT,					//114[���]XBox, ������, �ý� ��� ���� �ִ°� �˷���.
	GAMEMSG_RESPONSE_ANOTHERAUTH,				//115[�ؿ�] �ٸ� �������� ���� �˸�

	// ����. 
	GAMEMSG_RESPONSE_LETTER,					//116[�°�] ����. 

	// ä�� 
	GAMEMSG_REQUEST_CHAT		,				//117[�°�]
	GAMEMSG_RESPONSE_CHAT		,				//118[�°�]

	GAMEMSG_REQUEST_SECRETCHAT,					//119[�°�] �Ӹ� ��û. 

	GAMEMSG_RESPONSE_SECRETCHATRESULT,			//120[�°�] �Ӹ� ���� ����. 

	GAMEMSG_REQUEST_HEADCHAT,					//121[�°�] �Ӹ��� ��û. 
	GAMEMSG_RESPONSE_HEADCHAT,					//122[�°�] �Ӹ��� �뺸.

	GAMEMSG_REQUEST_MAKESECRETCHATCHANNEL,		//123[�ؿ�] ��� PersonID�� �Ӹ� ä���� �����. 
	GAMEMSG_RESPONSE_MAKESECRETCHATCHANNEL,		//124[�ؿ�]
	GAMEMSG_REQUEST_ACCEPTSECRETCHATCHANNEL,	//125[����] �ӼӸ� ���
	GAMEMSG_RESPONSE_ACCEPTSECRETCHATCHANNEL,	//126

	GAMEMSG_RESPONSE_ENEMYCAPTURE,				//127[�°�] ���� ���� ���¸� �뺸�Ѵ�.(����) 
	GAMEMSG_RESPONSE_ENEMYCAPTUREALL,			//128[�°�] ���� ��� ���� ���¸� �뺸�Ѵ�. 

	GAMEMSG_RESPONSE_WINWARPRIZE,				//129[�ؿ�] ���� �¸��� ���� ���� ����ġ�� �뺸�Ѵ�.

	GAMEMSG_REQUEST_WARJOIN,					//130[����] 30���� �������� ���ۿֱ� ������ �����ش�

	// ���� 
	GAMEMSG_REQUEST_ASKLIST,					//131[�°�] ���� ����� ��û�Ѵ�.  
	GAMEMSG_RESPONSE_ASKLIST,					//132[�°�]
	GAMEMSG_REQUEST_DELASK,						//133[�°�] Ư�� ������� ������ �����ϵ��� ��û�Ѵ�. 


	// ���� ����. 
	GAMEMSG_REQUEST_SKILLMASTERLIST,			//134[�°�] ���θ���Ʈ ��û. 	
	GAMEMSG_RESPONSE_SKILLMASTERLIST,			//135[�°�] ���θ���Ʈ �뺸. 

	GAMEMSG_REQUEST_REGISTMASTER,				//136[�°�] ���ε��/���� ��û.

	// ��ǰ. 
	GAMEMSG_RESPONSE_RAREITEMMADE,				//137[�°�] ��ǰ�� ����������� �뺸. 
	// ��� ����ǰ	
	GAMEMSG_RESPONSE_BIGWARITEM,				//138[�°�] ��� ����ǰ Ȯ�� �뺸. 
	// �渶, �鸶, ���丶 ����.
	GAMEMSG_RESPONSE_GOODHORSE,					//139[�°�] �� ���� �뺸. 

	GAMEMSG_RESPONSE_NOADDHORSE,				//140[��] �� �߰� ����. - 0 = �� ã��. 

	// ���� �ܰ� ��ȯ�� �⿬ 
	GAMEMSG_RESPONSE_HIGHSUMMON,				//141[����] ���� Rank�� ��ȯ�� ���� �뺸. 
	// ��õ�� ���� ���� 
	GAMEMSG_RESPONSE_RECOMMENDREWARD,			//142[�°�] ��õ�� ������ �޾����� ��ü ����. 
	// ������ ���� ���� 
	GAMEMSG_RESPONSE_FAMELEVELREWARD,			//143[�°�] ������ ��� ���� ������ �޾����� ��ü ����. 


	// ������ 
	GAMEMSG_RESPONSE_WARVILLAGE,				//144[����] �������� ���۰� ���Ḧ �˸�

	// ���ʽ� Ÿ��. 
	GAMEMSG_RESPONSE_BONUSTIME,					//145[�°�] ���ʽ� Ÿ�� ���۰� ���Ḧ �˸�

	// �����̵�
	GAMEMSG_REQUEST_WARPVILLAGE,				//146[�°�] �ش� ������ Warp�� ����� 
	GAMEMSG_REQUEST_RESIDENTWARPVILLAGE,		//147[���] �ֹ��� �ڱ� ������ Warp �� �����.


	// ȯ�� ���� ( �Ӹ� �ź�, �ŷ� �ź� )
	GAMEMSG_REQUEST_WHISPERCHAT_REJECT,			//148[���] ��� �Ӹ� �ź�
	GAMEMSG_RESPONSE_WHISPERCHAT_REJECT,		//149[���]

	GAMEMSG_REQUEST_PRIVATETRADE_REJECT,		//150[���] ��� �ŷ� �ź�
	GAMEMSG_RESPONSE_PRIVATETRADE_REJECT,		//151[���]

	GAMEMSG_REQUEST_PARTYINVITE_REJECT,			//152[���] ��Ƽ �ʴ� �ź�
	GAMEMSG_RESPONSE_PARTYINVITE_REJECT,		//153[���]

	GAMEMSG_REQUEST_FRIENDADD_REJECT,			//154[���] ģ�� �߰� �ź�
	GAMEMSG_RESPONSE_FRIENDADD_REJECT,			//155[���]

	// ��õ��. 
	GAMEMSG_RESPONSE_RECOMMENDPERSONAVAILABLE,	//156[�°�] ���� ��õ ����

	GAMEMSG_REQUEST_RECOMMENDPERSON,			//157[���] ���� ��õ
	GAMEMSG_RESPONSE_RECOMMENDPERSON,			//158[���]

	// ���� 
	GAMEMSG_RESPONSE_BOSSAPPEAR,				//159[�°�] ���� ���� ���� �˸�. 

	GAMEMSG_REQUEST_CAPTIONKINDCHANGE,			//160[���] �ؿ� �귯���� �ڸ� ���� ����

	// �Ұ��縮 ��� �̺�Ʈ. 
	GAMEMSG_RESPONSE_HUNTINGINFO,				//161[�°�] �Ұ��縮 ��� ����. 
	GAMEMSG_RESPONSE_HUNTINGREWARD,				//162[�°�] �Ұ��縮 ��� ������ ����. 

	// ���� ���� ��� �̺�Ʈ. 
	GAMEMSG_RESPONSE_GOGUINFO,					//163[�°�] ���� ���� ��� ����. 
	GAMEMSG_RESPONSE_GOGUREWARD,				//164[�°�] ���� ���� ���  ������ ����. 

	// ����ī�� �̺�Ʈ. 
	GAMEMSG_RESPONSE_OSAKAINFO,					//165[����] ����ī�� ���� ����. 
	GAMEMSG_RESPONSE_OSAKAREWARD,				//166[����] ����ī�� ������ ����. 

	// ��ȭ�� �̺�Ʈ. 
	GAMEMSG_RESPONSE_KANGHWADOINFO,				//167[����] ��ȭ�� ��� ����. 
	GAMEMSG_RESPONSE_KANGHWADOREWARD,			//168[����] ��ȭ�� ��� ������ ����. 

	// ���� 
	//GAMEMSG_RESPONSE_PRISONINFO, 

	// �ڵ� ���
	GAMEMSG_REQUEST_AUTOHUNTING,				//169[�ؿ�] �ڵ� ��� �Ű�
	GAMEMSG_RESPONSE_AUTOHUNTING,				//170

	GAMEMSG_REQUEST_AUTOHUNTING_ASK,			//171[�ؿ�] �ڵ� ��� �亯�ϱ�
	GAMEMSG_RESPONSE_AUTOHUNTING_ASK,			//172

	GAMEMSG_RESPONSE_AUTOHUNTING_TIMEUPDATE,	//173[�ؿ�] �亯 ���� �ð��� �귯���� ���� �˷��ش�.

	GAMEMSG_RESPONSE_PERSONALSHOPMAKEINFO,		//174[�°�]���� ���� �����Ƿ� ���� Ŭ���̾�Ʈ�� ���. 

	GAMEMSG_RESPONSE_INSTANCEMAPINFO,			//175[�ؿ�] �ν��Ͻ� ������ ����(���� ����,�ִ� ����, ���� �ð�)

	GAMEMSG_RESPONSE_ACCOUNTLETTER,				//176

	GAMEMSG_RESPONSE_SERVERTIME,				//177[����] ������ �ð� ����(�д���)

	GAMEMSG_RESPONSE_USERCHARITEMINFO,			//178[����] ����� ������ ���� ��û �亯
	GAMEMSG_RESPONSE_USERCHARITEMINFO2,			//179[����] �뷮������ �ΰ��� ����

	GAMEMSG_REQUEST_GET_HOMEPAGE_URL,			//180[��] Ȩ������ �ּҸ� �����´�.
	GAMEMSG_RESPONSE_GET_HOMEPAGE_URL,			//181

	GAMEMSG_REQUEST_SET_HOMEPAGE_URL,			//182[��] Ȩ������ �ּҸ� �����Ѵ�.
	GAMEMSG_RESPONSE_SET_HOMEPAGE_URL,			//183

	//------------------------------------
	// Person
	//------------------------------------
	GAMEMSG_RESPONSE_CHARUPDATE	= 200,		//[�°�] �������� �⺻ ���� ������Ʈ. 

	//--------------------------------
	//  - ���� �޽��� �߰����� ���ÿ�...
	// ����
	GAMEMSG_REQUEST_SETFATHER,				//[�°�] ���� ����. 
	GAMEMSG_RESPONSE_SETFATHER,				//[�°�]

	GAMEMSG_RESPONSE_CHILDINFO,				//[�°�] ���¿� ���� ������ ������.

	GAMEMSG_REQUEST_APPLYFATHER,			//[�°�] ���� ��� ��û�Ѵ�.

	GAMEMSG_REQUEST_FATHERAPPLYERLIST,		//[�°�]
	GAMEMSG_RESPONSE_FATHERAPPLYERLIST,		//[�°�] ���� ��� ������ ����� �뺸�Ѵ�. 

	GAMEMSG_REQUEST_UPDATECHILDLIST,		//[�°�] ���� ��� ������Ʈ ��û. 
	GAMEMSG_RESPONSE_UPDATECHILDLIST,		//[�°�]

	GAMEMSG_REQUEST_RENOUNCEPUPIL,			//[����] ������ ���ڸ� ¥����. 
	GAMEMSG_RESPONSE_RENOUNCEPUPIL,			//[����]

	GAMEMSG_RESPONSE_OVERTAKETEACHERLEVEL,	//[����] ���ڰ� ���·����� ��������(û����)

	GAMEMSG_RESPONSE_REQUEST_SETFATHER,		//[����] ���� ��û�� ���¿��� ����� �Ѵ�.

	GAMEMSG_RESPONSE_PVPRESULT,				//[����] PVP����� �˷��ش�.
	//---------------------------------

	//  - ���� �޽��� �߰����� ���ÿ�...
	//----------------------------------
	// ĳ������ Ư�� ���� 
	GAMEMSG_REQUEST_PERSON_IP,				//[�°�] ImportantParameta ������ ������ ���� ��û�Ѵ�. 
	GAMEMSG_RESPONSE_PERSON_IP,				//[�°�] ImportantParameta ������ Ŭ���̾�Ʈ�� ������. 
	GAMEMSG_RESPONSE_PERSON_HEALTH,			//[�°�] �ǰ� ������ Ŭ���̾�Ʈ�� ������. 		
	GAMEMSG_RESPONSE_PERSON_SKILL,			//[�°�] SkillData�� Ŭ���̾�Ʈ�� ������. 
	GAMEMSG_RESPONSE_PERSON_ONESKILL,		//[�°�] ������� �Ѱ��� ��� ������ Ŭ���̾�Ʈ�� ������. 
	GAMEMSG_RESPONSE_PERSON_ALLITEM,		//[�°�] ������ ��� ������ ������ ������. 
	GAMEMSG_RESPONSE_PERSON_BANK,			//[�°�] ���� ������ ������. (���� )
	GAMEMSG_RESPONSE_PERSON_STOCK,			//[�°�] ���� ������ ������. (����-�⺻)
	GAMEMSG_RESPONSE_PERSON_STOCKORDER,		//[�°�] ���� ������ ������. (����-�ֹ�����)
	GAMEMSG_RESPONSE_PERSON_MARKET,			//[�°�] ���� ����.  
	GAMEMSG_RESPONSE_PERSON_MARKETORDER,	//[�°�] ���� �ֹ� ������ �뺸�Ѵ�. 
	GAMEMSG_RESPONSE_PERSON_QUEST,			//[�°�] Person�� ����Ʈ ������ �뺸�Ѵ�. 
	GAMEMSG_RESPONSE_PERSON_HORSE,			//[�°�] Person�� �������� �뺸�Ѵ�. 
	GAMEMSG_RESPONSE_PERSON_GUILTY,			//[�°�] Person�� �� ������ �뺸�Ѵ�. 
	GAMEMSG_RESPONSE_PERSON_INNERSTATUS,	//[�°�] Person�� InnerStatus��ü�� �뺸�Ѵ�. 
	GAMEMSG_RESPONSE_PERSON_WORLDMONEY,			//[�ؿ�] ��ť ������ ������.

	GAMEMSG_REQUEST_CHANGESTATUSINFO,		//[�°�] ĳ������ ���¸� ������ ���� ��û�Ѵ�. 
	GAMEMSG_RESPONSE_CHANGESTATUSINFO,		//[����] ĳ������ ���°� ����Ǿ����� �˸���.

	GAMEMSG_REQUEST_SETGREETING,		//[����] ĳ������ �λ縻 ����
	GAMEMSG_RESPONSE_SETGREETING,

	GAMEMSG_REQUEST_GETGREETING,		//[����] ĳ������ �λ縻 ������
	GAMEMSG_RESPONSE_GETGREETING,

	//-----------------------------------
	//  - ���� �޽��� �߰����� ���ÿ�...
	//-----------------------------------
	// �б� 
	GAMEMSG_REQUEST_SETSCHOOL,				//[�°�] �б����. 

	GAMEMSG_RESPONSE_SCHOOL,				//[�°�] �б� ���� �뺸. 

	GAMEMSG_REQUEST_SCHOOLUSERNUM,			//[�°�] �������� �б� ����� ��. 
	GAMEMSG_RESPONSE_SCHOOLUSERNUM,	
	//-------------------------------------

	GAMEMSG_REQUEST_USERORDER	,			//[�°�] ĳ���� ��� ��û. 
	GAMEMSG_RESPONSE_USERORDER	,			//[�°�]

	GAMEMSG_RESPONSE_DEALTHPENALTYINFO,		//[�°�] ��� ���Ƽ ����. 

	GAMEMSG_REQUEST_NAME		,			//[�°�] �̸� ���� ��û. 
	GAMEMSG_RESPONSE_NAME		,			//[�°�]

	GAMEMSG_RESPONSE_USERLEVELUP,			//[�°�] ����� ������ �뺸. 

	GAMEMSG_REQUEST_ALLCHARINFO,			//[�°�] ����� ĳ���Ͱ� ĳ������ ��� ������ ��û�Ѵ�. 
	GAMEMSG_RESPONSE_ALLCHARINFO,			//[�°�]
	GAMEMSG_RESPONSE_ALLCHARINFOONE,		//[����] ĳ���� ����1
	GAMEMSG_RESPONSE_ALLCHARINFOTWO,		//[����] ĳ���� ����2


	GAMEMSG_REQUEST_USEBONUS,				//[�°�] ���ʽ��� ����ϰڴٴ� �޽����� ������.

	GAMEMSG_REQUEST_DECREASESKILLBONUS,		//[�°�] ��ų���ʽ��� �����Ѵ�. 

	GAMEMSG_RESPONSE_INCLIFE,				//[�°�] ����� ����. 
	GAMEMSG_RESPONSE_INCMANA,				//[�°�] 

	GAMEMSG_REPONSE_INCHUNGRY,				//[�°�]  ������ �Ծ �谡 �ҷ����� Ŭ���̾�Ʈ���� �˸���. 

	GAMEMSG_REQUEST_HORSEFREE,				//[�°�] ���� Ǯ���ش�. 
	GAMEMSG_RESPONSE_HORSEFREE,				//[�°�]

	//KHY - 1001 - ��µ��� 5���� ���� ����.
	GAMEMSG_REQUEST_CHANGEHORSE,				//[��]  ���� �ٲ۴�.
	GAMEMSG_RESPONSE_CHANGEHORSE,				//[��]

	GAMEMSG_RESPONSE_CHANGEMONEY,			//[�°�] ���� ����Ǿ���.

	GAMEMSG_REQUEST_USERID,					//[�°�] ĳ���� ���� �ƴ�, ���� ���̵� ��û�� ( �̴� Ȩ������ ����Ϸ���.. )
	GAMEMSG_RESPONSE_USERID,				//[�°�] ����

	GAMEMSG_RESPONSE_WARKILL,				//[�°�] ���� �뺸. 

	GAMEMSG_RESPONSE_JIM,					//[�°�] ������. 

	GAMEMSG_RESPONSE_HOMEVILLAGE,			//[�°�] �ּ��� ���� �뺸. 


	GAMEMSG_REQUEST_PLAYTIME,				//[�°�] �÷��� �ð��� ��û�Ѵ�.
	GAMEMSG_RESPONSE_PLAYTIME,				//[�°�]

	GAMEMSG_REQUEST_HIT,					//[����] Ÿ�� ������ ��û�Ѵ�.
	GAMEMSG_RESPONSE_HIT,					//[�°�] �¾����� ������. 

	GAMEMSG_REQUEST_SETBULLET,				//[����] ���Ÿ� ������ ������ ������ ��û�Ѵ�.

	GAMEMSG_RESPONSE_GETEXP,				//[�°�] ����ġ�� ȹ�������� �뺸. 

	GAMEMSG_RESPONSE_GENERALEFT,			//[�°�] ����ȿ�� �뺸. 

	GAMEMSG_REQUEST_PERSONPRIVATEINFO,		//[�°�] ���� ���� ��û.
	GAMEMSG_REQUEST_PERSONPRIVATEINFOBYPERSONID, //[���] ���� ���� ��û( PersonID �� )
	GAMEMSG_RESPONSE_PERSONPRIVATEINFO,		//[�°�]

	GAMEMSG_REQUEST_ADDINFO,				//[����] Ư��ĳ������ ��� �߰������� ��û�Ѵ�.
	GAMEMSG_RESPONSE_ADDINFO,				//[����]

	GAMEMSG_RESPONSE_CHANGESUMMONSTATUS,	//[�°�]���� ���� ��ȯ���� ������ ����Ǿ���. 

	GAMEMSG_REQUEST_CHANGEMAGIC,			//[����] ĳ������ ���� ������ �ٲپ���.
	GAMEMSG_RESPONSE_CHANGEMAGIC,			//[����]

	GAMEMSG_RESPONSE_EVENTINFO,				//[�°�] �̺�Ʈ ������ ������. 

	GAMEMSG_RESPONSE_WARPEFFECT,			//[�°�] ���� ���������� ������ ��� �̸� Ŭ���̾�Ʈ���� �˸���. 

	// ����Ʈ 
	GAMEMSG_RESPONSE_QUESTUSERINFO,			//[�°�]Ư�� ������� Ư�� ����Ʈ ������ �뺸�Ѵ�. 

	GAMEMSG_RESPONSE_SPECIALQUESTMADE,		//[�°�]Ư�� �ӹ��� �����Ǿ����� �˸���. 

	GAMEMSG_RESPONSE_SPECIALQUESTREWARD,	//[�°�]Ư�� �ӹ� �Ϸ��Ŀ� ���� ������ �˷��ش�. 

	GAMEMSG_RESPONSE_QUESTEFFECT,		//[����]����Ʈ ����, �Ϸ� ����Ʈ�� �˷���.

	GAMEMSG_RESPONSE_CLEAR_SPECIALWORD,		//[�ؿ�]�ܾ� ���� �ϼ� ���� �뺸��

	GAMEMSG_REQUEST_PRIZE_GAMEEVENT,		//[�ؿ�] �̺�Ʈ ��÷ ���θ� Ȯ���Ѵ�.
	GAMEMSG_RESPONSE_PRIZE_GAMEEVENT,

	GAMEMSG_REQUEST_SETSCHOOLEVENT,			//[����] �б� �̺�Ʈ ��û
	GAMEMSG_RESPONSE_SETSCHOOLEVENT,

	//GAMEMSG_REQUEST_COUNTATTACK_INFO,		//[�ؿ�] ������ �ݰ� �̺�Ʈ
	//GAMEMSG_RESPONSE_COUNTATTACK_INFO,

	GAMEMSG_REQUEST_EVENTNPC,				//[����] �̺�Ʈ ����(������ õ��)
	GAMEMSG_RESPONSE_EVENTNPC,

	// WeaponSkill
	GAMEMSG_REQUEST_GET_WEAPONSKILLCOST,	//[�ؿ�] �������� �����µ� ��� ����� �����´�.
	GAMEMSG_RESPONSE_GET_WEAPONSKILLCOST,

	GAMEMSG_REQUEST_SET_WEAPONSKILL,		//[�ؿ�] ����������ų�� �ø���.
	GAMEMSG_RESPONSE_SET_WEAPONSKILL,

	GAMEMSG_REQUEST_RIGHTMOUSE_USERLIST_NAME,	// [����] ������ ���콺�� ������ �������� �������� ����� ��ﶧ �ʿ��� �̸��� ����ִ� �޽���
	GAMEMSG_RESPONSE_RIGHTMOUSE_USERLIST_NAME,

	// !!!!!!!!!! WARNRING !!!!!!!!!!!  299���� ��δ� ã���ϴ�.   !!!!!!!!!! WARNRING !!!!!!!!!!!
	// !!!!!!!!!! WARNRING !!!!!!!!!!!  �� �̻� �߰����� ���ʽÿ�. !!!!!!!!!! WARNRING !!!!!!!!!!!
	GAMEMSG_RESPONSE_TIRED_STATUS,
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//---------------------------
	// ������ ���� �޽��� 
	//---------------------------
	GAMEMSG_REQUEST_MAKEITEMINV	= 300,				//300[�°�] �ι��丮���� �������� ����� 

	GAMEMSG_REQUEST_MAKEITEMSWITCH,					//301[����] ������ �����̹��� ����
	GAMEMSG_RESPONSE_MAKEITEMSWITCH,				//302[����] ������ �����̹��� ����

	GAMEMSG_REQUEST_ITEMMOVE,						//303[�°�] �������� ĳ���� ������ �̵���Ų��.

	GAMEMSG_REQUEST_ENCHANTITEMINV,					//304[�¾�] ��æƮâ���� �ƾ����� ��æƮ�Ѵ�.

	GAMEMSG_REQUEST_ITEMCHANGE,						//305[�¾�] �������� ĳ���� ������ �ٲ��ش�. 

	GAMEMSG_REQUEST_USEITEM,						//306[�°�] �������� ����� ���� ��û�Ѵ�. 

	GAMEMSG_REQUEST_INVDROP,						//307[�°�] ����ڰ� ���� �ִ� �������� ����ϵ��� ��û�Ѵ�. 

	GAMEMSG_REQUEST_INVPICKUP,						//308[�°�] ���� ������ �������� �ݵ��� ��û�Ѵ�. 

	GAMEMSG_RESPONSE_ITEMDROP,						//309[�°�] ���� ������ �������� ����. 

	GAMEMSG_REQUEST_ENCHANT,						//310[�°�] ������ ��� �����Ѵ�. 

	GAMEMSG_RESPONSE_MAKEITEMDELAY,					//311[�°�] ��ǰ ���� ���� �ð��� �뺸�Ѵ�. 

	GAMEMSG_REQUEST_NPCREPAIRPRICE,					//312[�°�] NPC�������� ��û. 
	GAMEMSG_RESPONSE_NPCREPAIRPRICE,				//313[�°�]

	GAMEMSG_REQUSET_NPCREPAIR,						//314[�°�] NPC���� ��û. 

	GAMEMSG_REQUEST_EXCHANGEWEAPON,					//315[�°�] ���� 1, 2���� active ��Ȳ�� �ٲ��ش�.
	GAMEMSG_RESPONSE_EXCHANGEWEAPON,				//316[�°�]	

	GAMEMSG_REQUEST_EXCHANGECLOTHES,				//317[�¾�] �Ǻ� 1, 2���� active ��Ȳ�� �ٲ��ش�.
	GAMEMSG_RESPONSE_EXCHANGECLOTHES,				//318[�¾�]	

	GAMEMSG_REQUEST_UPGRADEITEM,					//319[���] ������ ���׷��̵� �õ� ( �Ϲ�->ȣǰ->��ǰ->�ű� ) - Ȥ�θ� ���� �̿���� ����ؼ�.
	GAMEMSG_RESPONSE_UPGRADEITEM,					//320[���]

	GAMEMSG_REQUEST_PERFORMANCEUPGRADEITEM,			//321[���] ������ ���׷��̵� �õ� ( �Ϲ�->ȣǰ->��ǰ->�ű� ) - Ȥ�θ� ���� �̿���� ����ؼ�.
	GAMEMSG_RESPONSE_PERFORMANCEUPGRADEITEM,		//322[���]

	GAMEMSG_RESPONSE_MAKEITEMDLG,					//323[�ؿ�] ������ ������ ���â �ٿ��

	GAMEMSG_RESPONSE_ENCHANTITEMDLG,				//324[�¾�] ������ ��æƮ�� ���â �ٿ��

	GAMEMSG_RESPONSE_ISSKILLITEM,					//325[�ؿ�] �̴ϰ����� ���� ���ֳ� ����... �� ��ų�� ����� �������̳� ���� �ǳ�

	//	GAMEMSG_REQUEST_MONSTERCORP_START,				//[����] �̴ϰ����� �����Ѵ�.
	GAMEMSG_REQUEST_MONSTERCORP_SCORE,				//326[����] �����ֽ�ȸ�� ������ ������.
	GAMEMSG_REQUEST_MONSTERCORP_COMBOINFO,			//327[����] �����ֽ�ȸ�� ������ ���������� ����� �� �ְ� �޺� ������ ������.

	GAMEMSG_REQUEST_ROULETTEGAME_INFO,				//328[����] �ڴ�� ���������� ������
	GAMEMSG_RESPONSE_ROULETTEGAME_RESULT,			//329[����] �ڴ�� ���
	GAMEMSG_REQUEST_ROULETTEGAME_STOP,				//330[����] �ڴ�� ����

	GAMEMSG_RESPONSE_PREMIUM_INFO,					//331[�ؿ�] �����̾� �Ⱓ ������ �뺸�Ѵ�.
	GAMEMSG_REQUEST_MAKEITEMINVINDEX,				//332[�¾�] ->[����] ������ ����

	GAMEMSG_REQUEST_ENCHANTITEMINVINDEX,			//333[�¾�] ����â �κ��丮�� �ε����� ����
	GAMEMSG_RESPONSE_ENCHANTITEMSTARTOREND,			//334[�¾�] ����â �κ��丮�� �ε����� ����
	GAMEMSG_REQUEST_ENCHANTITEMSTARTOREND,			//335[�¾�] ����â �κ��丮�� �ε����� ����

	GAMEMSG_REQUEST_ENCHANTOTHERSHOW,				//336[�¾�]
	GAMEMSG_RESPONSE_ENCHANTOTHERSHOW,				//337[�¾�]

	GAMEMSG_REQUEST_ENCHANTOTHERPRICE,				//338[�¾�]
	GAMEMSG_RESPONSE_ENCHANTOTHERPRICE,				//339[�¾�]

	GAMEMSG_REQUEST_ENCHANTITEMSWITCH,				//340
	GAMEMSG_REQUEST_ITEMSPLIT,						//341

	GAMEMSG_REQUEST_ENCHANT_USEDAYPLUS,				//342[����] ������ �Ⱓ ����
	GAMEMSG_RESPONSE_ENCHANT_USEDAYPLUS,			//343[����]

	GAMEMSG_REQUEST_CHANGEENCHANT,					//344[����] ������ ��þƮ �Ӽ� ���� ��û - 2008.02.20

	GAMEMSG_REQUEST_SUMMONPUSHITEM,					//345[����] ������� ��ȯ���� ������ �̵�
	GAMEMSG_REQUEST_SUMMONPOPITEM,					//346[����] ��ȯ������ ������Է� ������ �̵�

	GAMEMSG_RESPONSE_SUMMONCHANGEITEM,				//347[����] ��ȯ�� �������� ����Ǿ��� (Push/Pop) ����ó��


	//******************************************************************************************
	//[�߰� : Ȳ���� 2008. 1. 29 =>  ���� ���� ��� �޽���.]
	GAMEMSG_REQUEST_SPACE_BOX_LIST,					//348 ���� ���� ����Ʈ ��û.
	GAMEMSG_RESPONSE_SPACE_BOX_LIST,				//349

	GAMEMSG_REQUEST_TRESURE_BOX_LIST,				//350 ���� ���� ����Ʈ ��û.
	GAMEMSG_RESPONSE_TRESURE_BOX_LIST,				//351

	GAMEMSG_REQUEST_KEEP_SPACE_BOX_MOVE_ITEM,		//352 �κ��� ���� ������ �̵�.
	GAMEMSG_RESPONSE_KEEP_SPACE_BOX_MOVE_ITEM,		//353

	GAMEMSG_REQUEST_RECOVERY_SPACE_BOX_MOVE_ITEM,	//354 �κ��� ���� ������ �̵�.
	GAMEMSG_RESPONSE_RECOVERY_SPACE_BOX_MOVE_ITEM,	//355

	GAMEMSG_RESPONSE_USE_SPACEBOX_ITEM,				//356[����] �������� �������� ����Ͽ���
	GAMEMSG_RESPONSE_USE_TREASURE_ITEM,				//357[����] ��í���� �������� ����Ͽ���

	//******************************************************************************************

	GAMEMSG_REQUEST_OPENBIGITEMBOX,					// [����] : ��� ���� ������ ����

	// 6�� �Ǽ� 
	GAMEMSG_REQUEST_GETBYUNGZOINFO = 400,			//[�ؿ�] ���� �Ǽ��� ������ ��û�Ѵ�.
	GAMEMSG_RESPONSE_GETBYUNGZOINFO,				//[�ؿ�]

	GAMEMSG_REQUEST_GETGONGZOINFO,					//[�ؿ�]
	GAMEMSG_RESPONSE_GETGONGZOINFO,					//[�ؿ�]

	GAMEMSG_REQUEST_GETHYUNGZOINFO,					//[�ؿ�]
	GAMEMSG_RESPONSE_GETHYUNGZOINFO,				//[�ؿ�]

	GAMEMSG_REQUEST_GETHOZOINFO,					//[�ؿ�]
	GAMEMSG_RESPONSE_GETHOZOINFO,					//[�ؿ�]

	GAMEMSG_REQUEST_GETIZOINFO,						//[�ؿ�]
	GAMEMSG_RESPONSE_GETIZOINFO,					//[�ؿ�]

	GAMEMSG_REQUEST_GETYEZOINFO,					//[�ؿ�] ���� �Ǽ��� ������ ��û�Ѵ�.
	GAMEMSG_RESPONSE_GETYEZOINFO,					//[�ؿ�]

	GAMEMSG_REQUEST_GETGOONZUINFO,					//[�ؿ�] ������ ������ ��û�Ѵ�.
	GAMEMSG_RESPONSE_GETGOONZUINFO,					//[�ؿ�]

	GAMEMSG_REQUEST_SETBYUNGZOINFO,					//[�ؿ�] ���� �Ǽ��� ������ �����Ѵ�.

	GAMEMSG_REQUEST_SETBYUNGZOINFO_VILLAGEWARINFO,	//[����] ���� �Ǽ��� ������ �ð� ������ �����Ѵ�.

	GAMEMSG_REQUEST_SETGONGZOINFO,					//[�ؿ�]

	GAMEMSG_REQUEST_SETHYUNGZOINFO,					//[�ؿ�]

	GAMEMSG_REQUEST_SETHYUNGZOPRISON,				//[�ؿ�] �����Ǽ��� �˼��� �����Ѵ� 

	GAMEMSG_REQUEST_SETHOZOINFO,					//[�ؿ�]

	GAMEMSG_REQUEST_SETIZOINFO,						//[�ؿ�]

	GAMEMSG_REQUEST_SETYEZOINFO,					//[�ؿ�] ���� �Ǽ��� ������ �����Ѵ�.

	GAMEMSG_REQUEST_SETGOONZUINFO,					//[�ؿ�] ������ ������ �����Ѵ�.

	GAMEMSG_REQUEST_GOONZU_SETMINISTER,				//[�ؿ�] ���ְ� �Ǽ��� �Ӹ��Ѵ�.
	GAMEMSG_RESPONSE_GOONZU_SETMINISTER,

	GAMEMSG_REQUEST_GETANGELAPPLYERLIST,			//[�ؿ�] ��ȣõ�� ��û�� ����� ��û�Ѵ�.
	GAMEMSG_RESPONSE_GETANGELAPPLYERLIST,

	GAMEMSG_REQUEST_GETANGELLIST,					//[�ؿ�] ��ȣõ�� ����� ��û�Ѵ�.
	GAMEMSG_RESPONSE_GETANGELLIST,

	GAMEMSG_REQUEST_SETANGELAPPLYER,				//[�ؿ�] ��ȣõ�� ��� ��û�� ��û�Ѵ�.
	GAMEMSG_RESPONSE_SETANGELAPPLYER,

	GAMEMSG_REQUEST_SETANGEL,						//[�ؿ�] ��ȣõ�� �Ӹ��� ��û�Ѵ�.
	GAMEMSG_RESPONSE_SETANGEL,

	GAMEMSG_REQUEST_GETCHANGEDNAME,					//[�ؿ�] �̸� ������ ����� ��û�Ѵ�.
	GAMEMSG_RESPONSE_GETCHANGEDNAME,

	GAMEMSG_REQUEST_GETPOLICELIST,					//[����] ���� ����Ʈ�� ��û�Ѵ�
	GAMEMSG_RESPONSE_GETPOLICELIST,

	GAMEMSG_REQUEST_SETPOLICE,						//[����] ������ �Ӹ��� ��û�Ѵ�.
	GAMEMSG_RESPONSE_SETPOLICE,

	GAMEMSG_REQUEST_GETCRIMINALLIST,				//[����] ����� ����� ��û�Ѵ�.
	GAMEMSG_RESPONSE_GETCRIMINALLIST,

	GAMEMSG_REQUEST_SETCRIMINAL,					//[����] ����� ����� ��û
	GAMEMSG_RESPONSE_SETCRIMINAL,

	GAMEMSG_REQUEST_GOONZU_SETLIQUIDATION,			//[����] ���ְ� �Ļ� ������ �����Ѵ�.
	GAMEMSG_RESPONSE_GOONZU_SETLIQUIDATION,

	GAMEMSG_REQUEST_GOONZU_GETBONUSTIME,			//[����] ���ְ� ������ ���ʽ� Ÿ���� �����´�.
	GAMEMSG_RESPONSE_GOONZU_GETBONUSTIME,	

	GAMEMSG_REQUEST_GOONZU_SETBONUSTIME,			//[����] ���ְ� ���ʽ� Ÿ���� �����Ѵ�.
	GAMEMSG_RESPONSE_GOONZU_SETBONUSTIME,	


	//--------------------------------
	// ���
	//--------------------------------
	GAMEMSG_REQUEST_BECHIEF = 1100,					//[�°�] Chief�� �ǰڴٴ� ��û. 

	GAMEMSG_REQUEST_VILLAGESTRUCT,					//[�°�] ������ �ǹ� ������ ��û�Ѵ�. 
	GAMEMSG_RESPONSE_VILLAGESTRUCT,					//[�°�]

	GAMEMSG_RESPONSE_RANK,							//[�°�] �ź��� �뺸 

	GAMEMSG_REQUEST_CANDIDATE,						//[�°�] �ĺ��ڵ�� ��û. 

	GAMEMSG_REQUEST_CANCELCANDIDATE,				//[�°�] �ĺ��ڵ�� ��� ��û. 

	GAMEMSG_REQUEST_CANDIDATELIST,					//[�°�] �ĺ��� ��� ��û. 
	GAMEMSG_RESPONSE_CANDIDATELIST,					//[�°�] ����� �ĺ��� ��� �뺸 . 

	GAMEMSG_RESPONSE_SERVERRTN,						//[�°�] ������ ���ϰ�  �뺸

	GAMEMSG_RESPONSE_CHARSERVERRTN,					//[��][KHY] - 0910 - Ŭ���̾�Ʈ�� ĳ���������� ���ϰ��� ������.
	GAMEMSG_REQUEST_CHARSERVERRTN,					//Ŭ���̾�Ʈ�� ������ ������ ���� ������ ������. 

	GAMEMSG_REQUEST_DELCANDIDATE,					//[�°�] �ĺ��� ��� ���� ��û. 

	GAMEMSG_REQUEST_RESIGN,							//[�°�] Chief���� ���� ��û 

	GAMEMSG_REQUEST_INVESTLIST,						//[�°�] ������ ������ ����Ʈ�� ��û�Ѵ�. 
	GAMEMSG_RESPONSE_INVESTLIST,					//[�°�] ������ ������ ����Ʈ�� �뺸�Ѵ�. 

	GAMEMSG_REQUEST_SETSYMBOLSTATUS,				//[����] ������� ����� �����ϰ� �ɺ�(��Ȳ��)�� ��ġ�� �����Ѵ� 
	GAMEMSG_RESPONSE_SETSYMBOLSTATUS,				//[����]

	GAMEMSG_REQUEST_SETCASTLESTATUS,		//[����] ������� ����� �����ϰ� ������ ��ġ�� �����Ѵ� 
	GAMEMSG_RESPONSE_SETCASTLESTATUS,		//[����]

	GAMEMSG_REQUEST_PAYDIVIDEND,			//[����] ������� ���ֵ鿡�� �ֽĹ���� �ǽ��Ѵ� 
	GAMEMSG_RESPONSE_PAYDIVIDEND,			//[����]

	GAMEMSG_REQUEST_HIRENPC,				//[����] ������� ����NPC�� ����Ѵ� 
	GAMEMSG_RESPONSE_HIRENPC,				//[����]

	GAMEMSG_REQUEST_GETNPCLIST,				//[����] ����NPC ����Ʈ�� ��û�Ѵ� 
	GAMEMSG_RESPONSE_GETNPCLIST,			//[����]

	GAMEMSG_REQUEST_APPLYRESIDENT,			//[����] ���� �ֹε�Ͻ�û�� �Ѵ� 
	GAMEMSG_RESPONSE_APPLAYRESIDENT,		//[����]	

	GAMEMSG_REQUEST_APPLYRESIDENT2,			// [����] ����, ����. �������� �ʴ�� ���� �ֹε�� ��û.

	GAMEMSG_REQUEST_CANCELRESIDENT,			//[����] ���� �ֹε�Ͻ�û�� ����Ѵ� 
	GAMEMSG_RESPONSE_CANCELRESIDENT,		//[����]

	GAMEMSG_REQUEST_BERESIDENT,				//[����] ������� ��û�ڸ� ���� �ֹ����� ����Ѵ� 
	GAMEMSG_RESPONSE_BERESIDENT,			//[����]

	GAMEMSG_REQUEST_RESIDENTAPPLYERLIST,	//[����] ���� �ֹε�Ͻ�û�� ����Ʈ�� ��û�Ѵ�
	GAMEMSG_RESPONSE_RESIDENTAPPLYERLIST,	//[����]

	GAMEMSG_REQUEST_RESIDENTLIST,			//[����] ���� �ֹ� ����Ʈ�� ��û�Ѵ� 
	GAMEMSG_RESPONSE_RESIDENTLIST,			//[����]

	GAMEMSG_REQUEST_RESIDENTINFO,			//[����] ���� �ֹ��� �� ������ ��û�Ѵ� 
	GAMEMSG_RESPONSE_RESIDENTINFO,			//[����]

	GAMEMSG_REQUEST_SETRESIDENTSCORE,		//[����] ���� �ֹ��� ������ �����Ѵ� 
	GAMEMSG_RESPONSE_SETRESIDENTSCORE,		//[����]

	GAMEMSG_REQUEST_GETSTRUCTURELIST,		//[����] ���� �ǹ� ����� ��û�Ѵ� 
	GAMEMSG_RESPONSE_GETSTRUCTURELIST,		//[����]

	GAMEMSG_REQUEST_UPDATESTRUCTURELIST,	//[����] ���� �ǹ� ����� �����Ѵ� 
	GAMEMSG_RESPONSE_UPDATESTRUCTURELIST,	//[����]	

	GAMEMSG_REQUEST_BUILDSTRUCTURE,			//[����] ���� �ǹ��� �Ǽ��Ѵ� 
	GAMEMSG_RESPONSE_BUILDSTRUCTURE,		//[����]

	GAMEMSG_REQUEST_DESTROYSTRUCTURE,		//[����] ���� �ǹ��� ��ü�Ѵ� 
	GAMEMSG_RESPONSE_DESTROYSTRUCTURE,		//[����]

	GAMEMSG_REQUEST_VILLAGENOTICE,			//[���]
	GAMEMSG_RESPONSE_VILLAGENOTICE,			//[���]

	GAMEMSG_REQUEST_ALLSTRCHIEFINFO,		//[����] ������ ��� ��� ������ ���´�
	GAMEMSG_RESPONSE_ALLSTRCHIEFINFO,

	GAMEMSG_REQUEST_PROFITTOCAPITALFUND,	//[����] ���ͱ�->�ں������� ��ȯ
	GAMEMSG_RESPONSE_PROFITTOCAPITALFUND,	//[����]

	GAMEMSG_REQUEST_STARTEVENT,				//[����] ���� �̺�Ʈ ����
	GAMEMSG_RESPONSE_STARTEVENT,

	GAMEMSG_REQUEST_SETVILLAGEMARK,			//[����] ���� ��ũ�� �����Ѵ� 
	GAMEMSG_RESPONSE_SETVILLAGEMARK,		//[����]

	GAMEMSG_REQUEST_SETVILLAGEMAP,			//[����] ���� ���� �����Ѵ�.
	GAMEMSG_RESPONSE_SETVILLAGEMAP,			//[����]

	GAMEMSG_REQUEST_VILLAGELEVELDETAILINFO,	//[����] ���� ���� �� ���� 
	GAMEMSG_RESPONSE_VILLAGELEVELDETAILINFO,//[����]

	GAMEMSG_REQUEST_GENERALMEETING_INFO,			//[����] ������ȸ ������ ��û�Ѵ�
	GAMEMSG_RESPONSE_GENERALMEETING_INFO,			//[����]

	GAMEMSG_REQUEST_GENERALMEETING_SUGGEST,			//[����] �Ȱ��� ���� �Ѵ� 
	GAMEMSG_RESPONSE_GENERALMEETING_SUGGEST,		//[����]

	GAMEMSG_REQUEST_GENERALMEETING_VOTE,			//[����] ��ǥ �Ѵ�
	GAMEMSG_RESPONSE_GENERALMEETING_VOTE,			//[����]

	GAMEMSG_REQUEST_GENERALMEETING_ACCEPTCANDIDATE,	//[����] ����� �ĺ����� ���� 
	GAMEMSG_RESPONSE_GENERALMEETING_ACCEPTCANDIDATE,//[����]

	GAMEMSG_RESPONSE_SETVILLAGEUPGRADE,				//[�ؿ�] ������ ���� �ǹ� ���׷��̵�

	//#if defined(_CITYHALL_BANKRUPTCY)
	GAMEMSG_RESPONSE_NOTIFYCLIENTABOUTCITYHALLSTATE, //[�뷡] ������ ���� ���� ���� �˸� �뺸

	//#endif


	GAMEMSG_RESPONSE_GENERALMEETINGLETTER,			//[����] ������ȸ ���� ���θ� ���´�

	GAMEMSG_REQUEST_GENERALMEETING_PARTICIPATE,		//[����] ������ȸ ���� ���θ� �����Ѵ�
	GAMEMSG_RESPONSE_GENERALMEETING_PARTICIPATE,	//[����]

	GAMEMSG_REQUEST_GENERALMEETING_CHAT,			//[����] 
	GAMEMSG_RESPONSE_GENERALMEETING_CHAT,			//[����] 

	GAMEMSG_REQUEST_GENERALMEETING_CHATJOIN,		//[����] 
	GAMEMSG_RESPONSE_GENERALMEETING_CHATJOIN,		//[����] 

	GAMEMSG_REQUEST_GENERALMEETING_CHATOUT,			//[����] 
	GAMEMSG_RESPONSE_GENERALMEETING_CHATOUT,		//[����] 

	GAMEMSG_NOTICE_GENERALMEETING,					//[����] 

	GAMEMSG_REQUEST_CHANGESTRBASEMONEY,				//[����] �ǹ� �ں��� ����(������)
	GAMEMSG_RESPONSE_CHANGESTRBASEMONEY,

	GAMEMSG_REQUEST_GENERALMEETING_VOTE_REFRESH,	//[����]	��ǥ ��Ȳ ���ſ�û

	GAMEMSG_RESPONSE_VILLAGEWARRESULT_FOR_VILLAGEMEMBER,	//[����] �ش� ���� �ֹε鿡�Ը� �����ִ� ������ ���

	GAMEMSG_REQUEST_DONATEVILLAGEMONEY,				//[����] ���� ��α� ����
	GAMEMSG_RESPONSE_DONATEVILLAGEMONEY,

	GAMEMSG_REQUEST_DONATEMEMBERLIST,				//[����] ����� �������
	GAMEMSG_RESPONSE_DONATEMEMBERLIST,

	//--------------------------------
	// ���� 
	//--------------------------------
	GAMEMSG_REQUEST_CREATEBANKACCOUNT	= 1200,		//[�°�] ���忡 ���¸� ������� ��û�Ѵ�
	GAMEMSG_REQUEST_CLOSEBANKACCOUNT,				//[�°�] ���忡 ���� ������ ��û�Ѵ�

	GAMEMSG_REQUEST_INPUTTOBANK,					//[�°�] ���忡 ���� �ñ�� ���� ��û�Ѵ�. 

	GAMEMSG_REQUEST_INPUTTOBANKALLMONEY,			//[�°�] �������� ��� �Ա� 

	GAMEMSG_REQUEST_OUTPUTFROMBANK,					//[�°�] ���忡�� ���� ã�� ���� ��û�Ѵ�. 

	GAMEMSG_REQUEST_OUTPUTFROMBANKALLMONEY,			//[����] ���忡�� �����Ḧ ���� ��� ���� ã�� ���� ��û�Ѵ�. 

	GAMEMSG_RESPONSE_BANKMONEY,						//[�°�] ���� �ܾ��� Ŭ���̾�Ʈ���� �뺸�Ѵ�. 

	GAMEMSG_REQUEST_SETBANKFEE,						//[�°�] ���� ������ ���� ��û. 

	GAMEMSG_RESPONSE_DATE,							//[�°�] ����ð� �뺸. 

	GAMEMSG_RESPONSE_CANCEL_STOCKORDER,				//[����] ������ ���� ���ڶ� �ż��ֹ����

	GAMEMSG_RESPONSE_CREATEBANKACCOUNT_CANCEL,		//[�߰� : Ȳ���� 2008. 1. 9 => ���� �������� 0�̾ ���¸���� ����.]	
	//-------------------------
	// ���� 
	//-------------------------
	GAMEMSG_REQUEST_STOCKORDERINFO = 1300,			//[�°�] ������ �ö�� �ֹ��߿� ������ ���� ��û�Ѵ�. 
	GAMEMSG_RESPONSE_STOCKORDERINFO,				//[�°�]

	GAMEMSG_REQUEST_CANCELSTOCKORDER,				//[�°�] �ֽ� �ֹ� ��� ��û.  	

	GAMEMSG_RESPONSE_STOCKPRICE,					//[�°�] �� ������ �ְ��� Ŭ���̾�Ʈ���� �뺸 

	GAMEMSG_REQUEST_SELLSTOCK,						//[�°�] �ֽ��� �� ���� ��û�Ѵ�. 
	GAMEMSG_REQUEST_BUYSTOCK,						//[�°�] �ֽ��� �� ���� ��û�Ѵ�.

	GAMEMSG_REQUEST_STOCKBIDVILLAGELIST,			//[����] �������� ���� ����Ʈ�� ��û�Ѵ� 
	GAMEMSG_RESPONSE_STOCKBIDVILLAGELIST,			//[����]

	GAMEMSG_REQUEST_STOCKBIDDERLIST,				//[����] ������ ����Ʈ�� ��û�Ѵ� 
	GAMEMSG_RESPONSE_STOCKBIDDERLIST,				//[����]

	GAMEMSG_REQUEST_BIDSTOCK,						//[����] ���� �Ѵ� 
	GAMEMSG_RESPONSE_BIDSTOCK,						//[����]

	GAMEMSG_REQUEST_CANCELBIDSTOCK,					//[����] ���� ���
	GAMEMSG_RESPONSE_CANCELBIDSTOCK,				//[����]

	GAMEMSG_REQUEST_STOCKBIDDATE,					//[����] ���� �������� ��û�Ѵ� (�ֱ�������)
	GAMEMSG_RESPONSE_STOCKBIDDATE,					//[����]

	GAMEMSG_REQUEST_SETSTOCKFEE,					//[�°�] ���� ������ ���� ��û. 

	GAMEMSG_RESPONSE_STOCKTRADEINFO,				//[�°�] ������ �÷��� ����, ���� �ֹ��� ����. 

	GAMEMSG_REQUEST_BUYBIDSTOCK,					//[����] ���ڽ��۵� �ֽ��� ���.
	GAMEMSG_RESPONSE_BUYBIDSTOCK,

	GAMEMSG_REQUEST_MYSTOCKINFO,					//[����] ���ڽ��۵� �ֽĶ����� ������ ��û

	GAMEMSG_REQUEST_STOCKOFFERINGORDER,				//[����] 

	GAMEMSG_REQUEST_STOCKOFFERINGINFO,				//[����]
	GAMEMSG_RESPONSE_STOCKOFFERINGINFO,				//[����]

	GAMEMSG_REQUEST_EXCHANGESTOCK,					//[����] �ֽ��� �������� �ٲ۴�.
	GAMEMSG_RESPONSE_EXCHANGESTOCK,					//[����]

	//------------------------------
	// ���� ���� �޽���. 
	//------------------------------
	GAMEMSG_REQUEST_GETFROMMARKET	= 1400,			//[�°�] ���� â���� ������ ȸ���϶�� ��û. 

	GAMEMSG_REQUEST_MARKETORDER,					//[�°�] Ư�� ��ǰ�� �ֹ� ������ ������ ���� ��û. 
	GAMEMSG_RESPONSE_MARKETORDER,					//[�°�] ��ǰ �ֹ� ������û�� ���� ����. 

	GAMEMSG_REQUEST_SELLITEM,						//[�°�] ��ǰ�� �� ���� ��û�Ѵ�. 
	GAMEMSG_REQUEST_BUYITEM,						//[�°�] ��ǰ�� �� ���� ��û�Ѵ�. 

	GAMEMSG_RESPONSE_PRODUCTPRICE,					//[�°�] ��ǰ ���ݿ� ���� �뺸.	

	GAMEMSG_RESPONSE_MARKETSELLINFO,				//[�°�] ���ֿ��� �� ������ �ȸ� ������ �뺸. 

	GAMEMSG_REQUEST_SETMARKETFEE,					//[�°�] ���� ������ ���� ��û. 

	GAMEMSG_REQUEST_PRODUCTPRICE,					//[����] ��ǰ ���� ��û.



	//---------------------------
	// ���� ���� �޽��� 
	//---------------------------
	GAMEMSG_REQUEST_CHANGEHOUSECONTRACT  = 1500,	//[�°�] ������ ��� ������ �����Ѵ�. 

	GAMEMSG_RESPONSE_MYHOUSEUNITLIST,				//[����] ���� ��������Ʈ�� ����Ʈ�� �뺸�Ѵ�.

	GAMEMSG_REQUEST_HOUSEUNITLIST,					//[�°�] ��������Ʈ�� ����Ʈ�� ��û�Ѵ�. (�Ϲ��� ������ ��� ) 
	GAMEMSG_RESPONSE_HOUSEUNITLIST,					//[�°�] ��������Ʈ�� ����Ʈ�� �뺸�Ѵ�. 

	GAMEMSG_REQUEST_HOUSEUNITLIST_DETAIL,			//[�°�] ��������Ʈ�� �� ���� ����Ʈ�� ��û�Ѵ�. (����� ��� ) 
	GAMEMSG_RESPONSE_HOUSEUNITLIST_DETAIL,			//[�°�] ��������Ʈ�� �� ���� ����Ʈ�� �뺸�Ѵ�. 

	GAMEMSG_REQUEST_HOUSEAPPLYERLIST,				//[�°�] ���� ���� ����� ����Ʈ�� ��û�Ѵ�.	
	GAMEMSG_RESPONSE_HOUSEAPPLYERLIST,				//[�°�] ���� ���� ����� ����Ʈ�� �뺸�Ѵ�.

	GAMEMSG_REQUEST_HOUSERENTAPPLY,					//[�°�] ���� ���� ��û�� ��û�Ѵ�. 	

	GAMEMSG_REQUEST_HOUSERENTAPPLYCANCEL,			//[�°�] ���� �Ӵ� ��û ��� ��û. 

	GAMEMSG_REQUEST_HOUSERENT,						//[�°�] ������ �Ӵ��� ���� ��û�Ѵ�.
	//GAMEMSG_REQUEST_HOUSERENT_USER,					//[����] ������ �Ӵ��û�� ��û�Ѵ�.

	GAMEMSG_REQUEST_DELHOUSEAPPLYER,				//[�°�] ���� ���� ����� ����� �����ϵ��� ��û�Ѵ�. 
	GAMEMSG_RESPONSE_DELHOUSEAPPLYER,				//[�°�]

	GAMEMSG_REQUEST_STGINFO,						//[�°�] â�� ������ ��û�Ѵ�. 
	GAMEMSG_RESPONSE_STGINFO,						//[�°�] â�� ������ ������. 

	GAMEMSG_REQUEST_MOVEITEMINVTOSTG,				//[�°�] �κ����� â��� �������� ���� ���� ��û�Ѵ�. 
	GAMEMSG_REQUEST_MOVEITEMSTGTOINV,				//[�°�] â���� �κ����� �������� ���� ���� ��û�Ѵ�. 	
	GAMEMSG_REQUEST_MAKEITEM,						//[�°�] â���� �������� ������� ��û�Ѵ�. 

	GAMEMSG_RESPONSE_STGITEMINFO,					//[�°�] â�� ������ ������ ������.(1�� ������) 

	GAMEMSG_REQUEST_HOUSEUNITSTABLECREATE,			//[���] â�� �������� �����Ѵ�.
	GAMEMSG_RESPONSE_HOUSEUNITSTABLECREATE,			//[���]	

	GAMEMSG_REQUEST_HOUSEUNITHORSEIN,				//[���] �������� ���� �ִ´�.
	GAMEMSG_RESPONSE_HOUSEUNITHORSEIN,				//[���]

	GAMEMSG_REQUEST_HOUSEUNITHORSEOUT,				//[���] ���������� ���� ������.
	GAMEMSG_RESPONSE_HOUSEUNITHORSEOUT,				//[���]	

	GAMEMSG_RESPONSE_HOUSEUNITHORSEINFOSET,			//[���] �������� ���� ������ ����Ǿ�������, �V���Ѵ�.
	GAMEMSG_RESPONSE_HOUSEUNITHORSEEATFOOD,			//[���] �������� ���� ���̰� �Ծ����� �뺸�Ѵ�.


	GAMEMSG_REQUEST_HOUSEUNITUSEDGOODSBUILDINGCREATE,		//[���] �����ҿ��� ������ �����Ѵ�.
	GAMEMSG_RESPONSE_HOUSEUNITUSEDGOODSBUILDINGCREATE,		//[���]

	GAMEMSG_REQUEST_HOUSEUNITMAKEITEMFROMUSEDGOODSINFO,		// [���] ������ ������ ���� �� ������ ��Ÿ����.	
	GAMEMSG_RESPONSE_HOUSEUNITMAKEITEMFROMUSEDGOODSINFO,	// [���]

	GAMEMSG_REQUEST_HOUSEUNITMAKEITEMFROMUSEDGOODS,			//[���] ������ �������� �̾Ƴ���.
	GAMEMSG_RESPONSE_HOUSEUNITMAKEITEMFROMUSEDGOODS,		//[���]

	GAMEMSG_RESPONSE_HOUSEUNITMAKEITEMFROMUSEDGOODSNOTIFY,	//[���] ������ �������� �̾Ƴ����� ���� ����鿡�� �˸�

	GAMEMSG_REQUEST_HOUSEUNITNAMECHANGE,				//[����] â�� �̸� ����
	GAMEMSG_RESPONSE_HOUSEUNITNAMECHANGE,				//[����] 

	GAMEMSG_REQUEST_HOUSEITEMARRANGEMENT,				//[����] â�� ������ ����

	//---------------------------
	// ��� ��� ���� ��� ��� ( Agriculture - ���� ��Ī )
	// �����
	//---------------------------
	GAMEMSG_REQUEST_AGRICULTUREAUTOGAIN	= 1800,		//[���] �ڵ� ȹ��
	GAMEMSG_RESPONSE_AGRICULTUREAUTOGAIN,			//[���]

	GAMEMSG_RESPONSE_AGRICULTUREGETPRODUCTS,		//[���] ��ǰ ȹ��

	GAMEMSG_RESPONSE_AGRICULTUREGETPRODUCTSNOTIFY,	//[���] ��ǰ�� ȹ�� ������ ���� ������ ��������鿡�� �˸�

	GAMEMSG_RESPONSE_AGRICULTURESTART,				//[���] ���� ����
	GAMEMSG_RESPONSE_AGRICULTUREPAYRENTFEE,			//[���] ����ü� �Ӵ��ϰ� ���� ������ �˷���

	GAMEMSG_RESPONSE_AGRICULTUREFORNOTRENTMAN,		//[���] �ǹ��� �Ӵ����� ���� ����� ����ϵ��� �� �ֱ� ���ؼ�.
	GAMEMSG_RESPONSE_AGRICULTURELEASELEFTTIME,		//[����] ����, ����� �ӽ÷� �������� ���� �ð�

	//---------------------------
	// ����
	//---------------------------
	GAMEMSG_RESPONSE_FISHINGSTART,					//[���] ���� ���� �˸�

	GAMEMSG_RESPONSE_FISHINGDECREASETOOLDURABILITY, //[���] ���ô븦 ������ �������� ��� ��.

	GAMEMSG_RESPONSE_FISHINGGETMARINEPRODUCTS,		//[���] ����⸦ �������� ���ο��� �˷���

	GAMEMSG_RESPONSE_FISHINGGETMARINEPRODUCTSNOTIFY,//[���] ���� ����⸦ �������� ���� ������ ��������鿡�� �˷���. ( ä������ ǥ���ϱ� ���ؼ� )

	//---------------------------
	// ���
	//---------------------------
	GAMEMSG_REQUEST_FARMINGSTART,					//[���] ��� ���� ��û �Ǵ� ȹ�� ��깰 ����

	GAMEMSG_RESPONSE_FARMINGGETPRODUCTS,			//[���] ��깰 ȹ�� �Ǵ� ����

	GAMEMSG_RESPONSE_FARMINGGETPRODUCTSNOTIFY,		//[���] ��깰�� ȹ�� ������ ���� ������ ��������鿡�� �˸�

	GAMEMSG_REQUEST_FARMINGPAYRENTFEE,				//[���] ������� ��Ʈ ���� ���� ����� �����ϱ����ؼ� ���� ���� ���� ����



	//---------------------------
	// ä��
	//---------------------------
	GAMEMSG_REQUEST_MININGSTART,					//[���] ä�� ����

	GAMEMSG_RESPONSE_MININGGETPRODUCTS,				//[���] ��깰 ȹ�� �Ǵ� ����

	GAMEMSG_RESPONSE_MININGGETPRODUCTSNOTIFY,		//[���] ������ �˸�

	GAMEMSG_REQUEST_MININGPAYRENTFEE,				//[���] ���� ��Ʈ	



	//---------------------------
	// ������ ���� �޽��� 
	//---------------------------
	GAMEMSG_REQUEST_ENTERHUNT	= 1900,				//[�°�] ���������� �� ���� ��û. 

	GAMEMSG_REQUEST_HUNTMONSTERFIELDLISTADD,		//[���] ���� ��ġ �߰�
	GAMEMSG_RESPONSE_HUNTMONSTERFIELDLISTADD,		//[���]

	GAMEMSG_REQUEST_HUNTMONSTERFIELDLISTDEL,		//[���] ���� ��ġ ����
	GAMEMSG_RESPONSE_HUNTMONSTERFIELDLISTDEL,		//[���]

	GAMEMSG_REQUEST_HUNTMONSTERIN,					//[���] ���� ���� â�� �ֱ�
	GAMEMSG_RESPONSE_HUNTMONSTERIN,					//[���]

	GAMEMSG_REQUEST_HUNTMONSTEROUT,					//[���] ���� ���� â���� ����
	GAMEMSG_RESPONSE_HUNTMONSTEROUT,				//[���]

	GAMEMSG_RESPONSE_HUNTADDRATE,					//[�°�] �������� ��庥Ƽ���� ���Ѵ�. 

	//------------------------------
	// ���� ���� �޽���. 
	//------------------------------
	GAMEMSG_REQUEST_POSTOFFICE_SENDITEM = 2000,		//[����] ��ǰ ������ ��û�Ѵ�
	GAMEMSG_RESPONSE_POSTOFFICE_SENDITEM,			//[����]

	GAMEMSG_REQUEST_POSTOFFICE_SENDMONEY,			//[����] �۱��� ��û�Ѵ� 
	GAMEMSG_RESPONSE_POSTOFFICE_SENDMONEY,			//[����]

	GAMEMSG_REQUEST_POSTOFFICE_SENDMSG,				//[����] �޽��� ������ ��û�Ѵ�
	GAMEMSG_RESPONSE_POSTOFFICE_SENDMSG,			//[����]

	GAMEMSG_REQUEST_POSTOFFICE_RECVITEMLIST,		//[����] ���� ������ ����� ��û�Ѵ�
	GAMEMSG_RESPONSE_POSTOFFICE_RECVITEMLIST,		//[����]

	GAMEMSG_REQUEST_POSTOFFICE_RECVMONEYLIST,		//[����] ���� ���� ����� ��û�Ѵ�
	GAMEMSG_RESPONSE_POSTOFFICE_RECVMONEYLIST,		//[����]

	GAMEMSG_REQUEST_POSTOFFICE_RECVMSGLIST,			//[����] ���� �޽��� ����� ��û�Ѵ�
	GAMEMSG_RESPONSE_POSTOFFICE_RECVMSGLIST,		//[����]

	GAMEMSG_REQUEST_POSTOFFICE_GETITEM,				//[����] ���� �������� �κ��丮�� �ִ´�
	GAMEMSG_RESPONSE_POSTOFFICE_GETITEM,			//[����]

	GAMEMSG_REQUEST_POSTOFFICE_GETMONEY,			//[����] ���� ������ �� �����ݿ� �߰��Ѵ� 
	GAMEMSG_RESPONSE_POSTOFFICE_GETMONEY,			//[����]

	GAMEMSG_REQUEST_POSTOFFICE_DELMSG,				//[����] ���� �޽����� �����Ѵ�
	GAMEMSG_RESPONSE_POSTOFFICE_DELMSG,				//[����]

	GAMEMSG_REQUEST_POSTOFFICE_SETFEE,				//[����] �����Ḧ �����Ѵ�

	GAMEMSG_REQUEST_POSTOFFICE_GETRECORD,			//[����] �ۼ��ų����� ��û�Ѵ�
	GAMEMSG_RESPONSE_POSTOFFICE_GETRECORD,			//[����]

	//[����] ��ü������ ��ü �޽��� ������. => 2008-8-4
	GAMEMSG_REQUEST_POSTOFFICE_SENDITEM_GROUP,		//[����] ��ü�� ������ ������. 
	GAMEMSG_REQUEST_POSTOFFICE_SENDMONEY_GROUP,		//[����] ��ü�� �� ������. 
	GAMEMSG_REQUEST_POSTOFFICE_SENDMSG_GROUP,		//[����] ��ü�� �޽��� ������. 

	GAMEMSG_REQUEST_POSTOFFICE_USER_LIST_GROUP,		//[����] ��ü�� ���� ����Ʈ ��û.( ���, �����ֹ�, ģ�� )
	GAMEMSG_RESPONSE_POSTOFFICE_USER_LIST_GROUP,	//[����] ��ü �޽��� ������. ��ü�� ���� ��������Ʈ�� ����. => 2008-8-4 	

	GAMEMSG_REQUEST_CHAR_NAME_CHECK,				//[����] ���� �Է��ϴ� ������ �̸��� �޾� DB�� �̸��� �ִ��� ��û�ϰ� �� �޽���.
	GAMEMSG_RESPONSE_CHAR_NAME_CHECK,				//[����] ��ü �޽��� ������. ��ü�� ���� ����Ʈ�� �߰��� 1���� ������ ����. => 2008-8-4 




	GAMEMSG_REQUEST_GET_SAVEUSERITEM,				//[����] �������� ���´�
	GAMEMSG_RESPONSE_GET_SAVEUSERITEM,

	GAMEMSG_REQUEST_GET_SAVEUSERHORSE,				//[��] ������ ���� ��µ����� ���´�
	GAMEMSG_RESPONSE_GET_SAVEUSERHORSE,

	GAMEMSG_REQUEST_GET_SAVEUSERITEMLIST,			//[����] ������ ����Ʈ�� ���´�
	GAMEMSG_RESPONSE_GET_SAVEUSERITEMLIST,

	GAMEMSG_REQUEST_MARKETCONDITIONS,				//[��] Ŭ��� - �ü�Ȯ�ο� ���� ������ �ְ� �޴´�.
	GAMEMSG_RESPONSE_MARKETCONDITIONS,

	//------------------------------
	// �纹�� ���� �޽���. 
	//------------------------------
	GAMEMSG_REQUEST_HORSEMARKET_OUTHORSE	= 2100,	//[����] �纹�� â���� ���� ȸ���϶�� ��û. 
	GAMEMSG_RESPONSE_HORSEMARKET_OUTHORSE,

	GAMEMSG_REQUEST_HORSEMARKET_MYACCOUNT,			//[����] �� �ֹ� ����
	GAMEMSG_RESPONSE_HORSEMARKET_MYACCOUNT,			//[����]

	GAMEMSG_REQUEST_HORSEMARKET_ORDERLIST,			//[����] �� �ֹ� ����Ʈ
	GAMEMSG_RESPONSE_HORSEMARKET_ORDERLIST,			//[����]

	GAMEMSG_REQUEST_HORSEMARKET_SELLHORSE,			//[����] �� ���� �ֹ�
	GAMEMSG_RESPONSE_HORSEMARKET_SELLHORSE,			//[����]

	GAMEMSG_REQUEST_HORSEMARKET_BUYHORSE,			//[����] �� ����
	GAMEMSG_RESPONSE_HORSEMARKET_BUYHORSE,			//[����]

	GAMEMSG_REQUEST_HORSEMARKET_SETFEE,				//[����] �纹�� ������ ���� ��û. 

	//------------------------------
	// �Ű� ���� �޽���. 
	//------------------------------
	GAMEMSG_REQUEST_REALESTATEMARKET_CANCELORDER = 2200,	//[����] �ֹ��� ����Ѵ� 
	GAMEMSG_RESPONSE_REALESTATEMARKET_CANCELORDER,			//[����]

	GAMEMSG_REQUEST_REALESTATEMARKET_MYORDER,				//[����] �� �ֹ� ������ ���´�
	GAMEMSG_RESPONSE_REALESTATEMARKET_MYORDER,				//[����]

	GAMEMSG_REQUEST_REALESTATEMARKET_ORDERLIST,				//[����] �ֹ� ����Ʈ�� ���´�
	GAMEMSG_RESPONSE_REALESTATEMARKET_ORDERLIST,			//[����]

	GAMEMSG_REQUEST_REALESTATEMARKET_SELL,					//[����] ���� �ֹ��� �Ѵ� 
	GAMEMSG_RESPONSE_REALESTATEMARKET_SELL,					//[����]

	GAMEMSG_REQUEST_REALESTATEMARKET_BUY,					//[����] ���� �ֹ��� �Ѵ� 
	GAMEMSG_RESPONSE_REALESTATEMARKET_BUY,					//[����]

	GAMEMSG_REQUEST_REALESTATEMARKET_SETFEE,				//[����] ������ �����Ѵ� 

	GAMEMSG_REQUEST_REALESTATEMARKET_DETAILINFO,			//[����] �� ������ ���´� 
	GAMEMSG_RESPONSE_REALESTATEMARKET_DETAILINFO,			//[����]

	//------------------------------
	// �忹�� ���� �޽���. 
	//------------------------------
	GAMEMSG_REQUEST_SUMMONMARKET_CANCELORDER = 2300,		//[����] �ֹ��� ����Ѵ� 
	GAMEMSG_RESPONSE_SUMMONMARKET_CANCELORDER,				//[����]

	GAMEMSG_REQUEST_SUMMONMARKET_MYORDER,					//[����] �� �ֹ� ������ ���´� 
	GAMEMSG_RESPONSE_SUMMONMARKET_MYORDER,					//[����]

	GAMEMSG_REQUEST_SUMMONMARKET_ORDERLIST,					//[����] �ֹ� ����Ʈ�� ���´� 
	GAMEMSG_RESPONSE_SUMMONMARKET_ORDERLIST,				//[����]

	GAMEMSG_REQUEST_SUMMONMARKET_SELL,						//[����] ���� �ֹ��� �Ѵ�
	GAMEMSG_RESPONSE_SUMMONMARKET_SELL,						//[����]

	GAMEMSG_REQUEST_SUMMONMARKET_BUY,						//[����] ���� �ֹ��� �Ѵ� 
	GAMEMSG_RESPONSE_SUMMONMARKET_BUY,						//[����]

	GAMEMSG_REQUEST_SUMMONMARKET_SETFEE,					//[����] ������ �����Ѵ� 


	//------------------------------
	// ���� ���� �޽���. 
	//------------------------------
	GAMEMSG_REQUEST_LAND_CHANGECONTRACT  = 2500,	//[����] ���� ��� ������ �����Ѵ�. 

	GAMEMSG_REQUEST_LAND_UNITLIST,					//[����] ���� ����Ʈ�� ����Ʈ�� ��û�Ѵ�. (�Ϲ��� ������ ��� ) 
	GAMEMSG_RESPONSE_LAND_UNITLIST,					//[����] 

	GAMEMSG_REQUEST_LAND_UNITDETAIL,				//[����] ���� ����Ʈ�� �� ���� ����Ʈ�� ��û�Ѵ�. (����� ��� ) 
	GAMEMSG_RESPONSE_LAND_UNITDETAIL,				//[����] 

	GAMEMSG_REQUEST_LAND_APPLYERLIST,				//[����] ���� ���� ����� ����Ʈ�� ��û�Ѵ�.	
	GAMEMSG_RESPONSE_LAND_APPLYERLIST,				//[����]

	GAMEMSG_REQUEST_LAND_RENTAPPLY,					//[����] ���� ���� ��û�� ��û�Ѵ�. 	
	GAMEMSG_RESPONSE_LAND_RENTAPPLY,				//[����]

	GAMEMSG_REQUEST_LAND_CANCELAPPLY,				//[����] ���� �Ӵ� ��û ��� ��û. 
	GAMEMSG_RESPONSE_LAND_CANCELAPPLY,				//[����]

	GAMEMSG_REQUEST_LAND_RENT,						//[����] ���带 �Ӵ��� ���� ��û�Ѵ�. (���)
	GAMEMSG_RESPONSE_LAND_RENT,

	GAMEMSG_REQUEST_LAND_DELAPPLYER,				//[����] ���� ���� ����� ����� �����ϵ��� ��û�Ѵ�. 
	GAMEMSG_RESPONSE_LAND_DELAPPLYER,				//[����]

	//------------------------------
	// ���ڽ� ���� �޽���. 
	//------------------------------
	GAMEMSG_REQUEST_FEAST_RESERVE = 2600,			//[����] ��ȸ ���� ��û�� �Ѵ� 
	GAMEMSG_RESPONSE_FEAST_RESERVE,					//[����]

	GAMEMSG_REQUEST_FEAST_SETCOST,					//[����] ���� �����Ѵ� 
	GAMEMSG_RESPONSE_FEAST_SETCOST,					//[����]

	GAMEMSG_REQUEST_FEAST_ADDPRESENTLIST,			//[����] ���� ����� �߰��Ѵ� 
	GAMEMSG_RESPONSE_FEAST_ADDPRESENTLIST,			//[����]

	GAMEMSG_REQUEST_FEAST_DELPRESENTLIST,			//[����] ���� ����� �����Ѵ� 
	GAMEMSG_RESPONSE_FEAST_DELPRESENTLIST,			//[����]

	GAMEMSG_REQUEST_FEAST_STGITEMIN,				//[����] â�� �������� �ִ´� 
	GAMEMSG_RESPONSE_FEAST_STGITEMIN,				//[����]

	GAMEMSG_REQUEST_FEAST_STGITEMOUT,				//[����] â���� �������� ����
	GAMEMSG_RESPONSE_FEAST_STGITEMOUT,				//[����]

	GAMEMSG_REQUEST_FEAST_GIVEITEM,					//[����] ��ȸ ��û�ڰ� �������� �����Ѵ�
	GAMEMSG_RESPONSE_FEAST_GIVEITEM,				//[����]

	GAMEMSG_REQUEST_FEAST_SENDCHAT,					//[����] ������ ���� ����鿡�� ������ �Ѵ�.

	//#if defined(_LEON_FEAST_EFFECT)
	GAMEMSG_REQUEST_FEAST_USEEFFECT,					//[�뷡] ��ȸ �� ������ ���� ����� ����Ʈ�� �Ѹ���.
	GAMEMSG_RESPONSE_FEAST_USEEFFECT,					//[�뷡] 
	//#endif

	GAMEMSG_REQUEST_PARTYHALL_TOTAL_INFO,						//[����] ��ƼȦ. ��ü ���� ���. C->S => 2008. 3. 17
	GAMEMSG_RESPONSE_PARTYHALL_TOTAL_INFO,						//[����] ��ƼȦ. ��ü ���� ���. S->C => 2008. 3. 17

	GAMEMSG_REQUEST_PARTYHALL_RESERVATION,						//[����] ��ƼȦ. ��Ƽ���� ���. C->S => 2008. 3. 11		
	GAMEMSG_RESPONSE_PARTYHALL_RESERVATION,						//[����] ��ƼȦ. ��Ƽ���� ���. S->C => 2008. 3. 11	

	GAMEMSG_REQUEST_PARTYHALL_ADD_PRESENT,						//[����] ��ƼȦ. ���� ���. C->S => 2008. 3. 11
	GAMEMSG_RESPONSE_PARTYHALL_ADD_PRESENT,						//[����] ��ƼȦ. ���� ���. S->C => 2008. 3. 11	

	GAMEMSG_REQUEST_PARTYHALL_ENTRANCE_APPLICATION,				//[����] ��ƼȦ. ���� ��û. C->S => 2008. 3. 11
	GAMEMSG_RESPONSE_PARTYHALL_ENTRANCE_APPLICATION,			//[����] ��ƼȦ. ���� ��û. S->C => 2008. 3. 11	

	GAMEMSG_REQUEST_PARTYHALL_ENTRANCE_APPLICATION_LIST,		//[����] ��ƼȦ. ���� ��û��. C->S => 2008. 3. 11
	GAMEMSG_RESPONSE_PARTYHALL_ENTRANCE_APPLICATION_LIST,		//[����] ��ƼȦ. ���� ��û��. S->C => 2008. 3. 11	

	GAMEMSG_REQUEST_PARTYHALL_GET_COSTUME,						//[����] ��ƼȦ. �� ���. C->S => 2008. 3. 11
	GAMEMSG_RESPONSE_PARTYHALL_GET_COSTUME,						//[����] ��ƼȦ. �� ���. S->C => 2008. 3. 11	

	GAMEMSG_REQUEST_PARTYHALL_ADD_DECORATION,					//[����] ��ƼȦ. ��Ĺ� �߰�. C->S => 2008. 3. 11
	GAMEMSG_RESPONSE_PARTYHALL_ADD_DECORATION,					//[����] ��ƼȦ. ��Ĺ� �߰�. S->C => 2008. 3. 11

	GAMEMSG_REQUEST_PARTYHALL_GIVEITEM,							//[����] ��ƼȦ. ��Ĺ� �߰�. C->S => 2008. 3. 19
	GAMEMSG_RESPONSE_PARTYHALL_GIVEITEM,						//[����] ��ƼȦ. ��Ĺ� �߰�. S->C => 2008. 3. 19

	GAMEMSG_REQUEST_PARTYHALL_EXIT,								//[����] ��ƼȦ. ��Ƽ�忡�� ������. C->S => 2008. 3. 19

	GAMEMSG_REQUEST_PARTYHALL_INVITATION,						//[����] ��ƼȦ. ��Ƽ�忡 �ʴ��ϱ�. C->S => 2008. 3. 23
	GAMEMSG_RESPONSE_PARTYHALL_INVITATION,						//[����] ��ƼȦ. ��Ƽ�忡 �ʴ��ϱ�. S->C => 2008. 3. 23

	GAMEMSG_REQUEST_PARTYHALL_USEEFFECT,						//[����] ��ƼȦ. ��Ƽ�� ����. C->S => 2008. 3. 28
	GAMEMSG_RESPONSE_PARTYHALL_USEEFFECT,						//[����] ��ƼȦ. ��Ƽ�� ����. S->C => 2008. 3. 28

	GAMEMSG_RESPONSE_PARTYHALL_DECORATION_LIST,
	//------------------------------
	// �񺯻� ���� �޽���. 
	//------------------------------
	GAMEMSG_REQUEST_SUMMONHEROMARKET_CANCELORDER = 2700,		//[����] �ֹ��� ����Ѵ� 
	GAMEMSG_RESPONSE_SUMMONHEROMARKET_CANCELORDER,				//[����]

	GAMEMSG_REQUEST_SUMMONHEROMARKET_MYORDER,					//[����] �� �ֹ� ������ ���´� 
	GAMEMSG_RESPONSE_SUMMONHEROMARKET_MYORDER,					//[����]

	GAMEMSG_REQUEST_SUMMONHEROMARKET_ORDERLIST,					//[����] �ֹ� ����Ʈ�� ���´� 
	GAMEMSG_RESPONSE_SUMMONHEROMARKET_ORDERLIST,				//[����]

	GAMEMSG_REQUEST_SUMMONHEROMARKET_SELL,						//[����] ���� �ֹ��� �Ѵ�
	GAMEMSG_RESPONSE_SUMMONHEROMARKET_SELL,						//[����]

	GAMEMSG_REQUEST_SUMMONHEROMARKET_BUY,						//[����] ���� �ֹ��� �Ѵ� 
	GAMEMSG_RESPONSE_SUMMONHEROMARKET_BUY,						//[����]

	GAMEMSG_REQUEST_SUMMONHEROMARKET_SETFEE,					//[����] ������ �����Ѵ� 

	//------------------------------
	// ���� ���� �޽���. 
	//------------------------------
	GAMEMSG_REQUEST_MINE_CHANGECONTRACT  = 2800,	//[����] ���� ��� ������ �����Ѵ�. 

	GAMEMSG_REQUEST_MINE_UNITLIST,					//[����] ���� ����Ʈ�� ����Ʈ�� ��û�Ѵ�. (�Ϲ��� ������ ��� ) 
	GAMEMSG_RESPONSE_MINE_UNITLIST,					//[����] 

	GAMEMSG_REQUEST_MINE_UNITDETAIL,				//[����] ���� ����Ʈ�� �� ���� ����Ʈ�� ��û�Ѵ�. (����� ��� ) 
	GAMEMSG_RESPONSE_MINE_UNITDETAIL,				//[����] 

	GAMEMSG_REQUEST_MINE_APPLYERLIST,				//[����] ���� ���� ����� ����Ʈ�� ��û�Ѵ�.	
	GAMEMSG_RESPONSE_MINE_APPLYERLIST,				//[����]

	GAMEMSG_REQUEST_MINE_RENTAPPLY,					//[����] ���� ���� ��û�� ��û�Ѵ�. 	
	GAMEMSG_RESPONSE_MINE_RENTAPPLY,				//[����]

	GAMEMSG_REQUEST_MINE_CANCELAPPLY,				//[����] ���� �Ӵ� ��û ��� ��û. 
	GAMEMSG_RESPONSE_MINE_CANCELAPPLY,				//[����]

	GAMEMSG_REQUEST_MINE_RENT,						//[����] ���긦 �Ӵ��� ���� ��û�Ѵ�. (���)
	GAMEMSG_RESPONSE_MINE_RENT,

	GAMEMSG_REQUEST_MINE_DELAPPLYER,				//[����] ���� ���� ����� ����� �����ϵ��� ��û�Ѵ�. 
	GAMEMSG_RESPONSE_MINE_DELAPPLYER,				//[����]

	//-------------------------------------
	// Guild
	//-------------------------------------
	GAMEMSG_REQUEST_GUILD_CREATEGUILD	= 2900,		//[�ؿ�] ��� ������ ��û�Ѵ�.
	GAMEMSG_RESPONSE_GUILD_CREATEGUILD,

	GAMEMSG_REQUEST_GUILD_DESTROYGUILD,				//[�ؿ�] ��� ��ü�� ��û�Ѵ�.
	GAMEMSG_RESPONSE_GUILD_DESTROYGUILD,

	GAMEMSG_REQUEST_GUILD_JOINGUILD,				//[�ؿ�] ��� ������ ��û�Ѵ�.
	GAMEMSG_RESPONSE_GUILD_JOINGUILD,

	GAMEMSG_REQUEST_GUILD_CONFIRMJOINGUILD,			//[�ؿ�] ��� ������ �㰡�Ѵ�.
	GAMEMSG_RESPONSE_GUILD_CONFIRMJOINGUILD,

	GAMEMSG_REQUEST_GUILD_LEAVEGUILD,				//[�ؿ�] ��� Ż�� ��û�Ѵ�.
	GAMEMSG_RESPONSE_GUILD_LEAVEGUILD,

	GAMEMSG_REQUEST_GUILD_CHANGEVILLAGE,			//[�ؿ�] ��� ������ �̵��� ��û�Ѵ�.
	GAMEMSG_RESPONSE_GUILD_CHANGEVILLAGE,

	GAMEMSG_REQUEST_GUILD_GETGUILDLIST,				//[�ؿ�] ��� ����Ʈ�� �ҷ��´�.
	GAMEMSG_RESPONSE_GUILD_GETGUILDLIST,

	GAMEMSG_REQUEST_GUILD_GETGUILDINFO,				//[�ؿ�] Ư�� ����� ������ �ҷ��´�.
	GAMEMSG_RESPONSE_GUILD_GETGUILDINFO,

	GAMEMSG_REQUEST_GUILD_CONFIRMCREATEGUILD,		//[�ؿ�] ��� ������ �㰡�Ѵ�.
	GAMEMSG_RESPONSE_GUILD_CONFIRMCREATEGUILD,

	GAMEMSG_REQUEST_GUILD_SETSECONDMASTER,			//[�ؿ�] �α������ �����Ѵ�.
	GAMEMSG_RESPONSE_GUILD_SETSECONDMASTER,

	GAMEMSG_REQUEST_GUILD_GIVEGUILDMONEY,			//[�ؿ�] ��� �ڱ��� �����Ѵ�.
	GAMEMSG_RESPONSE_GUILD_GIVEGUILDMONEY,

	GAMEMSG_REQUEST_GUILD_SETSTRFEERATE,			//[�ؿ�] ��� �ǹ� �����Ḧ �����Ѵ�. - ���
	GAMEMSG_RESPONSE_GUILD_SETSTRFEERATE,

	GAMEMSG_REQUEST_GUILD_CHANGESTATUS,				//[�ؿ�] ��� �ɷ�ġ�� �����Ѵ�.
	GAMEMSG_RESPONSE_GUILD_CHANGESTATUS,

	GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS,			//[�ؿ�] ��� �ɷ�ġ�� �������� �˷��ش�.

	GAMEMSG_REQUEST_GUILD_SETMARK,					//[�ؿ�] ��ũ�� �����Ѵ�.
	GAMEMSG_RESPONSE_GUILD_SETMARK,

	GAMEMSG_REQUEST_GUILD_CHANGENAME,				//[�ؿ�] �̸��� �ٲ۴�.
	GAMEMSG_RESPONSE_GUILD_CHANGENAME,

	GAMEMSG_REQUEST_GUILD_CHANGEMASTER,				//[����] ��帶���� ����
	GAMEMSG_RESPONSE_GUILD_CHANGEMASTER,			

	GAMEMSG_REQUEST_GUILDWAR_RESERVELIST,			//[����] ����� �� ���� ����Ʈ
	GAMEMSG_RESPONSE_GUILDWAR_RESERVELIST,			

	GAMEMSG_REQUEST_GUILDWAR_APPLYRESERVE,			//[����] ����� ���� ��û
	GAMEMSG_RESPONSE_GUILDWAR_APPLYRESERVE,			//[����] ����� ���� ��û

	GAMEMSG_RESPONSE_GUILDWAR_START,				//[����] ����� ���� �˸�
	GAMEMSG_RESPONSE_GUILDWAR_END,					//[����] ����� �� �˸�
	GAMEMSG_RESPONSE_GUILDWAR_KILLPOINT,			//[����] ����� KillPoint �˸�

	GAMEMSG_REQUEST_GUILDDUNGEON_APPLYLIST,			//[����] ����� ������ ��û�� ����Ʈ
	GAMEMSG_RESPONSE_GUILDDUNGEON_APPLYLIST,

	GAMEMSG_REQUEST_GUILDDUNGEON_APPLY,				//[����] ����� ������ ��û�ϱ�
	GAMEMSG_RESPONSE_GUILDDUNGEON_APPLY,

	GAMEMSG_REQUEST_GUILDDUNGEON_STATUS,			//[����] ����� ������ ��Ȳ
	GAMEMSG_RESPONSE_GUILDDUNGEON_STATUS,

	GAMEMSG_REQUEST_GUILD_MEMBERLIST,				//[����] ��� ��� ����Ʈ
	GAMEMSG_RESPONSE_GUILD_MEMBERLIST,

	GAMEMSG_REQUEST_GUILD_GETVILLAGELIST,			//[����] ��� �ǹ� �������ִ� ��������Ʈ
	GAMEMSG_RESPONSE_GUILD_GETVILLAGELIST,

	GAMEMSG_REQUEST_GUILDWAR_APPLYTOENEMY,			//[����] ��� ��忡�� ����� ��û(��û���->����)
	GAMEMSG_RESPONSE_GUILDWAR_APPLYTOENEMY,			//����->�����

	GAMEMSG_REQUEST_GUILDWAR_CONFIRMAPPLY,			//[����] �������û ���� ( �����->���� )
	GAMEMSG_RESPONSE_GUILDWAR_CONFIRMAPPLY,			//����->��û���

	GAMEMSG_REQUEST_GUILDWAR_RECOMMANDLIST,			//[����] ��õ��� ��� ��û
	GAMEMSG_RESPONSE_GUILDWAR_RECOMMANDLIST,

	//GAMEMSG_RESPONSE_GUILD_CLOSEGUILD,			//[����] ���� ���(��� ��ɾ�)

	/*	GAMEMSG_REQUEST_GUILD_APPLYWAR,					//[�ؿ�] �������� ��û�Ѵ�.
	GAMEMSG_RESPONSE_GUILD_APPLYWAR,

	GAMEMSG_REQUEST_GUILD_CONFIRMWAR,				//[�ؿ�] ������ ���� ���θ� �����Ѵ�.
	GAMEMSG_RESPONSE_GUILD_CONFIRMWAR,

	GAMEMSG_RESPONSE_GUILD_STARTWAR,				//[�ؿ�] �������� ���۵Ǿ���

	GAMEMSG_REQUEST_GUILD_GETHUNTINGMAP,			//[�ؿ�] ��忡 ����͸� �ͼӽ�Ų��.
	GAMEMSG_RESPONSE_GUILD_GETHUNTINGMAP,

	GAMEMSG_REQUEST_GUILD_APPLYWARMEMBER,			//[�ؿ�] ������� ������û�Ѵ�.
	GAMEMSG_RESPONSE_GUILD_APPLYWARMEMBER,

	GAMEMSG_REQUEST_GUILD_CONFIRMWARMEMBER,			//[�ؿ�] ����� ���� ��û�� �㰡 �� �����Ѵ�.
	GAMEMSG_RESPONSE_GUILD_CONFIRMWARMEMBER,

	GAMEMSG_REQUEST_GUILD_CONFIRMSTARTWAR,			//[�ؿ�] ����� ���۽� �����ϰڴٰ� �뺸
	GAMEMSG_RESPONSE_GUILD_CONFIRMSTARTWAR,*/

	//----------------------------
	// �ε��� ���� �޽��� 
	//----------------------------
	GAMEMSG_RESPONSE_REALESTATE	= 5000,			//[�°�] Person�� �ε��� ������ �뺸�Ѵ�. 

	GAMEMSG_REQUEST_EXTENDCONTRACT,				//[�°�] �ε��� ��� ���� ��û. 


	//--------------------------
	// �ǹ� ���� �޽���. 
	//--------------------------
	GAMEMSG_REQUEST_STRINFO	= 5100,			//[�°�] �ǹ��� ���� ������ ��û�Ѵ�. 
	GAMEMSG_RESPONSE_STRINFO,				//[�°�] �ǹ��� ���� ������ �뺸�Ѵ�. 

	GAMEMSG_REQUEST_GETTAXLIST,				//[����]
	GAMEMSG_RESPONSE_GETTAXLIST,			//[����]

	GAMEMSG_REQUEST_SETTAX,					//[����]
	GAMEMSG_RESPONSE_SETTAX,				//[����]

	GAMEMSG_REQUEST_PAYTAX,					//[����]
	GAMEMSG_RESPONSE_PAYTAX,				//[����]

	GAMEMSG_REQUEST_GETDIVIDENDLIST,		//[����]	
	GAMEMSG_RESPONSE_GETDIVIDENDLIST,		//[����]

	GAMEMSG_REQUEST_DECLAREWAR,				//[����]
	GAMEMSG_RESPONSE_DECLAREWAR,			//[����]

	GAMEMSG_REQUEST_CANCELDECLAREWAR,		//[����]
	GAMEMSG_RESPONSE_CANCELDECLAREWAR,		//[����]

	GAMEMSG_RESPONSE_VILLAGEWARRESULT,		//[����]
	GAMEMSG_RESPONSE_ENDVILLAGEWAR,			//[����]

	GAMEMSG_REQUEST_RESIDENTSHARE,			//[����]
	GAMEMSG_RESPONSE_RESIDENTSHARE,			//[����]

	// �ֹ� ��û�� ����Ʈ�� ������Ʈ �Ѵ�(��ϵǰų� ������ ���� �����)
	GAMEMSG_RESPONSE_UPDATERESIDENTAPPLYERLIST,	//[����]

	GAMEMSG_REQUEST_SETSTRUCTUREMESSAGE,		//[����]
	GAMEMSG_RESPONSE_SETSTRUCTUREMESSAGE,		//[����]

	GAMEMSG_REQUEST_GETSTRNOTICE,				//[����]
	GAMEMSG_RESPONSE_GETSTRNOTICE,				//[����]

	GAMEMSG_RESPONSE_LIST_DELETEALL,			//[����]
	GAMEMSG_RESPONSE_LIST_DELITEM,				//[����]

	GAMEMSG_REQUEST_NPCPAYMENT,					//[����]
	GAMEMSG_RESPONSE_NPCPAYMENT,				//[����]

	GAMEMSG_REQUEST_VILLAGEINFOSTRINFO,			//[�°�] ���� �� �����߿��� Ư�� �ǹ��� ������ ��û�Ѵ�. 
	GAMEMSG_RESPONSE_VILLAGEINFOSTRINFO,		//[�°�]

	GAMEMSG_REQUEST_CHIEFINFO,					//[�°�] ������ Chief�� ���� ������ ��û. 
	GAMEMSG_RESPONSE_CHIEFINFO,					//[�°�] ������ Chief����  ���� ����. 

	GAMEMSG_REQUEST_REPAIRSTRUCTURE,			//[����] ���� �ǹ��� �����Ѵ� 
	GAMEMSG_RESPONSE_REPAIRSTRUCTURE,			//[����]

	GAMEMSG_REQUEST_VILLAGEBOARD,				//[�ؿ�] ���� �Խ����� ��û�Ѵ�.
	GAMEMSG_RESPONSE_VILLAGEBOARD,				//[�ؿ�]

	GAMEMSG_REQUEST_HIREEVENTNPC,				//[����] �̺�Ʈ NPC����� ��û�Ѵ�.
	GAMEMSG_RESPONSE_HIREEVENTNPC,

	GAMEMSG_REQUEST_EVENT_INSERTMATERIAL,		//[����] ����� �̺�Ʈ ��� �ֱ�.
	GAMEMSG_RESPONSE_EVENT_INSERTMATERIAL,

	GAMEMSG_REQUEST_EVENT_MATERIALLIST,			//[����] ����� �̺�Ʈ ��� ���� ����
	GAMEMSG_RESPONSE_EVENT_MATERIALLIST,

	GAMEMSG_REQUEST_EVENT_MATERIALCOMPLETE,		//[����] ����� �̺�Ʈ ��� �ϼ�
	GAMEMSG_RESPONSE_EVENT_MATERIALCOMPLETE,

	GAMEMSG_RESPONSE_EVENT_COMPLETEBUILD,		//[����] ����� �̺�Ʈ �ϼ� �޽���

	//--------------------------
	// �ý��� NPC
	//--------------------------
	GAMEMSG_REQUEST_SELLNPC = 5200,				//[���] NPC���� �Ǹ����� ��û�Ѵ�. 
	GAMEMSG_RESPONSE_SELLNPC,					//[���]

	GAMEMSG_REQUEST_BUYNPC,						//[���] NPC���Լ� ������� ��û�Ѵ�. 
	GAMEMSG_RESPONSE_BUYNPC,					//[���]

	GAMEMSG_REQUEST_NPCSELLITEMINFO,			//[���] NPC(������) �� �Ǹ��ϴ� ������ ������ ��û
	GAMEMSG_RESPONSE_NPCSELLITEMINFO,			//[���]

	GAMEMSG_REQUEST_NPCPOS,						//[�°�] NPC��ġ ���� ��û. 
	GAMEMSG_RESPONSE_NPCPOS,					//[�°�]

	GAMEMSG_REQUEST_INVESTMENTGETINFO,			//[�ؿ�] ���ڻ�㰡(���� �輱��) ���� ��û
	GAMEMSG_RESPONSE_INVESTMENTGETINFO,

	GAMEMSG_REQUEST_GETRECOMMANDPOINT,			//[����] ������ �ִ� ��õ ����Ʈ�� ��� �´�
	GAMEMSG_RESPONSE_GETRECOMMANDPOINT,

	GAMEMSG_REQUEST_BUYRECOMMANDPRODUCT,			//[����] ��õ����Ʈ[RP]�� �������� ����
	GAMEMSG_RESPONSE_BUYRECOMMANDPRODUCT,

	GAMEMSG_REQUEST_RECOMMANDPOINTLIST,			//[����] �ڽ��� ��õ�� ������ ����� ������
	GAMEMSG_RESPONSE_RECOMMANDPOINTLIST,

	GAMEMSG_REQUEST_VILLAGEHAVEEVENTNPC,			//[����] �ڽ��� ������ �̺�ƮNPC�� �ִ��� �˷���
	GAMEMSG_RESPONSE_VILLAGEHAVEEVENTNPC,

	GAMEMSG_REQUEST_MANUFACTURENPC,
	GAMEMSG_REQUEST_RECEIVEBEGINNERITEM,


	//-------------------------
	// ���� ����(û, �Ϻ�) NPC ���� �ŷ�
	//-------------------------
	GAMEMSG_REQUEST_SELLTOFOREIGNMERCHANT = 5300,	//[���] ���� ���� NPC���� �ǸŸ� ��û

	GAMEMSG_REQUEST_FOREIGNMERCHANTNPCBUYINFO,		//[���] ���� ���� NPC �� �������� �����ۿ� ���� ������ ��û	
	GAMEMSG_RESPONSE_FOREIGNMERCHANTNPCBUYINFO,		//[���]

	GAMEMSG_REQUEST_FOREIGNMERCHANTBUYCASHITEMINFO,	//[���] ���� ������ �����ϴ� ĳ�� ������ ���� ��û
	GAMEMSG_RESPONSE_FOREIGNMERCHANTBUYCASHITEMINFO,	//[���]

	GAMEMSG_REQUEST_FOREIGNMERCHANTBUYCASHITEM,		//[���] ���� ������ ĳ�� ������ ����
	GAMEMSG_RESPONSE_FOREIGNMERCHANTBUYCASHITEM,	//[���]


	GAMEMSG_REQUEST_TRADEMERCHANTBUYINFO,			//[���] ���� ������ �����ϴ� ������ ��û
	GAMEMSG_RESPONSE_TRADEMERCHANTBUYINFO,			//[���]

	GAMEMSG_REQUEST_TRADEMERCHANTBUYITEMFROMPERSON,	//[���] ���� ������ ��ǰ�� ����
	GAMEMSG_RESPONSE_TRADEMERCHANTBUYITEMFROMPERSON,//[���]


	GAMEMSG_REQUEST_TRADEMERCHANTHORSEBUYINFO,		//[���] ������ ���� �����ϴ� ������ ��û
	GAMEMSG_RESPONSE_TRADEMERCHANTHORSEBUYINFO,		//[���]

	GAMEMSG_REQUEST_TRADEMERCHANTBUYHORSEFROMPERSON,//[���] ������ ���� ����
	GAMEMSG_RESPONSE_TRADEMERCHANTBUYHORSEFROMPERSON,//[���]

	GAMEMSG_REQUEST_TRADEMERCHANTBUYITEMINFO,		//[���] ������ ������ �����ϴ� ������ ��û
	GAMEMSG_RESPONSE_TRADEMERCHANTBUYITEMINFO,		//[���]

	GAMEMSG_REQUEST_TRADEMERCHANTBUYITEM,			//[���] ������ ������ ����
	GAMEMSG_RESPONSE_TRADEMERCHANTBUYITEM,			//[���]

	//-------------------------
	// �ֽ� ����
	//-------------------------
	GAMEMSG_RESPONSE_STOCKDISTRIBUTIONSET,			//[���] �ֽ� ���� �˸�

	GAMEMSG_REQUEST_STOCKDISTRIBUTIONORDER,			//[���]
	GAMEMSG_RESPONSE_STOCKDISTRIBUTIONORDER,		//[���]

	GAMEMSG_REQUEST_GETBEGINNERVILLAGESTOCK,		// [����] �ʺ��� ������ �ֽ��� �޶�� ��û

	//-------------------------
	// ���ΰ� �ŷ�
	//-------------------------
	GAMEMSG_REQUEST_PRIVATETRADE = 5400,		//[���] ���� �ŷ��� ��û�Ѵ�.
	GAMEMSG_RESPONSE_PRIVATETRADE,				//[���] ���� �ŷ� ��û�� ���� ����.

	GAMEMSG_REQUEST_PRIVATETRADE_ACCEPT,		//[����] ���� �ŷ� ���� ��û
	GAMEMSG_RESPONSE_PRIVATETRADE_ACCEPT,		//[����] ���� �ŷ� ���� ��û�� ���� ����

	GAMEMSG_REQUEST_PRIVATETRADE_CANCEL,		//[���] ���� �ŷ��� ����Ѵ�.
	GAMEMSG_RESPONSE_PRIVATETRADE_CANCEL,		//[���] ���� �ŷ� ��ҿ� ���� ����.

	GAMEMSG_REQUEST_PRIVATETRADE_ADDITEM,		//[���] �������� �ŷ��Ѵ�.
	GAMEMSG_RESPONSE_PRIVATETRADE_ADDITEM,

	GAMEMSG_REQUEST_PRIVATETRADE_DELLIST,		//[���] �ŷ� ��Ͽ��� �����Ѵ�.
	GAMEMSG_RESPONSE_PRIVATETRADE_DELLIST,

	GAMEMSG_REQUEST_PRIVATETRADE_DELITEM,		//[���] �ŷ� ��Ͽ��� �����۸� �����Ѵ�.
	GAMEMSG_RESPONSE_PRIVATETRADE_DELITEM,

	GAMEMSG_REQUEST_PRIVATETRADE_ADDPRICE,		//[���] ���� �ŷ��Ѵ�.
	GAMEMSG_RESPONSE_PRIVATETRADE_ADDPRICE,

	GAMEMSG_REQUEST_PRIVATETRADE_ADDSTOCK,		//[���] �ֽ��� �ŷ��Ѵ�.
	GAMEMSG_RESPONSE_PRIVATETRADE_ADDSTOCK,

	GAMEMSG_REQUEST_PRIVATETRADE_ADDHOUSEUNIT,	//[���] ������ �ŷ��Ѵ�.
	GAMEMSG_RESPONSE_PRIVATETRADE_ADDHOUSEUNIT,

	GAMEMSG_REQUEST_PRIVATETRADE_ADDHORSE,		//[���] ���� �ŷ��Ѵ�.
	GAMEMSG_RESPONSE_PRIVATETRADE_ADDHORSE,

	GAMEMSG_REQUEST_PRIVATETRADE_MYACCEPT,		//[���] ���� �ŷ����� �� ����� ���� 
	GAMEMSG_RESPONSE_PRIVATETRADE_MYACCEPT,		//[���] ���� �ŷ����� �� ����� ���� ����

	GAMEMSG_REQUEST_PRIVATETRADE_MYCANCEL,		//[���] ���� �ŷ����� �� ����� ���
	GAMEMSG_RESPONSE_PRIVATETRADE_MYCANCEL,		//[���] ���� �ŷ����� �� ����� ��� ����

	GAMEMSG_RESPONSE_PRIVATETRADE_OTHERACCEPT,	//[���] ���� �ŷ����� ������ ����� ���� ������ �˸�
	GAMEMSG_RESPONSE_PRIVATETRADE_OTHERCANCEL,	//[���] ���� �ŷ����� ������ ����� ��� ������ �˸�

	GAMEMSG_RESPONSE_PRIVATETRADE_END,			//[���] ���� �ŷ� ����

	//--------------------------
	// �� 
	//--------------------------
	GAMEMSG_REQUEST_RIDEHORSE		= 5500,	//[�°�] ���� Ÿ��� ��û
	GAMEMSG_RESPONSE_RIDEHORSE,				//[�°�]

	GAMEMSG_REQUEST_UNRIDEHORSE,			//[�°�] ������ ������� ��û. 
	GAMEMSG_RESPONSE_UNRIDEHORSE,			//[�°�]

	GAMEMSG_REQUEST_HORSERELEASE,			//[�°�] ���� Ǯ���ش�. 

	GAMEMSG_REQUEST_HORSENAMECHANGE,		//[���] �� �̸� ����
	GAMEMSG_RESPONSE_HORSENAMECHANGE,		//[���]

	//-------------------------
	// ����Ʈ 
	//-------------------------
	GAMEMSG_REQUEST_SETQUESTGOING	= 5700,			//[�°�] ����Ʈ ���� ��û �޽���. 

	GAMEMSG_REQUEST_CANCELQUEST,					//[�°�] ����Ʈ ���. 

	GAMEMSG_REQUEST_QUESTSTATUS,					//[�°�] ����Ʈ ���� ��Ȳ�� ������ ������. 

	//-------------------------
	// �ӼӸ�
	//-------------------------
	GAMEMSG_REQUEST_WHISPERCHAT_CREATE,				//[���] �Ӹ��ϱ� ��û( ������ ���콺�� �ӼӸ� �ϱ� �Ǵ� '/t' �� �� ��� )
	GAMEMSG_RESPONSE_WHISPERCHAT_CREATE,			//[���] �Ӹ��ϱ� ��û�Ǿ����� �˷���.

	GAMEMSG_REQUEST_WHISPERCHAT_INVITE,				//[���] �ʴ� ��û
	GAMEMSG_RESPONSE_WHISPERCHAT_INVITE,			//[���] �ʴ� �Ǿ����� �˷���

	GAMEMSG_REQUEST_WHISPERCHAT_USERLIST,			//[���] �ӼӸ����� ������� ����Ʈ�� ��û
	GAMEMSG_RESPONSE_WHISPERCHAT_USERLIST,			//[���]

	GAMEMSG_REQUEST_WHISPERCHAT_OUT,				//[���] �ӼӸ����� ����
	GAMEMSG_RESPONSE_WHISPERCHAT_OUT,				//[���] �ӼӸ����� Ż�������� �˷���


	//-------------------------
	// ��Ƽ
	//-------------------------
	GAMEMSG_REQUEST_PARTY_CREATEINVITE = 5800,		//[���] ��Ƽ ���� �� �ʴ�( ��Ƽ ������ �� �� �ܰ���.. )
	GAMEMSG_RESPONSE_PARTY_CREATEINVITE,			//[���] ��Ƽ ���� �� �ʴ� ����( ��Ƽ ������ �� �� �ܰ���.. )

	GAMEMSG_REQUEST_PARTY_CREATEJOIN,				//[���] ��Ƽ ���� �� �ʴ뿡 ���ϰڴ�.
	GAMEMSG_RESPONSE_PARTY_CREATEJOIN,				//[���] ��Ƽ���� �� ������� ��Ƽ ������ �˸�

	GAMEMSG_REQUEST_PARTY_INVITE,					//[���] ��Ƽ �ʴ� ��û
	GAMEMSG_RESPONSE_PARTY_INVITE,					//[���] ��Ƽ �ʴ� ����

	GAMEMSG_REQUEST_PARTY_INVITEREJECT,				//[���] ��Ƽ �ʴ� ���� ( ��Ƽ �ʴ��� -> ���� )
	GAMEMSG_RESPONSE_PARTY_INVITEREJECT,			//[���] ��Ƽ �ʴ� ���� ( ���� -> ��Ƽ�� )

	GAMEMSG_REQUEST_PARTY_JOIN,						//[���] ��Ƽ ���� ��û
	GAMEMSG_RESPONSE_PARTY_JOIN,					//[���] ��Ƽ ���� ����

	GAMEMSG_REQUEST_PARTY_LEAVE,					//[���] ��Ƽ Ż�� ��û
	GAMEMSG_REQUEST_PARTY_FORCELEAVE,				//[���] ��Ƽ ���� ���� ��û	

	GAMEMSG_REQUEST_PARTY_ALLUSERLIST,				//[���] ��Ƽ ���� ����Ʈ ���� ��û
	//[���] ������ GAMEMSG_RESPONSE_PARTY_ADDUSER �̰��� ���� ���鼭 �� ����

	GAMEMSG_RESPONSE_PARTY_DELETE,					//[���] ��Ƽ ���� �˸�

	GAMEMSG_RESPONSE_PARTY_ADDUSER,					//[���] ��Ƽ ���� �߰� �˸�
	GAMEMSG_RESPONSE_PARTY_DELUSER,					//[���] ��Ƽ ���� Ż�� �˸�
	GAMEMSG_RESPONSE_PARTY_FORCEDELUSER,			//[���] ��Ƽ ���� ���� Ż�� �˸� (��Ƽ�忡 ���� ��)

	GAMEMSG_RESPONSE_PARTY_CHANGELEADER,			//[���] ��Ƽ�� ���� �˸��� ���ؼ�.

	GAMEMSG_REQUEST_PARTY_CHANGETITLE,				//[���] ��Ƽ �̸� ����
	GAMEMSG_RESPONSE_PARTY_CHANGETITLE,		

	GAMEMSG_RESPONSE_PARTY_NOTIFYEXP,				//[���] ����ġ ���� ���� �˸�

	GAMEMSG_REQUEST_PARTY_CHANGEITEMGETPATTERN,		//[����] ��Ƽ ������ ȹ�� ��� ����
	GAMEMSG_RESPONSE_PARTY_CHANGEITEMGETPATTERN,	//[����] ��Ƽ ������ ȹ�� ��� ����

	GAMEMSG_RESPONSE_PARTY_NOTIFYITEMGET,			//[����] ��Ƽ���� ������ ȹ�� �˸�

	GAMEMSG_RESPONSE_PARTY_PARTYUSERPOS,			//[����] ��Ƽ���� ��ġ�� ����ɶ����� ��Ƽ���鿡�� x, y, mapindex �� �����ش�.

	GAMEMSG_RESPONSE_PARTY_NOTIFYLEVELUP,			//[����] ��Ƽ���� ������ �� ��Ƽ���鿡�� �˷��ش�.

	// [����] ��Ƽ��Ī���� ���� �޼��� �߰�
	GAMEMSG_REQUEST_PARTY_WANTJOIN,					//[����] ������ ���忡�� ��Ƽ ������ ��û (Ŭ��->����)
	GAMEMSG_RESPONSE_PARTY_WANTJOIN,				//[����] ������ ���� ������ ��Ƽ ���� ��û�� ���� Ŭ�󿡰� ���� (����->Ŭ��)

	GAMEMSG_REQUEST_PARTY_WANTJOINRESULT,			//[����] ������ ��Ƽ ���� ��û�� ���� ������ ������ ������ ���� (Ŭ��->����)
	GAMEMSG_RESPONSE_PARTY_WANTJOINRESULT,			//[����] ������ ���� ������ ��Ƽ ���� ��û�� ���� ������ ��û ���� Ŭ�� ���� (����->Ŭ��)


	//-------------------------
	// ��� ���� 
	//-------------------------
	GAMEMSG_RESPONSE_GAMEMASTERLEVEL	= 5900,	//[�°�] ��� ���ѿ� ���� ������ ������. 

	GAMEMSG_RESPONSE_GMGIVEMONEY,				//[�°�] ��ڰ� ���� �� �Ϳ� ���� ���. 

	GAMEMSG_REQUEST_PERSONAL_LOG,				//[�ؿ�] ��ڰ� ������� �α׸� ��û�Ѵ�.
	GAMEMSG_RESPONSE_PERSONAL_LOG,

	//	GAMEMSG_RESPONSE_ITEMINFOGET,				//[�ؿ�] �������� ������ ���´�. ����ũ �� ���̳ʸ���

	GAMEMSG_REQUEST_GETGAMEMASTER_SERVERINFO,	//[�ؿ�] ������ ���¸� ���´�.
	GAMEMSG_RESPONSE_GETGAMEMASTER_SERVERINFO,

	GAMEMSG_RESPONSE_NOTICEADMIN,				//[�ؿ�] �߿��� ������ �Ѵ�.
	GAMEMSG_RESPONSE_GMGIVERECOMMANDPOINT,		//[����] ��ڰ� FP�� �� �Ϳ� ���� ���.

	//-------------------------
	// �� 
	//-------------------------
	GAMEMSG_RESPONSE_NEWS	= 6000,				//[�°�]�Ź� ���� �뺸. 

	GAMEMSG_REQUEST_MYPUCHIKOMIURL,				//[����] �ڽ��� �α��ε� Ǫġ�ڹ� �ּҸ� �˾ƿ´�.
	GAMEMSG_RESPONSE_MYPUCHIKOMIURL,

	GAMEMSG_REQUEST_USERPUCHIKOMIURL,			//[����] �ٸ������� Ǫġ�ڹ� �ּҸ� �˾ƿ´�.
	GAMEMSG_RESPONSE_USERPUCHIKOMIURL,


	//-------------------------
	// ģ��
	//-------------------------
	GAMEMSG_REQUEST_FRIENDADD = 6200,			//6200 [���] ģ�� �߰� ��û
	GAMEMSG_RESPONSE_FRIENDADD,					//6201 [���]

	GAMEMSG_REQUEST_FRIENDADDACCEPT,			//6202 [���] ģ�� �߰� ���� ��û
	GAMEMSG_RESPONSE_FRIENDADDACCEPT,			//6203 [���]

	GAMEMSG_REQUEST_REJECTFRIENDADD,			//6204 [����] ģ�� �߰� �ź�

	GAMEMSG_REQUEST_FRIENDDEL,					//6205 [���] ģ�� ���� ��û
	GAMEMSG_RESPONSE_FRIENDDEL,					//6206 [���]

	GAMEMSG_RESPONSE_FRIENDLOGIN,				//6207 [���] ģ�� �α��� �˸�
	GAMEMSG_RESPONSE_FRIENDLOGOUT,				//6208 [���] ģ�� �α׾ƿ� �˸�

	GAMEMSG_REQUEST_FRIENDLIST,					//6209 [����] ģ�� ����Ʈ ��û
	GAMEMSG_RESPONSE_FRIENDLIST,				//6210 [����]

	GAMEMSG_REQUEST_FRIENDMEMO,					//6211 [����] ģ�� �޸� ��û
	GAMEMSG_RESPONSE_FRIENDMEMO,				//6212 [����]

	GAMEMSG_REQUEST_FRIENDMEMOSET,				//6213 [����] ģ�� �޸� ����
	GAMEMSG_RESPONSE_FRIENDMEMOSET,				//6214 [����]

	GAMEMSG_REQUEST_FRIENDCHANGEGROUP,			//6215 [����] ģ�� �׷� ����
	GAMEMSG_RESPONSE_FRIENDCHANGEGROUP,			//6216 [����]

	GAMEMSG_REQUEST_FRIENDCHANGEGROUPNAME,		//6217 [����] ģ�� �׷� �̸� ����
	GAMEMSG_RESPONSE_FRIENDCHANGEGROUPNAME,		//6218 [����]

	GAMEMSG_RESPONSE_FRIENDALLLIST,				//6219 [����] ģ�� ��ü ����Ʈ

	//-------------------------
	// ��ǥ
	//-------------------------
	GAMEMSG_REQUEST_VOTEKINGAVAILABLE,			//6220 [����] ���� ��ǥ ����� �����޶�� ��û
	GAMEMSG_RESPONSE_VOTEKINGAVAILABLE,			//6221 [���] �� ��ǥ ���� �ϹǷ� ��ǥ�� �����϶�� �޽���. 

	GAMEMSG_REQUEST_VOTEKINGSELECTION,			//6222 [���] ��ǥ
	GAMEMSG_RESPONSE_VOTEKINGSELECTION,			//6223 [���] ��ǥ ��� ����

	GAMEMSG_RESPONSE_VOTEKINGAGGREGATE,			//6224 [����] ���� ��ǥ ���� ��� ����

	GAMEMSG_REQUEST_STARTELECTIONSTUMP,			//6225 [����] ���Žý��� : ��������
	GAMEMSG_RESPONSE_STARTELECTIONSTUMP,		//6226 

	GAMEMSG_REQUEST_ENDELECTIONSTUMP,			//6227 [����] ���Žý��� : ��������
	GAMEMSG_RESPONSE_ENDELECTIONSTUMP,			//6228 

	GAMEMSG_REQUEST_ELECTIONSTUMP,				//6229 [����] ���Žý��� : �ɸ��� ������ �ʱ�ȭ �Ǿ����� ���� ������ �ٽ� ����

	GAMEMSG_REQUEST_STARTVOTESTATUS,			//6230 [����] ���� ��ǥ ��Ȳ ����
	GAMEMSG_RESPONSE_STARTVOTESTATUS,			//6231 [����] ���� ��ǥ ��Ȳ ���۾˸�

	GAMEMSG_RESPONSE_VOTESTATUS,				//6232 [����] ���� ��ǥ ��Ȳ

	GAMEMSG_REQUEST_WARPTOPOLLMAP,				//6233 [����] ���� ��ǥ�� �������� �̵��϶�

	//-------------------------
	// Daily ����Ʈ
	//-------------------------	
	GAMEMSG_REQUEST_DAILYQUESTLIST,				// [���] ����Ʈ ����Ʈ ��û
	GAMEMSG_RESPONSE_DAILYQUESTLIST,			// [���]

	GAMEMSG_REQUEST_DAILYQUESTSELECT,			// [���] ����Ʈ ����
	GAMEMSG_RESPONSE_DAILYQUESTSELECT,			// [���]

	GAMEMSG_REQUEST_DAILYQUESTSITUATION,		// [���] ����Ʈ ��Ȳ
	GAMEMSG_RESPONSE_DAILYQUESTSITUATION,		// [���]

	GAMEMSG_RESPONSE_DAILYQUESTCHANGE,			// [���] ����Ʈ ���� �ð��� ���� �������� ������Ʈ ����.

	GAMEMSG_REQUEST_DAILYQUESTEND,				// [���] ����Ʈ ����
	GAMEMSG_RESPONSE_DAILYQUESTEND,				// [���]


	//---------------------------------
	// ��������
	//---------------------------------
	GAMEMSG_REQUEST_PROPOSE_QUESTION	= 6500,	// [����] �������� ����
	GAMEMSG_RESPONSE_PROPOSE_QUESTION,			// [����] 

	GAMEMSG_REQUEST_PROPOSE_ANSWER,				// [����] �������� �亯

	GAMEMSG_RESPONSE_SET_MARRY,					// [����] ��ȥ �ߴ�

	GAMEMSG_RESPONSE_GET_MARRY_INFO,			// [����] ��ȥ���� ���� ���

	GAMEMSG_REQUEST_WEDDINGANNIVERSARY_ITEMGET,	// [����] ��ȥ ����� ������ �ޱ� ��û
	GAMEMSG_RESPONSE_MARRY_ITEMGET_SET,			// [����] ��ȥ ����� ������ ���� ��¥�� �����Ѵ�
	GAMEMSG_RESPONSE_MARRY_LOVE_SET,			// [����] ��ȥ ������ ���� ����


	//---------------------------------
	// ItemMall
	//---------------------------------
	GAMEMSG_REQUEST_ITEMMALLEXISTENCE = 6800,	//[�ؿ�] ������ ������ �� �������� ������ ��û�Ѵ�.
	GAMEMSG_RESPONSE_ITEMMALLEXISTENCE,

	GAMEMSG_REQUEST_ITEMMALLITEMLIST,			//[�ؿ�] ������ ������ �� �������� ������ ��û�Ѵ�.
	GAMEMSG_RESPONSE_ITEMMALLITEMLIST,

	GAMEMSG_REQUEST_ITEMMALLGETITEM,			//[�ؿ�] ������ ������ �� �������� �κ��丮�� �ű��.
	GAMEMSG_RESPONSE_ITEMMALLGETITEM,

	GAMEMSG_REQUEST_INITSTATUS,					//[�ؿ�] �����ʱ�ȭ�̿���� ����Ͽ� �������ͽ� �ʱ�ȭ ��û

	GAMEMSG_REQUEST_HUNTMAPWARP,				//[�ؿ�] �����̵��̿���� �̿��Ͽ� ����ͷ� �̵��Ѵ�.

	GAMEMSG_REQUEST_PERSONALSHOPWARP,			//[����] �����̵��̿���� �̿��Ͽ� ���λ������� �̵��Ѵ�.

	GAMEMSG_REQUEST_FRIENDWARP,					//[����] �����̵��̿���� �̿��Ͽ� ģ�����Է� �̵��Ѵ�.

	GAMEMSG_REQUEST_PARTYWARP,					//[�ؿ�] ��Ƽ������ �̵��Ѵ�.

	GAMEMSG_REQUEST_HORSEINIT,					//[�ؿ�] �������ʱ�ȭ�̿���� ����Ͽ� ���� �������ͽ� �ʱ�ȭ ��û

	GAMEMSG_REQUEST_USEHORSE_BONUS,				//[�ؿ�] ���� ���ʽ��� �̿��Ͽ� �ɷ�ġ�� �ø���.

	GAMEMSG_REQUEST_CHANGE_HORSETYPE,			//[�ؿ�] ���� ǰ���� �ٲ۴�.

	GAMEMSG_REQUEST_CHANGE_CHARNAME,			//[�ؿ�] ĳ���� �̸��� �����Ѵ�.
	GAMEMSG_RESPONSE_CHANGE_CHARNAME,

	GAMEMSG_REQUEST_CHANGE_CHARKIND,			//[�ؿ�] ĳ���� ������ �����Ѵ�.
	GAMEMSG_RESPONSE_CHANGE_CHARKIND,

	GAMEMSG_REQUEST_HORSE_ADDSTATUS,			//[�ؿ�] ���ɷ�����̿���� �̿��ؼ� ���ɷ��� ����Ų��.

	GAMEMSG_REQUEST_NOLIMITTICKET_WARP,			//[�ؿ�] �����̵����ױ��� �̿��ؼ� ���� ������ �����Ѵ�.(�Ⱓ��)
	GAMEMSG_RESPONSE_NOLIMITTICKET_WARP,

	GAMEMSG_REQUEST_GET_SEL_PGLIST,				//[�ؿ�] ��ǰ ��� �ҷ�����
	GAMEMSG_RESPONSE_GET_SEL_PGLIST,

	GAMEMSG_REQUEST_GET_ITEMMALL_ITEMINFO,		//[�ؿ�] ��ǰ�� ������ ��û�Ѵ�.
	GAMEMSG_RESPONSE_GET_ITEMMALL_ITEMINFO,

	GAMEMSG_REQUEST_GET_MYCASH_INFO,			//[�ؿ�] �� ĳ�� ������ ��û�Ѵ�.
	GAMEMSG_RESPONSE_GET_MYCASH_INFO,

	GAMEMSG_REQUEST_ITEMMALL_BUYITEM,			//[�ؿ�] ������ ������ ������ ���
	GAMEMSG_RESPONSE_ITEMMALL_BUYITEM,

	GAMEMSG_REQUEST_ITEMMALL_GIFTITEM,			//[�ؿ�] ������ ������ ������ �����ϱ�
	GAMEMSG_RESPONSE_ITEMMALL_GIFTITEM,

	GAMEMSG_REQUEST_CHECK_ACCOUNTID,			//[�ؿ�] ���̵� ��ȸ
	GAMEMSG_RESPONSE_CHECK_ACCOUNTID,

	GAMEMSG_REQUEST_BILLPAGE_URL,				//[����] �����κ��� ��ȣȭ�� �� ������ URL ������
	GAMEMSG_RESPONSE_BILLPAGE_URL,

	GAMEMSG_RESPONSE_SET_CHANGEHERO,			//[�ؿ�] ������ �� �ִ� ���� ����

	GAMEMSG_REQUEST_CHANGE_HERO,				//[�ؿ�] �������� ����!

	GAMEMSG_REQUEST_PRESENT_ANSWER,				//[����] ���� �༭ ���ٴ� ������ ������

	GAMEMSG_REQUEST_GACHAPAGE_URL,				//[����] ��í ������ �ּ� ������
	GAMEMSG_RESPONSE_GACHAPAGE_URL,				//	

	GAMEMSG_REQUEST_LOGINPAGE_URL,				//
	GAMEMSG_RESPONSE_LOGINPAGE_URL,

	GAMEMSG_REQUEST_OILLING_USEITEM ,		//[�� ] �ֹ����� ����ߴ�. - ���� , �ð��� ������ ���.
	GAMEMSG_RESPONSE_OILLING_USEITEM ,			

	//--------------------------------
	// ��Ÿ
	//--------------------------------
	GAMEMSG_REQUEST_GACHAPRODUCT_LIST = 6900,	//[����] ������ǰ�� ����� ��û�Ѵ�.
	GAMEMSG_RESPONSE_GACHAPRODUCT_LIST,
	GAMEMSG_REQUEST_GACHABUY,
	GAMEMSG_RESPONSE_GACHABUY,

	//KHY - 1104 -  ����2 -���� ���� ����. 
	GAMEMSG_REQUEST_GACHA2PRODUCT_LIST ,	//[��] ����2 ��ǰ�� ����� ��û�Ѵ�.
	GAMEMSG_RESPONSE_GACHA2PRODUCT_LIST,
	GAMEMSG_REQUEST_GACHA2BUY,
	GAMEMSG_RESPONSE_GACHA2BUY,

	// �̿� ��í
	GAMEMSG_REQUEST_CARRYOVER_GACHA_LIST,			//[����] ����/�̿� ���� ����� ��û�Ѵ�
	GAMEMSG_RESPONSE_CARRYOVER_GACHA_LIST,

	GAMEMSG_REQUEST_CARRYOVER_SELECTPRODUCT_LIST,	//[����] ����/�̿��� ������ ���� ��ǰ�� ����� ��û�Ѵ�
	GAMEMSG_RESPONSE_CARRYOVER_SELECTPRODUCT_LIST,

	GAMEMSG_REQUEST_CARRYOVER_GACHABUY,				//[����] ��í�� ���� �Ѵ�
	GAMEMSG_RESPONSE_CARRYOVER_GACHABUY,




	//-------------------------
	// ���λ��� 
	//-------------------------
	GAMEMSG_REQUEST_PERSONALSHOPBANNER = 7000,	//[����] ���λ��� ���
	GAMEMSG_RESPONSE_PERSONALSHOPBANNER,

	GAMEMSG_REQUEST_PERSONALSHOPDATA,			//[����] ���λ��� ������ 
	GAMEMSG_RESPONSE_PERSONALSHOPDATA,

	GAMEMSG_RESPONSE_UPDATEPERSONALSHOPBANNER,	//[����] ���λ��� ���� ����  

	GAMEMSG_RESPONSE_UPDATEPERSONALSHOPDATA,	//[����] ���λ��� ������ ����  

	GAMEMSG_REQUEST_STARTPERSONALSHOP,			//[����] ���λ��� ���� 
	GAMEMSG_RESPONSE_STARTPERSONALSHOP,		

	GAMEMSG_REQUEST_STOPPERSONALSHOP,			//[����] ���λ��� ���� 
	GAMEMSG_RESPONSE_STOPPERSONALSHOP,

	GAMEMSG_REQUEST_BUYPERSONALSHOP,			//[����] ���λ��� ���� ������ ������ ��� 
	GAMEMSG_RESPONSE_BUYPERSONALSHOP,

	GAMEMSG_REQUEST_SELLPERSONALSHOP,			//[����] ���λ��� ���� ������ ������ �ȱ� 
	GAMEMSG_RESPONSE_SELLPERSONALSHOP,

	GAMEMSG_REQUEST_SEARCHPERSONALSHOPITEM,		//[����] ���λ�����ǰ �˻�
	GAMEMSG_RESPONSE_SEARCHPERSONALSHOPITEM,

	GAMEMSG_REQUEST_MAKEPERSONALSHOP,			//[����] ���λ�����ǰ����
	GAMEMSG_RESPONSE_MAKEPERSONALSHOP,

	//-------------------------
	// ��ȯ�� SUMMON
	//-------------------------
	GAMEMSG_REQUEST_SUMMONFREE= 7100,			//[����] ��ȯ���� Ǯ���ش�. 
	GAMEMSG_RESPONSE_SUMMONFREE,				//[����]

	GAMEMSG_REQUEST_SUMMONNAMECHANGE,			//[����] ��ȯ�� �̸� ����
	GAMEMSG_RESPONSE_SUMMONNAMECHANGE,			//[����]

	GAMEMSG_REQUEST_SUMMONINFO,					//[����] ��ȯ�� ������ ��û�Ѵ�.
	GAMEMSG_RESPONSE_SUMMONINFO,

	GAMEMSG_REQUEST_SUMMONREVIVE,				//[����] ��ȯ���� ��Ȱ��Ų��.
	GAMEMSG_RESPONSE_SUMMONREVIVE,

	GAMEMSG_REQUEST_USESUMMONBONUS,				//[����] ��ȯ���� ���ʽ��� ����ϰ� �Ѵ�.

	GAMEMSG_REQUEST_TAKEINOUT,					//[����] ��ȯ�� �־��� ���� �Ѵ�.
	
	GAMEMSG_REQUEST_SUMMONATTACKCHANGE,			//[����] ��ȯ�� ���ݼӼ� ���� 
	GAMEMSG_RESPONSE_SUMMONATTACKCHANGE,		//[����]

	GAMEMSG_REQUEST_SUMMONEVOLVE,				//[����] ��ȯ�� ��ȭ 
	GAMEMSG_RESPONSE_SUMMONEVOLVE,				//[����] 

	GAMEMSG_REQUEST_SUMMONSCROLL,				//[����] ��ȯ�� ��ȭ 
	GAMEMSG_RESPONSE_SUMMONSCROLL,				//[����] 

	GAMEMSG_REQUEST_SUMMON_STATUSINIT,			//[�ؿ�] ��ȯ�� ���� �ʱ�ȭ

	GAMEMSG_REQUEST_SUMMON_SETAUTOHEAL,			//[�ؿ�] ��ȯ�� �ڵ� ȸ�� ����
	GAMEMSG_RESPONSE_SUMMON_SETAUTOHEAL,

	GAMEMSG_REQUEST_TRADEMERCHANTBUYSUMMONINFO,	//[����] ��ȯ�� �ȱ� ���� ���
	GAMEMSG_RESPONSE_TRADEMERCHANTBUYSUMMONINFO,	

	GAMEMSG_REQUEST_SUMMONTRADE,				//[����] ��ȯ�� �ȱ�
	GAMEMSG_RESPONSE_SUMMONTRADE,

	GAMEMSG_REQUEST_SELECT_SUMMONCHAR,			//[�ؿ�] ��ȯ���� ĳ���ͷ� ����
	GAMEMSG_RESPONSE_SELECT_SUMMONCHAR,

	GAMEMSG_REQUEST_SUMMON_TRANSFORM,			// ��ȯ�� ����.
	GAMEMSG_RESPONSE_SUMMON_TRANSFORM,
	//-------------------------	
	//-------------------------
	// ���� 
	//-------------------------
	GAMEMSG_REQUEST_VILLAGEDETAILINFO = 7200,	//[�°�] ���� �� ������ ��û. 
	GAMEMSG_RESPONSE_VILLAGEDETAILINFO,			//[�°�]

	GAMEMSG_REQUEST_GETVILLAGEINFO,				//[����] ���� ���� ( ��������, �θ��� )
	GAMEMSG_RESPONSE_GETVILLAGEINFO,			//[����]	

	GAMEMSG_REQUEST_GETNOWVILLAGEINFO,			//[����] Ư�� �ð��� �ϰ� ������Ʈ�Ǵ� ���� ������ ������ Ŭ���̾�Ʈ�� ������. 
	GAMEMSG_RESPONSE_GETNOWVILLAGEINFO,

	GAMEMSG_REQUEST_RESIDENTSLIST,				//[���] ���� �ֹ��� ������ �ִ� �ֹ� ���� ��û
	GAMEMSG_RESPONSE_RESIDENTSLIST,				//[���]

	GAMEMSG_RESPONSE_RESIDENTLOGIN,				//[���] ���� �ֹ��� ���������� �ֹε鿡�� �˷���.

	GAMEMSG_RESPONSE_SETGAMEDELAY,				//[�°�] ������ �ӵ��� Ŭ���̾�Ʈ�� ������. 

	GAMEMSG_RESPONSE_PERSONITEMINFO,			//[�°�] Person�� �Ѱ� ������ ������ Ŭ���̾�Ʈ�� ������. 

	GAMEMSG_RESPONSE_PERSONENCHANTITEMINFO,		//[] Person�� �Ѱ� ������ ������ Ŭ���̾�Ʈ�� ������. 

	GAMEMSG_RESPONSE_PERSONALLSHAPEINFO,		//[�°�] �ٸ� ������� ��ü ���� ������ �뺸�Ѵ�. 

	GAMEMSG_RESPONSE_PERSONMAKEITEMSWITCH,		//[����] �ٸ� ������� ���� ���¸� �뺸

	GAMEMSG_REQUEST_INVREPAIR,					//[�°�] ����ڰ� ���� �ִ� �������� �����ϵ��� ��û�Ѵ�. 
	GAMEMSG_RESPONSE_INVREPAIR,					//[�°�] ������ ����� �뺸�Ѵ�. 


	GAMEMSG_RESPONSE_WEATHER,					//[�°�] ������ �뺸�Ѵ�. 

	GAMEMSG_RESPONSE_PERSONHORSE,				//[�°�] Person�� Horse ������ ������. (������ ����.) 

	GAMEMSG_RESPONSE_NEIGHBOURHORSE,			//[�°�] Person�� Horse ������ �̿����� ������. 

	GAMEMSG_RESPONSE_LOWPRICESTOCKORDER,		//[�°�] ���ֿ� �ö�� �ֹ��� ���� ���� ������ ��ǰ ������ ������. 

	GAMEMSG_REQUEST_READY,						//[�°�] Ŭ���̾�Ʈ�� �غ�Ǿ����� �뺸. 

	GAMEMSG_RESPONSE_LEVELUP,					//[�°�] ������ �Ǿ����� �뺸�Ѵ�. 

	GAMEMSG_RESPONSE_LEVELUPNOTICE,				//[��] ������ �Ǿ����� �뺸�Ѵ�. ä��â�� ���� ��� �� �����ϰ�� ǥ���Ѵ�. 

	GAMEMSG_REQUEST_INV_CANCELLATIONSEALINGUP,	//[�ؿ�] ������ �ִ� �������� �к��� �����Ѵ�.
	GAMEMSG_RESPONSE_INV_CANCELLATIONSEALINGUP, //[�ؿ�]

	GAMEMSG_REQUEST_REVIVE,						//[����] Ŭ���̾�Ʈ���� ������ ĳ���� ��Ȱ���� �޶���û
	GAMEMSG_RESPONSE_REVIVE,					//[����] ������ ĳ���� ��Ȱ��ų ������ ����

	GAMEMSG_REQUEST_RESURRECTION,				//[����] Ŭ���̾�Ʈ���� ������ ��� ��Ȱ�� ��û

	GAMEMSG_RESPONSE_NOTICE_ITEMUSEABLEDAY,		//[����] ������ ���Ⱓ 3�� �̸� ���� �˸�.

	GAMEMSG_REQUEST_PRESELLTOFOREIGNMERCHANT,	//[����] ���ο��� �����ȱ����� �Ⱓ�� ���� ���ݺ��� ��û
	GAMEMSG_RESPONSE_PRESELLTOFOREIGNMERCHANT,	//[����] ���ο��� �����ȱ����� �Ⱓ�� ���� ���ݺ��� ����

	GAMEMSG_REQUEST_SITDOWN,					//[���] �ɱ�

	GAMEMSG_REQUEST_HOUSECANCELLATIONPENALTYMONEY,//[����] ���� �ؾ�� ����ݾ� ��û
	GAMEMSG_RESPONSE_HOUSECANCELLATIONPENALTYMONEY,
	GAMEMSG_REQUEST_HOUSECANCELLATION,			//[����] ���� �ؾ�
	GAMEMSG_RESPONSE_HOUSECANCELLATION,			

	GAMEMSG_RESPONSE_VILLAGEGENERALMEETING,		//[�߰� : Ȳ���� 2008. 2. 21 => ���� ������ȸ �ߵ� ���� ���� �뺸.]

	GAMEMSG_RESPONSE_CRYSTALITEMINFO, //KHY - 0421 - ����ü ������ Ŭ���̾�Ʈ�� ������.

	GAMEMSG_REQUEST_BLACKARMYAPPLY = 7300,				//[����] ���Ǳ��� �̺�Ʈ ��û
	GAMEMSG_RESPONSE_BLACKARMYAPPLY,			//[����] ���Ǳ��� �̺�Ʈ ����

	GAMEMSG_RESPONSE_BLACKARMYWAR,				//[����] ����޽���

	GAMEMSG_REQUEST_BLACKARMY_RANKINFO,			//[����] ���� ���� ��û
	GAMEMSG_RESPONSE_BLACKARMY_RANKINFO,		//[����] ���� ���� ����

	GAMEMSG_REQUEST_BLACKARMY_WARPTOGATE,		//[����] ����ʰ���Ʈ�� ���� ��û

	GAMEMSG_RESPONSE_BLACKARMY_MVPEFFECT,		//[����] ���� MVP ����Ʈ ����

	GAMEMSG_RESPONSE_BLACKWAR,					//[����] ���Ǳ��� ����޼���

	GAMEMSG_REQUEST_PERSONNAME_SERIALID,		//[����] ������ �ø����ȣ�� ������ �̸� ��û
	GAMEMSG_RESPONSE_PERSONNAME_SERIALID,		//[����] ������ �ø����ȣ�� ������ �̸� ����

	GAMEMSG_REQUEST_PERSONNAME_FROMPERSONID,	//[����] ������ �̸� ��û
	GAMEMSG_RESPONSE_PERSONNAME_FROMPERSONID,	//[����] ������ �̸� ����

	GAMEMSG_REQUEST_BELONGITEM_DESTROY,			//[����] �ͼӾ����� �ı���û

	GAMEMSG_REQUEST_DISASSEMBLEITEM,			//[����] �����ۺ��� ��û
	GAMEMSG_RESPONSE_DISASSEMBLEITEM,			//[����] �����ۺ��� ����
	GAMEMSG_REQUEST_DISASSEMBLEITEM_LIST,		//[����] �����ۺ��� ����Ʈ ��û
	GAMEMSG_RESPONSE_DISASSEMBLEITEM_LIST,		//[����] �����ۺ��� ����Ʈ ����
	GAMEMSG_REQUEST_DISASSEMBLEITEM_RECIEVE,	//[����] ���ص� ������ ���� ��û
	GAMEMSG_RESPONSE_DISASSEMBLEITEM_RECIEVE,	//[����] ���ص� ������ ���� ����

	GAMEMSG_RESPONSE_OPENTREASUREBOX,			//[����] �������� ����

	GAMEMSG_RESPONSE_KINGGURIINFO,				///[����] ��ձ����� �̺�Ʈ

	GAMEMSG_RESPONSE_KITERACCOONINFO,			// [����] ī��Ʈ���� �̺�Ʈ

	GAMEMSG_RESPONSE_RAREITEMFROMTREASUREBOX,	// [����] �������ڿ��� ����������� ��������(���� �������� �ҽ��� �ھҴ�)

	//--------------------------------
	// WorldMoney ( ��ť )
	//--------------------------------
	GAMEMSG_RESPONSE_SETWORLDMONEY_BUYDLG = 7400 ,		//[�ؿ�] ������ ��ɾ�� ��ť�� ����ϴ� �ڽ��� ����

	GAMEMSG_REQUEST_DISTRIBUTION_WORLDMONEY,			//[�ؿ�] ��ť�� �ý��ۿ��Լ� ����Ѵ�.
	GAMEMSG_RESPONSE_DISTRIBUTION_WORLDMONEY,

	GAMEMSG_REQUEST_WORLDMONEY_TRADELIST,				//[�ؿ�] ��ť �ŷ��� ����Ʈ�� ��û�Ѵ�.
	GAMEMSG_RESPONSE_WORLDMONEY_TRADELIST,

	GAMEMSG_REQUEST_WORLDMONEY_SELLORDER,				//[�ؿ�] ��ť �ŷ��ҿ� ��ť �ȱ⸦ ��û�Ѵ�.
	GAMEMSG_RESPONSE_WORLDMONEY_SELLORDER,

	GAMEMSG_REQUEST_WORLDMONEY_BUYORDER,				//[�ؿ�] ��ť �ŷ��ҿ��� ��ť ��⸦ ��û�Ѵ�.
	GAMEMSG_RESPONSE_WORLDMONEY_BUYORDER,

	GAMEMSG_REQUEST_WORLDMONEY_CANCELORDER,				//[�ؿ�] ��ť �ŷ����� �ֹ� ��� ��Ҹ� ��û�Ѵ�.
	GAMEMSG_RESPONSE_WORLDMONEY_CANCELORDER,

	GAMEMSG_RESPONSE_WORLDMONEY_SET_CHAR,				//[�ؿ�] ��ť�� ������Ʈ �����.

	//--------------------------------
	// TradeServer ( ���� )
	//--------------------------------

	GAMEMSG_REQUEST_TRADESERVER_SET_SELLORDER = 7500,	//[�ؿ�] Ʈ���̵� ������ �ֹ��� �ø���.
	GAMEMSG_RESPONSE_TRADESERVER_SET_SELLORDER,

	GAMEMSG_REQUEST_TRADESERVER_CANCEL_SELLORDER,		//[�ؿ�] Ʈ���̵� ������ �ֹ��� ������.
	GAMEMSG_RESPONSE_TRADESERVER_CANCEL_SELLORDER,

	GAMEMSG_REQUEST_TRADESERVER_SET_BUYORDER,			//[�ؿ�] Ʈ���̵� ������ �ֹ��� ���.
	GAMEMSG_RESPONSE_TRADESERVER_SET_BUYORDER,

	GAMEMSG_REQUEST_TRADESERVER_GET_LISTINFO,			//[�ؿ�] Ʈ���̵� ������ ����Ʈ�� ��û�Ѵ�.
	GAMEMSG_RESPONSE_TRADESERVER_GET_LISTINFO,

	GAMEMSG_RESPONSE_TRADESERVER_GET_SELLINFO,			//[�ؿ�] Ʈ���̵� �������� �ȸ� ���ǿ� ���� ������ �޾Ҵ�.

	GAMEMSG_REQUEST_TRADESERVER_GET_MYINFO,				//[�ؿ�] Ʈ���̵� ������ �ö� �� ������ ������ ��û�Ѵ�.
	GAMEMSG_RESPONSE_TRADESERVER_GET_MYINFO,

	GAMEMSG_REQUEST_TRADESERVER_GET_SAVEDACU_LIST,		//[����] ���������� ����� ��ť/�ֽŰŷ����� ��û
	GAMEMSG_RESPONSE_TRADESERVER_GET_SAVEDACU_LIST,

	GAMEMSG_REQUEST_TRADESERVER_GET_WITHDRAW_ACU,		//[����] ���������� ����� ��ť �ޱ� ��û
	GAMEMSG_RESPONSE_TRADESERVER_GET_WITHDRAW_ACU,

	//--------------------------------
	// WorldPassport ( ���� ���� )
	//--------------------------------
	GAMEMSG_REQUEST_WORLDPASSPORT_SET = 7550,			//[����] �������� ���� �߱�
	GAMEMSG_RESPONSE_WORLDPASSPORT_SET,

	GAMEMSG_REQUEST_WORLDPASSPORT_EXTEND,				//[����] �������� ���� ����
	GAMEMSG_RESPONSE_WORLDPASSPORT_EXTEND,

	//--------------------------------
	// ��Ÿ
	//--------------------------------

	GAMEMSG_RESPONSE_COUNTRYINFO = 7600,				//[����] ���� ���� �ޱ�.
	GAMEMSG_REQUEST_SETCOUNTRYINFO,					    //[����] ���� ���� ���� ��û
	GAMEMSG_RESPONSE_SETCOUNTRYINFO,					//[����] ���� ���� ���� ���� - ���� ����ũ ��
	GAMEMSG_REQUEST_SETSHOWCOUNTRY,
	GAMEMSG_RESPONSE_SETSHOWCOUNTRY,					//[����] ���� ���� ���� ���� - �����ֱ� ���� 

	GAMEMSG_REQUEST_SETSHOWPUCHIKOMI,					//[����] �ڽ��� Ǫġ�ڹ̸� �ٸ��������� �����ֳ�
	GAMEMSG_RESPONSE_SETSHOWPUCHIKOMI,					//[����] �ڽ��� Ǫġ�ڹ̸� �ٸ��������� �����ֳ�

	GAMEMSG_REQUEST_USERLISTBYCOUNTRY,					//[����] ������ ���� ����Ʈ ��û
	GAMEMSG_RESPONSE_USERLISTBYCOUNTRY,			

	GAMEMSG_RESPONSE_NOTGAMEPOTAUTH,					//[����] ������ ������ �ȵ� �����̸�

	GAMEMSG_REQUEST_ADDCHINESEUSER,						//[����] �߱���� ����� ���
	GAMEMSG_RESPONSE_NOTICECOUNTRYUSERMAKE,				//[����] ���� �Է½� �Ҽӱ����� ���� �������� �޼��� ������

	GAMEMSG_REQUEST_LOWLEVELLIST,						//[����] 20�̸� ���� ���� ��û
	GAMEMSG_RESPONSE_LOWLEVELLIST,						//[����] 20�̸� ���� ���� �뺸

	GAMEMSG_RESPONSE_ADDBUF,							//[����] ������ �߰��Ѵ�.
	GAMEMSG_RESPONSE_DELETEBUF,							//[����] ������ �����Ѵ�.

	GAMEMSG_RESPONSE_SETTEACHERPOINT,					//[����] ���������� ������Ʈ �Ѵ�.

	GAMEMSG_RESPONSE_SETITEMTYPEINFO,					//[����] ���� �� ��Ʈ ������ ������ Ŭ���̾�Ʈ�� �˷��ش�
	GAMEMSG_REQUEST_SETEMOTICON,						//[����] �̸�Ƽ��
	GAMEMSG_RESPONSE_SETEMOTICON,						//[����] 

	GAMEMSG_RESPONSE_CANNOTLOGIN_AGE,					//[����] �������� ������ �α��� �� �� ����.
	GAMEMSG_RESPONSE_GAMEDISCONNECT_AGE,				//[���] ���ӽ����߿� �������� üũ�� ��� �Ѵ�.
	GAMEMSG_RESPONSE_CANNOTLOGIN_ERROR,					//[����] �Ѱ��� ���� ��� ����

	//--------------------------------
	// ���ĸ��� �̺�Ʈ
	//--------------------------------

	GAMEMSG_REQUEST_MOFUMOFUEVENT_RESERVE = 7700,		//[����] ���ĸ��� �̺�Ʈ ����
	GAMEMSG_RESPONSE_MOFUMOFUEVENT_RESERVE,				//[����]

	GAMEMSG_REQUEST_MOFUMOFUEVENT_RESERVELIST,			//[����] ���ĸ��� �̺�Ʈ ���� ����Ʈ
	GAMEMSG_RESPONSE_MOFUMOFUEVENT_RESERVELIST,			//[����]

	GAMEMSG_RESPONSE_MOFUMOFUEVENT_START,				//[����] ���ĸ��� �̺�Ʈ ����
	GAMEMSG_RESPONSE_MOFUMOFUEVENT_END,					//[����] ���ĸ��� �̺�Ʈ ����

	GAMEMSG_REQUEST_MOFUMOFUEVENT_ENTERFIELD,			//[����] ���ĸ��� �̺�Ʈ �ʵ� ���� ��û
	GAMEMSG_REQUEST_MOFUMOFUEVENT_WARP,					//[����] ���ĸ��� �̺�Ʈ ���� �Ա� ���� ��û

	GAMEMSG_RESPONSE_MOFUMOFUEVENT_SETINFO,				//[����] ���ĸ��� �̺�Ʈ �ʵ� ����
	GAMEMSG_RESPONSE_MOFUMOFUEVENT_INFO,				//[����] ���ĸ��� �̺�Ʈ ����
	GAMEMSG_RESPONSE_MOFUMOFUEVENT_MAMAMOFUMOFU,		//[����] ���� ���ĸ��� ����

	//-------------------------------
	//���� �̺�Ʈ - ���� ����. 
	//-------------------------------
	GAMEMSG_RESPONSE_MONSTER_ATTACK_START,				//[����] ���� ������ ��������.
	GAMEMSG_RESPONSE_MONSTER_ATTACK_REWARD,				//[����] ���� ���� �̺�Ʈ�� ���� ���� ���� �뺸��

	//-------------------------------
	// ��Ī ����Ʈ
	//-------------------------------
	GAMEMSG_REQUEST_NAMINGQUEST_START = 7800,			//[����] ��Ī ����Ʈ ����

	GAMEMSG_RESPONSE_SETPERSONNAMINGINFO,				//[����] ������ ������ �ִ� ��Ī����

	GAMEMSG_REQUEST_SETPERSONCURRENTNAMING,				//[����] ������ ���� ������ ��Ī
	GAMEMSG_RESPONSE_SETPPERSONCURRENTNAMING,			//'����]

	//-------------------------------
	// ���� NPC
	//-------------------------------
	GAMEMSG_REQUEST_SYSTEMREWARDLIST	= 7810,			//[����] �̺�Ʈ ���� ��� ��û
	GAMEMSG_RESPONSE_SYSTEMREWARDLIST,

	GAMEMSG_REQUEST_RECIEVESYSTEMREWARD,				//[����] ���� �ޱ�
	GAMEMSG_RESPONSE_RECIEVESYSTEMREWARD,

	//�⼮üũ
	GAMEMSG_RESPONSE_DEMANDATTEND	= 7820,				//[����] �⼮ üũ�� ��û�Ѵ� ( ����->Ŭ���̾�Ʈ )

	GAMEMSG_REQUEST_ATTEND,								//[����] �⼮üũ
	GAMEMSG_RESPONSE_ATTEND,							//[����]

	GAMEMSG_REQUEST_ATTENDREWARDITEM,					//[����] �⼮üũ ���� ������



	//-------------------------------
	// ���Ǻ� ����Ʈ
	//-------------------------------
	//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.

	GAMEMSG_REQUEST_HAPPYBEANQUEST_START = 7900,		//����Ʈ ����
	GAMEMSG_RESPONSE_HAPPYBEANQUEST_START_NO,			// ����Ʈ �Ұ�.
	GAMEMSG_RESPONSE_HAPPYBEANQUEST_START_OK,			// ����Ʈ �㰡.
	GAMEMSG_RESPONSE_HAPPYBEANQUEST_REWARD,				//����Ʈ ������ �˸���.

	// [����] ���ֵ��� �̼�
	GAMEMSG_RESPONSE_GOONZUDAYMISSION_CLEARREWARD,		// �̼� �Ϸῡ ���� ������ �˸�

	//-------------------------------
	// ���ӹ� �̺�Ʈ ����.
	//-------------------------------
	//KHY - 0906 - ���ӹ� �̺�Ʈ ����.
	GAMEMSG_RESPONSE_EVENTCOUPON, 						//�̺�Ʈ ������ ���� ����� �˸���.
	////-------------------------------
	//// �����̺�Ʈ 2007.09.10 �ռ���
	////-------------------------------
	////KHY - 0906 - ���� �̺�Ʈ ����.
	//GAMEMSG_RESPONSE_AUCTIONEVENTCOUPON, 				//�̺�Ʈ ������ ���� ����� �˸���.

	GAMEMSG_RESPONSE_GAME_GUARD_AUTH,					//[����] �������� Ŭ���̾�Ʈ�� ���� ���� ������ ��û�Ѵ�
	GAMEMSG_REQUEST_GAME_GUARD_AUTH,	

	GAMEMSG_RESPONSE_SANTARACCOONINFO,					//[�߰� : Ȳ���� 2007. 11. 29 ��Ÿ���� �̺�Ʈ �޽���.]

	GAMEMSG_REQUEST_NEWYEAR_CLICK,						//[�߰� : Ȳ���� 2007. 12. 11 �ų� ��ư�� Ŭ�� �޴ٴ� �޽���.	C->S]
	GAMEMSG_RESPONSE_NEWYEAR_BTN,						//[�߰� : Ȳ���� 2007. 12. 11 �ų� ��ư ����� �޽���.		S->C]

	GAMEMSG_REQUEST_MISSIONQUEST_START,					// �̼� ����Ʈ ����
	GAMEMSG_RESPONSE_MISSIONQUEST_START,				//

	GAMEMSG_REQUEST_MISSIONQUEST_ACCEPT,				// �̼� ����Ʈ ����
	GAMEMSG_REQUEST_MISSIONQUEST_CANCEL,				// �̼� ����Ʈ ���

	/// ����
	GAMEMSG_REQUEST_CREATEEMPIRE = 7950,				//[����] ������ �����
	GAMEMSG_RESPONSE_CREATEEMPIRE,

	GAMEMSG_REQUEST_DESTROYEMPIRE,						//[����] ������ü
	GAMEMSG_RESPONSE_DESTROYEMPIRE,

	GAMEMSG_REQUEST_INVITEEMPIRE,						//[����] �������� �ʴ��Ѵ�.
	GAMEMSG_RESPONSE_INVITEEMPIRE,

	GAMEMSG_REQUEST_SECEDEEMPIRE,						//[����] �������� Ż���Ѵ�.
	GAMEMSG_RESPONSE_SECEDEEMPIRE,

	GAMEMSG_RESPONSE_UPDATEEMPIREINFO,					//[����] �ڱ� �ڽ��� ���� ���� ������Ʈ

	GAMEMSG_REQUEST_EMPIREINFO,							//[����] ������ ������ ��û�Ѵ�.
	GAMEMSG_RESPONSE_EMPIREINFO,

	GAMEMSG_REQUEST_JOINEMPIRE,							//[����] ������ �����Ѵ�.
	GAMEMSG_RESPONSE_JOINEMPIRE,

	GAMEMSG_REQUEST_SETEMPIREMONEY,						//[����] ���� �ں����� �ִ´�.
	GAMEMSG_RESPONSE_SETEMPIREMONEY,

	GAMEMSG_RESPONSE_AUTOMACRO_CHECK,					//[�߰� : Ȳ���� 2007. 12. 3  => ������������ Ŭ���̾�Ʈ�� �������α׷� �˻��϶��.]
	GAMEMSG_REQUEST_AUTOMACRO_ON,						//[�߰� : Ȳ���� 2007. 12. 5  => �������� Ŭ���̾�Ʈ�� �������α׷� ��� ���̶�� ����.]
	GAMEMSG_RESPONSE_AUTOMACRO_ON_OTHER,				//[�߰� : Ȳ���� 2007. 12. 10 => ������������ Ŭ���̾�Ʈ�� �������α׷��� ����ϴ� ������ ����.]

	//����������� �ٶ� ���� 

	//-------------------------------
	//KHY - 1220 - ���Žý���.
	//-------------------------------
	GAMEMSG_REQUEST_TRANSFORM = 8000,			//[�� ] ĳ���͸� ���� ��Ų��.
	GAMEMSG_RESPONSE_TRANSFORM,

	GAMEMSG_REQUEST_TRANSFORM_END,			//[�� ] ĳ���� ������ ���� ��Ų��.
	//GAMEMSG_RESPONSE_TRANSFORM_END,

	GAMEMSG_REQUEST_TRANSFORM_USEITEM ,			//[�� ] ���ſ� ���õ� �������� ��� �Ѵ�. - ĳ���� ���, �ð��� ������ ���.
	GAMEMSG_RESPONSE_TRANSFORM_USEITEM ,			

	GAMEMSG_RESPONSE_MAXSYNCRO_ATTAINMENT,		// [����] ��ũ���� 100% �޼�

	GAMEMSG_RESPONSE_TRANSFORM_LIMIT_TIME,		//[�߰� : Ȳ���� 2008. 1. 9 => ������ �ð��� 30�ʰ� �ȵǼ� ���� ���� �޽��� ����.]

	//-------------------------------
	// ������ ���� ���� - by LEEKH 2007.12.28
	//-------------------------------
	GAMEMSG_RESPONSE_TIMEMETERRATE_UPDATE = 8050,		//[����] ������ ���� ������Ʈ

	//---------------------------------------------------------------------------------
	//���� ���� ����Ʈ
	//--------------------------------------------------------------------------------
	GAMEMSG_REQUEST_HOFLIST,					//[����]���� ���� ����Ʈ ������.
	GAMEMSG_RESPONSE_HOFLIST, 

	GAMEMSG_REQUEST_RAKINGLIST,								//[����]��ŷ����Ʈ
	GAMEMSG_RESPONSE_RAKINGLIST, 

	//-------------------------------
	// �߰� : Ȳ���� 2008. 1. 9 => �ν��Ͻ����� �޽���.  
	//-------------------------------
	GAMEMSG_REQUEST_INSTANTSDUNGEON_STATUS,			
	GAMEMSG_RESPONSE_INSTANTSDUNGEON_STATUS,			
	GAMEMSG_RESPONSE_INSTANTSDUNGEON_RUN_STATUS,
	GAMEMSG_RESPONSE_INSTANTMAP_GATEINFO,					//[����] �ν��Ͻ� �� ����Ʈ ��������
	GAMEMSG_RESPONSE_INSTANTSDUNGEON_REWARD,
	GAMEMSG_RESPONSE_INSTANTSDUNGEON_TOP_CHANGE,

	//--------------------------------------------------------------
	// �߰� : Ȳ���� 2008. 1. 23 => ���� ���� ���� �޽���.  
	//--------------------------------------------------------------
	GAMEMSG_RESPONSE_BLACK_WAR_REFORM_CHAR_RESULT,			//���� ���� ���� �̺�Ʈ ���� �� ����� �˸� �޽���.  
	GAMEMSG_RESPONSE_BLACK_WAR_REFORM_VILLAGE_RESULT,

	GAMEMSG_REQUEST_FILECRCCHECK,							// [����] ���� ���� üũ
	GAMEMSG_RESPONSE_FILECRCCHECK,							// �������� ������ üũ�϶�� ����� ������

	//--------------------------------------------------------------
	// �߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ���� �޽���. C < - > S
	//--------------------------------------------------------------
	GAMEMSG_REQUEST_ARTIFACT_MIXTURE,						// ����ü ����.
	GAMEMSG_RESPONSE_ARTIFACT_MIXTURE,	

	GAMEMSG_REQUEST_ARTIFACT_REMOVE,						// ����ü ����.
	GAMEMSG_RESPONSE_ARTIFACT_REMOVE,

	GAMEMSG_REQUEST_ARTIFACT_SLOT_CREATE,					// ���� ����.
	GAMEMSG_RESPONSE_ARTIFACT_SLOT_CREATE,


	GAMEMSG_REQUEST_PIRATESHIP_ENTERFIELD,					// [����] ������ : ���������� ������ �������� ���

	GAMEMSG_RESPONSE_INSTANTDUNGEON_PARTY_CLEAR,			// [����] ������ : Ŭ���� �� ������ ����

	GAMEMSG_RESPONSE_PIRATESHIP_APPEAR,						// [����] ������ : �������� ��Ÿ���ٴ� �޽���

	//-------------------------
	// Daily ����Ʈ2
	//-------------------------	
	GAMEMSG_REQUEST_DAILYQUEST2LIST,			//����Ʈ ����Ʈ ��û
	GAMEMSG_RESPONSE_DAILYQUEST2LIST,		//

	GAMEMSG_REQUEST_DAILYQUEST2SELECT,		// ����Ʈ ����
	GAMEMSG_RESPONSE_DAILYQUEST2SELECT,		//

	GAMEMSG_REQUEST_DAILYQUEST2SITUATION,	// ����Ʈ ��Ȳ
	GAMEMSG_RESPONSE_DAILYQUEST2SITUATION,	//

	GAMEMSG_RESPONSE_DAILYQUEST2CHANGE,		// ����Ʈ ���� �ð��� ���� �������� ������Ʈ ����.

	GAMEMSG_REQUEST_DAILYQUEST2END,			// ����Ʈ ����
	GAMEMSG_RESPONSE_DAILYQUEST2END,			//

	//-------------------------
	// Daily ����Ʈ3
	//-------------------------	
	GAMEMSG_REQUEST_DAILYQUEST3LIST,			//����Ʈ ����Ʈ ��û
	GAMEMSG_RESPONSE_DAILYQUEST3LIST,		//

	GAMEMSG_REQUEST_DAILYQUEST3SELECT,		// ����Ʈ ����
	GAMEMSG_RESPONSE_DAILYQUEST3SELECT,		//

	GAMEMSG_REQUEST_DAILYQUEST3SITUATION,	// ����Ʈ ��Ȳ
	GAMEMSG_RESPONSE_DAILYQUEST3SITUATION,	//

	GAMEMSG_RESPONSE_DAILYQUEST3CHANGE,		// ����Ʈ ���� �ð��� ���� �������� ������Ʈ ����.

	GAMEMSG_REQUEST_DAILYQUEST3END,			// ����Ʈ ����
	GAMEMSG_RESPONSE_DAILYQUEST3END,			//

	GAMEMSG_RESPONSE_HEALTH_CHANGE,			//[����] �ǰ������� ���� ��Ų��. => 2008-4-6

	GAMEMSG_REQUEST_INV_CHANGITEMFORMNPC,	// ���ݼ���κ��� ������ ������ ��û�Ѵ�.
	GAMEMSG_RESPONSE_INV_CHANGITEMFORMNPC,	

	// �ɸ��� �ɼ� ����
	GAMEMSG_REQUEST_CHAR_OPTION,		//[����] ������� �ɼ��� �����Ѵ�.
	GAMEMSG_RESPONSE_CHAR_OPTION,		//[����]

	// �ɸ��� �ɼ� ��û
	GAMEMSG_RESPONSE_CHAR_GET_OPTION,	//[����] �ɸ��� �ɼ� ��û

	// [����] ������ ���� �̺�Ʈ �����귿 ������ ����ϴ� ��Ŷ. => 2008-6-10
	GAMEMSG_REQUEST_BUFF_ROULETTE,		
	GAMEMSG_RESPONSE_BUFF_ROULETTE,		

	//	[��ȣ_BALANCECURRENCY]  protocol
	GAMEMSG_REQUEST_BALANCECURRENCY_BUFF,		
	GAMEMSG_RESPONSE_BALANCECURRENCY_BUFF,		


	// [����] ���� �̺�Ʈ => 2008-6-19 
	GAMEMSG_REQUEST_SERVER_EVENT_RANK_INFO,					// [����] ����, ���� ��ŷ���� ��û.			=> 2008-6-20
	GAMEMSG_RESPONSE_SERVER_EVENT_RANK_INFO,				// [����] ����, ���� ��ŷ���� �ޱ�.			=> 2008-6-20
	GAMEMSG_RESPONSE_SERVER_EVENT_SERVER_INFO,				// [����] ���� ��ŷ���� �ޱ�.				=> 2008-6-20
	GAMEMSG_RESPONSE_SERVER_DAILY_EVENT_SERVER_INFO,		// [����] �Ϸ� ���� ��ŷ���� �ޱ�.			=> 2008-6-20
	GAMEMSG_RESPONSE_SERVER_EVENT_PERSONAL_INFO,			// [����] ���� ��ŷ���� �ޱ�.				=> 2008-6-20
	GAMEMSG_REQUEST_SERVER_EVENT_BONUS_STAGE,				// [����] ���� �̺�Ʈ ���� �� 1�� ������ ����� ������ �� ����.=> 2008-6-24
	GAMEMSG_RESPONSE_SERVER_EVENT_INSTANCEMAP_BONUS_FIGURE,	// [����] ���� �̺�Ʈ �δ� ���� �� �� �δ��� �ܰ迡 ���� ������ �´°�� ���ʽ� �˸� => 2008-6-27

	GAMEMSG_REQUEST_SERVER_EVENT_QUEST_START,				// [����] ���� �̺�Ʈ ����Ʈ ���� ������ ��û��
	GAMEMSG_RESPONSE_SERVER_EVENT_QUEST_START,				// [����] ���� �̺�Ʈ ����Ʈ ���� ������ ����
	GAMEMSG_RESPONSE_SERVER_EVENT_QUEST_RUNINFO,			// [����] ���� �̺�Ʈ ����Ʈ ���� ������ ����
	GAMEMSG_RESPONSE_SERVER_EVENT_QUEST_CLEARSTATUS,		// [����] ���� �̺�Ʈ ����Ʈ Ŭ���� ���� ������ ����

	GAMEMSG_REQUEST_SERVER_EVENT_LOBBY_ENTERFIELD,			// [����] ���� �̺�Ʈ �δ� �κ� ���� ��û

	GAMEMSG_RESPONSE_SERVER_EVENT_INSTANCEDUNGEON_RUNINFO,	// [����] ���� �̺�Ʈ ����Ʈ Ŭ���� ���� ������ ����

	//GAMEMSG_RESPONSE_TANGWANGGIRL,							// [����] 2�� ����
	GAMEMSG_REQUEST_SUMMON_SPTCHARGE,						// [���] ��ȯ�� ���¹̳� ����
	GAMEMSG_RESPONSE_SUMMON_STPCHARGE,

	GAMEMSG_REQUEST_SUMMONUSTON,							//[����] ��ȯ���� ���� �������� �ڴ´�.
	GAMEMSG_RESPONSE_SUMMONUSTON,

	GAMEMSG_REQUEST_GUILD_NOTCONNECT_CHANGEMASTER,			//[����] �Ѵ��̻� ������� ���� �������� ����� ����
	GAMEMSG_RESPONSE_GUILD_NOTCONNECT_CHANGEMASTER,			

	GAMEMSG_REQUEST_BASESUMMONINFO,							//[����] ��ȯ�� ������ ��û�Ѵ�.
	GAMEMSG_RESPONSE_BASESUMMONINFO,

	GAMEMSG_REQUEST_SUMMONSLOTIN,							//[����] Base�� ��ȯ���� SLot���� �ִ´�.
	GAMEMSG_RESPONSE_SUMMONSLOTIN,

	GAMEMSG_REQUEST_SUMMONSLOTOUT,							//[����] SLot���� �ش� ��ȯ���������� 
	GAMEMSG_RESPONSE_SUMMONSLOTOUT,


	//-------------------------------
	// �߰� : �ý��� �޽���
	//-------------------------------
	GAMEMSG_REQUEST_EVENTTIME_UPDATE,						//[����] EventTime ���� ������Ʈ

	GAMEMSG_REQUEST_CHECKPROCESS,							// [����] ���μ��� ����� � ����Ǵ��� ����
	GAMEMSG_RESPONSE_CHECKPROCESS,							// [����] ���μ��� ����� � ����Ǵ��� ��û��

	GAMEMSG_RESPONSE_CHECKPROCESS_RESULT,					// [����] ���μ��� ��� ���� ����� ����(��ڿ���)

	//-----------------------------------
	//[����] ȣ�ڻ��� => 2008-9-16
	//-----------------------------------
	GAMEMSG_RESPONSE_AMBER_BOX_LIST,						// [����] ȣ�ڻ��� ����Ʈ �ֱ� => 2008-9-16

	GAMEMSG_REQUEST_AMBER_BOX_SELECT_ITEM_LIST,				// [����] ȣ�ڻ��� ���� ������ ����Ʈ ��û => 2008-9-16
	GAMEMSG_RESPONSE_AMBER_BOX_SELECT_ITEM_LIST,			// [����] ȣ�ڻ��� ���� ������ ����Ʈ �ֱ� => 2008-9-16

	GAMEMSG_REQUEST_AMBER_BOX_SELECT_ITEM_ADD,				// [����] ȣ�ڻ��� ���� ������ �߰�. => 2008-9-16
	//GAMEMSG_RESPONSE_AMBER_BOX_SELECT_ITEM_LIST,			// [����] ȣ�ڻ��� ���� ������ ����Ʈ �ֱ� => 2008-9-16

	GAMEMSG_REQUEST_AMBER_BOX_SELECT_ITEM_GET,				// [����] ȣ�ڻ��� ����Ʈ �ֱ� => 2008-9-16
	GAMEMSG_RESPONSE_AMBER_BOX_SELECT_ITEM_GET,				// [����] 
	//-----------------------------------
	GAMEMSG_RESPONSE_NOTICE_QUEST,							//	[ ���� ] ȣ������Ʈ �Ҷ� ����Ʈ�� ��ü ���� �ϱ� ���ؼ�

	GAMEMSG_REQUEST_CHAR_ROULETTE,							// [����] ĳ���� �귿
	GAMEMSG_RESPONSE_CHAR_ROULETTE,		

	//---------------------------------------
	//	�Ϲݸʿ��� ���ΰ��� PVP
	//---------------------------------------
	GAMEMSG_REQUEST_PVP_FILED,							// [����] �Ϲ� �ʵ忡���� ���ΰ��� pvp ��û,���,����// NEW PVP - �ռ��� 2008.10.08
	GAMEMSG_RESPONSE_PVP_FILED,

	GAMEMSG_RESPONSE_PVP_LEAGUE_INFOGET,				// [����] PVP ���Ѵ��� ���� ����

	GAMEMSG_REQUEST_PVP_LEAGUE_UI_INFOGET,				// [����] PVP ���Ѵ��� ���̾�α� ������û
	GAMEMSG_RESPONSE_PVP_LEAGUE_UI_INFOGET,

	GAMEMSG_REQUEST_PVP_LEAGUE_APPLY,					// [����] PVP ���Ѵ��� ������û

	GAMEMSG_REQUEST_PVP_LEAGUE_CANCEL,					// [����] PVP ���Ѵ��� �������

	GAMEMSG_REQUEST_PVP_LEAGUE_AGAIN_RESERVE,			// [����] PVP ���Ѵ��� ��⿡ ��Ī���� �ʾƼ� ���� ��⿡ ������ �Ұ��ΰ�?
	GAMEMSG_RESPONSE_PVP_LEAGUE_BATTLE_CHANGEGRADE,		// [����] PVP ���Ѵ��� ����� ���� �Ǿ���




	//[����] ����, ����
	GAMEMSG_REQUEST_VILLAGE_RESIDENT_INVITE,			//[����] ���� �ֹ� �ʴ��ϱ�. => 2008-10-8
	GAMEMSG_RESPONSE_VILLAGE_RESIDENT_INVITE,


	//[����] ����� 2008-11-05
	GAMEMSG_REQUEST_QUESTION_LIST_GET,
	GAMEMSG_RESPONSE_QUESTION_LIST_GET,  
	GAMEMSG_REQUEST_QUESTION_CONTENTS_GET,
	GAMEMSG_RESPONSE_QUESTION_CONTENTS_GET,  
	GAMEMSG_REQUEST_CHECK_QUESTION,
	GAMEMSG_REQUEST_ADD_QUESTION,
	GAMEMSG_RESPONSE_ADD_QUESTION,  
	GAMEMSG_REQUEST_ADD_ANSWER,
	GAMEMSG_RESPONSE_ADD_ANSWER,  
	GAMEMSG_REQUEST_ADD_ANSWER_COMPLETE,
	GAMEMSG_RESPONSE_ADD_ANSWER_COMPLETE,  
	GAMEMSG_REQUEST_ADD_ANSWER_COMPLETE_RESULT,
	GAMEMSG_RESPONSE_ADD_ANSWER_COMPLETE_RESULT,  
	GAMEMSG_REQUEST_DEL_QUESTION,  
	GAMEMSG_REQUEST_DEL_ANSWER,

	GAMEMSG_RESPONSE_SETMUTE,							//[����]ä�ú�ϸ���Ʈ
	GAMEMSG_RESPONSE_MUTELIST,							//[����]ä�ú�ϸ���Ʈ

	GAMEMSG_REQUEST_DIVINATION_ROULETTE,				//[���] �ų��귿
	GAMEMSG_RESPONSE_DIVINATION_ROULETTE,				//[���] �ų��귿

	//KHY - 1113 - ũ�������� �̺�Ʈ -  ����ͺ� �и� ����.
	GAMEMSG_REQUEST_CHRISTMASEVET_ENTERFIELD, 

	//=======================================================================
	//[����] ������.
	//-----------------------------------------------------------------------
	GAMEMSG_REQUEST_ELIXIR_NPC_ITEM_TYPE_LIST_GET,		// �ش� ������ Ÿ�Կ� ���õ� ���� ��û. (�������� ����ũ, ������ ���� ����)
	GAMEMSG_RESPONSE_ELIXIR_NPC_ITEM_TYPE_LIST_GET,

	GAMEMSG_REQUEST_ELIXIR_NPC_CHANGE_ITEM,				// ������ NPC���� ��� ������ ������� ������ ��ȯ.
	GAMEMSG_RESPONSE_ELIXIR_NPC_CHANGE_ITEM,

	GAMEMSG_REQUEST_ELIXIR_USE_START,
	GAMEMSG_RESPONSE_ELIXIR_USE_START,

	GAMEMSG_REQUEST_ELIXIR_SET,							// ������ ����.
	GAMEMSG_RESPONSE_ELIXIR_SET,
	//=======================================================================

	// �߷�Ÿ�ε��� ���� ���� 
	GAMEMSG_REQUEST_VALENTINE_INFO_GET,
	GAMEMSG_RESPONSE_VALENTINE_INFO_GET,

	GAMEMSG_REQUEST_VALENTINE_REQUEST,
	GAMEMSG_RESPONSE_VALENTINE_REQUEST,

	GAMEMSG_RESPONSE_VALENTINE_RUSOLO_RUCOUPLE_ONTIME,	// 12�ô� �߷�Ÿ�ε��̿� �ַ������� �����~

	GAMEMSG_RESPONSE_VALENTINE_OPENDLG,					//�߷�Ÿ�ε��� ���� â�� �����

	GAMEMSG_REQUEST_NEWSELECTBOX_SELECT,				// [����] ���ο� ���� ���ڿ��� 12������ �ϳ��� �����Ѵ�
	GAMEMSG_RESPONSE_NEWSELECTBOX_SELECT,

	GAMEMSG_REQUEST_NEWSELECTBOX_GETITEM,				// [����] ���ο� ���� ���ڿ��� 12������ �ϳ��� �����Ѵ�
	GAMEMSG_RESPONSE_NEWSELECTBOX_GETITEM,
	GAMEMSG_RESPONSE_VALENTINE_PRIZEGET,				// �߷�Ÿ�ε��� ��ǰ�� �޾Ҵ�.


	//=======================================================================
	// [����] ���ո���.
	//-----------------------------------------------------------------------
	GAMEMSG_REQUEST_ITEM_LIST,							// ���ո����� �ش� ������ �ֹ� ���� ���.
	GAMEMSG_RESPONSE_ITEM_LIST,							//

	GAMEMSG_REQUEST_SELL_NEWMARKET,						// ���ո��Ͽ� �Ǹ� �ֹ� �ֱ�.
	GAMEMSG_RESPONSE_SELL_NEWMARKET,					//

	GAMEMSG_REQUEST_BUY_NEWMARKET,						// ���ո��Ͽ��� ���� �ϱ�.
	GAMEMSG_RESPONSE_BUY_NEWMARKET,						//

	GAMEMSG_REQUEST_RECALL_NEWMARKET,					// ���ո��Ͽ��� �Ǹ� �ֹ��� ������ ȸ���ϱ�.
	GAMEMSG_RESPONSE_RECALL_NEWMARKET,					//

	GAMEMSG_REQUEST_NEWMARKETACCOUNT,					//[����] ���ո��Ͽ� �÷��� �� ��ǰ ��� ��û
	GAMEMSG_RESPONSE_NEWMARKETACCOUNT,

	GAMEMSG_REQUEST_NEWMARKETITEMLIST,					//[����] ���ո��Ͽ� ����� �ϴ� ��ǰ ��� ��û
	GAMEMSG_RESPONSE_NEWMARKETITEMLIST,

	GAMEMSG_REQUEST_GETFROMNEWMARKET,					//[����] ���ո��Ͽ� ������ ȸ���϶�� ��û. 
	GAMEMSG_RESPONSE_GETFROMNEWMARKET,

	GAMEMSG_REQUEST_NEWSELLITEM,						//[����] ���ո��Ͽ� ��ǰ�� �� ���� ��û�Ѵ�. 
	GAMEMSG_RESPONSE_NEWSELLITEM,

	GAMEMSG_REQUEST_NEWBUYITEM,							//[����] ���ո��Ͽ� ��ǰ�� �� ���� ��û�Ѵ�. 
	GAMEMSG_RESPONSE_NEWBUYITEM,

	GAMEMSG_REQUEST_SETNEWMARKETFEE,					//[����] ���ո��Ͽ� ������ ���� ��û. 
	GAMEMSG_RESPONSE_SETNEWMARKETFEE,
	//=======================================================================

	//=======================================================================
	GAMEMSG_REQUEST_GUILDHUNTMAPWAR_MAPREGISTER,				//[����]  ��� ����� ���� �ʵ��
	GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_MAPREGISTER,

	GAMEMSG_REQUEST_GUILDHUNTMAPWAR_WARREGISTER,				//[����]  ��� ����� ����� ��û
	GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_WARREGISTER,
	
	GAMEMSG_REQUEST_GUILDHUNTMAPWAR_REQUEST_WARP,				//[����]  ��� ����� ��������� �Ұ��ΰ� ���� 
	GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_REQUEST_WARP,
	
	GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_START,						//[����] ����� ���� �˸�
	
	GAMEMSG_REQUEST_GUILDHUNTMAPWAR_GETTOP10,					//[����]  ��� ����� ����� �ʺ� top10
	GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_GETTOP10,

	GAMEMSG_REQUEST_GUILDHUNTMAPWAR_WAREND,					//[����]  ��� ����� ����� ����
	GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_WAREND,
	
	GAMEMSG_REQUEST_GUILDHUNTMAPWAR_ADD_KILLPOINT,					//[����]  ��� ����� ų����Ʈ �߰�
	GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_ADD_KILLPOINT,

	GAMEMSG_REQUEST_GUILDHUNTMAPWAR_MAPUSERLIST,
	GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_MAPUSERLIST,
	
	GAMEMSG_REQUEST_GUILDHUNTMAPWAR_SERVERTIME,					//[����]  ��� ����� ���� �����ð��� �˾ƿ´�
	GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_SERVERTIME,

	//////////////////////////////////////////////////////////////////////////
	
	GAMEMSG_REQUEST_PROMOTERNPC_GIVE_ITEM_GET,					//[����] ���θ��� �ý��ۿ��� �ִ� ������.
	GAMEMSG_RESPONSE_PROMOTERNPC_GIVE_ITEM_GET,

	GAMEMSG_REQUEST_PROMOTER_INFO_TOTAL_GET,					//[����] ���θ��� ���� ��ü ����. (ĳ���Ϳ� URL)
	GAMEMSG_RESPONSE_PROMOTER_INFO_TOTAL_GET,

	GAMEMSG_REQUEST_PROMOTER_INFO_GET,							//[����] ���θ��� ĳ���� ����.
	GAMEMSG_RESPONSE_PROMOTER_INFO_GET,

	GAMEMSG_REQUEST_PROMOTER_URL_GET,							//[����] ���θ��� URL ����.
	GAMEMSG_RESPONSE_PROMOTER_URL_GET,							
 
	GAMEMSG_REQUEST_PROMOTER_SET,								//[����] ���θ��� ������ ����.
	GAMEMSG_RESPONSE_PROMOTER_SET,							
	
	GAMEMSG_REQUEST_PROMOTER_WARP,								//[����] ���θ��Ͱ� �ڽ��� ��õ�� ĳ������ �̵��Ѵ�

	GAMEMSG_RESPONSE_RECOMMEND_INTRODUCE,						//[����] ���θ��Ϳ��� ������ ĳ���� �ڽ��� �Ұ��Ѵ�.
	GAMEMSG_RESPONSE_RECOMMENDEE_INTRODUCE,						//[����] �����⿡�� ���θ��� ĳ���� �ڽ��� �Ұ��Ѵ�.
	
	//////////////////////////////////////////////////////////////////////////
	

	GAMEMSG_REQUEST_GUILDHUNTMAPWAR_HAVEMAP,					//[����] ��� ����ͽ�û�� �ߴ°�.
	GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_HAVEMAP,
	
	GAMEMSG_REQUEST_GUILDHUNTMAPWAR_SENDMATCHINGRESULT,			//[����] ��Ī����Ʈ ����� �� ����� �����鿡�� �˷��ش�
	GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_SENDMATCHINGRESULT,

	GAMEMSG_REQUEST_TREASUREEVENT_KILLNPC,						// [����] ����ã�� �̺�Ʈ ���� �蹶ġ�� Ŭ���ϰ� ���� �׿� ������.
	GAMEMSG_RESPONSE_TREASUREEVENT_KILLNPC,						//

	GAMEMSG_REQUEST_TREASUREEVENT_USEOKARA,						// [����] ����ã�� �̺�Ʈ ��ī�� 10���� �ƹ�¦�� ������� ���� �ޱ�..
	GAMEMSG_RESPONSE_TREASUREEVENT_USEOKARA,	

	// ��ȥ�ý���
	GAMEMSG_REQUEST_WEDDING_RESERVE,							// [����] ��ȥ �����ϱ�
	GAMEMSG_RESPONSE_WEDDING_RESERVE,

	GAMEMSG_REQUEST_WEDDING_SIMPLELIST_GET,						// [����] ��ȥ ���� ����Ʈ ��������
	GAMEMSG_RESPONSE_WEDDING_SIMPLELIST_GET,

	GAMEMSG_REQUEST_WEDDING_QUESTION_ANSWER,					// [����] ��ȥ ���� ������ �亯�Ѵ�

	GAMEMSG_REQUEST_WEDDING_LIST_GET,							// [����] ��ȥ ����Ʈ ��������
	GAMEMSG_RESPONSE_WEDDING_LIST_GET,

	GAMEMSG_REQUEST_WEDDING_HALL_ENTER,							// [����] ������ ����

	GAMEMSG_REQUEST_WEDDING_RESERVE_CANCEL,						// [����] ��ȥ�� ����ϱ�
	GAMEMSG_RESPONSE_WEDDING_RESERVE_CANCEL,					

	GAMEMSG_REQUEST_MARRIAGEMATE_WARP,							// [����] ����ڿ��� �����ϱ�	

	GAMEMSG_REQUEST_BALANCECANUSECURRENCY,						// [��ȣ] ��밡�� ��ȭ�� ��û
	GAMEMSG_RESPONSE_BALANCECANUSECURRENCY,						// [��ȣ] ��밡�� ��ȭ�� ����

	GAMEMSG_RESPONSE_GETBALANCECANUSECURRENCY,					// [��ȣ] GM�� ��û�� ��� ���� ��ȭ��

	GAMEMSG_REQUEST_FAMILY_REQUEST_ADD_CHILDREN,				// [����] ������ �ڳ� �߰� ��û
	GAMEMSG_RESPONSE_FAMILY_REQUEST_ADD_CHILDREN,				// [����] 

	GAMEMSG_REQUEST_FAMILY_ADD_FAMILY,							// [����] ���� �߰�
	GAMEMSG_RESPONSE_FAMILY_ADD_FAMILY,							// [����] 

	GAMEMSG_REQUEST_FAMILY_DEL_CHILDREN,						// [����] ������ �ڳ� ����
	GAMEMSG_RESPONSE_FAMILY_DEL_CHILDREN,						// [����]

	GAMEMSG_REQUEST_FAMILY_GET_FAMILYINFO,						// [����] ���� ���� �ޱ�
	GAMEMSG_RESPONSE_FAMILY_GET_FAMILYINFO,						// [����]

	GAMEMSG_REQUEST_FAMILY_UPDATE,								// [����] �������� ������Ʈ
	GAMEMSG_RESPONSE_FAMILY_UPDATE,								// [����] 

	GAMEMSG_REQUEST_FAMILY_WARP,								// [����] ��ǥ �������� ���� 
	GAMEMSG_RESPONSE_FAMILY_WARP,								// [����]

	GAMEMSG_REQUEST_FAMILY_CHAT,								// [����] ����ê
	GAMEMSG_RESPONSE_FAMILY_CHAT,								// [����]

	GAMEMSG_REQUEST_FAMILY_PLUS_FAMILYEFFECT,					// [����] ����ȿ�� �Ⱓ ����
	GAMEMSG_RESPONSE_FAMILY_PLUS_FAMILYEFFECT,					// [����]

	GAMEMSG_REQUEST_SOULGUARD_STATUSINOUT,						// [����] ��ȣ���� : ��ȯ/����
	GAMEMSG_RESPONSE_SOULGUARD_STATUSINOUT,						// [����]

	GAMEMSG_RESPONSE_SOULGUARD_FELLOWSHIPSET,					// [����] ��ȣ���� : ģȭ�� �����

	GAMEMSG_REQUEST_SOULGUARD_CHANGENAME,						// [����] ��ȣ���� : �̸� ����
	GAMEMSG_RESPONSE_SOULGUARD_CHANGENAME,						// [����]

	GAMEMSG_REQUEST_SOULGUARD_DEAD,								// [����] ��ȣ���� : ����
	GAMEMSG_RESPONSE_SOULGUARD_DEAD,							// [����]

	GAMEMSG_RESPONSE_SOULGUARD_GET,								// [����] ��ȣ���� : ĳ���Ϳ� �ִ� ���� ��������

	GAMEMSG_RESPONSE_SOULGUARD_HOUSE_GET,						// [����] ��ȣ���� ������ ���� ������

	GAMEMSG_REQUEST_SOULGUARD_HOUSE_CHANGE,						// [����] ĳ���Ϳ� �ִ� ��ȣ���ɰ� �����ҿ� �ִ� ��ȣ������ �±�ȯ �Ѵ�

	GAMEMSG_REQUEST_SOULGUARD_HOUSE_CREATE,						// [����] ��ȣ���� ������ ������ �ø�
	GAMEMSG_RESPONSE_SOULGUARD_HOUSE_CREATE,					// [����]


	//Switch_10MonthEvent_RacoonDodge
	GAMEMSG_REQUEST_RACOONDODGE_EVENT_RESERVATION,				// [����] ���� �̺�Ʈ ���� 
	GAMEMSG_RESPONS_RACOONDODGE_EVENT_RESERVATION,				// [����]
	GAMEMSG_REQUEST_RACOONDODGE_EVENT_REQUEST_PLAYEVENT,		// [����] ���� �̺�Ʈ �÷��� ���� �Ǿ��� �Ұ��� ���� ���� 
	GAMEMSG_RESPONS_RACOONDODGE_EVENT_REQUEST_PLAYEVENT,		// [����]
	GAMEMSG_REQUEST_RACOONDODGE_EVENT_WAIT5SECOND,				// [����] ���� �̺�Ʈ5�� ��� 
	GAMEMSG_RESPONS_RACOONDODGE_EVENT_WAIT5SECOND,				// [����]
	GAMEMSG_REQUEST_RACOONDODGE_EVENT_OVER5SECOND_START,		// [����] 5�� �ð� �� ��ٷ��� ���� �Ѵ�.
	GAMEMSG_RESPONS_RACOONDODGE_EVENT_OVER5SECOND_START,		// [����]
	GAMEMSG_REQUEST_RACOONDODGE_EVENT_GET_RESERVE_LIST,			// [����] ���� ����Ʈ�� ������ �´�
	GAMEMSG_RESPONS_RACOONDODGE_EVENT_GET_RESERVE_LIST,			// [����]
	
	GAMEMSG_REQUEST_RACOONDODGE_EVENT_30SECOND,					// [����] 30�� �ð� ī��Ʈ ����
	GAMEMSG_RESPONS_RACOONDODGE_EVENT_30SECOND,					// [����]
	GAMEMSG_REQUEST_RACOONDODGE_EVENT_ROUNDCOUNT,				// [����] ���� ǥ��
	GAMEMSG_RESPONS_RACOONDODGE_EVENT_ROUNDCOUNT,
	
	GAMEMSG_REQUEST_RACOONDODGE_EVENT_30SECOND_CLEAR,					// [����] 30�� �ð� ī��Ʈ ����
	GAMEMSG_RESPONS_RACOONDODGE_EVENT_30SECOND_CLEAR,					// [����]
	GAMEMSG_REQUEST_RACOONDODGE_EVENT_ROUNDCOUNT_CLEAR,					// [����] ���� ǥ��	����
	GAMEMSG_RESPONS_RACOONDODGE_EVENT_ROUNDCOUNT_CLEAR,					// [����]



	GAMEMSG_REQUEST_DORMANCY_TAKEOUTEQUIPITEMINBOX,				// [����] ���� ���ڿ��� ��� �������� ������
	GAMEMSG_RESPONSE_DORMANCY_TAKEOUTEQUIPITEMINBOX,			// [����] ���� ���ڿ��� ��� �������� ������
	GAMEMSG_RESPONSE_DORMANCY_REFRESHPOINTINFO,					// [����] �������� ���������� �޸� ����Ʈ ����
	GAMEMSG_REQUEST_DORMANCY_BUYPOINTITEM,						// [����] ����Ʈ�� ������ ����

	GAMEMSG_REQUEST_GAWIBAWIBO_CHARGED_MONEY,					//  [8/12/2009 ��ȣ_GAWIBAWIBO] ���������� �ݾ� ����		Client -> Server
	GAMEMSG_RESPONSE_GAWIBAWIBO_CHARGED_MONEY,					//	[8/12/2009 ��ȣ_GAWIBAWIBO] ���������� �ݾ� �������	Server -> Client

	GAMEMSG_REQUEST_GAWIBAWIBO_CALCULATE_RESULT,				//  [8/12/2009 ��ȣ_GAWIBAWIBO] ���������� �¹��� ���		Client -> Server
	GAMEMSG_RESPONSE_GAWIBAWIBO_CALCULATE_RESULT,				//	[8/12/2009 ��ȣ_GAWIBAWIBO] ���������� �¹��� ���		Server -> Client
	GAMEMSG_RESPONSE_GAWIBAWIBO_NOTICE_RESULT,					

	//GAMEMSG_REQUEST_GAWIBAWIBO_COUNT,							//	[8/19/2009 ��ȣ_GAWIBAWIBO] ���������� �������� 		Client -> Server
	//GAMEMSG_RESPONSE_GAWIBAWIBO_COUNT,							//	[8/19/2009 ��ȣ_GAWIBAWIBO] ���������� �������� 		Server -> Client

	GAMEMSG_REQUEST_GAWIBAWIBO_REWARD,							//	[8/20/2009 ��ȣ_GAWIBAWIBO] ���������� ����				Client -> Server
	GAMEMSG_RESPONSE_GAWIBAWIBO_REWARD,							//	[8/20/2009 ��ȣ_GAWIBAWIBO] ���������� ����				Server -> Client

	// ���Һ�----------------------------------------------------------------------------------------------
	GAMEMSG_REQUEST_BBB_CHECK_PlAY_CONDITION,				// [����] ���Һ� ���� ���� ���� ���θ� üũ�Ѵ�. (�ٷ��ʵ��̵� or �����ڵ��) 
	GAMEMSG_RESPONSE_BOKBULBOK_CHECK_ENTERMAP_ENABLE,		// [����] �ʿ� ���尡��
	GAMEMSG_RESPONSE_BOKBULBOK_CHECK_WAITLIST_ENABLE,		// [����] ����� ����Ʈ�� ��� ����
	GAMEMSG_RESPONSE_BOKBULBOK_CHECK_ENTRYREQUEST_FAIL,		// [����] �������� �� �� ����.
	
	GAMEMSG_REQUEST_BBB_WAITLIST_ANSWER,					// [����] ���Һ� ����ڸ���Ʈ��� ������.(Ŭ��->����)
	GAMEMSG_RESPONSE_BBB_WAITLIST_ANSWER,					// [����] ����ڸ���Ʈ(����->Ŭ��)
	
	GAMEMSG_REQUEST_BBB_WAITLIST_CANCEL,					// [����] ��� ��� ��û (Ŭ��->����)
	GAMEMSG_RESPONSE_BBB_WAITLIST_CANCEL,					// [����] ��� ��� ��û�� ���� ���� (����->Ŭ��)
	
	GAMEMSG_RESPONSE_BBB_STAGESTART,						// [����] �� �������� �����Ҷ� Ŭ��� ������ �޼���
	
	GAMEMSG_REQUEST_BBB_STAGEFAIL,							// [����] �������� ���� (Ŭ��->����)
	GAMEMSG_RESPONSE_BBB_STAGEFAIL,							// [����] �������� ���� (����->Ŭ��)

	GAMEMSG_RESPONSE_BBB_WARPMAPQUESTION,					// [����] ����� 1�������� ������ "���� ���Ӹ����� �����ҷ���?" �޼��� (����->Ŭ��)
	GAMEMSG_REQUEST_BBB_WARPMAPANSWER,						// [����] ����� 1������ ���� GAMEMSG_REQUEST_BBB_WARPMAPQUESTION �޼����� ���� ���� (Ŭ��->����);

	GAMEMSG_RESPONSE_BBB_NOTENOUGHMONEY,					// [����] ���� ������ �����ϴٰ� Ŭ�� �˷��� (����->Ŭ��)
	GAMEMSG_RESPONSE_BBB_STAGECLEAR,						// [����] �������� Ŭ����� ������ Win �̹��� (�� �������� Ŭ����� ���)
	GAMEMSG_RESPONSE_BBB_TOTALSTAGECLEAR,					// [����] ���� �������� Ŭ����� ������ Win �̹��� (���� �ѹ��� ���)

	GAMEMSG_RESPONSE_BBB_GM_SHOWMONSTERTYPE,				// [����] gm ��ɾ�� ���� �Ӹ����� �������� ���� ��� (�׽�Ʈ ����)
	GAMEMSG_RESPONSE_BBB_10CLEARNOTICE,						// [����] 10�ܰ� Ŭ���� ���� ������ ��ü ���� �Ѵ�.
	GAMEMSG_REQUEST_BBB_ALREADYRESERVED,					// [����] �̹� ���� �Ǿ� �ִ��� ���� 
	GAMEMSG_RESPONSE_BBB_ALREADYRESERVED,					// [����] �̹� ���� �Ǿ� �ִ����� ���� �亯  
	//-----------------------------------------------------------------------------------------------------

	GAMEMSG_REQUEST_2010NEWYEAREVENT_QUESTCANCEL,			// [����] 2010�ų��̺�Ʈ - ����Ʈ ���� �޼���
	GAMEMSG_RESPONSE_GOONZUDAYMISSION,						// [����] ���ֵ��� - �̺�Ʈ ���������� ������ �̼ǿ� ���� �뺸


	GAMEMSG_REQUEST_NEWNPCREPAIR,								// [����] ���ο� ������ ���� �޽���
	GAMEMSG_RESPONSE_NEWNPCREPAIR,								// [����] ���ο� ������ ���� �޽���

	GAMEMSG_REQUEST_NEWITEMREPAIR,								// [����] ���ο� ������ ���� �޽���
	GAMEMSG_RESPONSE_NEWITEMREPAIR,								// [����] ���ο� ������ ���� �޽���

	GAMEMSG_REQUEST_NEWITEMREPAIRREQUESTINFO,					// [����] ������ ���� �Ƿ� ���� ��û
	GAMEMSG_RESPONSE_NEWITEMREPAIRREQUESTINFO,					// [����] ������ ���� �Ƿ� ���� ��û

	GAMEMSG_REQUEST_FESTIVAL_EVENT_ENTERFIELD_EVENTAREA,		// [����] ���� �̺�Ʈ �������� �̵� ��û

	GAMEMSG_REQUEST_HALLOWEENSPIRITBOX_OK,						// [��ȣ] �ҷ��� ���Ǹ� �ڽ� Ȯ�ν�

	GAMEMSG_REQUEST_MONSTERCREATE,								// [���] ���� ���� ��û
	GAMEMSG_RESPONSE_MONSTERCREATE,								// [���] ���� ���� ��û

	GAMEMSG_REQUEST_EQUIPMENTCREATE,							// [���] ��� ���� ��û
	GAMEMSG_RESPONSE_EQUIPMENTCREATE,							// [���] ��� ���� ��û

	// �ʺ��� ��Ƽ ����Ʈ �ý��� (��Ƽ��Ī)-----------------------------------------------------
	GAMEMSG_REQUEST_PARTYMATCHING_LEVEL,						// [����] ��Ƽ ����Ʈ ���� ���� ���� üũ ��û
	GAMEMSG_RESPONSE_PARTYMATCHING_LEVEL,						// [����] ��Ƽ ����Ʈ ���� ���� ���� üũ ����

	GAMEMSG_REQUEST_APPYLYTOPARTYJOIN,							// [����] ��Ƽ ���� ��û ��û
	GAMEMSG_RESPONSE_APPLYTOPARTYJOIN,

	GAMEMSG_REQUEST_CREATEMYPARTY,								// [����] ��Ƽ ����� ��û
	GAMEMSG_RESPONSE_CREATEMYPARTY,

	GAMEMSG_REQUEST_CREATECOMPLETEPARTY,						// [����] ���� �Է� �� ��Ƽ ���� ��û.
	GAMEMSG_RESPONSE_CREATECOMPLETEPARTY,						// [����] ��Ƽ ���� ���

	GAMEMSG_REQUEST_REMOVEPARTYMATCHING,						// [����] ��ȭ������ ��Ƽ��Ī ���� ��ư ��������

	GAMEMSG_REQUEST_GETPARTYMEMBERNAMELIST,						// [����] ������ ��Ƽ��Ī�� ��Ƽ�� �̸� ������ ��û
	GAMEMSG_RESPONSE_GETPARTYMEMBERNAMELIST,					// [����] ��Ƽ��� �̸� ��û�� ���� ���� ó�� ����

	GAMEMSG_RESPONSE_PARTYMATCHINGEXCEPTION,					// [����] ��Ƽ��Ī ��� ������ ���� �߻��Ѱ� Ŭ�� �˷���


	//-------------------------------------------------------------------------------------------------------------------
	//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����
	//-------------------------------------------------------------------------------------------------------------------
	GAMEMSG_REQUEST_RACCOONEVENT_TOGOONZU,						//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����
	GAMEMSG_RESPONSE_RACCOONEVENT_TOGOONZU,						//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����

	GAMEMSG_REQUEST_GOONZURACCOONEVENT_SETINFO,					//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����-���������� ������´�
	GAMEMSG_RESPONSE_GOONZURACCOONEVENT_SETINFO,				//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����

	//-------------------------------------------------------------------------------------------------------------------
	//[����] ��ų
	//-------------------------------------------------------------------------------------------------------------------
	GAMEMSG_REQUEST_SKILLBOOK_BUYITEM,							// ��ų�� ������ ����.
	GAMEMSG_RESPONSE_SKILLBOOK_BUYITEM,		
	GAMEMSG_RESPONSE_SKILLBOOK_MAGICINFO_GET,					// ��ų������ ���ο� ���� ȹ��.
	GAMEMSG_RESPONSE_SKILLBOOK_MAGIC_ADD,						// ��ų������ ���ο� ���� ȹ��.
	GAMEMSG_RESPONSE_SKILLBOOK_MAGIC_DEL,						// ��ų������ ���ο� ���� ȹ��.
	GAMEMSG_RESPONSE_SKILLBOOK_SUBMAGIC_ADD,					// ��ų������ ���� ���� ȹ��.
	GAMEMSG_REQUEST_SKILLBOOK_SUBMAGIC_DEL,						// ��ų������ ���� ���� ȹ��.
	GAMEMSG_RESPONSE_SKILLBOOK_SUBMAGIC_DEL,					// ��ų������ ���� ���� ȹ��.
	GAMEMSG_REQUEST_SKILLBOOK_SUBMAGIC_LIST_GET,				// ��ų������ ���� ���� ȹ��.
	GAMEMSG_RESPONSE_SKILLBOOK_SUBMAGICLIST_DEL,				// ��ų������ ���� ���� ȹ��.
	GAMEMSG_RESPONSE_CURSEINFO,

	
	//-------------------------------------------------------------------------------------------------------------------
	//[����] ��Ʋ�ξ�
	//-------------------------------------------------------------------------------------------------------------------
	GAMEMSG_RESPONSE_BATTLEROYAL_NOTICERESULT,					// [����] ��Ʋ�ξ� - ���� ��� �޽���
	GAMEMSG_REQUEST_BATTLEROYAL_REMAINEDTIME,					// [����] ��Ʋ�ξ� - ���� �ð� 
	GAMEMSG_RESPONSE_BATTLEROYAL_REMAINEDTIME,					// [����] ��Ʋ�ξ� - ���� �ð� 
	GAMEMSG_RESPONSE_BATTLEROYAL_STARTGAME,						// [����] ��Ʋ�ξ� - ���� ����
	GAMEMSG_RESPONSE_BATTLEROYAL_ENDGAME,						// [����] ��Ʋ�ξ� - ���� ����
	GAMEMSG_RESPONSE_BATTLEROYAL_POWERUPMODE,					// [����] ��Ʋ�ξ� - ĳ���� �Ŀ��� ���
	GAMEMSG_REQUEST_BATTLEROYAL_MOVETOSTADIUM,					// [����] ��Ʋ�ξ� ��������� �̵�
	GAMEMSG_RESPONSE_BATTLEROYAL_OPENSTADIUM,					// [����] ��Ʋ�ξ� - ������� ����
	//=======================================================================

	//[����] 2010�ų��̺�Ʈ
	GAMEMSG_RESPONSE_FORTUNERESULT,								// [����] ���� ��� ���� ����� Ŭ�� �뺸�Ѵ�

	//-------------------------------------------------------------------------------------------------------------------
	// [����] ��ũ�� ���� ���� �м�
	//-------------------------------------------------------------------------------------------------------------------
	GAMEMSG_REQUEST_RECORD_ACTION,				// [2009.06.29 ������] Ŭ���̾�Ʈ�� �ൿ�� ���
	GAMEMSG_RESPONSE_RECORD_ACTION,				// [2009.06.29 ������] Ŭ���̾�Ʈ�� �ൿ�� ���
	GAMEMSG_REQUEST_RECORD_ACTION_FINISHED,		// [2009.06.29 ������] Ŭ���̾�Ʈ�� �ൿ ��� �Ϸ�
	GAMEMSG_RESPONSE_RECORD_ACTION_FINISHED,	// [2009.06.29 ������] Ŭ���̾�Ʈ�� �ൿ ��� �Ϸ��� ��ڿ��� ����

	GAMEMSG_GZFTP_PROTOCOL,						// [2009.06.30 ������] GZFtpProtocol


	GAMEMSG_REQUEST_WARP_TARGETWORLD,									//[����] ��ǥ �������� ���� ���󰡴� Ƽ�� ->������ ������常 ����
	GAMEMSG_RESPONSE_WARP_TARGETWORLD,

	GAMEMSG_REQUEST_PARTY_QUEST_CHECKSTART,								// [��ȣ] ��Ƽ����Ʈ ���� ���� üũ
	GAMEMSG_RESPONSE_PARTY_QUEST_CHECKSTART,							
	GAMEMSG_REQUEST_PARTY_QUEST_START,									// [��ȣ] ��Ƽ����Ʈ ���� ��û
	GAMEMSG_RESPONSE_PARTY_QUEST_START,	
	GAMEMSG_RESPONSE_PARTY_QUEST_UPDATE,								// ��Ƽ����Ʈ ����
	GAMEMSG_RESPONSE_PARTY_QUEST_GIVEUP,								// ��Ƽ����Ʈ ����

	GAMEMSG_REQUEST_CONTRIBUTION_ITEM_LIST,								// [����] ��� �� �������� ������ ����� �������� ���� ȹ��.
	GAMEMSG_RESPONSE_CONTRIBUTION_ITEM_LIST,

	GAMEMSG_REQUEST_CONTRIBUTION_ITEM_LIST_INPUT,
	GAMEMSG_RESPONSE_CONTRIBUTION_ITEM_LIST_INPUT,

	GAMEMSG_REQUEST_CONTRIBUTION_ITEM_INPUT,							// [����] ������ ���.
	GAMEMSG_RESPONSE_CONTRIBUTION_ITEM_INPUT,	

	GAMEMSG_REQUEST_CONTRIBUTION_MAKE_NPC,								// [����] ������ ��ΰ� �Ϸ�ǰ� NPC�� ���鶧.

	//-------------------------------------------------------------------------------------------------------------------
	// [����] �߷�Ÿ�ε��� �̺�Ʈ 
	//-------------------------------------------------------------------------------------------------------------------
	GAMEMSG_RESPONSE_VALENTINEEVENT_CHANGEBUF,	
	GAMEMSG_RESPONSE_VALENTINEEVENT_BUF,	
	GAMEMSG_RESPONSE_VALENTINEEVENT_START,	
	GAMEMSG_RESPONSE_VALENTINEEVENT_END,
	GAMEMSG_REQUEST_VALENTINEEVENT_ISHOLDING,		
	GAMEMSG_RESPONSE_VALENTINEEVENT_ISHOLDING,	
	GAMEMSG_REQUEST_VALENTINEEVENT_GIVE_PRESENT_TONPC,		
	GAMEMSG_RESPONSE_VALENTINEEVENT_GIVE_PRESENT_TONPC,	
	
	GAMEMSG_RESPONSE_GIANTRACCOON_RESURRECT_EVENT_START,			// [����] ���̾�Ʈ ���� ��Ȱ �̺�Ʈ ���� �˸�.
	GAMEMSG_REQUEST_GIANTRACCOON_RESURRECT_EVENT_ITEM_GET,			// [����] ���̾�Ʈ ���� ��Ȱ �̺�Ʈ�� ��Ȱž�� �ϰ��ϸ� �������� �ش�.
	GAMEMSG_REQUEST_NPOTRACCOON_ITEM_GET,							// [����] ���̾�Ʈ ���� ��Ȱ ���� ����ϸ� ���̾�Ʈ ���� ��Ȱ �� ��Ʈ ���.
	

	GAMEMSG_REQUEST_MAKEPERSONALSHOP_MANUFACTURE,					//[����]	���� �Ƿ� �������̽� ���� 
	GAMEMSG_RESPONSE_MAKEPERSONALSHOP_MANUFACTURE,

	GAMEMSG_REQUEST_SEARCHMANUFACTURE,								//[����] ���� �Ƿ� �������̽� ���� -> �˻� 
	GAMEMSG_RESPONSE_SEARCHMANUFACTURE,
	
	GAMEMSG_REQUEST_GO_RACCOONWORLD,								//[����] �������� �̵� 
	GAMEMSG_RESPONSE_GO_RACCOONWORLD,
	// [����] ���� ���� ���ڿ��� �������� �ش� 
	GAMEMSG_REQUEST_OPEN_LEVEL_LIMIT_BOX,							//[����] ���� ���� ���ڸ� ������- �߱��� ��� �Ѵ� 
	GAMEMSG_RESPONSE_OPEN_LEVEL_LIMIT_BOX,
	
	GAMEMSG_REQUEST_PVPMAPWARP,										//[����] �����̵��̿���� �̿��Ͽ� pvp����ͷ� �̵��Ѵ�.

	GAMEMSG_REQUEST_JUSTITEMUSE,									//[����] // �׾��� ���� ���Ȳ�̴� �������� ���δ�
	
	//[����] �߷�Ÿ�� ���� ���� ������.
	GAMEMSG_REQUEST_VALENTINEDAY_ITEM_PACKING,						// �����Ƿ�.
	GAMEMSG_RESPONSE_VALENTINEDAY_ITEM_PACKING,
	GAMEMSG_REQUEST_VALENTINEDAY_BUY_ITEM,							// ����.
	GAMEMSG_RESPONSE_VALENTINEDAY_BUY_ITEM,
	GAMEMSG_REQUEST_VALENTINEDAY_CONFESSION_QUESTION,				// ���.
	GAMEMSG_RESPONSE_VALENTINEDAY_CONFESSION_QUESTION,
	GAMEMSG_REQUEST_VALENTINEDAY_CONFESSION_ANSWER,					// ���.
	GAMEMSG_RESPONSE_VALENTINEDAY_CONFESSION_ANSWER,

	
	
	
	
	
	
	GAMEMSG_END	//���� �޽����� �ƴ� ������. 

};



#pragma pack(1)

//-------------------------------------------------------------------
// Ŭ���̾�Ʈ���� ������ ������ �Ϲ����� ���� �޽����� ���� ����. 
//-------------------------------------------------------------------
#define MAX_CLTMSG_DATA_SIZE   11000 // 4�� ������� �Ѵ�. 

class cltMsg{
public:
	sPacketHeader clHead;	

	union{
		BYTE    cData[MAX_CLTMSG_DATA_SIZE];				// ���� �����Ͱ� ����ִ� ����. 
		SI32	siData32[MAX_CLTMSG_DATA_SIZE/4];
	};


	cltMsg(){};

	cltMsg(UI16 type, SI32 datasize, const BYTE* pdata)
	{
		clHead.usCmd	=	type;

		if(datasize >= MAX_CLTMSG_DATA_SIZE)
		{
			MsgBox(TEXT("cltMsg"), TEXT("type:%d datasize:%d"), type, datasize);
		}
		else
		{
			clHead.usSize	=	sizeof(sPacketHeader) + datasize;

			if(pdata && datasize)
			{
				memcpy(cData, pdata, datasize);
			}
		}
	}

	// 32bit ���� ������ ������.
	cltMsg(UI16 type, SI32 sidata)
	{
		clHead.usCmd	=	type;
		clHead.usSize	=	sizeof(sPacketHeader) + sizeof(SI32);

		siData32[0] = sidata;
	}

	SI32 GetTotalSize(){return clHead.usSize;}
	SI32 GetDataSize(){return clHead.usSize - sizeof(sPacketHeader);}
};

#pragma pack()


//-------------------------------------------------------
// ���ֿ��� �� ������ �ȸ� ������ Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
//-------------------------------------------------------
class cltGameMsgResponse_MarketSellInfo{
public:
	SI32 siUnique;		// ������ ����ũ.
	SI32 siItemNum;		// �ȸ� ����. 
	GMONEY siPrice;		// �ܰ�. 

	cltGameMsgResponse_MarketSellInfo(SI32 unique, SI32 itemnum, GMONEY price)
	{
		siUnique	= unique;
		siItemNum	= itemnum;
		siPrice		= price;
	}
};

//----------------------------------
// Ŭ���̾�Ʈ�� ���Ӽ����� �������� �� 
// CharUnique,��ȣȭŰ���� Ŭ���̾�Ʈ�� ������. 
//----------------------------------
class cltGameMsgResponse_ClientCharUnique{
public:
	SI32	siCharUnique;
	UI08	uiKey1;
	UI08	uiKey2;
	SI16	siVersion;

	cltGameMsgResponse_ClientCharUnique(SI32 charunique, UI08 key1, UI08 key2, SI16 version)
	{
		siCharUnique	= charunique;
		uiKey1			= key1;
		uiKey2			= key2;
		siVersion		= version;
	}
};

//-----------------------------------
// ������ �Ǿ����� �뺸 (��������, �����..) 
//-----------------------------------
class cltGameMsgResponse_LevelUp{
public:
	SI16 siCharUnique;		// ������ ���� ĳ����
	SI08 siLevel;			// ������ �ö� �ᱹ �󸶰� �Ǿ��°�?(���� ����) 
	SI08 siFameLevel;		// ������ �ö� �ᱹ �󸶰� �Ǿ��°�?(�� ���)

	cltGameMsgResponse_LevelUp(SI16 charunique, SI08 level, SI08 famelevel)
	{
		siCharUnique	= charunique;
		siLevel			= level;
		siFameLevel		= famelevel;
	}
};

//-----------------------------------
// //KHY - 1205 - ���������� ���� - 
//-----------------------------------
class cltGameMsgResponse_LevelUpNotice{
public:
	TCHAR szName[MAX_PLAYER_NAME];
	SI32 siLevel;			// 0 �̻��̸� �����������̴�.
	SI32 siSkillLevel;		// 0 �̻��̸� ��ų �������̴�.
	SI32 siSkillType;		// 0 �̻��̸� ��ų �������̴�. ��ų�� ������ ��Ÿ����.
	SI16 siMessageType;		// 1 = ��� �޽���. 2= ���� �޽���.



	cltGameMsgResponse_LevelUpNotice(TCHAR* name, SI32 level, SI32 skilllevel,SI32 skilltype ,SI16 messagetype)
	{
		MStrCpy( szName, name, MAX_PLAYER_NAME );
		siLevel			= level;
		siSkillLevel		= skilllevel;
		siSkillType		= skilltype;
		siMessageType	= messagetype;
	}
};

//-----------------------------------
// ���� �Ӵ��û ��� ��û. 
//-----------------------------------
class cltGameMsgRequest_HouseRentApplyCancel{
public:
	SI32 siVillageUnique;		// ��� ����� �Ǵ� ������ ����ũ. 
	cltGameMsgRequest_HouseRentApplyCancel(SI32 villageunique)
	{
		siVillageUnique = villageunique;
	}
};


//-----------------------------------
// ���� �ǹ� ���� 
//-----------------------------------
class cltGameMsgResponse_VillageStruct{
public:
	SI16	VillageUnique;			// ������ �����ϱ� ���� ����ũ. 
	SI16 siVillageStructureInfo[MAX_CONSTRUCTION_NUM];

	cltGameMsgResponse_VillageStruct()
	{
		ZeroMemory(this, sizeof(cltGameMsgResponse_VillageStruct));
	}

	cltGameMsgResponse_VillageStruct(SI32 villageunique, SI16 pstrinfo[])
	{
		VillageUnique	= villageunique;

		for(SI32 i = 0;i < MAX_CONSTRUCTION_NUM;i++)
		{
			siVillageStructureInfo[i]	= pstrinfo[i];
		}
	}
};

class cltGameMsgResponse_GetVillageInfo
{
public:
	SI32			siMasterVillage[ MAX_VILLAGE_NUMBER ];
	SI32			siParentVillage[ MAX_VILLAGE_NUMBER ];
	SI32			siDeclareWarVillage[ MAX_VILLAGE_NUMBER ];
	NDate			clDeclareWarDate[ MAX_VILLAGE_NUMBER ];
	SI32			siVillageMark[ MAX_VILLAGE_NUMBER ];
	SI32			siTotalVillageScore[ MAX_VILLAGE_NUMBER ];
	SI32			siNewYearEventScore[MAX_VILLAGE_NUMBER];
	SI32			siNowWarVillage[ MAX_VILLAGE_NUMBER ];
	cltGameMsgResponse_GetVillageInfo()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_GetVillageInfo ) );
	}
};


class cltGameMsgResponse_GetNowVillageWarInfo
{
public:
	SI32			siNowWarVillage[ MAX_VILLAGE_NUMBER ];

	cltGameMsgResponse_GetNowVillageWarInfo()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_GetNowVillageWarInfo ) );
	}
};

//--------------------------------------------------------
// ���ֿ� �ö�� �ֹ��� ���� ���� ������ ������ ���´�. 
//--------------------------------------------------------
#define LOWPRICE_STOCK_ORDER_NUM	2
class cltLowPriceStockOrderUnit{
public:
	SI32 siItemUnique;		// ����� �Ǵ� ��ǰ�� ����. 
	GMONEY siPrice;			// ��ǰ�� ����. 
	SI32 siAmount;			// ��ǰ�� ����. 

	cltLowPriceStockOrderUnit()
	{
		siItemUnique	= 0;
		siPrice			= 0;
		siAmount		= 0;
	}

	cltLowPriceStockOrderUnit(SI32 unique, GMONEY price, SI32 amount)
	{
		siItemUnique	= unique;
		siPrice			= price;
		siAmount		= amount;
	}


	void Set(cltLowPriceStockOrderUnit* pclunit)
	{
		siItemUnique	= pclunit->siItemUnique;
		siPrice			= pclunit->siPrice;
		siAmount		= pclunit->siAmount;
	}
};

class cltGameMsgResponse_LowPriceStockOrder{
public:
	cltLowPriceStockOrderUnit clUnit[LOWPRICE_STOCK_ORDER_NUM];

	void Add(cltLowPriceStockOrderUnit* pclunit)
	{
		for(SI32 i = 0;i < LOWPRICE_STOCK_ORDER_NUM;i++)
		{
			if(clUnit[i].siItemUnique )continue;

			clUnit[i].Set(pclunit);
			return ;
		}
	}
};


//--------------------------------------
// Person�� �̸��� ��û�Ѵ�. 
//--------------------------------------
class cltGameMsgRequest_GetName{
public:
	SI32 siCharUnique;	// �̸��� ���;� �ϴ� ����� CharUnique
	cltGameMsgRequest_GetName(SI32 charunique)
	{
		siCharUnique = charunique;
	}
};

class cltGameMsgResponse_GetName{
public:
	SI32 siCharUnique;	// �̸��� ���;� �ϴ� ����� CharUnique
	TCHAR szName[MAX_PLAYER_NAME];

	cltGameMsgResponse_GetName(SI32 charunique, TCHAR* name)
	{
		siCharUnique = charunique;
		MStrCpy( szName, name, MAX_PLAYER_NAME );
	}

};

//----------------------------------------------
// Person�� Horse ������ ������. 
//----------------------------------------------
class cltGameMsgResponse_NeighbourHorse{
public:
	SI16		siCharUnique;		// ���� ����. 
	SI16		siHorseUnique;		// �������� ���� ����ũ. 

	cltGameMsgResponse_NeighbourHorse(SI16 charunique, SI16 horseunique)
	{
		siCharUnique	= charunique;
		siHorseUnique	= horseunique;
	}
};


//---------------------------------------------------------------
// ����ǰ ���� �������� �����ϵ��� �Ѵ�. 
//--------------------------------------------------------------
class cltGameMsgRequest_InvRepair{
public:
	SI32	siItemPos;
	cltItem clItem;

	cltGameMsgRequest_InvRepair(SI32 itempos, cltItem* pclitem)
	{
		siItemPos = itempos;
		clItem.Set(pclitem);
	}
};

class cltGameMsgResponse_InvRepair{
public:
	SI32	siItemPos;
	cltItem clItem;

	cltGameMsgResponse_InvRepair(SI32 itempos, cltItem* pclitem)
	{
		siItemPos = itempos;
		clItem.Set(pclitem);
	}
};

//----------------------------------------------------------------
// ���� ����. 
//----------------------------------------------------------------
class cltGameMsgResponse_Notice
{
public:
	SI32	siDataSize;
	SI32	PlayerNameLength;
	//KHY - 0129 - �ϴ� ä��â�� ���� ��¿��θ� �����Ѵ�. - true = ���.
	bool	UseChatBarNotic;
	// ��ڰ� ������ ����	
	bool	m_bGMNotice;

	TCHAR	szChatText[128];

	cltGameMsgResponse_Notice( TCHAR* playername, TCHAR*text ,bool ChatBarNotic, bool bGMNotice=false )
	{
		siDataSize		= sizeof(SI32) + sizeof(SI32);

		UseChatBarNotic	= ChatBarNotic;
		siDataSize		+= sizeof(bool);

		m_bGMNotice		= bGMNotice;
		siDataSize		+= sizeof(bool);

		StringCchCopy( szChatText, MAX_PLAYER_NAME, playername );

		size_t length;
		StringCchLength( szChatText, 128, &length );
		PlayerNameLength = length;

		StringCchCopyN(&szChatText[ PlayerNameLength ], 128, text, 100 );

		StringCchLength( szChatText, 128, &length );
		siDataSize		+= (SI32)length * (SI32)(sizeof(TCHAR)) + 2;		
	}
};

#define HALLOWEENQUEST		1	// �ҷ��� ����Ʈ NPC ��ġ �˸�
#define HALLOWEENSUPRISE	2	// �ҷ��� ��¦ ������ �˸�
//----------------------------------------------------------------
// ����Ʈ �߻��� ��ü �����Ѵ�.( npc ���� ��Ÿ���� ���ؼ�)
//----------------------------------------------------------------
class cltGameMsgResponse_Notice_Quset
{
public:
	SI32 siKind		;
	SI32 siMapIndex	;
	SI32 siType		;

	SI16 siX		;		// �ҷ��� ���Ǿ� ���� ��ǥ
	SI16 siY		;		// �ҷ��� ���Ǿ� ���� ��ǥ

	cltGameMsgResponse_Notice_Quset( SI32 Kind , SI32 MapIndex, SI32 Type, SI16 X, SI16 Y )
	{
		siKind = Kind			;	// �ش� ����Ʈ�� NPC ī�ε� �� ������ 
		siMapIndex = MapIndex	;	// �ش� ����Ʈ�� NPC�� ��Ÿ�� ������ ���ε��� 0 �̸� �������� �ʿ� ����
		siType = Type			;	// ����Ʈ ������ �˷��ٰ��� ��¦ �������� �˷��ٰ��� Ÿ�� 
		siX		=	X			;	// �ҷ��� ���Ǿ� ���� ��ǥ
		siY		=	Y			;	// �ҷ��� ���Ǿ� ���� ��ǥ
	}
};


//-------------------------------------------------------------------
// Person�� �Ѱ� ������ ������ Ŭ���̾�Ʈ�� ������ �޽����� ����ü. 
//-------------------------------------------------------------------
#define PERSONITEMINFO_OPTION_NONE						0	// �ƹ��� �ɼ��� ����. 
#define PERSONITEMINFO_OPTION_SHOW						1	// ȭ�鿡 ������ ǥ�����ش�.
#define PERSONITEMINFO_OPTION_MAKE						2	// ����� �������� �����̴�. (�������� ǥ���ؾ�..) 
#define PERSONITEMINFO_OPTION_WARITEM					3	// ����ǰ�� ȹ���ߴ�. 
#define PERSONITEMINFO_OPTION_MASTER					4	// ��ڿ� ���ؼ� �־��� ������.
#define PERSONITEMINFO_OPTION_WASTE						5	// ������ �Ҹ�� ������. 
#define PERSONITEMINFO_OPTION_QUEST						6	// ����Ʈ�� ���ؼ� �����.
#define PERSONITEMINFO_OPTION_MAKEALMOSTFAIL			7	// ���� ������ ������ ���������. 
#define PERSONITEMINFO_OPTION_MAKEFAIL					8	// ���� ���� ����. 
#define PERSONITEMINFO_OPTION_MAKELUCK					9	// ���� ���� ���� (����� �ۿ�)  
#define PERSONITEMINFO_OPTION_FAMELEVEL					10	// ������ ������� ���� ����. 
#define PERSONITEMINFO_OPTION_SPECIALQUEST				11	// ��ι�����Ʈ�� ���ؼ� ����. 
#define PERSONITEMINFO_OPTION_TOOLWASTE					12	// ��ǰ �������� ������ �������� ����
#define PERSONITEMINFO_OPTION_ROULETTEGAME				13	// �ڴ�� �������� �����
#define PERSONITEMINFO_OPTION_MAKEITEMFAIL_POS			23  //�ϼ�ǰ �ڸ��� �ٸ� ��ǰ�� ����
#define PERSONITEMINFO_OPTION_ENCHANTITEMFAIL			24  //��æƮ ����
#define PERSONITEMINFO_OPTION_LASTENCHANTITEMFAIL		25  //��æƮ ����
#define PERSONITEMINFO_OPTION_NOMATENCHANTITEMFAIL		26  //��æƮ ������
#define PERSONITEMINFO_OPTION_NOSKILLENCHANTFAIL		28  //��æƮ ��ų ����
#define PERSONITEMINFO_OPTION_NOMONEYENCHANTFAIL		29  //������ ���� ����
#define PERSONITEMINFO_OPTION_NOCONDENCHANTFAIL			30  //���ǿ� ���� �ʾ� ����
#define PERSONITEMINFO_OPTION_NOSEALINGUP_ENCHANTFAIL	31  //������ �к��� Ǯ���־ ����
#define PERSONITEMINFO_OPTION_BEGINNERWEAPON			32	// �ʺ��� ���� ����
#define PERSONITEMINFO_OPTION_EVENT						33	// �ų� �̺�Ʈ		
#define PERSONITEMINFO_OPTION_MOFUMOFUEVENT				34	// ���ĸ��� �̺�Ʈ�� �޾Ҵ�.
#define PERSONITEMINFO_OPTION_SERVEREVENTQUEST			35	// ���� �̺�Ʈ ����Ʈ�� �������� �޾Ҵ�
#define PERSONITEMINFO_OPTION_HALLOWEENEVENT			36	// �ҷ��� �귿���� ���並 �޾Ҵ�.
#define PERSONITEMINFO_OPTION_PVP_LEAGUE				37	// PVP���׿��� ��ǥ�޼� ������ �޾Ҵ�.
#define PERSONITEMINFO_OPTION_NEWYEAREVENT				38	// �ų��̺�Ʈ ��귿�� ������ �������� �����.
#define PERSONITEMINFO_OPTION_BUYFROMNEWMARKET			39	// ���ո��Ͽ��� ��ǰ����
#define PERSONITEMINFO_OPTION__TREASUREEVENTITEMUSE		40	// ����ã�� ������ ���
#define PERSONITEMINFO_OPTION_SEQGMCOMMAND				41  // SEQ ��ɾ ����ؼ� �������� ������.
#define PERSONITEMINFO_OPTION_DORMANCY					42  // �޸� ���� �ý���
#define PERSONITEMINFO_OPTION_BATTLEROYAL				43  // ��Ʋ�ξ�
#define PERSONITEMINFO_OPTION_ADDITIONALITEM_GET		44	// �μ����� �������� �����

class cltGameMsgResponse_PersonItemInfo
{
public:
	SI16	siItemPos;
	SI16	siOption;		// Ŭ���̾�Ʈ���� ������ ������ ��� ����Ұ��ΰ� ?
	SI16	siChangedNum;	// ������ ������. 
	SI32	siExp;			// ��ǰ �������� ȹ���� ����ġ. 
	cltItem clItem;
	GMONEY	siPrice;		// �� �������� �ü�. 	

	cltGameMsgResponse_PersonItemInfo()
	{
		siItemPos		= 0;
		siOption		= PERSONITEMINFO_OPTION_NONE;
		siChangedNum	= 0;
		siPrice			= 0;
	}
	cltGameMsgResponse_PersonItemInfo(SI16 itempos, SI16 option,  SI16 changednum, SI32 exp, cltItem* pclitem, GMONEY price)
	{
		siItemPos		= itempos;
		siOption		= option;
		siChangedNum	= changednum;
		siExp			= exp;
		clItem.Set(pclitem);
		siPrice			= price;
	}
};

class cltGameMsgResponse_CrystalItemInfo
{
public:
	SI16	siItemPos;

	cltCrystalItemInfo clCrystalItemInfo; // ���� �������� Crystal ���� ���� (����� ��������)

	cltGameMsgResponse_CrystalItemInfo()
	{
		siItemPos		= 0;
	}
	cltGameMsgResponse_CrystalItemInfo(SI16 itempos, cltItem* pclitem)
	{
		siItemPos		= itempos;

		cltCrystalItemInfo Crystalitem;

		for(SI16 cNum = 0; cNum < MAX_CRYSTAL_NUM ; cNum++)
		{
			Crystalitem.siDurability[cNum] = pclitem->cltItemCrytal[cNum].GetDurability();
		}

		clCrystalItemInfo.Set(&Crystalitem);
	}
};

//-------------------------------------------------------------------
// �ٸ� Person�� ��ü ���� ������ �뺸�Ѵ�.
//-------------------------------------------------------------------
class cltGameMsgResponse_PersonAllShapeInfo
{
public:
	SI32	siCharUnique;

	cltShapeEquipInfo clEquipInfo;

	SI16	siHorse;
	cltDate clAddStatusDate;
	SI32	siStatusTicketNum;

	cltGameMsgResponse_PersonAllShapeInfo()
	{
		siCharUnique	= 0;
		siHorse			= 0;
		clAddStatusDate.MakeFullDateFromDateVary(0);
		siStatusTicketNum = 0;
	}

	cltGameMsgResponse_PersonAllShapeInfo(SI32 charunique, cltShapeEquipInfo* pclEquipInfo,
		SI16 horse,cltDate* cldate,SI32 ticket)
	{
		siCharUnique	= charunique;
		clEquipInfo.Set(pclEquipInfo);

		siHorse			= horse;
		clAddStatusDate.Set(cldate);
		siStatusTicketNum = ticket ;
	}
};


class cltGameMsgResponse_PersonMakeItemSwitch
{
public:
	SI32	siCharUnique;
	SI08    siMakeItemSwitch;

	cltGameMsgResponse_PersonMakeItemSwitch(SI32 charunique, SI08 makeitemswitch)
	{
		siCharUnique	= charunique;
		siMakeItemSwitch = makeitemswitch;
	}
};


//-----------------------------------------------------------------
// ���ֿ� �ö�� Ư�� ��ǰ�� ����� ��û�Ѵ�. 
//-----------------------------------------------------------------
class cltGameMsgRequest_MarketOrder{
public:
	SI16 siItemUnique;			// ��� ��ǰ�� ����ũ. 
	GMONEY siPriceCondition;		// ���� ����. 

	cltGameMsgRequest_MarketOrder(SI32 itemunique, GMONEY pricecondition)
	{
		siItemUnique		= itemunique;
		siPriceCondition	= pricecondition;
	}
};


class cltGameMsgResponse_NewMarketAccount
{
public:

	cltNewMarketAccount	clMarketAccount;

	cltGameMsgResponse_NewMarketAccount(cltNewMarketAccount* pMarketAccount)
	{
		clMarketAccount.Init();
		if( NULL != pMarketAccount )
			clMarketAccount.Set( pMarketAccount );
	}
};

class cltGameMsgRequest_NewMarketItemList{
public:

	enum
	{
		TYPE_NORMAL_LIST = 0,
		TYPE_CHEAP_LIST
	};

	SI16 siItemUnique;			// ��� ��ǰ�� ����ũ. 
	SI16 siRequestPage;
	UI08 uiType;

	cltGameMsgRequest_NewMarketItemList(SI16 itemunique, SI16 requestpage, UI08 type = TYPE_NORMAL_LIST )
	{
		siItemUnique		= itemunique;
		siRequestPage	= requestpage;
		uiType			 = type;
	}
};

class cltGameMsgResponse_NewMarketItemList{
public:

	UI08				uiType;
	SI16				siMaxPage;		
	SI64				siCurrentPrice;
	cltNewTradeOrder	clNewTradeOrder[MAX_NEWMARKET_ITEMLIST];

	cltGameMsgResponse_NewMarketItemList( UI08 type, SI16 maxpage, SI64 CurrentPrice, cltNewTradeOrder* newtradeorder)
	{
		uiType = type;
		siMaxPage		= maxpage;
		siCurrentPrice = CurrentPrice;
		for( SI16 i = 0; i < MAX_NEWMARKET_ITEMLIST; ++i )
			clNewTradeOrder[i].Set( &newtradeorder[i] );
	}
};

//---------------------------------------------------------------
// ����ǰ ���� �к� �������� ������ ��û�Ѵ�.
//--------------------------------------------------------------
class cltGameMsgRequest_Inv_CancellationSealingUp{
public:
	SI32	siItemPos;
	cltItem clItem;

	cltGameMsgRequest_Inv_CancellationSealingUp(SI32 itempos, cltItem* pclitem)
	{
		siItemPos = itempos;
		clItem.Set(pclitem);
	}
};

class cltGameMsgResponse_Inv_CancellationSealingUp{
public:
	SI32	siItemPos;
	cltItem clItem;

	cltGameMsgResponse_Inv_CancellationSealingUp(SI32 itempos, cltItem* pclitem)
	{
		siItemPos = itempos;
		clItem.Set(pclitem);
	}
};

//--------------------------------------------------------
// �Ƿε� �ý����� ���� ���� �� �ð� ��� �Ѵ�.
//--------------------------------------------------------
class cltGameMsgResponse_TiredStateNotice{
public:
	UI08 uiTiredState;
	SI32 siTiredTimeNotice;
	NTCHARStringName	m_kCharName;		// ĳ���� �̸�

	cltGameMsgResponse_TiredStateNotice(UI08 TiredState, SI32 TiredTimeNotice,  NTCHARStringName kCharName)
	{
		uiTiredState = TiredState;
		siTiredTimeNotice = TiredTimeNotice;
		m_kCharName = kCharName;
	}
};

//--------------------------------------------------------
// �������ڸ� ����.
//--------------------------------------------------------
class cltGameMsgResponse_OpenTreasureBox
{
public:
	SI16	siItemPos;
	cltItem	clItem;

	SI16	siKeyItemPos;
	cltItem	clKeyItem;

	SI16	siToItemPos1;
	cltItem clToItem1;
	SI32	siGetItemNumber1;

	SI16	siToItemPos2;
	cltItem clToItem2;
	SI32	siGetItemNumber2;

	cltGameMsgResponse_OpenTreasureBox(SI16 itempos, cltItem* pclitem, SI16 keyitempos, cltItem* pclkeyitem, SI16 toitempos1, cltItem* pcltoitem1, SI32 getitemnumber1 ,SI16 toitempos2 , cltItem* pcltoitem2 , SI32 getitemnumber2 )
	{
		siItemPos		= itempos;
		clItem.Set(pclitem);

		siKeyItemPos		= keyitempos;
		if(pclkeyitem)	clKeyItem.Set(pclkeyitem);

		siToItemPos1		= toitempos1;
		clToItem1.Set(pcltoitem1);
		siGetItemNumber1 = getitemnumber1;

		siToItemPos2		= toitempos2;
		clToItem2.Set(pcltoitem2);
		siGetItemNumber2 = getitemnumber2;
	}
};
// [����] �����ڽ��κ��� ����������� ȹ�������� ������ ��Ŷ
class cltGameMsgResponse_RareItemFromTreasureBox
{
public:
	TCHAR	tszUserName[MAX_PLAYER_NAME]; // �������� ȹ���� User�̸�
	cltItem	cltTreasureBox;				// � �����ڽ��� �����°�?
	cltItem	cltGetItem;					// ���� �������� ����°�?


	cltGameMsgResponse_RareItemFromTreasureBox( TCHAR* ptszUserName, cltItem* pclTreasureBox, cltItem* pclGetItem )
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_RareItemFromTreasureBox ) );

		StringCchCopy( tszUserName, MAX_PLAYER_NAME, ptszUserName );

		cltTreasureBox.Set( pclTreasureBox );
		cltGetItem.Set( pclGetItem );
	}
};

//---------------------------------------------------------------
// ���ݼ���κ��� ������ ������ ��û�Ѵ�.
//--------------------------------------------------------------
class cltGameMsgRequest_Inv_ChangItemFormNpc{
public:
	SI32	siItemPos;		// ������ ������
	UI16	uiStatusNow;	// ���� �������ͽ�
	UI08	uiStatusLater;	// �����ҽ������ͽ�
	//cltItem clItem;

	cltGameMsgRequest_Inv_ChangItemFormNpc(SI32 itempos, UI16	StatusNow, UI08	StatusLater/*, cltItem* pclitem*/)
	{
		siItemPos = itempos;			// ������ ������ 
		uiStatusNow = StatusNow;		//  ������ ���� �������ͽ� ����
		uiStatusLater = StatusLater;	// ������ �������ͽ� 
		//clItem.Set(pclitem);
	}
};

class cltGameMsgResponse_Inv_ChangItemFormNpc{
public:
	SI32	siItemPos;
	cltItem clItem;

	cltGameMsgResponse_Inv_ChangItemFormNpc(SI32 itempos, cltItem* pclitem)
	{
		siItemPos = itempos;
		clItem.Set(pclitem);
	}
};
// [2009.06.29 ������] Ŭ���̾�Ʈ�� �ൿ�� ���
class cltGameMsgRequest_RecordAction
{
public:

	SI32	siAdminPersonID;	

	SI32	siyourpersonid;
	CHAR	szyourip[ 32 ];
	SI32	time_now;

	BOOL	bReportedByAdminCommand;

public:
	cltGameMsgRequest_RecordAction( SI32 _siadminpersonid, SI32 yourpersonid, CHAR *ip, SI32 _timenow, BOOL breportedbyadmincommand )
	{
		siAdminPersonID			=	_siadminpersonid;
		siyourpersonid			=	yourpersonid;

		strncpy( szyourip, ip, 31 );
		time_now				=	_timenow;

		bReportedByAdminCommand	=	breportedbyadmincommand;
	}

};

// [2009.06.29 ������] Ŭ���̾�Ʈ�� �ൿ�� ���(����)
class cltGameMsgResponse_RecordAction
{
public:

	SI32	siResult;

	SI32	siAdminPersonID;
	BOOL	bReportedByAdminCommand;


public:
	cltGameMsgResponse_RecordAction( SI32 _siresult, SI32 _siadminpersonid, BOOL _breportedbyadmincommand )
	{
		siResult					=	_siresult;
		siAdminPersonID				=	_siadminpersonid;
		bReportedByAdminCommand		=	_breportedbyadmincommand;
	}
};

// [2009.06.29 ������]Ŭ���̾�Ʈ�� �ൿ ��� �Ϸ�
class cltGameMsgRequest_RecordActionFinished
{
public:

	SI32	siAdminPersonID;	
	CHAR	szFilePath[ MAX_PATH ];
	BOOL	bReportedByAdminCommand;

public:
	cltGameMsgRequest_RecordActionFinished( SI32 _siadminpersonid, CHAR *pszFilePath, BOOL _breportedbyadmincommand  )
	{
		siAdminPersonID			=	_siadminpersonid;
		strcpy( szFilePath, pszFilePath );
		bReportedByAdminCommand	=	_breportedbyadmincommand ;
	}
};

// [2009.06.29 ������]Ŭ���̾�Ʈ�� �ൿ ��� �Ϸ��� ��ڿ��� ����
class cltGameMsgResponse_RecordActionFinished
{
public:

	CHAR	szCharName[ MAX_PLAYER_NAME ];
	CHAR	szFilePath[ MAX_PATH ];

public:
	cltGameMsgResponse_RecordActionFinished( CHAR *pszPlayerName, CHAR *pszFilePath )
	{
		strncpy( szCharName, pszPlayerName, MAX_PLAYER_NAME - 1 );
		strncpy( szFilePath, pszFilePath, MAX_PATH - 1 );
	}
};

class cltGameMsgGZFTPProtocol
{
public:

	SI32		personid_from;			
	SI32		personid_to;

	enum	GZFtpMsg{	GZFTP_INITIALIZE,						
		GZFTP_REQUEST_GETFILE,
		GZFTP_RESPONSE_GETFILE,
		GZFTP_REQUEST_DATA,
		GZFTP_RESPONSE_DATA

	};


	GZFtpMsg	msg;
	SI32		sibuffersize;

	struct __initialize_data
	{
		SI32	siyourPersonID;
		SI32	siotherPersonID;

		CHAR	szSenderName[ MAX_PLAYER_NAME ];

		BOOL	boption_delete;

		CHAR	szFilePath[ 260 ];			// 260 - MAX_PATH;	
	};

	struct	__req_getfile_data
	{
		DWORD	dwID;

		CHAR	szFilePath[ 260 ];			// 260 - MAX_PATH;	

		BOOL	bDeleteFile;
	};

	struct	__res_getfile_data
	{
		DWORD	dwResult;
		DWORD	dwID;

		LONG	ltotalbytes;
	};

	struct	__req_filedata
	{
		DWORD	dwID;
		BYTE	filedata[ 1024 ];			
		LONG	lsize;
	};

	struct	__res_filedata
	{
		DWORD	dwResult;
		DWORD	dwID;
	};

	union	
	{
		char	buffer[ 1032 ];

		__initialize_data	initialize_data;

		__req_getfile_data	req_getfile_data;

		__res_getfile_data	res_getfile_data;

		__req_filedata		req_filedata;

		__res_filedata		res_filedata;		
	};	

public:

	cltGameMsgGZFTPProtocol( GZFtpMsg _msg, SI32 _personid_from, SI32 _personid_to, BYTE *_buffer, SI32 _sibuffersize )
	{
		msg					=	_msg;

		personid_from		=	_personid_from;
		personid_to			=	_personid_to;

		sibuffersize		=	_sibuffersize;

		memcpy( buffer, _buffer, _sibuffersize );
	}	
};

#endif
