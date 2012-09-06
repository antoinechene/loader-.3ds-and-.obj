#ifndef loader_3ds_h
#define loader_3ds_h
#include "buffer.h"
#include "object.h"
#include "vertex.h"

class Loader3ds
{
	public:
			Loader3ds();
			~Loader3ds();
		int	Load3ds(char* filename);
		long	filelength(int f);
		int	ObjectBlock(int fd);
		void	VerticeList(int fd, double* len, Object* o);
		void	FacesDescription(int fd, double* len, Object* o);
		void	MappingCoordinatesList(int fd, double*
		len, Object* o);
		void	ReadMaterials(int fd, double* len);

	private:
		bool*	MatDside;
		int	count;
};
#endif
