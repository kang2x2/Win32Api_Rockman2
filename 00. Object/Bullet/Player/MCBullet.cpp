#include "stdafx.h"
#include "MCBullet.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CMCBullet::CMCBullet(float _fX, float _fY, float _fAngle)
{
	m_tInfo = { _fX, _fY, 32.f, 32.f };
	m_fAngle = _fAngle;
	m_fSpeed = 6.0f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/MCBullet.bmp", L"MCBullet");
	m_iDamage = 2;
	m_sType = "pMcBullet";

	m_iImgPosX = 0;
	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 1;
	m_tFrame.iFrameY = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}


CMCBullet::~CMCBullet()
{
}

void CMCBullet::Initialize(void)
{
}

int CMCBullet::Update(void)
{
	if (m_bDead) return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMCBullet::Late_Update(void)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// 화면 밖
	if (fScrollX - (fScrollX + m_tInfo.fX) > fScrollX ||
		fScrollX - (fScrollX + m_tInfo.fX) < fScrollX - WINCX ||
		fScrollY - (fScrollY + m_tInfo.fY) > fScrollY) {
		m_bDead = true;
	}

	if (m_fAngle == -90.f) {
		m_bRight = false;
	}
	if (m_fAngle == 90.f) {
		m_bRight = true;
	}

	if (!m_bReflect) {
		m_tInfo.fX += m_fSpeed * (m_fAngle * sin(PI / 180));
	}
	else {
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
	}

	__super::Motion_FrameR(m_iImgPosX);
}

void CMCBullet::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MCBullet");

	GdiTransparentBlt(hDC,
		int(m_tDrawRect.left + fScrollX), // 복사받을 x위치의 좌표
		int(m_tDrawRect.top + fScrollY), // 복사 받을 y위치의 좌표)
		(int)m_tInfo.fCX, // 복사 받을 가로 길이
		(int)m_tInfo.fCY, // 복사 받을 세로 길이
		hMemDC,	// 복사할 비트맵 이미지 dc
		m_tFrame.iFrameStartX * (int)m_tInfo.fCX,
		m_tFrame.iFrameY * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, // 복사할 비트맵의 가로 사이즈
		(int)m_tInfo.fCY,// 복사할 비트맵의 세로 사이즈
		RGB(0, 91, 91)); //제거하고자 하는 색상
}

void CMCBullet::Release(void)
{
}
