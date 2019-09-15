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
	void Entry(string path, string name, int xCount, int yCount,long long NextTimer); // ���,�̸�,x����,y���� ,�Ѱ��ѱ�½ð�

	void Render(HDC hdc, const string& name, const int x, const int y);
private:
	AnimationData* getImage(const string& name)
	{
		return animations.find(name)->second;
	}

	void Next(AnimationData* temp, long long time);
};