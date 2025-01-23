#pragma once

class CBoss_HpNote
{
public:
	CBoss_HpNote(int _iY);
	~CBoss_HpNote();

	void	Render(HDC hDC);

private:
	RECT	 m_tDrawRect;
};

