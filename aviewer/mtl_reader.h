#ifndef mtl_reader_h
#define mtl_reader_h
#include "buffer.h"
class MTL_Reader
{
	public:
		MTL_Reader();
		~MTL_Reader();
		char*	getword(char* str);
		int	read(char* filename);
		void	Construct_Material(char* buf);

	private:
		id_buffer*	buf;
		int		cpt;
};


#endif
