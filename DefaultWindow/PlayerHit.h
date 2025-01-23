#pragma once

class CPlayerHit
{
public:
	CPlayerHit();
	~CPlayerHit();

	void Initialize();
	void Render(HDC hDC, float _fX, float _fY);

private:
	RECT m_tDrawRect;
};

