#ifndef material_h
#define material_h

struct color
{
	float	R;
	float	B;
	float	G;
};

enum	ilumination
{
	AMBIENT_OFF,
	AMBIENT_ON,
	HILIGHT_ON,
	RFELECTION_ON_RAYTRACE_ON,
	TRANSPARENCY_GLASS_ON,
	REFLECTION_FRESNEL_ON_RAYTRACE_ON,
	REFRACTION_ON_REFLECTION_FRESNEL_OFF_RAYTRACE_ON,
	REFRACTION_ON_REFLECTION_FRESNEL_ON_RAYTRACE_ON,
	REFLECTION_ON_RAYTRACE_OFF,
	TRANSPARENCY_GLASS_ON_REFLECTION_RAYTRACE_OFF,
	CAST_SHADOWS_ONTO_INVISIBLE_SURFACES
};

class Material
{
	public:
		Material(const char* name);
		~Material();


	float	ns;	//specuar value
	float	ni;	//opticla density
	float	d;	//dissolve factor
	float	tr;	//transparancy //
	color	tf;	//transmission filter 3 valeur
	int	illum; //illumination model
	color	ka; //ambient reflection 3valuers//
	color	kd;	//diffuse reflexion
	color	ks;	//specular reflexion 3 valuers//
	color	ke;	//emmissive color 3 valaurs
	char*	name;
	int	shapeness;
	char*	map_ka;	//fileka
	char*	map_kd;	//filekd
	char*	map_ks;	//fileks
	char*	map_ns;	//filems
	char*	map_d;	//file d
	char*	disp;
	char*	decal;
	char*	bump;

	private:


};


#endif
