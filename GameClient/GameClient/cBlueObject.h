#pragma once
#include "cMyInclude.h"
#include "cSprite.h"
#include "cAnimation.h"
#include "cObject.h"

class cBlueObject : public cObject
{
public:
	cBlueObject(int x, int y, int mType, Type type);
	~cBlueObject();
public:
	virtual void Update();
	virtual void Render(HDC hdc);
private:
};