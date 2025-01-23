#include "stdafx.h"
#include "CloudTile.h"

#include "ThunderLoad.h"

#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"

CCloudTile::CCloudTile(INFO _info)
{
	m_tInfo = _info; 
	m_fCenterX = m_tInfo.fX;
	m_fCenterY = m_tInfo.fY;
	Initialize();
}


CCloudTile::~CCloudTile()
{
}

void CCloudTile::Initialize(void)
{
	// 썬더로드 생성
	CObjMgr::Get_Instance()->Add_Object(OBJ_ENEMY, new CThunderLoad(
	{m_tInfo.fX, (m_tInfo.fY - m_tInfo.fCY * 0.5f), 96, 69}, this,
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front()));

	m_sType = "CloudTile";
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/CloudTile.bmp", L"CloudTile");

	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 1;
	m_tFrame.iFrameY = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = GetTickCount();

	m_prevX = 0.f;
	m_prevY = 0.f;

	m_fIncreaseAngle = 0.4f;
	m_fOffSetX = 120.0f;
	m_fOffSetY = 150.0f;
	m_fMs = 0.0154f;
}

int CCloudTile::Update(void)
{
	m_fAngle += m_fIncreaseAngle;
	
	if (m_fAngle >= 360.0f)
	{
		m_fAngle -= 360.0f;
	}

	m_prevX = m_tInfo.fX;
	m_prevY = m_tInfo.fY;
    
    m_tInfo.fX = LONG(m_fCenterX + (m_fOffSetX * (cosf(m_fAngle * (PI / 180.f)))));
    m_tInfo.fY = LONG(m_fCenterY - (m_fOffSetY * (sinf(m_fAngle * (PI / 180.f)))));

	m_fSpeed = ((m_tInfo.fX - m_prevX) * (m_tInfo.fX - m_prevX)) + 
		((m_tInfo.fY - m_prevY) * (m_tInfo.fY - m_prevY)) * m_fMs;

	__super::Update_Rect();

	return 0;
}

void CCloudTile::Late_Update(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStartX;
		if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX) {
			m_tFrame.iFrameStartX = 0;
		}
		m_tFrame.dwTime = GetTickCount();
	}
}

void CCloudTile::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"CloudTile");
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

void CCloudTile::Release(void)
{
}

