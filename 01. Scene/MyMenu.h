#pragma once
#include "Scene.h"

class CMyMenu : public CScene
{
public:
	CMyMenu();
	virtual ~CMyMenu();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	FRAME		m_tFrame;
	float		m_fScrollSpeed; // 스크롤 속도
	int			m_iWaitTime; // 중간 대기 시간
	int			m_iNum; // 트리거 넘버
	float		m_fTpSpeed; // 록맨 텔포 속도
};

