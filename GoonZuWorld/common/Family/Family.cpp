#include "Family.h"

// �θ� �̸� ������ ����.
void CFamily::GetParentName( TCHAR* ParentName_SLot1 , TCHAR* ParentName_SLot2 ) 
{
	ParentName_SLot1 = pclParentData[0].GetParent_Name()	;
	ParentName_SLot2 = pclParentData[1].GetParent_Name()	;
}
// ���̵� �̸� ������ ����.
TCHAR* CFamily::GetChildrenName( SI32 siSLot ) 
{
	return pclChildrenData[ siSLot ].Get_Children_Name()	;
}
SI32 CFamily:: GetChildPersonID( SI32 siSLot)
{
	return pclChildrenData[siSLot].Get_Children_PersonID()	;

}
SI32 CFamily:: GetChildPersonIDfromName( TCHAR* charname)
{
	for ( SI32 siSLot = 0 ; siSLot < MAX_CHILDREN_NUM; siSLot++)
	{
		if ( pclChildrenData[siSLot].Get_Children_Name() == NULL )	continue	;		  
		if( 0 == stricmp( pclChildrenData[siSLot].Get_Children_Name() , charname ) /*pclChildrenData[siSLot].Get_Children_Name() == charname*/ )
		{
			return pclChildrenData[siSLot].Get_Children_PersonID()	;
		}		
	}
	return 0	;
}
SI32 CFamily:: GetParentPersonIDfromName( TCHAR* charname)
{
	for ( SI32 siSLot = 0 ; siSLot < MAX_CHILDREN_NUM; siSLot++)
	{
		if ( pclParentData[siSLot].GetParent_Name() == NULL )	continue	;		  
		if( 0 == stricmp( pclParentData[siSLot].GetParent_Name() , charname ) /*pclChildrenData[siSLot].Get_Children_Name() == charname*/ )
		{
			return pclParentData[siSLot].GetParent_PersonID()	;
		}		
	}
	return 0	;
}
SYSTEMTIME CFamily::GetChild_Add_Date( SI32 siSLot)
{
	return pclChildrenData[siSLot].GetFamilyEffectTime() ;

}
SYSTEMTIME CFamily::FInd_Add_Date( SI32 PersonID )
{
	SYSTEMTIME addTime ;
	addTime.wDay	=	0	;
	addTime.wDayOfWeek	=	0	;
	addTime.wHour	=	0	;
	addTime.wMilliseconds	=	0	;
	addTime.wMinute	=	0	;
	addTime.wMonth	=	0	;
	addTime.wSecond	=	0	;
	addTime.wYear	=	0	;
	for ( SI32 siSLot = 0 ; siSLot < MAX_CHILDREN_NUM; siSLot++)
	{
		if ( PersonID == pclChildrenData[siSLot].Get_Children_PersonID() )
		{
			addTime = pclChildrenData[siSLot].GetFamilyEffectTime()	;
			return addTime	;
		}
	}
	return addTime	;
}

