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

// Clase objeto de la que heredan los elementos a mostrar por pantalla.
// Solo contiene una variable type, para diferenciarlos unos de otros
// y el metodo printObject, que lo tienen que implementar todos, para poder ser pintados.
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