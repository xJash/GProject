#ifndef _DIALOGRESOURCE_H_
#define _DIALOGRESOURCE_H_


////////////////////////////////////// DANGER //////////////////////////////
// ���̾�α� �߰��� �߰��ϸ� �ȵ˴ϴ� >_< - ����
// ������� ���̾�α� ��ġ�� ����ǰ� �ֽ��ϴ�
////////////////////////////////////////////////////////////////////////////


enum
{
	NMSGBOX_DLG,		// 0
	NMSGBOX0_DLG,
	NMSGBOX1_DLG,
	NMSGBOX2_DLG,
	NMSGBOX3_DLG,
	NMSGBOX4_DLG,
	NMSGBOX5_DLG,
	NMSGBOX6_DLG,
	NMSGBOX7_DLG,
	NMSGBOX8_DLG,
	NMSGBOX9_DLG,		// 10
	NCANDIDATE_DLG,
	TOOLBAR_DLG,

	STATUSBAR_DLG,
	NCHAT_DLG,
	TEST_DLG,
	NOTIFYMSG_DLG,
	NOTIFYGETITEM_DLG,
	NOTICEEVENTMSG_DLG,
	MONSTERCORPORATION_DLG,		//������ �̴ϰ���
	NINVENTORY_DLG,		// 20
	NEXITCONFIRM_DLG,
	NEXIT_DLG,
	NITEMINFO_DLG,
	NHUNTMAPINFO_DLG,
	NHOMEPAGE_DLG,
	NRESIDENTSINFO_DLG,
	NMAGICINFO_DLG,
	NNEWMAGICINFO_DLG,
	NFATHER_DLG,
	NCHILD_DLG,
	NPARTY_DLG,			// 30
	NPARTYINVITE_DLG,
	NSOUNDONOFF_DLG,
	NMONSTERINFO_DLG,
	NVILLAGEDETAILINFO_DLG,
	NFRIEND_DLG,
	NFRIENDACCEPT_DLG,
	NQUEST_DLG,
	NDEATH_DLG,
	NPORTPAYTAX,
	NEVENTNOTIC_DLG,	// 40
	NVILLAGEWARINFO_DLG,
	NSELECTWORLDLIST_DLG,
	NMASTERINFO_DLG,
	NBOBUSANG_DLG,
	NFARMING_DLG,
	NRAREITEM_DLG,
	NLOGIN_DLG,
	NMAKEITEM_DLG,
	NSELECTCHAR_DLG,
	NSELECTNOLIMITWARPTICKET_DLG,	// 50
	NMAKECHAR_DLG,
	NNOTICEADMIN_DLG,
	NRECOMMENDPERSON_DLG,
	NVOTEKING_DLG,
	NDELETECHAR_DLG,
	NSEIGEWIN_DLG,
	NFISHING_DLG,
	NFOREIGNMERCHANT_DLG,	
	NTRADEMERCHANTHORSE_DLG,
	NFOREIGNMERCHANTBUYITEM_DLG,	// 60
	NFOREIGNMERCHANTBUYCASHITEM_DLG,
	NTRADEMERCHANT_DLG, // ���� ����
	NTRADEMERCHANTHIGHCLASS_DLG,	// ��ǰ ����
	NHOZOBASE_DLG,	
	NHOZORESIDENT_DLG,
	NHOZOPRIZE_DLG,
	NHOZOCHANGEDNAME_DLG,
	NHOZOFIXATION_DLG,
	NHOZONEWCHARRATE_DLG,
	NHOZOANGEL_DLG,				// 70
	NHOZOANGELAPPYER_DLG,
	NHOZOAPPOINTMENT_DLG,
	NBYUNGZO_DLG,
	NIZOBASE_DLG,
	NIZOPRICEVALUE_DLG,
	NGONGZO_DLG,
	NGOONZU_DLG,
	NYEZOBASE_DLG,
	NYEZOANGEL_DLG,
	NYEZOANGELAPPYER_DLG,		// 80
	NYEZOAPPOINTMENT_DLG,
	NYEZOJAPANWAR_DLG,
	NHYUNGZOBASE_DLG,
	NHYUNGZOANNOUNCEMENT_DLG,
	NHYUNGZOMAIN_DLG,
	NHYUNGZOUSER_DLG,
	NHYUNGZOPOLICE_DLG,
	NHYUNGZOCRIMINAL_DLG,
	NNEWQUEST_DLG,
	NSUMMONUNITBUYNPC_DLG,		// 90
	QUESTVIEWER_DLG,


