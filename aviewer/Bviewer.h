#ifndef Bviewer_h
#define Bviewer_h
#include <GL/glut.h>
#include <iostream>

	void	init(int argc, char** argv);
	void	resize(int w, int h);
	void	keyboard(unsigned char key, int x, int y);
	void	keyboard_s(int key, int x, int y);
	void	display();
	void	mouse(int,int);
	void	callback(int button, int state, int x, int y);
#endif
