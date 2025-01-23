#include "stdafx.h"
#include "Player_MpNote.h"
#include "BmpMgr.h"

CPlayer_MpNote::CPlayer_MpNote(int _iY)
{
	m_tDrawRect = { 113, _iY - 7, 140, _iY };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PlayerMp.bmp", L"PlayerMp");
}


CPlayer_MpNote::~CPlayer_MpNote()
{
}

void CPlayer_MpNote::Render(HDC hDC)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PlayerMp.bmp", L"PlayerMp");
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerMp");

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
