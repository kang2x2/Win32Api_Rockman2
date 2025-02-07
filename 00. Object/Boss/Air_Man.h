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
	// ��Ʈ��(������) ����
	bool	Get_Opening() { return m_bOpening; }
	void	Set_Opening() { m_bOpening = false; }
	// ���� ����
	bool	Get_Invincible() { return m_bInvincible; }
	void	Set_Invincible();
	// ���� ����
	void	Set_Jump(bool _bJump) { m_bJump = _bJump; }
	void	Set_JumpPower(float _jumpPower) { m_fJumpPower = _jumpPower; }
	// hp UI ����
	void	HpBar_Update();
	void	Intro_Hp();
	// ���� ����
	void	Set_State(CAir_ManState* _pState);
	// ������ �������°� ����.
	void	Boss_HpBar_Render(HDC hDc);

private:
	// �ִϸ��̼� ����
	BOSS_STATE				m_ePreState;
	BOSS_STATE				m_eCurState;

	// ���� ������(��Ʈ��)
	bool	m_bOpening;

	// ������ �̴� ��
	float	m_fPushPower;

	// ���� ���� ����
	bool	m_bInvincible;
	float	m_fInvincibleTime;

	CAir_ManState* m_pState;
	CBoss_HpBar* m_pHpBar;
	CBossHit m_hitEffect;

	// ���� ���
	int		m_ClearWait;
};

