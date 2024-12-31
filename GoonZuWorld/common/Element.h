#ifndef __CELEMENT__
#define __CELEMENT__

// ������ ���Ұ� �Ǵ� Ŭ������ �θ� Ŭ���� 
class CElement
{
private:
	int				m_key;							//  ������ ������ Ű�� 
	DWORD			m_uniqID;						//  ������ ������ ���̵� �� 
	bool			m_bUsed;						//	���� �� ������ ��� ���� 	
	
public:
	CElement();
	virtual ~CElement();

public:	
	void			setKey(int key);
	int				getKey();

	void			setUsed(bool which);
	bool			getUsed();

	void			setUniqID(DWORD uniqID);
	DWORD			getUniqID();
};

#endif