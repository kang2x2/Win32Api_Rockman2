#pragma once
#include "Effect.h"

class CVerySmallDead : public CEffect
{
public:
	CVerySmallDead(INFO _info);
	~CVerySmallDead();

	// CEffect��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
};

