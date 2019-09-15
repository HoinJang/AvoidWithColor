#include "cLose.h"
#include "cMain.h"

cLose::cLose()
{
	mMessage = 0;
	mBackGround = NULL;
}
cLose::~cLose()
{
	SAFE_DELETE(mBackGround);
}
void cLose::Init()
{
	mMessage = 0;
	if (mBackGround == NULL)
	{
		mBackGround = new cSprite;
		mBackGround->Entry("res/Lose.png", "cLose");
	}

}
void cLose::Destroy()
{
	SAFE_DELETE(mBackGround);
}
void cLose::Update()
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
void cLose::Render(HDC hdc)
{
	mBackGround->Render(hdc, "cLose", 0, 0);
}
void cLose::KeyBoard(UINT message, WPARAM wParam, LPARAM lParam)
{
}

void cLose::Mouse(UINT _type, int _x, int _y, int _w)
{
	if (_type == WM_LBUTTONDOWN)
	{
		if ((_x > 650) && (_x < 950) && (_y < 610) && (_y > 560))
		{
			mMessage = 1;
		}
		if ((_x > 650) && (_x < 780) && (_y < 710) && (_y > 660))
		{
			mMessage = 2;
		}
	}
}
