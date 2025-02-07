#include "stdafx.h"
#include "Obj.h"
#include "ObjMgr.h"

#include "SmallHelth.h"
#include "LargeHelth.h"
#include "SmallMp.h"
#include "LargeMp.h"


CObj::CObj() : m_fSpeed(0.f), m_eDir(DIR_END), m_bDead(false), m_fAngle(0.f)
, m_pTarget(nullptr), m_fDistance(0.f), m_pFrameKey(nullptr), m_iDamage(0)
, m_sType(""), m_bWideDead(false), m_bReflect(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tDrawRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tDrawRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tDrawRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tDrawRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tDrawRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObj::Update_Creature_Rect(void)
{
	m_tColRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.3f));
	m_tColRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.3f));
	m_tColRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.3f));
	m_tColRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObj::Drop_Item(void)
{
	int iRand = rand() % 8;
	if (iRand == 0) {
		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, new CSmallHelth({ m_tInfo.fX, m_tInfo.fY , 15 , 15 }));
	}
	if (iRand == 2) {
		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, new CLargeHelth({ m_tInfo.fX, m_tInfo.fY , 40 , 40 }));
	}
	if (iRand == 4) {
		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, new CSmallMp({ m_tInfo.fX, m_tInfo.fY , 15 , 15 }));
	}

	if (iRand == 6) {
		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, new CLargeMp({ m_tInfo.fX, m_tInfo.fY , 40 , 30 }));
	}

}

void CObj::Motion_FrameR(int _iImgPosX)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStartX;

		if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX)
			m_tFrame.iFrameStartX = _iImgPosX;
		m_tFrame.dwTime = GetTickCount();
	}
}

void CObj::Motion_FrameL(int _iImgPosX)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		--m_tFrame.iFrameStartX;

		if (m_tFrame.iFrameStartX < m_tFrame.iFrameEndX)
			m_tFrame.iFrameStartX = _iImgPosX;

		m_tFrame.dwTime = GetTickCount();
	}
}

void CObj::Charge_FrameR(int _iImgPosX, int _iImgPosY)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameY;
		++m_tFrame.iFrameStartX;

		if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX)
			m_tFrame.iFrameStartX = _iImgPosX;

		if (m_tFrame.iFrameY > m_tFrame.iFrameEndY)
			m_tFrame.iFrameY = _iImgPosY;

		m_tFrame.dwTime = GetTickCount();
	}
}

void CObj::Charge_FrameL(int _iImgPosX, int _iImgPosY)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameY;
		--m_tFrame.iFrameStartX;

		if (m_tFrame.iFrameStartX < m_tFrame.iFrameEndX)
			m_tFrame.iFrameStartX = _iImgPosX;

		if (m_tFrame.iFrameY > m_tFrame.iFrameEndY)
			m_tFrame.iFrameY = _iImgPosY;

		m_tFrame.dwTime = GetTickCount();
	}
}
