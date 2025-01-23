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
		int(m_tDrawRect.left), // 복사받을 x위치의 좌표
		m_tDrawRect.top, // 복사 받을 y위치의 좌표)
		22.f, // 복사 받을 가로 길이
		160.f, // 복사 받을 세로 길이
		hMemDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		0,		// 비트맵을 출력할 시작 y좌표
		22.f, // 복사할 비트맵의 가로 사이즈
		160.f,// 복사할 비트맵의 세로 사이즈
		RGB(255, 255, 255)); //제거하고자 하는 색상

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
