#pragma once

#include "cMyInclude.h"
#include "cMyDefine.h"
#include "cScene.h"
#include "cSprite.h"
#include "cAnimation.h"
#include "cPlayer.h"
#include "cObject.h"

#include "cBackGround.h"
#include "cHpMark.h"

#include "cRedObject.h"
#include "cGreenObject.h"
#include "cBlueObject.h"
#include "cHpObject.h"
#include "cClearObject.h"


class cGame : public cScene
{
private:
	WSADATA wsa;
	int retval;
	SOCKET sock;
	SOCKADDR_IN serveraddr;
private:
	KeyBoard_Data KeyPacket;
	Game_Data GamePacket;
private:
	cPlayer*			pPlayer1;
	cPlayer*			pPlayer2;
	vector<cObject*>	mObject;
	vector<cObject*>	hObject;
	cBackGround*		mBackGround;
	cHpMark*			mHpMark;
	cAnimation*			m_Animation;
private:
	short playerID;
	char* SERVERIP;
public:
	cGame();
	~cGame();
public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void KeyBoard(UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Mouse(UINT _type, int _x, int _y, int _w) override;
public:
	void SetGameData();
	void AddObject(int x, int y, int t, Type type);
	void ClearVector();
	void GameEndCheck();
public:
	void SendForServer();
	void RecvFromServer();
	void InitServer();
	void ReleaseServer();
	void err_display(char *msg);
	void err_quit(char *msg);
	int recvn(SOCKET s, char *buf, int len, int flags);
};