#pragma once

#include "Define.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	float		Get_ScrollX(void) { return m_fScrollX; }
	float		Get_ScrollY(void) { return m_fScrollY; }
	float		Get_ScrollMinX(void) { return m_fMinScrollX; }
	float		Get_ScrollMaxX(void) { return m_fMaxScrollX; }
	bool		Get_SCrollMoveX(void) { return m_bScrollMoveX; }

	void		TestY() { m_fMinScrollY = -600; }
	void		TestY2() { m_fMinScrollY = 0; }

	void		Set_ScrollFixX(float _fX) { m_fScrollX = _fX; }
	void		Set_ScrollFixY(float _fY) { m_fScrollY = _fY; }
	void		Set_ScrollX(float _fX) { m_fScrollX += _fX; }
	void		Set_ScrollY(float _fY) { m_fScrollY += _fY; }

	// 타이틀화면용
	void		Set_ScrollY_Title(float _fY) { m_fScrollY = _fY; }

	float		Get_ScrollMinY() { return m_fMinScrollY; }

	void		Scroll_Lock(void);

	void		Scroll_SetMinY() { m_fMinScrollY -= WINCY; }
	void		Scroll_SetMinFixY(int _fixY) { m_fMinScrollY = _fixY; }
	void		Set_MinScrollX(int _scrollPos) { m_fMinScrollX = (float)_scrollPos; }
	void		Set_MaxScrollX(int _scrollPos) { m_fMaxScrollX = (float)_scrollPos; }
	// x축 스크롤 이벤트 관련
	void	Set_ScrollMoveX(bool _bMoveScroll) { m_bScrollMoveX = _bMoveScroll; }
public:
	static CScrollMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CScrollMgr;

		return m_pInstance;
	}
	static void		Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}

	}
private:
	static CScrollMgr*		m_pInstance;
	float					m_fScrollX;
	float					m_fScrollY;

	float					m_fMaxScrollX;
	float					m_fMinScrollX;

	float					m_fMinScrollY;

	// x스크롤 무브 연출 관련
	bool m_bScrollMoveX;
};

