#pragma once

#define WindowWidth 1000
#define WindowHeight 800

#define PlayerSize 50
#define ObjectSize 25

#define PlayerFull -100
#define Player1 0
#define Player2 1

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{if(p) {delete (p);     (p)=NULL;}}
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)			{if(p) {delete[] (p);     (p)=NULL;}}
#endif


enum SceneType
{
	Menu = 0,
	Game ,
	Win,
	Lose,
	End,
};

enum Type
{
	Red = 0,
	Blue,
	Green,
	HpItem,
	ClearItem,
};
#pragma pack(push, 1)
struct Object_Data
{
	short x;
	short y;
	short color;
	short type;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Player_Info
{
	short x;
	short y;
	short color;
	short hp;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct KeyBoard_Data
{
	bool up;
	bool down;
	bool left;
	bool right;
	short color;
	short id; // 클라이언트 -> 서버 전송시 구분하기 위한 ID
};
#pragma pack(pop)

#pragma pack(push,1)
struct Game_Data
{
	short id;					//서버 -> 클라에게 처음 보내주는 ID
	short oDataSize;
	short hDataSize;
	Object_Data oData[40];
	Object_Data hData[40];
	Player_Info pData1;
	Player_Info pData2;
};
#pragma pack(pop)
