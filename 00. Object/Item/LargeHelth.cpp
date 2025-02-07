#include "stdafx.h"
#include "LargeHelth.h"

#include "BmpMgr.h"

CLargeHelth::CLargeHelth(INFO _info)
{
	m_tInfo = _info;
	Initialize();
}


CLargeHelth::~CLargeHelth()
{
}

void CLargeHelth::Initialize(void)
{
	// 이미지 정보
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/LargeHelth.bmp", L"LargeHelth");

	__super::Initialize();

	m_iHp = 6;
	m_sType = "HpItem";
}

int CLargeHelth::Update(void)
{
	return __super::Update();
}

void CLargeHelth::Late_Update(void)
{
	__super::Late_Update();
}

void CLargeHelth::Render(HDC hDC)
{
	__super::Render(hDC);
}

void CLargeHelth::Release(void)
{
}
