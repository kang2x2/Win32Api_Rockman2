#pragma once
#include "Obj.h"

class CLargeMp : public CObj
{
public:
	CLargeMp(INFO _info);
	~CLargeMp();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

