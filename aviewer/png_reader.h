#ifndef png_reader_h
#define png_reader_h
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>

#include <string.h>

#include <png.h>

struct	gl_texture_t
{
	GLsizei		width;
	GLsizei		height;
	GLenum		format;
	GLint		internalFormat;
	GLuint		id;
	GLubyte*	texels;
};

class PNG_Reader
{
	public:
					PNG_Reader();
					~PNG_Reader();
		GLuint			loadPNGTexture (const char *filename);
		struct gl_texture_t*	ReadPNGFromFile (const char *filename);
		void			GetPNGtextureInfo (int color_type, struct gl_texture_t *texinfo);
	private:
		GLuint	texId;
};
#endif
