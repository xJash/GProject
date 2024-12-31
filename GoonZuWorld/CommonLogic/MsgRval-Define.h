#ifndef _MSGRVALDEFINE_H
#define _MSGRVALDEFINE_H


//----------------------------------------------
// �����Ͽ� ������ ������ ���ϰ�. 
//----------------------------------------------
#define SRVAL_ALREADYMAYOR				5		// �̹� ������� ������. 
#define SRVAL_INVALIDCANDIDATE			9		// �ĺ��� ��ܿ� �ش� ĳ���Ͱ� ���� 
#define SRVAL_NOCANDIDATE				10		// �ĺ��ڰ� �Ѹ� ����. 
#define SRVAL_NOMAYOR					11		// ������� �ƴϴ�. 		
#define SRVAL_NOBANKCHIEF				12		// ��������� �ƴϴ�.
#define SRVAL_SUCCESSRESIGNMAYOR		13		// ��������� �����ϴµ� �����ߵ�. 
#define SRVAL_SUCCESSSETFEE				14		// ������ ������ ����. 
#define SRVAL_NOSELLPRODUCT				15		// ���ڷ� ���� ������ �����δ� �������� �ʴ´�. 
#define SRVAL_NOSELLBANKACCOUNT			16		// ������ ���� ���°� ����. 
#define SRVAL_NOTENOUGHBANKMONEY		17		// ���忡 ����� ���� ����. 		
#define SRVAL_NOBUYBANKACCOUNT			18		// ����� �ϴ� ����� ������°� ����.		
#define SRVAL_CANNOTINPUTTOBUYER		19		// ���ڿ��� ������ �� �� ����. 		
#define SRVAL_SUCCESSTOBUYMARKET		20		// ���ֿ��� ���������� ������ �����ߴ�. 
#define SRVAL_SUCCESSTOSELLMARKET		21		// ���ֿ��� ���������� ������ �����Ҵ�. 
#define SRVAL_NOMARKETACCOUNT			22		// ���ֿ� ���°� ����. 
#define SRVAL_NOMATCHINGITEMININV		23		// �κ��丮�� ��ġ�ϴ� �������� ����. 
#define SRVAL_NOTMATCHMARKETACCOUNT		24		// ������� ���� ���°� �߸� �����Ǿ� �ִ�.
#define SRVAL_NOMATCHINGITEMINSTG		25		// ���� â��  ��ġ�ϴ� �������� ����. 
#define SRVAL_CANNOTINPUTTOINV			26		// �κ��丮�� ���� �� ����. 
#define SRVAL_SUCCESSTOGETFROMSTG		27		// ����â���� ���������� ȸ���ߴ�.
#define SRVAL_NOEMPTYHOUSE				28		// �� ������ ��� �Ӵ��� �� ����.
#define SRVAL_INVALIDHOUSEAPPLYER		30		// ���� ����ڰ� ��ȿ���� �ʴ�. 
#define SRVAL_INVALIDBANKACCOUNT		31		// �����ο��� ���� ���°� ����. 

//------------------------------------------
// ���� �޽��� 
//------------------------------------------
// ���. 
#define SRVAL_SETSKILL					40		// ����� �����Ǿ���. 
#define SRVAL_SKILLNOTREADYFORMAKE		41		// ��ǰ ���꿡 �ʿ��� ��ų �̺�. 	
#define SRVAL_INSUFFICIENTMATERIAL		42		// ���� �������� ���� �Ұ�. 
#define SRVAL_INSUFFICIENTTOOL			43		// ���� �������� ���� �Ұ�. 
#define SRVAL_MATMATCHNUM				44		// ���� �䱸���� ���ɼ����� ���� ����. 
#define SRVAL_FAILPROBILITY				45		// ���� Ȯ������ ����. 
#define SRVAL_NOEMPTYAREA				46		// ���ڸ��� ��� ����. 
#define SRVAL_BLOCK_BLOCKED				47		// ����� �α����� ���ѵǾ���. 
#define SRVAL_BLOCK_UNBLOCKED			48		// ����� �α����� ���Ǿ���. 
#define SRVAL_BLOCKUSER_BLOCKED			49		// Ư�� ����� �α����� ���ѵǾ���. 
#define SRVAL_BLOCKUSER_UNBLOCKED		50		// Ư�� ����� �α����� ���Ǿ���. 
#define SRVAL_SUCCESSASK				51		// ���� ��� ����. 
#define SRVAL_INPUTBIDMONEY				52		// ���� �Ա� ���� (���� ��û �ϸ鼭 ���� ���� �����ϴµ� ����) 	
#define SRVAL_ENCHANTFAILTOOMUCH		53		// ���̻� ���� ���� ����. 
#define SRVAL_NOFATHERNAME				54		// ���´��� �������� �ʴ´�.
#define SRVAL_SAMEACCOUNT				55		// ���� ������ ������ �� �� ����. 
#define SRVAL_ENCHANTFAILNOTATBMATCH	56		// �����ҷ��� ITEM�� ATB�Ӽ��� ��ġ���� �ʴ´�.
#define SRVAL_ENCHANTFAILTOOMUCHKIND	57		// ������ ���� 2�����̻� ���ϼ� ����.	
#define SRVAL_DECSKILL_FAIL_HAVECHILD	58		// ���� ����� �־� ���� ����� �ʱ�ȭ �� �� ����. 
#define SRVAL_WEAPONSKILL_FAIL_MONEY	59		// ���� ���ڶ� �� �ø���.
#define SRVAL_REJECT_SETFATHER			60		// ������ ���½�û ������ �ź��ߴ�
#define SRVAL_ACCEPT_SETFATHER			61		// ������ ���½�û ������ �³��ߴ�.
#define SRVAL_PENALTY_SETFATHER_TEACHER		62		// ���� �г�Ƽ������ ���ڸ� �� �޾Ƽ� ���� ��û�� ������� �޼���
#define SRVAL_PENALTY_SETFATHER_PUPIL		63		// ���� �г�Ƽ������ ���ڰ� ���� �� �ؼ� ���ڿ��� �޼���

//���� ���� 
#define SRVAL_BANK_SUCCESSINPUTMONEY						70		// �Ա� ����. 
#define SRVAL_BANK_FAILINPUTMONEY_OUTOFMONEY				71		// �Ա� ���� - ������ ����.  
#define SRVAL_BANK_FAILINPUTMONEY_NOACCOUNT					72		// �Ա� ���� - ���� ����. 
#define SRVAL_BANK_FAILINPUTMONEY_NOTENOUGHFEE				73		// �Ա� ���� - ������ ����
#define SRVAL_BANK_SUCCESSOUTPUTMONEY						75		// ��� ����
#define SRVAL_BANK_SUCCESSCLOSEACCOUNT						76		// ���� ���� ����. 
#define SRVAL_BANK_FAILCLOSEACCOUNT							77		// ���� ���� ����
#define SRBAL_BANK_FAILCLOSEACCOUNT_OTHERVILLAGE			78		// ���� ���� ���� ( �ٸ� ���� ������ )
#define SRBAL_BANK_FAILCLOSEACCOUNT_CHECKMARKET				79		// ���� ���� ���� ( ���Ͽ� ��ǰ������ )

#define SRVAL_BANK_SUCCESSOUTPUTMONEY_DELACCOUNT			80		// ��� ���� - ���»���. 
#define SRVAL_BANK_FAILOUTPUTMONEY_NOACCOUNT				85		// ��� ���� - ���°� ���� ���� ����. 
#define SRVAL_BANK_FAILOUTPUTMONEY_NOTENOUGHFEE				86		// ��� ���� - ������ ����. 
#define SRVAL_BANK_FAILOUTPUTMONEY_NOTENOUGHMONEYINACCOUNT	90		// ��� ���� - �ܾ��� ����
#define SRVAL_BANK_FAILSETFEE_NOTCHIEF						95		// ������ ���� ���� - ��������ƴ� 
#define SRVAL_BANK_SUCCESSSETFEE							96		// ������ ���� ���� 
#define SRVAL_BANK_SUCCESSCREATEACCOUNT						97		// ���� ���� ����.
#define SRVAL_BANK_FAILCREATEACCOUNT						98		// ���� ���� ����. 
#define SRVAL_BANK_FAILCREATEACCOUNT_ALREADY				99		// ���� ���� ���� - �̹� ���°� �ִ�. 



// ���� ���� 
#define SRVAL_STOCK_BUY_SUCCESSTRADE				110		// ���� ����. 
#define SRVAL_STOCK_SELL_SUCCESSTRADE				115		// �Ű�  ����. 
#define SRVAL_STOCK_FAIL_NOTENOUGHFEE				116		// �ŷ� ���� - ������ ����
#define SRVAL_STOCK_BUY_FAILNOACCOUNT				120	// ������ ���� ���°� ����. 
#define SRVAL_STOCK_SELL_FAILNOACCOUNT				125	// ������ ���� ���°� ����. 
#define SRVAL_STOCK_DSTSELLERNOACCOUNT				126	// ���� ����� �ϴµ� ������ ���°� ����. 
#define SRVAL_STOCK_DSTBUYERNOACCOUNT				127	// ���� �ȷ��� �ϴµ� ������ ���°� ����. 
#define SRVAL_STOCK_BUY_FAILNOTENOUGHMONEY			130 // ������ ���� ���¿� �ܾ��� ������� �ʴ�. 
#define SRVAL_STOCK_SELL_FAILNOTENOUGHMONEY			135 // ������ ���� ���¿� �ܾ��� ������� �ʴ�. 
#define SRVAL_STOCK_BUY_FAILLIMITSTOCKKIND			140	// ���ѵ� ���� �̻��� �ֽ��� �� �� ����. 
#define SRVAL_STOCK_SELL_FAILLIMITSTOCKKIND			145	// ���ѵ� ���� �̻��� �ֽ��� �� �� ����. 
#define SRVAL_STOCK_BUY_HALFSUCCESS					150 // �ֹ��� �Ϻδ� ó���ǰ� �Ϻδ� ó������ �ʾҴ�. 
#define SRVAL_STOCK_SELL_HALFSUCCESS				155 // �ֹ��� �Ϻδ� ó���ǰ� �Ϻδ� ó������ �ʾҴ�. 
#define SRVAL_STOCK_BUY_FAILLIAR					170 // ��� �ֹ��� �㱸���� ���ֵ� �ŷ��� ü����� �ʾҴ�. 
#define SRVAL_STOCK_SELL_FAILLIAR					175 // ��� �ֹ��� �㱸���� ���ֵ� �ŷ��� ü����� �ʾҴ�. 
#define SRVAL_STOCK_BUY_SUCCESSORDER				180 // ���� �ֹ� ����. 
#define SRVAL_STOCK_SELL_SUCCESSORDER				185 // ���� �ֹ� ����. 
#define SRVAL_STOCK_FAILSETFEE						190	// ������ ���� ����. 
#define SRVAL_STOCK_SUCCESSSETFEE					191	// ������ ���� ����.
#define SRVAL_STOCK_SUCCESS_BIDDING					192 // �ֽ����� ����( �� ���� ����)
#define SRVAL_STOCK_FAIL_BIDDING					193	// �ֽ����� ����( �� ���� ����)
#define SRVAL_STOCK_SUCCESS_BUY_BIDSTOCK			194 // ���� �ֽ� ��� ����
#define SRVAL_STOCK_FAIL_BUY_BIDSTOCK				195 // ���� �ֽ� ��� ����
#define SRVAL_STOCK_FAIL_BUY_BIDSTOCK_NOTENOUGHMONEY 196 //	���� �ֽ� ��� ���� - ������ ����
#define SRVAL_STOCK_FAIL_BUY_BIDSTOCK_ALREADY		197 // ���� �ֽ� ��� ���� - ���ֶ� �̹� �ֽ��� �����ߴ�.
#define SRVAL_STOCK_FAIL_BUY_BIDSTOCK_EXCEEDAMOUNT		198 // ���� �ֽ� ��� ���� - ���� �ʰ�
#define SRVAL_STOCK_FAIL_BUY_BIDSTOCK_NOTBUYER		199 // ���� �ֽ� ��� ���� - ���ڴ�� ���Ա����� ����.

//#define SRVAL_STOCK_FAIL_BIDDING_NOBANKACCOUNT		194 // ���� ���� - ���� ���� ���� 
//#define SRVAL_STOCK_FAIL_BIDDING_NOTENOUGHMONEY		195 // ���� ���� - ���� ���� �ݾ� ���� 
//#define SRVAL_STOCK_FAIL_BIDDING_EXCEEDAMOUNT		196 // ���� ���� - ���� �ʰ�
//#define SRVAL_STOCK_FAIL_BIDDING_EXCEEDBIDDER		197 // ���� ���� - ������ �� �ʰ�
//#define SRVAL_STOCK_FAIL_BIDDING_WRONGVALUE			198 // ���� ���� - �̹� ��û�� �ݾ� ���� ���� 
//#define SRVAL_STOCK_FAIL_BIDDING_WRONGVALUE10		199 // ���� ���� - ���� �ְ� ������ �ݾ׺��� 10%�̻� ũ�� ����

// ��ܰ��� 
#define SRVAL_CITYHALL_SUCCESSCANDIDATE				200	// ���ĺ� ��� ����. 
#define SRVAL_CITYHALL_FAILCANDIDATE				205	// ���ĺ� ��� ����. 
#define SRVAL_CITYHALL_FAILCANDIDATE_LEVELERROR		206	// �ĺ� ��� ���� ������ �ȵǼ� ����
#define SRVAL_CITYHALL_FAILCANDIDATE_ALREADY		210	// �̹� ���� �ź����� ��ϵǾ� �־ ����. 
#define SRVAL_CITYHALL_FAILCANCELCANDIDATE			215	// �ĺ������� ����. 
#define SRVAL_CITYHALL_SUCCESSCANCELCANDIDATE		220	// �ĺ������� ����. 
#define SRVAL_CITYHALL_SUCCESSBERANK				225	// ���� ���� ����. 
#define SRVAL_CITYHALL_FAIL_BERANK_NOTHOME			226 // ���� ���� ���� - �ٸ� ������ �ֹ���
#define SRVAL_CITYHALL_FAILCANDIDATE_ALREADYRANK	230	// �̹� �ٸ� �ź��� ������. 
#define SRVAL_CITYHALL_FAILCANDIDATE_OVERFLOW		232	// ���ĺ� ��� ���� - ���̻� ���ĺ��� �� ����. (�����÷�) 
#define SRVAL_CITYHALL_DONATE_OVERMONEY				233	// ��θ� �Ҽ� ���� - ��αݺ��� �������� ����
#define SRVAL_CITYHALL_NOTBESTBEHOLDER				235	// �ִ����ְ� �ƴ�. 
#define SRVAL_CITYHALL_NOTMAYOR						237 // ������� �ƴ϶� ����� ������ ����� �� ����. 
#define SRVAL_CITYHALL_SUCCESSDELCANDIDATE			240 // �ĺ��ڸ� ���������� ������. 
#define SRVAL_CITYHALL_SUCCESSAPPLYRESIDENT			245 // ���������� �ֹ� ��� ��û�� �� 
#define SRVAL_CITYHALL_FAILALREADYAPPLY				246 // �ֹ� ��� ��û ���� - �̹� ��� �Ǿ�����
#define SRVAL_CITYHALL_FAILALREADYRESIDENT			247 // �ֹ� ��� ��û ���� - �̹� �ֹ��� 
#define SRVAL_CITYHALL_FAILEXCEEDAPPLYER			248 // �ֹ� ��� ��û ���� - ��û�� ���ڸ� �ʰ� �Ͽ���
#define SRVAL_CITYHALL_FAILTIMELIMIT				249 // �ֹ� ��� ��û ���� - ����Ż������ 5�ϰ��� �簡�� �Ұ�
#define SRVAL_CITYHALL_SUCCESSCANCELRESIDENT		250 // �ֹ� ��� ��� ���� 
#define SRVAL_CITYHALL_FAILCANCELRESIDENT			251 // �ֹ� ��� ��� ����
#define SRVAL_CITYHALL_FAIL_EXCEEDMAXRESIDENT		252 // �ֹ� ��� ��û/��� ���� - �ִ� �ֹμ� �ʰ� 
#define SRVAL_CITYHALL_FAIL_VILLAGEATWAR			253 // �ֹ� ��� ��û/��� ���� - ������ �ֹε�� �Ұ�
#define SRVAL_CITYHALL_SUCCESS_GETRESIDENTINFO		255 // �ֹ� ã�� ���� 
#define SRVAL_CITYHALL_FAIL_GETRESIDENTINFO			256 // �ֹ� ã�� ���� 
#define SRVAL_CITYHALL_FAIL_BERESIDENT_WRONGRANK	257 // �ֹ� ��� �㰡 ���� - �ٸ� ������ ������� �����
#define SRVAL_CITYHALL_FAIL_DECLAREWAR_NOMASTER		258	// ���� ���� ���� - �ֽ��� ���� �� Ǯ���� ������ ����.
#define SRVAL_CITYHALL_SUCCESS_SETBASEMONEY			259 // ���� �ǹ��� �ں��� ���� ����

