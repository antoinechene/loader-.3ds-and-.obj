#include "vertex.h"

Vertex::Vertex()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}


Vertex::~Vertex()
{

}

float	Vertex::Get_X()
{
	return (this->x);
}

float	Vertex::Get_Y()
{
	return (this->y);
}

float	Vertex::Get_Z()
{
	return (this->z);
}

void	Vertex::Set_X(float x)
{
	this->x = x;
}

void	Vertex::Set_Y(float y)
{
	this->y = y;
}

void	Vertex::Set_Z(float z)
{
	this->z = z;
}

