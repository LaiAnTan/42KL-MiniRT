/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 13:41:18 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:37:38 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vec3.h"

t_vec3	*vec3_negate(t_vec3 *vctr)
{
	vctr->raw_matrix->m[0][0] = -vctr->raw_matrix->m[0][0];
	vctr->raw_matrix->m[1][0] = -vctr->raw_matrix->m[1][0];
	vctr->raw_matrix->m[2][0] = -vctr->raw_matrix->m[2][0];
	return (vctr);
}

t_vec3	*vec3_addition(t_vec3 *left, t_vec3 *right, t_options op)
{
	int	i;

	i = 0;
	if (op == O_CREATE)
		return (vec3_init_from_matrix(
				m_addition(left->raw_matrix, right->raw_matrix)));
	else if (op == O_REPLACE)
	{
		while (i < 3)
		{
			left->raw_matrix->m[i][0] += right->raw_matrix->m[i][0];
			++i;
		}
		return (left);
	}
	return (NULL);
}

t_vec3	*vec3_difference(t_vec3 *left, t_vec3 *right, t_options op)
{
	int	i;

	i = 0;
	if (op == O_CREATE)
		return (vec3_init_from_matrix(
				m_subtraction(left->raw_matrix, right->raw_matrix)));
	else if (op == O_REPLACE)
	{
		while (i < 3)
		{
			left->raw_matrix->m[i][0] -= right->raw_matrix->m[i][0];
			++i;
		}
		return (left);
	}
	return (NULL);
}

t_vec3	*vec3_scalar_multi(t_vec3 *vctr, double value, t_options op)
{
	int	i;

	i = 0;
	if (op == O_CREATE)
		return (vec3_init_from_matrix(m_scalar_multi(vctr->raw_matrix, value)));
	else if (op == O_REPLACE)
	{
		while (i < 3)
		{
			vctr->raw_matrix->m[i][0] *= value;
			++i;
		}
		return (vctr);
	}
	return (NULL);
}

t_vec3	*vec3_multi_each_elem(t_vec3 *left, t_vec3 *right, t_options op)
{
	t_matrix_type	store[3];
	int				i;

	i = 0;
	while (i < 3)
	{
		store[i] = left->raw_matrix->m[i][0] * right->raw_matrix->m[i][0];
		++i;
	}
	if (op == O_CREATE)
		return (vec3_init_from_array(store));
	i = 0;
	while (i < 3)
	{
		left->raw_matrix->m[i][0] = store[i];
		++i;
	}
	return (left);
}
