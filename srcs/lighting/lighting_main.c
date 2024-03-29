/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:16 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:32:48 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

// switcher to calculate b_norm
static t_vec3	*diffuse_lighting_switcher(t_ray *r, t_object *o)
{
	t_vec3	*b_norm;

	b_norm = NULL;
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
// a_norm -> the direction vector of the intersection point to the light
// b_norm -> normal vector of the object
// jesus who named these
void	diffuse_the_bomb(t_ray *r, t_light *l, t_object *o)
{
	t_vec3	*a_norm;
	t_vec3	*b_norm;
	double	costheta;

	a_norm = vec3_normalize(vec3_difference(l->l_coords, r->pos_vector,
				O_CREATE), O_REPLACE);
	b_norm = diffuse_lighting_switcher(r, o);
	costheta = vec3_dotproduct(a_norm, b_norm);
	// HEY small error here
	// dont need to check for plane only, literally if its negative --> opposite side d
	if (costheta < 0)
		costheta *= -1;
	if (costheta >= 0)
	{
		calculate_diffuse_color(r, l, o, costheta);
		calculate_specular_color(r, l, o,
			calc_angle_ray_n_reflected(a_norm, b_norm,
				r->dir_vector));
	}
	vec3_free(&a_norm);
	vec3_free(&b_norm);
}

void	calculate_result_color(t_ray *r)
{
	r->color = vec3_addition(r->a_color, r->d_color, O_CREATE);
	vec3_addition(r->color, r->s_color, O_REPLACE);
}

void	calculate_ray_color(t_ray *ray, t_light *light, t_object *objs,
	t_object *closest)
{
	double		p_from_light;

	while (light)
	{
		p_from_light = get_closest_light_runner(ray, light,
				objs);
		if (p_from_light != ERROR)
			diffuse_the_bomb(ray, light, closest);
		light = light->next;
	}
}
