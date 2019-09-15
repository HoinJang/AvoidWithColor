#include "cObject.h"
#include "cMain.h"

cObject::cObject(short x, short y, short mType, Type type) : x(x), y(y), mType(mType), cType(type)
{
}
cObject::~cObject()
{
}