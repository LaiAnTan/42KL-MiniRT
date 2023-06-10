#include "ray.h"

// malloc both vectors thanks
t_ray	*init_ray(t_vector	*pos_vector, t_vector *dir_vector)
{
	// white light baby
	matrix_type	color[3] = {255,255,255};
	t_ray		*ret;

	ret = malloc(sizeof(t_ray));
	ret->pos_vector = pos_vector;
	ret->dir_vector = dir_vector;
	ret->color = init_vector_intarr(color);
	ret->type = LIGHT;

	return (ret);
}

t_ray	*dup_ray(t_ray *source)
{
	t_ray	*ret;

	ret = init_ray(dup_vct(source->pos_vector), dup_vct(source->dir_vector));
	ret->type = source->type;
	return (ret);
}

void	free_ray(t_ray **ray)
{
	free_vector(&(*ray)->pos_vector);
	free_vector(&(*ray)->dir_vector);
	free_vector(&(*ray)->color);
	free((*ray));
	*ray = NULL;
}