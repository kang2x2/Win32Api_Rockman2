#include "stdafx.h"
#include "CoPipi.h"

#include "VerySmallDead.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "EffectMgr.h"

CCoPipi::CCoPipi(INFO _info, float _fAngle)
{
	m_tInfo = _info;
	m_fAngle = _fAngle;
	Initialize();
}


CCoPipi::~CCoPipi()
{
}

void CCoPipi::Initialize(void)
{
	// 이미지 정보
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Enemy/CoPipi.bmp", L"CoPipi");

	// 정보
	m_iDamage = 2;
	m_iHp = 1;
	m_sType = "Enemy";
	m_fSpeed = 3.0f;
	m_bSpread = true;
	m_fSpreadTime = GetTickCount() + 500;

	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 1;
	m_tFrame.iFrameY = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	m_pTarget = CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front();
}

int CCoPipi::Update(void)
{
	if (m_bDead) {
		if (!m_bWideDead) {
			CEffectMgr::Get_Instance()->Add_Effect(EFFECT_SMALL, new CVerySmallDead({ m_tInfo.fX, m_tInfo.fY, 50, 56 }));
		}
		else {
			Drop_Item();
		}
		return OBJ_DEAD;
	}

	if (m_bSpread && m_fSpreadTime < GetTickCount()) {
		m_bSpread = false;
		float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;

		m_fAngle = (atan2(fY, fX) * 180.f / PI);

		m_fSpeed = 7.5f;
	}

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);


	__super::Update_Rect();
	__super::Update_Creature_Rect();

	return OBJ_NOEVENT;
}

void CCoPipi::Late_Update(void)
{
	if (m_iHp <= 0) m_bDead = true;

	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	// 화면 밖
	if (fScrollX - (fScrollX + m_tInfo.fX) > fScrollX ||
		fScrollX - (fScrollX + m_tInfo.fX) < fScrollX - WINCX) {
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

void CCoPipi::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"CoPipi");

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

void CCoPipi::Release(void)
{
}
