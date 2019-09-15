#include "cWin.h"
#include "cMain.h"
cWin::cWin()
{
	mMessage = 0;
	mBackGroundWin = NULL;
}
cWin::~cWin()
{
	SAFE_DELETE(mBackGroundWin);
}
void cWin::Init()
{
	mMessage = 0;
	if (mBackGroundWin == NULL)
	{
		mBackGroundWin = new cSprite;
		mBackGroundWin->Entry("res/Win.png", "cWin");
	}

}
void cWin::Destroy()
{
	SAFE_DELETE(mBackGroundWin);
}
void cWin::Update()
{
	if (mMessage == 1)
	{
		cMain::getinstance().Trans(Menu);
	}
	else if (mMessage == 2)
	{
		cMain::getinstance().Trans(End);
	}
}
void cWin::Render(HDC hdc)
{
	mBackGroundWin->Render(hdc, "cWin", 0, 0);
}
void cWin::KeyBoard(UINT message, WPARAM wParam, LPARAM lParam)
{
}

void cWin::Mouse(UINT _type, int _x, int _y, int _w)
{
	if (_type == WM_LBUTTONDOWN)
	{
		if ((_x > 670) && (_x < 960) && (_y < 610) && (_y > 560))
		{
			mMessage = 1;
		}
		if ((_x > 670) && (_x < 800) && (_y < 700) && (_y > 650))
		{
			mMessage = 2;
		}
	}
}
