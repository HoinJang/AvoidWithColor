#pragma once
#include "cMyInclude.h"
#include "cSprite.h"
#include "cAnimation.h"
#include "cObject.h"

class cRedObject : public cObject 
{
public:
	cRedObject(int x, int y, int mType, Type type) : cObject(x, y, mType, type) {}
	~cRedObject() {}
public:
	virtual void Update();
private:
};