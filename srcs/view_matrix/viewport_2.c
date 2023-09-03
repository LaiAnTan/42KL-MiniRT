/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:54:16 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/03 21:55:33 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

// need a specific center bottom getter
// (since the cylinder axis isnt constantly 0,0,1)
t_vec3	*cyn_get_centre_bottom(t_vec3 *center, t_vec3 *vec_axis, double diff)
{
	t_vec3	*ret;
	t_vec3	*to_min;

	to_min = vec3_scalar_multi(vec_axis, diff, O_CREATE);
	ret = vec3_difference(center, to_min, O_CREATE);
	vec3_free(&to_min);
	return (ret);
}

void	transform_plane(t_plane *pl, t_camera *mrtx)
{
	apply_matrix(&(pl->pl_vec_normal), mrtx->orr_matrix);
	pl->pl_vec_normal = vec3_normalize(pl->pl_vec_normal, O_REPLACE);
}

void	transform_cylinder(t_vec3 *center, t_cylinder *cy, t_camera *mtrx)
{
	apply_matrix(&(cy->cy_vec_axis), mtrx->orr_matrix);
	vec3_normalize(cy->cy_vec_axis, O_REPLACE);
	cy->cy_bottom = cyn_get_centre_bottom(center, cy->cy_vec_axis,
			cy->cy_height / 2);
}

void	transform_cone(t_vec3 *center, t_cone *cn, t_camera *mtrx)
{
	apply_matrix(&(cn->cn_vec_axis), mtrx->orr_matrix);
	vec3_normalize(cn->cn_vec_axis, O_REPLACE);
	cn->cn_bottom = cyn_get_centre_bottom(center, cn->cn_vec_axis,
			cn->cn_height);
}
