#pragma once
#include "Trigger.h"

class CSclMove_YTrigger : public CTrigger
{
public:
	CSclMove_YTrigger(INFO _myInfo);
	~CSclMove_YTrigger();

	// CTrigger��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

