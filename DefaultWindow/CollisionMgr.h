#pragma once

#include "Obj.h"
#include "Trigger.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	// player 타일관련
	static bool Collision_Tile(CObj* _pCreature); // player가 사용중
	static bool Collision_Tile(CObj* _pCreature, list<CObj*> _tileList); 
	static bool	Collision_Tile(CObj* _pPlayer, float& _fY); // player가 사용중

	// player vs rushcoil
	static void Collision_RushCoil(CObj* _pPlayer, list<CObj*> _pBulletList);

	// PipiEgg 
	static void Collision_Egg(CObj* _pEgg);
	
	static bool Check_Tile(CObj* _pDst, CObj* _pSrc, float* _pX, float* _pY);

	// 고블린 타일용
	static bool Collision_GoblinTile(CObj* _pPlayer, CObj* _GoblinTile);

	// 구름 타일용
	// y값만
	static bool Colision_CloudTileY(CObj* _pPlayer, list<CObj*> _CloudTileList);
	// x y 값 둘다(이동 상태가 아닐때)
	static bool Colision_CloudTile(CObj* _pPlayer, list<CObj*> _CloudTileList);

	// 플레이어 vs 아이템
	static void Collision_Item(CObj* _pPlayer, list<CObj*> _ItemList);

	// 아이템 vs 타일
	static bool Collision_Item_Tile(CObj* _item, list<CObj*> _tileList);

	// 생명체와 총알
	static void Collision_Creature_Bullet(list<CObj*> _pCreature, list<CObj*> _bulletList);

	// 총알 vs 총알
	static void Collision_Bullet_Bullet(list<CObj*> _pBulletList, list<CObj*> _eBulletList);

	// 플레이어 vs 적
	static void Collision_Player_Enemy(CObj* _pPlayer, list<CObj*> _enemyList);

	// 플레이어 vs 고블린트리거
	static void Collision_TriggerGoblin(CObj* _pPlayer, list<CTrigger*> _triggerList);

	// 플레이어 vs 피피트리거
	static void Collision_TriggerPipi(CObj* _pPlayer, list<CTrigger*> _triggerList);

	// 플레이어 vs 구름발판트리거
	static void Collision_TriggerCloud(CObj* _pPlayer, list<CTrigger*> _triggerList);

	// 플레이어 vs 스크롤트리거
	static void Collision_ScrollTrigger(CObj* _pPlayer, list <CTrigger*> _triggerList[TRIGGER_END]);

	// 플레이어 총알 vs 고블린타일
	static void Collision_Tile_Bullet(list<CObj*> _pBullet, list<CObj*> _pTile);

	// 낙사트리거
	static void Collision_DeadTrigger(CObj* _pPlayer, list<CTrigger*> _triggerList);
};