void CFamily::SetChildren( SI32 siPersonID, TCHAR* szCharName,SYSTEMTIME stFamilyEffectDate)
{
	for ( SI32 siSlot = 0 ; siSlot < MAX_CHILDREN_NUM ; siSlot++)
	{
		if( 0 == pclChildrenData[siSlot].Get_Children_PersonID() )
		{
			pclChildrenData[siSlot].Set_Children_PersonID(	siPersonID	)	;	// �ڳ� personId
			pclChildrenData[siSlot].Set_Children_Name(	szCharName	)	;		// �ڳ� �̸�
			pclChildrenData[siSlot].SetFamilyEffectTime(stFamilyEffectDate) ;		// �ڳ� �̸�
			break	;

		}
	}
}
void CFamily::SetParent( SI32 siPersonID, TCHAR* szCharName)
{
	for ( SI32 siSlot = 0 ; siSlot < MAX_PARENT_NUM ; siSlot++ )
	{
		if( 0 == pclParentData[siSlot].GetParent_PersonID() )
		{
			pclParentData[siSlot].SetParent_PersonID(	siPersonID	)	;	// �θ� personId
			pclParentData[siSlot].SetParent_Name(	szCharName	)	;		// �θ��̸� �̸�
			break	;
		}
	}
}
SI32 CFamily::GetParent_1()
{
	return pclParentData[0].GetParent_PersonID()	;
}
SI32 CFamily::GetParent_2()
{
	return pclParentData[1].GetParent_PersonID()	;
}
SI32 CFamily::GetMatePersonID ( SI32 siParentID)
{
	for ( SI32 siSlot = 0; siSlot < MAX_PARENT_NUM; siSlot++)
	{
		if( siParentID != pclParentData[siSlot].GetParent_PersonID() )
		{
			return pclParentData[siSlot].GetParent_PersonID()	;
		}
	}
	return 0	;// �̰��� ������
}
void CFamily::DelFamilyMember ( SI32 siParentID)
{
	// �θ��߿� ���� personid�� ������ �����
	for ( SI32 siSlot = 0 ; siSlot < MAX_PARENT_NUM ; siSlot++ )
	{
		if( siParentID == pclParentData[siSlot].GetParent_PersonID() )
		{
			pclParentData[siSlot].Init()	;
			return	;	// ����� ������Ų��
		}
	}
	// �ڽ��߿� ���� personid�� ������ �����
	for ( SI32 siSlot = 0 ; siSlot < MAX_CHILDREN_NUM ; siSlot++ )
	{
		if( siParentID == pclChildrenData[siSlot].Get_Children_PersonID() )
		{
			pclChildrenData[siSlot].Init()	;
			return	;	// ����� ������Ų��
		}
	}

}
TCHAR* CFamily::GetParent_Name(SI32 siSlot)
{
	return pclParentData[siSlot].GetParent_Name()	;
}
SI32 CFamily::GetParent_PersonId(SI32 siSlot)	
{
	return pclParentData[siSlot].GetParent_PersonID()	;
}
SI32 CFamily::IsParent( SI32 siPersonID)
{
	for ( SI32 siSlot = 0 ; siSlot < MAX_PARENT_NUM ; siSlot++)
	{
		 if( siPersonID == pclParentData[siSlot].GetParent_PersonID() )	return MYCLASS_IN_FAMILY_PARANTS	;

	}
	for ( SI32 siSlot = 0 ; siSlot < MAX_CHILDREN_NUM ; siSlot++)
	{
		if( siPersonID == pclChildrenData[siSlot].Get_Children_PersonID() )	return MYCLASS_IN_FAMILY_CHILDREN	;

	}
	return MYCLASS_IN_FAMILY_NONE;
}
//--------------------------------------------------------
void CChildrenData::SetCookie( SI32 siPerson, SI32 siCookieLevel, SI32 EndDatevary, SI32 siUseLimitDateVary)
{
	m_siFamilyEffectLevel	=	siCookieLevel;	
	m_siFamilyEffectDate_EndDateVary = EndDatevary;	// ���Ŀ� ��Ű ��� ����ð� �ܰ躰�� 48�� 
	m_siFamilyEffectDate_LimitDateVary = siUseLimitDateVary;	// ���Ŀ� ��Ű ���� ��� ���ѽð� 20��
}
void CChildrenData::DelCookie()	// ��Ű ��~!
{
	m_siFamilyEffectLevel = USE_COOKIE_LEVEL_NONE	;
	m_siFamilyEffectDate_EndDateVary = 0	;
	m_siFamilyEffectDate_LimitDateVary = 0 ;

}
//--------------------------------------------------------
void CFamily::ConnectIn( SI32 siPersonID ,SI32 siClassTargetChar )
{
	switch ( siClassTargetChar )
	{
	case MYCLASS_IN_FAMILY_PARANTS :	// �θ���
		{
			for( SI32 siSLot = 0; siSLot < MAX_PARENT_NUM; siSLot++)
			{
				if( siPersonID == pclParentData[siSLot].GetParent_PersonID() )
				{
					pclParentData[siSLot].InGame()	;	// �ش� �ɸ��Ͱ� �ΰ��� �ߴ�.
					AddOnParentNum()	;	// �θ� ���� �ο� �ϳ� �߰�
					break	;
				}
			}
		}
		break;
	case MYCLASS_IN_FAMILY_CHILDREN:	// �ڽ��̶�� 
		{
			for( SI32 siSLot = 0; siSLot < MAX_CHILDREN_NUM; siSLot++)
			{
				if( siPersonID == pclChildrenData[siSLot].Get_Children_PersonID( ) )
				{
					pclChildrenData[siSLot].InGame()	;	// �ش� �ɸ��Ͱ� �ΰ��� �ߴ�.
					AddOnChildrenNum()	;	// �θ� ���� �ο� �ϳ� �߰�
					break	;
				}
			}

		}break;
	}
}
void CFamily::ConnectOut( SI32 siPersonID ,SI32 siClassTargetChar  )
{
	switch ( siClassTargetChar )
	{
	case MYCLASS_IN_FAMILY_PARANTS :	// �θ���
		{
			for( SI32 siSLot = 0; siSLot < MAX_PARENT_NUM; siSLot++)
			{
				if( siPersonID == pclParentData[siSLot].GetParent_PersonID(  ) )
				{
					pclParentData[siSLot].OutGame()	;	// �ش� �ɸ��Ͱ� ������ ������
					LoseOnParentNum()	;	// �θ� ���� �ο� �ϳ� ����
					break	;
				}
			}
		}
		break;
	case MYCLASS_IN_FAMILY_CHILDREN:	// �ڽ��̶�� 
		{
			for( SI32 siSLot = 0; siSLot < MAX_CHILDREN_NUM; siSLot++)
			{
				if( siPersonID == pclChildrenData[siSLot].Get_Children_PersonID(  ) )
				{
					pclChildrenData[siSLot].OutGame()	;	// �ش� �ɸ��Ͱ� ������ ������
					LoseOnChildrenNum()	;	// �θ� ���� �ο� �ϳ� �߰�
					break	;
				}
			}

		}break;
	}
}
void CFamily:: SetCookie( SI32 siPersonID , SI32 siCookieLevel , SI32 EndDatevary, SI32 USeLimitDateVary, SI32 siMyClass )	// ��Ű�� ��� �ߴ�.
{
	switch ( siMyClass )
	{
	case MYCLASS_IN_FAMILY_CHILDREN:	// �ڽ��̶�� 
		{
			for( SI32 siSLot = 0; siSLot < MAX_CHILDREN_NUM; siSLot++)
			{
				if( siPersonID == pclChildrenData[siSLot].Get_Children_PersonID(  ) )
				{
					//  ��Ű�� ��� �Ѵ�. 
					pclChildrenData[siSLot].SetCookie(siPersonID,siCookieLevel,EndDatevary,USeLimitDateVary )	;
				}
			}

		}break;
	}

}
SI32 CFamily:: GetMyCookieLevel( SI32 siPersonID )	// ��Ű������ ������ �´�
{
	if ( siPersonID == 0 )		return	USE_COOKIE_LEVEL_NONE;
	for( SI32 siSLot = 0; siSLot < MAX_CHILDREN_NUM; siSLot++)
	{
		if( siPersonID == pclChildrenData[siSLot].Get_Children_PersonID(  ) )
		{
			return pclChildrenData[siSLot].GetCookieLevel()	;
		}
	}
	return USE_COOKIE_LEVEL_NONE;
}
void CFamily:: LoseCookieLevel( SI32 siPersonID )	// ��Ű ������ �����.
{
	if ( siPersonID == 0 )		return	;
	for( SI32 siSLot = 0; siSLot < MAX_CHILDREN_NUM; siSLot++)
	{
		if( siPersonID == pclChildrenData[siSLot].Get_Children_PersonID(  ) )
		{
			//  ��Ű������ �����.
			pclChildrenData[siSLot].LoseCookieLevel()	;
			break	;
		}
	}
}
SI32 CFamily:: GetMyCookie_EndTime( SI32 siPersonID )	// ��Ű������ ������ �´�
{
	if ( siPersonID == 0 )		return	0;
	for( SI32 siSLot = 0; siSLot < MAX_CHILDREN_NUM; siSLot++)
	{
		if( siPersonID == pclChildrenData[siSLot].Get_Children_PersonID(  ) )
		{
			return pclChildrenData[siSLot].GetCookie_Effect_EndTime()	;
		}
	}
	return 0 ;
}
SI32 CFamily:: GetMyCookie_Limitime( SI32 siPersonID )	// ��Ű������ ������ �´�
{
	if ( siPersonID == 0 )		return	0;
	for( SI32 siSLot = 0; siSLot < MAX_CHILDREN_NUM; siSLot++)
	{
		if( siPersonID == pclChildrenData[siSLot].Get_Children_PersonID(  ) )
		{
			return pclChildrenData[siSLot].GetCookieEffect_LimitTime()	;
		}
	}
	return 0 ;
}
bool CFamily::GetOnGame_Children( SI32 siSlot )
{
	for( siSlot = 0; siSlot < MAX_CHILDREN_NUM; siSlot++)
	{
		if( true == pclChildrenData[siSlot].GetGame() )
		{
			return true	;
		}
	}
	return false ;
}
bool CFamily::GetOnGame_Parent( SI32 siSlot )
{
	return pclParentData[siSlot].GetGame();
}
SI32 CFamily::GetCookieEffect( SI32 siCookieLevel )
{
	return siCookieLevel * 2	;
}