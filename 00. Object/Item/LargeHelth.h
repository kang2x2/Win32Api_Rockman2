#pragma once
#include "Item.h"

class CLargeHelth : public CItem
{
public:
	CLargeHelth(INFO _info);
	~CLargeHelth();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

