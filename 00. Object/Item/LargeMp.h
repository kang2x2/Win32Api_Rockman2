#pragma once
#include "Item.h"

class CLargeMp : public CItem
{
public:
	CLargeMp(INFO _info);
	~CLargeMp();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

