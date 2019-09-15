#pragma once
#include "cMyInclude.h"
#include "cScene.h"
#include "cSprite.h"
class cMapTool : public cScene
{
private:
public:
	cMapTool();
	~cMapTool();
public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void KeyBoard(UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Mouse(UINT _type, int _x, int _y, int _w) override;
}; 