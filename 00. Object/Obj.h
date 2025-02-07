#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	RECT		Get_DrawRect(void) { return m_tDrawRect; }
	RECT		Get_ColRect(void) { return m_tColRect; }
	INFO		Get_Info(void) { return m_tInfo; }
	float		Get_Speed(void) { return m_fSpeed; }
	float		Get_Angle(void) { return m_fAngle; }
	bool		Get_Dead() { return m_bDead; }
	bool		Get_Ground() { return m_bGround; }
	float		Get_DropTime() { return m_fDropTime; }
	bool		Get_bRight() { return m_bRight; }
	int			Get_Hp() { return m_iHp; }
	int			Get_Damage() { return m_iDamage; }
	string		Get_Type() { return m_sType; }
	

	void		Set_Hp(int _iDamage) { m_iHp -= _iDamage; }
	void		Set_DeadHp() { m_iHp = 0; }
	void		Set_Ground() { m_bGround = true; }
	void		Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Dead() { m_bDead = true; }
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	void		Set_X(float _fX) { m_tInfo.fX += _fX; }
	void		Set_Y(float _fY) { m_tInfo.fY += _fY; }
	void		Set_FixX(float _fX) { m_tInfo.fX = _fX; }
	void		Set_FixY(float _fY) { m_tInfo.fY = _fY; }

	void		Set_Dir(DIRECTION _eDir) { m_eDir = _eDir; }
	void		Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }

	void		Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	// 총알 관련
	bool		Get_Reflect() { return m_bReflect; }
	void		Set_Reflect() { m_bReflect = true; }

public:
	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual void	Late_Update(void)	PURE;
	virtual void	Render(HDC hDC)		PURE;
	virtual void	Release(void)		PURE;

// 애니메이션 관련
public:
	void		Set_ImgRight(bool _bRight) { m_bRight = _bRight; }
	void		Set_iImgPosX(int _posX) { m_iImgPosX = _posX; }
	void		Set_iImgPosY(int _posY) { m_iImgPosY = _posY; }
	void		Set_iFrameStartX(int _iStartX) { m_tFrame.iFrameStartX = _iStartX; }
	void		Set_iFrameEndX(int _iEndX) { m_tFrame.iFrameEndX = _iEndX; }
	void		Set_iFrameY(int _iFrameY) { m_tFrame.iFrameY = _iFrameY; }
	void		Set_iFrameEndY(int _iEndX) { m_tFrame.iFrameEndY = _iEndX; }
	void		Set_idwSpeed(int _idwSpeed) { m_tFrame.dwSpeed = _idwSpeed; }
	void		Set_idwTime(int _idwTime) { m_tFrame.dwTime = _idwTime; }

protected:
	void		Update_Rect(void);
	void		Update_Creature_Rect(void);
	void		Drop_Item(void);
	void		Motion_FrameR(int _iImgPosX);
	void		Motion_FrameL(int _iImgPosX);
	void		Charge_FrameR(int _iImgPosX, int _iImgPosY);
	void		Charge_FrameL(int _iImgPosX, int _iImgPosY);

protected:
	INFO		m_tInfo;
	RECT		m_tDrawRect;
	RECT		m_tColRect;
	FRAME		m_tFrame;
	DIRECTION	m_eDir;
	CObj*		m_pTarget;
	TCHAR*		m_pFrameKey;

	// 공통값
	int			m_iHp;
	float		m_fSpeed;
	bool		m_bDead;
	bool		m_bWideDead;
	float		m_fAngle;
	float		m_fDistance;
	int			m_iDamage;
	string		m_sType;

	// 에니매이션 관련
	int					m_iImgPosX;
	int					m_iImgPosY;
	bool				m_bRight;

	// 점프 관련
	bool				m_bGround;
	bool				m_bJump;
	float				m_fJumpPower;
	float				m_fDropTime;

	// 총알 관련
	bool				m_bReflect;

	// 동작의 쿨타임을 위한 변수
	DWORD				m_iCurTime;
};

