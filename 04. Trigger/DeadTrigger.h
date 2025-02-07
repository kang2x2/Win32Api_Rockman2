#pragma once
#include "Trigger.h"

class CDeadTrigger : public CTrigger
{
public:
	CDeadTrigger(INFO _myInfo);
	~CDeadTrigger();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

