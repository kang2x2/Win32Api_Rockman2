#include "stdafx.h"
#include "Boss_HpNote.h"
#include "BmpMgr.h"

CBoss_HpNote::CBoss_HpNote(int _iY)
{
	m_tDrawRect = { 201, _iY - 7, 233, _iY };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/BossHp.bmp", L"BossHp");
}


CBoss_HpNote::~CBoss_HpNote()
{
}

void CBoss_HpNote::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BossHp");

	GdiTransparentBlt(hDC,
		int(m_tDrawRect.left), // ������� x��ġ�� ��ǥ
		m_tDrawRect.top, // ���� ���� y��ġ�� ��ǥ)
		18, // ���� ���� ���� ����
		5, // ���� ���� ���� ����
		hMemDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		0,		// ��Ʈ���� ����� ���� y��ǥ
		18, // ������ ��Ʈ���� ���� ������
		5,// ������ ��Ʈ���� ���� ������
		RGB(0, 0, 0)); //�����ϰ��� �ϴ� ����
}
