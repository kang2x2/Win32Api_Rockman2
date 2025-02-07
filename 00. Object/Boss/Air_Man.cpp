#include "stdafx.h"
#include "Air_Man.h"

#include "BsDeadEffect.h"

#include "CollisionMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "EffectMgr.h"

#include "AM_LAir_Jump.h"

CAir_Man::CAir_Man(INFO _info) : m_bInvincible(false), m_fInvincibleTime(0.f)
{
	m_tInfo = _info;
	Initialize();
}


CAir_Man::~CAir_Man()
{
	Release();
}

void CAir_Man::Initialize(void)
{
	m_iHp = 1;
	m_fSpeed = 5.f;
	m_iDamage = 5;
	m_sType = "Boss";

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/AirManL.bmp", L"Boss_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/AirManR.bmp", L"Boss_Right");
	m_hitEffect.Initialize();

	m_tFrame.iFrameStartX = 5;
	m_tFrame.iFrameEndX = 5;
	m_tFrame.iFrameY = 0;
	m_tFrame.dwSpeed = 10;
	m_tFrame.dwTime = GetTickCount();

	// 이미지 좌표
	m_iImgPosY = 0;
	m_iImgPosX = 5;
	m_bRight = true;

	// 점프관련
	m_bJump = false;
	m_bGround = false;
	m_fJumpPower = 0.f;
	m_fDropTime = 0.f;

	// 초반 오프닝(인트로)
	m_bOpening = true;

	m_pState = nullptr;

	m_eCurState = BOSS_ST_LAIR_JUMP;
	Set_State(new CAM_LAir_Jump(this));
	m_pHpBar = new CBoss_HpBar(this);
}

int CAir_Man::Update(void)
{
	if (m_bDead) {
		return OBJ_DEAD;
	}

	m_bGround = CCollisionMgr::Collision_Tile(this);
	m_pState->Update();
	Boss_Jump();

	__super::Update_Rect();
	__super::Update_Creature_Rect();

	return OBJ_NOEVENT;
}

void CAir_Man::Late_Update(void)
{
	// 사망
	if (!m_bDead && m_iHp <= 0) {
		CSoundMgr::Get_Instance()->StopAll();
		CSoundMgr::Get_Instance()->PlaySound(L"08 - MegamanDefeat.wav", SOUND_EFFECT, 1.0f);
		for (int i = 1; i <= 12; ++i) {
			CEffectMgr::Get_Instance()->Add_Effect(EFFECT_PLAYER_DEAD, new CBsDeadEffect({ m_tInfo.fX, m_tInfo.fY, 60, 67 }, float(i * 30.f)));
		}
		m_iClearTime = GetTickCount() + 5000;
		m_bClear = true;
		m_bDead = true;
	}

	if (!m_bGround) {
		m_fDropTime += 1.0f;
		m_tInfo.fY += m_fDropTime * 0.4f;
	}
	if (m_bGround) {
		m_fDropTime = 0;
	}

	if (m_bInvincible) {
		if (m_fInvincibleTime < GetTickCount()) {
			m_bInvincible = false;
		}
	}

	if (m_bRight)
		__super::Motion_FrameR(m_iImgPosX);
	if (!m_bRight)
		__super::Motion_FrameL(m_iImgPosX);
}

void CAir_Man::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	// 무적 상태라면 항시 드로우
	if (!m_bInvincible) {
		GdiTransparentBlt(hDC,
			int(m_tDrawRect.left + fScrollX),
			int(m_tDrawRect.top + fScrollY), 
			(int)m_tInfo.fCX, 
			(int)m_tInfo.fCY, 
			hMemDC,	
			m_tFrame.iFrameStartX * (int)m_tInfo.fCX,
			m_tFrame.iFrameY * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(128, 0, 128));
	}
	// 무적 상태라면 깜빡이게
	else {
		if (GetTickCount() % 2 == 0) {
			m_hitEffect.Render(hDC, m_tInfo.fX, m_tInfo.fY);
			GdiTransparentBlt(hDC,
				int(m_tDrawRect.left + fScrollX),
				int(m_tDrawRect.top + fScrollY), 
				(int)m_tInfo.fCX, 
				(int)m_tInfo.fCY, 
				hMemDC,	
				m_tFrame.iFrameStartX * (int)m_tInfo.fCX,
				m_tFrame.iFrameY * (int)m_tInfo.fCY,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				RGB(128, 0, 128)); 
		}
	}

	m_pHpBar->Render(hDC);
}

void CAir_Man::Release(void)
{
	if (m_pState) {
		delete m_pState;
		m_pState = nullptr;
	}

	if (m_pHpBar) {
		delete m_pHpBar;
		m_pHpBar = nullptr;
	}
}

void CAir_Man::Boss_Jump(void)
{
	float m_fY = 0.f;
	if (m_bJump) {
		m_fJumpPower -= 0.2f;
		m_tInfo.fY -= m_fJumpPower;
		// 오른쪽이라면
		if (m_bRight){
			m_tInfo.fX += m_fSpeed;
		}
		// 왼쪽이라면
		if (!m_bRight) {
			m_tInfo.fX -= m_fSpeed;
		}
	}
	if (m_bJump && CCollisionMgr::Collision_Tile(this, m_fY)) {
		m_fDropTime = 0;
		m_fJumpPower = 0;
		m_bJump = false;
	}
	if (m_bJump && CCollisionMgr::Collision_Tile(this, m_fY)) {
		m_fDropTime = 0;
		m_fJumpPower = 0;
		m_bJump = false;
	}
}

void CAir_Man::Set_State(CAir_ManState * _pState)
{
	if (m_pState) {
		delete m_pState;
		m_pState = nullptr;
	}
	m_pState = _pState;
}

void CAir_Man::Boss_HpBar_Render(HDC hDC)
{
	m_pHpBar->Render(hDC);
}

void CAir_Man::Set_Invincible()
{
	m_fInvincibleTime = GetTickCount() + 1000.f;
	m_bInvincible = true;
}

void CAir_Man::HpBar_Update()
{
	m_pHpBar->Set_HpBar();
}

void CAir_Man::Intro_Hp()
{
	m_iHp += 1;
	m_pHpBar->Update();
}
