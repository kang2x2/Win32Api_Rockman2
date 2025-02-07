#pragma once
#include "Trigger.h"

class CSclMove_XTrigger : public CTrigger
{
public:
	CSclMove_XTrigger(INFO _myInfo, bool _bRight, int _scrollPos, int _leftRockPos);
	~CSclMove_XTrigger();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	int	Get_LeftRockPos() { return m_LeftRockPos; }

private:
	int m_LeftRockPos;
};

