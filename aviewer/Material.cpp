#include "Material.h"
#include <string.h>

Material::Material(const char* name)
{
	this->name = strdup(name);
}



Material::~Material()
{
	delete[] this->name;
	delete[] this->map_ka;
	delete[] this->map_kd;
	delete[] this->map_ks;
	delete[] this->map_ns;
	delete[] this->map_d;
	delete[] this->disp;
	delete[] this->decal;
	delete[] this->bump;

}
