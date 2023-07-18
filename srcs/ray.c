# include "../headers/ray.h"

// malloc both vectors thanks
t_ray	*init_ray(t_vec3 *pos_vector, t_vec3 *dir_vector)
{
	// black light baby
	matrix_type	color[3] = {0,0,0};
	t_ray	*ret;

	ret = malloc(sizeof(t_ray));
	ret->pos_vector = pos_vector;
	ret->dir_vector = dir_vector;
	ret->color = vec3_init_from_array(color);
	ret->a_color = vec3_init_from_array(color);
	ret->d_color = vec3_init_from_array(color);
	ret->s_color = vec3_init_from_array(color);
	ret->type = LIGHT;
	ret->inside = 0;

	return (ret);
}

t_ray	*dup_ray(t_ray *source)
{
	t_ray	*ret;

	ret = init_ray(vec3_dup(source->pos_vector), vec3_dup(source->dir_vector));
	ret->type = source->type;
	return (ret);
}

// moves the ray to the direction of ray->dir_vector based on the k value given
void	move_ray(t_ray *ray, double k)
{
	vec3_scalar_multi(ray->dir_vector, k, O_REPLACE);
	vec3_addition(ray->pos_vector, ray->dir_vector, O_REPLACE);
}

void	free_ray(t_ray **ray)
{
	vec3_free(&(*ray)->pos_vector);
	vec3_free(&(*ray)->dir_vector);
	vec3_free(&(*ray)->color);
	vec3_free(&(*ray)->a_color);
	vec3_free(&(*ray)->s_color);
	vec3_free(&(*ray)->d_color);
	free((*ray));
	*ray = NULL;
}