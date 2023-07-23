/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:42:47 by tlai-an           #+#    #+#             */
/*   Updated: 2023/07/23 11:42:48 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minirt.h"

double	intersect_plane(t_ray *ray, t_object *o)
{
	t_vec3	*modified_ray_pos;

	modified_ray_pos = vec3_difference(ray->pos_vector, o->ob_coords, O_CREATE);

	// ipad notes... again
	// a = -k(b)
	double	values[2];
	double	k;

	values[0] = vec3_dotproduct(modified_ray_pos, o->ob_planes->pl_vec_normal);
	values[1] = vec3_dotproduct(ray->dir_vector, o->ob_planes->pl_vec_normal);
	vec3_free(&modified_ray_pos);

	k = - (values[0] / values[1]);
	if (k < 0)
		return (ERROR);
	return (k);
}