#define SRVAL_CITYHALL_SUCCESS_DECLAREWAR			260 // ���� ���� ����
#define SRVAL_CITYHALL_FAIL_DECLAREWAR_ALREADYACT   261 // ���� ���� ���� - �̹� ���� ���� �� ������ ���� 
#define SRVAL_CITYHALL_FAIL_DECLAREWAR_ALREADY		262 // ���� ���� ���� - �̹� ���� ���� �Ǿ�����
#define SRVAL_CITYHALL_FAIL_DECLAREWAR_NOTPROPER	263 // ���� ���� ���� - ���� ������ ���� ���� �Ұ�
#define SRVAL_CITYHALL_FAIL_DECLAREWAR_GAP			264 // ���� ���� ���� - �ֹμ� ���̰� ����

#define SRVAL_CITYHALL_SUCCESS_CANCELDECLAREWAR		265 // ���� ���� ��� ���� 
#define SRVAL_CITYHALL_FAIL_CANCELDECLAREWAR		266 // ���� ���� ��� ����

#define SRVAL_CITYHALL_FAIL_DECLAREWAR_NOTMAYOR		267 // ���� ���� ���� - ��� ������ ������ ����.

#define SRVAL_CITYHALL_FAIL_DECLAREWAR_WARTIME		268 // ���� ���� �� ���� ���� ��� ���� - ���� �ð�
#define SRVAL_CITYHALL_FAIL_DECLAREWAR_DATE			269 // ���� ���� �� ���� ���� ��� ���� - 1�� �̳� �Ұ� 
#define SRVAL_CITYHALL_FAIL_DECLAREWAR_LOWERRANK	270 // ���� ���� ���� - ��� ���������� 5�ʰ� ����.
#define SRVAL_CITYHALL_FAIL_DECLAREWAR_AFTERLOSE	271 // ���� ���� ���� - �й� �� ��ȣ �Ⱓ�̴�.
#define SRVAL_CITYHALL_FAIL_DECLAREWAR_TARGET_AFTERLOSE	272 // ���� ���� ���� - ��� ������ �й� �� ��ȣ �Ⱓ�̴�.
#define SRVAL_CITYHALL_FAIL_DECLAREWAR_NOTNATION	273 // ���� ���� ���� - ��� ������ �й� �� ��ȣ �Ⱓ�̴�.
#define SRVAL_CITYHALL_FAIL_DECLAREWAR_MADEPROTECT_TARGET	274 // ���� ���� ���� - ��� ������ ���� �Ǽ� �� ��ȣ �Ⱓ�̴�.
#define SRVAL_CITYHALL_FAIL_DECLAREWAR_MADEPROTECT_SELF	275 // ���� ���� ���� - �ڽ� ������ ���� �Ǽ� �� ��ȣ �Ⱓ�̴�.
#define SRVAL_CITYHALL_FAIL_DECLAREWAR_FORCESTOP	276 // ���� ���� ���� - ������ ����� ������ ������ �ִ�.

#define SRVAL_CITYHALL_FAIL_SYMBOLSTATUS_MAXLEVEL	277 // ��Ȳ�� ���� ���� ���� - ��Ȳ�� ���� ����� ���������� ���� �Ұ�
#define SRVAL_CITYHALL_FAIL_CASTLESTATUS_MAXLEVEL	278 // ĳ�� ���� ���� ���� - ��Ȳ�� ���� ����� ���������� ���� �Ұ�
#define SRVAL_CITYHALL_FAIL_SYMBOLSTATUS_LOWERLEVEL	279 // ��Ȳ�� ���� ���� ���� - ��Ȳ�� ���� ����� ���������� ���� �Ұ�
#define SRVAL_CITYHALL_FAIL_SYMBOLSTATUS_MONEY		280 // ��Ȳ�� ���� ���� ���� - ��� �ڱ� ���� 
#define SRVAL_CITYHALL_FAIL_SYMBOLSTATUS_DATE		281 // ��Ȳ�� ���� ���� ���� - 1�� �̳����� ������ �Ұ� 
#define SRVAL_CITYHALL_FAIL_SYMBOLSTATUS_RESIDENT	282	// ��Ȳ�� ���� ���� ���� - ���� �ֹμ� ���� 
#define SRVAL_CITYHALL_FAIL_SYMBOLSTATUS_WARTIME	283 // ��Ȳ�� ���� ���� ���� - �����߿��� ���� �Ұ� 
#define SRVAL_CITYHALL_FAIL_SYMBOLSTATUS_NOTEXIST	284 // ��Ȳ�� ���� ���� ���� - ��Ȳ���� �ʵ忡 �������� ���� 

#define SRVAL_CITYHALL_FAIL_CASTLESTATUS_MONEY		285 // ĳ�� ���� ���� ���� - ��� �ڱ� ���� 
#define SRVAL_CITYHALL_FAIL_CASTLESTATUS_DATE		286 // ĳ�� ���� ���� ���� - 1�� �̳����� ������ �Ұ� 
#define SRVAL_CITYHALL_FAIL_CASTLESTATUS_RESIDENT	287	// ĳ�� ���� ���� ���� - ���� �ֹμ� ���� 
#define SRVAL_CITYHALL_FAIL_CASTLESTATUS_WARTIME	288 // ĳ�� ���� ���� ���� - �����߿��� ���� �Ұ� 
#define SRVAL_CITYHALL_FAIL_CASTLESTATUS_NOTEXIST	289 // ĳ�� ���� ���� ���� - ĳ���� �ʵ忡 �������� ���� 

#define SRVAL_CITYHALL_FAILDESTROYSTR_NOLAST		290	// 1���� ������ �ʾƼ� �ǹ� ��ü ����. 

#define SRVAL_CITYHALL_SUCCESS_PROFITTOCAPITALFUND	291 // ���ͱ�->�ں��� ��ȯ ���� 
#define SRVAL_CITYHALL_FAIL_PROFITTOCAPITALFUND		292 // ���ͱ�->�ں��� ��ȯ ����

#define SRVAL_CITYHALL_FAIL_EVENT_NOTENOUGHMONEY	295	// �̺�Ʈ ���� - �ں��� ����
#define SRVAL_CITYHALL_FAIL_EVENT_ALREADYSTARTED	296	// �̺�Ʈ ���� - �ٸ� �������� �ǽ� ��
#define SRVAL_CITYHALL_FAIL_EVENT_JAPANWAR			297 // �̺�Ʈ ���� - �ֱ� �����߿��� �ǽ� �Ұ�

#define SRVAL_CITYHALL_FAIL_CONSTRUCT_NOTFARM		298 // ������ �Ǽ� �� �� ���� 
#define SRVAL_CITYHALL_FAIL_DESTROYSTR_MEETING		299 // ������ȸ ���� �߿��� �ǹ��� ��ü�� �� ���� 

// ����. 
#define SRVAL_HOUSE_FAILAPPLY						300	// ���� ���� ����. - ����. 
#define SRVAL_HOUSE_FAILAPPLY_NOACCOUNT				305	// ���� ���� ���� - �������� ���� ���� ����. 
#define SRVAL_HOUSE_FAILAPPLY_ALREADYAPPLY			310	// ���� ���� ���� - �̹� ��û����. 
#define SRVAL_HOUSE_SUCCESSAPPLY					315 // ���� ���� ����. 
#define SRVAL_HOUSE_SUCCESSAPPLYCANCEL				317 // ���� ��� ����. 
#define SRVAL_HOUSE_FAILSETCONTRACT_NOTCHIEF		320 // ��� ���� ���� ����. - ��������� �ƴ�. 
#define SRVAL_HOUSE_FAILSETCONTRACT_WRONGFEE		321 // ��� ���� ���� ����. - �Ӵ�� ������ ���� 
#define SRVAL_HOUSE_FAILSETCONTRACT_DATE			322 // ��� ���� ���� ����. - �Ѵ޿� �ѹ��� ���� ����  
#define SRVAL_HOUSE_SUCCESSSETCONTRACT				325	// ��� ���� ���� ����. 
#define SRVAL_HOUSE_FAILNOTSAMECONTRACT				327 // �Ӵ� ���� - �������� ��� ���ǰ� �ٸ���.
#define SRVAL_HOUSE_FAILNOMOREREALESTATE			328 // �Ӵ� ���� - ���̻��� �ε����� ������ �� ����. 
#define SRVAL_HOUSE_SUCCESSHOUSERENT				329	// �Ӵ뼺��. 
#define SRVAL_HOUSE_SUCCESSDELHOUSEAPPLYER			330 // ���� ����� ��� ���� ���� 
#define SRVAL_HOUSE_FAILDELHOUSEAPPLYER_NOTCHIEF	335 // ���� ����� ��� ���� ����  - ���� ����� �ƴϴ�. 
#define SRVAL_HOUSE_FAILEXTENDCONTRAC_NOMONEY		336	// ��� ���� ���� - ���� �ܰ� ����. 
#define SRVAL_HOUSE_VILLAGELEVELLIMIT				337	// ������ ���� ���� �ÿ� ���� ������ ���Ƽ� ���� ���� ���� ������
#define SRVAL_HOUSE_SUCCESSEXTENDCONTRACT			340	// ��� ���� ����
#define SRVAL_HOUSE_FAILNOTENOUGHMONEY				341 // ������ �������� ����� ���� ����
#define SRVAL_HOUSE_FAILREMAINDITEM					342	// ������,��, ��ȯ���� �����־ ���� �ؾ� ����
#define SRVAL_HOUSE_SUCCESSCANCELLATION				343 // ���� �ؾ� ����
#define SRVAL_HOUSE_FAILINPUT_NOTRADEITEM			344 // �����ŷ��ֹ��� �ö��������� �ŷ��Ұ������� ������
#define SRVAL_HOUSE_FAILINPUT_FULLSTG				345	// ������ �κ��丮�� ������ ���̻� ������ ����.
#define SRVAL_HOUSE_FAILARRANGEITEM					346 // â�� ���� ���� 

// ���� 
#define SRVAL_MARKET_SUCCESS_ORDERSELL				400 // ���� �ֹ� ����. 
#define SRVAL_MARKET_FAIL_NOTRADEITEM				402	// ���� �ֹ� ���� - �ŷ� ���� ǰ��. 
#define SRVAL_MARKET_FAIL_ORDERSELL_OVERFLOW		405	// ���� �ֹ� ���� - �ֹ� ���� �ʰ�. 
#define SRVAL_MARKET_SUCCESS_GETFROMMARKET			410 // ���� ȸ�� ���� 
#define SRVAL_MARKET_FAIL_GETFROMMARKET				415 // ���� ȸ�� ���� - �κ��� �ڸ��� ����. 
#define SRVAL_MARKET_SUCCESS_TRADE					420 // ���� ���� ����. 
#define SRVAL_MARKET_FAILSETFEE						470	// ������ ���� ����. 
#define SRVAL_MARKET_SUCCESSSETFEE					471	// ������ ���� ����. 

// ���ո���
#define SRVAL_NEWMARKET_SUCCESS_ORDERSELL				472 // ���� �ֹ� ����. 
#define SRVAL_NEWMARKET_FAIL_NOTRADEITEM				473	// ���� �ֹ� ���� - �ŷ� ���� ǰ��. 
#define SRVAL_NEWMARKET_FAIL_ORDERSELL_OVERFLOW			474	// ���� �ֹ� ���� - �ֹ� ���� �ʰ�. 
#define SRVAL_NEWMARKET_SUCCESS_GETFROMMARKET			475 // ���� ȸ�� ���� 
#define SRVAL_NEWMARKET_FAIL_GETFROMMARKET				476 // ���� ȸ�� ���� - �κ��� �ڸ��� ����. 
#define SRVAL_NEWMARKET_SUCCESS_TRADE					477 // ���� ���� ����. 
#define SRVAL_NEWMARKET_FAILSETFEE						478	// ������ ���� ����. 
#define SRVAL_NEWMARKET_SUCCESSSETFEE					479	// ������ ���� ����. 
#define SRVAL_NEWMARKET_DONOT_TRADETIME					480	// ������ ���� ����
#define	SRVAL_NEWMARKET_FAIL_ORDERSELL_ALREADY_ORDERED	481	// ���� �ֹ� ���� - �̹� �ֹ��Ǿ� �ִ� ������


// ������ 
#define SRVAL_HUNT_NOPARTMEMBER						600 // ��Ƽ���� �ƴϾ ���� ����. 
#define SRVAL_HUNT_ALREADYPARTYUSE					601 // �̹� ������� ��Ƽ�� �ִ�. 
#define SRVAL_HUNT_FAILENTER_LEVEL					602	// ���� ���ѿ� �ɷ� �������� �̿��� �� ����. 
#define SRVAL_HUNT_FAILENTER_NOFEE					603	// ����ᰡ �����Ͽ� ���� �Ұ�. 
#define SRVAL_HUNT_NOTENOUGHREWARD					604 // ����� ��� �����Ͽ� ���� �Ұ�. 
#define SRVAL_HUNT_NOTENOUGHMON						605 // ����  ��� �����Ͽ� ���� �Ұ�. 
#define SRVAL_HUNT_TIMEOUT							606 // �ð� ���� �ɸ�. 

#define SRVAL_HUNT_FAIL_HUNTMAP_NOTENOUGHMONEY		607	// ����� ���� ���� ���� - �����ڱ� ����
#define SRVAL_HUNT_SUCCESS_HUNTMAP					608	// ����� ���� ���� ����

// ���� 
#define SRVAL_POSTOFFICE_SUCCESS_SENDITEM			700 // ������ ���� ����
#define SRVAL_POSTOFFICE_SUCCESS_SENDMSG			701 // �޽��� ���� ����
#define SRVAL_POSTOFFICE_SUCCESS_SENDMONEY			702 // �۱� ����

#define SRVAL_POSTOFFICE_FAIL_SEND_NOTENOUGHMONEY	711 // ���� ���� - ������ ����
#define SRVAL_POSTOFFICE_FAIL_SEND_NOTENOUGHFEE		712 // ���� ���� - ������ ����  
#define SRVAL_POSTOFFICE_FAIL_SEND_WRONGNAME		713 // ���� ���� - ������ ���̵� �߸���
#define SRVAL_POSTOFFICE_FAIL_SEND_FULLRECVBOX		714 // ���� ���� - ������ ����
#define SRVAL_POSTOFFICE_FAIL_SEND_SAMEPERSON		715 // ���� ���� - �ڱ� �ڽſ��Դ� ���� �� ����
#define SRVAL_POSTOFFICE_FAIL_SEND_USEDATEOVER		716 // ���� ���� - ���Ⱓ�� ���� ������ �ı�
#define SRVAL_POSTOFFICE_FAIL_SEND_NOTRADEITEM		717	// ���� ���� - �ŷ��Ұ� ������
#define SRVAL_POSTOFFICE_FAIL_SEND_NOTPOSTOFFICE	718	// ���� ���� - (���)���� ��ġ�� ������ ������ ����
//KHY - 0614 - ���� �������� ���� ������ ĳ���Ϳ� ���Ͽ� �������� �ְ� ���� �� �ִ�. 
#define SRVAL_POSTOFFICE_FAIL_SEND_ANOTHERPERSON	719	// ���� ���� - �ٸ� ������ ĳ���Ϳ��� ������ �޴�.


#define SRVAL_POSTOFFICE_SUCCESS_GETITEM			720 // ������ ���� ���� 
#define SRVAL_POSTOFFICE_FAIL_GETITEM_FULLINVEN		721 // ������ ���� ���� - �κ��丮 �� á��
#define SRVAL_POSTOFFICE_FAIL_GETITEM_USEDATEOVER	722	// ������ ���� ���� - ������ ���Ⱓ ����
#define SRVAL_POSTOFFICE_SUCCESS_GETMONEY			725 // ���� �ޱ� ����
#define SRVAL_POSTOFFICE_FAIL_GETMONEY				726 // ���� �ޱ� ���� 

