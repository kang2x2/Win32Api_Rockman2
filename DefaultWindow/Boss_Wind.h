#pragma once
#include "Obj.h"

class CBoss_Wind : public CObj
{
public:
	CBoss_Wind(float _fX, float _fY, float _fDestX, float _fAngle, bool _bRight);
	~CBoss_Wind();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	float	m_DestPosX;
	float	m_DestPosY;
};

