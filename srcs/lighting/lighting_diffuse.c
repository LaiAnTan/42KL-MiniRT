/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_diffuse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:39:56 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:38:22 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

t_vec3	*inverse_color(t_vec3 *c)
{
	int				i;
	t_matrix_type	i_rgb[3];
	t_matrix_type	c_stuff[3];

	vec3_store_val(c, c_stuff);
	i = 0;
	while (i < 3)
	{
		i_rgb[i] = abs_double(255 - c_stuff[i]);
		++i;
	}
	return (vec3_init_from_array(i_rgb));
}

// a_o_c = absorbed object color
// d_c = object diffuse color
void	calculate_diffuse_color(t_ray *r, t_light *l, t_object *o,
								double costheta)
{
	double	diff_strength;
	t_vec3	*color_on_point;
	t_vec3	*a_o_c;
	t_vec3	*d_c;
	t_vec3	*store;

	color_on_point = get_object_color(r, o);
	diff_strength = DIFFUSE_FACTOR;
	a_o_c = inverse_color(color_on_point);
	vec3_free(&color_on_point);
	store = vec3_difference(l->l_rgb, a_o_c, O_CREATE);
	d_c = vec3_scalar_multi(store, (costheta * diff_strength), O_CREATE);
	vec3_addition(r->d_color, d_c, O_REPLACE);
	vec3_free(&d_c);
	vec3_free(&a_o_c);
	vec3_free(&store);
}
