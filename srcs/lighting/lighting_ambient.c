/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_ambient.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:39:52 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:32:41 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	ambient_color(t_ray	*ray, t_ambient *a, t_object *o)
{
	t_vec3	*store;

	vec3_free(&ray->a_color);
	if (o)
	{
		store = get_object_color(ray, o);
		ray->a_color = vec3_multi_each_elem(store, a->a_strength, O_REPLACE);
	}
	else
		ray->a_color = vec3_dup(a->bg_color);
}
