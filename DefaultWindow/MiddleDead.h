#pragma once
#include "Effect.h"

class CMiddleDead : public CEffect
{
public:
	CMiddleDead(INFO _info);
	~CMiddleDead();

	// CEffect��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
};

