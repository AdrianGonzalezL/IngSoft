#pragma once
#pragma warning(disable:4820)
#pragma warning(disable:4365)
#pragma warning(disable:4571)
#pragma warning(disable:4625)
#pragma warning(disable:4626)
#pragma warning(disable:4514)
#pragma warning(disable:4710)
#pragma warning(disable:5026)
#pragma warning(disable:5027)
#pragma warning(disable:4774)

struct Object
{
	enum dir
	{
		LEFT,
		RIGHT,
		NONE
	};

	enum type 
	{
		ENEMY,
		BULLET,
		PLAYER,
		MUSHROOM,
		DROP,
		NONETYPE
	};

	type m_type;

	Object();
	virtual void printObject() = 0;
};