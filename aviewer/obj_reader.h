#ifndef obj_h
#define obj_h
#include "buffer.h"

enum vertices
{
	X = 0,
	Y,
	Z
};

enum texture
{
	U = 0,
	V
};

enum normal
{
	N1 = 0,
	N2,
	N3
};
enum	face
{
	VERTEX,
	TEXTURE,
	NORMAL
};


class ObjReader
{
	public:
			ObjReader();
			~ObjReader();
		int	read(char* filename);
		void	Construct_Object(char* buf);
		char*	getword(char* str);
		void	Construct_Face(char* buf, char* str);
		void	Construct_Vertex(char* buf, char* str);
		void	Construct_Texture(char* buf, char* str);
		void	Construct_Normal(char* buf, char* str);
	private:
		id_buffer*	buf;
		int		cpt;
};
#endif
