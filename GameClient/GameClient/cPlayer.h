#pragma once
#include "cMyInclude.h"
#include "cSprite.h"
#include "cAnimation.h"


class cPlayer
{
private:
	int				width;
	int				height;
	short			selectColor;
	short			hp;
private:
	cSprite*		pSprite;
	short			x;
	short			y;
	BOOL			KeyBuffer[256];
	KeyBoard_Data	key;
public:
	cPlayer();
	cPlayer(int x, int y);
	~cPlayer();
public:
	void Render(HDC hdc);
	void KeyBoard(UINT message, WPARAM wParam, LPARAM lParam);
private:
	void Setting();
public:
	short getX() { return this->x; }
	short getY() { return this->y; }
	short getType() { return this->selectColor; }
	short getHp() { return this->hp; }
	KeyBoard_Data getKeyData() { return this->key; }
	void setColor(int color) { this->selectColor = color; }
	void setX(int xpos) { this->x = xpos; }
	void setY(int ypos) { this->y = ypos; }
	void setHp(int hp) { this->hp = hp; }
};