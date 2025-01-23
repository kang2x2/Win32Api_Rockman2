#pragma once

class CPlayer_HpNote
{
public:
	CPlayer_HpNote(int _iY);
	~CPlayer_HpNote();

	void	Render(HDC hDC);

private:
	RECT	 m_tDrawRect;
};

