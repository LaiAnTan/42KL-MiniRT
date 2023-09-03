/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:42:32 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/03 21:28:25 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

static void	assign_function(t_object *new_object, int ob_type)
{
	object_runner	store[4];

	store[0] = intersect_circle;
	store[1] = intersect_plane;
	store[2] = intersect_cylinder;
	store[3] = intersect_cone;
	new_object->intersect_checker = store[ob_type];
}

t_object	*scene_new_object(int ob_type, matrix_type *ob_coord,
		matrix_type *ob_rgb, double specular, char *ob_tex_filename)
{
	t_object	*new_object;

	new_object = object_init();
	new_object->ob_type = ob_type;
	assign_function(new_object, ob_type);
	new_object->ob_coords = vec3_init_from_array(ob_coord);
	new_object->ob_rgb = vec3_init_from_array(ob_rgb);
	new_object->ob_spec = specular;
	if (ft_strcmp(ob_tex_filename, "none") != 0)
		new_object->has_texture = ft_strdup(ob_tex_filename);
	else
		new_object->has_texture = NULL;
	return (new_object);
}

void	scene_object_add_back(t_object **list_object, t_object *new_object)
{
	t_object	*curr_node;

	if (!new_object)
		return ;
	if (!*list_object)
	{
		*list_object = new_object;
		return ;
	}
	curr_node = *list_object;
	while (curr_node->next != NULL)
		curr_node = curr_node->next;
	curr_node->next = new_object;
}

t_object	*object_init(void)
{
	t_object	*object;

	object = (t_object *) malloc(sizeof(t_object));
	object->ob_type = -1;
	object->ob_coords = NULL;
	object->ob_rgb = NULL;
	object->ob_spec = -1;
	object->ob_cylinders = NULL;
	object->ob_planes = NULL;
	object->ob_spheres = NULL;
	object->ob_cones = NULL;
	object->next = NULL;
	object->has_texture = NULL;
	object->ob_texture = NULL;
	return (object);
}
