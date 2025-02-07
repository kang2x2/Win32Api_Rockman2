#pragma once
#include "Tile.h"

class CNormalTile : public CTile
{
public:
	CNormalTile(CNormalTile& _pTile);
	CNormalTile(INFO _info);
	CNormalTile();
	~CNormalTile();

	virtual void Initialize(void) override;
	virtual void Late_Update(void) override;
	virtual void Release(void) override;
};

