#include "texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

float	Texture::Get_U()
{
	return (this->u);
}

float	Texture::Get_V()
{
	return (this->v);
}

void	Texture::Set_U(float u)
{
	this->u = u;
}

void	Texture::Set_V(float v)
{
	this->v = v;
}
