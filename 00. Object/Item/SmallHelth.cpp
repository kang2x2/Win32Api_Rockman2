#include "stdafx.h"
#include "SmallHelth.h"

#include "BmpMgr.h"

CSmallHelth::CSmallHelth(INFO _info)
{
	m_tInfo = _info;
	Initialize();
}


CSmallHelth::~CSmallHelth()
{
}

void CSmallHelth::Initialize(void)
{
	// 이미지 정보
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/SmallHelth.bmp", L"SmallHelth");

	__super::Initialize();

	m_iHp = 2;
	m_sType = "HpItem";
}

int CSmallHelth::Update(void)
{
	return __super::Update();
}

void CSmallHelth::Late_Update(void)
{
	__super::Late_Update();
}

void CSmallHelth::Render(HDC hDC)
{
	__super::Render(hDC);
}

void CSmallHelth::Release(void)
{
}
