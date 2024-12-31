#include "WhisperChatMgr.h"
#include "WhisperChatObj.h"

#include "..\SMLib\LibList\LibList.h"

#include "..\CommonLogic\CommonLogic.h"
extern cltCommonLogic *pclClient;

CWhisperChatMgr::CWhisperChatMgr()
{
	CreateMaxEmptyObj();
}

CWhisperChatMgr::~CWhisperChatMgr()
{

}

void CWhisperChatMgr::Init()
{
	return;
}

void CWhisperChatMgr::CreateMaxEmptyObj()
{
	CWhisperChatObj *pTemp = NULL;

	for ( int i = 0; i < MAX_WHISPERCHAT_OBJ_NUM; ++i )
	{
		pTemp = new CWhisperChatObj( i + 1 );		// �ε���
		PushBackToEmptyList( pTemp );
	}

	return;
}

CWhisperChatObj *CWhisperChatMgr::GetWhisperChatObj( SI32 Index )
{
	CWhisperChatObj *pTemp = (CWhisperChatObj *)GetExistList()->GetFirst();
	
	while( pTemp )
	{
		if ( pTemp->GetWhisperChatIndex() == Index )
		{
			return pTemp;
		}

		pTemp = (CWhisperChatObj *)pTemp->GetNext();
	}

	return NULL;
}

// �� ���� ��ȭ�� ���� ��
SI32 CWhisperChatMgr::Create( SI32 CharID1, SI32 PersonID1, TCHAR *CharName1, SI32 CharID2, SI32 PersonID2, TCHAR *CharName2 )
{
	CWhisperChatObj *pTemp = (CWhisperChatObj *)GetExistList()->GetFirst();
	
	while( pTemp )
	{
		if ( pTemp->IsCreated( PersonID1, PersonID2 ) )
		{
			return -1;	// ���� ���� �ӼӸ���
		}

		pTemp = (CWhisperChatObj *)pTemp->GetNext();
	}

	pTemp = (CWhisperChatObj *)PopFrontToEmptyListAndPushBackToExistList();

	if ( pTemp == NULL )
	{
		return 0;		// ��ü �Ҵ� �Ұ���
	}

	return pTemp->Create( CharID1, PersonID1, CharName1, CharID2, PersonID2, CharName2 );
}