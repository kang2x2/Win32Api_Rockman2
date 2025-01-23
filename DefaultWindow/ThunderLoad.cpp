#include "stdafx.h"
#include "ThunderLoad.h"

#include "MiddleDead.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "EffectMgr.h"

CThunderLoad::CThunderLoad(INFO _info, CObj* _pCloud, CObj* _pTarget)
{
	m_tInfo = _info;
	m_pCloud = _pCloud;
	m_pTarget = _pTarget;
	m_bDead = false;
	m_bRight = false;
	Initialize();
}


CThunderLoad::~CThunderLoad()
{
}

void CThunderLoad::Initialize(void)
{
	// 이미지 정보
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Enemy/ThunderLoadL.bmp", L"ThunderLoadL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Enemy/ThunderLoadR.bmp", L"ThunderLoadR");

	m_pFrameKey = L"ThunderLoadL";

	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 1;
	m_tFrame.iFrameY = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	// 정보
	m_iDamage = 3;
	m_iHp = 5;
	m_sType = "Enemy";

	m_iAtkCoolTime = 0;
}

int CThunderLoad::Update(void)
{
	if (m_bDead) {
		CEffectMgr::Get_Instance()->Add_Effect(EFFECT_MIDDLE, new CMiddleDead({ m_tInfo.fX, m_tInfo.fY, 80, 90 }));
		return OBJ_DEAD;
	}

	m_tInfo.fX = m_pCloud->Get_Info().fX - 5.f;
	m_tInfo.fY = m_pCloud->Get_Info().fY - (m_pCloud->Get_Info().fCY - 5.f);

	if (fabs(m_tInfo.fX - m_pTarget->Get_Info().fX) < 200.f) {
		if (m_iAtkCoolTime < GetTickCount()) {
			m_tFrame.iFrameStartX = 3;
			m_tFrame.dwTime = GetTickCount();
			m_iAtkCoolTime = GetTickCount() + 2500;
			CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET, new CThunder(
			{m_tInfo.fX, m_tInfo.fY ,38, 28}, false));
		}
	}

	__super::Update_Rect();
	__super::Update_Creature_Rect();

	return OBJ_NOEVENT;
}

void CThunderLoad::Late_Update(void)
{
	if (m_iHp <= 0) m_bDead = true;

	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStartX;
		if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX) {
			m_tFrame.iFrameStartX = 0;
		}
		m_tFrame.dwTime = GetTickCount();
	}
}

void CThunderLoad::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

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

void CThunderLoad::Release(void)
{
}
