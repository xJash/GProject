//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���� : GMDefine.h
//
// ���� : GMTool���� �޽��� ����
//
// ��¥ : 2008.01.23
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// �⺻���� ������ ��ư �޽���
enum UPDATA_ID_BASICINFO
{
	UPDATA_ID_BASICINFO_NONE = 0,			// �ƹ��͵� �ƴ�
	UPDATA_ID_BASICINFO_STATUS_RESET = 1,	// �������ͽ� ����	
	UPDATA_ID_BASICINFO_MONEY_ADD,			// ����� �Ӵ� �߰�
	UPDATA_ID_BASICINFO_MONEY_SUB,			// ����� �Ӵ� ����
	UPDATA_ID_BASICINFO_BANKMONEY_ADD,		// ���� �Ӵ� �߰�
	UPDATA_ID_BASICINFO_BANKMONEY_SUB,		// ���� �Ӵ� ����
	UPDATA_ID_BASICINFO_ACU_ADD,			// ��ť �߰�
	UPDATA_ID_BASICINFO_ACU_SUB,			// ��ť ����
	UPDATA_ID_BASICINFO_STOCK_ADD,			// �ֽ� �߰�
	UPDATA_ID_BASICINFO_STOCK_SUB,			// �ֽ� ����
	UPDATA_ID_BASICINFO_BUF_MODIFY,			// ���� ����
};

enum UPDATA_ID_CHARINFO
{
	UPDATA_ID_CHARINFO_REQUEST = 100,		// ĳ���� ���� ��û
};

// ��ų ������ ��ư �޽���
enum UPDATA_ID_SKILL
{
	UPDATA_ID_SKILL_NONE = 0 //�ƹ��͵� �ƴ�
};

// ����ǰ ������ ��ư �޽���
enum UPDATA_ID_INVENTORY
{
	UPDATA_ID_INVENTORY_NONE = 0,			// �ƹ��͵� �ƴ�
	UPDATA_ID_INVENTORY_ITEM_ADD = 1		// �������� �־��ش�
};

// �ε��� ������ ��ư �޽���
enum UPDATA_ID_REALESTATE
{
	UPDATA_ID_REALESTATE_NONE = 0 //�ƹ��͵� �ƴ�
};

// ��ȯ�� ������ ��ư �޽���
enum UPDATA_ID_SUMMON
{
	UPDATA_ID_SUMMON_NONE = 0 //�ƹ��͵� �ƴ�
};

// ����(Ż��) ������ ��ư �޽���
enum UPDATA_ID_ANIMAL
{
	UPDATA_ID_ANIMAL_NONE = 0 //�ƹ��͵� �ƴ�
};

// ������Ʈ ������ �޽���
enum UPDATA_MSG
{
	UPDATA_ERROR_MSG_NOT_DEFINE_ID = 0,		// ���ǵ��� ���� ���(��ư)�� ��������
	UPDATA_ERROR_MSG_DO_NOT_RUN,			// ������ �� ����
	UPDATA_ERROR_MSG_NO_PERSONID,			// �������� �ʴ� �ɸ���
	UPDATA_ERROR_MSG_ONLY_CONNECT_USER,		// ������ �ɸ��Ϳ� ���ؼ��� ����� ������ �� �ִ�
	UPDATA_ERROR_MSG_ONLY_DISCONNECT_USER,	// �������� ���� �ɸ��Ϳ� ���ؼ��� ����� ������ �� �ִ�
	UPDATA_ERROR_MSG_WRONG_MONEY,			// �� ������ �߸� �Ǿ��ִ�
	UPDATA_ERROR_MSG_WRONG_VILLAGE_UNIQUE,	// ���� ����ũ ������ �߸� �Ǿ���
	UPDATA_ERROR_MSG_WRONG_STOCK_AMOUNT,	// �ֽ� �� ������ �߸� �Ǿ���
	UPDATA_ERROR_MSG_WRONG_BUF_NUMBER,		// ���� ��ȣ(Type) ������ �߸� �Ǿ��ִ�
	UPDATA_ERROR_MSG_WRONG_BUF_SLOT,		// ���� ����(�迭 ��Ұ�) ������ �߸� �Ǿ��ִ�
	UPDATA_ERROR_MSG_WRONG_BUF_TIME,		// ���� �ð������� �߸� �Ǿ��ִ�

	UPDATA_ERROR_MSG_WRONG_ITEM_NAME,		// ������ �̸��� �߸� �Ǿ���
	UPDATA_ERROR_MSG_WRONG_ITEM_NUM,		// ������ ������ �߸� �Ǿ���
	UPDATA_ERROR_MSG_WRONG_INVENTORY_SLOT,	// �κ��丮 ���� ��ȣ�� �߸� �Ǿ���
	UPDATA_ERROR_MSG_DO_NOT_MAKE_ITEM,		// �������� ������ �� ����
	// �����޽��� �߰��� �� �޽��� ���� �߰�
	UPDATA_ERROR_MSG_END					// �����޽��� �� ��ȣ
};

const SI32 Const_UpData_Success = UPDATA_ERROR_MSG_END + 1;// ������Ʈ �۾��� ���� �ߴٴ� �޽���

const SI32 Const_Max_Account_Num = 50;	// GMTool�� �����Ҽ� �ִ� �ִ� ������ ��