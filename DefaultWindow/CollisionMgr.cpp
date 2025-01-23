#include "stdafx.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "ScrollMgr.h"

#include "Player.h"
#include "Air_Man.h"
#include "CoPipi.h"
#include "GoblinTile.h"
#include "CloudTile.h"
#include "SclFix_XTrigger.h"
#include "SclMove_XTrigger.h"
#include "DoorTrigger.h"

#include "SmallDead.h"
#include "RushCoil.h"
#include "Thunder.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

bool CCollisionMgr::Collision_Tile(CObj * _pCreature)
{
	float fX = 0.f, fY = 0.f;
	for (auto& tile : CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE)) {
		if (Check_Tile(_pCreature, tile, &fX, &fY)) {
			// 상 하 충돌
			if (fX > fY)
			{
				if (_pCreature->Get_Info().fY < tile->Get_Info().fY)
				{
					_pCreature->Set_Y(-fY);
					return true;
				}
				else
				{
					_pCreature->Set_Y(fY);
					return false;
				}
			}
			// 좌 우 충돌
			else
			{
				if (_pCreature->Get_Info().fX < tile->Get_Info().fX)
				{
					_pCreature->Set_X(-fX);
					return false;
				}
				else
				{
					_pCreature->Set_X(fX);
					return false;
				}
			}
		}
	}
	return false;
}

bool CCollisionMgr::Collision_Tile(CObj * _pCreature, list<CObj*> _tileList)
{
	float fX = 0.f, fY = 0.f;
	for (auto& tile : _tileList) {
		if (Check_Tile(_pCreature, tile, &fX, &fY)) {
			// 상 하 충돌
			if (fX > fY)
			{
				if (_pCreature->Get_Info().fY < tile->Get_Info().fY)
				{
					_pCreature->Set_Y(-fY);
					return true;
				}
				else
				{
					_pCreature->Set_Y(fY);
				}
			}
			// 좌 우 충돌
			else
			{
				if (_pCreature->Get_Info().fX < tile->Get_Info().fX)
				{
					_pCreature->Set_X(-fX);
				}
				else
				{
					_pCreature->Set_X(fX);
				}
			}
		}
	}
	return false;
}

bool CCollisionMgr::Collision_Tile(CObj * _pPlayer, float & _fY)
{
	float	fX = 0.f, fY = 0.f;
		
	for (auto& tile : CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE)) {
		if (Check_Tile(_pPlayer, tile, &fX, &fY))
		{
			// 상 하 충돌
			if (fX > fY)
			{
				if (_pPlayer->Get_Info().fY < tile->Get_Info().fY)
				{
					_fY = tile->Get_Info().fY;
					return true;
				}
				else
				{
					// _pPlayer->Set_Y(fY);
				}
			}
			// 좌 우 충돌
			else
			{
				if (_pPlayer->Get_Info().fX < tile->Get_Info().fX)
				{
					_pPlayer->Set_X(-fX);
				}
				else
				{
					_pPlayer->Set_X(fX);
				}
			}
		}
	}
	return false;
}

void CCollisionMgr::Collision_RushCoil(CObj * _pPlayer, list<CObj*> _pBulletList)
{
	RECT rc = {};
	for (auto pBullet : _pBulletList) {
		if (IntersectRect(&rc, &_pPlayer->Get_ColRect(), &pBullet->Get_DrawRect())) {
			if (pBullet->Get_Type() == "RushCoil" && dynamic_cast<CRushCoil*>(pBullet)->Get_RushState() == RUSH_IDLE) {
				cout << 1 << endl;
				dynamic_cast<CRushCoil*>(pBullet)->Set_Coil();
				dynamic_cast<CPlayer*>(_pPlayer)->Set_JumpPower(15.f);
				return;
			}
		}
	}
}

void CCollisionMgr::Collision_Egg(CObj * _pEgg)
{
	RECT rc = {};
	for (auto& tile : CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE)) {
		if (IntersectRect(&rc, &_pEgg->Get_DrawRect(), &tile->Get_DrawRect())) {
			// 코피피 소환
			for (int i = 1; i <= 8; ++i) {
				CObjMgr::Get_Instance()->Add_Object(OBJ_ENEMY, new CCoPipi(
				{ _pEgg->Get_Info().fX, _pEgg->Get_Info().fY, 20, 20}, (float)(45 * i)));
			}
			_pEgg->Set_Dead();
			return;
		}
	}

}

