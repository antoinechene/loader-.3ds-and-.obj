#include "normal.h"

Normal::Normal()
{
}

Normal::~Normal()
{

}

float	Normal::Get_N1()
{
	return (this->n1);
}

float	Normal::Get_N2()
{
	return (this->n2);
}
float	Normal::Get_N3()
{
	return (this->n3);
}

void	Normal::Set_N1(float n1)
{
	this->n1 = n1;
}

void	Normal::Set_N2(float n2)
{
	this->n2 = n2;
}

void	Normal::Set_N3(float n3)
{
	this->n3 = n3;
}

