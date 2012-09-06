NAME = id_aviewer

SRC =	buffer.cpp\
	main.cpp\
	vertex.cpp\
	face.cpp\
	tool.cpp\
	Bviewer.cpp\
	object.cpp\
	obj_reader.cpp\
	3ds_reader.cpp\
	Display.cpp\
	texture.cpp\
	normal.cpp\
	bmp_loader.cpp\
	JPEG_loader.cpp\
	png_reader.cpp\
	Material.cpp\
	mtl_reader.cpp\
	scene.cpp
OBJ = $(SRC:.cpp=.o)

LDFLAGS = -lglut -lGLU -lGL -lpng -ljpeg
CXXFLAGS = -Wall -W  -g3

$(NAME): $(OBJ)
	g++ $(CXXFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS) libjpeg.a libpng.a

clean:
	rm -rf $(OBJ)

distclean: clean
	rm -rf $(NAME)

rebuild: distclean $(NAME)
