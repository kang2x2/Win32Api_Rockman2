#pragma once
#include "Tile.h"

class CNormalTile : public CTile
{
public:
	CNormalTile(CNormalTile& _pTile);
	CNormalTile(INFO _info);
	CNormalTile();
	~CNormalTile();

	// CTile을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual void Late_Update(void) override;
	virtual void Release(void) override;
};

