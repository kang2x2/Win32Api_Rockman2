#pragma once
#include "Obj.h"

class CFCBullet : public CObj
{
public:
	CFCBullet(float _fX, float _fY, float _fAngle);
	~CFCBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

