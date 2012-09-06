#include "JPEG_loader.h"

JPEG_Loader::JPEG_Loader()
{
	this->TexNum = new GLuint[1];

}

JPEG_Loader::~JPEG_Loader()
{
	delete TexNum;
}


int	JPEG_Loader::Load_JPEG(const char* filename)
{

	struct	jpeg_decompress_struct	cInfo;
	struct	jpeg_error_mgr		jerr;
	GLubyte*			line;
	GLubyte*			image;
	int				ImageSize;
	FILE *				pFile;

	cInfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cInfo);
	if((pFile = fopen(filename, "rb")) == NULL) 
	{
		std::cout<<"error to open file"<<std::endl;
		return (0);
	}
	jpeg_stdio_src(&cInfo, pFile);
	jpeg_read_header(&cInfo, true);
	jpeg_start_decompress(&cInfo);
	ImageSize = cInfo.image_width * cInfo.image_height * 3;
	image = new GLubyte[ImageSize];
	line = image;
	while (cInfo.output_scanline < cInfo.output_height)
	{
		line = image + 3 * cInfo.image_width * cInfo.output_scanline;
		jpeg_read_scanlines (&cInfo, &line, 1);
	}
	jpeg_finish_decompress(&cInfo);
	jpeg_destroy_decompress(&cInfo);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &TexNum[0]);
	glBindTexture(GL_TEXTURE_2D, TexNum[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0 ,GL_RGB, cInfo.image_width, cInfo.image_height, 0 ,GL_RGB, GL_UNSIGNED_BYTE,
	image);
	fclose(pFile);
	free(image);
	return TexNum[0];
}
