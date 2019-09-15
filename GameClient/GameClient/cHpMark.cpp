#include "cHpMark.h"

cHpMark::cHpMark()
{
	hp = 3;
	pSprite = new cSprite;
	pSprite->Entry("res/HpMark.png", "HpMark");
}

cHpMark::~cHpMark()
{
	SAFE_DELETE(pSprite);
}

void cHpMark::Update()
{
}

void cHpMark::Render(HDC hdc)
{
	for (int i = 0; i < hp ;i++)
	{
		pSprite->Render(hdc, "HpMark", 60 * i+20, 20);
	}
}