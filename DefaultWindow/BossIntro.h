#pragma once
#include "Scene.h"

class CBossIntro : public CScene
{
public:
	CBossIntro();
	~CBossIntro();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	FRAME		m_tBgFrame; // 배경 프레임
	FRAME		m_tAirmanFrame; // 에어맨 프레임
	FRAME		m_tFontFrame; // 폰트 프레임
	int			m_iChangWaitTime; // 씬 전환 대기 시간
	int			m_iWaitTime; // 중간 대기 시간
	float		m_fAirmanPosX; // 에어맨 위치
	int			m_iNum; // 트리거 번호

};

