#include "cPlayer.h"
#include "cMain.h"


void cPlayer::Setting()
{
	selectColor = Red;
	pSprite = new cSprite;
	pSprite->Entry("res/Player.png", "player");
	memset(KeyBuffer, false, sizeof(KeyBuffer));
	pSprite->getSize("player", width, height);
	key = { 0,0,0,0,0 };
}
cPlayer::cPlayer()
{
	Setting();
}
cPlayer::cPlayer(int x,int y) : x(x),y(y)
{
	Setting();
}
cPlayer::~cPlayer()
{
	SAFE_DELETE(pSprite);
}
void cPlayer::Render(HDC hdc)
{
	pSprite->Render(hdc, "player", x, y, width / 3, height, 0 + (width / 3 )* selectColor, 0, width / 3, height);
}
void cPlayer::KeyBoard(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_KEYDOWN) 
	{
		KeyBuffer[wParam] = true;
		if (wParam == VK_UP)
			key.up = true;
		else if (wParam == VK_DOWN)
			key.down = true;
		else if (wParam == VK_LEFT)
			key.left = true;
		else if (wParam == VK_RIGHT)
			key.right = true;
	}
	if (message == WM_KEYUP)
	{
		KeyBuffer[wParam] = false;
		if (wParam == VK_UP)
			key.up = false;
		else if (wParam == VK_DOWN)
			key.down = false;
		else if (wParam == VK_LEFT)
			key.left = false;
		else if (wParam == VK_RIGHT)
			key.right = false;
	}
	if (message == WM_KEYDOWN)
	{
		switch (wParam)
		{
		case 'Q':
			key.color = Red;
			break;
		case 'W':
			key.color = Blue;
			break;
		case 'E':
			key.color = Green;
			break;
		default:
			break;
		}
	}
}
