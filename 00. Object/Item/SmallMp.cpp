#include "stdafx.h"
#include "SmallMp.h"

#include "BmpMgr.h"

CSmallMp::CSmallMp(INFO _info)
{
	m_tInfo = _info;
	Initialize();
}


CSmallMp::~CSmallMp()
{
}

void CSmallMp::Initialize(void)
{
	// 이미지 정보
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/SmallMp.bmp", L"SmallMp");

	__super::Initialize();

	m_iHp = 2;
	m_sType = "MpItem";
}

int CSmallMp::Update(void)
{
	return __super::Update();
}

void CSmallMp::Late_Update(void)
{
	__super::Late_Update();
}

void CSmallMp::Render(HDC hDC)
{
	__super::Render(hDC);
}

void CSmallMp::Release(void)
{
}