bool CCollisionMgr::Check_Tile(CObj * _pDst, CObj * _pSrc, float * _pX, float * _pY)
{
	// 두 객체의 거리차를 구함.
	float fWidth = fabs(_pDst->Get_Info().fX - _pSrc->Get_Info().fX);
	float fHeight = fabs(_pDst->Get_Info().fY - _pSrc->Get_Info().fY);

	// 두 객체의 크기합의 반지름을 구함.
	float fRadiusX = (_pDst->Get_Info().fCX * 0.7f + _pSrc->Get_Info().fCX) * 0.5f;
	float fRadiusY = (_pDst->Get_Info().fCY + _pSrc->Get_Info().fCY) * 0.5f;

	if (fRadiusX > fWidth && fRadiusY > fHeight) {
		*_pX = fRadiusX - fWidth;
		*_pY = fRadiusY - fHeight;
		return true;
	}
	return false;
}

// 플레이어 vs 고블린타일
bool CCollisionMgr::Collision_GoblinTile(CObj * _pPlayer, CObj * _GoblinTile)
{
	if (// _GoblinTile->Get_DrawRect().top == _pPlayer->Get_DrawRect().bottom ||
		_pPlayer->Get_Info().fX > _GoblinTile->Get_DrawRect().left &&
		_pPlayer->Get_Info().fX < _GoblinTile->Get_DrawRect().right) {
		return true;
	}
	return false;
}

bool CCollisionMgr::Colision_CloudTileY(CObj * _pPlayer, list<CObj*> _CloudTileList)
{
	for (auto cloudTile : _CloudTileList) {
		if (cloudTile->Get_Type() == "CloudTile") {
			if (_pPlayer->Get_Info().fX > cloudTile->Get_DrawRect().left &&
				_pPlayer->Get_Info().fX < cloudTile->Get_DrawRect().right && _pPlayer->Get_Ground()) {
				_pPlayer->Set_FixY(cloudTile->Get_Info().fY - 60.f);
				return true;
			}
		}
	}
	return false;
}

// 플레이어 vs 구름타일
bool CCollisionMgr::Colision_CloudTile(CObj * _pPlayer, list<CObj*> _CloudTileList)
{
	for (auto cloudTile : _CloudTileList) {
		if (cloudTile->Get_Type() == "CloudTile") {
			if (_pPlayer->Get_Info().fX > cloudTile->Get_DrawRect().left &&
				_pPlayer->Get_Info().fX < cloudTile->Get_DrawRect().right && _pPlayer->Get_Ground()) {

				_pPlayer->Set_FixY(cloudTile->Get_Info().fY - 60.f);
				// if (((int)dynamic_cast<CCloudTile*>(cloudTile)->GetAngle() / 180) % 2 == 0)
				if(dynamic_cast<CCloudTile*>(cloudTile)->GetAngle() <= 180.f)
				{
					_pPlayer->Set_X(-cloudTile->Get_Speed());
				}
				else 
				{
					_pPlayer->Set_X(cloudTile->Get_Speed());
				}
				return true; 
			}
		}
	}
	return false;
}

// 플레이어 vs 아이템
void CCollisionMgr::Collision_Item(CObj * _pPlayer, list<CObj*> _ItemList)
{
	RECT rc = {};
	for (auto& item : _ItemList) {
		if (IntersectRect(&rc, &_pPlayer->Get_ColRect(), &item->Get_DrawRect())) {
			if (item->Get_Type() == "HpItem") {
				dynamic_cast<CPlayer*>(_pPlayer)->Set_RecovCount(-item->Get_Hp());
				item->Set_Dead();
				break;
			}
			else if (item->Get_Type() == "MpItem") {
				// 무기를 든 상태일때만
				if (dynamic_cast<CPlayer*>(_pPlayer)->Get_WeaponType() != WEAPON_NORMAL) {
					dynamic_cast<CPlayer*>(_pPlayer)->Set_MpCount(-item->Get_Hp());
				}
				item->Set_Dead();
				break;
			}
		}
	}
}

