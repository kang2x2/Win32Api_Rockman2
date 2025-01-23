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

	// ���
	if (m_bSelect && m_iWaitTime > GetTickCount()) {
		if (m_tBgFrame.dwTime + m_tBgFrame.dwSpeed < GetTickCount())
		{
			++m_tBgFrame.iFrameStartX;

			if (m_tBgFrame.iFrameStartX > m_tBgFrame.iFrameEndX)
				m_tBgFrame.iFrameStartX = 0;
			m_tBgFrame.dwTime = GetTickCount();
		}
	}
	// ���� �� ��ȯ
	if (m_bSelect && m_iWaitTime < GetTickCount()) {
		// ��� ����� ���� �� �̴ϼȶ��������� ȿ���� �� �� �ִ�.
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);

		CSceneMgr::Get_Instance()->Scene_Change(SC_BOSS_INTRO);
	}
	
	// ����Ʈ ������ 
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
		//  ������� ���������
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
		0, // ������� x��ġ�� ��ǥ
		0, // ���� ���� y��ġ�� ��ǥ)
		800.f, // ���� ���� ���� ����
		600.f, // ���� ���� ���� ����
		hMemDC,	// ������ ��Ʈ�� �̹��� dc
		800.f * m_tBgFrame.iFrameStartX,		// ��Ʈ���� ����� ���� x��ǥ
		0,		// ��Ʈ���� ����� ���� y��ǥ
		800.f, // ������ ��Ʈ���� ���� ������
		600.f,// ������ ��Ʈ���� ���� ������
		RGB(120, 120, 120)); //�����ϰ��� �ϴ� ����

	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			if (m_iSelectAry[i][j] == 1) {
				GdiTransparentBlt(hDC,
					(134 + (59 * j) + (140 * j)), // ������� x��ġ�� ��ǥ
					(61 + (45 * i) + (105 * i)), // ���� ���� y��ġ�� ��ǥ)
					140, // ���� ���� ���� ����
					105, // ���� ���� ���� ����
					hPointDC,	// ������ ��Ʈ�� �̹��� dc
					140 * m_tPtFrame.iFrameStartX,		// ��Ʈ���� ����� ���� x��ǥ
					0,		// ��Ʈ���� ����� ���� y��ǥ
					140, // ������ ��Ʈ���� ���� ������
					105,// ������ ��Ʈ���� ���� ������
					RGB(128, 0, 128)); //�����ϰ��� �ϴ� ����
			}
		}
	}

}

void CSelectBoss::Release(void)
{
}
