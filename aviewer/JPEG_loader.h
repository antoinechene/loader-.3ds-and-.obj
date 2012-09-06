#ifndef JPEG_loader_h
#define JPEG_loader_h
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <jpeglib.h>
#include <GL/glut.h>

class	JPEG_Loader
{
	public:
		JPEG_Loader();
		~JPEG_Loader();
		int	Load_JPEG(const char* filename);
	private:
		GLuint*		TexNum;


};

#endif
