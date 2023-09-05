/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:42:17 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:03:12 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vec4.h"

t_vec4	*vec4_init(double x, double y, double z, double w)
{
	t_vec4	*ret;

	ret = malloc(sizeof(t_vec4));
	ret->raw_matrix = m_init_empty(1, 4);
	ret->raw_matrix->m[0][0] = x;
	ret->raw_matrix->m[1][0] = y;
	ret->raw_matrix->m[2][0] = z;
	ret->raw_matrix->m[3][0] = w;
	return (ret);
}

t_vec4	*vec4_init_from_matrix(t_matrix *matrix)
{
	t_vec4	*ret;

	if (!matrix)
		return (NULL);
	ret = (t_vec4 *) malloc(sizeof(t_vec4));
	ret->raw_matrix = matrix;
	return (ret);
}

t_vec4	*vec4_init_from_array(t_matrix_type array[4])
{
	t_vec4	*ret;

	ret = (t_vec4 *) malloc(sizeof(t_vec4));
	ret->raw_matrix = m_init(array, 1, 4);
	return (ret);
}

// arr[3] = w
t_vec4	*vec_4_init_from_coordinates(t_matrix_type coordinates[3])
{
	double	*arr;

	arr = (double *) malloc(sizeof(double) * 4);
	arr[0] = coordinates[0];
	arr[1] = coordinates[1];
	arr[2] = coordinates[2];
	arr[3] = 1;
	return (vec4_init_from_array(arr));
}

t_vec4	*vec4_dup(t_vec4 *vector)
{
	t_vec4	*ret;

	ret = (t_vec4 *) malloc(sizeof(t_vec4));
	ret->raw_matrix = m_dup(vector->raw_matrix);
	return (ret);
}
