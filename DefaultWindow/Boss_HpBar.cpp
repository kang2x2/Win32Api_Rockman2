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
		int(m_tDrawRect.left), // ������� x��ġ�� ��ǥ
		m_tDrawRect.top, // ���� ���� y��ġ�� ��ǥ)
		22, // ���� ���� ���� ����
		160, // ���� ���� ���� ����
		hMemDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		0,		// ��Ʈ���� ����� ���� y��ǥ
		22, // ������ ��Ʈ���� ���� ������
		160,// ������ ��Ʈ���� ���� ������
		RGB(255, 255, 255)); //�����ϰ��� �ϴ� ����

	for (auto& iter : m_BossHpList) {
		iter->Render(hDC);
	}
}

void CBoss_HpBar::Release()
{
	for_each(m_BossHpList.begin(), m_BossHpList.end(), CDeleteObj());
	m_BossHpList.clear();
}


