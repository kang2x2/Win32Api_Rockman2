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

	// ��� �ִϸ��̼�
	FRAME		m_tFrame;
};

