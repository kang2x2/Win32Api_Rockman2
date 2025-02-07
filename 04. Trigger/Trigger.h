#pragma once

#include "Define.h"
#include "Tile.h"

class CTrigger
{
public:
	CTrigger();
	~CTrigger();

public:
	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual void	Late_Update(void)	PURE;
	virtual void	Render(HDC hDC)		PURE;
	virtual void	Release(void)		PURE;

public:
	RECT		Get_DrawRect()		 { return m_tDrawRect; }
	string		Get_Type()		 { return m_sType; }
	INFO		Get_TargetInfo() { return m_tTargetInfo; }
	int			Get_ScrollPos()  { return m_iScrollPos; }

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		Create_GoblinTile(INFO _info);
	void		Create_CloudTile(INFO _info);
	void		Create_Pipi(INFO _info);
	void		Update_Rect(void);
	void		Set_Dead() { m_bDead = true; }

protected:
	INFO		m_tInfo;
	RECT		m_tDrawRect;
	bool		m_bDead; 
	string		m_sType; // Ʈ���� Ÿ��

	INFO m_tTargetInfo; // ��� Ÿ�� ��� ����

	int m_iScrollPos; // ������ ��ũ�� ���� ��ġ
};

