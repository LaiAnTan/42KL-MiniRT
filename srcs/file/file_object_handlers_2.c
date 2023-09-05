/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_object_handlers_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:55:21 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 17:29:23 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	handle_object_cylinder(t_scene *scene, char **tokens)
{
	double		*cy_rgb;
	double		*cy_coords;
	double		*cy_vec_axis;
	t_object	*new_object;

	printf("found cylinder object\n");
	if (count_2d_array(tokens) != 7)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[2]) == 0
		|| is_valid_3_values(tokens[5]) == 0)
		return (-1);
	cy_rgb = unpack_3_int_values(tokens[5]);
	cy_coords = unpack_3_double_values(tokens[1]);
	cy_vec_axis = unpack_3_double_values(tokens[2]);
	if (!cy_rgb || !cy_coords || !cy_vec_axis)
		return (-1);
	new_object = scene_new_object(CYLINDER, cy_coords, cy_rgb,
			ft_atof(tokens[6]));
	new_object->ob_cylinders = object_new_cylinder((double) ft_atof(tokens[4]),
			(double) ft_atof(tokens[3]), cy_vec_axis);
	scene_object_add_back(&scene->sc_objs, new_object);
	free(cy_rgb);
	free(cy_coords);
	free(cy_vec_axis);
	return (0);
}

int	handle_object_cone(t_scene *scene, char **tokens)
{
	double		*cn_rgb;
	double		*cn_coords;
	double		*cn_vec_axis;
	t_object	*new_object;

	printf("found cone object\n");
	if (count_2d_array(tokens) != 7)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[2]) == 0
		|| is_valid_3_values(tokens[5]) == 0)
		return (-1);
	cn_rgb = unpack_3_int_values(tokens[5]);
	cn_coords = unpack_3_double_values(tokens[1]);
	cn_vec_axis = unpack_3_double_values(tokens[2]);
	if (!cn_rgb || !cn_coords || !cn_vec_axis)
		return (-1);
	new_object = scene_new_object(CONE, cn_coords, cn_rgb, ft_atof(tokens[6]));
	new_object->ob_cones = object_new_cone((double) ft_atof(tokens[4]),
			(double) ft_atof(tokens[3]), cn_vec_axis);
	scene_object_add_back(&scene->sc_objs, new_object);
	free(cn_rgb);
	free(cn_coords);
	free(cn_vec_axis);
	return (0);
}
