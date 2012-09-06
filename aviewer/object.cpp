#include "object.h"
#include <GL/glut.h>
#include "Display.h"

Object::Object()
{
}

Object::~Object()
{
	size_t	i;
	size_t	size;

	i = 0;
	size = this->F.size();
	while (i < size)
	{
		delete this->F[i];
		i ++;
	}
	i = 0;
	size = this->V.size();
	while(i < size)
	{
		delete this->V[i];
		i ++;
	}
	i = 0;
	size = this->T.size();
	while(i < size)
	{
		delete this->T[i];
		i ++;
	}
	i = 0;
	size = this->N.size();
	while(i < size)
	{
		delete this->N[i];
		i ++;
	}
}

std::vector<Vertex*>*	Object::Get_List_Vertex()
{
	return (&this->V);
}

std::vector<Face*>*	Object::Get_List_Face()
{
	return (&this->F);
}

std::vector<Texture*>*	Object::Get_List_Texture()
{
	return (&this->T);
}

std::vector<Normal*>*	Object::Get_List_Normal()
{
	return (&this->N);
}

void	Object::Add_Vertex(Vertex* v)
{
	this->V.push_back(v);
}

void	Object::Add_Face(Face* f)
{
	this->F.push_back(f);
}

void	Object::Add_Texture(Texture* t)
{
	this->T.push_back(t);
}
void	Object::Add_Normal(Normal* n)
{
	this->N.push_back(n);
}

void	Object::Display(int texture)
{
	int			i;
	int			j;
	int			face_size;
	int			vertex_size;
	Face*			f;
	Vertex*			v;
	std::vector<Vertex*>*	copy;
	Texture*		t;
	std::vector<Texture*>*	copy2;

	i = 0;
	face_size = this->F.size();
	if (texture >= 0)
		glBindTexture(GL_TEXTURE_2D, texture);
	while (i < face_size)
	{
		j = 0;
		f = this->F[i];
		copy = f->Get_List();
		vertex_size = copy->size();
		if (vertex_size == 3)
			glBegin(GL_TRIANGLES);
		else if (vertex_size == 4)
			glBegin(GL_QUADS);
		else
			glBegin(GL_POLYGON);
		while(j < vertex_size)
		{
			copy2 = f->Get_List_Texture();
			if (copy2->size())
			{
				t =  (*copy2)[j];
				glTexCoord2f(t->Get_U(), t->Get_V());
			}
			v = (*copy)[j];
			glVertex3f(v->Get_X(),v->Get_Y(),v->Get_Z());
			j ++;
		}
		glEnd();
		i++;
	}
}
