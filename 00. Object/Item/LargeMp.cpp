#include "stdafx.h"
#include "LargeMp.h"

#include "BmpMgr.h"

CLargeMp::CLargeMp(INFO _info)
{
	m_tInfo = _info;
	Initialize();
}


CLargeMp::~CLargeMp()
{
}

void CLargeMp::Initialize(void)
{
	// 이미지 정보
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/LargeMp.bmp", L"LargeMp");

	__super::Initialize();

	m_iHp = 6;
	m_sType = "MpItem";

}

int CLargeMp::Update(void)
{
	return __super::Update();
}

void CLargeMp::Late_Update(void)
{
	__super::Late_Update();
}

void CLargeMp::Render(HDC hDC)
{
	__super::Render(hDC);
}

void CLargeMp::Release(void)
{
}