#define SRVAL_POSTOFFICE_SUCCESS_SETFEE				730 // ������ ���� ����
#define SRVAL_POSTOFFICE_FAIL_SETFEE				731 // ������ ���� ���� 

#define SRVAL_GET_SAVEUSERITEM_SUCCESS				732	// ���� �輱�޿��Լ� ������ ��� ����
#define SRVAL_GET_SAVEUSERITEM_FAIL					733	// ���� �輱�޿��Լ� ������ ��� ����



// ����
#define SRVAL_PORT_FAILAPPLY_NOACCOUNT				800 // ���忡 ���°� ��� ���� �Ӵ� ����
#define SRVAL_PORT_FAILSETCONTRACT_NOTCHIEF			801 // ���� ������� ���� ���� ���� ����
#define SRVAL_PORT_SUCCESSSETCONTRACT				802 // ��� ���� ���� ����
#define SRVAL_PORT_FAILNOTSAMECONTRACT				803 // ���� ������ Ʋ��
#define SRVAL_PORT_FAILEXTENDCONTRACT_NOMONEY		804 // ���� �ܰ� �������� ���� ��� �ȵ�
#define SRVAL_PORT_SUCCESSPORTRENT					805 // ���� �Ӵ� ����


// �纹�� 
#define SRVAL_HORSEMARKET_SUCCESS_SELLHORSE			900 // �� ���� �ֹ� ���� 
#define SRVAL_HORSEMARKET_FAIL_SELL					901 // �� ���� �ֹ� ����
#define SRVAL_HORSEMARKET_FAIL_SELL_ALREADY			902 // �� ���� �ֹ� ���� - �̹� �ֹ� �� ���� ���� 
#define SRVAL_HORSEMARKET_FAIL_SELL_NOTEMPTYINVEN	903 // �� ���� �ֹ� ���� - �κ��丮�� ��ǰ�� ���� 
#define SRVAL_HORSEMARKET_FAIL_SELL_NOTHAVE			904 // �� ���� �ֹ� ���� - �����ϰ� �ִ� �� ���� 
#define SRVAL_HORSEMARKET_FAIL_SELL_NOTENOUGHMONEY	905 // �� ���� �ֹ� ���� - �������� ������ �� ����
#define SRVAL_HORSEMARKET_FAIL_SELL_CANNOTTRADE		906 // �� ���� �ֹ� ���� - �ŷ��� �Ұ����� ��

#define SRVAL_HORSEMARKET_SUCCESS_GETBACK			910 // �� ȸ�� ���� 
#define SRVAL_HORSEMARKET_FAIL_GETBACK				911 // �� ȸ�� ����
#define SRVAL_HORSEMARKET_FAIL_GETBACK_HAVEANOTHER	912 // �� ȸ�� ���� - ���� �����ϰ� �ִ� �� ���� 
#define SRVAL_HORSEMARKET_FAIL_GETBACK_NOORDER		913 // �� ȸ�� ���� - �ֹ� ���� 

#define SRVAL_HORSEMARKET_SUCCESS_BUYHORSE			920 // �� ���� ���� 
#define SRVAL_HORSEMARKET_FAIL_BUY					921 // �� ���� ���� 
#define SRVAL_HORSEMARKET_FAIL_BUY_NOTENOUGHMONEY	922 // �� ���� ���� - ���� ���� 
#define SRVAL_HORSEMARKET_FAIL_BUY_HAVEANOTHER		923 // �� ���� ���� - ���� �����ϰ� �ִ� �� ���� 
#define SRVAL_HORSEMARKET_FAIL_BUY_NOTSELF			924 // �� ���� ���� - �ڽ��� �ֹ��� ���� ������ �� ����
#define SRVAL_HORSEMARKET_FAIL_BUY_NOTVALID			925 // �� ���� ���� - ��ȿ�� �ֹ��� �ƴմϴ�

#define SRVAL_HORSEMARKET_SUCCESS_SETFEE				930 // ������ ���� ����
#define SRVAL_HORSEMARKET_FAIL_SETFEE					931 // ������ ���� ���� 

// �Ű�
#define SRVAL_REALESTATEMARKET_SUCCESS_SELL				950 // �ε��� ���� �ֹ� ���� 
#define SRVAL_REALESTATEMARKET_FAIL_SELL				951 // �ε��� ���� �ֹ� ���� 
#define SRVAL_REALESTATEMARKET_FAIL_SELL_NOTENOUGHMONEY	952 // �ε��� ���� �ֹ� ���� - �������� ������ �� ����
#define SRVAL_REALESTATEMARKET_FAIL_SELL_NOTVALID		953 // �ε��� ���� �ֹ� ���� - ���� ���� �ε��� �ƴ� 

#define SRVAL_REALESTATEMARKET_SUCCESS_CANCELORDER		955 // �ε��� �ֹ� ��� ���� 
#define SRVAL_REALESTATEMARKET_FAIL_CANCELORDER			956	// �ε��� �ֹ� ��� ���� 

#define SRVAL_REALESTATEMARKET_FAIL_SELL_HAVENOTRADE	957 // �ε��� ���� �ֹ� ���� - �ŷ��Ұ��������� ����
#define SRVAL_REALESTATEMARKET_FAIL_SELL_HAVENOTRADEHORSE	958 // �ε��� ���� �ֹ� ���� - �ŷ��Ұ���µ����� ����

#define SRVAL_REALESTATEMARKET_SUCCESS_BUY				960 // �ε��� ���� ���� 
#define SRVAL_REALESTATEMARKET_FAIL_BUY					961 // �ε��� ���� ���� 
#define SRVAL_REALESTATEMARKET_FAIL_BUY_NOTENOUGHMONEY	962 // �ε��� ���� ���� - ���� ���� 
#define SRVAL_REALESTATEMARKET_FAIL_BUY_NOMORE			963 // �ε��� ���� ���� - �� �̻� �ε����� ������ �� ����
#define SRVAL_REALESTATEMARKET_FAIL_BUY_NOTVALID		964 // �ε��� ���� ���� - ��ȿ�� �ֹ� �ƴ� 
#define SRVAL_REALESTATEMARKET_FAIL_BUY_NOTSELF			965 // �ε��� ���� ���� - �ڽ��� �ֹ��� �ε����� ������ �� ����

#define SRVAL_REALESTATEMARKET_SUCCESS_SETFEE			970 // ������ ���� ����
#define SRVAL_REALESTATEMARKET_FAIL_SETFEE				971 // ������ ���� ���� 

#define SRVAL_STOCKOFFERING_SUCCESS_ORDER				980	
#define SRVAL_STOCKOFFERING_FAIL_ORDERALREADY			981
#define SRVAL_STOCKOFFERING_FAIL_ORDER					982
#define SRVAL_STOCKOFFERING_FAIL_ORDERMONEY				983
#define SRVAL_STOCKOFFERING_FAIL_ORDERLIMIT				984



// �忹��
#define SRVAL_SUMMONMARKET_SUCCESS_SELL					1000 // ��ȯ�� ���� �ֹ� ���� 
#define SRVAL_SUMMONMARKET_FAIL_SELL					1001 // ��ȯ�� ���� �ֹ� ���� 
#define SRVAL_SUMMONMARKET_FAIL_SELL_NOMORE				1002 // ��ȯ�� ���� �ֹ� ���� - ���̻� �ֹ��� �� ����
#define SRVAL_SUMMONMARKET_FAIL_SELL_NOTHAVE			1003 // ��ȯ�� ���� �ֹ� ���� - �����ϰ� �ִ� ��ȯ�� ���� 
#define SRVAL_SUMMONMARKET_FAIL_SELL_NOTENOUGHMONEY		1004 // ��ȯ�� ���� �ֹ� ���� - �������� ������ �� ����
#define SRVAL_SUMMONMARKET_FAIL_SELL_HAVEITEM			1009 // ��ȯ�� ���� �ֹ� ���� - ��ȯ���� ��ǰ�� ����ϰ� ���� 

#define SRVAL_SUMMONMARKET_SUCCESS_CANCELORDER			1005 // ��ȯ�� �ֹ� ��� ���� 
#define SRVAL_SUMMONMARKET_FAIL_CANCELORDER				1006 // ��ȯ�� �ֹ� ��� ���� 
#define SRVAL_SUMMONMARKET_FAIL_CANCELORDER_NOMORE		1007 // ��ȯ�� �ֹ� ��� ���� - ���̻� ������ �� ���� 
#define SRVAL_SUMMONMARKET_FAIL_CANCELORDER_NOTVALID	1008 // ��ȯ�� �ֹ� ��� ���� - ��ȿ�ֹ� �ƴ�

#define SRVAL_SUMMONMARKET_SUCCESS_BUY					1010 // ��ȯ�� ���� ���� 
#define SRVAL_SUMMONMARKET_FAIL_BUY						1011 // ��ȯ�� ���� ���� 
#define SRVAL_SUMMONMARKET_FAIL_BUY_NOTENOUGHMONEY		1012 // ��ȯ�� ���� ���� - ���� ���� 
#define SRVAL_SUMMONMARKET_FAIL_BUY_NOMORE				1013 // ��ȯ�� ���� ���� - ���̻� ������ �� ����
#define SRVAL_SUMMONMARKET_FAIL_BUY_NOTSELF				1014 // ��ȯ�� ���� ���� - �ڽ��� �ֹ��� ��ȯ���� ������ �� ���� 
#define SRVAL_SUMMONMARKET_FAIL_BUY_NOTVALID			1015 // ��ȯ�� ���� ���� - ��ȿ�� �ֹ� �ƴ� 

#define SRVAL_SUMMONMARKET_FAIL_SELL_USER_NO_BANK		1016 // ��ȯ�� ���� ������ ��� �ֹ� ����.

#define SRVAL_SUMMONMARKET_SUCCESS_SETFEE				1020 // ������ ���� ����
#define SRVAL_SUMMONMARKET_FAIL_SETFEE					1021 // ������ ���� ���� 

#define SRVAL_SUMMONMARKET_FAIL_SELECTSELL_WRONGNAME		1022	// �����ŷ� ���� �ֹ��� ���̵� �߸���
#define SRVAL_SUMMONMARKET_FAIL_BUY_NOTSELECTPERSON			1023	// �����ŷ� ���� ����ڰ� �ƴ� ���� �Ұ�
#define SRVAL_SUMMONMARKET_FAIL_SELECTSELL_NOTHAVETICKET	1024	// �����ŷ� �̿�� ����
#define SRVAL_SUMMONMARKET_FAIL_SELECTSELL_WRONGPRICE		1025	// �����ŷ� �����Ǽ��� ���� ���� ���� ���� ����

// ����
#define SRVAL_LAND_SUCCESS_APPLY					1201	// ���� ��û ����. 
#define SRVAL_LAND_FAIL_APPLY						1202	// ���� ��û ���� - ����. 
#define SRVAL_LAND_FAIL_APPLY_NOACCOUNT				1203	// ���� ��û ���� - �������� ���� ���� ����. 
#define SRVAL_LAND_FAIL_APPLY_ALREADYAPPLY			1204	// ���� ��û ���� - �̹� ��û����. 

#define SRVAL_LAND_SUCCESS_CANCELAPPLY				1210	// ���� ��� ����. 
#define SRVAL_LAND_FAIL_CANCELAPPLY					1211	// ���� ��� ���� 

#define SRVAL_LAND_SUCCESS_SETCONTRACT				1221	// ��� ���� ���� ����. 
#define SRVAL_LAND_FAIL_SETCONTRACT					1222	// 
#define SRVAL_LAND_FAIL_SETCONTRACT_WRONGFEE		1223	// ��� ���� ���� ����. - �Ӵ�� ������ ���� 
#define SRVAL_LAND_FAIL_SETCONTRACT_DATE			1224	// ��� ���� ���� ����. - �Ѵ޿� �ѹ��� ���� ����  

#define SRVAL_LAND_SUCCESS_RENT						1230	// �Ӵ뼺��. 
#define SRVAL_LAND_FAIL_RENT						1231	// �Ӵ� ����
#define SRVAL_LAND_FAIL_NOTSAMECONTRACT				1232	// �Ӵ� ���� - �������� ��� ���ǰ� �ٸ���.
#define SRVAL_LAND_FAIL_NOMOREREALESTATE			1233	// �Ӵ� ���� - �� �̻��� �ε����� ������ �� ����. 
#define SRVAL_LAND_FAIL_RENT_NOTEMPTY				1234	// �Ӵ� ���� -
#define SRVAL_LAND_FAIL_RENT_INVALIDPERSONID		1235	// �Ӵ� ���� -
#define SRVAL_LAND_SUCCESS_DELLANDAPPLYER			1240	// ���� ����� ��� ���� ���� 

// ���ڽ�
#define SRVAL_FEAST_SUCCESS_RESERVE					1260	// ��ȸ ���� ���� 
#define SRVAL_FEAST_FAIL_RESERVE					1261	// ��ȸ ���� ���� 
#define SRVAL_FEAST_FAIL_RESERVE_NOTENOUGHMONEY		1262	// ��ȸ ��� ���� 
#define SRVAL_FEAST_FAIL_RESERVE_ALREADY			1263	// �����ڰ� ���� 
#define SRVAL_FEAST_FAIL_RESERVE_DATE				1264	// ���� ��¥�� ���� 1��(���ǽð�) �̳��� �ð����θ� ���డ�� 
#define SRVAL_FEAST_FAIL_RESERVE_OPEN				1265	// ��ȸ�� ��������
#define SRVAL_FEAST_FAIL_RESERVE_ITEM				1266	// ��ǰ�� �غ���� ����
#define SRVAL_FEAST_FAIL_NOCHANGE					1267	// �����ڰ� �ְų� ��ȸ���϶��� ���� �Ұ�
#define SRVAL_FEAST_SUCCESS_SETCOST					1268	// ��ȸ��� ���� ����
#define SRVAL_FEAST_FAIL_SETCOST					1269	// ��ȸ��� ���� ����
#define SRVAL_FEAST_SUCCESS_GIVEITEM				1270	// ��ȸ ��ǰ ���� ����
#define SRVAL_FEAST_FAIL_GIVEITEM					1271	// ��ȸ ��ǰ ���� ����
#define SRVAL_FEAST_FAIL_GIVEITEM_WRONGPERSON		1272	// ��ȸ ������ �ƴ�
#define SRVAL_FEAST_FAIL_GIVEITEM_NOTOPEN			1273	// ��ȸ�� �ƴ�
#define SRVAL_FEAST_FAIL_GIVEITEM_ALREADY			1274	// �̹� ������ ��ǰ��
#define SRVAL_FEAST_FAIL_ITEM_WRONG					1275	// ����� �� ���� ��������
#define SRVAL_FEAST_FAIL_ITEM_ALREADY				1276	// �̹� ��ϵ� ��������

//#if defined(_LEON_FEAST_EFFECT)
	#define SRVAL_FEAST_FAIL_USEEFFECT_NOTHAVETICKET		1277	// �����̿�� ����
	#define SRVAL_FEAST_SUCCESS_USEEFFECT					1278	// �����̿�� ��� ����
//#endif

#define SRVAL_FEAST_FAIL_ITEM_TOOMANY				1279	// ������ ������ �ʹ� ����

// �񺯻�
#define SRVAL_SUMMONHEROMARKET_SUCCESS_SELL				1300 // ��ȯ���� ���� �ֹ� ���� 
#define SRVAL_SUMMONHEROMARKET_FAIL_SELL				1301 // ��ȯ���� ���� �ֹ� ���� 
#define SRVAL_SUMMONHEROMARKET_FAIL_SELL_NOMORE			1302 // ��ȯ���� ���� �ֹ� ���� - ���̻� �ֹ��� �� ����
#define SRVAL_SUMMONHEROMARKET_FAIL_SELL_NOTHAVE		1303 // ��ȯ���� ���� �ֹ� ���� - �����ϰ� �ִ� ��ȯ���� ���� 
#define SRVAL_SUMMONHEROMARKET_FAIL_SELL_NOTENOUGHMONEY	1304 // ��ȯ���� ���� �ֹ� ���� - �������� ������ �� ����
#define SRVAL_SUMMONHEROMARKET_FAIL_SELL_HAVEITEM		1309 // ��ȯ���� ���� �ֹ� ���� - ��ȯ������ ��ǰ�� ����ϰ� ���� 

