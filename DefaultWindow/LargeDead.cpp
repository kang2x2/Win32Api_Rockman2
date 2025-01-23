#include "stdafx.h"
#include "LargeDead.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"

CLargeDead::CLargeDead(INFO _info)
{
	m_tInfo = _info;
	Initialize();
}


CLargeDead::~CLargeDead()
{
}

void CLargeDead::Initialize(void)
{	
	// 이미지 정보
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/LargeDead.bmp", L"LargeDead");

	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 3;
	m_tFrame.iFrameY = 0;
	m_tFrame.dwSpeed = 40;
	m_tFrame.dwTime = GetTickCount();
}

int CLargeDead::Update(void)
{
	if (m_bDead) return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CLargeDead::Late_Update(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStartX;
		if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX) {
			m_bDead = true;
		}
		m_tFrame.dwTime = GetTickCount();
	}
}

void CLargeDead::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LargeDead");

	GdiTransparentBlt(hDC,
		int(m_tDrawRect.left + fScrollX),
		int(m_tDrawRect.top + fScrollY),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStartX * (int)m_tInfo.fCX,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(128, 0, 128));
}
