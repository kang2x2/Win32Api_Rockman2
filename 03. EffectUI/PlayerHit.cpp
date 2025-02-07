#include "stdafx.h"
#include "PlayerHit.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"

CPlayerHit::CPlayerHit()
{
}


CPlayerHit::~CPlayerHit()
{
}

void CPlayerHit::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/PlayerHitEffect.bmp", L"PlayerHit");
}

void CPlayerHit::Render(HDC hDC, float _fX, float _fY)
{
	m_tDrawRect = { (int)_fX - 40, (int)_fY - 40, 80, 80 };

	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerHit");

	GdiTransparentBlt(hDC, (int)(m_tDrawRect.left + fScrollX), (int)(m_tDrawRect.top + fScrollY),
		80, 80, hMemDC, 0, 0, 80, 80, RGB(128, 0, 128));
}
