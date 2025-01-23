#include "stdafx.h"
#include "Player.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"
#include "EffectMgr.h"

#include "NormalBullet.h"
#include "MCBullet.h"
#include "FCBullet.h"
#include "ReefShield.h"

#include "PlDeadEffect.h"

#include "Pl_DownTp.h"
#include "Pl_RIdle.h"
#include "Pl_RJump.h"
#include "Pl_LJump.h"
#include "Pl_RHit.h"
#include "Pl_LHit.h"
#include "Pl_UpTp.h"

float m_fPushPower;

CPlayer::CPlayer() : 
	m_bInvincible(false), m_bReefShield(false), m_bTest(false), m_bChangeSound(false),
	m_bTp(false), m_bCharge(false),
	m_fInvincibleTime(0.f), m_fChargeTime(0.f),
	m_iRecovCount(0), m_iMpCount(0), m_iRecovTime(0), m_eWeapon(WEAPON_NORMAL),
	m_iMetalMp(40), m_iReefMp(20), m_pState(nullptr)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 400.f, 0.f, 75.f, 75.f};
	//보스 체크용
	//m_tInfo = { 10000.f, 1300.f, 75.f, 75.f };
	//CScrollMgr::Get_Instance()->Set_ScrollFixX(-10000);
	//CScrollMgr::Get_Instance()->Set_ScrollFixY(-1200);
	//CScrollMgr::Get_Instance()->Set_MaxScrollX(-9570);
	//CScrollMgr::Get_Instance()->TestY();
	// 기믹 체크용
	//m_tInfo = { 5500.f, 900.f, 75.f, 75.f };
	//CScrollMgr::Get_Instance()->Set_ScrollFixX(-5500.f);
	//CScrollMgr::Get_Instance()->Set_ScrollFixY(-600.f);
	//CScrollMgr::Get_Instance()->Set_MaxScrollX(-9570);
	//CScrollMgr::Get_Instance()->TestY2();

	m_fSpeed = 3.f;
	m_iHp = 20;
	m_sType = "Player";

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RockmanL.bmp", L"Player_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RockmanR.bmp", L"Player_Right");

	m_pFrameKey = L"Player_Right";
	m_eCurState = ST_RIDLE;

	m_tFrame.iFrameStartX = 1;
	m_tFrame.iFrameEndX = 2;
	m_tFrame.iFrameY = 1;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	// 이미지 좌표
	m_iImgPosY = 0;
	m_iImgPosX = 1;
	m_bRight = true;

	// 점프관련
	m_bJump = false;
	m_bGround = false;
	m_fJumpPower = 10.0f;
	m_fDropTime = 15.f;

	// 리셋타임
	m_iResetTime = 0;

	Set_State(new CPl_DownTp(this));
	m_HpBar = new CPlayer_HpBar(this);
	m_MpBar = new CPlayer_MpBar(this);

	m_bEnding = false;
}

