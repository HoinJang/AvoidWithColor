#pragma once
#include "cMyDefine.h"
#include "cMyInclude.h"
#include <map>

class cSprite
{
private:
	map<string, CImage*> sprites;
public:
	cSprite();
	~cSprite();
public:
	void Entry(string path, string name);
	void Render(HDC hdc,const string& name, const int x, const int y);
	void Render(HDC hdc, const string& name, const int x, const int y,const int w, const int h);
	void Render(HDC hdc, const string& name, const int x, const int y, const int w, const int h, const int xSrc, const int ySrc, const int xSrcW, const int xSrcH);

public:
	void getSize(string name, int& w, int& h)
	{
		CImage* temp = getImage(name);
		w = temp->GetWidth();
		h = temp->GetHeight();
	}
private:

	CImage* getImage(const string& name)
	{
		return sprites.find(name)->second;
	}
};