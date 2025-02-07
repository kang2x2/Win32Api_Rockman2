#pragma once
#include "obj.h"

class CPucciGoblin : public CObj
{
public:
	CPucciGoblin(INFO _info, float _fPointY, bool _bRight, CObj* _target);
	~CPucciGoblin();

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

	// Å¸°ÙÆÃ º¯¼ö
	float	fWidth;
	float	fHeight;
	float	fDiagonal;
	float	fRadian;
};

