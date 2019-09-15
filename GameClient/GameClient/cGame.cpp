#include "cGame.h"
#include "cMain.h"
#include "cMyInclude.h"
#include "cMyDefine.h"


cGame::cGame()
{
	m_Animation = NULL;
	mBackGround = NULL;
	pPlayer1 = NULL;
	pPlayer2 = NULL;
	mHpMark = NULL;
	SERVERIP = NULL;
	mObject.clear();
	hObject.clear();
	playerID = 0;
}
cGame::~cGame()
{
	SAFE_DELETE(m_Animation);
	SAFE_DELETE(mBackGround);
	SAFE_DELETE(pPlayer1);
	SAFE_DELETE(pPlayer2);
	SAFE_DELETE(mHpMark);
	SAFE_DELETE(SERVERIP);
	for (int i = 0; i < mObject.size(); ++i)
		SAFE_DELETE(mObject[i]);
	for (int i = 0; i < hObject.size(); ++i)
		SAFE_DELETE(hObject[i]);
}
void cGame::Init()
{
	if (SERVERIP == NULL)
	{
		SERVERIP = new char[20];
	}
	InitServer();
	GamePacket.pData1= { 0, 0, 0, 0 };
	GamePacket.pData2= { 0, 0, 0, 0 };
	GamePacket.oDataSize = 0;
	GamePacket.hDataSize = 0;
	if (mBackGround == NULL)
	{
		mBackGround = new cBackGround();
	}
	if (mHpMark == NULL)
	{
		mHpMark = new cHpMark;
	}
	if (pPlayer1 == NULL)
	{
		pPlayer1 = new cPlayer(0,0);
	}
	if (pPlayer2 == NULL)
	{
		pPlayer2 = new cPlayer(0, 0);
	}
	if (m_Animation == NULL)
	{
		m_Animation = new cAnimation;
	}
	m_Animation->Entry("res/BlueObject.png", "Blue", 3, 1, 200);
	m_Animation->Entry("res/cClearObject.png", "Clear", 1, 1, 200);
	m_Animation->Entry("res/cHpObject.png", "Hp", 1, 1, 200);
	m_Animation->Entry("res/RedObject.png", "Red", 3, 1, 200);
	m_Animation->Entry("res/GreenObject.png", "Green", 3, 1, 200);
}
void cGame::Destroy()
{
	ReleaseServer();
	SAFE_DELETE(m_Animation);
	SAFE_DELETE(mBackGround);
	SAFE_DELETE(pPlayer1);
	SAFE_DELETE(pPlayer2);
	SAFE_DELETE(mHpMark);
	SAFE_DELETE(SERVERIP);
	for (int i = 0; i < mObject.size(); ++i)
		SAFE_DELETE(mObject[i]);
	for (int i = 0; i < hObject.size(); ++i)
		SAFE_DELETE(hObject[i]);
}
void cGame::Update()
{
	if (playerID == Player1)
	{
		KeyPacket = pPlayer1->getKeyData();
		KeyPacket.id = playerID;
	}
	if (playerID == Player2)
	{
		KeyPacket = pPlayer2->getKeyData();
		KeyPacket.id = playerID;
	}
	SendForServer();
	RecvFromServer();

	GameEndCheck();
}
void cGame::Render(HDC hdc)
{
	mBackGround->Render(hdc);
	pPlayer1->Render(hdc);
	pPlayer2->Render(hdc);
	for (int i = 0; i < GamePacket.oDataSize; ++i)
	{	
		if (mObject[i]->getType() == Red)
			m_Animation->Render(hdc, "Red", mObject[i]->getX(), mObject[i]->getY());
		else if (mObject[i]->getType() == Blue)
			m_Animation->Render(hdc, "Blue", mObject[i]->getX(), mObject[i]->getY());
		else if (mObject[i]->getType() == Green)
			m_Animation->Render(hdc, "Green", mObject[i]->getX(), mObject[i]->getY());
		else if (mObject[i]->getType() == HpItem)
			m_Animation->Render(hdc, "Hp", mObject[i]->getX(), mObject[i]->getY());
		else if (mObject[i]->getType() == ClearItem)
			m_Animation->Render(hdc, "Clear", mObject[i]->getX(), mObject[i]->getY());
	}
	for (int i = 0; i < GamePacket.hDataSize; ++i)
	{
		if (hObject[i]->getType() == Red)
			m_Animation->Render(hdc, "Red", hObject[i]->getX(), hObject[i]->getY());
		else if (hObject[i]->getType() == Blue)
			m_Animation->Render(hdc, "Blue", hObject[i]->getX(), hObject[i]->getY());
		else if (hObject[i]->getType() == Green)
			m_Animation->Render(hdc, "Green", hObject[i]->getX(), hObject[i]->getY());
		else if (hObject[i]->getType() == HpItem)
			m_Animation->Render(hdc, "Hp", hObject[i]->getX(), hObject[i]->getY());
		else if (hObject[i]->getType() == ClearItem)
			m_Animation->Render(hdc, "Clear", hObject[i]->getX(), hObject[i]->getY());
	}
	mHpMark->Render(hdc);
}
void cGame::KeyBoard(UINT message, WPARAM wParam, LPARAM lParam)
{
	pPlayer1->KeyBoard(message, wParam, lParam);
	pPlayer2->KeyBoard(message, wParam, lParam);
}
void cGame::Mouse(UINT _type, int _x, int _y, int _w)
{
}
void cGame::SetGameData()
{
	for (int i = 0; i < GamePacket.oDataSize; i++)
	{
		AddObject(GamePacket.oData[i].x, GamePacket.oData[i].y, 0, (Type)GamePacket.oData[i].color);
	}
	for (int j = 0; j < GamePacket.hDataSize; j++)
	{
		AddObject(GamePacket.hData[j].x, GamePacket.hData[j].y, 1, (Type)GamePacket.hData[j].color);
	}
	pPlayer1->setColor(GamePacket.pData1.color);
	pPlayer1->setX(GamePacket.pData1.x);
	pPlayer1->setY(GamePacket.pData1.y);
	pPlayer1->setHp(GamePacket.pData1.hp);

	pPlayer2->setColor(GamePacket.pData2.color);
	pPlayer2->setX(GamePacket.pData2.x);
	pPlayer2->setY(GamePacket.pData2.y);
	pPlayer2->setHp(GamePacket.pData2.hp);

	if (playerID == Player1)
	{
		mHpMark->setHp(GamePacket.pData1.hp);
	}
	else if (playerID == Player2)
	{
		mHpMark->setHp(GamePacket.pData2.hp);
	}
}
void cGame::AddObject(int x, int y, int t, Type type)
{
	if (t == 0)
	{
		mObject.emplace_back(new cObject(x, y, t, type));
	}
	else if(t == 1)
	{
		hObject.emplace_back(new cObject(x, y, t, type));
	}
}
void cGame::ClearVector()
{
	for (int i = 0; i < mObject.size(); i++)
	{
		SAFE_DELETE(mObject[i]);
	}
	mObject.clear();

	for (int i = 0; i < hObject.size(); i++)
	{
		SAFE_DELETE(hObject[i]);
	}
	hObject.clear();
}
void cGame::GameEndCheck()
{
	if (GamePacket.pData1.hp < 0 && playerID == Player1)
	{
		cMain::getinstance().Trans(Lose);
	}
	if (GamePacket.pData1.hp < 0 && playerID == Player2)
	{
		cMain::getinstance().Trans(Win);
	}
	if (GamePacket.pData2.hp < 0 && playerID == Player2)
	{
		cMain::getinstance().Trans(Lose);
	}
	if (GamePacket.pData2.hp < 0 && playerID == Player1)
	{
		cMain::getinstance().Trans(Win);
	}
}
void cGame::SendForServer()
{
	retval = send(sock, (char*)&KeyPacket, sizeof(KeyBoard_Data), 0);

	if (retval == SOCKET_ERROR)
	{
		err_display("send()");
	}
}
void cGame::RecvFromServer()
{
	retval = recvn(sock, (char*)&GamePacket, sizeof(Game_Data), 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("recv()");
	}
	ClearVector();
	SetGameData();
}
void cGame::InitServer()
{
	
	cout << "서버 IP주소를 입력해주세요 : ";
	cin >> SERVERIP;
	cout << SERVERIP << endl;
	

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return;

	// socket()
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");
	 
	// connect()
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	//serveraddr.sin_addr.s_addr = inet_addr("192.168.142.184");
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	retval = recvn(sock, (char*)&GamePacket, sizeof(Game_Data), 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("recv()");
	}

	playerID = GamePacket.id;

	if(playerID == PlayerFull)
	{
		cMain::getinstance().Trans(End);
	}
	cout << "플레이어 ID : "<< playerID << endl;
}
void cGame::ReleaseServer()
{ 
	// closesocket()
	closesocket(sock);

	// 윈속 종료
	WSACleanup();
}
void cGame::err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCTSTR)msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}
int cGame::recvn(SOCKET s, char * buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;
	while (left > 0) 
	{
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}
	return (len - left);
}
void cGame::err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}