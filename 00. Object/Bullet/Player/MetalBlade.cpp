#include "stdafx.h"
#include "MetalBlade.h"

#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

CMetalBlade::CMetalBlade(float _fX, float _fY, float _fAngle)
{
	m_tInfo = { _fX, _fY, 40.f, 40.f };
	m_fAngle = _fAngle;
	Initialize();
}


CMetalBlade::~CMetalBlade()
{
}

void CMetalBlade::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/MetalBlade.bmp", L"MetalBlade");
	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 1;
	m_tFrame.dwSpeed = 40;
	m_tFrame.dwTime = GetTickCount();

	m_fSpeed = 7.0f;
	m_iDamage = 1;
	m_sType = "pBullet";
}

int CMetalBlade::Update(void)
{
	if (m_bDead) {
		return OBJ_DEAD;
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMetalBlade::Late_Update(void)
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

	if (!m_bReflect) {
		m_tInfo.fX += m_fSpeed * (m_fAngle * sin(PI / 180));
	}
	else {
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
	}
}

void CMetalBlade::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MetalBlade");

	GdiTransparentBlt(hDC,
		int(m_tDrawRect.left + fScrollX), // ������� x��ġ�� ��ǥ
		int(m_tDrawRect.top + fScrollY), // ���� ���� y��ġ�� ��ǥ)
		(int)m_tInfo.fCX, // ���� ���� ���� ����
		(int)m_tInfo.fCY, // ���� ���� ���� ����
		hMemDC,	// ������ ��Ʈ�� �̹��� dc
		m_tFrame.iFrameStartX * (int)m_tInfo.fCX,
		0,
		(int)m_tInfo.fCX, // ������ ��Ʈ���� ���� ������
		(int)m_tInfo.fCY,// ������ ��Ʈ���� ���� ������
		RGB(0, 91, 91)); //�����ϰ��� �ϴ� ����
}

void CMetalBlade::Release(void)
{
}