	CLTNCHARSTATUS_DLG,
	CLTNCHARKINDCHANGE_DLG,
	CLTNHORSETYPECHANGE_DLG,
	CLTNCHARNAMECHANGE_DLG,
	CLTNCHARGREETINGCHANGE_DLG,

	NLETTER_DLG,
	NDECREEPASSWD_DLG,
	NGAMECONTRACT_DLG,
	NAUTOHUNT_DLG,				// 100        
	NNPCMENU_DLG,               //���̱輱��,�߸���Ű ù �޴�
	NNPCREPAIR_DLG,              //�念��

	NINVESTMENT_DLG,            //���̱輱��
	NNPCTRADE1_DLG,              //������
	NBOSSMARKET_DLG,			// ���� ùȭ��
	NBOSSMARKETDETAIL_DLG,		// ���� ��ȭ��
	NHIRENPC_DLG,               //NPC ���


	NPERSONMALINFO_DLG	,
	NPERSONALSHOP_DLG,
	NPERSONALSHOPSEARCH_DLG,	// 110

	NWENNYMAN_DLG,             //Ȥ�θ� ����
	NWENNYMANCHILD1_DLG,
	NWENNYMANCHILD2_DLG,

	NPRIVATETRADEACCEPT_DLG,
	NPRIVATETRADEACCEPT_MSGBOX_DLG,
	NPRIVATETRADE_DLG,    //���ΰŷ� 
	NPTRADECHILD1_DLG,
	NPTRADECHILD2_DLG,
	NPTRADECHILD3_DLG,
	NPTRADECHILD4_DLG,			// 120

	NPTRADEREPRAIR_DLG,   //���� ���� 	
	NITEMMALLMANAGER_DLG, //�����۸� ��ư 
	NITEMMALL_DLG, // �����۸� 
	NHINT_DLG,     //���� �޴�

	NMUDANG_DLG	,
	NMUDANG_EVOLVE_DLG	,
	NMUDANG_REVIVE_DLG	,
	NMUDANG_SCROLL_DLG	,

	NPLAYMATCH_DLG,	// ������, �ٴٸ��� ����..

	NMINING_DLG,			// 130

	NSKILL_DLG,
	NWEAPONSKILL_DLG,
	NHONGGILDONG_DLG,
	NWARJOIN_DLG,

	NRESIDENTS_DLG,

	NMENU_DLG,
	NRIGHTMOUSEMENU_DLG,
	NMINIMAP_DLG,

	NPRIVATECHAT0_DLG,
	NPRIVATECHAT1_DLG,		// 140
	NPRIVATECHAT2_DLG,
	NPRIVATECHAT3_DLG,
	NPRIVATECHAT4_DLG,
	NPRIVATECHAT5_DLG,
	NPRIVATECHAT6_DLG,
	NPRIVATECHAT7_DLG,
	NPRIVATECHAT8_DLG,
	NPRIVATECHAT9_DLG,

	NPRIVATECHATREJECT_DLG,

	NERRORMSGPRINT_DLG,		// 150
	NERRORMSGPRINT1_DLG,
	NDAILYQUEST_DLG	,

	NNOTIFYGETEXPANDITEM_DLG,
	NCITYHALLSUBMIT_DLG	,
	NSTOCK_DISTRIBUTION_DLG	, 
	NEVENT_DLG,	// �ܺ� �̺�Ʈ
	ROULETTEGAME_DLG,	// �ڴ�� �̴ϰ���
	NSAVEITEMLIST_DLG,
	NGUILDCHAT_DLG,			// ��� ä��


	NPERSONALSHOP_POP_DLG,	// 160

	// �ǹ� ���̾�α� 
	NSTR_BASE_DLG,
	NSTR_INFO_DLG,

	NCITYHALL_DLG,			// ���
	NCITYHALLCONSTRUCT_DLG,
	NRESIDENTLIST_DLG	, 
	NBERESIDENT_DLG	, 
	NAPPOINTMENTCHIEF_DLG,
	NSTRUCTUREMESSAGE_DLG,

	NBANK_DLG,				// ����
	NSTOCK_DLG,				// ����		170
	NMARKET_DLG,			// ���� 
	NHOUSE_DLG,				// ���� 	
	NPOSTOFFICE_DLG,		// ����	
	NHUNT_DLG,				// ������
	NPORT_DLG,				// ����
	NHORSEMARKET_DLG,		// �纹��
	NREALESTATEMARKET_DLG,	// �Ű�
	NSUMMONMARKET_DLG,		// �忹��
	NSUMMONHEROMARKET_DLG,	// �񺯻�
	NFEAST_DLG,				// ���ڽ�	180
	NLAND_DLG,				// ����	
	NMINE_DLG,				// ����
	NGUILDSTR_DLG,			// �����
	NGUILD_DLG,				// ���

