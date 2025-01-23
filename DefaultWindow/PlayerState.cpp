#include "stdafx.h"
#include "PlayerState.h"

float CPlayerState::m_fCurTime_S = 0;
float CPlayerState::m_fCurTime_A = 0;
float CPlayerState::m_fChargeTime = 0;
int	  CPlayerState::m_iBltCount = 0;

CPlayerState::CPlayerState() 
	: m_fSlideTime(500.f), m_fAtkTime(350.f), m_fMCTime(30), m_fFCTime(80)
{
}


CPlayerState::~CPlayerState()
{
}

void CPlayerState::Create_NBullet_R()
{
		CSoundMgr::Get_Instance()->StopSound(SOUNT_ATK);
		CSoundMgr::Get_Instance()->PlaySound(L"shooting.wav", SOUNT_ATK, 0.5f);

		CObjMgr::Get_Instance()->Add_Object(OBJ_PBULLET,
			new CNormalBullet(m_pPlayer->Get_Info().fX +
			(m_pPlayer->Get_Info().fCX * 0.5f),
				m_pPlayer->Get_Info().fY, 90.f));
}

void CPlayerState::Create_MCBullet_R()
{
	CSoundMgr::Get_Instance()->StopSound(SOUNT_ATK);
	CSoundMgr::Get_Instance()->PlaySound(L"shooting.wav", SOUNT_ATK, 0.5f);

	CObjMgr::Get_Instance()->Add_Object(OBJ_PBULLET,
		new CMCBullet(m_pPlayer->Get_Info().fX +
		(m_pPlayer->Get_Info().fCX * 0.5f),
			m_pPlayer->Get_Info().fY, 90.f));
}

void CPlayerState::Create_FCBullet_R()
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_CHARGE);
	CSoundMgr::Get_Instance()->PlaySound(L"splash.wav", SOUND_EFFECT, 0.5f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PBULLET,
		new CFCBullet(m_pPlayer->Get_Info().fX +
		(m_pPlayer->Get_Info().fCX * 0.5f),
			m_pPlayer->Get_Info().fY, 90.f));
}

void CPlayerState::Create_NBullet_L()
{
	CSoundMgr::Get_Instance()->StopSound(SOUNT_ATK);
	CSoundMgr::Get_Instance()->PlaySound(L"shooting.wav", SOUNT_ATK, 0.5f);

	CObjMgr::Get_Instance()->Add_Object(OBJ_PBULLET,
		new CNormalBullet(m_pPlayer->Get_Info().fX -
		(m_pPlayer->Get_Info().fCX * 0.5f),
			m_pPlayer->Get_Info().fY, -90.f));
}

void CPlayerState::Create_MCBullet_L()
{
	CSoundMgr::Get_Instance()->StopSound(SOUNT_ATK);
	CSoundMgr::Get_Instance()->PlaySound(L"shooting.wav", SOUNT_ATK, 0.5f);

	CObjMgr::Get_Instance()->Add_Object(OBJ_PBULLET,
		new CMCBullet(m_pPlayer->Get_Info().fX -
		(m_pPlayer->Get_Info().fCX * 0.5f),
			m_pPlayer->Get_Info().fY, -90.f));
}

void CPlayerState::Create_FCBullet_L()
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_CHARGE);
	CSoundMgr::Get_Instance()->PlaySound(L"splash.wav", SOUND_EFFECT, 0.5f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PBULLET,
		new CFCBullet(m_pPlayer->Get_Info().fX -
		(m_pPlayer->Get_Info().fCX * 0.5f),
			m_pPlayer->Get_Info().fY, -90.f));
}

void CPlayerState::Create_MetalBlade(float _fAngle)
{
	m_pPlayer->Set_MetalBladeMp(-1);

	if (m_pPlayer->Get_MetalBladeMp() > 0) {
		// 메탈 블레이드
		CSoundMgr::Get_Instance()->StopSound(SOUNT_ATK);
		CSoundMgr::Get_Instance()->PlaySound(L"MB.wav", SOUNT_ATK, 0.5f);

		if (_fAngle == 90.f) {
			CObjMgr::Get_Instance()->Add_Object(OBJ_PBULLET,
				new CMetalBlade(m_pPlayer->Get_Info().fX +
				(m_pPlayer->Get_Info().fCX * 0.5f),
					m_pPlayer->Get_Info().fY, _fAngle));
		}
		else if (_fAngle == -90.f) {
			CObjMgr::Get_Instance()->Add_Object(OBJ_PBULLET,
				new CMetalBlade(m_pPlayer->Get_Info().fX -
				(m_pPlayer->Get_Info().fCX * 0.5f),
					m_pPlayer->Get_Info().fY, _fAngle));
		}
	}
}

void CPlayerState::Create_ReefShield(float _fAngle)
{
	if (!m_pPlayer->Get_ReefShield()) {
		if (m_pPlayer->Get_ReefShieldMp() > 0) {
			CSoundMgr::Get_Instance()->StopSound(SOUNT_ATK);
			CSoundMgr::Get_Instance()->PlaySound(L"20 - IceSlasher.wav", SOUNT_ATK, 1.0f);

			m_pPlayer->Set_ReefShieldMp(-2);
			CObjMgr::Get_Instance()->Add_Object(OBJ_PBULLET, new CReefShield(m_pPlayer));
			m_pPlayer->Set_ReefShield(true);
		}
	}
	else {
		for (auto iter : CObjMgr::Get_Instance()->Get_ObjList(OBJ_PBULLET)) {
			if (iter->Get_Type() == "pReefShield") {
				if (iter->Get_Angle() == 0.f) {
					CSoundMgr::Get_Instance()->StopSound(SOUNT_ATK);
					CSoundMgr::Get_Instance()->PlaySound(L"27 - PointTally.wav", SOUNT_ATK, 0.5f);

					dynamic_cast<CReefShield*>(iter)->Set_Fire(_fAngle);
					break;
				}
			}
		}
	}

}
