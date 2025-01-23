#include "stdafx.h"
#include "ObjMgr.h"

#include "ScrollMgr.h"
#include "TriggerMgr.h"
#include "CollisionMgr.h"


CObjMgr*		CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Object(OBJID eID, CObj * pObj)
{
	if (OBJ_END <= eID || pObj == nullptr)
		return;
		m_ObjList[eID].push_back(pObj);
}

void CObjMgr::Update(void)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		if (m_ObjList[i].size() > 0) {
			for (auto iter = m_ObjList[i].begin();
				iter != m_ObjList[i].end();)
			{
				int iEvent = (*iter)->Update();

				if (OBJ_DEAD == iEvent)
				{
					Safe_Delete<CObj*>(*iter);
					iter = m_ObjList[i].erase(iter);
				}
				else
					++iter;
			}
		}
	}

}

void CObjMgr::Late_Update(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;
		}
	}

	// CCollisionMgr::Collision_Tile(m_ObjList[OBJ_PLAYER].front(), m_ObjList[OBJ_TILE]);
	// �� vs �÷��̾� �Ҹ�
	CCollisionMgr::Collision_Creature_Bullet(m_ObjList[OBJ_ENEMY], m_ObjList[OBJ_PBULLET]);
	// �÷��̾� vs �� �Ҹ�
	CCollisionMgr::Collision_Creature_Bullet(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_EBULLET]);
	// �÷��̾� �Ҹ� vs �� �Ҹ�
	CCollisionMgr::Collision_Bullet_Bullet(m_ObjList[OBJ_PBULLET], m_ObjList[OBJ_EBULLET]);
	// �÷��̾� vs ��
	CCollisionMgr::Collision_Player_Enemy(m_ObjList[OBJ_PLAYER].front(), m_ObjList[OBJ_ENEMY]);
	// ��� Ÿ�� ����
	CCollisionMgr::Collision_TriggerGoblin(m_ObjList[OBJ_PLAYER].front(), CTriggerMgr::Get_Instance()->Get_TgrList(TRIGGER_GOBLIN));
	// ���� Ÿ�� ����
	CCollisionMgr::Collision_TriggerCloud(m_ObjList[OBJ_PLAYER].front(), CTriggerMgr::Get_Instance()->Get_TgrList(TRIGGER_CLOUD));
	// ���� ����
	CCollisionMgr::Collision_TriggerPipi(m_ObjList[OBJ_PLAYER].front(), CTriggerMgr::Get_Instance()->Get_TgrList(TRIGGER_PIPI));
	// x ��ũ�� ����
	CCollisionMgr::Collision_ScrollTrigger(m_ObjList[OBJ_PLAYER].front(), CTriggerMgr::Get_Instance()->Get_TgrListAry());
	// �Ѿ� �ݻ�Ÿ��
	CCollisionMgr::Collision_Tile_Bullet(m_ObjList[OBJ_PBULLET], m_ObjList[OBJ_TILE]);
	// �÷��̾� ������
	CCollisionMgr::Collision_Item(m_ObjList[OBJ_PLAYER].front(), m_ObjList[OBJ_ITEM]);
	// �÷��̾� ��������
	CCollisionMgr::Collision_RushCoil(m_ObjList[OBJ_PLAYER].front(), m_ObjList[OBJ_PBULLET]);
	// �÷��̾� ��������Ʈ
	CCollisionMgr::Collision_DeadTrigger(m_ObjList[OBJ_PLAYER].front(), CTriggerMgr::Get_Instance()->Get_TgrList(TRIGGER_DEAD));
}


void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}
}

void CObjMgr::Release(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CDeleteObj());
		m_ObjList[i].clear();
	}

}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}
