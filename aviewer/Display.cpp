#include "Display.h"

Display::Display()
{
	this->screen_width = 800;
	this->screen_height = 800;
	this->rotation_x = 0;
	this->rotation_y = 0;
	this->rotation_z = 0;
	this->old_x = 0;
	this->old_y = 0;
	this->filling = true;
	this->zoom = -60;
}

Display::~Display()
{
}

