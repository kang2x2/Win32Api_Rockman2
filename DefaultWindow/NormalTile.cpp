#include "stdafx.h"
#include "NormalTile.h"


CNormalTile::CNormalTile(CNormalTile & _pTile)
{
	m_tInfo = _pTile.Get_Info();
}

CNormalTile::CNormalTile(INFO _info)
{
	m_tInfo = _info;
}

CNormalTile::CNormalTile()
{
}

CNormalTile::~CNormalTile()
{
}

void CNormalTile::Initialize(void)
{
}

void CNormalTile::Late_Update(void)
{
}

void CNormalTile::Release(void)
{
}
