#pragma once
template <class T>
class cSingleton
{
protected:
	cSingleton()
	{

	}
	virtual ~cSingleton()
	{

	}
public:
	static T& getinstance()
	{
		static T Instance;
		return Instance;
	}

private:
};
