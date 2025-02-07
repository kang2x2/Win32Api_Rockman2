#pragma once
#include "Scene.h"

class CGameEnd : public CScene
{
public:
	CGameEnd();
	~CGameEnd();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	HWND			m_hVideo;
};

