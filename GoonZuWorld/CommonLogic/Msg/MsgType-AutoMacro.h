#ifndef _MSGTYPE_AUTOMACRO_H
#define _MSGTYPE_AUTOMACRO_H

#define IP_STRING_SIZE	16

//[�߰� : Ȳ���� 2007. 12. 3 => �������α׷� üũ �޽��� ����ü. S->C]
class cltGameMsgResponse_AutoMacroCheck
{
public:
	SI32	m_siType;			// ��ɾ� Ÿ��.

	cltGameMsgResponse_AutoMacroCheck(SI32 _Type)
	{
		m_siType = _Type;
	}
};

//[�߰� : Ȳ���� 2007. 12. 3 => �������α׷� ����Ѵٴ� �޽��� ����ü. C->S]
class cltGameMsgRequest_AutoMacroOn
{
public:
	SI32		m_siType;
	bool		m_bAutoMacroOnOff;
	SI32		m_siPersonID;

	TCHAR		szAutoProcessName[MAX_PLAYER_NAME];		// ������� ���α׷� �̸�
	TCHAR		szIP[IP_STRING_SIZE];					// ������.
    
	cltGameMsgRequest_AutoMacroOn(SI32 _PersonID, SI32 _Type, TCHAR* _pname, TCHAR* _IP, bool _OnOff = true)
	{
		m_siPersonID	  = _PersonID;
		m_siType		  = _Type;
		m_bAutoMacroOnOff = _OnOff;

		MStrCpy(szAutoProcessName, _pname,  MAX_PLAYER_NAME);
		MStrCpy(szIP			 , _IP,		IP_STRING_SIZE);
	}
};

class cltGameMsgReponse_AutoMacroOnOther
{
public:
	SI32	m_siCount;
	TCHAR	m_szName[MAX_PLAYER_NAME];		// ĳ���̸�

	cltGameMsgReponse_AutoMacroOnOther(SI32 _Count, const TCHAR* _pName)
	{
		m_siCount = _Count;
		MStrCpy(m_szName, _pName,  MAX_PLAYER_NAME);
	}
};

#endif













