	// ����
	NHOUSENAMECHANGE_DLG,		// â�� �̸� ����
	NHOUSEEXTENSION_DLG,		// �Ⱓ ����
	NHOUSEUSERINFOBASE_DLG,		// ���� ����Ʋ
	NHOUSEUSERITEM_DLG,			// â��
	NHOUSEUSERHORSE_DLG,		// ������
	NHOUSEUSERSECONDHAND_DLG,	// ��
	NHOUSEUSERMANAGEMENT_DLG,	// ����
	NHOUSEUSERNEWMANAGEMENT_DLG, // ���ο� ����
	NVILLAGETREE_DLG,				// 190
	NGAMEMASTERORDER_DLG,		// GM���
	NCOMMONMSG_DLG,				// ����޼��� ���̾�α�
	NCHARMENUBAR_DLG,
	NSYSMENUBAR_DLG,
	NCHATBAR_DLG,
	NSYSCHILDMENU_DLG,
	NNEWINVENTORY_DLG,
	NNEWEQUIPWINDOW_DLG,
	NQUESTINFO_DLG,

	// ������ȸ ����
	NGENERALMEETINGLETTER_DLG,		// 200
	NGENERALMEETING2_DLG,

	// ����(���Ǳ���)
	NBLACKARMYMVP_DLG,

	// ������ ���� �������̽�
	NNEWITEMMAKE_DLG, 
	NNEWMAKECHILD_DLG,
	NNEWENCHANTCHILD_DLG,
	NNEWENCHANTOTHER_DLG,

	// ���Ӱ� �� ������ ��
	NNEWITEMMALL_DLG,	
	NBUYWINDOW_DLG,
	NPRESENTWINDOW_DLG,
	NBUYITEMINFOWINDOW_DLG,	// ���� ��� �� ���� ����â		210
	NPRESENTINFOWINDOW_DLG,	// ���� �ϰ� �� ���� ����â

	NACCOUNTBOOKBASE_DLG,	// ���� ȸ�����
	NACCOUNTBOOKPART1_DLG,	// �ں��ݺκ�
	NACCOUNTBOOKPART2_DLG,	// ���ͱݺκ�
	NACCOUNTBOOKPART3_DLG,	// ��ü
	NNEWENCHANTOTHERACCEPT_DLG,
	NNEWENCHANTOTHERACCEPT_MSGBOX_DLG,

	NGOONZUPOLICY_DLG,		// ���� ��åâ

	NRIGHTMOUSEUSERLIST_DLG, // ���콺 ������ Ű�� �������� �÷��̾ ���������� ���� ����� �����ش�.

	NGETPRESENT_DLG,	// �����۸� ������ ������ �����ִ� â	220
	NTHANKSPRESENT_DLG, // �������༭ ���ٴ� �޽����� ������ �����ִ� â

	NITEMMALL_GIVESTATUS_DLG,

	NSHOWGETITEM_DLG,		// ������ ȹ��â
	NTHANKSPRESENT_ANSWER_DLG,  // ������ �༭ ���ٴ� ������ �޽��� �����ִ� â

	NAQTRADEWINDOW_DLG,		// Aq Ʈ���̵� ���̾�α�
	NSETWORLDMONEYBUT_DLG,

	NINFO_DLG,	//

	// ���� ���̾�α�
	NTRADESERVERSELL_DLG,
	NTRADESERVERBUY_DLG,
	NTRADESERVERBASE_DLG,		// 230

	// ��������â ���� 
	NINFO_SUB_DLG,

	// ��õ����Ʈ ����, �Ҹ� npc ���̾�α�
	NRPMERCHANT_DLG,
	NRPLIST_DLG,

	NSETCOUNTRY_DLG,
	NUSERLISTBYCOUNTRY_DLG,

	NMANUFACTURE_DLG,

	NRPBASE_DLG,

	// �� �κ��丮
	NNEWINVENTORY_HORSE_DLG,

	// ���� �κ��丮
	NNEWINVENTORY_BAG0_DLG,
	NNEWINVENTORY_BAG1_DLG,		// 240

	NDOWNLOADADDON_DLG,
	NITEMMALLPRODUCT_DLG,

	NSELECTITEMCOUNT_DLG,

	NOPENINGBANNER_DLG,

