#include "ray.h"

// malloc both vectors thanks
t_ray	*init_ray(t_vector	*pos_vector, t_vector *dir_vector)
{
	// black light baby
	t_matrix_type	color[3] = {0,0,0};
	t_ray		*ret;

	ret = malloc(sizeof(t_ray));
	ret->pos_vector = pos_vector;
	ret->dir_vector = dir_vector;
	ret->color = init_vector_intarr(color);
	ret->a_color = init_vector_intarr(color);
	ret->d_color = init_vector_intarr(color);
	ret->s_color = init_vector_intarr(color);
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

// moves the ray to the direction of ray->dir_vector based on the k value given
void	move_ray(t_ray *ray, double k)
{
	t_vector	*store;
	t_vector	*new;

	store = v_scalar_multi(ray->dir_vector, k);
	new = v_addition(ray->pos_vector, store);
	free_vector(&store);
	free_vector(&ray->pos_vector);
	ray->pos_vector = new;
}

void	free_ray(t_ray **ray)
{
	free_vector(&(*ray)->pos_vector);
	free_vector(&(*ray)->dir_vector);
	free_vector(&(*ray)->color);
	free_vector(&(*ray)->a_color);
	free_vector(&(*ray)->d_color);
	free_vector(&(*ray)->s_color);
	free((*ray));
	*ray = NULL;
}
