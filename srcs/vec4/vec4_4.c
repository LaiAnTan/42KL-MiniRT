/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 13:56:01 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/01 23:46:34 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vec4.h"

t_vec4	*vec4_diff(t_vec4 *left_vec3, t_vec4 *right_vec3)
{
	return (vec4_init_from_matrix(
			m_subtraction(left_vec3->raw_matrix, right_vec3->raw_matrix)));
}

t_vec4	*vec4_add(t_vec4 *left_vec3, t_vec4 *right_vec3)
{
	return (vec4_init_from_matrix(
			m_addition(left_vec3->raw_matrix, right_vec3->raw_matrix)));
}

t_vec4	*vec4_scalar_mult(t_vec4 *vector, double scalar)
{
	return (vec4_init_from_matrix(m_scalar_multi(vector->raw_matrix, scalar)));
}

t_vec4	*vec4_normalize(t_vec4 *vector)
{
	double	mag;

	mag = vec4_magnitude(vector);
	return (vec4_scalar_mult(vector, 1 / mag));
}
