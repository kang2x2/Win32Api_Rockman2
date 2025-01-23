#pragma once
#include "Obj.h"
#include "Thunder.h"

class CThunderLoad : public CObj
{
public:
	CThunderLoad(INFO _info, CObj* _pCloud, CObj* _pTarget);
	~CThunderLoad();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	CObj* m_pCloud;

	int	  m_iAtkCoolTime;

	//int   m_iTempStartX;
	//int	  m_iTempEndX;
};

