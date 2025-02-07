#include "stdafx.h"
#include "PipiEgg.h"

#include "SmallDead.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"

#include "EffectMgr.h"

CPipiEgg::CPipiEgg(INFO _info)
{
	m_tInfo = _info;
	Initialize();
}


CPipiEgg::~CPipiEgg()
{
}

void CPipiEgg::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Enemy/PipiEgg.bmp", L"PipiEgg");

	m_fSpeed = 8.0f;
	m_fDropSpeed = 0.f;

	// 정보
	m_iDamage = 2;
	m_iHp = 1;
	m_sType = "Enemy";
	m_bDrop = false;
}

int CPipiEgg::Update(void)
{
	if (m_bDead) {
		CEffectMgr::Get_Instance()->Add_Effect(EFFECT_SMALL, new CSmallDead({ m_tInfo.fX, m_tInfo.fY, 50, 56 }));
		Drop_Item();
		return OBJ_DEAD;
	}

	if (!m_bDrop) {
		m_tInfo.fX -= m_fSpeed;
	}
	else if (m_bDrop) {
		m_fDropSpeed += 0.5f;
		m_tInfo.fY += m_fDropSpeed;
	}

	__super::Update_Rect();
	__super::Update_Creature_Rect();

	return OBJ_NOEVENT;
}

void CPipiEgg::Late_Update(void)
{
	if (m_iHp <= 0) m_bDead = true;

	// 카메라 밖으로 나가면
	if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front()->Get_Info().fX - m_tInfo.fX > 500.f ||
		m_tInfo.fY > WINCY * 3) {
		m_bDead = true;
	}


	if (m_tInfo.fX - CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front()->Get_Info().fX < 100.f) {
		m_bDrop = true;
	}

	CCollisionMgr::Collision_Egg(this);
}

void CPipiEgg::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PipiEgg");

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

void CPipiEgg::Release(void)
{
}
