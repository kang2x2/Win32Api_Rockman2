#include "stdafx.h"
#include "LargeHelth.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"

CLargeHelth::CLargeHelth(INFO _info)
{
	m_tInfo = _info;
	Initialize();
}


CLargeHelth::~CLargeHelth()
{
}

void CLargeHelth::Initialize(void)
{
	// 이미지 정보
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/LargeHelth.bmp", L"LargeHelth");

	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 1;
	m_tFrame.iFrameY = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	m_iHp = 6;
	m_sType = "HpItem";

	m_fDropTime = 0;
	m_bGround = false;
}

int CLargeHelth::Update(void)
{
	m_fDropTime += 0.5f;
	if (CCollisionMgr::Collision_Item_Tile(this, CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE))) {
		m_fDropTime = 0.f;
	}
	else {
		m_tInfo.fY += m_fDropTime;
	}

	if (m_bDead) return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CLargeHelth::Late_Update(void)
{
	if (m_tInfo.fY > 1800) m_bDead = true;

	// 애니메이션
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStartX;
		if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX) {
			m_tFrame.iFrameStartX = 0;
		}
		m_tFrame.dwTime = GetTickCount();
	}
}

void CLargeHelth::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LargeHelth");

	//Rectangle(hDC, m_tDrawRect.left + fScrollX,
	//	m_tDrawRect.top + fScrollY,
	//	m_tDrawRect.right + fScrollX,
	//	m_tDrawRect.bottom + fScrollY);

	// 무적 상태라면 항시 드로우
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

void CLargeHelth::Release(void)
{
}
