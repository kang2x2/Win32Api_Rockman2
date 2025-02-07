#pragma once
#include "Player_HpNote.h"

class CPlayer;

class CPlayer_HpBar
{
public:
	CPlayer_HpBar(CPlayer* _pPlayer);
	~CPlayer_HpBar();

	void	Update();
	void	Render(HDC hDC);
	void	Release();

public:
	list<CPlayer_HpNote*> Get_PlayerHpBar() { return m_PlayerHpList; }
	void				Set_HpBar();

private:
	RECT	 m_tDrawRect;
	CPlayer* m_pPlayer;
	list<CPlayer_HpNote*> m_PlayerHpList;
};

