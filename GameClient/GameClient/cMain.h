#pragma once
#include "cMyInclude.h"
#include "cMyDefine.h"
#include "cMainFw.h"
#include "cMenu.h"
#include "cGame.h"
#include "cWin.h"
#include "cLose.h"
#include "cEnd.h"

class cMain : public cSingleton<cMain>, public cMainFw
{
public:
	cMain();
	~cMain();
public:
	void Init();
};