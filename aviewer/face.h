#ifndef face_h
#define face_h
#include "vertex.h"
#include "texture.h"
#include <iostream>
#include <list>
#include <vector>
#include "normal.h"


class Face
{
	public:
					Face();
					~Face();
		std::vector<Vertex*>*	Get_List();
		void			Add_Index(Vertex* V);
		std::vector<Texture*>*	Get_List_Texture();
		void			Add_Texture(Texture* V);
		std::vector<Normal*>*	Get_List_Normal();
		void			Add_Normal(Normal* V);
		void			Set_Id_Tex(char* str);
	private:
		std::vector<Vertex*>	index;
		std::vector<Texture*>	Tex;
		std::vector<Normal*>	norm;
		char*			id_tex;
};
#endif
