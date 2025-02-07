#pragma once

#include "Trigger.h"

class CGoblinTrigger : public CTrigger
{
public:
	CGoblinTrigger(INFO _myInfo, INFO _targetInfo);
	~CGoblinTrigger();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};

