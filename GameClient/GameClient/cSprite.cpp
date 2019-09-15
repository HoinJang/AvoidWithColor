#include "cSprite.h"
#include "cMain.h"

cSprite::cSprite()
{
	sprites.clear();
}
cSprite::~cSprite()
{
	for (auto p = sprites.begin(); p != sprites.end(); ++p)
	{
		p->second->Destroy();
		SAFE_DELETE(p->second);
	}
}
void cSprite::Entry(string path, string name)
{
	CImage* temp = new CImage();
	temp->Load(path.c_str());
	sprites.insert(make_pair(name, temp));
}
void cSprite::Render(HDC hdc, const string& name, const int x, const int y)
{
	CImage* temp = getImage(name);
	//temp->Draw(hdc, 0, 0, 221, 221,0,0,221,221);

	temp->Draw(hdc, x, y );
}
void cSprite::Render(HDC hdc, const string& name, const int x, const int y, const int w, const int h)
{
	CImage* temp = getImage(name);
	temp->Draw(hdc, x, y,w,h);
}
void cSprite::Render(HDC hdc, const string& name, const int x, const int y, const int w, const int h, const int xSrc, const int ySrc, const int xSrcW, const int xSrcH)
{
	CImage* temp = getImage(name);
	temp->Draw(hdc, x, y, w, h, xSrc,ySrc, xSrcW, xSrcH);
}