/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:49 by tlai-an           #+#    #+#             */
/*   Updated: 2023/08/19 20:07:56 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

/*
result[0] = determinant
result[1] = +sqrt ans
result[2] = -sqrt ans
*/

// a slightly faster intercept circle finder
void	solve_quad(double *coefficients, double *result)
{
	double	b;
	double	c;
	double	d;

	b = coefficients[1];
	c = coefficients[2];
	result[0] = (b * b) - (c);
	if (result[0] < 0)
		return ;
	d = sqrt(result[0]);
	result[1] = (-1 * b) + d;
	result[2] = (-1 * b) - d;
}

// ax^2 + bx + c
double	intersect_circle(t_ray *ray, t_object *o)
{
	double	values[3];
	double	coefficients[3];
	t_vec3	*modified_ray_pos;

	modified_ray_pos = vec3_difference(ray->pos_vector, o->ob_coords, O_CREATE);
	coefficients[0] = 1;
	coefficients[1] = vec3_dotproduct(modified_ray_pos, ray->dir_vector);
	coefficients[2] = vec3_magnitude_sqrd(modified_ray_pos)
		- (o->ob_spheres->sp_radius * o->ob_spheres->sp_radius);
	vec3_free(&modified_ray_pos);
	solve_quad(coefficients, values);
	if (values[0] < 0)
		return (ERROR);
	if (values[1] < 0 && values[2] < 0)
		return (ERROR);
	values[0] = fmin(values[1], values[2]);
	if (values[0] < 0)
		values[0] = fmax(values[1], values[2]);
	return (values[0]);
}