	// �����Ǽ� 
	NIZOWORLDTRADETAX_DLG,
	NIZOMARKETPRICE_DLG,

	// �ʺ��� ����Ʈ
	NLOWLEVEL_DLG,

	NMARKET_SUB_DLG,

	// ��������û
	NGOONZUSIEGE_DLG,

	NMYGUILDBASE_DLG,		// 250
	NMYGUILD_DLG,
	NMYGUILDMASTER_DLG,

	NMYGUILDMASTERMANAGE_DLG,
	NMYGUILDMASTERSTATUS_DLG,
	NMYGUILDMASTERHUNTMAP_DLG,
	NMYGUILDMASTERGVG_DLG,
	NMYGUILDMASTERMARK_DLG,

	NBEGUILDMEMBER_DLG,

	NGUILDINFO_DLG,
	NTREASUREBOX_DLG,		// 260

	NGUILDDUNGEON_DLG,
	NGUILDDUNGEONAPPLY_DLG,

	NGUILDMEMBER_DLG,
	NGUILDSENDMSG_DLG,

	NEMOTICON_DLG,
	NFRIENDMEMO_DLG,

	NNEWFRIEND_DLG,
	NFRIENDCHANGEGROUPNAME_DLG,

	NMANUFACTURENPC_DLG,
	NBEGINNERWEAPONNPC_DLG,	// 270

	NGUILDWARAPPLY_DLG,
	NGUILDWARRECOMMAND_DLG,

	NMAKEITEMDEMO_DLG,
	NAUTOANSWER_DLG,
	NGACHA_DLG,

	NMOFUMOFULIST_DLG,

	NPREMIUMSTATUS_DLG,

	NBUYSECONDWINDOW_DLG,

	NBUFFSTATUS_DLG,//�����߰�.[2007.07.12 ����]

	NNAMINGQUESTLIST_DLG,	//tys	280
	NHELPBUTTON_DLG,		//tys
	NSELECTNAMING_DLG,		//tys
	NHAPPYBEAN_DLG,//���Ǻ� �̺�Ʈ [2007.08.22 �ռ���]

	NSYSTEMREWARDLIST_DLG,	//tys - systemreward
	NATTENDCHECK_DLG,		//tys - attend
	NQUESTSELECTITEM_DLG,	//tys - questitemselect
	NNEWNOTIFY_DLG,			//tys

	NMUSIC_DLG,

	NINVITEEMPIRE_DLG,	// kkm 

	NAUCTIONEVENT_DLG,		// 290

	NEXCHANGESTOCK_DLG,

	NCHRISTMASEVENT_DLG,//ũ���������̺�Ʈ

	NCHRISMASQUEST_DLG,			//[�߰� : Ȳ���� 2007. 11. 20 ũ�������� ����Ʈâ �߰�.]

	NNEWYEAR_DLG,				//[�߰� : Ȳ���� 2007. 12. 11 �ų� �̺�Ʈ ��ư�� ��ȭ���ڷ�...]

	CHARTRANSFORMINFO_DLG,				//[�߰� : Ȳ���� 2007. 12. 20 ���� ����â �߰�.]
	CHARTRANSFORMINFO_STORY_DLG,		//[�߰� : Ȳ���� 2007. 12. 20 ���� ���� ���丮â �߰�.]
	CHARTRANSFORMINFO_STORY_READ_DLG,	//[�߰� : Ȳ���� 2007. 12. 20 ���� ���� ���丮 �б�â �߰�.]
	NINSTANTDUNGEONBOARD_DLG,			//�ν���Ʈ ���� - ����,�������� 2008.01.07 �ռ���

	NINSTANST_DUNGEON_STATUS_DLG,		// [�߰� : Ȳ���� 2008. 1. 8  => �ν���Ʈ ���� ���º���.]
	NINSTANST_DUNGEON_RUN_INFO_DLG,		// [�߰� : Ȳ���� 2008. 1. 9  => �ν���Ʈ ���� ���� ���º���.]	300
	NINSTANST_DUNGEON_NOTIPY,			// [�߰� : Ȳ���� 2008. 1. 18 => �ν���Ʈ ���� ���� �˸� â.]

	NBLACK_WAR_RUN_DLG,					// [�߰� : Ȳ���� 2008. 1. 24 => ���� ���� ���� ���� ���� â.]
	NBLACK_WAR_REWARD_DLG,				// [�߰� : Ȳ���� 2008. 1. 25 => ���� ���� ���� ���� ���� â.]

	NSPACE_BOX,							// [�߰� : Ȳ���� 2008. 1. 29 => ���� ���� â.]

