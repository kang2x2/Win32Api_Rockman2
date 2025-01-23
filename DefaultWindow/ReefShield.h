#pragma once
#include "Obj.h"

class CPlayer;

class CReefShield : public CObj
{
public:
	CReefShield(CObj* _pPlayer);
	~CReefShield();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Set_Fire(float _fAngle) { 
		m_bFire = true;
		m_fAngle = _fAngle;
	}
	
private:
	bool		m_bFire;
	CObj*		m_pPlayer;
};