// 아이템 vs 타일
bool CCollisionMgr::Collision_Item_Tile(CObj* _item, list<CObj*> _tileList)
{
	float fX = 0.f, fY = 0.f;
	for (auto& tile : _tileList) {
		if (Check_Tile(_item, tile, &fX, &fY)) {
			if (fX > fY)
			{
				if (_item->Get_Info().fY < tile->Get_Info().fY)
				{
					_item->Set_Y(-fY);
					return true;
				}
			}
		}
	}
	return false;
}

// 크리쳐 vs 총알
void CCollisionMgr::Collision_Creature_Bullet(list<CObj*> _creatureList, list<CObj*> _bulletList)
{
	RECT rc = {};
	for (auto& creature : _creatureList) {
		for (auto& bullet : _bulletList) {
			if (IntersectRect(&rc, &creature->Get_ColRect(), &bullet->Get_DrawRect())) {
				// 보스 타격 시 무적체크
				if (creature->Get_Type() == "Boss") {
					if (!dynamic_cast<CAir_Man*>(creature)->Get_Invincible()) {
						creature->Set_Hp(bullet->Get_Damage());
						bullet->Set_Dead();
						dynamic_cast<CAir_Man*>(creature)->HpBar_Update();
						dynamic_cast<CAir_Man*>(creature)->Set_Invincible();
						break;
					}
					else {
						bullet->Set_Dead();
						break;
					}
				}
				// 일반몹
				else if(creature->Get_Type() == "Enemy"){
					CSoundMgr::Get_Instance()->StopSound(SOUND_EHIT);
					CSoundMgr::Get_Instance()->PlaySound(L"enemy_hit.wav", SOUND_EHIT, 1.0f);
					creature->Set_Hp(bullet->Get_Damage());
					bullet->Set_Dead();
					break;
				}
				// 플레이어
				else if (creature->Get_Type() == "Player") {
					if (!dynamic_cast<CPlayer*>(creature)->Get_Invincible()) {
						CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
						CSoundMgr::Get_Instance()->StopSound(SOUND_CHARGE);
						CSoundMgr::Get_Instance()->PlaySound(L"07 - MegamanDamage.wav", SOUND_EFFECT, 1.0f);
						creature->Set_Hp(bullet->Get_Damage());
						bullet->Set_Dead();
						dynamic_cast<CPlayer*>(creature)->HpBar_Update();
						dynamic_cast<CPlayer*>(creature)->Set_Invincible();
						break;
					}
				}
				break;
			}
		}
	}
	
}