	ARTIFACT_BASE_DLG,					// [�߰� : Ȳ���� 2008. 2. 26 => ��Ƽ��Ʈ �⺻ â. �� ��ưâ.]
	ARTIFACT_MIXTURE_DLG,				// [�߰� : Ȳ���� 2008. 2. 26 => ��Ƽ��Ʈ ���� â.]
	ARTIFACT_SLOT_CREATE_DLG,			// [�߰� : Ȳ���� 2008. 2. 26 => ��Ƽ��Ʈ ���Ի��� â.]
	ARTIFACT_REMOVE_DLG,				// [�߰� : Ȳ���� 2008. 2. 26 => ��Ƽ��Ʈ ����ü ���� â.]
	ARTIFACT_RESTORE_DLG,				// [�߰� : Ȳ���� 2008. 2. 26 => ��Ƽ��Ʈ ������ ȯ�� â.]

	PARTYHALL_IN_BASE_DLG,				// 310
	PARTYHALL_IN_COSTUME_USER_DLG,
	PARTYHALL_IN_FIRECRAKER_CHIEF_DLG,
	PARTYHALL_IN_INVITE_CHIEF_DLG,

	NDAILYQUEST2_DLG,					// ���ϸ� ����Ʈ 2 �ռ���
	ATTENDNOTICE_DLG,					// [����] �⼮üũ : ���� �⼮üũâ
	ELECTIONSTUMP_DLG,					// [����] ���Žý��� : ���� �ý���
	HIDDENQUEST2_DLG,					// ���� ����Ʈ2 ��� ���̾�α� 
	PREMIUMSTATUS_DLG,

	// ���� UI : Pannel
	PANNEL_DATEMONEY_DLG,				// [����] �ð��� �� ǥ�� ���̾�α�
	PANNEL_CHARSTATUS_DLG,				// [����] ĳ���� ����ǥ��		320
	PANNEL_SUMMON_DLG,					// [����] ��ȯ�� ����
	PANNEL_ORGAN_DLG,					// [����] ������ ����
	PANNEL_SOULGUARD_DLG,				// [����] ��ȣ���� ����

	STATUSBAR_POPUPPARENT_DLG,
	STATUSBAR_POPUPCHILDCOMMUNITY_DLG,
	STATUSBAR_POPUPCHILDSYSTEM_DLG,

	NDAILYQUEST3_DLG,					// ���ϸ� ����Ʈ 3 �ռ���
	CHARSTATUS_ABILITY_DETAIL_DLG,		// [����] ĳ���� ����â���� �� �ɷ�ġ ������ ������ â. 2008-3-24

	NVOTESTATUS_DLG,					// [����] ���� ��ǥ��Ȳ

	NOPENBIGITEMBOX_DLG,

	NMONSTER_ATTACK_EVENT,				// [����] ���� �̺�Ʈ - ���� ����. => 2008-3-26	330

	NGMINFO_DLG,						// [����] GM���� �ʿ��� ���� ǥ��â

	NCHARSUMMONRESET_DLG,				// [����] ��ȯ�� ��ȭ ���� �� �ʱ�ȭ â

	NCHANGE_DLG,						// [ ���� ] ���� �� ���� ���� ���� ���� NPC ���̾�α� 
	NSETCHAT_DLG,						// [ ���� ] ä��â�� �ö�� �޼������� �з��Ҷ� �� â

	NBUFF_ROULETTE_DLG,					// [����] ������ ����. => 2008-6-9

	NMAPNAME_DLG,						// [����] �� �̸� �����ֱ� (2008.06.17)

	// ���� �̺�Ʈ.
	SERVER_EVENT_RANK_DLG,				// [����] ���� �̺�Ʈ ��ü(����, ����)��ŷ ������ �Խ���.
	SERVER_EVENT_QUEST_DLG,				// [����] ���� �̺�Ʈ ����Ʈ ����
	SERVER_EVENT_INSTANCE_MAP_BONUS,	// [����] ���� �̺�Ʈ �δ� ���� �� ���� ������ ���ʽ� â. => 2008-6-25
	SERVER_EVENT_INDUNINFO,				// [����] ���� �̺�Ʈ ���ʽ� �δ����� ��Ȳ		340

	NTREASUREBOXEXTRA_DLG,				// [����] 2�� ���� �ָӴ�

	NDESTROYITEM_DLG,					// [����] ������ ��ӽ� ������ �̸��� ���� ���̾�α�

	NMUDANG_EQUIPITEM_DLG	,			// [����] ��ȯ�� ��� ������ 

