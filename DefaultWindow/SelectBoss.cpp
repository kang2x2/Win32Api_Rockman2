#include "stdafx.h"
#include "SelectBoss.h"

#include "BmpMgr.h"
#include "SoundMgr.h"
#include "AbstractFactory.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CSelectBoss::CSelectBoss()
{
}


CSelectBoss::~CSelectBoss()
{
}

void CSelectBoss::Initialize(void)
{
	CSoundMgr::Get_Instance()->PlayBGM(L"y2mate.com - Mega Man 2 Music  Stage Select NES.wav", 1.0f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/StageSelect/StageSelect.bmp", L"SelectBoss");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/StageSelect/SelectPoint.bmp", L"SelectPoint");

	m_tBgFrame.iFrameStartX = 0;
	m_tBgFrame.iFrameEndX = 1;
	m_tBgFrame.dwSpeed = 100;
	m_tBgFrame.dwTime = GetTickCount();

	m_tPtFrame.iFrameStartX = 0;
	m_tPtFrame.iFrameEndX = 1;
	m_tPtFrame.dwSpeed = 100;
	m_tPtFrame.dwTime = GetTickCount();

	m_iSelectAry[1][1] = 1;
	m_bSuccesMove = false;
	m_bSelect = false;
	m_iWaitTime = 0;
}

int CSelectBoss::Update(void)
{
	if (m_bSuccesMove) {
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"CursorMove.wav", SOUND_EFFECT, 0.4f);
	}

	m_bSuccesMove = false;

	// 배경
	if (m_bSelect && m_iWaitTime > GetTickCount()) {
		if (m_tBgFrame.dwTime + m_tBgFrame.dwSpeed < GetTickCount())
		{
			++m_tBgFrame.iFrameStartX;

			if (m_tBgFrame.iFrameStartX > m_tBgFrame.iFrameEndX)
				m_tBgFrame.iFrameStartX = 0;
			m_tBgFrame.dwTime = GetTickCount();
		}
	}
	// 다음 씬 전환
	if (m_bSelect && m_iWaitTime < GetTickCount()) {
		// 요거 해줘야 다음 씬 이니셜라이져에서 효과음 낼 수 있다.
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);

		CSceneMgr::Get_Instance()->Scene_Change(SC_BOSS_INTRO);
	}
	
	// 셀렉트 포인터 
	if (m_tPtFrame.dwTime + m_tPtFrame.dwSpeed < GetTickCount())
	{
		++m_tPtFrame.iFrameStartX;

		if (m_tPtFrame.iFrameStartX > m_tPtFrame.iFrameEndX)
			m_tPtFrame.iFrameStartX = 0;
		m_tPtFrame.dwTime = GetTickCount();
	}

	return 0;
}

void CSelectBoss::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN)) {
		//  에어맨을 골랐을때만
		if (m_iSelectAry[0][1] == 1) {
			CSoundMgr::Get_Instance()->StopAll();
			CSoundMgr::Get_Instance()->PlaySound(L"TitileToGame.wav", SOUND_EFFECT, 0.8f);
			m_bSelect = true;
			m_iWaitTime = (float)(GetTickCount() + 1500);
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT)) {
		for (size_t i = 0; i < 3; ++i) {
			for (size_t j = 0; j < 3; ++j) {
				if (m_iSelectAry[i][j] == 1) {
					if (j < 2) {
						int temp = m_iSelectAry[i][j];
						m_iSelectAry[i][j] = 0;
						m_iSelectAry[i][j + 1] = temp;
						m_bSuccesMove = true;
						break;
					}
				}
			}
			if (m_bSuccesMove) break;
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT)) {
		for (size_t i = 0; i < 3; ++i) {
			for (size_t j = 0; j < 3; ++j) {
				if (m_iSelectAry[i][j] == 1) {
					if (j > 0) {
						int temp = m_iSelectAry[i][j];
						m_iSelectAry[i][j] = 0;
						m_iSelectAry[i][j - 1] = temp;
						m_bSuccesMove = true;
						break;
					}
				}
			}
			if (m_bSuccesMove) break;
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP)) {
		for (size_t i = 0; i < 3; ++i) {
			for (size_t j = 0; j < 3; ++j) {
				if (m_iSelectAry[i][j] == 1) {
					if (i > 0) {
						int temp = m_iSelectAry[i][j];
						m_iSelectAry[i][j] = 0;
						m_iSelectAry[i - 1][j] = temp;
						m_bSuccesMove = true;
						break;
					}
				}
			}
			if (m_bSuccesMove) break;
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN)) {
		for (size_t i = 0; i < 3; ++i) {
			for (size_t j = 0; j < 3; ++j) {
				if (m_iSelectAry[i][j] == 1) {
					if (i < 2) {
						int temp = m_iSelectAry[i][j];
						m_iSelectAry[i][j] = 0;
						m_iSelectAry[i + 1][j] = temp;
						m_bSuccesMove = true;
						break;
					}
				}
			}
			if (m_bSuccesMove) break;
		}
	}
}

void CSelectBoss::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SelectBoss");
	HDC		hPointDC = CBmpMgr::Get_Instance()->Find_Image(L"SelectPoint");

	GdiTransparentBlt(hDC,
		0, // 복사받을 x위치의 좌표
		0, // 복사 받을 y위치의 좌표)
		800.f, // 복사 받을 가로 길이
		600.f, // 복사 받을 세로 길이
		hMemDC,	// 복사할 비트맵 이미지 dc
		800.f * m_tBgFrame.iFrameStartX,		// 비트맵을 출력할 시작 x좌표
		0,		// 비트맵을 출력할 시작 y좌표
		800.f, // 복사할 비트맵의 가로 사이즈
		600.f,// 복사할 비트맵의 세로 사이즈
		RGB(120, 120, 120)); //제거하고자 하는 색상

	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			if (m_iSelectAry[i][j] == 1) {
				GdiTransparentBlt(hDC,
					(134 + (59 * j) + (140 * j)), // 복사받을 x위치의 좌표
					(61 + (45 * i) + (105 * i)), // 복사 받을 y위치의 좌표)
					140, // 복사 받을 가로 길이
					105, // 복사 받을 세로 길이
					hPointDC,	// 복사할 비트맵 이미지 dc
					140 * m_tPtFrame.iFrameStartX,		// 비트맵을 출력할 시작 x좌표
					0,		// 비트맵을 출력할 시작 y좌표
					140, // 복사할 비트맵의 가로 사이즈
					105,// 복사할 비트맵의 세로 사이즈
					RGB(128, 0, 128)); //제거하고자 하는 색상
			}
		}
	}

}

void CSelectBoss::Release(void)
{
}
