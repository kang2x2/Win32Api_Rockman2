#pragma once

#include "Define.h"

class CCloud
{
public:
	CCloud();
	~CCloud();

public:
	void	Initialize(void);
	void	Update(void);
	void	Render(HDC hDC);

	// 배경 애니메이션
	FRAME		m_tFrame;
};

