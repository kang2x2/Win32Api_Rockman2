#pragma once
#include "Scene.h"
#include "Cloud.h"
#include "NormalTile.h"
#include "Tile.h"

class CMyEdit : public CScene
{
public:
	CMyEdit();
	~CMyEdit();

public:
	// CScene을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Save_Data(void);
	void		Load_Data(void);

private:
	//CCloud m_cloud;

	// 첫 클릭
	bool m_bStart;

	float m_fX;
	float m_fY;
	list<CNormalTile*> m_tileList;
};

