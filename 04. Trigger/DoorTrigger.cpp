#include "stdafx.h"
#include "DoorTrigger.h"

#include "BmpMgr.h"
#include "SoundMgr.h"
#include "ScrollMgr.h"

CDoorTrigger::CDoorTrigger(INFO _myInfo, bool _bRight, int _scrollPos, int _leftRockPos)
{
	if (_bRight) m_sType = "BossDoor";
	if (!_bRight) m_sType = "MoveLeftX";
	m_iScrollPos = _scrollPos;
	m_tInfo = _myInfo;
	m_iTriggerNum = 0;
	m_iDoorTime = 0;
	m_LeftRockPos = _leftRockPos;
	Initialize();
}


CDoorTrigger::~CDoorTrigger()
{
}

void CDoorTrigger::Initialize(void)
{
	// 이미지 정보
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/BossDoor.bmp", L"BossDoor");

	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 0;
	m_tFrame.iFrameY = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

}

int CDoorTrigger::Update(void)
{
	if (m_bDead) return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CDoorTrigger::Late_Update(void)
{
	if (m_iTriggerNum == 1) {
		if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
		{
			CSoundMgr::Get_Instance()->PlaySound(L"30 - BossGate.wav", SOUND_EFFECT, 1.0f);
			++m_tFrame.iFrameStartX;
			if (m_tFrame.iFrameStartX > 4) {
				m_tFrame.iFrameStartX = 4; 
				m_iDoorTime = GetTickCount() + 1500;
				m_iTriggerNum = 2;
			}
			m_tFrame.dwTime = GetTickCount();
		}
	}
	if (m_iTriggerNum == 2) {
		if (m_iDoorTime < GetTickCount()) {
			if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
			{
				CSoundMgr::Get_Instance()->PlaySound(L"30 - BossGate.wav", SOUND_EFFECT, 1.0f);
				--m_tFrame.iFrameStartX;
				if (m_tFrame.iFrameStartX < 0) {
					m_tFrame.iFrameStartX = 0;
					m_iTriggerNum = 3;
				}
				m_tFrame.dwTime = GetTickCount();
			}
		}
	}
}

void CDoorTrigger::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BossDoor");

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

void CDoorTrigger::Release(void)
{
}
