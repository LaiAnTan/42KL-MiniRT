/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:20:07 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/03 21:31:26 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

t_ambient	*scene_new_ambient(double a_rgb[3], double a_ratio)
{
	t_ambient	*new_ambient;

	new_ambient = (t_ambient *) malloc(sizeof(t_ambient));
	new_ambient->a_ratio = a_ratio;
	if (a_rgb)
		new_ambient->a_rgb = vec3_init_from_array(a_rgb);
	else
		new_ambient->a_rgb = vec3_init(0,0,0);
	new_ambient->a_strength = vec3_scalar_multi(new_ambient->a_rgb,
			(double) 1 / 255, O_CREATE);
	vec3_scalar_multi(new_ambient->a_strength, a_ratio, O_REPLACE);
	new_ambient->bg_color = vec3_multi_each_elem(vec3_init(255, 255, 255),
			new_ambient->a_strength, O_REPLACE);
	return (new_ambient);
}

t_camera	*scene_new_camera(double cam_fov, double cam_coords[3],
		double cam_vec_orient[3])
{
	t_camera	*new_camera;

	new_camera = (t_camera *) malloc(sizeof(t_camera));
	new_camera->cam_fov = cam_fov;
	new_camera->cam_coords = vec3_init_from_array(cam_coords);
	new_camera->cam_vec_orient = vec3_normalize(
			vec3_init_from_array(cam_vec_orient), O_REPLACE);
	new_camera->cam_coords_v4 = NULL;
	new_camera->cam_vec_orient_v4 = NULL;
	new_camera->orr_matrix = NULL;
	new_camera->view_matrix = NULL;
	new_camera->next = NULL;
	return (new_camera);
}

t_light	*scene_new_light(double l_rgb[3], double l_coords[3],
		double l_brightness)
{
	t_light		*new_light;

	new_light = (t_light *) malloc(sizeof(t_light));
	new_light->l_rgb = vec3_init_from_array(l_rgb);
	new_light->l_coords = vec3_init_from_array(l_coords);
	new_light->l_brightness = l_brightness;
	new_light->next = NULL;
	return (new_light);
}

void	scene_camera_add_back(t_camera **list_camera, t_camera *new_camera)
{
	t_camera	*curr_node;

	if (!new_camera)
		return ;
	if (!*list_camera)
	{
		*list_camera = new_camera;
		return ;
	}
	curr_node = *list_camera;
	while (curr_node->next != NULL)
		curr_node = curr_node->next;
	curr_node->next = new_camera;
}

void	scene_light_add_back(t_light **list_light, t_light *new_light)
{
	t_light	*curr_node;

	if (!new_light)
		return ;
	if (!*list_light)
	{
		*list_light = new_light;
		return ;
	}
	curr_node = *list_light;
	while (curr_node->next != NULL)
		curr_node = curr_node->next;
	curr_node->next = new_light;
}
