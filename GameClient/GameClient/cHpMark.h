#pragma once
#include "cMyInclude.h"
#include "cSprite.h"

class cHpMark
{
private:
	int width;
	int height;
	int hp;
	int x;
	int y;
private:
	cSprite*		pSprite;
public:
	cHpMark();
	~cHpMark();
public:
	void Update();
	void Render(HDC hdc);
public:
	void setHp(int hp) { this->hp = hp; }
	int getHp() { return hp; }
};