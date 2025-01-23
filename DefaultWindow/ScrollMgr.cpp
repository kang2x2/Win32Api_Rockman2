#include "stdafx.h"
#include "ScrollMgr.h"

CScrollMgr*		CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
	: m_fScrollX(0.f), m_fScrollY(0.f), m_bScrollMoveX(false),
	m_fMaxScrollX(-5080.f), m_fMinScrollX(0.f), m_fMinScrollY(600.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock(void)
{
	if (!m_bScrollMoveX && m_fMinScrollX < m_fScrollX)
		m_fScrollX = m_fMinScrollX;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (!m_bScrollMoveX && m_fMaxScrollX > m_fScrollX)
		m_fScrollX = m_fMaxScrollX;

	else if (m_bScrollMoveX && m_fMaxScrollX < m_fScrollX) {
		m_fScrollX -= 8.0f;
		if (m_fMaxScrollX >= m_fScrollX) {
			m_bScrollMoveX = false;
		}
	}
}


