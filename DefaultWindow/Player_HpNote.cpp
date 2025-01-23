#include "stdafx.h"
#include "Player_HpNote.h"
#include "BmpMgr.h"


CPlayer_HpNote::CPlayer_HpNote(int _iY)
{
	m_tDrawRect = { 81, _iY - 7, 99, _iY };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PlayerHp.bmp", L"PlayerHp");
}


CPlayer_HpNote::~CPlayer_HpNote()
{
}

void CPlayer_HpNote::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerHp");

	GdiTransparentBlt(hDC,
		int(m_tDrawRect.left), // ������� x��ġ�� ��ǥ
		m_tDrawRect.top, // ���� ���� y��ġ�� ��ǥ)
		18.f, // ���� ���� ���� ����
		5.f, // ���� ���� ���� ����
		hMemDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		0,		// ��Ʈ���� ����� ���� y��ǥ
		18.f, // ������ ��Ʈ���� ���� ������
		5.f,// ������ ��Ʈ���� ���� ������
		RGB(0, 0, 0)); //�����ϰ��� �ϴ� ����
}
