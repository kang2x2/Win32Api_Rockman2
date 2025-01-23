#pragma once
#include "Scene.h"

class CLogo : public CScene
{
public:
	CLogo();
	~CLogo();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	FRAME		m_tFrame;
	int			m_iWaitTile;
	int			m_iNum;
};

