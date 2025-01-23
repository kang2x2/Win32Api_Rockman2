#pragma once
#include "Scene.h"
#include "Cloud.h"
#include "Inventory.h"

class CStgAirman : public CScene
{
public:
	CStgAirman();
	~CStgAirman();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void		Load_Data(void);

private:
	CCloud m_cloud;
	int    m_iReadyTime;
	bool   m_bStart;
	bool   m_bInven;

	FRAME		m_tReadyFrame; // 폰트 프레임

	// 인벤토리
	CInventory* m_pInven;
};

