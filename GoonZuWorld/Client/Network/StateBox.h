#ifndef _STATEBOX_H
#define _STATEBOX_H

#include "itzbase.h"

enum {
		USERSTATE_DISCONNECTED = 0,
		USERSTATE_FRONT_CONNECTING,			// ����Ʈ ������ ���� �õ��� 
		USERSTATE_FRONT_CONNECTED,			// ����Ʈ ���� ���� ����, ���̵� �Է� ��, ���� �����
		USERSTATE_FRONT_AUTHOK,				// ���� ����
		USERSTATE_FRONT_NOTICEOK,			// �������� ����
		USERSTATE_FRONT_SERVERSELECTING,	// ���� ���� ��
		USERSTATE_GAME_CONNECTING,			// ���� ������ ���� �õ���
		USERSTATE_GAME_CONNECTED,			// ���� ���� ���� ����, ���� �����
		USERSTATE_GAME_AUTHOK,				// ���� ����
		USERSTATE_GAME_CHARSELECTING,		// ĳ���� ���� ��
		USERSTATE_GAME_PLAYING				// ���� �÷��� ��
};


class cltStateBox
{
public:
	cltStateBox() { m_uiState = 0; };
	~cltStateBox() {};

	void			SetState( UI32 state ) { InterlockedExchange( (LPLONG)&m_uiState, state ); };
	UI32			GetState() { return m_uiState; };

public:

	UI32			m_uiState;
};


#endif