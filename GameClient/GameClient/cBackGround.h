#pragma once
#include "cMyInclude.h"
#include "cSprite.h"

class cBackGround
{
private:
	int width;
	int height;
private:
	cSprite*		pSprite;
public:
	cBackGround();
	~cBackGround();
public:
	void Update();
	void Render(HDC hdc);
};