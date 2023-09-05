/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_free_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:17:17 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/03 21:29:43 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	object_free_sphere(t_sphere *sphere)
{
	if (!sphere)
		return ;
	free(sphere);
}

void	object_free_plane(t_plane *plane)
{
	if (!plane)
		return ;
	vec3_free(&plane->pl_vec_normal);
	if (plane->pl_vec_normal_v4)
		vec4_free(&plane->pl_vec_normal_v4);
	free(plane);
}

void	object_free_cylinder(t_cylinder *cylinder)
{
	if (!cylinder)
		return ;
	vec3_free(&cylinder->cy_vec_axis);
	vec3_free(&cylinder->cy_bottom);
	free(cylinder);
}

void	object_free_cone(t_cone *cone)
{
	if (!cone)
		return ;
	vec3_free(&cone->cn_vec_axis);
	vec3_free(&cone->cn_bottom);
	free(cone);
}

void	object_free_node(t_object *obj, void *mlx)
{
	if (!obj)
		return ;
	vec3_free(&obj->ob_coords);
	vec3_free(&obj->ob_rgb);
	object_free_cylinder(obj->ob_cylinders);
	object_free_plane(obj->ob_planes);
	object_free_sphere(obj->ob_spheres);
	object_free_cone(obj->ob_cones);
	if (obj->has_texture)
	{
		free(obj->has_texture);
		free_texture(&obj->ob_texture, mlx);
	}
	free(obj);
}
