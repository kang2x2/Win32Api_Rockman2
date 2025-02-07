#include "stdafx.h"
#include "Pipi.h"

#include "SmallDead.h"

#include "PipiEgg.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "EffectMgr.h"

CPipi::CPipi(INFO _info)
{
	m_tInfo = _info;
	Initialize();
}


CPipi::~CPipi()
{
}

void CPipi::Initialize(void)
{	
	// 이미지 정보
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Enemy/Pipi.bmp", L"Pipi");

	m_fSpeed = 8.0f;

	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 2;
	m_tFrame.iFrameY = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	// 정보
	m_iDamage = 2;
	m_iHp = 1;
	m_sType = "Enemy";

	CObjMgr::Get_Instance()->Add_Object(OBJ_ENEMY, new CPipiEgg({ m_tInfo.fX, (m_tInfo.fY + (m_tInfo.fCY * 0.8f)),40, 30 }));
}

int CPipi::Update(void)
{
	if (m_bDead) {
		if (!m_bWideDead) {
			CEffectMgr::Get_Instance()->Add_Effect(EFFECT_SMALL, new CSmallDead({ m_tInfo.fX, m_tInfo.fY, 50, 56 }));
			Drop_Item();
		}
		return OBJ_DEAD;
	}

	m_tInfo.fX -= m_fSpeed;

	__super::Update_Rect();
	__super::Update_Creature_Rect();

	return OBJ_NOEVENT;
}

void CPipi::Late_Update(void)
{
	if (m_iHp <= 0) m_bDead = true;

	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	// 화면 밖
	if (fScrollX - (fScrollX + m_tInfo.fX) > fScrollX) {
		m_bWideDead = true;
		m_bDead = true;
	}

	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStartX;
		if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX) {
			m_tFrame.iFrameStartX = 0;
		}
		m_tFrame.dwTime = GetTickCount();
	}
}

void CPipi::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Pipi");

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

void CPipi::Release(void)
{
}
