#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "obj_reader.h"
#include "tool.h"
#include <stdlib.h>
#include <string.h>
#include "scene.h"

ObjReader::ObjReader()
{
	buf = new id_buffer(1024);
	this->cpt = 0;
}

ObjReader::~ObjReader()
{
	delete this->buf;
}

int	ObjReader::read(char* filename)
{
	int			nread;
	int			fd ;
	char*			str2;
	std::vector<Object*>*	LO;
	Object*			O;
	Scene*			scene;

	scene = Scene::GetInstance();
	LO = scene->Get_List_Object();


	O = new Object();
	scene->Add_Object(O);
	fd = open (filename, O_RDONLY);
	if (fd == -1)
	{
		std::cout<<"error to open file"<<std::endl;
		return (42);;
	}
	nread = buf->buf_readfile(fd, 1024);
	while (nread > 0)
	{
		str2 = buf->getline();
		while (str2 != 0)
		{
			this->Construct_Object(str2);
			str2 = buf->getline();
		}
		nread = buf->buf_readfile(fd, buf->space());
	}
	buf->flush();
	if (O->Get_List_Vertex()->size() == 0 || O->Get_List_Face()->size() == 0)
		return (42);
	close(fd);
	return (0);
}

char*	ObjReader::getword(char* str)
{
	size_t	i;
	size_t	j;
	bool	find;
	size_t	size;
	char*	ptr;

	size = strlen(str);
	ptr = new char[size + 1];
	find = false;
	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' ||  str[i] == '\n' || str[i] == '\0')
		{
			ptr[i] = '\0';
			i++;
			find = true;
			break;
		}
		ptr[i] = str[i];
		i ++;
	}
	if (find)
	{
		while (i <= size)
		{
			str[j] = str[i];
			i ++;
			j ++;
		}
		return (ptr);
	}
	else
	{
		delete[] ptr;
		return (0);
	}
}
char*	getWord(char* str)
{
	size_t	i;
	size_t	j;
	bool	find;
	size_t	size;
	char*	ptr;

	size = strlen(str);
	ptr = new char[size + 1];
	find = false;
	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '/')
		{
			ptr[i] = '\0';
			i++;
			find = true;
			break;
		}
		ptr[i] = str[i];
		i ++;
	}
	if (find)
	{
		while (i <= size)
		{
			str[j] = str[i];
			i ++;
			j ++;
		}
		return (ptr);
	}
	else
	{
		delete[] ptr;
		return (0);
	}
}

void	ObjReader::Construct_Object(char* buf)
{
	char*			str;

	str = getword(buf);
	if (str != 0)
	{
		if (strcmp("v", str) == 0)
			this->Construct_Vertex(buf, str);
		else if (strcmp("f", str) == 0)
			this->Construct_Face(buf, str);
		else if (strcmp("vt", str) == 0)
			this->Construct_Texture(buf, str);
		else if (strcmp("vn", str) == 0)
			this->Construct_Normal(buf, str);
		else
			return;
	}
	return;
}

void	ObjReader::Construct_Normal(char* buf, char* str)
{
	Object*				O;
	std::vector<Object*>*		LO;
	Normal*				N;
	int				i;
	Scene*				scene;

	scene = Scene::GetInstance();
	i = 0;
	LO = scene->Get_List_Object();
	O = (*LO)[0];
	N = new Normal();
	while (str != 0)
	{
		str = getword(buf);
		if (str != 0)
		{
			if (i == N1)
				N->Set_N1(atof(str));
			else if (i == N2)
				N->Set_N2(atof(str));
			else if (i == N3)
			{
				N->Set_N3(atof(str));
				i = 0;
				O->Add_Normal(N);
			}
		}
		i ++;
	}
}

void	ObjReader::Construct_Texture(char* buf, char* str)
{
	Object*				O;
	std::vector<Object*>*		LO;
	Texture*			T;
	int				i;
	int				j;
	Scene*				scene;

	scene = Scene::GetInstance();
	i = 0;
	j = 0;
	LO = scene->Get_List_Object();
	O = (*LO)[0];
	T = new Texture();
	while (str != 0)
	{
		str = getword(buf);
		if (str != 0 && j < 2)
		{
			if (i == U)
				T->Set_U(atof(str));
			else if (i == V)
			{
				this->cpt ++;
				T->Set_V(atof(str));
				i = 0;
				O->Add_Texture(T);
			}
		}
		j ++;
		i ++;
	}
}

void	ObjReader::Construct_Vertex(char* buf, char* str)
{
	Object*					O;
	std::vector<Object*>*			LO;
	Vertex*					V;
	int					i;
	Scene*					scene;

	scene = Scene::GetInstance();

	i = 0;
	LO = scene->Get_List_Object();
	O = (*LO)[0];
	V = new Vertex();
	while (str != 0)
	{
		str = getword(buf);
		if (str != 0)
		{
			if (i == X)
				V->Set_X(atof(str));
			else if (i == Y)
				V->Set_Y(atof(str));
			else if (i == Z)
			{
				V->Set_Z(atof(str));
				i = 0;
				O->Add_Vertex(V);
			}
		}
		i ++;
	}
}

void	ObjReader::Construct_Face(char* buf, char* str)
{
	std::vector<Vertex*>*		cpy;
	Face*				F;
	Object*				O;
	size_t				index;
	std::vector<Object*>*		LO;
	Scene*				scene;
	int				cpt;

	scene = Scene::GetInstance();
	LO = scene->Get_List_Object();
	O = (*LO)[0];
	cpy = O->Get_List_Vertex();
	F = new Face();
	while (str != 0)
	{
		str = getword(buf);
		if (str != 0)
			index = atoi(str) -1 ;
			if ((int)index >= 0 && index < cpy->size())
				F->Add_Index((*cpy)[index]);
		cpt++;
	}
	O->Add_Face(F);
}
