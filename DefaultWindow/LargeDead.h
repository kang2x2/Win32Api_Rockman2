#pragma once
#include "Effect.h"

class CLargeDead : public CEffect
{
public:
	CLargeDead(INFO _info);
	~CLargeDead();

	// CEffect��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
};

