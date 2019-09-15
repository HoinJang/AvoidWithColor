#include "cAnimation.h"
#include "cMain.h"

cAnimation::cAnimation()
{
	animations.clear();
}
cAnimation::~cAnimation()
{
	for (auto p = animations.begin(); p != animations.end(); ++p)
	{
		p->second->image->Destroy();
		SAFE_DELETE(p->second->image);
		SAFE_DELETE(p->second);
	}
	animations.clear();
}
void cAnimation::Entry(string path, string name, int xCount, int yCount, long long NextTimer)
{
	AnimationData* TempData = new AnimationData;
	CImage* temp = new CImage();
	temp->Load(path.c_str());
	TempData->NowTimer = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	TempData->xCount = xCount;
	TempData->yCount = yCount;

	TempData->image = temp;
	TempData->xFrameCount = 0;
	TempData->yFrameCount = 0;
	TempData->xSize = temp->GetWidth() / xCount;
	TempData->ySize = temp->GetHeight() / yCount;
	TempData->NextTimer = NextTimer;
	animations.insert(make_pair(name, TempData));
}

void cAnimation::Render(HDC hdc, const string& name, const int x, const int y)
{
	AnimationData* TempData = getImage(name);
	int StartX =  (TempData->xFrameCount * TempData->xSize);
	int StartY =  (TempData->yFrameCount * TempData->ySize);
	TempData->image->Draw(hdc, x, y,TempData->xSize, TempData->ySize,
		StartX , StartY , TempData->xSize, TempData->ySize);


	Next(TempData, duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
}
void cAnimation::Next(AnimationData* temp,long long time)
{
	if (time - temp->NowTimer >= temp->NextTimer)
	{
		temp->xFrameCount++;
		if (temp->xFrameCount >= temp->xCount)
		{
			temp->xFrameCount = 0;
			temp->yFrameCount++;
		}
		if (temp->yFrameCount >= temp->yCount)
		{
			temp->yFrameCount = 0;
			temp->xFrameCount = 0;
		}
		temp->NowTimer = time;
	}
}