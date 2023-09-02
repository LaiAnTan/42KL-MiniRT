/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:33 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/02 10:28:56 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

// when used, r is already at intersection point
// answer stored inside modified_ray
t_vec3	*calc_cylinder_norm(t_ray *r, t_object *o)
{
	t_vec3	*modified_ray;
	t_vec3	*proj_ray;

	modified_ray = vec3_difference(r->pos_vector, o->ob_cylinders->cy_bottom,
			O_CREATE);
	proj_ray = vec3_projection(modified_ray, o->ob_cylinders->cy_vec_axis,
			O_CREATE);
	vec3_normalize(vec3_difference(modified_ray, proj_ray, O_REPLACE),
		O_REPLACE);
	vec3_free(&proj_ray);
	if (r->inside == 0)
		return (modified_ray);
	else
		return (vec3_negate(modified_ray));
}

void	solve_quad_cy(double *coefficients, double *result)
{
	double	a;
	double	b;
	double	c;
	double	d;

	a = coefficients[0];
	b = coefficients[1];
	c = coefficients[2];
	result[0] = (b * b) - (a * c);
	if (result[0] < 0)
		return ;
	d = sqrt(result[0]);
	result[1] = ((-1 * b) + d) / (a);
	result[2] = ((-1 * b) - d) / (a);
}

// calculates ray position relative to cylinder's bottom cap position
static double	calc_intersect(t_ray *ray, t_object *o, double value)
{
	double	k;
	t_vec3	*ray_mover;
	t_vec3	*ray_intersection;

	ray_mover = vec3_scalar_multi(ray->dir_vector, value, O_CREATE);
	ray_intersection = vec3_addition(ray->pos_vector, ray_mover, O_CREATE);
	k = vec3_dotproduct(vec3_difference(ray_intersection,
				o->ob_cylinders->cy_bottom, O_REPLACE),
			o->ob_cylinders->cy_vec_axis);
	vec3_free(&ray_mover);
	vec3_free(&ray_intersection);
	return (k);
}

// if k lies between 0 and cy_height => intersected
double	cy_test_intersect(t_ray *ray, t_object *o, double value[2])
{
	int		i;
	double	k;

	if (value[0] > value[1])
		swap(&value[0], &value[1]);
	i = -1;
	while (++i < 2)
	{
		if (value[i] < 0)
			continue ;
		k = calc_intersect(ray, o, value[i]);
		if (k >= 0 && k <= o->ob_cylinders->cy_height)
		{
			if (i == 1)
				ray->inside = 1;
			return (value[i]);
		}
	}
	return (ERROR);
}

double	intersect_cylinder(t_ray *ray, t_object *o)
{
	double	r;
	double	values[3];
	double	coefficients[3];
	t_vec3	*w;

	r = o->ob_cylinders->cy_diameter / 2;
	w = vec3_difference(ray->pos_vector, o->ob_cylinders->cy_bottom, O_CREATE);
	coefficients[0] = 1 - (vec3_dotproduct(ray->dir_vector,
				o->ob_cylinders->cy_vec_axis) * vec3_dotproduct(ray->dir_vector,
				o->ob_cylinders->cy_vec_axis));
	coefficients[1] = (vec3_dotproduct(ray->dir_vector,
				w) - vec3_dotproduct(ray->dir_vector,
				o->ob_cylinders->cy_vec_axis) * vec3_dotproduct(w,
				o->ob_cylinders->cy_vec_axis));
	coefficients[2] = vec3_dotproduct(w, w) - (vec3_dotproduct(w,
				o->ob_cylinders->cy_vec_axis) * vec3_dotproduct(w,
				o->ob_cylinders->cy_vec_axis)) - (r * r);
	vec3_free(&w);
	solve_quad_cy(coefficients, values);
	if (values[0] < 0)
		return (ERROR);
	if (values[1] < 0 && values[2] < 0)
		return (ERROR);
	return (cy_test_intersect(ray, o, &values[1]));
}
