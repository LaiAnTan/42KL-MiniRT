#include "minirt.h"

t_circle	*init_circle(int x, int y, int z, int r)
{
	matrix_type	stuff[3] = {x, y, z};
	t_circle	*ret;

	ret = malloc(sizeof(t_circle));
	// hardcode some stuff here for testing;
	ret->position = init_vector_intarr(stuff);
	ret->radius = r;
	ret->next = NULL;
	return ret;
}

void	free_circle(t_circle *c)
{
	t_circle	*temp;
	t_circle	*cur;

	cur = c;
	while (cur)
	{
		temp = cur->next;

		free_vector(&cur->position);
		free(cur);

		cur = temp;
	}
}

t_cam		*init_cam()
{
	matrix_type	position[3] = {0, 0, 0};
	matrix_type	orientation[3] = {0, 0, 1};
	t_cam	*ret;

	ret = malloc(sizeof(t_cam));
	// hardcode some stuff also
	ret->position = init_vector_intarr(position);
	ret->orientation = init_vector_intarr(orientation);
	return (ret);
}

void	free_cam(t_cam *cam)
{
	free_vector(&cam->position);
	free_vector(&cam->orientation);
	free(cam);	
}

t_light		*init_light(int x, int y, int z, double inten)
{
	matrix_type position[3] = {x, y, z};
	t_light		*ret;

	ret = malloc(sizeof(t_light));
	ret->position = init_vector_intarr(position);
	ret->next = NULL;
	// 100000000
	ret->intensity = inten;
	return (ret);
}

void	free_light(t_light *l)
{
	t_light	*temp;
	t_light	*cur;

	cur = l;
	while (cur)
	{
		temp = cur->next;

		free_vector(&cur->position);
		free(cur);

		cur = temp;
	}
}