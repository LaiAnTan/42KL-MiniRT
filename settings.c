#include "minirt.h"

// bunch of hard code and DEBUG
void	set_the_scene(t_scene *scene, double x)
{
	(void) x;
	scene->camera = init_cam(0,0,0);
	scene->circles = init_circle( x, 0, 150, 55 );
	// scene->circles = init_circle( 100, 0, 150, 55 );
	// scene->circles->next = init_circle(-50, 0, 150, 32);

	scene->lights = init_light( 35, 35, 35, NULL);
	// scene->lights = init_light( -300, 100, 150, NULL);
	// scene->lights->next = init_light( -300, -100, 150, NULL);

	scene->ambient = init_ambient(255, 255, 255, 0.2);
	// scene->ambient = init_ambient(255, 255, 255, 1);

	// deprecated.. i think
	// inten = 125000000;
	// scene->lights = init_light(100,150,200, inten);

	// inten = 1250000000;
	// scene->lights->next = init_light(-100,-150,200, inten);
}
