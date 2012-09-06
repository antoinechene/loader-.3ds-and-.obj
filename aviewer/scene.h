#ifndef scene_h
#define scene_h
#include <iostream>
#include <list>
#include <vector>
#include "Singleton.hpp"
#include "object.h"
#include "Material.h"
#include "object.h"
struct tex
{
	char*	name;
	int	id;
};

class Scene : public Singleton<Scene>
{
	friend class Singleton<Scene>;

	public:
		std::vector<Material*>*		Get_List_Material();
		void				Add_Material(Material* m);
		std::vector<Object*>*		Get_List_Object();
		void				Add_Object(Object* m);
		std::vector<tex*>*		Get_List_Texture();
		void				Add_Texture(tex* m);
	private:
					Scene();
					~Scene();
		std::vector<Material*>	mat;
		std::vector<Object*>	obj;
		std::vector<tex*>	texture;
};
#endif
