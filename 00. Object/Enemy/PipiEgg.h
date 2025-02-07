#pragma once
#include "Obj.h"

class CPipiEgg : public CObj
{
public:
	CPipiEgg(INFO _info);
	~CPipiEgg();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		 Set_Drop() { m_bDrop = true; }

private:
	bool	m_bDrop;
	float	m_fDropSpeed;
};

