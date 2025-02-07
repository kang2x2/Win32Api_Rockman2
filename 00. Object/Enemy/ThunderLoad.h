#pragma once
#include "Obj.h"
#include "Thunder.h"

class CThunderLoad : public CObj
{
public:
	CThunderLoad(INFO _info, CObj* _pCloud, CObj* _pTarget);
	~CThunderLoad();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	CObj* m_pCloud;

	int	  m_iAtkCoolTime;
};

