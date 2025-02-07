#include "stdafx.h"
#include "Air_ManState.h"

#include "ScrollMgr.h"

int CAir_ManState::m_iAtkCount = 3;
int CAir_ManState::m_iJumpCount = 2;
int CAir_ManState::m_iRandWind = 0;

CAir_ManState::CAir_ManState() : m_fCoolTime(0)
{
}


CAir_ManState::~CAir_ManState()
{
}

void CAir_ManState::Boss_LSplashWind()
{
	if (CAir_ManState::m_iRandWind == 0) {
		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 500.f,
				20.f, false));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 500.f,
				0.f, false));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 400.f,
				20.f, false));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 300.f,
				30.f, false));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 200.f,
				10.f, false));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 100.f,
				70.f, false));
	}

	if (CAir_ManState::m_iRandWind == 1) {
		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 500.f,
				10.f, false));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 500.f,
				5.f, false));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 400.f,
				20.f, false));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 300.f,
				30.f, false));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 200.f,
				0.f, false));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 100.f,
				10.f, false));
	}

	if (CAir_ManState::m_iRandWind == 2) {
		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 500.f,
				15.f, false));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 500.f,
				0.f, false));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 400.f,
				25.f, false));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 300.f,
				20.f, false));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 200.f,
				30.f, false));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				- (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX - 100.f,
				10.f, false));
	}
	
}

void CAir_ManState::Boss_RSplashWind()
{
	if (CAir_ManState::m_iRandWind == 0) {
		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 500.f,
				20.f, true));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 500.f,
				0.f, true));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 400.f,
				20.f, true));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 300.f,
				30.f, true));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 200.f,
				10.f, true));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 100.f,
				70.f, true));
	}

	if (CAir_ManState::m_iRandWind == 1) {
		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 500.f,
				10.f, true));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 500.f,
				5.f, true));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 400.f,
				20.f, true));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 300.f,
				30.f, true));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 200.f,
				0.f, true));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 100.f,
				10.f, true));
	}
	
	if (CAir_ManState::m_iRandWind == 2) {
		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 500.f,
				15.f, true));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 500.f,
				0.f, true));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 400.f,
				25.f, true));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 300.f,
				20.f, true));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 200.f,
				30.f, true));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EBULLET,
			new CBoss_Wind(m_pAirMan->Get_Info().fX
				+ (m_pAirMan->Get_Info().fCX * 0.5f),
				m_pAirMan->Get_Info().fY,
				m_pAirMan->Get_Info().fX + 100.f,
				10.f, true));
	}
}
