//-------------------------------------------------------------------------------------------------
// NkMsg.h
// �������� ���������
// ������
//-------------------------------------------------------------------------------------------------

#pragma once

class NkMsg
{
public:
	unsigned short m_usMsgSize;
	unsigned short m_usMsgType;

	inline unsigned short GetMsgSize() const { return m_usMsgSize; }
	inline unsigned short GetMsgType() const { return m_usMsgType; }
};

class NkNetMsg : public NkMsg
{
public:
	unsigned char m_chksum;
};
