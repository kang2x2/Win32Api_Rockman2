#pragma once

class CBossHit
{
public:
	CBossHit();
	~CBossHit();

public:
	void Initialize();
	void Render(HDC hDC, float _fX, float _fY);

private:
	RECT m_tDrawRect;
};

