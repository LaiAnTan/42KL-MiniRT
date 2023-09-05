/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_specular.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:40:02 by tlai-an           #+#    #+#             */
/*   Updated: 2023/07/23 13:40:08 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lighting.h"

// takes in a light-to-object vector and its normal and reflects it
static t_vec3	*reflect_light(t_vec3 *light, t_vec3 *normal)
{
	t_vec3	*v;

	v = vec3_scalar_multi(normal, (2 * vec3_dotproduct(light, normal)),
			O_CREATE);
	vec3_difference(v, light, O_REPLACE);
	return (v);
}

// original

// void	calculate_specular_color(t_ray *r, t_light *l, t_object *o,
// 			t_vec3 *light, t_vec3 *normal)
// {
// 	double	dot_vr;
// 	double	specular_exponent;
// 	double	ks;
// 	t_vec3	*s_c;
// 	t_vec3	*dir;
// 	t_vec3	*reflect;
// 	t_vec3	*spec_col;

// 	if (o->ob_spec <= 0)
// 		return ;
// 	specular_exponent = o->ob_spec;
// 	ks = 0.24f * log(0.14f * o->ob_spec) + 0.6f;
// 	reflect = reflect_light(light, normal);
// 	dir = vec3_dup(r->dir_vector);
// 	vec3_negate(dir);
// 	dot_vr = vec3_dotproduct(reflect, dir);
// 	if (dot_vr < 0)
// 	{
// 		vec3_free(&reflect);
// 		vec3_free(&dir);
// 		return ;
// 	}
// 	spec_col = vec3_scalar_multi(l->l_rgb,
// 			pow(dot_vr, specular_exponent), O_CREATE);
// 	s_c = vec3_scalar_multi(spec_col, ks, O_CREATE);
// 	vec3_addition(r->s_color, s_c, O_REPLACE);
// 	vec3_free(&s_c);
// 	vec3_free(&dir);
// 	vec3_free(&reflect);
// 	vec3_free(&spec_col);
// }

// specular color

double	calc_angle_ray_n_reflected(t_vec3 *to_light_dir,
		t_vec3 *normal, t_vec3 *eyes_to_obj_dir)
{
	t_vec3	*dir;
	t_vec3	*reflect;
	double	ret;

	reflect = reflect_light(to_light_dir, normal);
	dir = vec3_negate(vec3_dup(eyes_to_obj_dir));
	ret = vec3_dotproduct(reflect, dir);
	vec3_free(&reflect);
	vec3_free(&dir);
	if (ret < 0)
		return (ERROR);
	return (ret);
}

void	calculate_specular_color(t_ray *r, t_light *l, t_object *o,
			double dot_vr)
{
	double	ks;
	t_vec3	*spec_col;

	if (dot_vr == ERROR)
		return ;
	if (o->ob_spec <= 0)
		return ;
	ks = 0.24f * log(0.14f * o->ob_spec) + 0.6f;
	spec_col = vec3_scalar_multi(l->l_rgb,
			pow(dot_vr, o->ob_spec), O_CREATE);
	vec3_scalar_multi(spec_col, ks, O_REPLACE);
	vec3_addition(r->s_color, spec_col, O_REPLACE);
	vec3_free(&spec_col);
}
