#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"

#include "SoundMgr.h"
#include "ObjMgr.h"

CMyMenu::CMyMenu()
{
}

CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Intro/IntroBack.bmp", L"IntroBack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Intro/MegamanLogo.bmp", L"Logo");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Intro/PressKey.bmp", L"PressKey");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Intro/IntroRockman.bmp", L"IntroRockman");
	CSoundMgr::Get_Instance()->PlayBGM(L"Opening.wav", 0.4f);

	m_iNum = 0;
	m_fScrollSpeed = 0.f;
	m_iWaitTime = 0;
	m_fTpSpeed = 0.f;

	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 1;
	m_tFrame.iFrameY = 0;
	m_tFrame.iFrameEndY = 1;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = GetTickCount();

	CScrollMgr::Get_Instance()->Set_ScrollY(-3450.f);
}

int CMyMenu::Update(void)
{
	m_fScrollSpeed += 0.002f;

	if (m_iNum < 2 && CKeyMgr::Get_Instance()->Key_Down(VK_SPACE)) {
		CScrollMgr::Get_Instance()->Set_ScrollY_Title(0);
		m_iNum = 2;
	}

	// 스크롤 이동 중
	if (CScrollMgr::Get_Instance()->Get_ScrollY() < 0) {
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fScrollSpeed);
	}
	// 스크롤 이동 끝
	if (m_iNum == 0 && CScrollMgr::Get_Instance()->Get_ScrollY() >= 0) {
		m_iNum = 1;
	}
	// 타이틀 상태로 전환하기 전 대기 시간 정해주기
	if (m_iNum == 1) {
		m_iWaitTime = GetTickCount() + 1000;
		m_iNum = 2;
	}
	// 타이틀 상태 전환
	if (m_iNum == 2) {
		if (m_iWaitTime < GetTickCount()) {
			CSoundMgr::Get_Instance()->StopAll();
			CSoundMgr::Get_Instance()->PlayBGM(L"Title.wav", 0.4f);
			m_iNum = 3;
		}
	}
	// 게임 시작.
	if (m_iNum == 3) {
		if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN)) {
			CSoundMgr::Get_Instance()->StopAll();
			CSoundMgr::Get_Instance()->PlaySound(L"TitileToGame.wav", SOUND_EFFECT, 0.8f);
			m_tFrame.iFrameStartX = 0;
			m_tFrame.iFrameEndX = 7;
			m_tFrame.iFrameY = 1;
			m_iNum = 4;
		}
	}
	// 텔레포트 연출
	if (m_iNum == 6) {
		m_fTpSpeed += 10.0f;
		if (m_fTpSpeed >= 600) {
			CSceneMgr::Get_Instance()->Scene_Change(SC_SELECT_BOSS);
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('E')) {
		CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT);
		return 0;
	}

	return 0;
}

void CMyMenu::Late_Update(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		// 일반 머리 흩날리는 프레임
		if (m_iNum < 4) {
			++m_tFrame.iFrameStartX;

			if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX)
				m_tFrame.iFrameStartX = 0;
		}
		// 출동 준비 프레임
		if (m_iNum == 4) {
			++m_tFrame.iFrameStartX;

			if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX) {
				m_iWaitTime = GetTickCount() + 1000;
				m_iNum = 5;
				m_tFrame.iFrameStartX = m_tFrame.iFrameEndX;
			}
		}
		// 텔레포트 프레임
		if (m_iNum == 5) {
			if (m_iWaitTime < GetTickCount()) {
				m_iNum = 6;
				m_tFrame.iFrameStartX = 0;
				m_tFrame.iFrameEndX = 2;
				m_tFrame.iFrameY = 2;
			}
		}
		if (m_iNum == 6) {
			++m_tFrame.iFrameStartX;
			if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX) {
				m_tFrame.iFrameStartX = m_tFrame.iFrameEndX;
			}
		}

		m_tFrame.dwTime = GetTickCount();
	}
}

void CMyMenu::Render(HDC hDC)
{
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// 배경
	HDC		hBackgroundDC = CBmpMgr::Get_Instance()->Find_Image(L"IntroBack");
	BitBlt(hDC, 0, (int)fScrollY, 800, 4050, hBackgroundDC, 0, 0, SRCCOPY);
	// 로고
	HDC		hLogoDC = CBmpMgr::Get_Instance()->Find_Image(L"Logo");
	if (m_iNum >= 3) { // 사운드 변경 후에만
		GdiTransparentBlt(hDC, 100, int(50 + fScrollY), 565, 300,
			hLogoDC, 0, 0, 565, 300, RGB(128, 0, 128));
	}
	// 프레스 키
	HDC		hPressKeyDC = CBmpMgr::Get_Instance()->Find_Image(L"PressKey");
	if (m_iNum == 3) {
		BitBlt(hDC, 290, 450, 178, 20, hPressKeyDC, 0, 0, SRCCOPY);
	}
	// 록맨
	HDC		hRockmanDC = CBmpMgr::Get_Instance()->Find_Image(L"IntroRockman");
	GdiTransparentBlt(hDC, 585, int(375 + fScrollY) - m_fTpSpeed, 75, 75,
		hRockmanDC, 
		m_tFrame.iFrameStartX * 75,
		m_tFrame.iFrameY * 75,
		75, 75, RGB(128, 0, 128));
	
}

void CMyMenu::Release(void)
{
}

