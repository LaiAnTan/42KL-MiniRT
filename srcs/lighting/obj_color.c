/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:41:52 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:32:52 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	normalize_yourmother(double uv[2])
{
	double	cool_shit;

	cool_shit = sqrt((uv[0] * uv[0]) + (uv[1] * uv[1]));
	uv[0] = uv[0] / cool_shit;
	uv[1] = uv[1] / cool_shit;
}

// x = 0, y = 0, z = 0
void	calculate_uv_circle(t_ray *ray, t_object *o, double store[2])
{
	double	coord[3];
	t_vec3	*zeroed_please_kill_me;

	zeroed_please_kill_me = vec3_difference(ray->pos_vector, o->ob_coords,
			O_CREATE);
	vec3_store_val(vec3_normalize(zeroed_please_kill_me, O_REPLACE), coord);
	vec3_free(&zeroed_please_kill_me);
	store[0] = 0.5 + (atan2(coord[2], coord[0]) / (2 * PI));
	store[1] = 0.5 + (asin(coord[1]) / (PI));
	store[0] = 0.25 - store[0];
	store[1] = 1 - store[1];
}

// only for sphere
// uv_coord: 0, 1 = u, v
t_vec3	*get_object_color(t_ray *ray, t_object *o)
{
	double	uv_coord[2];

	if (!o->has_texture)
	{
		return (vec3_dup(o->ob_rgb));
	}
	else
	{
		if (o->ob_type == CIRCLE)
		{
			calculate_uv_circle(ray, o, uv_coord);
			return (get_rgb(o->ob_texture, uv_coord[0], uv_coord[1]));
		}
	}
	return (NULL);
}
