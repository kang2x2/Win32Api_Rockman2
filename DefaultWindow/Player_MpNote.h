#pragma once

class CPlayer_MpNote
{
public:
	CPlayer_MpNote(int _iY);
	~CPlayer_MpNote();

	void	Render(HDC hDC);

private:
	RECT	 m_tDrawRect;
};

