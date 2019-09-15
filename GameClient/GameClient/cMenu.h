#pragma once
#include "cMyInclude.h"
#include "cMyDefine.h"
#include "cScene.h"
#include "cSprite.h"
class cMenu : public cScene
{
private:
	cSprite* mBackGround;
	int mMessage;
public:
	cMenu();
	~cMenu();
public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void KeyBoard(UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Mouse(UINT _type, int _x, int _y, int _w) override;
};