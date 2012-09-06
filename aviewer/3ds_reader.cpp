#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "3ds_reader.h"
#include <stdio.h>
#include <string.h>
#include "scene.h"
#include <fcntl.h>
//#include <fstream>
#include <iostream>

Loader3ds::Loader3ds()
{
}

Loader3ds::~Loader3ds()
{
}

int	Loader3ds::Load3ds(char* filename)
{
	int							i;
	int							fd;
	unsigned short				chunk_id;
	unsigned int				chunk_length;
	double						len;
	Object*						o;
	std::vector<Object*>*		LO;
	Scene*						scene;
//	std::ifstream				my_file(filename);

	scene = Scene::GetInstance();
	LO = scene->Get_List_Object();
	len = 0.0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		std::cout<<"impossible d'ouvrir le fichier"<<std::endl;
		return (42);
	}
	while (len < filelength(fd))
	{
		read(fd, &chunk_id, 2);
		len = len + 2;
		read(fd, &chunk_length, 4);
		len = len + 4;
		if (chunk_id == 0x4d4d)
			;
		else if(chunk_id == 0x3d3d)	//debut des data
			;
		else if(chunk_id == 0x4000)	//object name
		{
			i = this->ObjectBlock(fd);
			len = len + i * sizeof(unsigned char);
			o = new Object();
			scene->Add_Object(o);
		}
		else if(chunk_id == 0x4100)	//matrix
			;
		else if(chunk_id == 0x4110)	//construction vertice
			this->VerticeList(fd, &len, o);
		else if (chunk_id == 0x4120)
			this->FacesDescription(fd, &len, o);	//construction face
		else if (chunk_id == 0x4140)	//mapping ccordonate list
			this->MappingCoordinatesList(fd, &len, o);
		else if (chunk_id == 0x4130)	//materiau
		{
			unsigned char		l_char;
			char*			str;
			unsigned short		numface;
			unsigned short*		faceassign;
			std::vector<Face*>*	F;

			str = new char [100];
			memset(str, 0, 100);
			i = 0;
			 read (fd, &l_char, 1);
			i++;
			while (l_char != '\0')
			{
				read (fd, &l_char, 1);
				i++;
			}
			F = o->Get_List_Face();
			len = len + i * sizeof(unsigned char);
			read(fd, &numface, sizeof(numface));
			len = len +  sizeof(numface);
			faceassign = new unsigned short[numface];
			read(fd, faceassign, numface * sizeof(numface));
			len = len + numface * sizeof(numface);
			for(int i = 0; i < numface;i++)
				(*F)[faceassign[i]]->Set_Id_Tex(str);
		}
		else if (chunk_id == 0xafff) //debut des materiaux
			;
		else if (chunk_id == 0xa000)	//matname
		{
			int	i;
			
			i = this->ObjectBlock(fd);
			len = len + i * sizeof(unsigned char);
		}
		else if (chunk_id == 0xa354)	//matmap vscale
		{
			float	vscale;
			read(fd,&vscale, sizeof(float));
			len = len + sizeof(float);
		}
		else if (chunk_id == 0xa356)	//matmap uscale
		{
			float	uscale;
			read(fd,&uscale, sizeof(float));
			len = len + sizeof(float);
		}
		else if (chunk_id == 0xa358)	//matmap uoffset
		{
			float	uoffset;
			read(fd,&uoffset, sizeof(float));
			len = len + sizeof(float);
		}
		else if (chunk_id == 0xa35a)	//matmap voffset
		{
			float	voffset;
			read(fd,&voffset, sizeof(float));
			len = len + sizeof(float);
		}
		else if (chunk_id == 0xa35c)	//matmpa angle
		{
			float	rot;
			read(fd,&rot, sizeof(float));
			len = len + sizeof(float);
		}
		else if (chunk_id == 0x2100)	//ambiant light
		{
			size_t	i;
			unsigned char uchar;

			i = 0;
			while(i < chunk_length - 6)
			{
				read(fd, &uchar,sizeof(unsigned char));
				i ++;
			}
			len = len + i * sizeof(uchar);
		}
		else if (chunk_id == 0x0011)	//color ???????????????????????
		{
			int	r,g,b;
			read(fd, &r, sizeof(unsigned char));
			read(fd, &g, sizeof(unsigned char));
			read(fd, &b, sizeof(unsigned char));
			len = len + 3 * sizeof(unsigned char);
		}
		else if (chunk_id == 0xa300)	//mat mapname +??????
		{
			size_t	i;
			unsigned char uchar;

			i = 0;
			while(i < chunk_length - 6)
			{
				read(fd, &uchar,sizeof(unsigned char));
				i ++;
			}
			len = len + i * sizeof(uchar);
		}
		else
		{
			lseek(fd, chunk_length -6, SEEK_CUR);
			len = len + chunk_length -6;
		}
	}
	close(fd);
	return (0);
}

