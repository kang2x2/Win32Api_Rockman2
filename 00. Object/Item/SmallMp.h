#pragma once
#include "Item.h"

class CSmallMp : public CItem
{
public:
	CSmallMp(INFO _info);
	~CSmallMp();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

