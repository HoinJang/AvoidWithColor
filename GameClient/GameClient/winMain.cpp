#include "cMyInclude.h"
#include <crtdbg.h>
#include "cMain.h"
#ifndef _DEBUG

#define new new(_CLIENT_BLOCK,__FILE__,__LINE)

#endif

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	cMain::getinstance().CreateWindowns(hInstance, hPrevInstance, lpszCmdParam, nCmdShow);
	cMain::getinstance().Init();
	cMain::getinstance().StartLoop();
	return 0;
}
