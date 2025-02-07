#pragma once

#include "Trigger.h"

class CPipiTrigger : public CTrigger
{
public:
	CPipiTrigger(INFO _myInfo, INFO _targetInfo);
	~CPipiTrigger();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

