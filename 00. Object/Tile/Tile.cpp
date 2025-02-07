#include "stdafx.h"
#include "Tile.h"
#include "ScrollMgr.h"

CTile::CTile()
{
}


CTile::~CTile()
{
}

void CTile::Initialize(void)
{
}

int CTile::Update(void)
{
	__super::Update_Rect();
	return 0;
}

void CTile::Late_Update(void)
{
}

void CTile::Render(HDC hDC)
{
	//float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	//float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	//
	//Rectangle(hDC, m_tDrawRect.left + fScrollX,
	//	m_tDrawRect.top + fScrollY,
	//	m_tDrawRect.right + fScrollX,
	//	m_tDrawRect.bottom + fScrollY);
}

void CTile::Release(void)
{
}
