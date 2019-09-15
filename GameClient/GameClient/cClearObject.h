#pragma once
#include "cMyInclude.h"
#include "cSprite.h"
#include "cAnimation.h"
#include "cObject.h"

class cClearObject : public cObject
{
public:
	cClearObject(int x, int y, int mType, Type type);
	~cClearObject();
public:
	virtual void Update();
	virtual void Render(HDC hdc);
private:
};