	NMARKETCONDITIONS_DLG	,			// [��] �ü�Ȯ�� 2008-07-18

	NPOSTOFFICE_GROUP_LIST_DLG,			// [����] ��ü �޽��� ������. ���� ����Ʈ ����â. => 2008-8-4

	NQUESTINFODLG_PARENT,				// [����] ����� ����Ʈ �˸�â �θ�â
	NQUESTINFODLG_GOINGQUEST,			// [����] ����� ����Ʈ �˸�â ���� ���� ����Ʈ â
	NQUESTINFODLG_ALLQUEST,				// [����] ����� ����Ʈ �˸�â ��ü ����Ʈ â

	NQUESTNOTICE_DLG,					// [����] ���� ���� ����Ʈ ǥ��â

	NMYSUMMON_DLG,						// [����] ��ȯ�� ���� �ý���		350

	NGACHANEW_DLG,						// [����] ���� â ����.				   			=> 2008-8-29
	NCHOISE_ITEM_GAME_START_DLG,		// [����] ���� â ������ ���� �� ���� ����.		=> 2008-8-29
	NOPENBOX,							// [����] ���� ���� ���� �ִϸ��̼� â .		=> 2008-8-29
	RECIEVED_ITEM_DLG,					// [����] ���� ���� ������ �޴� â .			=> 2008-8-29

	NMYKEY,								// [����] ������ �޴� ūâ.						=> 2008-9-3
	NMYKEYMINI,							// [����] ������ �޴� ����â.					=> 2008-9-3

	NACUTRADEDLG_PARENT,				// [����] ��ť �ŷ�â ������ �θ�â
	NACUTRADEDLG_SELL,					// [����] ��ť �ŷ�â ������ �ȱ�â
	NACUTRADEDLG_BUY,					// [����] ��ť �ŷ�â ������ ���â
	NACUTRADEDLG_WITHDRAW,				// [����] ��ť �ŷ�â ������ ȸ��â		360
	NACUTRADEDLG_PASSPORT,				// [����] ��ť �ŷ�â ������ ����â

	NAMBER_BOX_DLG,						// [����] ȣ�ڻ��� => 2008-9-12

	NCHARBUFF_ROULETTE_DLG,				// [����] ĳ���� ���� ȹ��â => 2008-09-11

	POSTBOX_BASE_DLG,					// [��] ��ü�� - 0919
	POSTBOX_INTRO_DLG,
	POSTBOX_PANPAL_DLG,
	POSTBOX_SENDMSG_DLG,
	POSTBOX_RECEIVEMSG_DLG,

	NYESORNODLG,						// [����] ��, �ƴϿ� â.							=> 2008-10-08
	NHELPER_DLG,						// [����] ����� â.								=> 2008-10-10
	NHELPER_CHAT_DLG,					// [����] ����� ��ȭ â.						=> 2008-10-10
	NHELPER_QUESTION_OR_ANSWER_DLG,		// [����] ���� â�̱⵵ �ϰ� �亯â�̱⵵ ���~	=> 2008-11-04
	NHELPER_QUESTION_LIST_DLG,			// [����] ���� ����Ʈ�� �� ��~					=> 2008-11-04
	NHELPER_ANSWER_COMPLETE_DLG,		// [����] �亯 ���� â~							=> 2008-11-04

	NMAGICCOOLTIME_DLG,					// [����] ���� ��Ÿ�� ǥ��â					=> 2008-10-15
	PVPLEAGUE_DLG,						// [����] PVP ���Ѵ��� UI						=> 2008-11-04

	NGACHA2_DLG,						// [��] //KHY - 1104 -  ����2 -���� ���� ����. 

	NEWYEAR_ROULETTE_DLG,				// [���] �ų��귿â

	NELIXIR_STATUS_DLG,					// [����] ������ �������ͽ� â.
	NELIXIR_USE_DLG,					// [����] ������ ��� â.
	NELIXIR_NPC_DLG,					// [����] ������ NPC â.

	NVALANTINE_DLG,						// [����] �߷�Ÿ�ε��� ���� ���̾�α�.

	NEWSELECTBOX_DLG,					// [����] ���ο� ���û���(�ų����)				=> 2008-12-17

	NNEWMARKET_DLG,						// [����] ���ո���
	NNEWMARKET_SUB_DLG,					// [����] ���ո���.

	NSUMMON_INVENTORY_DLG,				// [����] ��í : �κ��丮 ��ȯ��

