#include "cMain.h"
cMain::cMain() : cMainFw("My Game", 1000, 800)
{

}
cMain::~cMain()
{

}
void cMain::Init()
{
	Entry(Menu, new cMenu);
	Entry(Game, new cGame);
	Entry(Win, new cWin);
	Entry(Lose, new cLose);
	Entry(End, new cEnd);
	Trans(0);
}