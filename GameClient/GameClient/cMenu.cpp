#include "cMenu.h"
#include "cMain.h"
cMenu::cMenu()
{
	mMessage = 0;
	mBackGround = NULL;
}
cMenu::~cMenu()
{
	SAFE_DELETE(mBackGround);
}
void cMenu::Init()
{
	mMessage = 0;
	if (mBackGround == NULL)
	{
		mBackGround = new cSprite;
		mBackGround->Entry("res/Menu.png", "Menu");
	}
}
void cMenu::Destroy()
{
	SAFE_DELETE(mBackGround);
}
void cMenu::Update()
{
	if (mMessage == 1)
	{
		cMain::getinstance().Trans(Game);
	}
	else if (mMessage == 2)
	{
		cMain::getinstance().Trans(End);
	}
}
void cMenu::Render(HDC hdc)
{
	mBackGround->Render(hdc, "Menu", 0, 0);
}
void cMenu::KeyBoard(UINT message, WPARAM wParam, LPARAM lParam)
{
}

void cMenu::Mouse(UINT _type, int _x, int _y, int _w)
{
	if (_type == WM_LBUTTONDOWN)
	{
		if ((_x > 380) && (_x < 620) && (_y < 650) && (_y > 600))
		{
			mMessage = 1;
		}
		if ((_x > 450) && (_x < 550) && (_y < 750) && (_y > 700))
		{
			mMessage = 2;
		}
	}
}
