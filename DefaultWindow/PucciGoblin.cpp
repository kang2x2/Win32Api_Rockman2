#include "stdafx.h"
#include "PucciGoblin.h"

#include "SmallDead.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "EffectMgr.h"

CPucciGoblin::CPucciGoblin(INFO _info, float _fPointY, bool _bRight, CObj* _target)
{
	m_tInfo = _info;
	m_fPointY = _fPointY;
	m_bRight = _bRight;
	m_pTarget = _target;
	m_bTargeting = false;
	m_bDead = false;


	if (m_bRight) m_fPointX = m_tInfo.fX + 50.f;
	else m_fPointX = m_tInfo.fX - 50.f;

	Initialize();
}


CPucciGoblin::~CPucciGoblin()
{
}

void CPucciGoblin::Initialize(void)
{
	
	// �̹��� ����
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Enemy/PucciGoblin.bmp", L"PucciGoblin");
	
	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 2;
	m_tFrame.iFrameY = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
	
	// ����
	m_fSpeed = 0.3f;
	m_iDamage = 2;
	m_iHp = 1;
	m_sType = "Enemy";

	// Ÿ���� ����
	fWidth = 0.f;
	fHeight = 0.f;
	fDiagonal = 0.f;
	fRadian = 0.f;
}

int CPucciGoblin::Update(void)
{
	if (m_bDead) {
		if (!m_bWideDead) {
			CEffectMgr::Get_Instance()->Add_Effect(EFFECT_SMALL, new CSmallDead({ m_tInfo.fX, m_tInfo.fY, 50, 56 }));
			Drop_Item();
		}
		return OBJ_DEAD;
	}

	// ��ǥ x���� ���� ��������
	if (!m_bTargeting && m_bRight && m_tInfo.fX < m_fPointX) {
		m_tInfo.fX += 1.0f;
	}
	else if (!m_bTargeting && !m_bRight && m_tInfo.fX > m_fPointX) {
		m_tInfo.fX -= 1.0f;
	}
	// ��ǥ x���� ����������
	if (!m_bTargeting && m_tInfo.fX == m_fPointX) {
		// ��ǥ y���� ���� ��������
		if (!m_bTargeting && m_tInfo.fY > m_fPointY) {
			m_tInfo.fY -= 10.0f;
		}
	}
	
	// ��ǥ x,y�� ���� �� Ÿ���� ����
	if (!m_bTargeting && m_tInfo.fY == m_fPointY) {
		m_bTargeting = true;
	}

	if (m_bTargeting) {
		float	fWidth = 0.f, fHeight = 0.f, fDiagonal = 0.f;
		float	fRadian = 0.f;

		fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
		fRadian = acosf(fWidth / fDiagonal);

		/*if (m_pTarget->Get_Info().fY > m_tInfo.fY)
		fRadian = (2 * PI) - fRadian;*/

		// Radian To degree
		m_fAngle = fRadian * 180.f / PI;

		if (m_pTarget->Get_Info().fY > m_tInfo.fY)
			m_fAngle *= -1.f;

		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
	}
	

	__super::Update_Rect();
	__super::Update_Creature_Rect();

	return OBJ_NOEVENT;
}

void CPucciGoblin::Late_Update(void)
{
	if (m_iHp <= 0) m_bDead = true;

	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	// ȭ�� ��
	if (fScrollX - (fScrollX + m_tInfo.fX) > fScrollX ||
		fScrollX - (fScrollX + m_tInfo.fX) < fScrollX - WINCX) {
		m_bWideDead = true;
		m_bDead = true;
	}

	// �ִϸ��̼�
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStartX;
		if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX) {
			m_tFrame.iFrameStartX = 0;
		}
		m_tFrame.dwTime = GetTickCount();
	}
}

void CPucciGoblin::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PucciGoblin");

	//Rectangle(hDC, m_tDrawRect.left + fScrollX,
	//	m_tDrawRect.top + fScrollY,
	//	m_tDrawRect.right + fScrollX,
	//	m_tDrawRect.bottom + fScrollY);

	// ���� ���¶�� �׽� ��ο�
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

void CPucciGoblin::Release(void)
{
}
