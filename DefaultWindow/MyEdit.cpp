#include "stdafx.h"
#include "MyEdit.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"

CMyEdit::CMyEdit()
{
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/AirMan_Stage.bmp", L"Background");

	//m_cloud.Initialize();

	m_bStart = false;
}	

int CMyEdit::Update(void)
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	// �׸���
	if (!m_bStart && CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
		m_fX = (float)pt.x;
		m_fY = (float)pt.y;
		m_bStart = true;
	}
	if (m_bStart && CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
		m_tileList.push_back(new CNormalTile({m_fX + (pt.x - m_fX) * 0.5f, m_fY + (pt.y - m_fY) * 0.5f, pt.x - m_fX,  pt.y - m_fY }));
		m_bStart = false;
	}
	
	// �����
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON)) {
		for (auto iter = m_tileList.begin();
			iter != m_tileList.end(); iter++) {
			if (pt.x < (*iter)->Get_DrawRect().right &&
				pt.x >(*iter)->Get_DrawRect().left &&
				pt.y > (*iter)->Get_DrawRect().top &&
				pt.y < (*iter)->Get_DrawRect().bottom) {
				delete (*iter);
				(*iter) = nullptr;
				iter = m_tileList.erase(iter);
				break;
			}
		}
	}


	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(15.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-15.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(15.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-15.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		Save_Data();
	}

	if (CKeyMgr::Get_Instance()->Key_Down('L'))
	{
		Load_Data();
	}

	for (auto iter = m_tileList.begin();
		iter != m_tileList.end(); ++iter) {
		(*iter)->Update();
	}


	//m_cloud.Update();

	return 0;
}

void CMyEdit::Late_Update(void)
{
	for (auto& iter : m_tileList)
		iter->Late_Update();
}

void CMyEdit::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Background");

	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, (int)fScrollX, (int)fScrollY, 11904, 1800, hGroundDC, 0, 0, SRCCOPY);

	//m_cloud.Render(hDC);

	for (auto& iter : m_tileList)
		iter->Render(hDC);
}

void CMyEdit::Release(void)
{
	for_each(m_tileList.begin(), m_tileList.end(), CDeleteObj());
	m_tileList.clear();
}

void CMyEdit::Save_Data(void)
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.txt",		// ���� ��ο� ���� �̸��� ���
		GENERIC_WRITE,			// ���� ���� ���(GENERIC_WRITE : ���� ��� GENERIC_READ : �б� ���)
		NULL,					// ���� ��� ����(NULL�� �����ϸ� �������� ����)
		NULL,					// ���� �Ӽ� ����(NULL�� �⺻ ���� �Ӽ� ����)
		CREATE_ALWAYS,			// ���� �ɼ�( CREATE_ALWAYS(���� ����) : ������ ���ٸ� ����, �ִٸ� ����� �ɼ�, OPEN_EXISTING(�б� ����) : ������ ���� ��쿡�� �ҷ����� ����)
		FILE_ATTRIBUTE_NORMAL,	// ���� �Ӽ�(�б� ����, ���� ��) : �ƹ��� �Ӽ��� ���� �Ϲ� ���� ����
		NULL);					// ������ ������ �Ӽ��� ������ ���ø�, �츮�� �Ⱦ��ϱ� NULL

	if (INVALID_HANDLE_VALUE == hFile)	// ���� ���濡 �����ߴٸ�
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte = 0;

	for (auto& iter : m_tileList)
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save success"), L"Success", MB_OK);
}

void CMyEdit::Load_Data(void)
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.txt",		// ���� ��ο� ���� �̸��� ���
		GENERIC_READ,			// ���� ���� ���(GENERIC_WRITE : ���� ��� GENERIC_READ : �б� ���)
		NULL,					// ���� ��� ����(NULL�� �����ϸ� �������� ����)
		NULL,					// ���� �Ӽ� ����(NULL�� �⺻ ���� �Ӽ� ����)
		OPEN_EXISTING,			// ���� �ɼ�( CREATE_ALWAYS(���� ����) : ������ ���ٸ� ����, �ִٸ� ����� �ɼ�, OPEN_EXISTING(�б� ����) : ������ ���� ��쿡�� �ҷ����� ����)
		FILE_ATTRIBUTE_NORMAL,	// ���� �Ӽ�(�б� ����, ���� ��) : �ƹ��� �Ӽ��� ���� �Ϲ� ���� ����
		NULL);					// ������ ������ �Ӽ��� ������ ���ø�, �츮�� �Ⱦ��ϱ� NULL

	if (INVALID_HANDLE_VALUE == hFile)	// ���� ���濡 �����ߴٸ�
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	INFO tInfo{};
	DWORD	dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;
		CNormalTile* pTile = new CNormalTile(tInfo);
		m_tileList.push_back(pTile);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load success"), L"Success", MB_OK);

}

