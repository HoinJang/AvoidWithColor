#pragma once

#include "cMyInclude.h"
#include "cMyDefine.h"

class cObject
{
protected:
	short				x;
	short				y;
	short				mType;
	short				cType;
public:
	cObject(short x, short y, short mType, Type type);
	~cObject();
public:
	short getX() { return this->x; }
	short getY() { return this->y; }
	short getMtype() { return this->mType; }
	short getType() { return this->cType; }
};