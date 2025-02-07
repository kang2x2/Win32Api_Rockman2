#pragma once
#include "Item.h"

class CSmallHelth : public CItem
{
public:
	CSmallHelth(INFO _info);
	~CSmallHelth();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

