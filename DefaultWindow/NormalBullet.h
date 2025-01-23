#pragma once
#include "obj.h"

class CNormalBullet : public CObj
{
public:
	CNormalBullet(float _fX, float _fY, float _fAngle);
	~CNormalBullet();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