int CPlayer::Update(void)
{
	// 테스트 모드
	if (CKeyMgr::Get_Instance()->Key_Test()) {
		if(!m_bTest) m_bTest = true;
		else		 m_bTest = false;
	}

	// 다시 시작하는 부분
	if (m_bDead) {
		if (m_iResetTime < GetTickCount()) {
			m_bGameover = true;
		}
	}

	// 통상
	if (!m_bDead) {
		m_bGround = CCollisionMgr::Collision_Tile(this);

		if (m_iHp < 0) m_iHp = 0;

		m_pState->Update();
		Player_Jump();

		m_tInfo.fX -= m_fPushPower;

		__super::Update_Rect();
		__super::Update_Creature_Rect();
	}

	// 스크롤 락.
	// 왼쪽
	if (m_tInfo.fX + CScrollMgr::Get_Instance()->Get_ScrollMinX() <= 60.f)
		m_tInfo.fX += m_fSpeed + m_fPushPower;
	// 오른쪽 임시락
	else if (m_tInfo.fX >= 11835)
		m_tInfo.fX -= m_fSpeed - m_fPushPower;

	// mp 관련
	if (m_eWeapon != WEAPON_NORMAL && m_eWeapon != WEAPON_RUSH) {
		m_MpBar->Set_MpBar();
	}

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	// 클리어 사운드
	if (!m_bEnding && m_bClear && m_iClearTime < GetTickCount()) {
		m_iClearTime = GetTickCount() + 8000;
		CSoundMgr::Get_Instance()->StopAll();
		CSoundMgr::Get_Instance()->PlaySound(L"StageClear.wav", SOUND_EFFECT, 1.0f);
		m_bEnding = true;
	}
	// 클리어 후 화면 전환
	if (m_bEnding && m_iClearTime < GetTickCount()) {
		if (!m_bChangeSound) {
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"teleport_in.wav", SOUND_EFFECT, 1.0f);
			m_bChangeSound = true;
		}
		Set_State(new CPl_UpTp(this));
		m_tInfo.fY -= 10.0f;
		if (m_tInfo.fY <= 750.f) {
			CSceneMgr::Get_Instance()->Scene_Change(SC_GAME_END);
			return;
		}
	}

	if (!m_bDead) {
		// 사망
		if (m_iHp <= 0 && !m_bTest) {
			CSoundMgr::Get_Instance()->StopAll();
			CSoundMgr::Get_Instance()->PlaySound(L"08 - MegamanDefeat.wav", SOUND_EFFECT, 1.0f);
			m_iResetTime = GetTickCount() + 5000;
			for (int i = 1; i <= 12; ++i) {
				CEffectMgr::Get_Instance()->Add_Effect(EFFECT_PLAYER_DEAD, new CPlDeadEffect({ m_tInfo.fX, m_tInfo.fY, 60, 67 }, float(i * 30.f)));
			}
			m_bDead = true;
		}

		// 회복 연출
		if (m_iRecovCount > 0) {
			m_bPause = true;
			// hp
			if (m_iRecovTime < GetTickCount()) {
				if (m_iHp < 20) {
					CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"hpRepill.wav", SOUND_EFFECT, 1.0f);
					m_iRecovTime = GetTickCount() + 100;
					m_iHp += 1;
					m_iRecovCount -= 1;
					HpBar_Update();
				}
				if (m_iHp >= 20) {
					m_iRecovCount = 0;
				}
			}
		}

		if (m_iMpCount > 0) {
			m_bPause = true;
			// mp
			if (m_iRecovTime < GetTickCount()) {
				if (m_eWeapon == WEAPON_MB) {
					if (m_iMetalMp < 40) {
						CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
						CSoundMgr::Get_Instance()->PlaySound(L"hpRepill.wav", SOUND_EFFECT, 1.0f);
						m_iRecovTime = GetTickCount() + 100;
						m_iMetalMp += 1;
						m_iMpCount -= 1;
						MpBar_Update();
					}
					if (m_iMetalMp >= 40) m_iMpCount = 0;
				}
				else if (m_eWeapon == WEAPON_RS) {
					if (m_iReefMp < 20) {
						CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
						CSoundMgr::Get_Instance()->PlaySound(L"hpRepill.wav", SOUND_EFFECT, 1.0f);
						m_iRecovTime = GetTickCount() + 100;
						m_iReefMp += 1;
						m_iMpCount -= 1;
						MpBar_Update();
					}
					if (m_iReefMp >= 20) m_iMpCount = 0;
				}
			}
		}
		if(m_iMpCount <= 0 && m_iRecovCount <= 0) {
			m_bPause = false;
		}
		//////////////////////////////////


		// y축 카메라 연출 중이 아닐때만 중력 적용.
		if ((CScrollMgr::Get_Instance()->Get_ScrollMinY() >= CScrollMgr::Get_Instance()->Get_ScrollY() + WINCY)
			&& !CScrollMgr::Get_Instance()->Get_SCrollMoveX()) {
			// 회복중이면 안떨어지게
			if (!m_bEnding && !m_bGround && m_iRecovCount <= 0 && m_iMpCount <= 0) {
				m_fDropTime += 0.5f;
				m_tInfo.fY += m_fDropTime * 0.4f;
			}
			if (m_bGround) {
				m_fDropTime = 0;
				m_fJumpPower = 10.f;
			}
		}

		// 보스방 입장 카메라 연출 시
		if (CScrollMgr::Get_Instance()->Get_SCrollMoveX())
		{
			m_fJumpPower = 0;
			__super::Update_Rect();
			m_tInfo.fX += 0.9f;
		}


		// 무적
		if (m_bInvincible) {
			if (m_fInvincibleTime < GetTickCount()) {
				m_bInvincible = false;
			}
		}

		OffSet();

		// 보스방 입장 카메라 연출이 아니고 회복중이 아니면
		if (!CScrollMgr::Get_Instance()->Get_SCrollMoveX() && m_iRecovCount <= 0 && m_iMpCount <= 0) {
			if (m_bCharge) {
				CSoundMgr::Get_Instance()->PlaySound(L"Charging.wav", SOUND_CHARGE, 0.5f);
				if (m_bRight)
					__super::Charge_FrameR(m_iImgPosX, m_iImgPosY);
				if (!m_bRight)
					__super::Charge_FrameL(m_iImgPosX, m_iImgPosY);
			}
			else {
				if (m_bRight)
					__super::Motion_FrameR(m_iImgPosX);
				if (!m_bRight)
					__super::Motion_FrameL(m_iImgPosX);
			}
		}
	}
}