void	Loader3ds::MappingCoordinatesList(int fd, double* len, Object* o)
{
	int			i;
	unsigned short		l_qty;
	float			map;
	int			nread;
	Texture*		T;
	

	i = 0;
	nread = read(fd, &l_qty, sizeof(l_qty));
	len = len +  sizeof(l_qty);
	while (i < l_qty)
	{
		T = new Texture();
		nread = read(fd, &map, sizeof(map));
		T->Set_U(map);
		nread = read(fd, &map, sizeof(map));
		T->Set_V(map);
		len = len + (2 * sizeof(map));
		o->Add_Texture(T);
		i ++;
	}
}

void	Loader3ds::FacesDescription(int fd, double* len, Object* o)
{

	std::vector<Vertex*>*	cpy;
	std::vector<Texture*>*	cpy2;
	int			i;
	unsigned short		l_qty;
	unsigned short		index;
	unsigned short		l_flag;
	Face*			F;
	int			nread;

	cpy = o->Get_List_Vertex();
	cpy2 = o->Get_List_Texture();
	i = 0;
	nread = read (fd, &l_qty, sizeof(l_qty));
	len = len +  sizeof(l_qty);
	while (i < l_qty)
	{
		F = new Face();
		nread = read(fd, &index , sizeof(index));
		F->Add_Index((*cpy)[index]);
		if (cpy2->size())
			F->Add_Texture((*cpy2)[index]);
		nread = read(fd, &index , sizeof(index));
		F->Add_Index((*cpy)[index]);
		if (cpy2->size())
			F->Add_Texture((*cpy2)[index]);
		nread = read(fd, &index , sizeof(index));
		F->Add_Index((*cpy)[index]);
		if (cpy2->size())
			F->Add_Texture((*cpy2)[index]);
		o->Add_Face(F);
		nread = read(fd, &l_flag , sizeof(l_flag));
		len = len + (4 * sizeof(index));
		i++;
	}
}

void	Loader3ds::VerticeList(int fd, double* len, Object* o)
{
	Vertex*		V;
	int		i;
	unsigned short	l_qty;
	float		x;
	float		y;
	float		z;
	int		nread ;

	i = 0;
	nread = read(fd, &l_qty, sizeof(l_qty));
	len = len + sizeof(l_qty);
	while (i < l_qty)
	{
		V = new Vertex();
		nread = read(fd, &x , sizeof(x));
		nread = read(fd, &y , sizeof(y));
		nread = read(fd, &z , sizeof(z));
		V->Set_X(x);
		V->Set_Y(y);
		V->Set_Z(z);
		o->Add_Vertex(V);
		len = len + (3 * sizeof(x));
		i++;
	}
}

int	Loader3ds::ObjectBlock(int fd)
{
	unsigned char	l_char;
	int		i;
	int		nread;

	i = 0;
	nread = read (fd, &l_char, 1);
	i++;
	while (l_char != '\0')
	{
		nread =read (fd, &l_char, 1);
		i++;
	}
	return (i);
}

long	Loader3ds::filelength(int f)
{
	struct stat buf;

	fstat(f, &buf);
	return (buf.st_size);
}
