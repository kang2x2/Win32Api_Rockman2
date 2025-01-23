#pragma once
#include "Trigger.h"

class CSclFix_XTrigger : public CTrigger
{
public:
	CSclFix_XTrigger(INFO _myInfo, bool _bRight, int _scrollPos);
	~CSclFix_XTrigger();

	// CTrigger을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

