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
		0, // ������� x��ġ�� ��ǥ
		0, // ���� ���� y��ġ�� ��ǥ)
		800.f, // ���� ���� ���� ����
		600.f, // ���� ���� ���� ����
		hMemDC,	// ������ ��Ʈ�� �̹��� dc
		800.f * m_tFrame.iFrameStartX,		// ��Ʈ���� ����� ���� x��ǥ
		m_tFrame.iFrameY * 600.f,		// ��Ʈ���� ����� ���� y��ǥ
		800.f, // ������ ��Ʈ���� ���� ������
		600.f,// ������ ��Ʈ���� ���� ������
		RGB(123, 123, 123)); //�����ϰ��� �ϴ� ����
}

void CLogo::Release(void)
{
}
