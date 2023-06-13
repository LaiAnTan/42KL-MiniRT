#include "minirt.h"

t_circle	*init_circle(int r)
{
	t_circle	*ret;

	ret = malloc(sizeof(t_circle));
	ret->radius = r;
	return ret;
}

t_cam		*init_cam(int x, int y, int z)
{
	matrix_type	position[3] = {x, y, z};
	matrix_type	orientation[3] = {0, 0, 1};
	t_cam	*ret;

	ret = malloc(sizeof(t_cam));
	// hardcode some stuff also
	ret->position = init_vector_intarr(position);
	ret->orientation = init_vector_intarr(orientation);
	return (ret);
}

t_light		*init_light(int x, int y, int z, matrix_type *color)
{
	matrix_type position[3] = {x, y, z};
	matrix_type def_color[3] = {255,255,255}; // <-- white light
	t_light		*ret;

	ret = malloc(sizeof(t_light));
	ret->position = init_vector_intarr(position);
	if (color)
		ret->color = init_vector_intarr(color);
	else
		ret->color = init_vector_intarr(def_color);
	ret->next = NULL;
	return (ret);
}

t_ambient	*init_ambient(int r, int g, int b, double ambient_strength)
{
	// cant remember name of this one :skull
	// double		ambient_strength; // domain is [0 , 1]
	// ambient_strength = 0.1;
	
	matrix_type	stuff[] = {r * ambient_strength, g * ambient_strength, b * ambient_strength};
	t_ambient	*ret;

	ret = malloc(sizeof(t_ambient));
	ret->color = init_vector_intarr(stuff);
	// ret->ambient_ratio = v_scalar_divide(ret->color, 255);
	// ret->multiply_mtrx = m_make_diagonal_matrix(ret->ambient_ratio->raw_matrix);
	return (ret);
}

t_objects	*init_object(int type, double *pos, double *rgb)
{
	t_objects	*ret;

	ret = malloc(sizeof(t_objects));
	ret->type = type;
	ret->position = init_vector_intarr(pos);
	ret->color = init_vector_intarr(rgb);
	ret->circle = NULL;
	ret->plane = NULL;
	ret->next = NULL;
	return (ret);
}

t_plane	*init_plane(double *normal)
{
	t_plane	*ret;

	ret = malloc(sizeof(t_plane));
	ret->normal_vect = init_vector_intarr(normal);
	ret->normal_vect = v_get_unit_v(ret->normal_vect);
	return (ret);
}

void	free_circle(t_circle **c)
{
	free((*c));
	(*c) = NULL;
}

void	free_plane(t_plane **p)
{
	free_vector(&(*p)->normal_vect);
	free((*p));
	(*p) = NULL;
}

void	free_cam(t_cam **cam)
{
	free_vector(&(*cam)->position);
	free_vector(&(*cam)->orientation);
	free((*cam));
	(*cam) = NULL; 
}

void	free_light(t_light **l)
{
	t_light	*temp;
	t_light	*cur;

	cur = (*l);
	while (cur)
	{
		temp = cur->next;

		free_vector(&cur->position);
		free_vector(&cur->color);
		free(cur);

		cur = temp;
	}
	(*l) = NULL;
}

void	free_objects(t_objects	**obj)
{
	t_objects	*cur;
	t_objects	*temp;

	cur = (*obj);
	while (cur)
	{
		temp = cur->next;

		free_vector(&(cur->position));
		free_vector(&(cur->color));
		if (cur->type == CIRCLE)
		{
			free_circle(&(cur->circle));
		}
		else if (cur->type == PLANE)
		{
			free_plane(&(cur->plane));
		}
		free(cur);

		cur = temp;
	}
	(*obj) = NULL;
}

void	free_ambient(t_ambient **a)
{
	free_vector(&(*a)->color);
	free(*a);
	(*a) = NULL;
}