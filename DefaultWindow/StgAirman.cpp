#include "stdafx.h"
#include "StgAirman.h"
#include "ObjMgr.h"
#include "TriggerMgr.h"
#include "AbstractFactory.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "EffectMgr.h"
#include "KeyMgr.h"

#include "Player.h"
#include "Matasaburo.h"
#include "Air_Man.h"
#include "NormalTile.h"
#include "CloudTile.h"

#include "LargeMp.h"

#include "GoblinTrigger.h"
#include "PipiTrigger.h"
#include "SclFix_XTrigger.h"
#include "SclMove_YTrigger.h"
#include "SclMove_XTrigger.h"
#include "BossTrigger.h"
#include "CloudTrigger.h"
#include "DeadTrigger.h"
#include "DoorTrigger.h"

#include "Pipi.h"

bool   m_bPause;
bool   m_bGameover = false;
bool   m_bClear;
int	   m_iClearTime;
CStgAirman::CStgAirman()
{
}


CStgAirman::~CStgAirman()
{
	Release();
}

void CStgAirman::Initialize(void)
{
	m_fPushPower = 0;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/AirMan_Stage.bmp", L"Background");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Ready.bmp", L"Ready");

	m_tReadyFrame.iFrameStartX = 0;
	m_tReadyFrame.iFrameEndX = 1;
	m_tReadyFrame.dwSpeed = 100;
	m_tReadyFrame.dwTime = GetTickCount();

	// 플레이어 
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

	// 마타사부로
	CObjMgr::Get_Instance()->Add_Object(OBJ_ENEMY, new CMatasaburo({ 7230, 1388, 100, 80 }));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ENEMY, new CMatasaburo({ 8680, 1388, 100, 80 }));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ENEMY, new CMatasaburo({ 8930, 1313, 100, 80 }));

	// 고블린 트리거 세팅
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_GOBLIN, 
		new CGoblinTrigger({ 550.f, 250.f, 50.f, 50.f },{ 750.f, 350, 180.f, 180.f }));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_GOBLIN,
		new CGoblinTrigger({ 990.f, 250.f, 50.f, 50.f }, { 1175.f, 320.f, 180.f, 180.f }));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_GOBLIN,
		new CGoblinTrigger({ 1350.f, 250.f, 50.f, 50.f }, { 1600.f, 300.f, 180.f, 180.f }));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_GOBLIN,
		new CGoblinTrigger({ 1760.f, 210.f, 50.f, 50.f }, { 1950.f, 320.f, 180.f, 180.f }));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_GOBLIN,
		new CGoblinTrigger({ 2160.f, 225.f, 50.f, 50.f }, { 2320.f, 320.f, 180.f, 180.f }));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_GOBLIN,
		new CGoblinTrigger({ 5745.f, 1450.f, 50.f, 200.f }, { 5930.f, 1650.f, 180.f, 180.f }));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_GOBLIN,
		new CGoblinTrigger({ 6000.f, 1560.f, 10.f, 50.f }, { 6220.f, 1550.f, 180.f, 180.f }));
	
	// 구름 트리거 세팅
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_CLOUD,
		new CCloudTrigger({ 2450.f, 300.f, 10.f, 600.f }, { 2850.f, 320.f, 80.f, 50.f }));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_CLOUD,
		new CCloudTrigger({ 2750.f, 300.f, 10.f, 600.f }, { 3200.f, 220.f, 80.f, 50.f }));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_CLOUD,
		new CCloudTrigger({ 2950.f, 400.f, 10.f, 600.f }, { 3550.f, 360.f, 80.f, 50.f }));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_CLOUD,
		new CCloudTrigger({ 3250.f, 420.f, 10.f, 600.f }, { 3900.f, 260.f, 80.f, 50.f }));
	
	// 피피 트리거
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_PIPI,
		new CPipiTrigger({ 4300.f, 300.f, 50.f, 600.f }, { 4650, 110, 50, 44 }));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_PIPI,
		new CPipiTrigger({ 4650.f, 300.f, 50.f, 600.f }, { 5000, 110, 50, 44 }));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_PIPI,
		new CPipiTrigger({ 5100.f, 300.f, 50.f, 600.f }, { 5450, 110, 50, 44 }));
	
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_PIPI,
		new CPipiTrigger({ 7200.f, 1500.f, 50.f, 600.f }, { 7550, 1320, 50, 44 }));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_PIPI,
		new CPipiTrigger({ 8250.f, 1500.f, 50.f, 600.f }, { 8600, 1320, 50, 44 }));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_PIPI,
		new CPipiTrigger({ 9050.f, 1500.f, 50.f, 600.f }, { 9450, 1320, 50, 44 }));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_PIPI,
		new CPipiTrigger({ 9700.f, 1500.f, 50.f, 600.f }, { 10050, 1320, 50, 44 }));
	
	// 스크롤x 트리거
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGEL_X,
		new CSclFix_XTrigger({ 6000.f, 700.f, 1000.f, 10.f }, false, -5080));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_X,
		new CSclFix_XTrigger({ 5555.f, 1500.f, 50.f, 600.f }, true, -9570));

	// 보스방 입장 연출 트리거
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_DOOR,
		new CDoorTrigger({ 10340.f, 1427.f, 50.f, 150.f }, true, -10340, -10340));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_DOOR,
		new CDoorTrigger({ 11110.f, 1427.f, 50.f, 150.f }, true, -11100, -11100));


	// 스크롤y 트리거
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_Y,
		new CSclMove_YTrigger({ 6000.f, 650.f, 1000.f, 10.f }));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_Y,
		new CSclMove_YTrigger({ 5200.f, 1250.f, 1000.f, 10.f }));

	// 낙사 포인트
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_DEAD, new CDeadTrigger({ 2250.f, 650.f, 4500.f, 50.f }));
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_DEAD, new CDeadTrigger({ 5000.f, 1850.f, 10000.f, 50.f }));

	// 보스 트리거
	CTriggerMgr::Get_Instance()->Add_Trigger(TRIGGER_BOSS,
		new CBossTrigger({ 11150.f, 1610.f, 150.f, 20.f }, { 11760.f, 1200.f, 104.f, 83.f }));

	Load_Data();
	CSoundMgr::Get_Instance()->PlayBGM(L"AirmanStage.wav", 0.4f);

	m_cloud.Initialize();

	m_iReadyTime = GetTickCount() + 4000;
	m_bStart = false;
	// m_bStart = true; 
	m_bPause = false;

	// 인벤
	m_pInven = nullptr;
	m_bInven = false;
}

