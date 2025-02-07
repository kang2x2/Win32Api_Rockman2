#pragma once
#include "Player.h"
#include "Pl_Animation.h"

#include "NormalBullet.h"
#include "MCBullet.h"
#include "FCBullet.h"
#include "MetalBlade.h"
#include "ReefShield.h"

#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

class CPlayerState
{
public:
	CPlayerState();
	virtual ~CPlayerState();

public:
	virtual void Update() PURE;
	// �Ѿ� ��
	static int		m_iBltCount;
protected:
	void Create_NBullet_R();
	void Create_MCBullet_R();
	void Create_FCBullet_R();

	void Create_NBullet_L();
	void Create_MCBullet_L();
	void Create_FCBullet_L();

	void Create_MetalBlade(float _fAngle);
	void Create_ReefShield(float _fAngle);
	
protected:
	CPlayer* m_pPlayer;
	CPl_Animation m_animation;

	// ���� �ð��� ���� ����
	static float	m_fCurTime_S;
	static float	m_fCurTime_A;
	static float	m_fChargeTime;

	// ���� ��� �ð��� ���� ����
	float			m_fAtkTime;
	// �����̵� �ð��� ���� ����
	float			m_fSlideTime;
	// ���� �ð��� ���� ����
	float			m_fMCTime;
	float			m_fFCTime;
};