	NGUILDDUNGEON_NEW_DLG,				// [����] ��� ����� ������ĺ���-����� ��Ȳ ���̾�α�
	NREQUESTHUNTMAPWARREQUEST,			// [����] ��� ����� ������ĺ���-����� ��û ���̾�α�

	NPERIODITEMLIST_DLG,				//	�Ⱓ�������� ���̾�α�^

	NCARRYOVERGACHA_DLG,				// [����] �̿� ��í ���̾�α�					=> 2009-04-07
	NGACHAPRODUCT_DLG,					// [����] �̿� ��í(������ ���̾�α�)			=> 2009-04-08
	NGACHARESULT_DLG,					// [����] �̿� ��í(���â)						=> 2009-04-09

	NGUILDWARRESULT_DLG,				// [��ȣ] �����ȹ�� ����� ���â ���̾�α�
	NGUILDWARKILLSIGN_DLG,				// [��ȣ] ����� ȹ�� ����� ������ ų�� ��Ȳ ���̾�α�

	NPROMOTER_INFO,						// [����] ���θ��� ĳ���� ������ ȹ�� ������ ����.
	NPROMOTER_URL,						// [����] ���θ��� URL.
	NPROMOTER_GIVE_ITEM_NOTICE,			// [����] ���θ��� ���� ���� �˸�â.
	NPROMOTER_MINI,						// [����] ���θ��� ��õ�� �� ĳ���Ͱ� �������� �Ҷ� 1�е��� ��µǴ� ��ư â.
	NPROMOTER_INTRODUCE,				// [����] ���θ��� ������ �λ�â.

	NWEDDINGCEREMONY_MENU_DLG,			// [����] ��ȥ�ý��� : ���� �޴� ���̾�α�		=> 2009-04-21
	NPROPOSE_QUESTION_DLG,				// [����] ��ȥ�ý��� : �������� ����			=> 2009-04-23
	NPROPOSE_ANSWER_DLG,				// [����] ��ȥ�ý��� : �������� �亯			=> 2009-04-28

	NMARRIAGELOVELEVEL_DLG,				// [����] ��ȥ�ý��� : ������ ǥ�� ���̾�α�	=> 2009-05-11
	NWEDDINGANNIVERSARY_DLG,			// [����] ��ȥ�ý��� : ��ȥ ����� ���̾�α�	=> 2009-05-12

	NWEDDINGCEREMONY_LIST_DLG,			// [����] ��ȥ�ý��� : ���� ����Ʈ ���̾�α�	=> 2009-05-18
	NFAMILYINFO_DLG,					// [����] ���� ����â							=> 2009-05-20

	NMYFAMILYINFO_DLG_WITH_CHILDREN,	// [����] ���� ����â							=> 2009-05-25
	NBUTTONMENU_DLG,					// [����] ���� ��ư Ŭ�� �˾� ���̾�α�		=> 2009-05-27
	NBALANCECURRENCY_DLG,				// [��ȣ] ��ȭ�� ���� �귿 ���� â
	NFAMILY_DLG_ADD_CHILDREN,			// [����] �ڳ� �߰� â							=> 2009-05-29
	NFAMILYCOOKIELEVEL_DLG,				// [����] �����ý��� : ��Ű���ǥ�� ���̾�α�  => 2009-06-05

	CLTNSOULGUARDHOUSESTATUS_DLG,		// [����] ��ȣ���� ������ ���� ����â			=> 2009-06-16
	NCHARSOULGUARDINFO_DLG,				// [����] ��ȣ���� ��ȭ ����â					=> 2009-06-17

	NPCROOM_DISPLAY_DLG,				// [����] PC�� ���� ǥ��â						=> 2009-07-01
	NPCROOM_DLG,						// [����] PC�� ���� ������â					=> 2009-07-01
	NRACOONDODGE_EVENT_DLG,				// [����] ���� ���ϱ� �̺�Ʈ ���� ���̾�α�	==> 2009-07-23
	NRACOONDODGE_EVENT_RESERVELIST_DLG,	// [����] ���� ���ϱ� �̺�Ʈ ���ฮ��Ʈ			==> 2009-08-6
	NBOKBULBOK_EVENT_DLG,				// [����] ���Һ� �̺�Ʈ							=> 2009-08-06
	NBOKBULBOK_RESERVELIST_DLG,			// [����] ���Һ� �̺�Ʈ����ڸ���Ʈ ����â
	NNEWNPCREPAIR_DLG,					// [����] NPC ������ ����â						=> 2009-08-07
	NGAWIBAWIBO_DLG,					// [��ȣ] ����������

