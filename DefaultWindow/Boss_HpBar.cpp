#include "stdafx.h"
#include "Boss_HpBar.h"

#include "BmpMgr.h"
#include "Air_Man.h"

CBoss_HpBar::CBoss_HpBar(CAir_Man* _pBoss)
{
	m_pBoss = _pBoss;
	m_tDrawRect = { 201, 50, 233, 210 };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/BossEmptyHpBar.bmp", L"BossEmptyHpBar");

	for (size_t i = 0; i < m_pBoss->Get_Hp(); ++i) {
		m_BossHpList.push_back(new CBoss_HpNote(210 - (i * 7)));
	}
}


CBoss_HpBar::~CBoss_HpBar()
{
	Release();
}

void CBoss_HpBar::Update()
{
	for (size_t i = 0; i < m_pBoss->Get_Hp(); ++i) {
		m_BossHpList.push_back(new CBoss_HpNote(210 - (i * 8)));
	}
}

void CBoss_HpBar::Set_HpBar()
{
	if (m_pBoss->Get_Hp() >= 0) {
		Release();
		Update();
	}
}


void CBoss_HpBar::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BossEmptyHpBar");

	GdiTransparentBlt(hDC,
		int(m_tDrawRect.left), // 복사받을 x위치의 좌표
		m_tDrawRect.top, // 복사 받을 y위치의 좌표)
		22, // 복사 받을 가로 길이
		160, // 복사 받을 세로 길이
		hMemDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		0,		// 비트맵을 출력할 시작 y좌표
		22, // 복사할 비트맵의 가로 사이즈
		160,// 복사할 비트맵의 세로 사이즈
		RGB(255, 255, 255)); //제거하고자 하는 색상

	for (auto& iter : m_BossHpList) {
		iter->Render(hDC);
	}
}

void CBoss_HpBar::Release()
{
	for_each(m_BossHpList.begin(), m_BossHpList.end(), CDeleteObj());
	m_BossHpList.clear();
}


