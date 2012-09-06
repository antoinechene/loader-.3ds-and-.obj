#include "face.h"

Face::Face()
{
}

Face::~Face()
{
}

void	Face::Add_Index(Vertex* v)
{
	this->index.push_back(v);
}

std::vector<Vertex*>*	Face::Get_List()
{
	return (&this->index);
}

void	Face::Add_Texture(Texture* u)
{
	this->Tex.push_back(u);
}

std::vector<Texture*>*	Face::Get_List_Texture()
{
	return (&this->Tex);
}
void	Face::Add_Normal(Normal* n)
{
	this->norm.push_back(n);
}

std::vector<Normal*>*	Face::Get_List_Normal()
{
	return (&this->norm);
}

void	Face::Set_Id_Tex(char* str)
{
	this->id_tex = str;
}

