#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"


CLogo::CLogo()
{
}


CLogo::~CLogo()
{
}

void CLogo::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Intro/Intro.bmp", L"Intro");

	m_iNum = 0;
	m_iWaitTile = 500;

	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 3;
	m_tFrame.iFrameY = 0;
	m_tFrame.dwSpeed = 400;
	m_tFrame.dwTime = GetTickCount();
}

int CLogo::Update(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		if (m_iNum == 0) {
			++m_tFrame.iFrameStartX;
			if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX) {
				m_iWaitTile = GetTickCount() + 1000;
				m_iNum = 1;
			}
		}
		else if (m_iNum == 1) {
			if (m_iWaitTile < GetTickCount()) {
				--m_tFrame.iFrameStartX;
				if (m_tFrame.iFrameStartX < 0) {
					m_iWaitTile = GetTickCount() + 1000;
					m_tFrame.iFrameY = 1;
					m_iNum = 2;
				}
			}
		}
		else if (m_iNum == 2) {
			if (m_iWaitTile < GetTickCount()) {
				++m_tFrame.iFrameStartX;
				if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX) {
					m_iWaitTile = GetTickCount() + 1000;
					m_iNum = 3;
				}
			}
		}
		else if (m_iNum == 3) {
			if (m_iWaitTile < GetTickCount()) {
				--m_tFrame.iFrameStartX;
				if (m_tFrame.iFrameStartX < 0) {
					m_iWaitTile = GetTickCount() + 1000;
					m_iNum = 4;
				}
			}
		}
		else if (m_iNum == 4) {
			if (m_iWaitTile < GetTickCount()) {
				CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
			}
		}

		m_tFrame.dwTime = GetTickCount();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		// CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_AIRMAN);
		return 0;
	}
	return 0;
}

void CLogo::Late_Update(void)
{
}

void CLogo::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Intro");

	GdiTransparentBlt(hDC,
		0, // 복사받을 x위치의 좌표
		0, // 복사 받을 y위치의 좌표)
		800.f, // 복사 받을 가로 길이
		600.f, // 복사 받을 세로 길이
		hMemDC,	// 복사할 비트맵 이미지 dc
		800.f * m_tFrame.iFrameStartX,		// 비트맵을 출력할 시작 x좌표
		m_tFrame.iFrameY * 600.f,		// 비트맵을 출력할 시작 y좌표
		800.f, // 복사할 비트맵의 가로 사이즈
		600.f,// 복사할 비트맵의 세로 사이즈
		RGB(123, 123, 123)); //제거하고자 하는 색상
}

void CLogo::Release(void)
{
}