	NDORMANCYARMOURBOX_DLG,				// [����] �޸� ���� �ý��� : �� ���� ����   => 2009-08-01 
	NDORMANCYWEAPONBOX_DLG,				// [����] �޸� ���� �ý��� : ���ⱸ ���� ����   => 2009-08-01 	
	NDORMANCYPOINT_DLG,					// [����] �޸� ���� �ý��� : ����Ʈ ����		=> 2009-08-17 	

	NITEMREPAIR_DLG,					// [����] ������ ���� & ������û â
	NAVATARQUEST_DLG,					// [��ȣ] �ƹ�Ÿ����Ʈ

	NWARNDURABILITY_DLG,				// [����] ������ ��� ǥ��â					=> 2009-09-03
	NHALLOWEENSPIRITBOX_DLG,			// [��ȣ] �ҷ��� ���Ǹ� dlg

	NMAINMAP_DLG,						// [����] �߿����� ��ü�� â					=> 2009-09-28

	NMONSTERCREATE_DLG,					// [���] ���� ���� â						=> 2009-09-30
	NEQUIPMENTCREATE_DLG,				// [���] ��� ���� â							=> 2009-09-30
	NCHANGECHARNAME_DLG,				// [��ȣ] ĳ���� �̸� ���� dlg					=> 2009-10-07	

	NCHARHOUSE_DLG,						// [����] ĳ���� ������							=> 2009-10-07

	NCOPFIELD_DLG,						// [����] ��ų�� npc
	NRACCOONEVENT_CHANGE_GOONZUEVENT_DLG,//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����			=> 2009-10-13

	NBATTLEROYALRESULT1_DLG,			// [����]��Ʋ�ξ� ��� ��� 
	NBATTLEROYALRESULT2_DLG,			// [����]��Ʋ�ξ� ��� ��� (����)
	NBATTLEROYALTIME_DLG,				// [����]��Ʋ�ξ� ��Ⱑ ���� �ð� 

	N2010NEWYEAR_FORTUNE_DLG,			// [����] 2010�ų��̺�Ʈ - ������Ű �â.

	// ��Ƽ��Ī
	NSELECT_QUEST_BASE_DLG,				// [����] �ʺ��� ��Ƽ ����Ʈ �ý��� - ������ ����Ʈ��Ƽ ���� â.
	NPARTY_MATCHING_BASE_DLG,			// [����] �ʺ��� ��Ƽ ����Ʈ �ý��� - ��ȸ�� ��Ƽ����Ʈ���� �� ��Ƽ �����ϴ� â.
	NCREATE_PARTY_BASE_DLG,				// [����] �ʺ��� ��Ƽ ����Ʈ �ý��� - ��Ƽ�����ϴ� â.
	NPARTY_JOIN_DLG,					// [����] ��Ƽ ���� ��û ��ȭ����

	NGIANTRACCOONRESURRECTEVENTDLG,		// [����] ���̾�Ʈ ���� ��Ȱ ���â. 
	NPOTRACCOONDLG,						// [����] ���̾�Ʈ ���� ��Ȱ ��Ȱ �� ���â. 

	// pvp �� npc �̵�
	NPVPMAPGODLG,						// [����] PVP �� �̵� npc

	NMANUFACTURE_NEW_DLG,				// [����] �����Ƿ� �������̽� ����
	MANUFACTURESEARCH_DLG,				// [����] �����Ƿ� �������̽� ����->ã��

	NBATTLEROYALMOVE_DLG,				// [����] ��Ʋ�ξ� ��������� �̵������ִ� ��ư ���̾�α�

	VALENTINEDAY_NPC_DLG,					// [����] �߷�Ÿ�ε��� NPC
	VALENTINEDAY_PACKING_DLG,				// [����] �߷�Ÿ�ε��� �����ϱ�.
	VALENTINEDAY_TRADE_DLG,					// [����] �߷�Ÿ�ε��� �����ϱ�.
	VALENTINEDAY_CONFESSION_QUESTION_DLG,	// [����] �߷�Ÿ�ε��� ���	�ϱ�.
	VALENTINEDAY_CONFESSION_ANSWER_DLG,		// [����] �߷�Ÿ�ε��� ��鿡 �����ֱ�.

	DIALOG_END
};
//DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER

// ���̾�α� �߰��� �߰��Ͻø� �ȵ˴ϴ�. DIALOG_END �ٷ� ���� �߰��� �ּ���. >_< - ����

// ���̾�α� ��ġ�� ������� ���Ͽ� ����ǰ� �ֽ��ϴ�

//DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER


#endif

