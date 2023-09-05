/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:16:33 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/03 21:28:04 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	scene_free_ambient(t_ambient *ambient)
{
	if (ambient == NULL)
		return ;
	vec3_free(&ambient->a_rgb);
	vec3_free(&ambient->a_strength);
	vec3_free(&ambient->bg_color);
	free(ambient);
}

void	scene_free_camera_list(t_camera *camera_list_head)
{
	t_camera	*temp;
	t_camera	*curr;

	curr = camera_list_head;
	while (curr)
	{
		temp = curr->next;
		vec3_free(&curr->cam_coords);
		vec3_free(&curr->cam_vec_orient);
		vec4_free(&curr->cam_coords_v4);
		vec4_free(&curr->cam_vec_orient_v4);
		free_matrix(&curr->orr_matrix);
		free_matrix(&curr->view_matrix);
		free(curr);
		curr = temp;
	}
}

void	scene_free_light_list(t_light *light_list_head)
{
	t_light	*temp;
	t_light	*curr;

	curr = light_list_head;
	while (curr)
	{
		temp = curr->next;
		vec3_free(&curr->l_rgb);
		vec3_free(&curr->l_coords);
		free(curr);
		curr = temp;
	}
}

void	scene_free_object_list(t_object	*object_list_head, void *mlx_ptr)
{
	t_object	*temp;
	t_object	*curr;

	curr = object_list_head;
	while (curr)
	{
		temp = curr->next;
		object_free_node(curr, mlx_ptr);
		curr = temp;
	}
}

t_scene	*scene_free(t_scene *scene, void *mlx_ptr)
{
	if (!scene)
		return (scene);
	if (scene->sc_ambients)
		scene_free_ambient(scene->sc_ambients);
	if (scene->sc_cameras)
		scene_free_camera_list(scene->sc_cameras);
	if (scene->sc_lights)
		scene_free_light_list(scene->sc_lights);
	if (scene->sc_objs)
		scene_free_object_list(scene->sc_objs, mlx_ptr);
	free(scene);
	return (NULL);
}
