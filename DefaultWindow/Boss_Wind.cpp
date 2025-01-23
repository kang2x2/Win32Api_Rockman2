#include "stdafx.h"
#include "Boss_Wind.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"


extern float m_fPushPower;
CBoss_Wind::CBoss_Wind(float _fX, float _fY, float _fDestX, float _fAngle, bool _bRight)
{
	m_tInfo = { _fX, _fY, 40.f, 40.f };
	
	m_DestPosX = _fDestX;
	m_fAngle = _fAngle;
	m_fSpeed = 20.0f;
	m_bRight = _bRight;
	m_iDamage = 3;
	m_sType = "bossBullet";
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/AirmanBulletR.bmp", L"BossBulletR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/AirmanBulletL.bmp", L"BossBulletL");


	m_iImgPosX = 0;
	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 2;
	m_tFrame.iFrameY = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
}


CBoss_Wind::~CBoss_Wind()
{
}

void CBoss_Wind::Initialize(void)
{
}

int CBoss_Wind::Update(void)
{
	if (m_bDead) return OBJ_DEAD;

	m_tInfo.fX -= m_fPushPower;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CBoss_Wind::Late_Update(void)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// 화면 밖
	if (fScrollX - (fScrollX + m_tInfo.fX) > fScrollX ||
		fScrollX - (fScrollX + m_tInfo.fX) < fScrollX - WINCX ||
		fScrollY - (fScrollY + m_tInfo.fY) > fScrollY || 
		m_tInfo.fY > 1800.f) {
		m_bDead = true;
	}


	if (m_bReflect) {
		m_tInfo.fX -= m_fSpeed * cosf(m_fAngle * PI / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
	}

	if (!m_bRight) {
		m_pFrameKey = L"BossBulletL";
		m_iImgPosX = 2;
		m_tFrame.iFrameEndX = 0;
		__super::Motion_FrameL(m_iImgPosX);
		if (!m_bReflect && m_tInfo.fX > m_DestPosX) {
			m_tInfo.fX -= m_fSpeed * cosf(m_fAngle * PI / 180.f);
			m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
		}
	}
	if (m_bRight) {
		m_pFrameKey = L"BossBulletR";
		m_iImgPosX = 0;
		m_tFrame.iFrameEndX = 2;
		__super::Motion_FrameR(m_iImgPosX);
		if (!m_bReflect && m_tInfo.fX < m_DestPosX) {
			m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
			m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
		}
	}
}

void CBoss_Wind::Render(HDC hDC)
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
		RGB(128, 0, 128)); //제거하고자 하는 색상

	//Rectangle(hDC, m_tDrawRect.left + fScrollX,
	//	m_tDrawRect.top, 
	//	m_tDrawRect.right + fScrollX, 
	//	m_tDrawRect.bottom);
}

void CBoss_Wind::Release(void)
{
}
