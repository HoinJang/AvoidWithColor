#pragma once
#include "cMyInclude.h"
#include "cSprite.h"
#include "cAnimation.h"
#include "cObject.h"

class cGreenObject : public cObject
{
public:
	cGreenObject(int x, int y, int mType, Type type);
	~cGreenObject();
public:
	virtual void Update();
	virtual void Render(HDC hdc);
private:
};