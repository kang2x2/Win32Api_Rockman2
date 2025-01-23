#pragma once
#include "obj.h"

class CMCBullet : public CObj
{
public:
	CMCBullet(float _fX, float _fY, float _fAngle);
	~CMCBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

