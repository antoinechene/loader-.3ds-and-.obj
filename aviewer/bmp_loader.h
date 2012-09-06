#ifndef bmp_loader
#define bmp_loader

struct BMP_HEADER
{
	unsigned short	Type;
	unsigned int	Size;
	unsigned short	Apli;
	unsigned short	Apli2;
	unsigned int	Offset;
}
#ifdef __GNUC__
__attribute__((packed))
#endif
;

#define BF_TYPE 0x4D42

struct BMP_INFO_HEADER
{
	unsigned int	Size;
	int		Width;
	int		Height;
	unsigned short	Plane;
	unsigned short	BitCount;
	unsigned int	Compression;
	unsigned int	Size_Image;
	int		XPelsPerMeter;
	int		PelsPerMeter;
	unsigned int	ClrUsed;
	unsigned int	ClrImportant;
//har*		data;
}
#ifdef __GNUC__
__attribute__((packed))
#endif
;

struct RGB_TRIPLE
{
	unsigned char B;
	unsigned char G;
	unsigned char R;
}
#ifdef __GNUC__
__attribute__((packed))
#endif
;


class BMP_Loader
{
	public:
		BMP_Loader();
		~BMP_Loader();
		int	Read(char* pathname);
	private:
};

#endif
