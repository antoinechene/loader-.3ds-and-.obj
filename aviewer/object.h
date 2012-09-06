#ifndef object_h
#define object_h
#include "face.h"
#include "vertex.h"
#include "texture.h"
#include "normal.h"

class Object 
{
	public:
					Object();
					~Object();
		std::vector<Vertex*>*	Get_List_Vertex();
		std::vector<Face*>*	Get_List_Face();
		void			Add_Vertex(Vertex* v);
		void			Add_Face(Face* f);
		void			Display(int num_tex);
		std::vector<Texture*>*	Get_List_Texture();
		void			Add_Texture(Texture* v);
		std::vector<Normal*>*	Get_List_Normal();
		void			Add_Normal(Normal* v);

	private:
		std::vector<Face*>	F;
		std::vector<Vertex*>	V;
		std::vector<Texture*>	T;
		std::vector<Normal*>	N;
};
#endif
