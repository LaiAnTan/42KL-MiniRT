# include "../headers/ray.h"

// malloc both vectors thanks
t_ray	*init_ray(t_vec4 *pos_vector, t_vec4 *dir_vector)
{
	t_ray	*ret;

	ret = malloc(sizeof(t_ray));
	ret->pos_vector = pos_vector;
	ret->dir_vector = dir_vector;
	ret->type = LIGHT;

	return (ret);
}

t_ray	*dup_ray(t_ray *source)
{
	t_ray	*ret;

	ret = init_ray(vec4_dup(source->pos_vector), vec4_dup(source->dir_vector));
	ret->type = source->type;
	return (ret);
}

void	free_ray(t_ray **ray)
{
	vec4_free(&(*ray)->pos_vector);
	vec4_free(&(*ray)->dir_vector);
	free((*ray));
	*ray = NULL;
}