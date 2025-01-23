#pragma once
#include "Obj.h"

class CPucciGoblin : public CObj
{
public:
	CPucciGoblin(INFO _info, float _fPointY, bool _bRight, CObj* _target);
	~CPucciGoblin();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	float	m_fPointY;
	float	m_fPointX;
	bool	m_bRight;
	bool    m_bTargeting;

	// 타겟팅 변수
	float	fWidth;
	float	fHeight;
	float	fDiagonal;
	float	fRadian;
};

