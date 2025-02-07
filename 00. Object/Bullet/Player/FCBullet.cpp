#include "stdafx.h"
#include "FCBullet.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

#include "PlayerState.h"

CFCBullet::CFCBullet(float _fX, float _fY, float _fAngle)
{
	m_tInfo = { _fX, _fY, 64.f, 64.f };
	m_fAngle = _fAngle;
	m_fSpeed = 7.0f;
	m_iDamage = 4;
	m_sType = "pFcBullet";

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FCBulletR.bmp", L"FCBulletR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FCBulletL.bmp", L"FCBulletL");

	if (m_fAngle == -90.f) m_bRight = false;
	if (m_fAngle == 90.f) m_bRight = true;

	if (m_bRight) {
		m_iImgPosX = 0;
		m_tFrame.iFrameStartX = 0;
		m_tFrame.iFrameEndX = 1;
		m_tFrame.iFrameY = 0;
		m_tFrame.dwSpeed = 200;
		m_tFrame.dwTime = GetTickCount();
	}
	else {
		m_iImgPosX = 1;
		m_tFrame.iFrameStartX = 1;
		m_tFrame.iFrameEndX = 0;
		m_tFrame.iFrameY = 0;
		m_tFrame.dwSpeed = 200;
		m_tFrame.dwTime = GetTickCount();
	}
	
}


CFCBullet::~CFCBullet()
{
}

void CFCBullet::Initialize(void)
{
}

int CFCBullet::Update(void)
{
	if (m_bDead) {
		CPlayerState::m_iBltCount -= 3;
		return OBJ_DEAD;
	}

	__super::Update_Rect();
	
	return OBJ_NOEVENT;
}

void CFCBullet::Late_Update(void)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// 화면 밖
	if (fScrollX - (fScrollX + m_tInfo.fX) > fScrollX ||
		fScrollX - (fScrollX + m_tInfo.fX) < fScrollX - WINCX ||
		fScrollY - (fScrollY + m_tInfo.fY) > fScrollY) {
		if (CPlayerState::m_iBltCount < 0) CPlayerState::m_iBltCount = 0;
		m_bDead = true;
	}
	
	if (m_bRight) {
		m_pFrameKey = L"FCBulletR";
		__super::Motion_FrameR(m_iImgPosX);
	}
	else {
		m_pFrameKey = L"FCBulletL";
		__super::Motion_FrameL(m_iImgPosX);
	}

	if (!m_bReflect) {
		m_tInfo.fX += m_fSpeed * (m_fAngle * sin(PI / 180));
	}
	else {
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
	}

}

void CFCBullet::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

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

void CFCBullet::Release(void)
{
}
