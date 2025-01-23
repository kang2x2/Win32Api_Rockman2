#pragma once
#include "Player.h"

class CInventory
{
public:
	CInventory(CObj* _pPlayer);
	~CInventory();

	void Initialize(void);
	int Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Release(void);

	
public:
	int		Get_iFrameStartX() { return m_tFrame.iFrameStartX; }
	int		Get_iFrameEndX() { return m_tFrame.iFrameEndX; }
	bool	Get_CloseInven() { return m_bClose; }
	void	Set_CloseInven() { m_bClose = true; }

private:
	int			m_iArrowPos;

	bool		m_bClose;
	FRAME		m_tFrame;
	TCHAR*		m_pFrameKey;
	CObj* m_pPlayer;
};

