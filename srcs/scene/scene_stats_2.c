/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_stats_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:04:44 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/03 20:12:03 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	scene_print_ambient_stats(t_ambient *ambient)
{
	printf("a_ratio = %.2f\n", ambient->a_ratio);
	printf("a_rgb = ");
	vec3_print(ambient->a_rgb);
	printf("a_strength = ");
	vec3_print(ambient->a_strength);
}

void	scene_print_camera_stats(t_camera *camera)
{
	printf("cam_coords = ");
	vec3_print(camera->cam_coords);
	printf("cam_vec_orient = ");
	vec3_print(camera->cam_vec_orient);
	printf("cam_fov = %.2f\n", camera->cam_fov);
}

void	scene_print_light_stats(t_light *light)
{
	printf("l_coords = ");
	vec3_print(light->l_coords);
	printf("l_rgb = ");
	vec3_print(light->l_rgb);
	printf("l_brightness = %.2f\n", light->l_brightness);
}

void	scene_print_sphere_stats(t_sphere *sphere)
{
	printf("sp_diameter = %.2f\n", sphere->sp_diameter);
}

void	scene_print_plane_stats(t_plane *plane)
{
	printf("pl_vec_normal = ");
	vec3_print(plane->pl_vec_normal);
}
