#pragma once
#include "Obj.h"
#include "Boss_HpBar.h"
#include "BossHit.h"

class CAir_ManState;

class CAir_Man : public CObj
{
public:
	CAir_Man(INFO _info);
	~CAir_Man();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void	Boss_Jump(void);

public:
	// 인트로(오프닝) 관련
	bool	Get_Opening() { return m_bOpening; }
	void	Set_Opening() { m_bOpening = false; }
	// 무적 관련
	bool	Get_Invincible() { return m_bInvincible; }
	void	Set_Invincible();
	// 점프 관련
	void	Set_Jump(bool _bJump) { m_bJump = _bJump; }
	void	Set_JumpPower(float _jumpPower) { m_fJumpPower = _jumpPower; }
	// hp UI 관련
	void	HpBar_Update();
	void	Intro_Hp();
	// 상태 관련
	void	Set_State(CAir_ManState* _pState);
	// 구름에 가려지는거 방지.
	void	Boss_HpBar_Render(HDC hDc);

private:
	// 애니매이션 관련
	BOSS_STATE				m_ePreState;
	BOSS_STATE				m_eCurState;

	// 보스 오프닝(인트로)
	bool	m_bOpening;

	// 보스의 미는 힘
	float	m_fPushPower;

	// 보스 무적 상태
	bool	m_bInvincible;
	float	m_fInvincibleTime;

	CAir_ManState* m_pState;
	CBoss_HpBar* m_pHpBar;
	CBossHit m_hitEffect;

	// 보스 사망
	int		m_ClearWait;
};

