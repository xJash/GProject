//---------------------------------
// 2003/7/29 ���°�
//---------------------------------

#include "..\Client.h"
#include "..\..\resource.h"
#include "..\..\Common\CommonHeader.h"
#include "..\..\Common\JWLib\IsCorrectID\IsCorrectID.h"

#include "..\Interface\RecommendPersonDlg\RecommendPersonDlg.h"
#include "..\Interface\ResidenceCheck\ResidenceCheck.h"
#include "../../CommonLogic/MsgType-Person.h"
#include "../Interface/LoginClient/LoginClient.h"
#include "../NInterface/NLogin/NLogin.h"
#include "../NInterface/NSelectChar/NSelectChar.h"
#include "../Interface/SoundOnOffDlg/SoundOnOffDlg.h"

#include "../lib/WebHTML/WebHTML.h"

extern cltCommonLogic* pclClient;

// ĳ���� ����Ʈ�� 3���� ĳ���� ������ ��� ���Դ��� Ȯ���Ѵ�.
BOOL cltClient::IsReadyCharList()
{
	SI32 i;
	BOOL readyswitch = TRUE;

	for(i = 0;i < MAX_TOTAL_CHAR_PER_USER;i++)
	{
		if(clCharListInfo[ i ].clBI.GetIndex() != i)
		{
			readyswitch = FALSE;
		}
	}

	if(readyswitch == TRUE)
	{
		if(g_SoundOnOffDlg.m_bFullScreenMode)
		{
			if( m_pDialog[ NSELECTCHAR_DLG ] == NULL )
			{
				CreateInterface(NSELECTCHAR_DLG);				
				
				if ( IsCountrySwitch(Switch_CharHouse) )
				{
					if ( NULL == m_pDialog[NCHARHOUSE_DLG] )
					{
						CreateInterface( NCHARHOUSE_DLG );
					}

				}
				return TRUE;
			}

		}
	}

	return FALSE;
}


BOOL cltClient::SelectChar()//�̰����� ���������� ��������.
{
	if(g_SoundOnOffDlg.m_bFullScreenMode)
	{
		if ( m_pDialog[ NSELECTCHAR_DLG ] )
		{
			if( ((CNSelectCharDlg*)m_pDialog[ NSELECTCHAR_DLG ])->IsShowCheck() == TRUE)
			{
				((CNSelectCharDlg*)m_pDialog[ NSELECTCHAR_DLG ])->SetShowCheck(false);
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		if(SelectCharDlg == NULL)
			return FALSE;
	}

	return TRUE;
}
