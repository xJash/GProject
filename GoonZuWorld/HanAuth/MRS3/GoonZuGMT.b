class GMTMessageReq_K_GOONZU			// ���ӹ�۰���
{
    int32 nIdx;				// �޽��� index
    string strMessage;		// ��� �޽���
    int32 nContinueTime;		// ���� ���ӽð�(��)
};

class GMTMessageAns_K_GOONZU
{
    int32 nIdx;
    int32 nErrCode;
};

class GMTKickReq_K_GOONZU			// ����
{
    int32 nIdx;				// �޽��� index
    string strPlayerName;		// ĳ���͸�
    string strTime;			// ���ӽð�(��) -1 : ���ӽð� ����(�ܼ� ����), 0 : �������� ��� ����, >0 ���ӽð�(��)
};

class GMTKickAns_K_GOONZU
{
    int32 nIdx;
    int32 nErrCode;
};

class GMTChatBlockReq_K_GOONZU		// ä�� ���
{
    int32 nIdx;				// �޽��� index
    string strPlayerName;		// ĳ���͸�
    string strTime;			// ���ӽð�(��) 0 : ä�� ��� ����, >0 ���ӽð�(��)
};

class GMTChatBlockAns_K_GOONZU
{
    int32 nIdx;
    int32 nErrCode;
};

class GMTCmdReq_K_GOONZU			// ���ӸӴ�, ������ �߰�
{
    int32 nIdx;				// �޽��� index
    int32 nServerId;			// ���� id
    string strCmd;			// ���ӸӴ�, ������ �߰�
};

class GMTCmdAns_K_GOONZU
{
    int32 nIdx;
    int32 nErrCode;
};
