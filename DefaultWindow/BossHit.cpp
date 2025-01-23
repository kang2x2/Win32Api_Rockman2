#include "stdafx.h"
#include "BossHit.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"

CBossHit::CBossHit()
{
}


CBossHit::~CBossHit()
{
}

void CBossHit::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/BossHitEffect.bmp", L"BossHit");
}

void CBossHit::Render(HDC hDC, float _fX, float _fY)
{
	m_tDrawRect = { (int)_fX - 57, (int)_fY - 45, 114, 91 };

	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BossHit");

	GdiTransparentBlt(hDC, (int)(m_tDrawRect.left + fScrollX), (int)(m_tDrawRect.top + fScrollY),
		104, 83, hMemDC, 0, 0, 104, 83, RGB(128, 0, 128));
}