#define SRVAL_SUMMONHEROMARKET_SUCCESS_CANCELORDER		1305 // ��ȯ���� �ֹ� ��� ���� 
#define SRVAL_SUMMONHEROMARKET_FAIL_CANCELORDER			1306 // ��ȯ���� �ֹ� ��� ���� 
#define SRVAL_SUMMONHEROMARKET_FAIL_CANCELORDER_NOMORE	1307 // ��ȯ���� �ֹ� ��� ���� - ���̻� ������ �� ���� 
#define SRVAL_SUMMONHEROMARKET_FAIL_CANCELORDER_NOTVALID	1308 // ��ȯ���� �ֹ� ��� ���� - ��ȿ�ֹ� �ƴ�

#define SRVAL_SUMMONHEROMARKET_SUCCESS_BUY				1310 // ��ȯ���� ���� ���� 
#define SRVAL_SUMMONHEROMARKET_FAIL_BUY					1311 // ��ȯ���� ���� ���� 
#define SRVAL_SUMMONHEROMARKET_FAIL_BUY_NOTENOUGHMONEY	1312 // ��ȯ���� ���� ���� - ���� ���� 
#define SRVAL_SUMMONHEROMARKET_FAIL_BUY_NOMORE			1313 // ��ȯ���� ���� ���� - ���̻� ������ �� ����
#define SRVAL_SUMMONHEROMARKET_FAIL_BUY_NOTSELF			1314 // ��ȯ���� ���� ���� - �ڽ��� �ֹ��� ��ȯ������ ������ �� ���� 
#define SRVAL_SUMMONHEROMARKET_FAIL_BUY_NOTVALID		1315 // ��ȯ���� ���� ���� - ��ȿ�� �ֹ� �ƴ� 


#define SRVAL_SUMMONHEROMARKET_SUCCESS_SETFEE				1320 // ������ ���� ����
#define SRVAL_SUMMONHEROMARKET_FAIL_SETFEE					1321 // ������ ���� ���� 

#define SRVAL_SUMMONHEROMARKET_FAIL_SELECTSELL_WRONGNAME		1322	// �����ŷ� ���� �ֹ��� ���̵� �߸���
#define SRVAL_SUMMONHEROMARKET_FAIL_BUY_NOTSELECTPERSON			1323	// �����ŷ� ���� ����ڰ� �ƴ� ���� �Ұ�
#define SRVAL_SUMMONHEROMARKET_FAIL_SELECTSELL_NOTHAVETICKET	1324	// �����ŷ� �̿�� ����
#define SRVAL_SUMMONHEROMARKET_FAIL_SELECTSELL_WRONGPRICE		1325	// �����ŷ� �����Ǽ��� ���� ���� ���� ���� ����





#define SRVAL_STRMSG_SUCCESS						1450	// �ǹ� �ȳ��� ���� ����

// ���� 
#define SRVAL_TAX_SUCCESS_SETTAX					1480 // ���� ���� ���� 
#define SRVAL_TAX_SUCCESS_PAYTAX					1490 // ���� ���� ���� 
#define SRVAL_TAX_FAIL_PAYTAX_NOTENOUGHMONEY		1491 // ���� ���� ���� - �ü��� �����ڱ��� ������� ����
#define SRVAL_TAX_FAIL_PAYTAX_NODURA				1492 // ���� ���� ���� - �ǹ� ������ ����
#define SRVAL_TAX_FAIL_WRONGMONEY					1493 // ���� ���� ���� - 10���� �̸�
#define SRVAL_TAX_FAIL_DATE							1494 // ���� ���� ���� - �Ѵ޿� �ѹ��� ���� ����

// ��� 
#define SRVAL_DIVIDEND_SUCCESS_PAYDIVIDEND			1495 // ��� ����
#define SRVAL_DIVIDEND_FAIL_WRONGMONEY				1496 // ��� ���� - ������ �������� ����
#define SRVAL_DIVIDEND_FAIL_NOTENOUGHMONEY			1497 // ��� ���� - ��ܿ� �����ڱ��� ������� ���� 
#define SRVAL_DIVIDEND_FAIL_DATEERROR				1498 // ��� ���� - ������� �������� ����


// �α��� 
#define SRVAL_MAKEPERSON_FAIL_DUPNAME				1500	// ĳ���� ���� ����. - �ߺ��� ĳ����. 
#define SRVAL_DELPERSON_FAIL_UNKNOWN				1510	// ĳ���� ����� ���� 
#define SRVAL_DELPERSON_FAIL_IDMATCHERROR			1520	// ĳ���� ����� ���� - �ֹε�Ϲ�ȣ ����ġ 
#define SRVAL_LOGINFAIL_LIMITMAXUSER				1221	// ���������� �ɷ��� �α��� ����

#define SRVAL_NOTCORRECTIP							1530	// ���ӺҰ����� IP

//KHY - 0910 - Ŭ���̾�Ʈ�� ĳ���������� ���ϰ��� ������.
// Ư�� ���ּҰ��� ������, ���¸� Ȯ���ϰ� �Ѵ�.
#define SRVAL_CHECK_WEBVAL							1531	// ���ӺҰ����� IP

// ����Ʈ. 
#define SRVAL_QUEST_FAIL_FULLINV					1600 // ����Ʈ ��ǰ ���� ���� - �κ��� ����. 


// DailyQuest
#define SRVAL_DAILYQUEST_FAIL_NOTEXISTLIST			1650	// DailyQuest ���� ����Ʈ ������ ���� ����Ʈ�� ���� ���
// DailyQuest2
#define SRVAL_DAILYQUEST2_FAIL_NOTEXISTLIST			1650	// DailyQuest ���� ����Ʈ ������ ���� ����Ʈ�� ���� ���

// ��ǰ ���� ���� 
#define SRVAL_NOTENOUGHTOOLDURABILITY				1700	// ������ �������� �����Ͽ� ��ǰ ���� ����. 
#define SRVAL_TOOMANYITEMMAKE						1701	// �ѹ��� 1���� �̻��� ��ǰ�� ���� �Ұ�. 

// ���� �̵�. 
#define SRVAL_NOTENOUGHLEVELTOMAP					1800	// ������ ���� ������ �ű� �� ����. 
#define SRVAL_TOOHIGHLEVEL							1801	// 
#define SRVAL_FAIL_WARP_LIMITTIME					1802	// �����̵��� 3�ʸ��� �ѹ���
#define SRVAL_TOOHIGHLEVEL_SANTA					1803	// ��Ÿ�۾����� ��������
#define SRVAL_FAIL_WARP_LEVEL_RANGE					1804	// ���� ������ ��� ���� �Ұ�
#define SRVAL_FAIL_WARP_NOITEM						1805	// ���忡 �ʿ��� �������� ��� ���� �Ұ�
#define SRVAL_FAIL_WARP_BLOCKWARP					1806	// ������ �����Ǿ� �ִ� ���̴�.
#define SRVAL_FAIL_FORBID_ENTERMAP					1807	// �� �� ���� ���̴�.
#define SRVAL_FAIL_FORBID_BATTLE					1808	// ������ �߿��� ģ������ �̵��� �Ұ��� �մϴ�.
#define SRVAL_FAIL_RACCOONWORLD						1809	// �������� ������ ���� ����
//#define SRVAL_FAIL_WARP_RETURNTOWER					1809	// [����/090515] - ��ȯž ��ġ�ؾ߸� ���� �����ϴٴ� �޼���.

// ��Ƽ�θ� �̵�����
#define SRVAL_NOPARTY								1850	// ��Ƽ�θ� �̵�����
#define SRVAL_NOINSTANCEMAP							1851	// ���̻� �ν��Ͻ� ������ ����.
#define SRVAL_MAKE_BOSSMONSTER						1852	// ���� ���Ͱ� ���������
#define SRVAL_CLEAR_INSTANCEMAP						1853	// �ν��Ͻ� ���� Ŭ����
#define SRVAL_FAIL_TIMEOUT							1854	// ���� �ð� �ʰ��� ����

// ���� 
#define SRVAL_NOWARSEASON							1900	// ����ÿ��� �̿��� �� �ִ�. 
#define SRVAL_OUTOFWARKILL							1901	// ������ �����Ͽ� �̿��� �� ����. 
#define SRVAL_AUTOWAR								1902	// �ڵ�����. 

#define SRVAL_BLACKARMY_MAPPOSITION					1910	// ���Ǳ��� ���� ������ ����
#define SRVAL_BLACKARMY_NOTALLOC					1911	// �ش��ϴ� ���� �ƴ�
#define SRVAL_BLACKARMY_NOTWAR						1912	// ����ð� �ƴ�
#define SRVAL_BLACKARMY_WARAPPLY					1913	// �����û (1 : ����, 2 : �Ұ���) [GMĿ�ǵ� ����]
#define SRVAL_BLACKARMY_FAILALLOC					1914	// ����� ���� ����

#define SRVAL_WENNYOLDMAN_FULLINVEN					1950	// Ȥ�θ�(2ȣ��) ����� �κ��� ������ ������ ������ ���� ����
#define SRVAL_WENNYOLDMAN_FAILDISASSEMBLE_FULLINVEN	1951	// Ȥ�θ�(2ȣ��) �κ��� ������ ���� ����
#define SRVAL_WENNYOLDMAN_FAILDISASSEMBLE_UNLUCK	1952	// Ȥ�θ�(2ȣ��) Ȯ���� ���Ͽ� ���� ����
#define SRVAL_WENNYOLDMAN_FAILDISASSEMBLE_LOWPRICE	1953	// Ȥ�θ�(2ȣ��) ���������� ���� �Ұ�
#define SRVAL_WENNYOLDMAN_FAILDISASSEMBLE_CANNOTITEM	1954	// Ȥ�θ�(2ȣ��) ���� �Ұ� ������

#define SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN		1960	// �������� �κ��� ������ ���ڿ��� ����
#define SRVAL_FEAST_FAIL_USE_ONLY_VILLAGE			1961	// ���� �������� �����ȿ����� ��밡���ϴ�.

// [����] ���� ���� ���ڿ��� �������� �ش� 
#define SRVAL_FAIL_OPEN_LEVELLIMTBOX_NOT_OVER_LEVEL		1980	//	���ڸ� ���� �ִ� ������ �ȵȴ� 
#define SRVAL_FAIL_OPEN_LEVELLIMTBOX_NOT_NOT_ENOUGH_INV	1981	//	�κ��丮 ������ ���� �ϴ�


#define SRVAL_HIDDENQUEST_BOX						10100	// ���� ����Ʈ

// ���� ���� ��� �̺�Ʈ 
#define SRVAL_GOGUWARPFAIL_NOTVILLAGE				2000	// ���� �������� �̵� �Ұ�. - �̺�Ʈ ���� �ֹ��� �ƴ�. 
#define SRVAL_GOGUWARPFAIL_NOEVENTTIME				2001	// ���� �������� �̵� �Ұ�. - �ش� �̺�Ʈ �ð��� �ƴ�. 

// ����ī ����
#define SRVAL_NOOSAKAWARSEASON						2010	// ����ÿ��� �̿��� �� �ִ�. 

#define SRVAL_NOWARP_TRADEPORT_VILLAGE				2015	// �����ִ� ���� �ֹ��� �ƴϴ�.
#define SRVAL_INSTANCEPROFIT_VILLAGE				2016	// �ν��Ͻ� ���� ���ͱ� ��������.

// ��ȭ�� ��� �̺�Ʈ 
#define SRVAL_KANGHWADOWARPFAIL_NOTVILLAGE			2020	// ��ȭ�� �̵� �Ұ�. - �̺�Ʈ ���� �ֹ��� �ƴ�. 
#define SRVAL_KANGHWADOWARPFAIL_NOEVENTTIME			2021	// ��ȭ�� �̵� �Ұ�. - �ش� �̺�Ʈ �ð��� �ƴ�. 

// ���ĸ��� �̺�Ʈ
#define SRVAL_MOFUMOFUEVENT_START_LEFTTIME			2030	// %d�� ���ҽ��ϴ�. ���ĸ��� ���̰��� ������ ���̼���. (�ڵ��̵��� 1000Q)
#define SRVAL_MOFUMOFUEVENT_FAIL_ALREADY_RESERVE	2031	// �̹� ��û�� �ð��Դϴ�. �ٸ� �ð��� �����Ͽ� �ֽʽÿ�.
#define SRVAL_MOFUMOFUEVENT_FAIL_RESERVE			2032	// �̺�Ʈ ���࿡ �����Ͽ����ϴ�.
#define SRVAL_MOFUMOFUEVENT_SUCCESS_SETENEMYCOUNT	2033	// ��� ���� ���� �ٲٱ� ����
#define	SRVAL_MOFUMOFUEVENT_FAIL_SETENEMYCOUNT		2034	

// ������ �̺�Ʈ
#define	SRVAL_PIRATESHIP_APPEAR						2040	// ������ ��Ÿ��

#define SRVAL_PUCHIKOMI_FAIL_OP_REJECTION			2101	// Ǫġ�ڹ� - ������ ���� �ź���

// ����
#define SRVAL_MINE_SUCCESS_APPLY					2201	// ���� ��û ����. 
#define SRVAL_MINE_FAIL_APPLY						2202	// ���� ��û ���� - ����. 
#define SRVAL_MINE_FAIL_APPLY_NOACCOUNT				2203	// ���� ��û ���� - �������� ���� ���� ����. 
#define SRVAL_MINE_FAIL_APPLY_ALREADYAPPLY			2204	// ���� ��û ���� - �̹� ��û����. 

#define SRVAL_MINE_SUCCESS_CANCELAPPLY				2210	// ���� ��� ����. 
#define SRVAL_MINE_FAIL_CANCELAPPLY					2211	// ���� ��� ���� 

#define SRVAL_MINE_SUCCESS_SETCONTRACT				2221	// ��� ���� ���� ����. 
#define SRVAL_MINE_FAIL_SETCONTRACT					2222	// 
#define SRVAL_MINE_FAIL_SETCONTRACT_WRONGFEE		2223	// ��� ���� ���� ����. - �Ӵ�� ������ ���� 
#define SRVAL_MINE_FAIL_SETCONTRACT_DATE			2224	// ��� ���� ���� ����. - �Ѵ޿� �ѹ��� ���� ����  

#define SRVAL_MINE_SUCCESS_RENT						2230	// �Ӵ뼺��. 
#define SRVAL_MINE_FAIL_RENT						2231	// �Ӵ� ����
#define SRVAL_MINE_FAIL_NOTSAMECONTRACT				2232	// �Ӵ� ���� - �������� ��� ���ǰ� �ٸ���.
#define SRVAL_MINE_FAIL_NOMOREREALESTATE			2233	// �Ӵ� ���� - �� �̻��� �ε����� ������ �� ����. 
#define SRVAL_MINE_FAIL_RENT_NOTEMPTY				2234	// �Ӵ� ���� -
#define SRVAL_MINE_FAIL_RENT_INVALIDPERSONID		2235	// �Ӵ� ���� -
#define SRVAL_MINE_SUCCESS_DELMINEAPPLYER			2240	// ���� ����� ��� ���� ���� 

#define SRVAL_CITYHALL_FAIL_CONSTRUCT_NOTMINE			2250
#define SRVAL_CITYHALL_FAIL_CONSTRUCT_NOTENOUGHMONEY	2251

