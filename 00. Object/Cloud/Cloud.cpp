#include "stdafx.h"
#include "Cloud.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"

CCloud::CCloud()
{
}


CCloud::~CCloud()
{
}

void CCloud::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/RockMan_Stage.bmp", L"Cloud");
	m_tFrame.iFrameY = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

void CCloud::Update(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameY;

		if (m_tFrame.iFrameY > 2)
			m_tFrame.iFrameY = 0;

		m_tFrame.dwTime = GetTickCount();
	}
}

void CCloud::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Cloud");

	GdiTransparentBlt(hDC,
		(int)(0 + fScrollX),
		(int)(0 + fScrollY),
		11910,
		1800,
		hMemDC,
		0,
		m_tFrame.iFrameY * 1800,
		11910,
		1800,
		RGB(128, 0, 128));
}
