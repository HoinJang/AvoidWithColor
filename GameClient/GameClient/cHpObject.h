#pragma once
#include "cMyInclude.h"
#include "cSprite.h"
#include "cAnimation.h"
#include "cObject.h"

class cHpObject : public cObject
{
public:
	cHpObject(int x, int y, int mType, Type type) : cObject(x, y, mType, type) {}
	~cHpObject() {}
	virtual void Update();
}; 
