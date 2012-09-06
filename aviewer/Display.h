#ifndef display_h
#define display_h
#include "Singleton.hpp"
#include <iostream>
#include <vector>
class Display : public Singleton<Display>
{
	friend class Singleton<Display>;

	public:
			Display();
			~Display();
		int	screen_width;
		int	screen_height;
		double	rotation_x;
		double	rotation_y;
		double	rotation_z;
		int	old_x;
		int	old_y;
		bool	filling;
		double	zoom;
};
#endif
