#include "Bviewer.h"
#include "vertex.h"
#include "Display.h"
#include "tool.h"
#include "bmp_loader.h"
#include "JPEG_loader.h"
#include "png_reader.h"
#include "scene.h"
void	init(int argc, char** argv)
{
	Display*	disp;
	int		width;
	int		height;
	PNG_Reader	P;
	int		i;
	BMP_Loader	B;
	JPEG_Loader	J;
	Scene*		scene;
	struct	tex*	t;

	scene = Scene::GetInstance();
	i = 2;
	disp = Display::GetInstance();
	width = disp->screen_width;
	height = disp->screen_height;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Bviewer");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard_s);
	glutMotionFunc(mouse);
	glutMouseFunc(callback);
	atexit(exit);
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 10000.0f);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	while (i < argc)
	{
		t = new tex();
		t->name = strdup(argv[i]);
		t->id = P.loadPNGTexture(argv[i]);
		if (t->id == -1)
		{
			t->id = B.Read(argv[i]);
			if (t->id == -1)
			{	
				t->id = J.Load_JPEG(argv[i]);
				if (t->id != -1)
					scene->Add_Texture(t);
			}
			else
				scene->Add_Texture(t);
		}
		else
			scene->Add_Texture(t);
		i ++;
	}
	glEnable(GL_TEXTURE_2D);
}

void	resize(int w, int h)
{
	Display*	disp;
	int		width;
	int		height;

	disp = Display::GetInstance();
	disp->screen_width = w;
	disp->screen_height = h;
	width = disp->screen_width;
	height = disp->screen_height;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 1.0f, 1000.0f);
	glutPostRedisplay();
}

void	keyboard(unsigned char key, int x, int y)
{
	(void)x;
	(void)y;
	double		zoom;
	bool		fill;
	Display*	disp;

	disp = Display::GetInstance();
	zoom = disp->zoom;
	fill = disp->filling;
	if (key == ' ')
	{
		disp->rotation_x = 0;
		disp->rotation_y = 0;
		disp->rotation_z = 0;
	}
	if (key == 'r' || key == 'R')
	{
		if (fill == false)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			disp->filling = true;
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			disp->filling = false;
		}
	}
	else if (key == '+')
		disp->zoom = zoom + 10.0;
	else if (key == '-')
		disp->zoom = zoom - 10.0;
}

void	callback(int button, int state, int x, int y)
{
	Display*	disp;

	disp = Display::GetInstance();

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		disp->old_x = x;
		disp->old_y = y;
	}
	return;
}

void	mouse(int x, int y)
{
	int		move_x;
	int		move_y;
	int		old_x;
	int		old_y;
	double		rx;
	double		ry;
	Display*	disp;

	disp = Display::GetInstance();
	old_x = disp->old_x;
	old_y = disp->old_y;
	rx = disp->rotation_x;
	ry = disp->rotation_y;
	move_x = x - old_x;
	if (move_x)
		disp->rotation_y = ry + move_x / 10.0;
	move_y = y - old_y;
	if (move_y)
		disp->rotation_x = rx + move_y / 10.0;
	disp->old_x = x;
	disp->old_y = y;
}

void	keyboard_s(int key, int x, int y)
{
	(void)x;
	(void)y;
	Display*	disp;
	double		rx;
	double		ry;

	disp = Display::GetInstance();
	rx = disp->rotation_x;
	ry = disp->rotation_y;
	if (key == GLUT_KEY_UP)
		disp->rotation_x = rx + 2.5;
	else if (key == GLUT_KEY_DOWN)
		disp->rotation_x = rx - 2.5;
	else if (key == GLUT_KEY_LEFT)
		disp->rotation_y = ry + 2.5;
	else if (key == GLUT_KEY_RIGHT)
		disp->rotation_y = ry - 2.5;
}

void	gameCycle()
{
	static double	current_time = 0;
	static double	last_time = 0;
	double		fps;
	double		res;

	last_time = current_time;
	current_time = (double)glutGet(GLUT_ELAPSED_TIME) / 1000;
	res = (current_time - last_time);
	if (res)
	{
		fps =  1.0 / res;
		std::cout<< "fps: "<<fps<<std::endl;
	}
}

void	display()
{
	int			i;
	int			size_obj;
	Object*			obj;
	Display*		disp;
	double			rx;
	double			ry;
	double			rz;
	double			zoom;
	std::vector<Object*>*	O;
	Scene*			scene;
	std::vector<tex*>*	T;

	scene = Scene::GetInstance();
	O = scene->Get_List_Object();
	disp = Display::GetInstance();
	zoom = disp->zoom;
	rx = disp->rotation_x;
	ry = disp->rotation_y;
	rz = disp->rotation_z;
//	gameCycle();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, zoom);
	if (rx > 359)
		disp->rotation_x = 0;
	if (ry > 359)
		disp->rotation_y = 0;
	if (rz > 359)
		disp->rotation_z = 0;
	rx = disp->rotation_x;
	ry = disp->rotation_y;
	rz = disp->rotation_z;
	glRotatef(rx, 1.0, 0.0, 0.0);
	glRotatef(ry, 0.0, 1.0, 0.0);
	glRotatef(rz, 1.0, 0.0, 1.0);
	i = 0;
	size_obj =  O->size();
	T = scene->Get_List_Texture();
	while (i < size_obj)
	{
		obj = (*O)[i];
		if (T->size() > 0)
		{
			obj->Display((*T)[i]->id);
		}
		else
			obj->Display(-1);
		i++;
	}
	glFlush();
	glutSwapBuffers();
}
