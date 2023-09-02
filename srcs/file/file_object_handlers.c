/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_object_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:54:34 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/03 00:00:13 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	handle_object_ambient(t_scene *scene, char **tokens)
{
	double			*a_rgb;

	printf("found ambient object\n");
	if (count_2d_array(tokens) != 3)
		return (-1);
	if (is_valid_3_values(tokens[2]) == 0)
		return (-1);
	a_rgb = unpack_3_int_values(tokens[2]);
	if (!a_rgb)
		return (-1);
	scene->sc_ambients = scene_new_ambient(a_rgb, ft_atof(tokens[1]));
	free(a_rgb);
	return (0);
}

int	handle_object_camera(t_scene *scene, char **tokens)
{
	double		*cam_coords;
	double		*cam_vec_orient;
	t_camera	*new_camera;

	printf("found camera object\n");
	if (count_2d_array(tokens) != 4)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[2]) == 0)
		return (-1);
	cam_coords = unpack_3_double_values(tokens[1]);
	cam_vec_orient = unpack_3_double_values(tokens[2]);
	if (!cam_coords || !cam_vec_orient)
		return (-1);
	new_camera = scene_new_camera(ft_atoi(tokens[3]), cam_coords,
			cam_vec_orient);
	scene_camera_add_back(&scene->sc_cameras, new_camera);
	free(cam_coords);
	free(cam_vec_orient);
	return (0);
}

int	handle_object_light(t_scene *scene, char **tokens)
{
	double		*l_rgb;
	double		*l_coords;
	t_light		*new_light;

	printf("found light object\n");
	if (count_2d_array(tokens) != 4)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[3]) == 0)
		return (-1);
	l_rgb = unpack_3_int_values(tokens[3]);
	l_coords = unpack_3_double_values(tokens[1]);
	if (!l_rgb || !l_coords)
		return (-1);
	new_light = scene_new_light(l_rgb, l_coords, atof(tokens[2]));
	scene_light_add_back(&scene->sc_lights, new_light);
	free(l_rgb);
	free(l_coords);
	return (0);
}

int	handle_object_sphere(t_scene *scene, char **tokens)
{
	double		*sp_rgb;
	double		*sp_coords;
	t_object	*new_object;

	printf("found sphere object\n");
	if (count_2d_array(tokens) != 6)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[3]) == 0)
		return (-1);
	sp_rgb = unpack_3_int_values(tokens[3]);
	sp_coords = unpack_3_double_values(tokens[1]);
	if (!sp_rgb || !sp_coords)
		return (-1);
	new_object = scene_new_object(CIRCLE, sp_coords, sp_rgb,
			ft_atof(tokens[4]), tokens[5]);
	new_object->ob_spheres = object_new_sphere((double) ft_atof(tokens[2]));
	scene_object_add_back(&scene->sc_objs, new_object);
	free(sp_rgb);
	free(sp_coords);
	return (0);
}

int	handle_object_plane(t_scene *scene, char **tokens)
{
	double		*pl_rgb;
	double		*pl_coords;
	double		*pl_vec_normal;
	t_object	*new_object;

	printf("found plane object\n");
	if (count_2d_array(tokens) != 5)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[2]) == 0
		|| is_valid_3_values(tokens[3]) == 0)
		return (-1);
	pl_rgb = unpack_3_int_values(tokens[3]);
	pl_coords = unpack_3_double_values(tokens[1]);
	pl_vec_normal = unpack_3_double_values(tokens[2]);
	if (!pl_rgb || !pl_coords || !pl_vec_normal)
		return (-1);
	new_object = scene_new_object(PLANE, pl_coords, pl_rgb,
			ft_atof(tokens[4]), "none");
	new_object->ob_planes = object_new_plane(pl_vec_normal);
	scene_object_add_back(&scene->sc_objs, new_object);
	free(pl_rgb);
	free(pl_coords);
	free(pl_vec_normal);
	return (0);
}
