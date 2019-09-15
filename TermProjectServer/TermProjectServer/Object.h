#pragma once

class Object
{
private:
	short x;
	short y;
	short color;
	short type;
	short speed;
public:
	Object(short x, short y, short color, short type) : x(x), y(y), color(color), type(type)
	{
		speed = ObjectSpeed;
	}
	~Object() {}
public:
	void Updata()
	{
		if (type == 0)
		{
			y += speed;
		}
		else
		{
			x += speed;
		}
	}
	short getX() { return x; }
	short getY() { return y; }
	short getColor() { return color; }
	short getType() { return type; }
};