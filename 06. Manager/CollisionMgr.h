#pragma once

#include "Obj.h"
#include "Trigger.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	// player Ÿ�ϰ���
	static bool Collision_Tile(CObj* _pCreature); // player�� �����
	static bool Collision_Tile(CObj* _pCreature, list<CObj*> _tileList); 
	static bool	Collision_Tile(CObj* _pPlayer, float& _fY); // player�� �����

	// player vs rushcoil
	static void Collision_RushCoil(CObj* _pPlayer, list<CObj*> _pBulletList);

	// PipiEgg 
	static void Collision_Egg(CObj* _pEgg);
	
	static bool Check_Tile(CObj* _pDst, CObj* _pSrc, float* _pX, float* _pY);

	// ��� Ÿ�Ͽ�
	static bool Collision_GoblinTile(CObj* _pPlayer, CObj* _GoblinTile);

	// ���� Ÿ�Ͽ�
	// y����
	static bool Colision_CloudTileY(CObj* _pPlayer, list<CObj*> _CloudTileList);
	// x y �� �Ѵ�(�̵� ���°� �ƴҶ�)
	static bool Colision_CloudTile(CObj* _pPlayer, list<CObj*> _CloudTileList);

	// �÷��̾� vs ������
	static void Collision_Item(CObj* _pPlayer, list<CObj*> _ItemList);

	// ������ vs Ÿ��
	static bool Collision_Item_Tile(CObj* _item, list<CObj*> _tileList);

	// ����ü�� �Ѿ�
	static void Collision_Creature_Bullet(list<CObj*> _pCreature, list<CObj*> _bulletList);

	// �Ѿ� vs �Ѿ�
	static void Collision_Bullet_Bullet(list<CObj*> _pBulletList, list<CObj*> _eBulletList);

	// �÷��̾� vs ��
	static void Collision_Player_Enemy(CObj* _pPlayer, list<CObj*> _enemyList);

	// �÷��̾� vs ���Ʈ����
	static void Collision_TriggerGoblin(CObj* _pPlayer, list<CTrigger*> _triggerList);

	// �÷��̾� vs ����Ʈ����
	static void Collision_TriggerPipi(CObj* _pPlayer, list<CTrigger*> _triggerList);

	// �÷��̾� vs ��������Ʈ����
	static void Collision_TriggerCloud(CObj* _pPlayer, list<CTrigger*> _triggerList);

	// �÷��̾� vs ��ũ��Ʈ����
	static void Collision_ScrollTrigger(CObj* _pPlayer, list <CTrigger*> _triggerList[TRIGGER_END]);

	// �÷��̾� �Ѿ� vs ���Ÿ��
	static void Collision_Tile_Bullet(list<CObj*> _pBullet, list<CObj*> _pTile);

	// ����Ʈ����
	static void Collision_DeadTrigger(CObj* _pPlayer, list<CTrigger*> _triggerList);
};

