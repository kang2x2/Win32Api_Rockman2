#pragma once
#include "Scene.h"

class CMyMenu : public CScene
{
public:
	CMyMenu();
	virtual ~CMyMenu();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	FRAME		m_tFrame;
	float		m_fScrollSpeed; // ��ũ�� �ӵ�
	int			m_iWaitTime; // �߰� ��� �ð�
	int			m_iNum; // Ʈ���� �ѹ�
	float		m_fTpSpeed; // �ϸ� ���� �ӵ�
};

