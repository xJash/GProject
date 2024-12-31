#ifndef _ASTARLIST_H_
#define _ASTARLIST_H_

class CAStarNode;

class CAStarList  
{
public:
	CAStarList();													// �� �� ��
	~CAStarList();													// �� �� ��

	void			Initialize();								// �� �� ȭ
	void			Destroy();									// ���� ó��

	void			ListClear();								// ����Ʈ ���� ���� ���� ����
	
	//void	AddNode( CAStarNode *pNode );				// ����Ʈ�� ��� ������ �߰�
		
	CAStarNode		*IsExist( int siTileX, int siTileY );		// ����Ʈ�� ��尡 �����ϴ� ���� üũ

	CAStarNode		*GetFirstNode();							// ����Ʈ ���� ���� ����� �����͸� ������.
	void			SetFirstNode( CAStarNode * );				// ����Ʈ ���� ���� ����� �����͸� ������

	CAStarNode		*GetLastNode();								// ����Ʈ ���� ���� ����� �����͸� ������.
	void			SetLastNode( CAStarNode * pNode );			// ����Ʈ ���� ���� ����� �����͸� ������
	
	int				GetNodeNum();								// ����Ʈ�� ��ü�� �� �� ������...

private:
	CAStarNode *m_pFirst;									// ����Ʈ �� ���� ���
	CAStarNode *m_pLast;									// ����Ʈ �� ���� ���

	
};

#endif