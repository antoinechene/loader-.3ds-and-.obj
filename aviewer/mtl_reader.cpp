#include "mtl_reader.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "Material.h"
#include "scene.h"
MTL_Reader::MTL_Reader()
{
	this->buf = new id_buffer(1024);
	this->cpt = -1;
}

MTL_Reader::~MTL_Reader()
{
	delete this->buf;
}

int	MTL_Reader::read(char* filename)
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
	std::cout<<"filename "<<filename<<std::endl;
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
			this->Construct_Material(str2);
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

char*	MTL_Reader::getword(char* str)
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
		if (str[i] == ' ' ||  str[i] == '\n' || str[i] == '\0' )
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

void	MTL_Reader::Construct_Material(char* buf)
{
	char*		str;
	Material*	M;
	Scene*		scene;

	scene = Scene::GetInstance();
	str = getword(buf);
	if (this->cpt != -1)
		M = (*scene->Get_List_Material())[cpt];
	if (str != 0)
	{
		std::cout<<"str "<<str<<std::endl;
		if (strcmp("newmtl",str) == 0)
		{
			std::cout<<"create material"<<std::endl;
			str = getword(buf);
			M = new Material(str);
			scene->Add_Material(M);
			this->cpt++;
		}
		else if (strcmp("Ns",str) == 0)
		{
			str = getword(buf);
			M->ns = atof(str);
		}
		else if (strcmp("Ni",str) == 0)
		{
			str = getword(buf);
			M->ni = atof(str);
		}
		else if (strcmp("d",str) == 0)
		{
			str = getword(buf);
			M->d = atof(str);
		}
		else if (strcmp("Tr",str) == 0)
		{
			str = getword(buf);
			M->tr = atof(str);
		}
		else if (strcmp("Tf",str) == 0)
		{
			str = getword(buf);
			M->tf.G = atof(str);
			str = getword(buf);
			M->tf.R = atof(str);
			str = getword(buf);
			M->tf.B = atof(str);
		}
		else if (strcmp("illum",str) == 0)
		{
			str = getword(buf);
			M->illum = atoi(str);
		}
		else if (strcmp("Ka", str) == 0)
		{
			str = getword(buf);
			std::cout<<"str ka "<<str<<std::endl;
			M->ka.G = atof(str);
			str = getword(buf);
			M->ka.R = atof(str);
			str = getword(buf);
			M->ka.B = atof(str);
		}
		else if (strcmp("Kd",str) == 0)
		{
			str = getword(buf);
			M->kd.G = atof(str);
			str = getword(buf);
			M->kd.R = atof(str);
			str = getword(buf);
			M->kd.B = atof(str);
		}
		else if (strcmp("Ks",str) == 0)
		{
			str = getword(buf);
			M->ks.G = atof(str);
			str = getword(buf);
			M->ks.R = atof(str);
			str = getword(buf);
			M->ks.B = atof(str);
		}
		else if (strcmp("Ke",str) == 0)
		{
			str = getword(buf);
			M->ke.G = atof(str);
			str = getword(buf);
			M->ke.R = atof(str);
			str = getword(buf);
			M->ke.B = atof(str);
		}
		else if (strcmp("map_Ka",str) == 0)
		{
			str = getword(buf);
			M->map_ka = str;
		}
		else if (strcmp("map_Kd",str) == 0)
		{
			str = getword(buf);
			M->map_kd = str;
		}
		else if (strcmp("map_Ks",str) == 0)
		{
			str = getword(buf);
			M->map_ks = str;
		}
		else if (strcmp("map_Ns",str) == 0)
		{
			str = getword(buf);
			M->map_ns = str;
		}
		else if (strcmp("map_d",str) == 0)
		{
			str = getword(buf);
			M->map_d = str;
		}
	}
}
