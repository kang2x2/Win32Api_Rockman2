#include "stdafx.h"
#include "GoblinTile.h"

#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"

CGoblinTile::CGoblinTile(INFO _info) : m_bIntro(true)
{
	m_tInfo = _info;
	Initialize();
}


CGoblinTile::~CGoblinTile()
{
	Release();
}

void CGoblinTile::Initialize(void)
{	
	m_sType = "GoblinTile";
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/GoblinTile.bmp", L"GoblinTile");

	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 2;
	m_tFrame.iFrameY = 0;
	m_tFrame.dwSpeed = 150;
	m_tFrame.dwTime = GetTickCount();

	m_iSummonsTime = GetTickCount();
}

int CGoblinTile::Update(void)
{
	// 뿌찌 고블린 소환
	if (CCollisionMgr::Collision_GoblinTile(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front(), this)) {
		if (m_iSummonsTime < GetTickCount()) {
			m_iSummonsTime = GetTickCount() + 5000;
			CObjMgr::Get_Instance()->Add_Object(OBJ_ENEMY, new CPucciGoblin(
			{ m_tInfo.fX + (m_tInfo.fCX * 0.4f), (m_tInfo.fY + 10.f), 50.f, 39.f }, m_tInfo.fY - 180.f, true,
				CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front()));
			CObjMgr::Get_Instance()->Add_Object(OBJ_ENEMY, new CPucciGoblin(
			{ m_tInfo.fX - (m_tInfo.fCX * 0.4f), (m_tInfo.fY + 10.f), 50.f, 39.f }, m_tInfo.fY - 180.f, false,
				CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front()));
		}
	}


	__super::Update_Rect();

	return 0;
}

void CGoblinTile::Late_Update(void)
{
	// 첫 등장
	if (m_bIntro) {
		if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStartX;
			if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX) {
				m_bIntro = false;
				m_tFrame.iFrameStartX = 2;
				m_tFrame.iFrameEndX = 3;
			}
			m_tFrame.dwTime = GetTickCount();
		}
	} 
	// 첫 등장 이후
	else {
		if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStartX;
			if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX) {
				m_tFrame.iFrameStartX = 2;
			}
			m_tFrame.dwTime = GetTickCount();
		}
	}
}

void CGoblinTile::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"GoblinTile");
	//Rectangle(hDC, m_tDrawRect.left + fScrollX,
	//	m_tDrawRect.top + fScrollY,
	//	m_tDrawRect.right + fScrollX,
	//	m_tDrawRect.bottom + fScrollY);

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
		RGB(101, 141, 209));
}

void CGoblinTile::Release(void)
{
}
