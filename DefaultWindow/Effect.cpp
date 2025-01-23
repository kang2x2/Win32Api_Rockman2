#include "stdafx.h"
#include "Effect.h"


CEffect::CEffect() : m_bDead(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
}


CEffect::~CEffect()
{
}

void CEffect::Update_Rect(void)
{
	m_tDrawRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tDrawRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tDrawRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tDrawRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}
