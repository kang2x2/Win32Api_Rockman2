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

	// 그리기
	if (!m_bStart && CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
		m_fX = (float)pt.x;
		m_fY = (float)pt.y;
		m_bStart = true;
	}
	if (m_bStart && CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
		m_tileList.push_back(new CNormalTile({m_fX + (pt.x - m_fX) * 0.5f, m_fY + (pt.y - m_fY) * 0.5f, pt.x - m_fX,  pt.y - m_fY }));
		m_bStart = false;
	}
	
	// 지우기
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
	HANDLE	hFile = CreateFile(L"../Data/Tile.txt",		// 파일 경로와 파일 이름을 명시
		GENERIC_WRITE,			// 파일 접근 모드(GENERIC_WRITE : 쓰기 모드 GENERIC_READ : 읽기 모드)
		NULL,					// 공유 모드 설정(NULL을 지정하면 공유하지 않음)
		NULL,					// 보안 속성 설정(NULL로 기본 보안 속성 설정)
		CREATE_ALWAYS,			// 파일 옵션( CREATE_ALWAYS(쓰기 전용) : 파일이 없다면 생성, 있다면 덮어쓰기 옵션, OPEN_EXISTING(읽기 전용) : 파일이 있을 경우에만 불러오기 실행)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성(읽기 전용, 숨김 등) : 아무런 속성이 없는 일반 파일 생성
		NULL);					// 생성될 파일의 속성을 제공한 템플릿, 우리는 안쓰니깐 NULL

	if (INVALID_HANDLE_VALUE == hFile)	// 파일 개방에 실패했다면
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
	HANDLE	hFile = CreateFile(L"../Data/Tile.txt",		// 파일 경로와 파일 이름을 명시
		GENERIC_READ,			// 파일 접근 모드(GENERIC_WRITE : 쓰기 모드 GENERIC_READ : 읽기 모드)
		NULL,					// 공유 모드 설정(NULL을 지정하면 공유하지 않음)
		NULL,					// 보안 속성 설정(NULL로 기본 보안 속성 설정)
		OPEN_EXISTING,			// 파일 옵션( CREATE_ALWAYS(쓰기 전용) : 파일이 없다면 생성, 있다면 덮어쓰기 옵션, OPEN_EXISTING(읽기 전용) : 파일이 있을 경우에만 불러오기 실행)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성(읽기 전용, 숨김 등) : 아무런 속성이 없는 일반 파일 생성
		NULL);					// 생성될 파일의 속성을 제공한 템플릿, 우리는 안쓰니깐 NULL

	if (INVALID_HANDLE_VALUE == hFile)	// 파일 개방에 실패했다면
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

