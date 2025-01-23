#pragma once

#include "Define.h"

class CEffect
{
public:
	CEffect();
	~CEffect();

public:
	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual void	Late_Update(void)	PURE;
	virtual void	Render(HDC hDC)		PURE;

public:
	void		Update_Rect(void);
protected:
	INFO		m_tInfo;
	RECT		m_tDrawRect;
	FRAME		m_tFrame;
	bool		m_bDead;
};

