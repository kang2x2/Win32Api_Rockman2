#pragma once
#include "obj.h"

class CCloudTile : public CObj
{
public:
	CCloudTile(INFO _info);
	~CCloudTile();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	
public:
	float		 GetAngle() { return m_fAngle; }

private:
	float m_fCenterX;
	float m_fCenterY;

	float m_prevX;
	float m_prevY;

	float m_fIncreaseAngle;
	float m_fOffSetX;
	float m_fOffSetY;
	float m_fMs;
};

