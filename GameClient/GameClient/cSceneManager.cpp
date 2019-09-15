#include "cSceneManager.h"

cSceneManager::cSceneManager()
{
	pNowScene = NULL;
	Scenes.clear();
}
cSceneManager::~cSceneManager()
{
	for (int i = 0; i < Scenes.size(); ++i)
		SAFE_DELETE(Scenes[i]);
}
void cSceneManager::Entry(int num, cScene* scene)
{
	Scenes.push_back(scene);
}
void cSceneManager::Trans(int num)
{
	if (pNowScene != NULL)
		pNowScene->Destroy();
	pNowScene = Scenes[num];
	pNowScene->Init();
}