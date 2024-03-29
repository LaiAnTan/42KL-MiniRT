/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:42:42 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/02 10:25:03 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ray.h"

// malloc both vectors 
// note that ret->color will only be initialized at calculate_result_color
t_ray	*init_ray(t_vec3 *pos_vector, t_vec3 *dir_vector)
{
	t_ray	*ret;

	ret = malloc(sizeof(t_ray));
	ret->pos_vector = pos_vector;
	ret->dir_vector = dir_vector;
	ret->color = NULL;
	ret->a_color = vec3_init(0, 0, 0);
	ret->d_color = vec3_init(0, 0, 0);
	ret->s_color = vec3_init(0, 0, 0);
	ret->inside = 0;
	return (ret);
}

t_ray	*dup_ray(t_ray *source)
{
	t_ray	*ret;

	ret = init_ray(vec3_dup(source->pos_vector), vec3_dup(source->dir_vector));
	return (ret);
}

// moves the ray to the direction of ray->dir_vector based on the k value given
void	move_ray(t_ray *ray, double k)
{
	t_vec3	*mover;

	mover = vec3_scalar_multi(ray->dir_vector, k, O_CREATE);
	ray->pos_vector = vec3_addition(ray->pos_vector, mover, O_REPLACE);
	vec3_free(&mover);
}

void	free_ray(t_ray **ray)
{
	if (*ray == NULL)
		return ;
	vec3_free(&(*ray)->pos_vector);
	vec3_free(&(*ray)->dir_vector);
	vec3_free(&(*ray)->color);
	vec3_free(&(*ray)->a_color);
	vec3_free(&(*ray)->s_color);
	vec3_free(&(*ray)->d_color);
	free((*ray));
	*ray = NULL;
}
