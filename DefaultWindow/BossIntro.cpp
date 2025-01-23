#include "stdafx.h"
#include "BossIntro.h"

#include "BmpMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"

CBossIntro::CBossIntro()
{
}


CBossIntro::~CBossIntro()
{
}

void CBossIntro::Initialize(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"Game Start.wav", SOUND_EFFECT, 0.8f);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/StageSelect/BossIntroBg.bmp", L"BossIntroBg");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/StageSelect/AirManL.bmp", L"BossIntro");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/StageSelect/AirManFont.bmp", L"BossFont");

	m_iChangWaitTime = GetTickCount() + 8000;

	m_tBgFrame.iFrameStartX = 0;
	m_tBgFrame.iFrameEndX = 1;
	m_tBgFrame.dwSpeed = 50;
	m_tBgFrame.dwTime = GetTickCount();

	m_tAirmanFrame.iFrameStartX = 0;
	m_tAirmanFrame.iFrameEndX = 1;
	m_tAirmanFrame.dwSpeed = 200;
	m_tAirmanFrame.dwTime = GetTickCount();
	
	m_tFontFrame.iFrameY = -1;
	m_tFontFrame.iFrameEndY = 5;
	m_tFontFrame.dwSpeed = 200;
	m_tFontFrame.dwTime = GetTickCount();

	m_fAirmanPosX = -104;

	m_iNum = 0;
}

int CBossIntro::Update(void)
{	
	if (m_iChangWaitTime < GetTickCount()) {
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_AIRMAN);
	}

	// 에어맨 이동
	if (m_fAirmanPosX < 350.f) {
		m_fAirmanPosX += 10.0f;
	} 

	// 에어맨 이동 완료
	if (m_iNum == 0 && m_fAirmanPosX >= 350.f) {
		m_iWaitTime = GetTickCount() + 1000;
		m_iNum = 1;
	}

	// 에어맨 모션 변경 및 폰트 애니메이션 트리거 on
	if (m_iNum == 1 && m_iWaitTime < GetTickCount()) {
		m_tAirmanFrame.iFrameStartX = 2;
		m_iNum = 2;
	}

	// 배경 애니메이션
	if (m_tBgFrame.dwTime + m_tBgFrame.dwSpeed < GetTickCount())
	{
		++m_tBgFrame.iFrameStartX;
		if (m_tBgFrame.iFrameStartX > m_tBgFrame.iFrameEndX)
			m_tBgFrame.iFrameStartX = 0;

		m_tBgFrame.dwTime = GetTickCount();
	}

	// 에어맨 애니메이션
	if (m_iNum == 1) {
		if (m_tAirmanFrame.dwTime + m_tAirmanFrame.dwSpeed < GetTickCount())
		{
			++m_tAirmanFrame.iFrameStartX;
			if (m_tAirmanFrame.iFrameStartX > m_tAirmanFrame.iFrameEndX)
				m_tAirmanFrame.iFrameStartX = 0;

			m_tAirmanFrame.dwTime = GetTickCount();
		}
	}

	// 폰트 애니메이션
	if (m_iNum == 2) {
		if (m_tFontFrame.dwTime + m_tFontFrame.dwSpeed < GetTickCount())
		{
			++m_tFontFrame.iFrameY;
			if (m_tFontFrame.iFrameY > m_tFontFrame.iFrameEndY)
				m_tFontFrame.iFrameY = m_tFontFrame.iFrameEndY;

			m_tFontFrame.dwTime = GetTickCount();
		}
	}

	return 0;
}

void CBossIntro::Late_Update(void)
{
}

void CBossIntro::Render(HDC hDC)
{
	// 배경
	HDC		hIntroBgDC = CBmpMgr::Get_Instance()->Find_Image(L"BossIntroBg");
	BitBlt(hDC, 0, 0, 800, 600, hIntroBgDC, m_tBgFrame.iFrameStartX * 800, 0, SRCCOPY);

	// 에어맨
	HDC		hBossDC = CBmpMgr::Get_Instance()->Find_Image(L"BossIntro");
	GdiTransparentBlt(hDC,
		(int)m_fAirmanPosX, 220, 104, 83, hBossDC,	
		104 * (m_tAirmanFrame.iFrameStartX),
		0, 104, 83, RGB(128, 0, 128));

	// 폰트
	if (m_iNum == 2) {
		HDC		hFontDC = CBmpMgr::Get_Instance()->Find_Image(L"BossFont");
		GdiTransparentBlt(hDC,
			340, 310, 152, 18, hFontDC,
			0, 18 * m_tFontFrame.iFrameY, 152, 18, RGB(128, 0, 128));
	}
	
}

void CBossIntro::Release(void)
{
}
