#pragma once
#include "cMyInclude.h"

class cScene
{
public:
	cScene()
	{

	}
	virtual ~cScene()
	{

	}
public:
	virtual void Init() = 0;
	virtual void Destroy() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void KeyBoard(UINT message, WPARAM wParam, LPARAM lParam) = 0;
	virtual void Mouse(UINT _type, int _x, int _y, int _w) = 0;
};