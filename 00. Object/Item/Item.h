#pragma once
#include "Obj.h"

class CItem : public CObj
{
public:
	CItem();
	~CItem();

	virtual void Initialize(void) PURE;
	virtual int Update(void) override;
	virtual void Late_Update(void) PURE;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) PURE;
};

