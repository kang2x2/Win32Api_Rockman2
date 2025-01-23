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
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void	Player_Jump(void);
	void	OffSet(void);

public:
	// ���� ����
	bool		Get_Invincible() { return m_bInvincible; }
	void		Set_Invincible();
	// tp ����
	void		Set_Tp(bool _bTp) { m_bTp = _bTp; }
	// ���� ����
	void		Set_Jump(bool _bJump) { m_bJump = _bJump; }
	void		Set_JumpPower(float _fPower) {
		m_fDropTime = 0.f;
		m_fJumpPower = _fPower;
	}
	// ���� ����
	bool		Get_Charge() { return m_bCharge; }
	void	    Set_Charge(bool _bCharge) { m_bCharge = _bCharge; }
	// ���� ����
	void		Set_State(CPlayerState* _pState);
	// hp UI ����
	void		HpBar_Update();
	// mp UI ����
	void		MpBar_Update();
	// hp ȸ�� ����
	int			Get_RecovCount() { return m_iRecovCount; }
	void		Set_RecovCount(int _count) { m_iRecovCount -= _count; }

	// mp ȸ�� ����
	int			Get_MpCount() { return m_iMpCount; }
	void		Set_MpCount(int _count) { m_iMpCount -= _count; }

	// weapon ����
	WEAPON_ID   Get_WeaponType() { return m_eWeapon; }
	void		Set_WeaponType(WEAPON_ID _eID) { m_eWeapon = _eID; }

	int			Get_MetalBladeMp() { return m_iMetalMp; }
	void		Set_MetalBladeMp(int _iMp) { m_iMetalMp += _iMp; }

	int			Get_ReefShieldMp() { return m_iReefMp; }
	void		Set_ReefShieldMp(int _iMp) { m_iReefMp += _iMp; }
	bool		Get_ReefShield() { return m_bReefShield; }
	void		Set_ReefShield(bool _bReef) { m_bReefShield = _bReef; }


	// ������ �������°� ����.
	void	Pl_HpBar_Render(HDC hDc);
	void	Pl_MpBar_Render(HDC hDc);

private:
	// tp��
	bool				m_bTp;
	// ������ ���� ����
	float				m_fChargeTime;
	bool				m_bCharge;

	// ���� ����
	bool	m_bInvincible;
	float	m_fInvincibleTime;

	// ȸ����
	int		m_iRecovCount;
	int		m_iMpCount;
	int		m_iRecovTime;


	// ����Ÿ��
	int		m_iResetTime;

	// �ִϸ��̼� ����
	STATE				m_ePreState;
	STATE				m_eCurState;

	// ����
	bool				m_bEnding;
	bool				m_bChangeSound;

	// ���� ����
	WEAPON_ID			m_eWeapon;

	int					m_iMetalMp;
	int					m_iReefMp;
	bool				m_bReefShield;
	
	// ���� ü�� ����
	bool				m_bFly;

	// �׽�Ʈ�� ����
	bool				m_bTest;
	
	CPlayerState* m_pState;
	CPlayer_HpBar* m_HpBar;
	CPlayer_MpBar* m_MpBar;
	CPlayerHit m_hitEffect;
};

