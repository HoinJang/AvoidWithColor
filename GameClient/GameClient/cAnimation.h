#pragma once
#include "cMyDefine.h"
#include "cMyInclude.h"
#include <map>
 struct AnimationData
{
	int xCount;
	int yCount;
	int xSize;
	int ySize;
	CImage* image;

	int xFrameCount;
	int yFrameCount;

	long long NextTimer; 
	long long NowTimer;

};

class cAnimation
{
private:
	map<string, AnimationData*> animations;
public:
	cAnimation();
	~cAnimation();
public:
	void Entry(string path, string name, int xCount, int yCount,long long NextTimer); // 경로,이름,x갯수,y갯수 ,한개넘기는시간

	void Render(HDC hdc, const string& name, const int x, const int y);
private:
	AnimationData* getImage(const string& name)
	{
		return animations.find(name)->second;
	}

	void Next(AnimationData* temp, long long time);
};