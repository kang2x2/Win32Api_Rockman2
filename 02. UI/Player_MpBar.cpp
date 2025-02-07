#include "stdafx.h"
#include "Player_MpBar.h"

#include "BmpMgr.h"
#include "Player.h"

CPlayer_MpBar::CPlayer_MpBar(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
	m_tDrawRect = { 111, 50, 142, 210 };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PlayerEmptyMpBar.bmp", L"PlayerEmptyMpBar");

	if (m_pPlayer->Get_WeaponType() == WEAPON_MB) {
		for (size_t i = 0; i < m_pPlayer->Get_MetalBladeMp(); ++i) {
			m_PlayerMpList.push_back(new CPlayer_MpNote((210) - (i * 8)));
		}
	}
	else if (m_pPlayer->Get_WeaponType() == WEAPON_RS) {
		for (size_t i = 0; i < m_pPlayer->Get_ReefShieldMp(); ++i) {
			m_PlayerMpList.push_back(new CPlayer_MpNote((210) - (i * 8)));
		}
	}

}


CPlayer_MpBar::~CPlayer_MpBar()
{
	Release();
}

void CPlayer_MpBar::Update()
{
	if (m_pPlayer->Get_WeaponType() == WEAPON_MB) {
		for (size_t i = 0; i < m_pPlayer->Get_MetalBladeMp() / 2; ++i) {
			m_PlayerMpList.push_back(new CPlayer_MpNote((210) - (i * 8)));
		}
	}
	else if (m_pPlayer->Get_WeaponType() == WEAPON_RS) {
		for (size_t i = 0; i < m_pPlayer->Get_ReefShieldMp(); ++i) {
			m_PlayerMpList.push_back(new CPlayer_MpNote((210) - (i * 8)));
		}
	}
}

void CPlayer_MpBar::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerEmptyMpBar");

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

	for (auto& iter : m_PlayerMpList) {
		iter->Render(hDC);
	}
}

void CPlayer_MpBar::Release()
{
	if (!m_PlayerMpList.empty()) {
		for_each(m_PlayerMpList.begin(), m_PlayerMpList.end(), CDeleteObj());
		m_PlayerMpList.clear();
	}
}

void CPlayer_MpBar::Set_MpBar()
{
	if (m_pPlayer->Get_WeaponType() == WEAPON_MB) {
		if (m_pPlayer->Get_MetalBladeMp() >= 0) {
			Release();
			Update();
		}
	}
	else if (m_pPlayer->Get_WeaponType() == WEAPON_RS) {
		if (m_pPlayer->Get_ReefShieldMp() >= 0) {
			Release();
			Update();
		}
	}
}
