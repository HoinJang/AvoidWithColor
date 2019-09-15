#pragma once
#include "cScene.h"
#include "cMyInclude.h"
#include <vector>
class cSceneManager
{
private:
	cScene* pNowScene;
	vector<cScene*> Scenes;
protected:
	cSceneManager();
public:
	virtual ~cSceneManager();
public:
	void Entry(int num, cScene* scene);
	void Trans(int num);
#pragma region set,get
public:
	cScene* getNowScene()
	{
		return pNowScene;
	}
#pragma endregion

};