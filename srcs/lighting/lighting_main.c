/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:16 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/02 09:58:19 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lighting.h"

// switcher to calculate b_norm
static t_vec3	*diffuse_lighting_switcher(t_ray *r, t_object *o)
{
	t_vec3	*b_norm;

	if (o->ob_type == CIRCLE)
		b_norm = vec3_normalize(vec3_difference(r->pos_vector, o->ob_coords,
					O_CREATE), O_REPLACE);
	else if (o->ob_type == PLANE)
		b_norm = vec3_dup(o->ob_planes->pl_vec_normal);
	else if (o->ob_type == CYLINDER)
		b_norm = calc_cylinder_norm(r, o);
	else if (o->ob_type == CONE)
		b_norm = calc_cone_norm(r, o);
	return (b_norm);
}

// main lighting calc function
void	diffuse_the_bomb(t_ray *r, t_light *l, t_object *o)
{
	t_vec3	*a_norm;
	t_vec3	*b_norm;
	double	costheta;

	a_norm = vec3_normalize(vec3_difference(l->l_coords, r->pos_vector,
				O_CREATE), O_REPLACE);
	b_norm = diffuse_lighting_switcher(r, o);
	costheta = vec3_dotproduct(a_norm, b_norm);
	if (o->ob_type == PLANE && costheta < 0)
		costheta *= -1;
	if (costheta >= 0)
	{
		r->type = COLLIDED;
		calculate_diffuse_color(r, l, o, costheta);
		calculate_specular_color(r, l, o, a_norm, b_norm);
	}
	vec3_free(&a_norm);
	vec3_free(&b_norm);
}

void	calculate_result_color(t_ray *r)
{
	r->color = vec3_addition(r->a_color, r->d_color, O_CREATE);
	vec3_addition(r->color, r->s_color, O_REPLACE);
}
