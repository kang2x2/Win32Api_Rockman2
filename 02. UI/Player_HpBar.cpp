#include "stdafx.h"
#include "Player_HpBar.h"

#include "BmpMgr.h"
#include "Player.h"

CPlayer_HpBar::CPlayer_HpBar(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
	m_tDrawRect = { 79, 50, 101, 210 };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PlayerEmptyHpBar.bmp", L"PlayerEmptyHpBar");

	for (size_t i = 0; i < m_pPlayer->Get_Hp(); ++i) {
		m_PlayerHpList.push_back(new CPlayer_HpNote((210) - (i * 8)));
	}
}


CPlayer_HpBar::~CPlayer_HpBar()
{
	Release();
}

void CPlayer_HpBar::Update()
{
	for (size_t i = 0; i < m_pPlayer->Get_Hp(); ++i) {
		m_PlayerHpList.push_back(new CPlayer_HpNote((210) - (i * 8)));
	}
}

void CPlayer_HpBar::Set_HpBar()
{
	if (m_pPlayer->Get_Hp() >= 0) {
		Release();
		Update();
	}
}

void CPlayer_HpBar::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerEmptyHpBar");

	GdiTransparentBlt(hDC,
		int(m_tDrawRect.left), // ������� x��ġ�� ��ǥ
		m_tDrawRect.top, // ���� ���� y��ġ�� ��ǥ)
		22.f, // ���� ���� ���� ����
		160.f, // ���� ���� ���� ����
		hMemDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		0,		// ��Ʈ���� ����� ���� y��ǥ
		22.f, // ������ ��Ʈ���� ���� ������
		160.f,// ������ ��Ʈ���� ���� ������
		RGB(255, 255, 255)); //�����ϰ��� �ϴ� ����

	for (auto& iter : m_PlayerHpList) {
		iter->Render(hDC);
	}
}

void CPlayer_HpBar::Release()
{
	for_each(m_PlayerHpList.begin(), m_PlayerHpList.end(), CDeleteObj());
	m_PlayerHpList.clear();
}

