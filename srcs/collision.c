/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:42 by tlai-an           #+#    #+#             */
/*   Updated: 2023/07/23 13:14:46 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minirt.h"

t_object	*get_closest_object(t_ray *ray, t_object *o, int closest,
		double	*k_val)
{
	t_object	*closest_object_src;
	double		closest_object;
	double		r_to_o;

	closest_object = INFINITY;
	closest_object_src = NULL;
	while (o)
	{
		r_to_o = o->intersect_checker(ray, o);

		if (r_to_o != ERROR)
		{
			if (!closest)
			{
				*k_val = r_to_o;
				return (o);
			}
			if (r_to_o < closest_object)
			{
				closest_object = r_to_o;
				closest_object_src = o;
			}
		}
		o = o->next;
	}
	*k_val = closest_object;
	return (closest_object_src);
}

// for my next magic trick i will use recursion 
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
			// last object
			if (!o->next)
				return (SUCCESS);
			else
				return (get_closest_light(to_light, exceed_k, o->next));
		}
		else
			return (ERROR);
	}
}

// runs get_closest_light
int	get_closest_light_runner(t_ray *r, t_light *l, t_object *o)
{
	double		ret;
	double		precision = 0.1f;
	t_vec3		*r_to_l;
	t_ray		*to_light;

	r_to_l = vec3_difference(l->l_coords, r->pos_vector, O_CREATE);
	to_light = init_ray(vec3_dup(r->pos_vector), vec3_normalize(r_to_l, O_CREATE));
	move_ray(to_light, precision);

	ret = get_closest_light(to_light, vec3_magnitude_sqrd(r_to_l), o);
	free_ray(&to_light);
	return (ret);
}