//----------------------------------
// ���
//----------------------------------
#define SRVAL_GUILD_SUCCESS_CREATE					2300	// ������� ���� ����
#define SRVAL_GUILD_FAIL_CREATE						2301	// ������� ���� ����
#define SRVAL_GUILD_FAIL_WRONG_NAME					2302	// �������� ����
#define SRVAL_GUILD_FAIL_FULLSLOT					2303	// ������� ���� ���� - ��á��
#define SRVAL_GUILD_FAIL_ALREADYMEMBER				2304	// ������� ���� ���� - �̹� �ٸ� ��� �����
#define SRVAL_GUILD_FAILSETFEE						2305	// �� ������ ���� ����. 
#define SRVAL_GUILD_FAILSETFEERATE					2306	// �������� ���� ����. 
#define SRVAL_GUILD_SUCCESSSETCONTRACT				2307	// �� ������ �� �������� ���� ����. 
#define SRVAL_GUILD_FAILSETCONTRACT_NOTCHIEF		2308	// ��� ���� ���� ����. - �������� �ƴ�. 
#define SRVAL_GUILD_FAILSETCONTRACT_WRONGFEE		2309	// �� ������ �λ� �� ���� 
#define SRVAL_GUILD_FAILSETCONTRACT_DATE			2310	// ��� ���� ���� ����. - �Ѵ޿� �ѹ��� ���� ����  
#define SRVAL_GUILD_FAILSETCONTRACT					2311	// �� ������ �� �������� ���� ���� 
#define SRVAL_GUILD_FAIL_GETGUILDRANKLIST			2312	// ��� ��ŷ ����Ʈ�� ��µ� ����
#define SRVAL_GUILD_FAIL_NOTENOUGHMONEY				2313	// �������� ������
#define SRVAL_GUILD_FAIL_NOTCONNECTMASTER			2314	// ������� ���� �Ű� ����

#define SRVAL_GUILDWAR_FAILAPPLY_DENY				2315	// ���� ��忡�� �ź���
#define SRVAL_GUILDWAR_FAILAPPLY_ALREADY			2316	// �̹� �ٸ� ��忡�� ��������
#define SRVAL_GUILDWAR_FAILAPPLY_LOWLEVEL			2317	// ������ ����.6692
#define SRVAL_GUILDWAR_FAILAPPLY_NOTCONNECTED		2318	// ���� �����Ͱ� �������� ����
#define SRVAL_GUILDWAR_FAILAPPLY_FAULTNAME			2319	// ���� ���!6690
#define SRVAL_GUILDWAR_FAILAPPLY_MYGUILD			2320	// ����� 6691
#define SRVAL_GUILDWAR_FAILAPPLY_IM_ALREADYRESERVE	2321	// �� ��尡 ���� �ð��� �̹� �������̴�
#define SRVAL_GUILDWAR_FAILAPPLY_ENEMY_ALREADYRESERVE	2322 // ��� ��尡 ���� �ð��� �̹� �������̴�
#define SRVAL_GUILDWAR_FAILAPPLY_NOTALLOWSERVER		2323	// ����� ������� �ʴ� ����
#define SRVAL_GUILDWAR_FAILAPPLY_OVERTIME			2324	// �Ϸ翡 ������� 3ȸ�̻� �Ҽ� ����.

#define SRVAL_GUILDDUNGEON_FAIL_REG					2400	// ������Ϳ� �̹� ��ϵǾ� �־ ����

#define SRVAL_PAYFEE_SUCCESS						3900 // ������ ���� ����
#define SRVAL_PAYFEE_FAIL_NOTENOUGHMONEY			4001 // ������ ���� ���� - ���¿� ���� ������� ����

// ������. 
#define SRVAL_NOLISTINFATHERAPPLYER					5000 // ��밡 ���� ��� ��û�� ����ؼ� �������� ����� �� ����. 
#define SRVAL_SUCCESSAPPLYFATHER					5010 // ���� ��� ��û ����. 
#define SRVAL_FAILAPPLYFATHER_ALREADY				5020 // �̹� ���� ��� ��û�Ǿ� �־ ��� ����. 
#define SRVAL_FAILAPPLYFATHER_FULL					5030 // ���� ��� ��û�� ������ ���̻� ��� �Ұ�. 
#define SRVAL_SUCCESSDELFATHERAPPLY					5040 // ���� ��� ��û ��� ����. 

#define	SRVAL_INITSTATUS							6000 // ��ų, �������ͽ� �ʱ�ȭ �Ǵ�. 

// �ֽ� ���� 
#define SRVAL_STOCKGIVEFAIL_FULL					7000	// �ֽ� ����� 10���� �̻��� �ֽ��� �̹� �����ϰ� �־� ����. 
#define SRVAL_STOCK_FAIL_DISTRIBUTIONSTOP			7010	// �ֽ� ���� ��û�� ������ ���� ���������� ����.
#define SRVAL_AUTOSTOCKDISTRIBUTION					7020	// �ڵ�����

// ������ 
#define SRVAL_WAR_CANTENTERENEMYCASTLE				7100	// ������ �߿��� �������� ������ �� �� ����. 

// ���� �ŷ�
#define SRVAL_PRIVATETRADE_MONEY_INSUFFICIENCY		7300	// �� �ŷ����� ���� ����
#define SRVAL_PRIVATETRADE_ITEM_INFO_DIFFERENT		7301	// �ֽ� �ŷ����� �ֽ��� ������ Ʋ��
#define SRVAL_PRIVATETRADE_PERSON_INVENTORY_FULL	7302	// ������ �ŷ����� �κ��� ����� ����
#define SRVAL_PRIVATETRADE_STOCK_INFO_DIFFERENT		7303	// �ֽ� �ŷ����� �ֽ��� ������ Ʋ��
#define SRVAL_PRIVATETRADE_HOUSEUNIT_INFO_DIFFERENT	7304	// ���� �ŷ����� ������ ������ Ʋ��
#define SRVAL_PRIVATETRADE_HORSE_INFO_DIFFERENT		7305	// �� �ŷ����� ���� ������ Ʋ��
#define SRVAL_PRIVATETRADE_HORSE_INVENTORY_NOTEMPTY 7306	// �� �ŷ����� �� �κ��� ��� ���� ���� ���
#define SRVAL_PRIVATETRADE_HORSE_NAME_SAME			7307	// �� �ŷ����� �� ���� �̸��� ���� ���. �� �̸��� �ٸ� ��쿡�� �ŷ� ������
#define SRVAL_PRIVATETRADE_HOUSEUNIT_LEVEL_LIMIT	7308	// ���� �ŷ����� ������ �ŷ��� �� �ִ� ���� ������ ���� ���� ���.
#define SRVAL_PRIVATETRADE_HOUSEUNIT_EXCEED_NUMBER_PER_PERSON	7309	// ���� ���� �ʰ� ���� �� ����.
#define SRVAL_PRIVATETRADE_STOCK_TOOMANY			7310	// �ֽ� ���� ���� �ʰ�
#define SRVAL_PRIVATETRADE_HORSE_NOTEMPTY			7311	// ���� �� �̻� �߰� �Ұ�
#define SRVAL_PRIVATETRADe_HORSE_CANNOTTRADE		7312	// �ŷ� �Ұ����� ����.

// ��ǥ
#define SRVAL_VOTE_INIT								7450	// ��ǥ �ʱ�ȭ �Ϸ�

// ģ��
#define SRVAL_FRIEND_NOTCONNECTED					7500	// ģ���� �߰��ҷ��� ����� ���� ���������� �ʴ�.

#define SRVAL_CITYHALL_SUCCESS_HIRENPC				8000	// ��� ���� 
#define SRVAL_CITYHALL_FAIL_HIRENPC_NOTENOUGHMONEY	8001	// ��� �ڱ� ���� 
#define SRVAL_CITYHALL_FAIL_HIRENPC_VILLAGELEVEL	8002	// �ʿ� ���� ���� ����
#define SRVAL_CITYHALL_FAIL_HIRENPC_BUILDSTRUCTURE	8003    // NPC���Կ� �ǹ��� ������ ����
#define SRVAL_CITYHALL_FAIL_HIRECHRISTMAS_NOTENOUGHMONEY	8004	// ũ�������� Ʈ�� �Ǽ� �ڱ� ����

#define SRVAL_CITYHALL_FAIL_CONSTRUCT_NPCZONE		8014	// �ǹ��� �������� ���Կ� NPC�� ���Ǿ����� 
#define SRVAL_CITYHALL_FAIL_CONSTRUCT_VILLAGELEVEL	8015	// �ʿ� ���� ���� ����

#define SRVAL_CITYHALL_SUCCESS_VILLAGEMARK				8016	// ���� ��ũ ���� ����
#define SRVAL_CITYHALL_FAIL_VILLAGEMARK_NOTENOUGHMONEY	8017	// ���� ��ũ ���� ���� - �����ڱ� ����
#define SRVAL_CITYHALL_FAIL_VILLAGEMARK_ALREADYUSED		8018	// ���� ��ũ ���� ���� - �ٸ� �������� ����� 
#define SRVAL_CITYHALL_FAIL_VILLAGEMARK_DATE			8019	// ���� ��ũ ���� ���� - �������� �Ѵ��� ������ �ʾ��� 

#define SRVAL_CITYHALL_SUCCESS_VILLAGEMAP				8020	// ���� ��ũ ���� ����
#define SRVAL_CITYHALL_FAIL_VILLAGEMAP_NOTENOUGHMONEY	8021	// ���� ��ũ ���� ���� - �����ڱ� ����
#define SRVAL_CITYHALL_FAIL_VILLAGEMAP_LEVEL			8022	// ���� ��ũ ���� ���� - ������ ����

#define SRVAL_CITYHALL_FAIL_RESIDENTSHARE_WRONGCOUNT		8100		// �ֹ� ���� ����
#define SRVAL_CITYHALL_FAIL_RESIDENTSHARE_WRONGMONEY		8101		// ���� ������
#define SRVAL_CITYHALL_FAIL_RESIDENTSHARE_NOTENOUGHMONEY	8102		// ��� �ڱ� ����
#define SRVAL_CITYHALL_FAIL_RESIDENTSHARE_WRONGTIME			8103		// ��� ���� �ð� �ƴ� 
#define SRVAL_CITYHALL_FAIL_RESIDENTSHARE_DATE				8104		// �ǹ� ��ü �� 1���̳� ��� �Ұ� 

#define SRVAL_GENERALMEETING_SUCCESS_SUGGEST				8200		// ������ȸ�� ���������� ���� 
#define SRVAL_GENERALMEETING_FAIL_SUGGEST					8201		// ������ȸ ���� ���� 
#define SRVAL_GENERALMEETING_FAIL_SUGGEST_ALEADY			8202		// ������ȸ�� �̹� ���� ���̴� 
#define SRVAL_GENERALMEETING_FAIL_SUGGEST_NOTENOUGHSTOCK	8203		// �������� �ֽ��� �����ϴ� 
#define SRVAL_GENERALMEETING_FAIL_SUGGEST_WRONGCANDIDATE	8204		// ����� �ĺ��� ���� �߸� �Ǿ��� 
#define SRVAL_GENERALMEETING_FAIL_SUGGEST_ALREDYCANDIDATE	8205		// �̹� �ٸ������� ����� �ĺ��� ��ϵǾ� �ִ�
#define SRVAL_GENERALMEETING_FAIL_SUGGEST_CHIEFLEVEL		8206		// ����� �ĺ� ���� ���� 50

#define SRVAL_GENERALMEETING_SUCCESS_VOTE					8210		// ��ǥ ���� 
#define SRVAL_GENERALMEETING_FAIL_VOTE						8211		// ��ǥ ����
#define SRVAL_GENERALMEETING_FAIL_VOTE_ALREADY				8212		// ��ǥ ���� - �̹� ��ǥ �Ͽ���
#define SRVAL_GENERALMEETING_FAIL_VOTE_NOTVOTER				8213		// ��ǥ ���� - ��ǥ���ڰ� �ƴ�

#define SRVAL_GENERALMEETING_SUCCESS_ACCEPTCANDIDATE		8220		// ����� �ĺ��� ���ε��� ���� 
#define SRVAL_GENERALMEETING_FAIL_ACCEPTCANDIDATE			8221		// ����� �ĺ��ڷ� ������ ����� �ƴ϶� ����

//---------------------------------------------------------------------------------------------
// PVP ����
//---------------------------------------------------------------------------------------------
#define SRVAL_PVP_LEAGUE_APPLY_MESSAGE						8500		// PVP ���Ѵ��� ��û���� �޽���
#define SRVAL_PVP_LEAGUE_AGAIN_RESERVE						8501		// PVP ���Ѵ��� �ٽ� ������ �Ұ����� �����

//---------------------------------------------------------------------------------------------
//�������� 
//---------------------------------------------------------------------------------------------
#define SRVAL_FAMILY_ADD_ERROR_NO_CHAR						8600		// ���� ���� �޼���	-	�߸��� �ɸ��͸� �ڽ����� ��� �Ϸ��� �Ҷ�
#define SRVAL_FAMILY_ADD_WRONG_BEFORE_IN_FAMILY				8601		// ���� ���� �޼���	-	�̹� ������ �ֽ��ϴ�
#define SRVAL_FAMILY_ADD_WRONG_NOTCONNECT_MATE				8602		// ���� ���� �޼���	-	�θ� ��� �����ؾ� �մϴ�.
#define SRVAL_FAMILY_ADD_WRONG_No_TICKET					8603		// ���� ���� �޼���	-	Ƽ���� ����
#define SRVAL_FAMILY_ADD_WRONG_DEL_FAMILY					8604		// ���� ���� �޼���	-	// �������� ©�ȴ�.
#define SRVAL_FAMILY_ADD_WRONG_No_TICKET_PLUSDATE			8605		// ���� ���� �޼���	-	�������� �̿���� ����.
#define SRVAL_FAMILY_ADD_WRONG_DEL_HAVECHILD				8606		// ���� ���� �޼���	-	�������� Ż�� ���� - �θ��ε� ������ �ִ�.
#define SRVAL_FAMILY_ADD_FAMILY								8607		// ���� ���� �޼���	-	������ �߰� �Ͽ���./
#define SRVAL_FAMILY_GONE_FAMILY							8608		// ���� ���� �޼���	-	��������Ż�� �Ͽ���.

// ���� ���ϱ� �̺�Ʈ
//Switch_10MonthEvent_RacoonDodge
#define SRVAL_RACOONDODGEEVENT_NOTEMPTYLISTPLACE			8700		// ���ڸ��� ����
#define SRVAL_RACOONDODGEEVENT_RESERVEPERSON				8701		// �̹� ��û �Ͽ���.
#define SRVAL_RACOONDODGEEVENT_CLEAR						8702		// Ŭ���� �ϰ� ���޴� �޼���
#define SRVAL_RACOONDODGEEVENT_CANNOTRESERVE_INPLAY			8703		// �����ȿ����� ��û�Ҽ� ����
#define SRVAL_RACOONDODGEEVENT_NOTENOUGHMONEY				8704		// ����� ���� ����

// �����Ǽ�
#define SRVAL_MINISTER_FAIL_SETIZOINFO				9000	// �����Ǽ��� ���� ���� 
#define SRVAL_MINISTER_FAIL_SETHOZOINFO				9001	// ȣ���Ǽ��� ���� ���� 
#define SRVAL_MINISTER_FAIL_SETYEZOINFO				9002	// �����Ǽ��� ���� ���� 
#define SRVAL_MINISTER_FAIL_SETBYUNGZOINFO			9003	// �����Ǽ��� ���� ���� 
#define SRVAL_MINISTER_FAIL_SETHYUNGZOINFO			9004	// �����Ǽ��� ���� ���� 
#define SRVAL_MINISTER_FAIL_SETGONGZOINFO			9005	// �����Ǽ��� ���� ���� 
#define SRVAL_MINISTER_FAIL_SETGOONZUINFO			9006	// ������	  ���� ����
#define SRVAL_MINISTER_SUCCESS_GETMINISTER			9007	// ��� ��ɾ� getministerr�� �� �Ǽ����� ���� �������� ����
#define SRVAL_MINISTER_FAIL_SETHYUNGZOPRISON		9008	// �����Ǽ��� �˼� ���� ����
#define SRVAL_MINISTER_FAIL_SETMINISTER				9009	// ���� �� �Ǽ��� �Ӹ� ����
#define SRVAL_MINISTER_SUCCESS_SETMINISTER			9010	// ���� �� �Ǽ��� �Ӹ� ����
#define SRVAL_MINISTER_FIRE_MINISTER				9011	// ���� �� �Ǽ��� ���� ���� - �������� �׳� �����ڽ�
#define SRVAL_MINISTER_APPOINTMENT_SETMINISTER		9012	// ���� �� �Ǽ��� �Ӹ� ����
#define SRVAL_MINISTER_FAIL_SETMINISTER_DATE		9013	// ���ְ� �Ǽ� �Ӹ� ���ڶ����� ����
#define SRVAL_MINISTER_SUCCESS_SETLIQUIDATION		9014	// ���ְ� ���� ���� ���� ����
#define SRVAL_MINISTER_FAIL_SETLIQUIDATION			9015	// ���ְ� ���� ���� ���� ����
#define SRVAL_MINISTER_SUCCESS_SETBONUS				9016	// ���ְ� ���ʽ� Ÿ�� ���� ����
#define SRVAL_MINISTER_FAIL_SETBONUS				9017	// ���ְ� ���ʽ� Ÿ�� ���� ����
//KHY - 0629 - ���� ���� ���� �߰�.
#define SRVAL_MINISTER_FIRE_SUCCESS_SETMINISTER		9018	// ���� �� �Ǽ��� ���� ����



