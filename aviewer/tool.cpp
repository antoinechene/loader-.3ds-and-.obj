#include "tool.h"
#include <string.h>
#include <stdlib.h>
#include "face.h"
#include "scene.h"
void	exit()
{
	Scene::Kill();
	Display::Kill();
}
