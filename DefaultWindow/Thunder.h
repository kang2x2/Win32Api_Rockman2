#pragma once
#include "Obj.h"

class CThunder : public CObj
{
public:
	CThunder(INFO _info, bool _bRight);
	~CThunder();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Set_UpPower() { m_fUpPower = 10.f; }
private:
	float	m_fUpPower;
};