// �����Ǽ� �� ��� - �������
#define SRVAL_PRISON_FAIL_NAMEERROR					9020	// �̸��� �߸� �Ǿ���.
#define SRVAL_PRISON_FAIL_TIMEERROR					9021	// �ð��� �߸� �Ǿ���.
#define SRVAL_PRISON_FAIL_REASONERROR				9022	// �˸��� �߸� �Ǿ���.
#define SRVAL_PRISON_SUCCESS						9023	// ���� ������ ����

// �ڵ� ���
#define SRVAL_AUTOHUNTING_FAIL_NAMEERROR			9040	// �̸��� �߸� �Ǿ���.
#define SRVAL_AUTOHUNTING_FAIL_NOTHUNTING			9041	// �ѵ��� ����� ���� ���� ����̴�.
#define SRVAL_AUTOHUNTING_FAIL_NOSUSPICION			9042	// �ڵ���� üũ â���� ����� �ؼ� �����Ǵ�.
#define SRVAL_AUTOHUNTING_FAIL_SERVERERROR			9043	// ���� ���� - �� ������ �����̴�.
#define SRVAL_AUTOHUNTING_FAIL_ISREQUEST			9044	// �̹� �Ƿ�ó���Ǿ���.
#define SRVAL_AUTOHUNTING_SUCCESS_REQUEST			9045	// �Ƿ� ����
#define SRVAL_AUTOHUNTING_SUCCESS_PRISON			9046	// ������ ���� ����

#define SRVAL_HOZO_FAIL_SETANGELAPPLYER				9050	// ��û ����
#define SRVAL_HOZO_FAIL_SETANGEL					9051	// �Ӹ� ����
#define SRVAL_HOZO_SUCCESS_SETANGELAPPLYER			9053	// ��û ����
#define SRVAL_HOZO_SUCCESS_SETANGEL					9054	// �Ӹ� ����
#define SRVAL_HOZO_SUCCESS_SETANGELAPPLYER_FALSE	9055	// ���� ����
#define SRVAL_HOZO_SUCCESS_SETANGELADMIN_FALSE		9056	// ���� ����
#define SRVAL_HOZO_SUCCESS_SETANGEL_FALSE_SELF		9057	// Ż�� ����
#define SRVAL_HOZO_FAIL_SETANGELAPPLYER_FALSE		9058	// Ż�� ����

//�����Ǽ� ��ȣõ��
/*cyj �����Ǽ� ����
#define SRVAL_YEZO_FAIL_SETANGELAPPLYER				9050	// ��û ����
#define SRVAL_YEZO_FAIL_SETANGEL					9051	// �Ӹ� ����
#define SRVAL_YEZO_SUCCESS_SETANGELAPPLYER			9053	// ��û ����
#define SRVAL_YEZO_SUCCESS_SETANGEL					9054	// �Ӹ� ����
#define SRVAL_YEZO_SUCCESS_SETANGELAPPLYER_FALSE	9055	// ���� ����
#define SRVAL_YEZO_SUCCESS_SETANGELADMIN_FALSE		9056	// ���� ����
#define SRVAL_YEZO_SUCCESS_SETANGEL_FALSE_SELF		9057	// Ż�� ����
#define SRVAL_YEZO_FAIL_SETANGELAPPLYER_FALSE		9058	// Ż�� ����
*/

//�����Ǽ� ����
#define SRVAL_HYUNGZO_SUCCESS_SETPOLICE				9060	// �Ӹ� ����
#define SRVAL_HYUNGZO_SUCCESS_SETPOLICE_FALSE		9061	// �Ӹ� ����


// �� 
#define SRVAL_HORSEDIE								9100	// ���� �׾���.

// ItemMall
#define SRVAL_ITEMMALL_FAIL_DBFAIL					9200	// DB ����
#define SRVAL_ITEMMALL_FAIL_GETITEM_NOTINV			9201	// ������ �������� ���� - ��ø ����̳� �κ��丮 ĭ ����
#define SRVAL_ITEMMALL_FAIL_GETITEM_INFOERROR		9202	// ������ �������� ���� - ������ �����Ͱ� �ٸ�
#define SRVAL_ITEMMALL_FAIL_CONTINUERENEWAL			9203	// 1�� �ȿ� �Ȱ��� ��Ŷ�� �� �޴´�
#define SRVAL_ITEMMALL_FAIL_CHADEAD					9204	// ����ÿ��� �ȵȴ�.
#define SRVAL_ITEMMALL_FAIL_GETITEM_NOITEM			9205	// ������ ������ �ùٸ��� �ʴ�.
#define SRVAL_ITEMMALL_FAIL_CANNOT_SERVER			9206	// ���� �� ���� �����̴�
#define SRVAL_ITEMMALL_FAIL_NOADDITEM				9207	// ���̻� ���� ������ �������̴�
#define SRVAL_ITEMMALL_FAIL_BADREQUEST				9208	// 1�ʿ� 5ȸ �̻��� ��û�� ������ ����. ���̻� �����۸� ���� �޽����� �ȹ޴´�.
#define SRVAL_ITEMMALL_FAIL_EQUIPUNABLE				9209	// �����Ҽ� ���� ���� �������� �������� ����.
#define SRVAL_ITEMMALL_FAIL_ONLYGROWNUP				9210	// ��ü �̿밡 ���������� ������ �� ���� ������ �Դϴ�. 18�� �̻� �������� �������ּ���.
#define SRVAL_ITEMMALL_FAIL_LIMIT_LEVEL				9211	// ������ ������ ���� ������ ������ �ȵǼ� ������.

// �̺�Ʈ���� 
#define SRVAL_EVENTCHAR								10000	
#define SRVAL_EVENT									10020	

// ȯ�� ����
#define SRVAL_WHISPERCHAT_REJECT					11000
#define SRVAL_PRIVATETRADE_REJECT					11001
#define SRVAL_PARTYINVITE_REJECT					11002
#define SRVAL_FRIENDADD_REJECT						11003

#define SRVAL_LOTTOFAIL								11100	// ��ι� ���� 

#define SRVAL_LEVELUPFAIL_NOCLEARQUEST				11200	// ����Ʈ �Ϸ����� �ʾ� ������ ����. 

// ��� ��� 
#define SRVAL_INVALIDGMORDER						12000	// ��� ��� ���� - �ش� ��ɾ� ����.

#define SRVAL_GAMEMASTER_SUCCESS					12001	// ��� ��ɾ� ����
#define SRVAL_GAMEMASTER_FAILED						12002	// ��� ��ɾ� ����
#define SRVAL_GAMEMASTER_VILLAGEWAR					12003	// ������ ���� ����
#define SRVAL_GAMEMASTER_GOONZUDAY					12004	// ���ֵ��� ���� ����
#define SRVAL_GAMEMASTER_MAKETIMEREDUCE				12005	// ���� �ð� ���� ��ɾ� ����
#define SRVAL_GAMEMASTER_QUESTCOUNT					12006	// ����Ʈ ī��Ʈ �� ����
#define SRVAL_GAMEMASTER_FOURLEAF					12007	// ����Ŭ�ι� ���� ��
#define SRVAL_GAMEMASTER_VOTECAMPAGIN				12008	// �������� ���� ����
#define SRVAL_GAMEMASTER_EVENTENABLE				12009	// �̺�Ʈ ���� ����
#define SRVAL_GAMEMASTER_POSTOFFICE_NOPERSON		12010	// ��ü�� ������ ���� - ĳ���� ����
#define SRVAL_GAMEMASTER_POSTOFFICE_NOTENOUGHBOX	12011	// ��ü�� ������ ���� - ������ ����
#define SRVAL_GAMEMASTER_POSTOFFICE_SYSTEMERROR		12012	// ��ü�� ������ ���� - �ý��� ����
#define SRVAL_GAMEMASTER_SYSTEM_PACKET_ENABLE		12013	// ��Ŷ ���� ������ ���� ����
#define SRVAL_GAMEMASTER_SETMUTETIME				12014	// ä�� �� ������ ���� ����
#define SRVAL_GAMEMASTER_SETMUTETIME_CHAR			12015	// ä�� �� ������ ���� ����
#define SRVAL_GAMEMASTER_GACHALOCK					12016	// ��í Lock ���� �� ���� ���� 
#define SRVAL_GAMEMASTER_GACHA_NOT_LOCK_CHANGE_UNIQUE	12017	// ��í �� lock�� �ȵȻ��¿��� ����ũ�� ���� �Ϸ� �ߴ�.

// ��� ��� - �ý��۸��
#define SRVAL_GAMEMASTER_BLOCK_PACKET				12900	// ���ѵ� ��Ŷ��

// DB SYSTEM INFO
#define SRVAL_DBSYSTEMINFO							13000	// DB�� ������ ��û 

// ���� ���� ���� 
#define SRVAL_CANUSEMAGIC_FAIL						14000	// ���� ������ 


// ��ȯ��  
#define SRVAL_SUMMONDIE									16000	// ��ȯ���� �׾���.
#define SRVAL_SUMMONHATCHFAIL							16001	// ��ȯ�� ������ ����Ͽ� ��ȯ���� ��ȯ�ϴµ� ���� 
#define SRVAL_SUMMON_FREE_FAIL_HAVEITEM					16002	// ��ȯ���� �����ϰ� �־ Ǯ���ֱ� �Ұ�
#define SRVAL_SUMMON_FAIL_TAKEOUTDELAY					16003	// �����̶����� ��ȯ�� ��ȯ�Ұ�
#define SRVAL_SUMMON_WASTEALLSTAMINA					16004	// ���׹̳� ��� ��ȯ�� ȸ��
#define SRVAL_SUMMONSUCCESS								16005	// ��ȯ�� ��ȯ ����
#define SRVAL_SUMMON_FREE_FAIL_STONNUMINCORRECT			16006	// ��ȯ�� ���� �������� ���� ��������.
#define SRVAL_SUMMON_FREE_FAIL_STONNUMNOTENOUGHSTON		16007	// ��ȯ�� ���� �������� ������� �ʴ�.
#define SRVAL_SUMMONSUCCESS_USESTON						16008	// ��ȯ�� ���� �������� ������� �ʴ�.
#define SRVAL_SUMMON_FREE_FAIL_CANNOTOVERUSESTON		16009	// ��ȯ�� �������� ������뼮�� ����Ҽ� ����.
#define SRVAL_SUMMONSUCCESS_CHARGESTAMINA				16010	// ��ȯ�� ���¹̳� ���� �������� �̿��ؼ� ���� ����
#define SRVAL_SUMMON_NEEDCHARGESTAMINA					16011	// ��ȯ�� ���¹̳� ������ �ʿ��ϴ�.
#define SRVAL_SUMMON_STATUSINIT_FAIL_HAVEITEM			16012	// ��ȯ���� ��� �����ؼ� �����ʱ�ȭ �Ұ���
#define SRVAL_SUMMON_FAIL_OVERSLOT						16013	// ��ȯ�� ������ 8���� ��� ��ã��.
#define SRVAL_SUMMON_FAIL_OVERDATE						16014	// ��ȯ�� ���� ���Ⱓ�� �������ϴ�
#define SRVAL_SUMMON_FAIL_LOTSOFDATE					16015	// ��ȯ�� ������ ���� ���� �ֽ��ϴ�.
#define SRVAL_SUMMON_FAIL_CANNOTSLOTOUTDEAD				16016	// ���� ��ȯ���� ������ �� ����.
#define SRVAL_SUMMON_ADD_MUDANGPRESENT					16017	// �������� ������ �޾Ҵ�.
#define SRVAL_SUMMON_SUCCES_USESTRAGERICKET				16018	// ��ȯ�� Ƽ���� ��� �Ͽ����ϴ�.
#define SRVAL_SUMMON_DONOTHAVE_PROJECTILE				16019	// ��ȯ�� �߻�ü �������� ����

// ���λ��� 
#define SRVAL_PERSONALSHOP								17000	// ���λ���
#define SRVAL_FAIL_PERSONALSHOP_USEITEM					17001	// ���λ����� �����ְ� ���� ������ �÷��� �������� ������ ��� �� �Ѵ�
#define SRVAL_FAIL_PERSONALSHOP_MOVEITEM				17002	// ���λ����߿��� �������� �������� �ű� �� ����( �Ȱ� �ִ� �����۸�)

// �������� ��ƿ ��� 
#define SRVAL_BADSTEALACTION							18000
#define SRVAL_BADSTEALACTIONPUNISH						18010	// �������� ��ƿ�� ó�� 

// ����. 
#define SRVAL_NOPROPERFISHAREA							18500	// �����ϱ� �������� ���. 
#define SRVAL_FISHRUNNINGAWAY							18501	// ����� ��������.
#define SRVAL_FISHSKILLNOTENOUGH						18502	// �� ����� ���µ�, ����� ����
#define SRVAL_FISHTOOLNOTEXIST							18503	// ����� ���µ�, �ʿ��� ������ ����
#define SRVAL_FISHTOOLNOTENOUGHDURABILITY				18504	// ������ ������ ����
#define SRVAL_FISHNOTBAITITEM							18505	// �̳��� ����� �� ���� ������ ( ���깰 �߿��� �׷��� �̳��� ����� �� ���°� ��������... )
#define	SRVAL_FISHNOTBAITSHRIMP							18506	// �ι������������� ���츦 ���� ������ �޽���
#define SRVAL_FISHNOTBAITLUGWORM						18507	// �ؾ糬���������� �������̸� ���� ������ �޽���

// ���
#define SRVAL_FARM_FAIL									18510	// ��� ����. 
#define SRVAL_FARM_LANDSTRUCTURE_NOT_EXIST				18511	// �ǹ��� ��� ��� �Ұ�

// ä��
#define SRVAL_MINE_FAIL									18520	// ä�� ����. 
#define SRVAL_MINE_MINESTRUCTURE_NOT_EXIST				18521	// �ǹ��� ��� ä�� �Ұ�

// �κ��丮 
#define SRVAL_ADDINV_FAIL_FULL							19000	// �κ��� ���ڸ��� ��� �߰� �Ұ�. 

// ���� �ŷ� 
#define SRVAL_MARKET_SELL_FAIL							20000	// ���ֿ��� ���ǻ�� ����. 
#define SRVAL_NEWMARKET_BUY_FAIL						20001	// ���ո��Ͽ��� ���ǻ�� ����

// ���� ����
#define SRVAL_TRADEMERCHANT_MONEY_INSUFFICIENTY			21000	// �� �������� ���� ���� ���� ���� �ȵ�
#define SRVAL_TRADEMERCHANT_NOT_BUY_TIME				21001	// ���� �� �ƴ�
#define SRVAL_TRADEMERCHANT_PREPARE						21002	// �غ���

#define SRVAL_FOREIGNMERCHANT_NOTBUYCASHITEM_SBS		21005	// SBS ȸ���� ĳ�������� �Ǹ� ����
#define SRVAL_FOREIGNMERCHANT_NOTBUYCASHITEM_PRICE		21006	// 60000 �� �̻� �Ǹ� ����


// ĳ��. 
#define SRVAL_GIVECASH									21100	// �������� ����. 

// �⼮ 
#define SRVAL_ATTENDANCE								21200	// �⼮ ��Ȳ 

#define SRVAL_CANNOTDROPITEM							21250	// ����Ҽ� ���� ������ ����ҷ��� ���

#define SRVAL_CANNOTMOVEITEM_PERSONALSHOP				21251	// ���λ��� �������̶� ����Ҽ� ����.
#define SRVAL_CANNOTSEALINGUP_PERSONALSHOP				21252	// ���λ��� �������̶� �к����� �� �� ����.

//KHY - 0530 ���� ���� ��������.
#define SRVAL_CANNOTBUYITEM_FOREIGNMERCHANT				21253	// ������ �Ⱓ�� �������� �ݾ��� �Ѿ� ���̻� ������ �� ����.