// 총알 vs 총알
void CCollisionMgr::Collision_Bullet_Bullet(list<CObj*> _pBulletList, list<CObj*> _eBulletList)
{
	RECT rc = {};
	for (auto& pBullet : _pBulletList) {
		for (auto& eBullet : _eBulletList) {
			if (IntersectRect(&rc, &pBullet->Get_DrawRect(), &eBullet->Get_DrawRect())) {
				CSoundMgr::Get_Instance()->StopSound(SOUND_REFLECT);
				CSoundMgr::Get_Instance()->PlaySound(L"11 - Dink.wav", SOUND_REFLECT, 1.0f);
				// 풀차지
				if (!eBullet->Get_Reflect() && (eBullet->Get_Type() == "bossBullet") && (pBullet->Get_Type() == "pFcBullet")) {
					eBullet->Set_Reflect();
					eBullet->Set_Speed(20.f);
					pBullet->Set_Speed(20.f);
					if (eBullet->Get_bRight()) {
						eBullet->Set_Angle(35.f);
						pBullet->Set_Angle(35.f);
						pBullet->Set_ImgRight(true);
						pBullet->Set_iImgPosX(1);
						pBullet->Set_iFrameEndX(0);
					}
					else {
						eBullet->Set_Angle(-215.f);
						pBullet->Set_Angle(-215.f);
						pBullet->Set_ImgRight(false);
						pBullet->Set_iImgPosX(0);
						pBullet->Set_iFrameEndX(1);
					}
				}
				// 리프실드 vs 번개
				else if (!eBullet->Get_Reflect() && (eBullet->Get_Type() == "eBullet") && (pBullet->Get_Type() == "pReefShield")) {
					eBullet->Set_Reflect();
					dynamic_cast<CThunder*>(eBullet)->Set_UpPower();
					break;
				}
				// 리프실드 vs 보스불릿
				else if (!eBullet->Get_Reflect() && (eBullet->Get_Type() == "bossBullet") && (pBullet->Get_Type() == "pReefShield")) {
					eBullet->Set_Reflect();
					eBullet->Set_Speed(20.f);
					if (eBullet->Get_bRight()) {
						eBullet->Set_Angle(35.f);
					}
					else {
						eBullet->Set_Angle(-215.f);
					}
				}
				// 그 외
				else if(!eBullet->Get_Reflect() && (eBullet->Get_Type() == "bossBullet") && !(pBullet->Get_Type() == "pFcBullet") && !(pBullet->Get_Type() == "pReefShield")){
					pBullet->Set_Reflect();
					if (pBullet->Get_bRight()) {
						pBullet->Set_Speed(15.0f);
						pBullet->Set_Angle(-215.f);
					}
					else {
						pBullet->Set_Speed(15.0f);
						pBullet->Set_Angle(35.f);
					}
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Player_Enemy(CObj * _pPlayer, list<CObj*> _enemyList)
{
	RECT rc = {};
	for (auto& enemy : _enemyList) {
		if (IntersectRect(&rc, &_pPlayer->Get_ColRect(), &enemy->Get_DrawRect())) {
			if (!dynamic_cast<CPlayer*>(_pPlayer)->Get_Invincible()) {	
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->StopSound(SOUND_CHARGE);
				CSoundMgr::Get_Instance()->PlaySound(L"07 - MegamanDamage.wav", SOUND_EFFECT, 1.0f);
				_pPlayer->Set_Hp(enemy->Get_Damage());
				dynamic_cast<CPlayer*>(_pPlayer)->HpBar_Update();
				dynamic_cast<CPlayer*>(_pPlayer)->Set_Invincible();
				break;
			}
			break;
		}
	}
}

void CCollisionMgr::Collision_TriggerGoblin(CObj * _pPlayer, list<CTrigger*> _triggerList)
{
	RECT rc = {};
	for (auto& trigger : _triggerList) {
		if (IntersectRect(&rc, &_pPlayer->Get_DrawRect(), &trigger->Get_DrawRect())) {
			trigger->Create_GoblinTile(trigger->Get_TargetInfo());
		}
	}
}

void CCollisionMgr::Collision_TriggerPipi(CObj * _pPlayer, list<CTrigger*> _triggerList)
{
	RECT rc = {};
	for (auto& trigger : _triggerList) {
		if (IntersectRect(&rc, &_pPlayer->Get_DrawRect(), &trigger->Get_DrawRect())) {
			trigger->Create_Pipi(trigger->Get_TargetInfo());
		}
	}
}

void CCollisionMgr::Collision_TriggerCloud(CObj * _pPlayer, list<CTrigger*> _triggerList)
{
	RECT rc = {};
	for (auto& trigger : _triggerList) {
		if (IntersectRect(&rc, &_pPlayer->Get_DrawRect(), &trigger->Get_DrawRect())) {
			trigger->Create_CloudTile(trigger->Get_TargetInfo());
		}
	}
}

void CCollisionMgr::Collision_ScrollTrigger(CObj * _pPlayer, list <CTrigger*> _triggerList[TRIGGER_END])
{
	RECT rc = {};
	
	for (size_t i = 0; i < TRIGGER_END; ++i) {
		for (auto& trigger : _triggerList[i]) {
			if (IntersectRect(&rc, &_pPlayer->Get_DrawRect(), &trigger->Get_DrawRect())) {
				// 오른쪽 스크롤 고정
				if (trigger->Get_Type() == "FixRightX") {
					CScrollMgr::Get_Instance()->Set_MaxScrollX(trigger->Get_ScrollPos());
					trigger->Set_Dead();
					return;
				}
				// 왼쪽 스크롤 고정
				else if (trigger->Get_Type() == "FixLeftX") {
					CScrollMgr::Get_Instance()->Set_MinScrollX(trigger->Get_ScrollPos());
					trigger->Set_Dead();
					return;
				}
				// y스크롤 이동
				else if (trigger->Get_Type() == "MoveY") {
					CScrollMgr::Get_Instance()->Scroll_SetMinY();
					trigger->Set_Dead();
					return;
				}
				// x스크롤 이동
				else if (trigger->Get_Type() == "MoveRightX") {
					CScrollMgr::Get_Instance()->Set_ScrollMoveX(true);
					CScrollMgr::Get_Instance()->Set_MaxScrollX(trigger->Get_ScrollPos());
					CScrollMgr::Get_Instance()->Set_MinScrollX(
					dynamic_cast<CSclMove_XTrigger*>(trigger)->Get_LeftRockPos());

					trigger->Set_Dead();
					return;
				}
				// 도어 트리거
				else if (trigger->Get_Type() == "BossDoor" &&
					dynamic_cast<CDoorTrigger*>(trigger)->Get_TriggerNum() == 0) {
					CScrollMgr::Get_Instance()->Set_ScrollMoveX(true);
					CScrollMgr::Get_Instance()->Set_MaxScrollX(trigger->Get_ScrollPos());
					CScrollMgr::Get_Instance()->Set_MinScrollX(
					dynamic_cast<CDoorTrigger*>(trigger)->Get_LeftRockPos());
					dynamic_cast<CDoorTrigger*>(trigger)->Set_TriggerNum(1);

					// trigger->Set_Dead();
					return;
				}
				// 보스 트리거
				else if (trigger->Get_Type() == "BossTrigger") {
					// 보스 등장 시 모든 몬스터 제거
					// for_each(CObjMgr::Get_Instance()->Get_ObjList(OBJ_ENEMY).begin(), CObjMgr::Get_Instance()->Get_ObjList(OBJ_ENEMY).end(), CDeleteObj());
					// CObjMgr::Get_Instance()->Get_ObjList(OBJ_ENEMY).clear();

					CObjMgr::Get_Instance()->Add_Object(OBJ_ENEMY, new CAir_Man(trigger->Get_TargetInfo()));
					CSoundMgr::Get_Instance()->StopAll();
					CSoundMgr::Get_Instance()->PlayBGM(L"BossBattle.wav", 1.0f);
					trigger->Set_Dead();
					return;
				}
			}
		}
	}
	
}

// 고블린 타일 vs 총알
void CCollisionMgr::Collision_Tile_Bullet(list<CObj*> _pBulletList, list<CObj*> _pTileList)
{
	RECT rc = {};
	for (auto& bullet : _pBulletList) {
		for (auto& tile : _pTileList) {
			if (tile->Get_Type() == "GoblinTile" && !bullet->Get_Reflect() && IntersectRect(&rc, &bullet->Get_DrawRect(), &tile->Get_DrawRect())) {
				bullet->Set_Reflect();
				CSoundMgr::Get_Instance()->StopSound(SOUND_REFLECT);
				CSoundMgr::Get_Instance()->PlaySound(L"11 - Dink.wav", SOUND_REFLECT, 1.0f);
				if (bullet->Get_bRight()) {
					if (bullet->Get_Type() == "pFcBullet") {
						bullet->Set_ImgRight(false);
						bullet->Set_iImgPosX(1);
						bullet->Set_iFrameEndX(0);
						bullet->Set_Speed(15.f);
					}
					else {
						bullet->Set_Speed(10.f);
					}
					bullet->Set_Angle(-215.f);
				}
				else {
					if (bullet->Get_Type() == "pFcBullet") {
						bullet->Set_ImgRight(true);
						bullet->Set_iImgPosX(0);
						bullet->Set_iFrameEndX(1);
						bullet->Set_Speed(15.f);
					}
					else {
						bullet->Set_Speed(10.f);
					}
					bullet->Set_Angle(35.f);
				}
			}
		}
	}
}

void CCollisionMgr::Collision_DeadTrigger(CObj * _pPlayer, list<CTrigger*> _triggerList)
{
	RECT rc = {};
	for (auto& trigger : _triggerList) {
		if (IntersectRect(&rc, &_pPlayer->Get_ColRect(), &trigger->Get_DrawRect())) {
			_pPlayer->Set_DeadHp();
		}
	}
}
