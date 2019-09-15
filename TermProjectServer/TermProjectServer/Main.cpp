#include "MyDefine.h"
#include "MyInclude.h"
#include "Object.h"
#include <crtdbg.h>

//
//#ifndef _DEBUG
//#define new new(_CLIENT_BLOCK,__FILE__,__LINE)
//#endif

vector<Object*> v;
vector<Object*> h;

KeyBoard_Data KeyPacket;
Game_Data GamePacket;
short playerID;  // 클라이언트가 접속했을때 보내주는 ID번호
short ConnectClientNum;// 현재 클라이언트 접속 갯수
Object_Data Pattern[10][30];
bool ClearOn;

WSADATA wsa;
int retval;
SOCKET listen_sock;
SOCKADDR_IN serveraddr;

void InitObjectData();
void SelectPatternV();
void SelectPatternH();
void Calculation();

Player_Info& CollisionCheck(Player_Info *p);
Player_Info& PlayerMove(Player_Info *p, KeyBoard_Data* Key);
bool Collision_AABB(int x1, int y1, int x2, int y2, int size1, int size2);

void err_display(char *msg);
void err_quit(char *msg);
int recvn(SOCKET s, char *buf, int len, int flags);

//멀티스레드 변수
HANDLE ClientThread[PlayerMaxNum];
HANDLE WorkerThread;
//이벤트 변수
HANDLE hReadEvent;
HANDLE hWriteEvent;

DWORD WINAPI WorkerProcess(LPVOID arg)
{
	cout << "연산 스레드 시작 : " << GetCurrentThreadId() << endl;
	v.clear();
	h.clear();
	SelectPatternV();
	SelectPatternH();
	GamePacket.pData1 = { 300, 700, Red , 5 };
	GamePacket.pData2 = { 600, 700, Red , 5 };
	ClearOn = false;
	while (1)
	{
		retval = WaitForSingleObject(hWriteEvent, INFINITE);

		Calculation();
		
		SetEvent(hReadEvent);

		if (ConnectClientNum == 0)
			break;
	}
	cout << "연산 스레드 종료 : " << GetCurrentThreadId() << endl;

	return 0;
}
DWORD WINAPI ClientProcess(LPVOID arg)
{
	cout << "클라이언트 스레드 생성 : " << GetCurrentThreadId() << endl;

	SOCKET client_sock = (SOCKET)arg;
	int retval;
	SOCKADDR_IN clientaddr;
	int addrlen;


	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);


	if (ConnectClientNum >= PlayerMaxNum)
	{
		GamePacket.id = PlayerFull;

		retval = send(client_sock, (char*)&GamePacket, sizeof(Game_Data), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
		}

		closesocket(client_sock);
		printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		cout << playerID << ConnectClientNum << endl;
		cout << "클라이언트 스레드 종료 : " << GetCurrentThreadId() << endl;

		return 0;
	}
	else
	{
		GamePacket.id = playerID;
		GamePacket.oDataSize = (short)v.size();
		GamePacket.hDataSize = (short)h.size();
		ResetEvent(hWriteEvent);
		ResetEvent(hReadEvent);

		//플레이어 아이디와 오브젝트 데이터 전송
		retval = send(client_sock, (char*)&GamePacket, sizeof(Game_Data), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
		}

		playerID++;
		ConnectClientNum++;

		if (ConnectClientNum == PlayerMaxNum)
		{
			WorkerThread = CreateThread(NULL, 0, WorkerProcess, NULL, 0, NULL);
			SetEvent(hWriteEvent);
		}
	}
	

	auto nowTime = system_clock::now();
	int FPS = 30;
	long long FPSTIME = ((float)(1000.0 / (float)FPS));
	while (1)
	{
		auto time = duration_cast<milliseconds>(system_clock::now() - nowTime).count();
		if (time >= FPSTIME)
		{
			retval = WaitForSingleObject(hReadEvent, INFINITE);

			retval = recvn(client_sock, (char*)&KeyPacket, sizeof(KeyBoard_Data), 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv()");
			}
			retval = send(client_sock, (char*)&GamePacket, sizeof(Game_Data), 0);
			if (retval == SOCKET_ERROR) {
				err_display("send()");
			}

			nowTime = system_clock::now();

			SetEvent(hWriteEvent);

			// 한 명이 죽으면 클라이언트 스레드 & 연산스레드 모두 종료
			if (GamePacket.pData1.hp < 0 || GamePacket.pData2.hp < 0)
			{
				ConnectClientNum--;
				if (ConnectClientNum == 0)
				{
					playerID = 0;
				}
				break;
			}
		}
	}
	closesocket(client_sock);
	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
	cout << "클라이언트 스레드 종료 : " << GetCurrentThreadId() << endl;

	return 0;
}

