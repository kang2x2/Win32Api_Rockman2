#pragma once
#include "Obj.h"
#include "Player_HpBar.h"
#include "Player_MpBar.h"
#include "PlayerHit.h"

class CPlayerState;

class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void	Player_Jump(void);
	void	OffSet(void);

public:
	// 무적 관련
	bool		Get_Invincible() { return m_bInvincible; }
	void		Set_Invincible();
	// tp 관련
	void		Set_Tp(bool _bTp) { m_bTp = _bTp; }
	// 점프 관련
	void		Set_Jump(bool _bJump) { m_bJump = _bJump; }
	void		Set_JumpPower(float _fPower) {
		m_fDropTime = 0.f;
		m_fJumpPower = _fPower;
	}
	// 차지 관련
	bool		Get_Charge() { return m_bCharge; }
	void	    Set_Charge(bool _bCharge) { m_bCharge = _bCharge; }
	// 상태 관련
	void		Set_State(CPlayerState* _pState);
	// hp UI 관련
	void		HpBar_Update();
	// mp UI 관련
	void		MpBar_Update();
	// hp 회복 관련
	int			Get_RecovCount() { return m_iRecovCount; }
	void		Set_RecovCount(int _count) { m_iRecovCount -= _count; }

	// mp 회복 관련
	int			Get_MpCount() { return m_iMpCount; }
	void		Set_MpCount(int _count) { m_iMpCount -= _count; }

	// weapon 관련
	WEAPON_ID   Get_WeaponType() { return m_eWeapon; }
	void		Set_WeaponType(WEAPON_ID _eID) { m_eWeapon = _eID; }

	int			Get_MetalBladeMp() { return m_iMetalMp; }
	void		Set_MetalBladeMp(int _iMp) { m_iMetalMp += _iMp; }

	int			Get_ReefShieldMp() { return m_iReefMp; }
	void		Set_ReefShieldMp(int _iMp) { m_iReefMp += _iMp; }
	bool		Get_ReefShield() { return m_bReefShield; }
	void		Set_ReefShield(bool _bReef) { m_bReefShield = _bReef; }


	// 구름에 가려지는거 방지.
	void	Pl_HpBar_Render(HDC hDc);
	void	Pl_MpBar_Render(HDC hDc);

private:
	// tp중
	bool				m_bTp;
	// 차지를 위한 변수
	float				m_fChargeTime;
	bool				m_bCharge;

	// 무적 상태
	bool	m_bInvincible;
	float	m_fInvincibleTime;

	// 회복중
	int		m_iRecovCount;
	int		m_iMpCount;
	int		m_iRecovTime;


	// 리셋타임
	int		m_iResetTime;

	// 애니메이션 관련
	STATE				m_ePreState;
	STATE				m_eCurState;

	// 엔딩
	bool				m_bEnding;
	bool				m_bChangeSound;

	// 웨폰 관련
	WEAPON_ID			m_eWeapon;

	int					m_iMetalMp;
	int					m_iReefMp;
	bool				m_bReefShield;
	
	// 공중 체공 관련
	bool				m_bFly;

	// 테스트용 변수
	bool				m_bTest;
	
	CPlayerState* m_pState;
	CPlayer_HpBar* m_HpBar;
	CPlayer_MpBar* m_MpBar;
	CPlayerHit m_hitEffect;
};

