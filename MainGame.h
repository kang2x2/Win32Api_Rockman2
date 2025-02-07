#pragma once

#include "Define.h"
#include "Player.h"

class CMainGame
{
public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render();
	void		Release(void);

private:
	HDC			m_DC;
	int			m_iFPS;
	TCHAR		m_szFPS[32];
	DWORD		m_dwTime;

	bool m_bGameStart;

public:
	CMainGame();
	~CMainGame();
};

