#include "cBackGround.h"

cBackGround::cBackGround()
{
	pSprite = new cSprite;
	pSprite->Entry("res/BackGround.png", "BackGround");
	width = 1000;
	height = 800;
}

cBackGround::~cBackGround()
{
	SAFE_DELETE(pSprite);
}

void cBackGround::Update()
{
}

void cBackGround::Render(HDC hdc)
{
	pSprite->Render(hdc, "BackGround", 0, 0);
}