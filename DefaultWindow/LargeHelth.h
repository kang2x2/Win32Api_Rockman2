#pragma once
#include "Obj.h"

class CLargeHelth : public CObj
{
public:
	CLargeHelth(INFO _info);
	~CLargeHelth();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