int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	InitObjectData();
	v.clear();
	h.clear();
	playerID = 0;
	ConnectClientNum = 0;

	// 윈속 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 0;

	// socket()
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	//통신
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;

	hWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hWriteEvent == NULL) return 1;
	hReadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hReadEvent == NULL) return 1;

	while (1)
	{
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
		}
		// 접속한 클라이언트 정보 출력
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		ClientThread[playerID] = CreateThread(NULL, 0, ClientProcess, (LPVOID)client_sock, 0, NULL);
		
		if (ClientThread[playerID] == NULL)
		{
			closesocket(client_sock);
		}
		else
		{
			CloseHandle(ClientThread[playerID]);
		}
	}

	WaitForMultipleObjects(2, ClientThread, TRUE, INFINITE);
	cout << "클라 종료" << endl;
	WaitForSingleObject(WorkerThread, INFINITE);

	CloseHandle(hWriteEvent);
	CloseHandle(hReadEvent);

	// closesocket()
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();
	for (int i = 0; i < v.size(); ++i)
		SAFE_DELETE(v[i]);

	return 0;
}

void InitObjectData()
{
	ifstream ReadFile;

	char* a = "res/Pattern";
	char* b = ".txt";
	for (int j = 0; j < ObjectReSelectSize; j++)
	{
		char* FileName = new char[20];
		sprintf(FileName, "%s%d%s", a, j, b);

		ReadFile.open(FileName);

		for (int i = 0; i < ObjectInitSize; i++)
		{
			ReadFile >> Pattern[j][i].x >> Pattern[j][i].y >> Pattern[j][i].color;
		}
		ReadFile.close();
		SAFE_DELETE(FileName);
	}
}
void SelectPatternV()
{
	int randomNum = rand() % ObjectReSelectSize;
	for (int i = 0; i< ObjectInitSize; i++)
	{
		v.emplace_back(new Object(Pattern[randomNum][i].x, Pattern[randomNum][i].y, Pattern[randomNum][i].color, 0));
	}
}
void SelectPatternH() 
{
	int randomNum = rand() % ObjectReSelectSize;

	for (int j = 0; j < ObjectInitSize; j++)
	{
		h.emplace_back(new Object(Pattern[randomNum][j].y - 500, Pattern[randomNum][j].x, Pattern[randomNum][j].color, 1));
	}
}
void Calculation()
{
	if (KeyPacket.id == Player1)
	{
		GamePacket.pData1 = PlayerMove(&GamePacket.pData1, &KeyPacket);
	}
	else if (KeyPacket.id == Player2)
	{
		GamePacket.pData2 = PlayerMove(&GamePacket.pData2, &KeyPacket);
	}
	if (v.size() < ObjectReSelectSize)
	{
		SelectPatternV();
	}
	if (h.size() < ObjectReSelectSize)
	{
		SelectPatternH();
	}
	for (int i = 0; i < v.size(); i++)
	{
		v[i]->Updata();
	}
	for (int j = 0; j < h.size(); j++)
	{
		h[j]->Updata();
	}
	CollisionCheck(&GamePacket.pData1);
	CollisionCheck(&GamePacket.pData2);

	for (int i = 0; i < v.size(); i++)
	{
		GamePacket.oData[i] = { v[i]->getX(), v[i]->getY(), v[i]->getColor() , v[i]->getType() };
	}
	for (int j = 0; j < h.size(); j++)
	{
		GamePacket.hData[j] = {h[j]->getX(), h[j]->getY(), h[j]->getColor() , h[j]->getType() };
	}
	GamePacket.oDataSize = (short)v.size();
	GamePacket.hDataSize = (short)h.size();
}
void err_display(char *msg)
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
void err_quit(char *msg)
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
int recvn(SOCKET s, char * buf, int len, int flags)
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
Player_Info& PlayerMove(Player_Info *p, KeyBoard_Data* Key)
{
	p->color = Key->color;
	if (Key->right)
	{
		p->x += PlayerSpeed;
		p->x = min(p->x, WindowWidth - 50);
	}
	if (Key->left)
	{
		p->x -= PlayerSpeed;
		p->x = max(p->x, 0);
	}
	if (Key->up)
	{
		p->y -= PlayerSpeed;
		p->y = max(p->y, 0);
	}
	if (Key->down)
	{
		p->y += PlayerSpeed;
		p->y = min(p->y, WindowHeight - 50);
	}
	return *p;
}
bool Collision_AABB(int x1, int y1, int x2, int y2, int size1, int size2)
{
	if (x1 - size1 / 2 > x2 + size2 / 2)
		return false;
	if (x1 + size1 / 2 < x2 - size2 / 2)
		return false;
	if (y1 + size1 / 2 < y2 - size2 / 2)
		return false;
	if (y1 - size1 / 2 > y2 + size2 / 2)
		return false;
	return true;
}
Player_Info& CollisionCheck(Player_Info *p)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (Collision_AABB(v[i]->getX(), v[i]->getY(), p->x, p->y, ObjectSize, PlayerSize))
		{
			if (v[i]->getColor() == HpItem)
			{
				p->hp += 1;
				p->hp = min(p->hp, PlayerMaxHp);
				SAFE_DELETE(v[i]);
				v.erase(v.begin() + i);
				break;
			}
			else if (v[i]->getColor() == ClearItem)
			{
				ClearOn = true;
				break;
			}
			else
			{
				if (p->color != v[i]->getColor())
				{
					p->hp -= 1;
				}
				else
					;

				SAFE_DELETE(v[i]);
				v.erase(v.begin() + i);
				break;
			}
		}
	}

	for (int i = 0; i < h.size(); i++)
	{
		if (Collision_AABB(h[i]->getX(), h[i]->getY(), p->x, p->y, ObjectSize, PlayerSize))
		{
			if (h[i]->getColor() == HpItem)
			{
				p->hp += 1;
				p->hp = min(p->hp, PlayerMaxHp);
				SAFE_DELETE(h[i]);
				h.erase(h.begin() + i);
				break;
			}
			else if (h[i]->getColor() == ClearItem)
			{
				ClearOn = true;
				break;
			}
			else
			{
				if (p->color != h[i]->getColor())
				{
					p->hp -= 1;
				}
				else
					;

				SAFE_DELETE(h[i]);
				h.erase(h.begin() + i);
				break;
			}
		}
	}
	//클리어 아이템 효과
	if (ClearOn)
	{
		for (int i = 0; i < v.size(); i++)
		{
			if (v[i]->getY() > 0)
			{
				SAFE_DELETE(v[i]);
				v.erase(v.begin() + i);
				i--;
			}
		}
		for (int j = 0; j < h.size(); j++)
		{
			if (h[j]->getX() > 0)
			{
				SAFE_DELETE(h[j]);
				h.erase(h.begin() +j);
				j--;
			}
		}
		ClearOn = false;
	}
	// 화면 밖 제거
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i]->getY() > WindowHeight)
		{
			SAFE_DELETE(v[i]);
			v.erase(v.begin() + i);
			i--;
		}
	}
	for (int j = 0; j < h.size(); j++)
	{
		if (h[j]->getX() > WindowWidth)
		{
			SAFE_DELETE(h[j]);
			h.erase(h.begin() + j);
			j--;
		}
	}
	return *p;
}