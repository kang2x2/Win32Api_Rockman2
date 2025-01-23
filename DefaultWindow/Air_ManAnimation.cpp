#include "stdafx.h"
#include "Air_ManAnimation.h"


CAir_ManAnimation::CAir_ManAnimation()
{
}


CAir_ManAnimation::~CAir_ManAnimation()
{
}

void CAir_ManAnimation::Air_Man_Animation(CAir_Man * _pAirman, BOSS_STATE _eState)
{
	if (m_ePreState != _eState) {
		switch (_eState) {
		// 등장
		case BOSS_ST_OPIENING:
			_pAirman->Set_FrameKey(L"Boss_Left");
			_pAirman->Set_ImgRight(false);
			_pAirman->Set_iImgPosX(1);
			_pAirman->Set_iFrameStartX(1);
			_pAirman->Set_iFrameEndX(0);
			_pAirman->Set_iImgPosY(0);
			_pAirman->Set_iFrameY(0);
			_pAirman->Set_iFrameEndY(0);
			_pAirman->Set_idwSpeed(200);
			_pAirman->Set_idwTime(GetTickCount());
			break;
		case BOSS_ST_LIDLE:
			_pAirman->Set_FrameKey(L"Boss_Left");
			_pAirman->Set_ImgRight(false);
			_pAirman->Set_iImgPosX(0);
			_pAirman->Set_iFrameStartX(0);
			_pAirman->Set_iFrameEndX(0);
			_pAirman->Set_iImgPosY(0);
			_pAirman->Set_iFrameY(0);
			_pAirman->Set_iFrameEndY(0);
			_pAirman->Set_idwSpeed(50);
			_pAirman->Set_idwTime(GetTickCount());
			break;
		case BOSS_ST_RIDLE:
			_pAirman->Set_FrameKey(L"Boss_Right");
			_pAirman->Set_ImgRight(true);
			_pAirman->Set_iImgPosX(5);
			_pAirman->Set_iFrameStartX(5);
			_pAirman->Set_iFrameEndX(5);
			_pAirman->Set_iImgPosY(0);
			_pAirman->Set_iFrameY(0);
			_pAirman->Set_iFrameEndY(0);
			_pAirman->Set_idwSpeed(50);
			_pAirman->Set_idwTime(GetTickCount());
			break;
		// 일반 공격
		case BOSS_ST_LFIRE_WIND:
			break;
		case BOSS_ST_RFIRE_WIND:
			break;
		// 회오리 흩뿌리기
		case BOSS_ST_LSPLASH_WIND:
			_pAirman->Set_FrameKey(L"Boss_Left");
			_pAirman->Set_ImgRight(false);
			_pAirman->Set_iImgPosX(2);
			_pAirman->Set_iFrameStartX(2);
			_pAirman->Set_iFrameEndX(2);
			_pAirman->Set_iImgPosY(0);
			_pAirman->Set_iFrameY(0);
			_pAirman->Set_iFrameEndY(0);
			_pAirman->Set_idwSpeed(50);
			_pAirman->Set_idwTime(GetTickCount());
			break;
		case BOSS_ST_RSPLASH_WIND:
			_pAirman->Set_FrameKey(L"Boss_Right");
			_pAirman->Set_ImgRight(true);
			_pAirman->Set_iImgPosX(3);
			_pAirman->Set_iFrameStartX(3);
			_pAirman->Set_iFrameEndX(3);
			_pAirman->Set_iImgPosY(0);
			_pAirman->Set_iFrameY(0);
			_pAirman->Set_iFrameEndY(0);
			_pAirman->Set_idwSpeed(50);
			_pAirman->Set_idwTime(GetTickCount());
			break;
		// 회오리 밀기
		case BOSS_ST_LPUSH_WIND:
			_pAirman->Set_FrameKey(L"Boss_Left");
			_pAirman->Set_ImgRight(false);
			_pAirman->Set_iImgPosX(4);
			_pAirman->Set_iFrameStartX(4);
			_pAirman->Set_iFrameEndX(3);
			_pAirman->Set_iImgPosY(0);
			_pAirman->Set_iFrameY(0);
			_pAirman->Set_iFrameEndY(0);
			_pAirman->Set_idwSpeed(50);
			_pAirman->Set_idwTime(GetTickCount());
			break;
		case BOSS_ST_RPUSH_WIND:
			_pAirman->Set_FrameKey(L"Boss_Right");
			_pAirman->Set_ImgRight(true);
			_pAirman->Set_iImgPosX(1);
			_pAirman->Set_iFrameStartX(1);
			_pAirman->Set_iFrameEndX(2);
			_pAirman->Set_iImgPosY(0);
			_pAirman->Set_iFrameY(0);
			_pAirman->Set_iFrameEndY(0);
			_pAirman->Set_idwSpeed(50);
			_pAirman->Set_idwTime(GetTickCount());
			break;
		// 에어 점프
		case BOSS_ST_LAIR_JUMP:
			_pAirman->Set_FrameKey(L"Boss_Left");
			_pAirman->Set_ImgRight(false);
			_pAirman->Set_iImgPosX(5);
			_pAirman->Set_iFrameStartX(5);
			_pAirman->Set_iFrameEndX(5);
			_pAirman->Set_iImgPosY(0);
			_pAirman->Set_iFrameY(0);
			_pAirman->Set_iFrameEndY(0);
			_pAirman->Set_idwSpeed(10);
			_pAirman->Set_idwTime(GetTickCount());
			break;
		case BOSS_ST_RAIR_JUMP:
			_pAirman->Set_FrameKey(L"Boss_Right");
			_pAirman->Set_ImgRight(true);
			_pAirman->Set_iImgPosX(0);
			_pAirman->Set_iFrameStartX(0);
			_pAirman->Set_iFrameEndX(0);
			_pAirman->Set_iImgPosY(0);
			_pAirman->Set_iFrameY(0);
			_pAirman->Set_iFrameEndY(0);
			_pAirman->Set_idwSpeed(10);
			_pAirman->Set_idwTime(GetTickCount());
			break;
		}


		m_ePreState = _eState;
	}
}
