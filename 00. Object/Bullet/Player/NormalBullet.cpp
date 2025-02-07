#include "stdafx.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

#include "NormalBullet.h"

#include "PlayerState.h"


CNormalBullet::CNormalBullet(float _fX, float _fY, float _fAngle)
{
	m_tInfo = { _fX, _fY, 18.f, 12.f };
	m_fAngle = _fAngle;
	m_fSpeed = 5.0f;
	m_iDamage = 1;
	m_sType = "pBullet";

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/NormalBullet.bmp", L"NormalBullet");
}


CNormalBullet::~CNormalBullet()
{
}

void CNormalBullet::Initialize(void)
{
}

int CNormalBullet::Update(void)
{
	if (m_bDead) {
		CPlayerState::m_iBltCount -= 1;
		return OBJ_DEAD;
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CNormalBullet::Late_Update(void)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// ȭ�� ��
	if (fScrollX - (fScrollX + m_tInfo.fX) > fScrollX || 
		fScrollX - (fScrollX + m_tInfo.fX) < fScrollX - WINCX ||
		fScrollY - (fScrollY + m_tInfo.fY) > fScrollY) {
		if (CPlayerState::m_iBltCount < 0) CPlayerState::m_iBltCount = 0;
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
}

void CNormalBullet::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"NormalBullet");

	GdiTransparentBlt(hDC,
		int(m_tDrawRect.left + fScrollX), // ������� x��ġ�� ��ǥ
		int(m_tDrawRect.top + fScrollY), // ���� ���� y��ġ�� ��ǥ)
		(int)m_tInfo.fCX, // ���� ���� ���� ����
		(int)m_tInfo.fCY, // ���� ���� ���� ����
		hMemDC,	// ������ ��Ʈ�� �̹��� dc
		m_tFrame.iFrameStartX * (int)m_tInfo.fCX,
		m_tFrame.iFrameY * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, // ������ ��Ʈ���� ���� ������
		(int)m_tInfo.fCY,// ������ ��Ʈ���� ���� ������
		RGB(255, 255, 255)); //�����ϰ��� �ϴ� ����
}

void CNormalBullet::Release(void)
{
}


