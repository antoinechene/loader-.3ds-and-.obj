#include "scene.h"


Scene::Scene()
{
}

Scene::~Scene()
{
	size_t	i;
	size_t	size;

	i = 0;
	size = this->mat.size();
	while (i < size)
	{
		delete this->mat[i];
		i++;
	}
	i = 0;
	size = this->obj.size();
	while (i < size)
	{
		delete this->obj[i];
		i++;
	}
	i = 0;
	size = this->texture.size();
	while (i < size)
	{
		delete this->texture[i];
		i++;
	}
}

std::vector<Material*>*	Scene::Get_List_Material()
{
	return (&this->mat);
}

void	Scene::Add_Material(Material* m)
{
	this->mat.push_back(m);
}


std::vector<Object*>*	Scene::Get_List_Object()
{
	return (&this->obj);
}

void	Scene::Add_Object(Object* m)
{
	this->obj.push_back(m);
}

std::vector<tex*>*	Scene::Get_List_Texture()
{
	return (&this->texture);
}

void	Scene::Add_Texture(tex* t)
{
	this->texture.push_back(t);
}