int CStgAirman::Update(void)
{
	// 게임 오버 관련
	if (m_bGameover) {
		CObjMgr::Get_Instance()->Destroy_Instance();
		CTriggerMgr::Get_Instance()->Destroy_Instance();
		CEffectMgr::Get_Instance()->Destroy_Instance();
		m_bGameover = false;
		m_fPushPower = 0;
		CScrollMgr::Get_Instance()->Set_ScrollFixX(0);
		CScrollMgr::Get_Instance()->Set_ScrollFixY(0);
		CScrollMgr::Get_Instance()->Set_MinScrollX(0);
		CScrollMgr::Get_Instance()->Scroll_SetMinFixY(600);
		CSceneMgr::Get_Instance()->Init_Scene(SC_STAGE_AIRMAN);
		m_bInven = false;
		//CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_AIRMAN);
	}	

	// 게임 시작전 레디
	if (!m_bStart && !m_bGameover) {
		if (m_tReadyFrame.dwTime + m_tReadyFrame.dwSpeed < GetTickCount())
		{
			++m_tReadyFrame.iFrameStartX;
			if (m_tReadyFrame.iFrameStartX > m_tReadyFrame.iFrameEndX)
				m_tReadyFrame.iFrameStartX = 0;

			m_tReadyFrame.dwTime = GetTickCount();
		}
	}
	

	// 게임 시작!
	if (!m_bStart && m_iReadyTime <= GetTickCount() && !m_bGameover) {
		m_bStart = true;
	}

	if (m_bStart && !m_bGameover) {
		// 스크롤 연출중이 아니면서
		if ((CScrollMgr::Get_Instance()->Get_ScrollMinY() >= CScrollMgr::Get_Instance()->Get_ScrollY() + WINCY &&
			!CScrollMgr::Get_Instance()->Get_SCrollMoveX())) {
			// 게임이 정지중이지 않으면 
			if (!m_bPause && !m_bInven) {
				CObjMgr::Get_Instance()->Update();
				CEffectMgr::Get_Instance()->Update();
			}
		}

		CTriggerMgr::Get_Instance()->Update();
	}

	// 인벤토리(keyDown()으로 하면 난리난다.(이미 상태 머신에서 사용하고 있어서?))
	if (CKeyMgr::Get_Instance()->Key_InvenDown()) {
		if (!m_pInven) {
			m_bInven = true;
			m_pInven = new CInventory(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front());
		}
		else {
			m_pInven->Set_CloseInven();
		}
	}
	// 인벤
	if (!m_bClear && m_bInven) {
		if (m_pInven->Update()) {
			m_bInven = false;
			delete m_pInven;
			m_pInven = nullptr;
		}
	}

	m_cloud.Update();

	return 0;
}

void CStgAirman::Late_Update(void)
{
	if (m_bStart && !m_bGameover && !m_bInven) {
		CObjMgr::Get_Instance()->Late_Update();
		CEffectMgr::Get_Instance()->Late_Update();
		CTriggerMgr::Get_Instance()->Late_Update();
	}

	// 인벤
	if (!m_bClear && m_bInven) m_pInven->Late_Update();

	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CStgAirman::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Background");

	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, (int)fScrollX, (int)fScrollY, 11904, 1800, hGroundDC, 0, 0, SRCCOPY);

	HDC		hReadyDC = CBmpMgr::Get_Instance()->Find_Image(L"Ready");

	if (!m_bStart && !m_bGameover) {
		BitBlt(hDC, 300, 200, 200, 60, hReadyDC, m_tReadyFrame.iFrameStartX * 200, 0, SRCCOPY);
	}

	if (m_bStart && !m_bGameover && !m_bInven){
		CObjMgr::Get_Instance()->Render(hDC);
		CEffectMgr::Get_Instance()->Render(hDC);
		CTriggerMgr::Get_Instance()->Render(hDC);
	}

	m_cloud.Render(hDC);

	// 인벤
	if (!m_bClear && m_bInven) m_pInven->Render(hDC);

	if (m_bStart && !m_bGameover && !m_bInven) {
		dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front())->Pl_HpBar_Render(hDC);
		if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front())->Get_WeaponType() != WEAPON_NORMAL &&
			dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front())->Get_WeaponType() != WEAPON_RUSH) {
			dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front())->Pl_MpBar_Render(hDC);
		}
	}
	
	//dynamic_cast<CAir_Man*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_ENEMY).front())->Boss_HpBar_Render(hDC);
}


void CStgAirman::Load_Data(void)
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
		CObjMgr::Get_Instance()->Add_Object(OBJ_TILE, pTile);
	}

	CloseHandle(hFile);
}

void CStgAirman::Release(void)
{
	if (m_pInven) {
		delete m_pInven;
		m_pInven = nullptr;
	}
}


