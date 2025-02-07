#include "stdafx.h"
#include "PlDeadEffect.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"

CPlDeadEffect::CPlDeadEffect(INFO _info, float _fAngle) : m_fSpeed(4.0f), m_fAngle(_fAngle)
{
	m_tInfo = _info;
	Initialize();
}


CPlDeadEffect::~CPlDeadEffect()
{
}

void CPlDeadEffect::Initialize(void)
{
	// 이미지 정보
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Dead.bmp", L"Dead");

	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 3;
	m_tFrame.iFrameY = 0;
	m_tFrame.dwSpeed = 40;
	m_tFrame.dwTime = GetTickCount();
}

int CPlDeadEffect::Update(void)
{
	if (m_bDead) return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlDeadEffect::Late_Update(void)
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

void CPlDeadEffect::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Dead");

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
