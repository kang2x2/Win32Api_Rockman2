#pragma once
#include "Trigger.h"

class CBossTrigger : public CTrigger
{
public:
	CBossTrigger(INFO _myInfo, INFO _targetInfo);
	~CBossTrigger();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

