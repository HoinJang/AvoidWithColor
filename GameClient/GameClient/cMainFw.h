#pragma once
#include "cMyInclude.h"
#include "cSceneManager.h"
// 윈도우 만들어주고 덤으로 윈도우 정보도 저장


class cMainFw : public cSceneManager
{
private:
	int x;
	int y;
	char name[256];
	HWND hWnd;
	HINSTANCE hInst;
public:
	cMainFw(const char* name, int x, int y) : x(x) , y(y)
	{
		strcpy(this->name, name);
	}
public:
	virtual ~cMainFw()
	{

	}
public:
	void CreateWindowns(HINSTANCE hInstance, HINSTANCE hPrevInstance
		, LPSTR lpszCmdParam, int nCmdShow);

	int StartLoop();
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#pragma region get
public:
	int getX() const
	{
		return x;
	}
	int getY() const
	{
		return y;
	}
	char* getName() 
	{
		return name;
	}
	HWND getHwnd() const
	{
		return hWnd;
	}
	HINSTANCE gethinstance() const
	{
		return hInst;
	}
#pragma endregion
};