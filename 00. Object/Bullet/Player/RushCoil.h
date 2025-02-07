#pragma once
#include "Obj.h"

class CRushCoil : public CObj
{
public:
	CRushCoil(INFO _info, float _fDestY);
	~CRushCoil();

	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		 Set_Coil() { m_bState = RUSH_COIL; }
	RUSH_STATE   Get_RushState() { return m_bState; }
private:
	int		m_iDuration;

	float	m_fDestY;
	
	RUSH_STATE m_bState;
};

