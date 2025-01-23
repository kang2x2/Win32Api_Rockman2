#pragma once
#include "Scene.h"

class CSelectBoss : public CScene
{
public:
	CSelectBoss();
	~CSelectBoss();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	FRAME		m_tBgFrame;
	FRAME		m_tPtFrame;

	int			m_iSelectAry[3][3] = {0,}; // ����Ʈ ������ �迭
	bool		m_bSuccesMove; // ����Ʈ ������
	bool		m_bSelect; // ���� �Ϸ�

	int		m_iWaitTime; // �� ��ȯ ��� �ð�
};

