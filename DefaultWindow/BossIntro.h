#pragma once
#include "Scene.h"

class CBossIntro : public CScene
{
public:
	CBossIntro();
	~CBossIntro();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	FRAME		m_tBgFrame; // ��� ������
	FRAME		m_tAirmanFrame; // ����� ������
	FRAME		m_tFontFrame; // ��Ʈ ������
	int			m_iChangWaitTime; // �� ��ȯ ��� �ð�
	int			m_iWaitTime; // �߰� ��� �ð�
	float		m_fAirmanPosX; // ����� ��ġ
	int			m_iNum; // Ʈ���� ��ȣ

};

