#include "stdafx.h"
#include "Thunder.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"

CThunder::CThunder(INFO _info, bool _bRight)
{
	m_tInfo = _info;
	m_bRight = _bRight;
	Initialize();
}


CThunder::~CThunder()
{
}

void CThunder::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Enemy/ThunderL.bmp", L"ThunderL");
	m_fUpPower = 8.f;
	m_fSpeed = 3.0f;

	m_iDamage = 2;
	m_sType = "eBullet";
}

int CThunder::Update(void)
{
	if (m_bDead) return OBJ_DEAD;


	if (m_bReflect) {
		m_tInfo.fX -= -m_fSpeed;
		m_tInfo.fY -= m_fUpPower;
	}
	else {
		m_tInfo.fX -= m_fSpeed;
		m_tInfo.fY -= m_fUpPower;
	}
	m_fUpPower -= 0.4f;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CThunder::Late_Update(void)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// È­¸é ¹Û
	if (fScrollX - (fScrollX + m_tInfo.fX) > fScrollX ||
		fScrollX - (fScrollX + m_tInfo.fX) < fScrollX - WINCX ||
		m_tInfo.fY > 700.f) {
		m_bDead = true;
	}

}

void CThunder::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ThunderL");

	GdiTransparentBlt(hDC,
		int(m_tDrawRect.left + fScrollX),
		int(m_tDrawRect.top + fScrollY), 
		(int)m_tInfo.fCX, 
		(int)m_tInfo.fCY, 
		hMemDC,	
		m_tFrame.iFrameStartX * (int)m_tInfo.fCX,
		m_tFrame.iFrameY * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(128, 0, 128)); 
}

void CThunder::Release(void)
{
}
