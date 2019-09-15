#pragma once

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{if(p) {delete (p);     (p)=nullptr;}}
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)			{if(p) {delete[] (p);     (p)=nullptr;}}
#endif

#define SERVERPORT 9000
#define WindowWidth 1000
#define WindowHeight 800

#define PlayerSize 40
#define ObjectSize 20

#define ObjectPacketSize 40
#define ObjectInitSize 30
#define ObjectReSelectSize 10


#define PlayerFull -100
#define PlayerMaxNum 2
#define Player1 0
#define Player2 1
#define PlayerMaxHp 5
#define PlayerSpeed 10
#define ObjectSpeed 8


enum Type
{
	Red = 0,
	Blue,
	Green,
	HpItem, 
	ClearItem
};

#pragma pack(push,1)
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
	short id;
};
#pragma pack(pop)

#pragma pack(push,1)
struct Game_Data
{
	short id;
	short oDataSize;
	short hDataSize;
	Object_Data oData[ObjectPacketSize];
	Object_Data hData[ObjectPacketSize];
	Player_Info pData1;
	Player_Info pData2;
};
#pragma pack(pop)



