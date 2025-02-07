#include "stdafx.h"
#include "Pl_Animation.h"

CPl_Animation::CPl_Animation()
{
}


CPl_Animation::~CPl_Animation()
{
}

void CPl_Animation::Player_Animation(CPlayer* _pPlayer, STATE _eState)
{
	if (m_ePreState != _eState) {
		switch (_eState) {
		// TP
		case ST_UPTP:
			_pPlayer->Set_Charge(false);
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(false);
			_pPlayer->Set_iImgPosX(0);
			_pPlayer->Set_iFrameStartX(0);
			_pPlayer->Set_iFrameEndX(0);
			_pPlayer->Set_iFrameY(0);
			_pPlayer->Set_idwSpeed(200);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_DOWNTP:
			_pPlayer->Set_Charge(false);
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(0);
			_pPlayer->Set_iFrameStartX(0);
			_pPlayer->Set_iFrameEndX(0);
			_pPlayer->Set_iFrameY(0);
			_pPlayer->Set_idwSpeed(200);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_SUCCESTP:
			_pPlayer->Set_Charge(false);
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(1);
			_pPlayer->Set_iFrameStartX(1);
			_pPlayer->Set_iFrameEndX(2);
			_pPlayer->Set_iFrameY(0);
			_pPlayer->Set_idwSpeed(50);
			_pPlayer->Set_idwTime(GetTickCount());
			break;


			// 일반
		case ST_RIDLE:
			_pPlayer->Set_Charge(false);
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(1);
			_pPlayer->Set_iFrameStartX(1);
			_pPlayer->Set_iFrameEndX(2);
			_pPlayer->Set_iFrameY(1);
			_pPlayer->Set_idwSpeed(200);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_LIDLE:
			_pPlayer->Set_Charge(false);
			_pPlayer->Set_FrameKey(L"Player_Left");
			_pPlayer->Set_ImgRight(false);
			_pPlayer->Set_iImgPosX(10);
			_pPlayer->Set_iFrameStartX(10);
			_pPlayer->Set_iFrameEndX(9);
			_pPlayer->Set_iFrameY(1);
			_pPlayer->Set_idwSpeed(200);
			_pPlayer->Set_idwTime(GetTickCount());
			break;


			// 이동
		case ST_RWALK:
			_pPlayer->Set_Charge(false);
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(4);
			_pPlayer->Set_iFrameStartX(4);
			_pPlayer->Set_iFrameEndX(6);
			_pPlayer->Set_iFrameY(1);
			_pPlayer->Set_idwSpeed(100);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_LWALK:
			_pPlayer->Set_Charge(false);
			_pPlayer->Set_FrameKey(L"Player_Left");
			_pPlayer->Set_ImgRight(false);
			_pPlayer->Set_iImgPosX(7);
			_pPlayer->Set_iFrameStartX(7);
			_pPlayer->Set_iFrameEndX(5);
			_pPlayer->Set_iFrameY(1);
			_pPlayer->Set_idwSpeed(100);
			_pPlayer->Set_idwTime(GetTickCount());
			break;


			// 공격
		case ST_RATK:
			_pPlayer->Set_Charge(false);
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(1);
			_pPlayer->Set_iFrameStartX(1);
			_pPlayer->Set_iFrameEndX(1);
			_pPlayer->Set_iFrameY(2);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_LATK:
			_pPlayer->Set_Charge(false);
			_pPlayer->Set_FrameKey(L"Player_Left");
			_pPlayer->Set_ImgRight(false);
			_pPlayer->Set_iImgPosX(10);
			_pPlayer->Set_iFrameStartX(10);
			_pPlayer->Set_iFrameEndX(10);
			_pPlayer->Set_iFrameY(2);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;


			// 이동공격
		case ST_RWALK_ATK:
			_pPlayer->Set_Charge(false);
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(4);
			_pPlayer->Set_iFrameStartX(4);
			_pPlayer->Set_iFrameEndX(6);
			_pPlayer->Set_iFrameY(2);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_LWALK_ATK:
			_pPlayer->Set_Charge(false);
			_pPlayer->Set_FrameKey(L"Player_Left");
			_pPlayer->Set_ImgRight(false);
			_pPlayer->Set_iImgPosX(7);
			_pPlayer->Set_iFrameStartX(7);
			_pPlayer->Set_iFrameEndX(5);
			_pPlayer->Set_iFrameY(2);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;


			// 점프
		case ST_RJUMP:
			_pPlayer->Set_Charge(false);
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(7);
			_pPlayer->Set_iFrameStartX(7);
			_pPlayer->Set_iFrameEndX(7);
			_pPlayer->Set_iFrameY(1);
			_pPlayer->Set_idwSpeed(100);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_LJUMP:
			_pPlayer->Set_Charge(false);
			_pPlayer->Set_FrameKey(L"Player_Left");
			_pPlayer->Set_ImgRight(false);
			_pPlayer->Set_iImgPosX(4);
			_pPlayer->Set_iFrameStartX(4);
			_pPlayer->Set_iFrameEndX(4);
			_pPlayer->Set_iFrameY(1);
			_pPlayer->Set_idwSpeed(100);
			_pPlayer->Set_idwTime(GetTickCount());
			break;


			// 점프 공격
		case ST_RJUMP_ATK:
			_pPlayer->Set_Charge(false);
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(7);
			_pPlayer->Set_iFrameStartX(7);
			_pPlayer->Set_iFrameEndX(7);
			_pPlayer->Set_iFrameY(2);
			_pPlayer->Set_idwSpeed(100);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_LJUMP_ATK:
			_pPlayer->Set_Charge(false);
			_pPlayer->Set_FrameKey(L"Player_Left");
			_pPlayer->Set_ImgRight(false);
			_pPlayer->Set_iImgPosX(4);
			_pPlayer->Set_iFrameStartX(4);
			_pPlayer->Set_iFrameEndX(4);
			_pPlayer->Set_iFrameY(2);
			_pPlayer->Set_idwSpeed(100);
			_pPlayer->Set_idwTime(GetTickCount());
			break;


			// 슬라이딩
		case ST_RSLIDE:
			_pPlayer->Set_Charge(false);
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(0);
			_pPlayer->Set_iFrameStartX(0);
			_pPlayer->Set_iFrameEndX(0);
			_pPlayer->Set_iFrameY(1);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_LSLIDE:
			_pPlayer->Set_Charge(false);
			_pPlayer->Set_FrameKey(L"Player_Left");
			_pPlayer->Set_ImgRight(false);
			_pPlayer->Set_iImgPosX(11);
			_pPlayer->Set_iFrameStartX(11);
			_pPlayer->Set_iFrameEndX(11);
			_pPlayer->Set_iFrameY(1);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;

///////////////////////////////////////////////////////////////////////////////

			// 미들 차지
		case ST_RM_CHARGE:
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(1);
			_pPlayer->Set_iFrameStartX(1);
			_pPlayer->Set_iFrameEndX(1);
			_pPlayer->Set_iImgPosY(3);
			_pPlayer->Set_iFrameY(3);
			_pPlayer->Set_iFrameEndY(5);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_LM_CHARGE:
			_pPlayer->Set_FrameKey(L"Player_Left");
			_pPlayer->Set_ImgRight(false);
			_pPlayer->Set_iImgPosX(10);
			_pPlayer->Set_iFrameStartX(10);
			_pPlayer->Set_iFrameEndX(10);
			_pPlayer->Set_iImgPosY(3);
			_pPlayer->Set_iFrameY(3);
			_pPlayer->Set_iFrameEndY(5);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;


			// 미들 차지 걷기
		case ST_RM_WALK_CHARGE:
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(4);
			_pPlayer->Set_iFrameStartX(4);
			_pPlayer->Set_iFrameEndX(6);
			_pPlayer->Set_iImgPosY(3);
			_pPlayer->Set_iFrameY(3);
			_pPlayer->Set_iFrameEndY(5);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_LM_WALK_CHARGE:
			_pPlayer->Set_FrameKey(L"Player_Left");
			_pPlayer->Set_ImgRight(false);
			_pPlayer->Set_iImgPosX(7);
			_pPlayer->Set_iFrameStartX(7);
			_pPlayer->Set_iFrameEndX(5);
			_pPlayer->Set_iImgPosY(3);
			_pPlayer->Set_iFrameY(3);
			_pPlayer->Set_iFrameEndY(5);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;


			// 미들 차지 점프
		case ST_RM_JUMP_CHARGE:
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(7);
			_pPlayer->Set_iFrameStartX(7);
			_pPlayer->Set_iFrameEndX(7);
			_pPlayer->Set_iImgPosY(3);
			_pPlayer->Set_iFrameY(3);
			_pPlayer->Set_iFrameEndY(5);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_LM_JUMP_CHARGE:
			_pPlayer->Set_FrameKey(L"Player_Left");
			_pPlayer->Set_ImgRight(false);
			_pPlayer->Set_iImgPosX(4);
			_pPlayer->Set_iFrameStartX(4);
			_pPlayer->Set_iFrameEndX(4);
			_pPlayer->Set_iImgPosY(3);
			_pPlayer->Set_iFrameY(3);
			_pPlayer->Set_iFrameEndY(5);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;


			// 미들 차지 슬라이딩
		case ST_RM_SLIDE_CHARGE:
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(0);
			_pPlayer->Set_iFrameStartX(0);
			_pPlayer->Set_iFrameEndX(0);
			_pPlayer->Set_iImgPosY(3);
			_pPlayer->Set_iFrameY(3);
			_pPlayer->Set_iFrameEndY(5);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_LM_SLIDE_CHARGE:
			_pPlayer->Set_FrameKey(L"Player_Left");
			_pPlayer->Set_ImgRight(false);
			_pPlayer->Set_iImgPosX(11);
			_pPlayer->Set_iFrameStartX(11);
			_pPlayer->Set_iFrameEndX(11);
			_pPlayer->Set_iImgPosY(3);
			_pPlayer->Set_iFrameY(3);
			_pPlayer->Set_iFrameEndY(5);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;

///////////////////////////////////////////////////////////////////////////////
 
		// 풀 차지
		case ST_RF_CHARGE:
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(1);
			_pPlayer->Set_iFrameStartX(1);
			_pPlayer->Set_iFrameEndX(1);
			_pPlayer->Set_iImgPosY(6);
			_pPlayer->Set_iFrameY(6);
			_pPlayer->Set_iFrameEndY(7);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_LF_CHARGE:
			_pPlayer->Set_FrameKey(L"Player_Left");
			_pPlayer->Set_ImgRight(false);
			_pPlayer->Set_iImgPosX(10);
			_pPlayer->Set_iFrameStartX(10);
			_pPlayer->Set_iFrameEndX(10);
			_pPlayer->Set_iImgPosY(6);
			_pPlayer->Set_iFrameY(6);
			_pPlayer->Set_iFrameEndY(7);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;


			// 풀차지 이동
		case ST_RF_WALK_CHARGE:
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(4);
			_pPlayer->Set_iFrameStartX(4);
			_pPlayer->Set_iFrameEndX(6);
			_pPlayer->Set_iImgPosY(6);
			_pPlayer->Set_iFrameY(6);
			_pPlayer->Set_iFrameEndY(7);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_LF_WALK_CHARGE:
			_pPlayer->Set_FrameKey(L"Player_Left");
			_pPlayer->Set_ImgRight(false);
			_pPlayer->Set_iImgPosX(7);
			_pPlayer->Set_iFrameStartX(7);
			_pPlayer->Set_iFrameEndX(5);
			_pPlayer->Set_iImgPosY(6);
			_pPlayer->Set_iFrameY(6);
			_pPlayer->Set_iFrameEndY(7);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;


			// 풀 차지 점프
		case ST_RF_JUMP_CHARGE:
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(7);
			_pPlayer->Set_iFrameStartX(7);
			_pPlayer->Set_iFrameEndX(7);
			_pPlayer->Set_iImgPosY(6);
			_pPlayer->Set_iFrameY(6);
			_pPlayer->Set_iFrameEndY(7);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_LF_JUMP_CHARGE:
			_pPlayer->Set_FrameKey(L"Player_Left");
			_pPlayer->Set_ImgRight(false);
			_pPlayer->Set_iImgPosX(4);
			_pPlayer->Set_iFrameStartX(4);
			_pPlayer->Set_iFrameEndX(4);
			_pPlayer->Set_iImgPosY(6);
			_pPlayer->Set_iFrameY(6);
			_pPlayer->Set_iFrameEndX(7);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;


			// 풀 차지 슬라이딩
		case ST_RF_SLIDE_CHARGE:
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(0);
			_pPlayer->Set_iFrameStartX(0);
			_pPlayer->Set_iFrameEndX(0);
			_pPlayer->Set_iImgPosY(6);
			_pPlayer->Set_iFrameY(6);
			_pPlayer->Set_iFrameEndY(7);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_LF_SLIDE_CHARGE:
			_pPlayer->Set_FrameKey(L"Player_Left");
			_pPlayer->Set_ImgRight(false);
			_pPlayer->Set_iImgPosX(11);
			_pPlayer->Set_iFrameStartX(11);
			_pPlayer->Set_iFrameEndX(11);
			_pPlayer->Set_iImgPosY(6);
			_pPlayer->Set_iFrameY(6);
			_pPlayer->Set_iFrameEndY(7);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;


			// 피격 상태
		case ST_RHIT:
			_pPlayer->Set_FrameKey(L"Player_Right");
			_pPlayer->Set_ImgRight(true);
			_pPlayer->Set_iImgPosX(8);
			_pPlayer->Set_iFrameStartX(8);
			_pPlayer->Set_iFrameEndX(8);
			_pPlayer->Set_iImgPosY(1);
			_pPlayer->Set_iFrameY(1);
			_pPlayer->Set_iFrameEndY(1);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		case ST_LHIT:
			_pPlayer->Set_FrameKey(L"Player_Left");
			_pPlayer->Set_ImgRight(false);
			_pPlayer->Set_iImgPosX(3);
			_pPlayer->Set_iFrameStartX(3);
			_pPlayer->Set_iFrameEndX(3);
			_pPlayer->Set_iImgPosY(1);
			_pPlayer->Set_iFrameY(1);
			_pPlayer->Set_iFrameEndY(1);
			_pPlayer->Set_idwSpeed(80);
			_pPlayer->Set_idwTime(GetTickCount());
			break;
		}
		m_ePreState = _eState;
	}
	
}
