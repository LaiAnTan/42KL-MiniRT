/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_objects_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:21:17 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/03 21:30:31 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

t_sphere	*object_new_sphere(double sp_diameter)
{
	t_sphere	*new_sphere;

	new_sphere = (t_sphere *) malloc(sizeof(t_sphere));
	new_sphere->sp_diameter = sp_diameter;
	new_sphere->sp_radius = sp_diameter / 2;
	return (new_sphere);
}

t_plane	*object_new_plane(double pl_vec_normal[3])
{
	t_plane		*new_plane;

	new_plane = (t_plane *) malloc(sizeof(t_plane));
	new_plane->pl_vec_normal = vec3_normalize(
			vec3_init_from_array(pl_vec_normal), O_REPLACE);
	new_plane->pl_vec_normal_v4 = NULL;
	return (new_plane);
}

t_cylinder	*object_new_cylinder(double cy_height, double cy_diameter,
		double cy_vec_axis[3])
{
	t_cylinder	*new_cylinder;

	new_cylinder = (t_cylinder *) malloc(sizeof(t_cylinder));
	new_cylinder->cy_height = cy_height;
	new_cylinder->cy_diameter = cy_diameter;
	new_cylinder->cy_vec_axis = vec3_normalize(
			vec3_init_from_array(cy_vec_axis), O_REPLACE);
	new_cylinder->cy_bottom = NULL;
	return (new_cylinder);
}

t_cone	*object_new_cone(double cn_height, double cn_diameter,
		double cn_vec_axis[3])
{
	t_cone	*new_cone;

	new_cone = (t_cone *) malloc(sizeof(t_cone));
	new_cone->cn_height = cn_height;
	new_cone->cn_diameter = cn_diameter;
	new_cone->cn_vec_axis = vec3_normalize(
			vec3_init_from_array(cn_vec_axis), O_REPLACE);
	new_cone->cn_bottom = NULL;
	return (new_cone);
}
