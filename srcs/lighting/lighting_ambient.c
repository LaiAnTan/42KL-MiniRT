/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_ambient.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:39:52 by tlai-an           #+#    #+#             */
/*   Updated: 2023/07/23 13:40:13 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lighting.h"

void	ambient_color(t_ray	*ray, t_ambient *a, t_object *o)
{
	vec3_free(&ray->a_color);
	if (o)
		ray->a_color = vec3_multi_each_elem(o->ob_rgb, a->a_strength, O_CREATE);
	else
		ray->a_color = vec3_dup(a->bg_color);
}
