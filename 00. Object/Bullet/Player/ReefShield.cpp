#include "stdafx.h"
#include "ReefShield.h"

#include "Player.h"

#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

CReefShield::CReefShield(CObj* _pPlayer) : m_bFire(false)
{
	m_pPlayer = _pPlayer;
	m_tInfo = { m_pPlayer->Get_Info().fX, m_pPlayer->Get_Info().fY, 105, 99};
	Initialize();
}


CReefShield::~CReefShield()
{
}

void CReefShield::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/ReefShield.bmp", L"ReefShield");

	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 3;
	m_tFrame.dwSpeed = 40;
	m_tFrame.dwTime = GetTickCount();

	m_fSpeed = 4.0f;
	m_iDamage = 3;
	m_fAngle = 0.f;
	m_sType = "pReefShield";
}

int CReefShield::Update(void)
{
	if (m_bDead) {
		dynamic_cast<CPlayer*>(m_pPlayer)->Set_ReefShield(false);
		return OBJ_DEAD;
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CReefShield::Late_Update(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStartX;

		if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX)
			m_tFrame.iFrameStartX = 0;

		m_tFrame.dwTime = GetTickCount();
	}

	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// ȭ�� ��
	if (fScrollX - (fScrollX + m_tInfo.fX) > fScrollX ||
		fScrollX - (fScrollX + m_tInfo.fX) < fScrollX - WINCX ||
		fScrollY - (fScrollY + m_tInfo.fY) > fScrollY ||
		m_tInfo.fY > 1800.f) {
		m_bDead = true;
	}


	if (m_fAngle == -90.f) {
		m_bRight = false;
	}
	if (m_fAngle == 90.f) {
		m_bRight = true;
	}

	if (!m_bFire) {
		m_tInfo.fX = m_pPlayer->Get_Info().fX;
		m_tInfo.fY = m_pPlayer->Get_Info().fY;
	}
	else {
		if (!m_bReflect) {
			m_tInfo.fX += m_fSpeed * (m_fAngle * sin(PI / 180));
		}
		else {
			m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
			m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
		}
	}
}

void CReefShield::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ReefShield");

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
		RGB(128, 0, 128)); //�����ϰ��� �ϴ� ����
}

void CReefShield::Release(void)
{
}
