#include "stdafx.h"
#include "Inventory.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"

CInventory::CInventory(CObj* _pPlayer) : m_bClose(false), m_iArrowPos(165)
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"02 - PauseMenu.wav", SOUND_EFFECT, 1.0f);
	m_pPlayer = _pPlayer;
	Initialize();
}


CInventory::~CInventory()
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"02 - PauseMenu.wav", SOUND_EFFECT, 1.0f);
}

void CInventory::Initialize(void)
{
	// �̹��� ����
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/OpenInventory.bmp", L"OpenInventory");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Arrow.bmp", L"Arrow");

	m_pFrameKey = L"OpenInventory";

	m_tFrame.iFrameStartX = 0;
	m_tFrame.iFrameEndX = 14;
	m_tFrame.iFrameY = 0;
	m_tFrame.dwSpeed = 10;
	m_tFrame.dwTime = GetTickCount();

}

int CInventory::Update(void)
{
	if (m_bClose) {
		m_tFrame.iFrameEndX = 0;
	}

	if (m_bClose && m_tFrame.iFrameStartX == 0) {
		return 1;
	}
	
	// ������ â
	if (m_tFrame.iFrameStartX == 14) {
		if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN)) {
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"03 - MenuSelect.wav", SOUND_EFFECT, 1.0f);
			if (m_iArrowPos == 245) {
				m_iArrowPos += 200;
			}
			else {
				m_iArrowPos += 40;
			}
		}
		if (CKeyMgr::Get_Instance()->Key_Down(VK_UP)) {
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"03 - MenuSelect.wav", SOUND_EFFECT, 1.0f);		
			if (m_iArrowPos == 445) {
				m_iArrowPos -= 200;
			}
			else {
				m_iArrowPos -= 40;
			}
		}
	}

	return 0;
}

void CInventory::Late_Update(void)
{
	// �ִϸ��̼�
	if (!m_bClose) {
		if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStartX;
			if (m_tFrame.iFrameStartX > m_tFrame.iFrameEndX) {
				m_tFrame.iFrameStartX = 14;
			}
			m_tFrame.dwTime = GetTickCount();
		}
	}
	else if (m_bClose) {
		if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
		{
			--m_tFrame.iFrameStartX;
			if (m_tFrame.iFrameStartX < m_tFrame.iFrameEndX) {
				m_tFrame.iFrameStartX = 0;
			}
			m_tFrame.dwTime = GetTickCount();
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('Z')) {
		if (m_iArrowPos == 165) {
			dynamic_cast<CPlayer*>(m_pPlayer)->Set_WeaponType(WEAPON_NORMAL);
			m_bClose = true;
		}
		if (m_iArrowPos == 205) {
			dynamic_cast<CPlayer*>(m_pPlayer)->Set_WeaponType(WEAPON_RS);
			m_bClose = true;
		}
		if (m_iArrowPos == 245) {
			dynamic_cast<CPlayer*>(m_pPlayer)->Set_WeaponType(WEAPON_MB);
			m_bClose = true;
		}
		if (m_iArrowPos == 445) {
			dynamic_cast<CPlayer*>(m_pPlayer)->Set_WeaponType(WEAPON_RUSH);
			m_bClose = true;
		}
	}
}

void CInventory::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		450, // ������� x��ġ�� ��ǥ
		100, // ���� ���� y��ġ�� ��ǥ)
		250, // ���� ���� ���� ����
		412, // ���� ���� ���� ����
		hMemDC,	// ������ ��Ʈ�� �̹��� dc
		250 * m_tFrame.iFrameStartX,		// ��Ʈ���� ����� ���� x��ǥ
		0,		// ��Ʈ���� ����� ���� y��ǥ
		250, // ������ ��Ʈ���� ���� ������
		412,// ������ ��Ʈ���� ���� ������
		RGB(128, 0, 128)); //�����ϰ��� �ϴ� ����


	HDC		hArrowDC = CBmpMgr::Get_Instance()->Find_Image(L"Arrow");

	GdiTransparentBlt(hDC,
		480, // ������� x��ġ�� ��ǥ
		m_iArrowPos, // ���� ���� y��ġ�� ��ǥ)
		20, // ���� ���� ���� ����
		17, // ���� ���� ���� ����
		hArrowDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		0,		// ��Ʈ���� ����� ���� y��ǥ
		20, // ������ ��Ʈ���� ���� ������
		17,// ������ ��Ʈ���� ���� ������
		RGB(128, 0, 128)); //�����ϰ��� �ϴ� ����
}

void CInventory::Release(void)
{
}
