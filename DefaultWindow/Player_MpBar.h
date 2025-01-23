#pragma once
#include "Player_MpNote.h"

class CPlayer;

class CPlayer_MpBar
{
public:
	CPlayer_MpBar(CPlayer* _pPlayer);
	~CPlayer_MpBar();

	void	Update();
	void	Render(HDC hDC);
	void	Release();

public:
	list<CPlayer_MpNote*> Get_PlayerHpBar() { return m_PlayerMpList; }
	void				Set_MpBar();

private:
	RECT	 m_tDrawRect;
	CPlayer* m_pPlayer;
	list<CPlayer_MpNote*> m_PlayerMpList;
	int		 m_iMp;
};

