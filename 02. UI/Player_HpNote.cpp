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
		int(m_tDrawRect.left), // 복사받을 x위치의 좌표
		m_tDrawRect.top, // 복사 받을 y위치의 좌표)
		18.f, // 복사 받을 가로 길이
		5.f, // 복사 받을 세로 길이
		hMemDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		0,		// 비트맵을 출력할 시작 y좌표
		18.f, // 복사할 비트맵의 가로 사이즈
		5.f,// 복사할 비트맵의 세로 사이즈
		RGB(0, 0, 0)); //제거하고자 하는 색상
}
