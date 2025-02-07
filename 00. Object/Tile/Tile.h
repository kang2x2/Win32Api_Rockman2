#pragma once
#include "Obj.h"

class CTile : public CObj
{
public:
	CTile();
	~CTile();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize(void) PURE;
	virtual int Update(void) override;
	virtual void Late_Update(void) PURE;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) PURE;
};
