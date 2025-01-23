#include "stdafx.h"
#include "Matasaburo.h"

#include "LargeDead.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "EffectMgr.h"

CMatasaburo::CMatasaburo(INFO _info)
{
	m_tInfo = _info;
	Initialize();
}


CMatasaburo::~CMatasaburo()
{
}

void CMatasaburo::Initialize(void)
{
	// 이미지 정보
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Enemy/Matasaburo.bmp", L"Matasaburo");

	m_tFrame.iFrameStartX = 1;
	m_tFrame.iFrameEndX = 2;
	m_tFrame.iFrameY = 0;
	m_tFrame.dwSpeed = 40;
	m_tFrame.dwTime = GetTickCount();

	// 정보
	m_iDamage = 4;
	m_iHp = 10;
	m_sType = "Enemy";

	m_iWaitTime = GetTickCount();
}

int CMatasaburo::Update(void)
{
	if (m_bDead) {
		CEffectMgr::Get_Instance()->Add_Effect(EFFECT_LARGE, new CLargeDead({ m_tInfo.fX, m_tInfo.fY, 100, 112 }));
		Drop_Item();
		m_fPushPower = 0.f;
		return OBJ_DEAD;
	}

	if (m_tInfo.fX - CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front()->Get_Info().fX  < 350.f &&
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front()->Get_Info().fX < 9000.f) {
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front()->Set_X(-2.0f);
	}

	__super::Update_Rect();
	__super::Update_Creature_Rect();

	return OBJ_NOEVENT;
}

void CMatasaburo::Late_Update(void)
{
	if (m_iHp <= 0) m_bDead = true;

	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStartX;
		if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX) {
			m_tFrame.iFrameStartX = 1;
		}
		m_tFrame.dwTime = GetTickCount();
	}
}

void CMatasaburo::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Matasaburo");

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

void CMatasaburo::Release(void)
{
}
