#pragma once
#include "Boss_HpNote.h"

class CAir_Man;

class CBoss_HpBar
{
public:
	CBoss_HpBar(CAir_Man* _pBoss);
	~CBoss_HpBar();

	void	Update();
	void	Render(HDC hDC);
	void	Release();

public:
	list<CBoss_HpNote*> Get_BossHpBar() { return m_BossHpList; }
	void				Set_HpBar();

private:
	RECT	 m_tDrawRect;
	CAir_Man* m_pBoss;
	list<CBoss_HpNote*> m_BossHpList;
};