void CPlayer::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	if (!m_bDead) {
		if (!m_bInvincible) {
			GdiTransparentBlt(hDC,
				int(m_tDrawRect.left + fScrollX),
				int(m_tDrawRect.top + fScrollY),
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY + 1.5f,
				hMemDC,
				m_tFrame.iFrameStartX * (int)m_tInfo.fCX,
				m_tFrame.iFrameY * (int)m_tInfo.fCY + 1.5f,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY + 1.5f,
				RGB(210, 230, 210));
		}
		else {
			if (GetTickCount() % 2 == 0) {
				m_hitEffect.Render(hDC, m_tInfo.fX, m_tInfo.fY);
				GdiTransparentBlt(hDC,
					int(m_tDrawRect.left + fScrollX),
					int(m_tDrawRect.top + fScrollY),
					(int)m_tInfo.fCX,
					(int)m_tInfo.fCY + 1.5f,
					hMemDC,
					m_tFrame.iFrameStartX * (int)m_tInfo.fCX,
					m_tFrame.iFrameY * (int)m_tInfo.fCY + 1.5f,
					(int)m_tInfo.fCX,
					(int)m_tInfo.fCY + 1.5f,
					RGB(210, 230, 210));
			}
		}
	}
}

void CPlayer::Release(void)
{
	if (m_pState) {
		delete m_pState;
		m_pState = nullptr;
	}
	if (m_HpBar) {
		delete m_HpBar;
		m_HpBar = nullptr;
	}
	if (m_MpBar) {
		delete m_MpBar;
		m_MpBar = nullptr;
	}
}

void CPlayer::Player_Jump(void)
{
	float m_fY = 0.f;
	if (m_bJump) {
		m_fJumpPower -= 0.2f;
		m_tInfo.fY -= m_fJumpPower;
	}

	if (m_bJump && CCollisionMgr::Collision_Tile(this, m_fY)) {
		CSoundMgr::Get_Instance()->PlaySound(L"land.wav", SOUND_GROUND, 1.0f);
		m_fDropTime = 0;
		m_fJumpPower = 0;
		m_bJump = false;
	}
}

void CPlayer::OffSet(void)
{
	float fOffSetminX = 390.f;
	float fOffSetmaxX = 410.f;

	float fOffSetminY = 50.f;
	float fOffSetmaxY = 550.f;

	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	if (fOffSetminX > m_tInfo.fX + fScrollX)	// 플레이어가 왼쪽으로 향하고 있는 경우
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed + m_fPushPower);

	if (fOffSetmaxX < m_tInfo.fX + fScrollX)	// 플레이어가 오른쪽으로 향하고 있는 경우
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed + m_fPushPower);

	// y축 연출 (스크롤 매니저에서 해도 되지만 옮기기 귀찮음)
	if (CScrollMgr::Get_Instance()->Get_ScrollMinY() < fScrollY + WINCY) {
		CScrollMgr::Get_Instance()->Set_ScrollY(-5.f);
	}
}

void CPlayer::Set_Invincible()
{
	m_fInvincibleTime = GetTickCount() + 2000.f;
	m_bInvincible = true;
	if (m_bRight)		 Set_State(new CPl_RHit(this));
	else if (!m_bRight)  Set_State(new CPl_LHit(this));
}

void CPlayer::Set_State(CPlayerState * _pState)
{
	if (m_pState) {
		delete m_pState;
		m_pState = nullptr;
	}
	m_pState = _pState;
}

void CPlayer::HpBar_Update()
{
	m_HpBar->Set_HpBar();
}

void CPlayer::MpBar_Update()
{
	m_MpBar->Set_MpBar();
}

void CPlayer::Pl_HpBar_Render(HDC hDC)
{
	m_HpBar->Render(hDC);
}

void CPlayer::Pl_MpBar_Render(HDC hDC)
{
	m_MpBar->Render(hDC);
}


