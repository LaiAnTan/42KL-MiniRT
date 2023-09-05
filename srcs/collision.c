/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:42 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/03 21:39:54 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

/*
// value[0] -> store closest object distance
// value[1] -> stores return value of intersect_checker
*/
t_object	*get_closest_object(t_ray *ray, t_object *o, int closest,
		double	*k_val)
{
	t_object	*closest_object_src;
	double		values[2];

	values[0] = INFINITY;
	closest_object_src = NULL;
	while (o)
	{
		values[1] = o->intersect_checker(ray, o);
		if (values[1] != ERROR)
		{
			if (!closest)
			{
				*k_val = values[1];
				return (o);
			}
			if (values[1] < values[0])
			{
				values[0] = values[1];
				closest_object_src = o;
			}
		}
		o = o->next;
	}
	*k_val = values[0];
	return (closest_object_src);
}

int	get_closest_light(t_ray *to_light, double exceed_k, t_object *o)
{
	double		save;
	t_object	*collided_obj;

	collided_obj = get_closest_object(to_light, o, 0, &save);
	if (collided_obj == NULL)
		return (SUCCESS);
	else
	{
		if ((save * save) > exceed_k)
		{
			if (!o->next)
				return (SUCCESS);
			return (get_closest_light(to_light, exceed_k, o->next));
		}
		return (ERROR);
	}
}

// setup and run get_closest_light
int	get_closest_light_runner(t_ray *r, t_light *l, t_object *o)
{
	double		ret;
	double		precision;
	t_vec3		*r_to_l;
	t_ray		*to_light;

	precision = 0.1f;
	r_to_l = vec3_difference(l->l_coords, r->pos_vector, O_CREATE);
	to_light = init_ray(vec3_dup(r->pos_vector), vec3_normalize(r_to_l,
				O_CREATE));
	move_ray(to_light, precision);
	ret = get_closest_light(to_light, vec3_magnitude_sqrd(r_to_l), o);
	free_ray(&to_light);
	vec3_free(&r_to_l);
	return (ret);
}
