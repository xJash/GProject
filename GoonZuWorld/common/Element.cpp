#include <windows.h>
#include "Element.h"
//-----------------------------------------------------------------------------------------------------------------------
//	Name : CElement()
//	Desc : 생성자 
//-----------------------------------------------------------------------------------------------------------------------
CElement::CElement()
{
	m_key	 = -1;	
	m_uniqID = -1;
	m_bUsed  = FALSE;
}



//-----------------------------------------------------------------------------------------------------------------------
//	Name : ~CElement()
//	Desc : 소멸자 
//-----------------------------------------------------------------------------------------------------------------------
CElement::~CElement()
{
}



//-----------------------------------------------------------------------------------------------------------------------
//	Name : setKey()
//	Desc : 원소에 키를 할당한다 
//-----------------------------------------------------------------------------------------------------------------------
void CElement::setKey(int key)	
{	
	m_key = key;	
}



//-----------------------------------------------------------------------------------------------------------------------
//	Name : GetKey()
//	Desc : 원소에 지정된 키를 얻는다 
//-----------------------------------------------------------------------------------------------------------------------
int CElement::getKey()
{		
	return m_key;	
}



//-----------------------------------------------------------------------------------------------------------------------
//	Name : setUsed()
//	Desc : 원소의 사용여부를 결정한다 
//-----------------------------------------------------------------------------------------------------------------------
void CElement::setUsed(bool which)	
{
	m_bUsed = which;	
}



//-----------------------------------------------------------------------------------------------------------------------
//	Name : getUsed()
//	Desc : 원소의 현재 사용여부를 얻는다 
//-----------------------------------------------------------------------------------------------------------------------
bool CElement::getUsed()  
{
	return m_bUsed;
}



//-----------------------------------------------------------------------------------------------------------------------
//	Name : setUniqID()
//	Desc : 유일한 아이디 값을 할당한다 
//-----------------------------------------------------------------------------------------------------------------------
void CElement::setUniqID(DWORD uniqID)	
{
	m_uniqID = uniqID;	
}



//-----------------------------------------------------------------------------------------------------------------------
//	Name : getUniqID()
//	Desc : 유일한 아이디 값을 얻는다 
//-----------------------------------------------------------------------------------------------------------------------
DWORD CElement::getUniqID()  
{
	return m_uniqID;
}