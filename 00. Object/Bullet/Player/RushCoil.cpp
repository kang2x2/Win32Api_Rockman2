#include "stdafx.h"
#include "RushCoil.h"

#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

CRushCoil::CRushCoil(INFO _info, float _fDestY) : m_iDuration(0), m_bState(RUSH_COME)
{
	m_tInfo = _info;
	m_fDestY = _fDestY;
	Initialize();
}


CRushCoil::~CRushCoil()
{
}

void CRushCoil::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Rush/RushTp.bmp", L"RushTp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Rush/RushCoil.bmp", L"RushCoil");
	
	m_pFrameKey = L"RushTp";
	
	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 0;
	m_tFrame.dwSpeed = 40;
	m_tFrame.dwTime = GetTickCount();

	m_fSpeed = 10.0f;
	m_sType = "RushCoil";
}

int CRushCoil::Update(void)
{
	if (m_bDead) {
		return OBJ_DEAD;
	}

	// ȣ�� ����
	if (m_bState == RUSH_COME && m_tInfo.fY <= m_fDestY) {
		cout << m_tInfo.fY << endl;
		cout << m_fDestY << endl;
		m_tInfo.fY += m_fSpeed;
	}

	// ���� ����
	if (m_bState == RUSH_COME && m_tInfo.fY >= m_fDestY) {
		m_iDuration = GetTickCount() + 4000;
		m_bState = RUSH_GROUND;
		m_tFrame.iFrameEndX = 2;
	}

	// ��� ����
	if (m_bState == RUSH_IDLE) {
		m_tFrame.dwSpeed = 200;
		if (m_iDuration < GetTickCount()) {
			m_bState = RUSH_BACK;
		}
	}

	if (m_bState == RUSH_COIL) {
		m_tFrame.iFrameStartX = 0;
		if (GetTickCount() % 1000 == 0) {
			m_bState = RUSH_BACK;
		}
	}

	// ���� ����
	if (m_bState == RUSH_BACK) {
		m_pFrameKey = L"RushTp";
		m_tFrame.iFrameStartX = 0;
		m_tInfo.fY -= m_fSpeed;
		if (fabs(m_fDestY - m_tInfo.fY) >= 500.f) {
			m_bDead = true;
		}
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CRushCoil::Late_Update(void)
{
	if (m_bState == RUSH_GROUND) {
		if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStartX;

			if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX) {
				m_bState = RUSH_IDLE;
				m_pFrameKey = L"RushCoil";
				m_tFrame.iFrameStartX = 2;
				m_tFrame.iFrameEndX = 1;
			}
			m_tFrame.dwTime = GetTickCount();
		}
	}

	if (m_bState == RUSH_IDLE) {
		if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
		{
			--m_tFrame.iFrameStartX;

			if (m_tFrame.iFrameStartX < m_tFrame.iFrameEndX) {
				m_tFrame.iFrameStartX = 2;
			}
			m_tFrame.dwTime = GetTickCount();
		}
	}
	
}

void CRushCoil::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

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
		RGB(128, 0, 128)); //�����ϰ��� �ϴ� ����
}

void CRushCoil::Release(void)
{
}
