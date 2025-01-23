#pragma once
#include "Scene.h"

class CSelectBoss : public CScene
{
public:
	CSelectBoss();
	~CSelectBoss();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	FRAME		m_tBgFrame;
	FRAME		m_tPtFrame;

	int			m_iSelectAry[3][3] = {0,}; // 셀렉트 포인터 배열
	bool		m_bSuccesMove; // 셀렉트 포인터
	bool		m_bSelect; // 선택 완료

	int		m_iWaitTime; // 씬 전환 대기 시간
};

