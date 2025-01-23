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

	for (auto& iter : m_PlayerHpList) {
		iter->Render(hDC);
	}
}

void CPlayer_HpBar::Release()
{
	for_each(m_PlayerHpList.begin(), m_PlayerHpList.end(), CDeleteObj());
	m_PlayerHpList.clear();
}

