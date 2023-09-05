/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:14:58 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/03 21:16:25 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	get_texture_files(t_object *objs, void *mlx_ptr)
{
	while (objs)
	{
		if (objs->has_texture)
		{
			objs->ob_texture = texture_init(ft_strdup(objs->has_texture), mlx_ptr);
			if (!objs->ob_texture)
			{
				free(objs->has_texture);
				objs->has_texture = NULL;
			}
		}
		objs = objs->next;
	}
}

t_scene	*scene_init(void)
{
	t_scene	*new_scene;

	new_scene = (t_scene *) malloc(sizeof(t_scene));
	new_scene->sc_ambients = NULL;
	new_scene->sc_lights = NULL;
	new_scene->sc_objs = NULL;
	new_scene->sc_cameras = NULL;
	return (new_scene);
}
