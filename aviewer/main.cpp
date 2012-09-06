#include <GL/glut.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tool.h"
#include "Bviewer.h"
#include "obj_reader.h"
#include "3ds_reader.h"
#include "Display.h"
#include "bmp_loader.h"
#include "mtl_reader.h"
#

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		printf("id_aviewer + file(obj/3ds) and if you want texture file\n");
		return (0);
	}
		
	int				ret;
	Display*			disp;
	unsigned short			chunkid;
	int 				fd;

	disp = Display::GetInstance();
	fd = open(argv[1], O_RDONLY);
	read(fd, &chunkid, 2);
	if (chunkid == 0x4d4d)
	{
		Loader3ds	L;
		init(argc, argv);
		close(fd);
		ret = L.Load3ds(argv[1]);
		if(ret)
		{
			exit();
			std::cout<<"error to load file"<<std::endl;
			return(42);
		}
	}
	else
	{
		ObjReader	R;
		init(argc, argv);
		close(fd);
		ret = R.read(argv[1]);
		if(ret)
		{
			std::cout<<"error to load file"<<std::endl;
			exit();
			return(42);
		}
	}
	glutMainLoop();
	return (0);
}