#define SRVAL_BUYLIMITMONEYSET_FOREIGNMERCHANT			21254	// �������� �ݾ��� �缳���Ѵ�.
#define SRVAL_BUYLIMITMONEYVIEW_FOREIGNMERCHANT			21255	//���� �������� �ݾ��� �����ش�.


#define SRVAL_NO_BATTLEQUIT								22001	// �����߿��� �� ������.
#define SRVAL_NO_DIEQUIT								22002	// �׾����� �� ������.

#define SRVAL_FAIL_DIS_WORLDMONEY						22010	// ���� ����
#define SRVAL_FAIL_WORLDMONEY_SELLORDER					22013	// �ȱ� ��� ����
#define SRVAL_FAIL_WORLDMONEY_BUYORDER					22015	// ��� ����
#define SRVAL_FAIL_WORLDMONEY_BUYORDER_MYSELF			22016	// ��� ���� - �ڱ��ڽ��� �ֹ�
#define SRVAL_FAIL_WORLDMONEY_BUYORDER_NOMONEY			22103	// ��� ���� - �� ����
#define SRVAL_SUCCESS_WORLDMONEY_SETPRICE				22104	// ��ť �ü� ����
#define SRVAL_FAIL_WORLDMONEY_SET_CHAR					22105	// ��ť �ֱ� ����
#define SRVAL_SUCCESS_WORLDMONEY_SET_CHAR				22106	// ��ť �ֱ� ����

#define SRVAL_NPC_MARKET_SELL_FAIL						22100   // NPC���� ���� ��� ����

// ��Ƽ
#define SRVAL_PARTYINVITE_FULLPARTY						22300	// ��Ƽ���� �����ϼ� ��Ƽ ���� ����
#define SRVAL_PARTYINVITE_NOTLEADER						22301	// ���� ��Ƽ���� �ƴϾ ��Ƽ �ʴ� ����
#define SRVAL_PARTYINVITE_ALREADYPARTY					22302	// ������ �̹� ��Ƽ���̶� �ʴ����
#define SRVAL_PARTYINVITE_NOTFINDNAME					22303	// /p �����̸�  ���� ������ �̸��� ����
#define SRVAL_PARTYINVITE_LEADERALREADYPARTY			22304	// ���� �ʴ��ߴ� ������ �ٸ� ��Ƽ�� ��Ƽ���̴�.

#define SRVAL_NOTRADE_ITEM								22400	// �ŷ��Ұ�������

// ����
#define SRVAL_CAN_NOT_USE_ITEM_IN_PRISON				22500	// �����̶� �����ۻ�� �Ҽ� ���� �� �޽���
#define SRVAL_CAN_NOT_CHAT_IN_PRISON					22501	// �����̶� ä�� �Ҽ� ���� �� �޽���
#define SRVAL_CAN_NOT_WARP_IN_PRISON					22502	// �����̶� ���� �Ҽ� ���� �� �޽���
#define SRVAL_CAN_NOT_MAKEITEM_IN_PRISON				22503	// �����̶� ������ ����� ���� �� �޽���
#define SRVAL_CAN_NOT_ENCHANTITEM_IN_PRISON				22504	// �����̶� ������ ��æƮ �� �� ���� �� �޽���

//������
#define SRVAL_CAN_NOT_WARP_IN_VILLAGEWAR				22600	//  ������ �̶� ���� �� �� ���� �� �޽���

// �������� ��ȯ��
#define SRVAL_SUMMONEGG_USED							22700	// [%s]���� [%s]�� ��ȯ�Ͽ����ϴ�.

// �Ƿι��� ���� ��� �˸�
#define	SRVAL_TIRED_SYSTEM_CHAR							23000	// �Ƿι��� ������ ĳ�����Դϴ�.

// ��ũ�� �������� ���콺���� �м�
#define	SRVAL_RECORD_MOUSEACTION_START					24000	// ���콺 ������ ���� ���� 

//����
#define SRVAL_GACHA_FAIL_FULLINVEN						25000	// �κ��� �������� ������ ���Ѵ�.
#define SRVAL_GACHA_FAIL_KEYNEED						25001	// �κ��� �������� ������ ���Ѵ�.
#define SRVAL_GACHA_FAIL_LOCK							25002	// ������ ��ڰ� ������� ���ϵ��� �ߴ�.
#define SRVAL_GACHA_NOTCORRECT_ITEM						25003	// ���� �ְ� �������� �ٸ���

//KHY - 1220 - ���Žý���.
#define SRVAL_FAIL_ALEADYTRANSFROMCHR 					25101 // �̹� ���� ĳ���Ͱ� ��ϵǾ� ��� ����. 
#define SRVAL_FAIL_NOTRANSFROMITEM 						25102 // ���ſ� �ʿ��� �������� ���� ����. 

//[�߰� : Ȳ���� 2008. 1. 11 => �δ� �޽��� �߰�.]
#define SRVAL_FAIL_INSTANTDUNGEON_NO_TICKET				25103	// �����ϴµ� Ƽ���� ����.
#define SRVAL_FAIL_INSTANTDUNGEON_NO_GUILD 				25104	// �츮 ��尡 ��� ���� �Ұ�.
#define SRVAL_FAIL_INSTANTDUNGEON_OVER_COUNT_GUILD		25105	// �츮 ��尡 �� �����ؼ� ���� �Ұ�.
#define SRVAL_FAIL_INSTANTDUNGEON_MY_NO_GUILD			25106	// ���� ��尡 ��� ���� �Ұ�.
#define SRVAL_SUCCESS_INSTANTDUNGEON_SET_BESTGUILD		25107	// ����Ʈ ��带 �����Ѵ�.

//[�߰� : Ȳ���� 2008. 1. 22 => ���Ǳ��� ���� �޽��� �߰�.]
#define SRVAL_BLACKWAR_CHAR_REWARD						25108	// ���Ǳ��� ���� ����.
#define SRVAL_BLACKWAR_VILLAGE_REWARD					25109	// ���Ǳ��� ���� ����.

//[�߰� : Ȳ���� 2008. 2. 4 => ���� ����. ]
#define SRVAL_SPACE_BOX_INVEN_FULL						25110	// �κ��� �������� ������ �̵��� �Ҽ� ���ٸ�.
#define SRVAL_SPACE_BOX_TIME_OVER						25111	// ���ڰ� ��� �Ⱓ�� ����Ǽ� ��� �Ұ���.

//[�߰� : Ȳ���� 2008. 2. 20 => ������ȸ �ߵ� ���� �Ұ��� ������ ���̶�� �޽���. ]
#define SRVAL_GENERAL_MEETING_SUGGEST_ON_OFF_INFO		25112	
#define SRVAL_GENERAL_MEETING_SUGGEST_OFF_FAIL			25113	//[�߰� : Ȳ���� 2008. 2. 20 => ������ȸ �ߵ��� �Ұ����Ͽ� ������ �޽��� . ]

// [����] CRC üũ ����
#define SRVAL_FAIL_FILECRCCHECK							26000	// CRC üũ��� �߸��� ����

#define SRVAL_FAIL_INSTANTDUNGEON_NO_PARTY				26010	// [����] ������ : ��Ƽ�� ���� ���� �δ��� ���� �Ұ�
#define SRVAL_FAIL_INSTANTDUNGEON_OVER_PARTY_MAP		26011	// [����] ������ : �ִ� ���� ��Ƽ ���� �ʰ��� �δ��� ���� �Ұ�
#define SRVAL_INSTANTDUNGEON_CLEAR_REWARD_ITEM			26012	// [����] ������ : �������� Ŭ�����ؼ� �������� �޴´�

#define SRVAL_CHANGE_ITEM_FROM_NPC						26017	// ���ݼ���� ������ �ɷ�ġ ���� �Ϸ�

#define SRVAL_REWARDITEM_FOR_PCROOM						26020	// [����] PC�� : PC���̶� �������� �����Ѵٴ� �޽���


#define SRVAL_NOTICE_SEASON2_ATTEND						26030	// [����] �⼮üũ : �⼮üũ �̺�Ʈ �˸�
#define SRVAL_FAIL_SEASON2_ATTEND_REWARDITEM			26031	// [����] �⼮üũ : ��������� ���� ����
#define SRVAL_SUCCESS_SEASON2_ATTEND_REWARDITEM			26032	// [����] �⼮üũ : ��������� ���� ����

#define SRVAL_FAIL_WARPTO_NOTMARKETOPEN_MAP				26033	// [����] �ش� ���������� ������ �� �� ����

#define	SRVAL_NOTICE_WARPTOPOLL_MAP						26034	// [����] ���� ��ǥ�� �������� �̵��Ұ����� �����

#define SRVAL_FAIL_REASON_ALREADYVOTE					26035	// [����] �̹� ��ǥ�� �����ƴ�
#define SRVAL_FAIL_REASON_DONOTARRIVELEVLE				26036	// [����] ��ǥ�� �� �ִ� ������ �������� ���ߴ�
#define SRVAL_FAIL_DONOTBUY_ELECTIONSTUMPITEM			26037	// [����] ��ǥ�Ⱓ�� �ƴ϶� ����츦 ���� ���Ѵ�

#define SRVAL_FAIL_SEASON2_ATTEND_NOTGIVEITEM			26038	// [����] �⼮üũ : ������ �������� �⼮ ������ ����������

#define	SRVAL_NOTICE_OPENTHE_SERVEREVENTGATE			26039	// [����] �����̺�Ʈ �δ� ����Ʈ�� ���ȴ�
#define	SRVAL_NOTICE_CLOSETHE_SERVEREVENTGATE			26040	// [����] �����̺�Ʈ �δ� ����Ʈ�� ������

// ��ȥ����
#define SRVAL_FAIL_PROPOSE_IS_NOT_VALIDCHAR				27000	// [����] ûȥ�� ĳ���Ͱ� �������� �ʰų� �������� �ƴ�
#define SRVAL_FAIL_PROPOSE_ALREADY_MARRIED				27001	// [����] ûȥ�� ĳ���Ͱ� �̹� ��ȥ�ߴ�
#define SRVAL_FAIL_PROPOSE_LESSTHAN_MARRY_LEVEL			27002	// [����] ûȥ�� ĳ���Ͱ� ��ȥ ���ɷ����� �ƴϴ�
#define SRVAL_FAIL_PROPOSE_SAME_SEX						27003	// [����] ûȥ�� ĳ���Ϳ� ������ �����ϴ�
#define SRVAL_FAIL_PROPOSE_ANSWER_NO					27004	// [����] ûȥ�� ĳ���Ͱ� ûȥ�� �����ߴ�
#define SRVAL_SET_MARRY_WITHSAMEMAP						27005	// [����] �� ����ڰ� �����ʻ� �����ߴ��� ���θ� �����Ѵ�
#define SRVAL_REQUEST_WEDDING_ITEMGET					27006	// [����] ��ȥ ����� �������� ������� ��û�Ѵ�
#define SRVAL_WEDDING_MATE1_QUESTION					27007	// [����]
#define SRVAL_WEDDING_MATE2_QUESTION					27008	// [����]
#define SRVAL_WEDDING_GIVEITEM_QUESTION					27009	// [����]
#define SRVAL_WEDDING_GIVEITEM							27010	// [����] ��ȥ�� ȭ�� �������� �޾Ҵ�
#define SRVAL_WEDDING_HALL_OUT_NOTICE					27011	// [����] ��ȥ�� ���ΰ��� ������

// �޸� ���� �ý���
#define SRVAL_REWARDITEM_FOR_DORMANCYEQUIPBOX			27200	// [����] �޸� �������� ��� ���� ���� �ȳ�
#define SRVAL_FAIL_BUY_DORMANCYITEM						27201	// [����] �޸� ���� ����Ʈ ������ ���� ����
#define SRVAL_FAIL_IS_FULLIVEN							27202	// [����] �κ��丮�� ������ ������ ���� ����
#define SRVAL_FAIL_MOVE_ITEM_INHOUSE					27203	// [����] �޸� ��� �������� â�� �̵� ����
#define SRVAL_FAIL_NOT_ENOUGH_POINT						27204	// [����] �޸� ����Ʈ�� ���ڸ�

// ��Ʋ�ξ�
#define SRVAL_BATTLEROYAL_NOTOPEND						27300	// [����] ������� ������ ����
#define SRVAL_BATTLEROYAL_NOTREJOIN						27301	// [����] �� ��� ���� �� ���� ��⿡ ���� �Ұ�
#define SRVAL_BATTLEROYAL_NOTREADYFORMAKING				27302	// [����] ���� �߿��� ���� �Ұ�
#define SRVAL_BATTLEROYAL_NOTREADYFORSUMMON				27303	// [����] ��ȯ�� ��ȯ�߿� ���� �Ұ�
#define SRVAL_BATTLEROYAL_NOTREADYFORFULLEDGAMER		27304	// [����] �����ڰ� ���� ��� ���� �Ұ�
#define SRVAL_BATTLEROYAL_NOTPROPERLEVEL				27305	// [����] ������ ���� �ʴٸ� ���� �Ұ�
#define SRVAL_BATTLEROYAL_JOINPARTY						27306	// [����] ��Ƽ ���̶�� ���� �Ұ�

//--------------------------------------------
//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����
//--------------------------------------------
#define SRVAL_SUCCES_SET_GOONZURACCOONEVENT				28000	// [����] ������ �ð��� ���̾�Ʈ ���� �̺�Ʈ�� ���� �Ǿ����ϴ�
#define SRVAL_FAIL_EVENTSET_SAMETIME					28001	// [����] ���� �ð��뿡�� ���̾�Ʈ ���� �̺�Ʈ ������ �Ұ����մϴ� 
#define SRVAL_FAIL_EVENTSET_NOT_ENOUGH_TIME				28002	// [����] ��� ������ �Ϸ���� �ʾҽ��ϴ�.
#define SRVAL_FAIL_EVENTSET_NOT_OVER_LIMITTIME			28003	// [����] ���̾�Ʈ ���� �̺�Ʈ ������ ���� ���� �� 24�ð��� ������ ���� �մϴ�.

//--------------------------------------------
//[����] �������� �̵� 
//--------------------------------------------
#define SRVAL_FAIL_GORACCOONWORLD_UNDER_18				29000	// [����] 18�� ���ϴ� �������� �̵� �Ұ���
#define SRVAL_FAIL_GORACCOONWORLD_WARP					29001	// [����] �ش��������δ� ���� �Ҽ� �����ϴ� 

#define SRVAL_NOTICE_CLOSE_PERSONALSHOP_BY_WARP			29002	// [����] ���λ��� ������������ �����ؼ� ������ �����

//TradeServer
#define SRVAL_FAIL_TRADESERVER_NOMORE_SELL				30000	// �� �̻� �ֹ��� �� �ø���.
#define SRVAL_FAIL_TRADESERVER_SESSION					30001	// ���� ������ ������ ������ �ִ�.
#define SRVAL_FAIL_TRADESERVER_GM						30002	// ��� ��ɾ�� ���ϰ� �Ǿ� �ִ�.
#define SRVAL_FAIL_TRADESERVER_LIMITTIME				30003	// ���� �� �� �ִ� �ð��� �ƴϴ�.
#define SRVAL_FAIL_TRADESERVER_NOT_BUY					30004	// �� �� �ִ� ������ �ƴϴ�. - �̹� �ȷȰų� �ߴ�.
#define SRAVL_SUCCESS_TRADESERVER_SETTIME				30005	// ��� ��ɾ�� ���� �ð��� �����ߴ�.
#define SRVAL_SUCCESS_SET_TRADESERVER					30006	// ��� ��ɾ�� ���� ����� ���� �Ǵ� �������״�.

#define SRVAL_FAIL_TRADESERVER_CANCEL_NOT				30007	// ���� ȸ�������� �̹� �ȷ��� ������ ����
#define SRVAL_FAIL_TRADESERVER_CANCEL_ERROR				30008	// ���� ȸ�������� �� �� ���� ������ ȸ�� �����ߴ�.
#define SRVAL_FAIL_TRADESERVER_BUY_FULLINV				30009	// ��� ������ �κ��� �� á��

#define SRVAL_NOTICE_TRADESERVER_STATE					30010	// [����] ���� ���� ������ ���¸� �˷��ش�

