#pragma once
#include "Scene.h"
#include "Cloud.h"
#include "Inventory.h"

class CStgAirman : public CScene
{
public:
	CStgAirman();
	~CStgAirman();

	// CScene��(��) ���� ��ӵ�
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

	FRAME		m_tReadyFrame; // ��Ʈ ������

	// �κ��丮
	CInventory* m_pInven;
};

