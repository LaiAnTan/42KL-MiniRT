/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 13:41:15 by tlai-an           #+#    #+#             */
/*   Updated: 2023/08/20 13:42:57 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vec3.h"

// we gonna happily assume its i, j, k (so perpendicular, so cancel each other out)
double	vec3_dotproduct(t_vec3 *left, t_vec3 *right)
{
	t_matrix	*left_m;
	t_matrix	*right_m;

	left_m = left->raw_matrix;
	right_m = right->raw_matrix;

	// epic hard code
	return (
		(left_m->m[0][0] * right_m->m[0][0]) +
		(left_m->m[1][0] * right_m->m[1][0]) +
		(left_m->m[2][0] * right_m->m[2][0]) 
	);
}

// oh WE ARE DEFINATELY OPTIMIZING THIS LATER
double	vec3_magnitude(t_vec3 *vctr)
{
	double	x;
	double	y;
	double	z;

	x = vctr->raw_matrix->m[0][0];
	y = vctr->raw_matrix->m[1][0];
	z = vctr->raw_matrix->m[2][0];
	return (sqrt((x * x) + (y * y) + (z * z)));
}

// magnitude, but not square-rooted
double	vec3_magnitude_sqrd(t_vec3 *vctr)
{
	double	x;
	double	y;
	double	z;

	x = vctr->raw_matrix->m[0][0];
	y = vctr->raw_matrix->m[1][0];
	z = vctr->raw_matrix->m[2][0];
	return ((x * x) + (y * y) + (z * z));
}

// 0 - angle between ray and x axis
// 1 - angle between ray and y axis
// 2 - angle between ray and z axis
// dont port this to t_vec3 (good luck figuring out angle between the 4th dimension )
double	*vec3_direction_cosines(t_vec3 *vctr)
{
    double	*ret;
    double	mag;

    ret = malloc(sizeof(double) * 3);
    mag = vec3_magnitude(vctr);

    ret[0] = acos(vctr->raw_matrix->m[0][0] / mag);
    ret[1] = acos(vctr->raw_matrix->m[1][0] / mag); 
    ret[2] = acos(vctr->raw_matrix->m[2][0] / mag);
    return (ret);
}


double	*vec3_u_direction_cosines(t_vec3 *vec3_norm)
{
	double	*ret;

	ret = malloc(sizeof(double) * 3);
	ret[0] = acos(vec3_norm->raw_matrix->m[0][0]);
	ret[1] = acos(vec3_norm->raw_matrix->m[1][0]); 
	ret[2] = acos(vec3_norm->raw_matrix->m[2][0]);
	return (ret);
}