#define	SRVAL_FAIL_WORLDPASSPORT_OVERLAPPING			30011	// [����] �����̸��� �ߺ��̶� ���ǹ߱� ����

#define	SRVAL_NOTICE_EVENT_TOGGLE_SWITCH				30012	// [����] �̺�Ʈ ���� ����ġ On/Off����

#define	SRVAL_NOTICE_LEVELUP_REWARD						30013	// [����] ���� ������ �������� ����

//[����] ��Ƽ��Ʈ. ���� ���� ������ �������� �����ϴ� �޽���.
#define SRVAL_FAIL_ARTIFACT								30015
#define SRVAL_FAIL_ARTIFACT_REMOVE_GETITEM_NOTINV		30016

//[����] ��ƼȦ. ���� ���� ������ �������� �����ϴ� �޽���.
#define SRVAL_FAIL_PARTYHALL							30017

//[����] ���� �̺�Ʈ - ���� ����. ���� �޽���. => 2008-3-27
#define SRVAL_MONSTER_ATTACK_EVENT						30018

//[����] �ŵ������� �ֽļ��� �ʰ��ؼ� Ŭ�󿡼� ���� �޽���. => 2008-3-27
#define SRVAL_OVER_STOCK_ORDER							30019

//[����] ���λ��� ��� ���� ���� �޽���. => 2008-3-27
#define SRVAL_PERSONAL_SHOP_MODE_CHANGE_FAIL			30020

//[����] ���� �̺�Ʈ ���������� 1�� �˸�. => 2008-6-24
#define SRVAL_SERVER_EVENT_RANK_1						30021
#define SRVAL_SERVER_EVENT_END							30022
#define SRVAL_SERVER_EVENT_BUF							30023

//[����] �̰� ���� ������ ���� �޽��� ���
#define SRVAL_ITEMUSE_REWARDBONUS						30024

//[����] ��ģ ���� ����Ʈ�� �̹� �ο� �ƴٸ� ����Ʈ�� ���� ���Ѵٴ� ���� ǥ��. => 2008-7-10
#define SRVAL_NAMINGQUEST_START_FAIL					30025
// ��Ī ����Ʈ�� ����Ʈ�� ���������� �ο� �Ǿ��ٴ� ���� ǥ��
#define SRVAL_NAMINGQUEST_START_SUCCESS					30026

// Recommand  ��õ
#define SRVAL_FAIL_RECOMMANDPERSON						30100	// ���� �˻� ����
#define SRVAL_FAIL_RECOMMANDPERSON_CANCEL				30101	// ��õ ���
#define SRVAL_GIVEITEM_RECOMMANDER						30102	// ��õ�� �ѻ���� �������� �޴´�
#define SRVAL_GIVEITEM_RECOMMAND						30103	// ��õ�� ���ѻ���� �������� �޴´�
// �δ� �޽���
#define SRVAL_INSTANTDUNGEON_MAKEGATE					30110	// �ν��Ͻ� �������� ����Ʈ�� ������.

#define SRVAL_GIANTRACCOONRESURRECTEVENT_GIVE_ITEM		30111	// ���̾�Ʈ ���� ��Ȱ �̺�Ʈ���� ������Ͽ� ��� �������� ������

//KHY - 1211 - ���ݻ�ǰ - ���� ����
#define SRVAL_RETURN_USE_ALLPURPOSETOOL					30200	// ���� ������ ��� �Ͽ���.


#define SRVAL_RETURN_NOT_USE_FOURLEAF					30201	//[����] ����ũ�ι��� ���� ����Ҽ� ���� �Ÿ� ������ ���Ѵ�. => 2008-8-14
#define SRVAL_EVENTDAY_OVER_NOT_MAKE_ITEM				30202	//[����] �̺�Ʈ �ð��� ������ �������� ���� �� ����. => 2008-9-8

#define SRVAL_GIVE_MENTOR_BUF							30203	//[����] ���°� ���� ������ �شٰ� �޽��� ������. => 2008-10-9
#define SRVAL_VILLAGE_RESIDENT_INVITE					30204	//[����] ������ ������ �ʴ� ���� �� �޽���. => 2008-10-9
#define SRVAL_VILLAGE_RESIDENT_RESULT					30205	//[����] �ֹ� ���� ��û ���.

#define SRVAL_VILLAGE_HELPER							30206	//[����] ����� ���� �޽���. => 2008-11-10
#define SRVAL_DIVINATION_MSG							30207	//[����] � ���� �޽���.

#define SRVAL_ELIXIR_CHARGE_ITEM_NUM_ZERO_FAIL			30208	//[����] ������ NPC�� ��ȭ���ַ��� �������� ������ ��� ������ 0�� �϶� ����

#define SRVAL_PROMOTER_NOT_CELLULAR_PHONE_AUTH			30209	//[����] �߱� �ڵ��� ���� ���ؼ� �������� �� ��.

#define SRVAL_NEWMARKET_REPAIR_FAIL						30210	//[����] ���ո��� ���� ����

#define SRVAL_TRANSFORM_SYNCRO_UP						30211	//[����] ���� ��ũ�� ������ ���� �޽���.

#define SRVAL_PROMOTER_CHAR_LEVELUP_MINI_BUTTON			30212	//[����] �߱������� ĳ���Ͱ� �������ϸ� ���θ��� ����â�� ����Ǵ� ���� ��ư�� �����ش�.


#define SRVAL_RECOMMEND_GIVE_ITEM_SUCCEED					30213	//[����] ��õ���� ���������� ������ ȹ��.
#define SRVAL_RECOMMENDEE_GIVE_ITEM_SUCCEED					30214	//[����] ����õ�ο��� ��õ���� ������ ȹ�� ���� �˸�.
#define SRVAL_RECOMMEND_GIVE_ITEM_FAIL						30215	//[����] ��õ���� ���������� ������ ȹ��.
#define SRVAL_RECOMMENDEE_GIVE_ITEM_FAIL					30216	//[����] ����õ�ο��� ��õ���� ������ ȹ�� ���� �˸�.
#define SRVAL_RECOMMEND_GIVE_ITEM_SUCCEED_NO_AUTH			30217	//[����] ��õ���� ���������� ������ ȹ��. �����ȵȰ�.
#define SRVAL_RECOMMENDEE_GIVE_ITEM_SUCCEED_NO_AUTH			30218	//[����] ����õ�ο��� ��õ���� ������ ȹ�� ���� �˸�. �����ȵȰ�.

#define SRVAL_REPAIR_REQUEST_FAIL							30219	//[����] �����Ƿ� �̿���� �����ϴ�.

#define SRVAL_GIANTRACCOONRESURRECTEVENT_NO_TIME			30220	//[����] ���̾�Ʈ ���� �̺�Ʈ �ð��� �ƴϾ �Ұ���.
#define SRVAL_GIANTRACCOONRESURRECTEVENT_ALREAY_MAKE_NPC	30221	//[����] ���̾�Ʈ ���� �̺�Ʈ �̹� �ٸ� �������� �ǹ� ��ġ�� �Ϸ���.
#define SRVAL_GIANTRACCOONRESURRECTEVENT_EVENT_START		30222	//[����] ���̾�Ʈ ���� �̺�Ʈ �ð��� �Ǿ� ������ �˸�.
#define SRVAL_GIANTRACCOONRESURRECTEVENT_FAIL_USE_ITEM		30223	//[����] ���̾�Ʈ ���� �̺�Ʈ�� ȹ���ϴ� ���̾�Ʈ ���� ��Ʈ �Դ� ����.


#define SRVAL_VALENITNEDAY_ALREADY_BUF						30224   //[����] ������ ���ݸ����� ����Ͽ� ������ ȹ���ϰ��� �ϳ� �̹� ������ �������� �˸�.
#define SRVAL_VALENITNEDAY_NOT_MYSELF						30225   //[����] ������ ���ݸ����� ����Ͽ� ������ ȹ���ϰ��� �ϳ� �̹� ������ �������� �˸�.
#define SRVAL_VALENITNEDAY_NOT_USER							30226   //[����] ������ ���ݸ����� ����Ͽ� ������ ȹ���ϰ��� �ϳ� �̹� ������ �������� �˸�.


// ��� - SJY
#define SRVAL_FAIL_CONFIRMCREATEGUILD_NOMONEY				31000	// ������ �������� ��� �㰡�� �����ؼ� ��尡 ��������
#define SRVAL_FAIL_ALEADYRECEIVE_BEGINNERWEAPON				32000	// �̹� �ʺ��� ���⸦ �޾Ҵ�!
#define SRVAL_FAIL_MANUFATURENPC_NOMONEY					32001	// ������ �������� NPC�� ���� ���� �Ұ���
#define SRVAL_FAIL_GIVEITEM_NOINVEN							32002	// �κ��� ������ �������� �����Ҽ� ����(GM)
#define SRVAL_RETURN_USERCOUNT								32003	// �ش� ���� ���� ����

#define SRVAL_RETURN_BEFORE_REG_MAPWAR						32004	// �̹� ������� ��û �ߴ�.
#define SRVAL_RETURN_REG_CANTSTATUSGUILD					32005	// ��巾 4�̻� �ο��� 5�̻��� �ȵȴ�- ����� ���� ���°� �ƴϴ�.
#define SRVAL_RETURN_NOTMASTER								32006	// ��� �����Ͱ� �ƴմϴ�.
#define SRVAL_RETURN_NOT_RED_HUTMAP							32007	// ������ ��û ���� �ʾҴ�.
#define SRVAL_RETURN_NOT_REG_TIME							32008	// ������� ��û�Ҽ� ���� �ð��̴�.
#define SRVAL_RETURN_CANNOTGUILDWAR_NOGUILD					32009	// ��Ī�� ��尡 ����. ����� ���� �Ұ��� 
#define SRVAL_RETURN_CANNOTGUILDWAR_RESEASON				32010	// ������� �ʱ�ȭ �Ǿ��� ���Ӱ� ����ض�.

// �Ҿ���� ���� ����Ʈ
#define SRVAL_RETURN_LOSTWORLDQUEST_COMPLETE				32011	// �Ҿ���� ���� ����Ʈ - ��Ƽ��� ���� ��ġ�� ���� �Ϸ�

// ��ȣ���� Ư���ɷ� : ��ȣ������ Ư�� �ɷ����� ������ �߻� �Ѵ�
#define SRVAL_RETURN_SOULGUARD_SHOT_MAGIC					32012

// ���� �̺�Ʈ ���� �޼��� ���� �޾����� �˷� �ش� 
#define SRVAL_RETURN_RACOONDODGEEVENT_CLEAR					32013

#define SRVAL_RETURN_GAWIBAWIBO_SRPWIN						32014	// [��ȣ_GAWIBAWIBO] ���� ���
#define SRVAL_RETURN_GAWIBAWIBO_SRPLIMIT					32015	// [��ȣ_GAWIBAWIBO] ���� ����

// ���Һ� ���� Ŭ���� �޼��� (�� ���� �ȳ�)
#define SRVAL_RETURN_BOKBULBOK_CLEAR_REWARD					32016	// ���� 32767��...

#define SRVAL_RETURN_SUMMON_TRANSFORM_USE_BONUS				32017	// ��ȭ���� ���� ���¿��� ������ �����Ϸ��� �� �� ��� �Ұ� �޽���.
#define SRVAL_RETURN_SUMMON_TRANSFORM_USE_STAMINA_ITEM		32018	// ��ȭ���� ���� ���¿��� ���׹̳� ���� �Ծ��� ��� ��� �Ұ� �޽���.

// ���� ����â�� ����
#define SRVAL_RETURN_MONCREATE_DLG							32019
// ��� ����â�� ����
#define SRVAL_RETURN_EQUIPMENTCREATE_DLG					32020
// /CMT ��ɾ�� ���� ���� ����
#define SRVAL_RETURN_MONCREATE_DLG_SUCCESS					32021
// /SEQ ��ɾ�� ��� ���� ����
#define SRVAL_RETURN_EQUIPMENTCREATE_DLG_SUCCESS			32022
// [���] ũ�������� �̺�Ʈ - ���縮���� 1�ܰ� Ʈ�� �������� �˸�
#define SRVAL_RETURN_WORLDCHRISTMASTREE_SUCCESS				32023
// [���] ũ�������� �̺�Ʈ - ���縮���� 2�ܰ� Ʈ�� �������� �˸�
#define SRVAL_RETURN_WORLDCHRISTMASTREE2_SUCCESS			32024
// [���] ũ�������� �̺�Ʈ - ���縮���� 1�ܰ� Ʈ�� �������� �˸� (�޽��� �ȶ��)
#define SRVAL_RETURN_WORLDCHRISTMASTREE3_SUCCESS			32025
// [���] ũ�������� �̺�Ʈ - ���縮���� ���� Ʈ�� �����Ǹ� �˸�
#define SRVAL_RETURN_WORLDCHRISTMASTREE_DEL					32026

//----------------------------------------------------------------------------------------------
// !!! �߰��� ����� �����ϴ�. SI16�̴� �� �̻��� �߰����� ���ʽÿ�. !!!!
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
// ���� 
// 2008-3-28
//
// �������� �޽����� �Ķ���� ��.
//----------------------------------------------------------------------------------------------

//[����] ��ƼȦ ���� �޽��� �Ķ����. => 2008-3-28
//SRVAL_FAIL_PARTYHALL
enum 
{ 
	PARTYHALL_ALREADY_USER,				// �̹� ������ ������.
	PARTYHALL_ETRANCE_RESERVATION,		// ���� ���� �Ϸ�.
	PARTYHALL_ETRANCE_RESERVATION_FAIL, // ���� ���� ����.
	PARTYHALL_ALREADY_RESERVATION,		// �̹� ���� ������.
	PARTYHALL_OPEN,						// ��Ƽ�� ����.
	PARTYHALL_CLOSE,					// ��Ƽ�� ����.
	
	PARTYHALL_MSG_NUM,					// �޽��� ����.
};

//[����] ���� �̺�Ʈ �޽��� �ĸ�����. => 2008-3-28
//SRVAL_MONSTER_ATTACK_EVENT
enum
{
	MONSTER_ATTACK_EVENT_START,			// ���� �̺�Ʈ ����.
	MONSTER_ATTACK_EVENT_END_SUCCED,	// ���� �̺�Ʈ ����.
	MONSTER_ATTACK_EVENT_END_FAIL,		// ���� �̺�Ʈ ����.
	MONSTER_ATTACK_EVENT_MONSTER_DIE,	// ���� ������~ 
	MONSTER_ATTACK_EVENT_ALREADY_RUN,	// �̹� �̺�Ʈ�� �ٸ� ������ ������. 
	MONSTER_ATTACK_EVENT_REMAIN_TIME,	// �����ð��� Ŭ�󿡰�.
};

//[����] �����. => 2008-3-28
//SRVAL_VILLAGE_HELPER
enum
{
	 SRVAL_VILLAGE_HELPER_ALREADY_QUESTION		// �̹� ������ �ֽ��ϴ�.
	,SRVAL_VILLAGE_HELPER_ALREADY_ANSWER_ME		// �̹� ���� �亯���Դϴ�.
	,SRVAL_VILLAGE_HELPER_ALREADY_ANSWER_OTHER	// �̹� �ٸ� �亯�ڰ� �亯���Դϴ�.
	,SRVAL_VILLAGE_HELPER_QUESTION_ADD_SUCCESS	// ���� ��� ����.
	,SRVAL_VILLAGE_HELPER_QUESTION_ADD_FAIL		// ���� ��� ����.
	,SRVAL_VILLAGE_HELPER_QUESTION_DEL_SUCCESS	// ���� ����.
	,SRVAL_VILLAGE_HELPER_ANSWER_ADD_SUCCESS	// �亯�� ��� ����.
	,SRVAL_VILLAGE_HELPER_ANSWER_ADD_FAIL		// �亯�� ��� ����.
	,SRVAL_VILLAGE_HELPER_QUESTION_FULL			// ������ �� ������.
	,SRVAL_VILLAGE_HELPER_ALREADY_DEL_QUESTION	// ������ ���� �Ǿ���.
	,SRVAL_VILLAGE_HELPER_LIMIT_COUNT_QUESTION	// ������ �Ϸ� ���� ���� �Ǿ���.
	,SRVAL_VILLAGE_HELPER_ANSWER_SEND_SUCCESS	// �����ڿ��� �亯�� �������� �亯�ڿ��� �˸�. 
};


//_______________________________________________________
#endif
