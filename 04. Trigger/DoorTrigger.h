#pragma once
#include "Trigger.h"

class CDoorTrigger : public CTrigger
{
public:
	CDoorTrigger(INFO _myInfo, bool _bRight, int _scrollPos, int _leftRockPos);
	~CDoorTrigger();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	int	Get_LeftRockPos() { return m_LeftRockPos; }
	int Get_TriggerNum() { return m_iTriggerNum; }
	void Set_TriggerNum(int _iNum) { m_iTriggerNum = _iNum; }
private:
	int		    m_LeftRockPos;
	int			m_iTriggerNum;
	int			m_iDoorTime;
	FRAME		m_tFrame;
};

