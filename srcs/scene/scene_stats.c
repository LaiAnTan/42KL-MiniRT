/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_stats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:08:11 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/03 22:03:30 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	scene_print_cylinder_stats(t_cylinder *cylinder)
{
	printf("cy_vec_axis = ");
	vec3_print(cylinder->cy_vec_axis);
	printf("cy_diameter = %.2f\n", cylinder->cy_diameter);
	printf("cy_height = %.2f\n", cylinder->cy_height);
	if (cylinder->cy_bottom)
	{
		printf("cy_bottom_center_point = ");
		vec3_print(cylinder->cy_bottom);
	}
}

void	scene_print_cone_stats(t_cone *cone)
{
	printf("cn_vec_axis = ");
	vec3_print(cone->cn_vec_axis);
	printf("cn_diameter = %.2f\n", cone->cn_diameter);
	printf("cn_height = %.2f\n", cone->cn_height);
	if (cone->cn_bottom)
	{
		printf("cn_bottom_center_point = ");
		vec3_print(cone->cn_bottom);
	}
}

void	scene_print_object_stats(t_object *obj)
{
	printf("obj_coord =");
	vec3_print(obj->ob_coords);
	printf("obj_rgb =");
	vec3_print(obj->ob_rgb);
	printf("obj_specular = %.2f\n", obj->ob_spec);
	printf("obj_texture_filename = %s\n", obj->has_texture);
	printf("obj_type = %d\n", obj->ob_type);
	if (obj->ob_cylinders)
		scene_print_cylinder_stats(obj->ob_cylinders);
	if (obj->ob_planes)
		scene_print_plane_stats(obj->ob_planes);
	if (obj->ob_spheres)
		scene_print_sphere_stats(obj->ob_spheres);
	if (obj->ob_cones)
		scene_print_cone_stats(obj->ob_cones);
}

static void	scene_print_stats_helper(t_camera *curr_camera, t_light *curr_light,
			t_object *curr_object)
{
	while (curr_camera != NULL)
	{
		printf("\nCamera: %p\n", curr_camera);
		scene_print_camera_stats(curr_camera);
		curr_camera = curr_camera->next;
	}
	while (curr_light != NULL)
	{
		printf("\nLight: %p\n", curr_light);
		scene_print_light_stats(curr_light);
		curr_light = curr_light->next;
	}
	while (curr_object != NULL)
	{
		printf("\nObject: %p\n", curr_object);
		scene_print_object_stats(curr_object);
		curr_object = curr_object->next;
	}
}

void	scene_print_stats(t_scene *scene)
{
	t_camera	*curr_camera;
	t_light		*curr_light;
	t_object	*curr_object;

	curr_camera = scene->sc_cameras;
	curr_light = scene->sc_lights;
	curr_object = scene->sc_objs;
	printf("\n--- Stats ---\n");
	printf("\nAmbient: %p\n", scene->sc_ambients);
	scene_print_ambient_stats(scene->sc_ambients);
	scene_print_stats_helper(curr_camera, curr_light, curr_object);
	printf("\n--- Stats End ---\n");
}
