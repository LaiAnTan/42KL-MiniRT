#include "minirt.h"

// bunch of hard code and DEBUG
void	set_the_scene(t_scene *scene, double x)
{
	(void) x;
	matrix_type	pos[3];
	matrix_type	color[3];

	matrix_type	pos_c[3];
	matrix_type	color_c[3];

	scene->camera = init_cam(0,0,0);

	matrix_type	normal[3];

	// cicle
	pos_c[0] = x;
	pos_c[1] = 0;
	pos_c[2] = 320;

	color_c[0] = 255;
	color_c[1] = 255;
	color_c[2] = 0;

	// plane
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 225;

	color[0] = 255;
	color[1] = 0;
	color[2] = 0;

	normal[0] = 1;
	normal[1] = 0;
	normal[2] = -1;

	// normal[0] = x;
	// x -= 10;
	// normal[1] = x;
	// x -= 10;
	// normal[2] = x;

	// scene->objs = init_object(PLANE, pos, color);
	// scene->objs->plane = init_plane(normal);

	// scene->objs->next = init_object(CIRCLE, pos_c, color_c);
	// scene->objs->next->circle = init_circle(55);

	scene->objs = init_object(CIRCLE, pos_c, color);
	scene->objs->circle = init_circle(25);

	// pos[0] = 100;
	// pos[1] = 0;
	// pos[2] = 200;

	// scene->objs->next = init_object(CIRCLE, pos, color);
	// scene->objs->next->circle = init_circle(55);

	// scene->circles = init_circle( 100, 0, 150, 55 );
	// scene->circles->next = init_circle(-50, 0, 150, 32);

	scene->lights = init_light( 35, 35, 35, NULL);

	// scene->lights = init_light( 35, 35, 35, NULL);
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
