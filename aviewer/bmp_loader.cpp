#include "bmp_loader.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>
#include <GL/glut.h>
#include <stdio.h>

BMP_Loader::BMP_Loader()
{
}

BMP_Loader::~BMP_Loader()
{
}

int	BMP_Loader::Read(char* filename)
{
	int		i;
	int		j;
	FILE*		l_file; 
	unsigned char*	l_texture;
	GLuint		texid;
	BMP_HEADER	fileheader; 
	BMP_INFO_HEADER	infoheader;
	RGB_TRIPLE	rgb;

	i = 0;
	j = 0;
	if (filename[0]=='\0')
	{
		fprintf( stdout, "Loading BMP file: %s\n",filename);
		return(-1);
	}
	if((l_file = fopen(filename, "rb"))==NULL) 
	{
		fprintf( stdout, "File %s not found!\n",filename);
		return (-1);
	}
	fread(&fileheader, sizeof(fileheader), 1, l_file); 
	if (fileheader.Type != 0x4d42)
		return (-1);
	fseek(l_file, sizeof(fileheader), SEEK_SET); 
	fread(&infoheader, sizeof(infoheader), 1, l_file); 
	l_texture = (unsigned char*) malloc(infoheader.Width * infoheader.Height * 4);
	memset(l_texture, 0, infoheader.Width * infoheader.Height * 4);
	for (i = 0; i < infoheader.Width*infoheader.Height; i ++)
	{            
		fread(&rgb, sizeof(rgb), 1, l_file); 
		l_texture[j + 0] = rgb.R;
		l_texture[j + 1] = rgb.G;
		l_texture[j + 2] = rgb.B;
		l_texture[j + 3] = 255;
		j += 4;
	}
	fclose(l_file);
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.Width, infoheader.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.Width, infoheader.Height, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
	free(l_texture); 
	printf("coucou %d\n",texid);
	return (texid); 

}
