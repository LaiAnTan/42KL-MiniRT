/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 13:55:14 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/01 23:47:20 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vec4.h"

// does this exist? idk whoop whoop
double	vec4_dotproduct(t_vec4 *left_vec3, t_vec4 *right_vec3)
{
	int			i;
	double		res;
	t_matrix	*left_m;
	t_matrix	*right_m;

	i = 0;
	res = 0;
	left_m = left_vec3->raw_matrix;
	right_m = right_vec3->raw_matrix;
	while (i < 4)
	{
		res += left_m->m[i][0] * right_m->m[i][0];
		++i;
	}
	return (res);
}

double	vec4_magnitude(t_vec4 *vector)
{
	int		i;
	double	res;

	i = 0;
	res = 0;
	while (i < 4)
	{
		res += vector->raw_matrix->m[i][0] * vector->raw_matrix->m[i][0];
		++i;
	}
	return (sqrt(res));
}

double	vec4_magnitude_sqrd(t_vec4 *vector)
{
	int		i;
	double	res;

	i = 0;
	res = 0;
	while (i < 4)
	{
		res += vector->raw_matrix->m[i][0] * vector->raw_matrix->m[i][0];
		++i;
	}
	return (res);
}
