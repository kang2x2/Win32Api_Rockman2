#pragma once
#include "obj.h"
#include "PucciGoblin.h"

class CGoblinTile : public CObj
{
public:
	CGoblinTile(INFO _info);
	~CGoblinTile();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool	m_bIntro;
	int		m_iSummonsTime;
};

