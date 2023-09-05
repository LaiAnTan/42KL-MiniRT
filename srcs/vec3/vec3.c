/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:42:22 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:03:12 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vec3.h"

t_vec3	*vec3_init(double x, double y, double z)
{
	t_vec3	*ret;

	ret = malloc(sizeof(t_vec3));
	ret->raw_matrix = m_init_empty(1, 3);
	ret->raw_matrix->m[0][0] = x;
	ret->raw_matrix->m[1][0] = y;
	ret->raw_matrix->m[2][0] = z;
	return (ret);
}

t_vec3	*vec3_init_from_matrix(t_matrix *stuff)
{
	t_vec3	*ret;

	if (!stuff)
		return (NULL);
	ret = malloc (sizeof(t_vec3));
	ret->raw_matrix = stuff;
	return (ret);
}

t_vec3	*vec3_init_from_array(t_matrix_type array[3])
{
	t_vec3	*ret;

	ret = malloc (sizeof(t_vec3));
	ret->raw_matrix = m_init(array, 1, 3);
	return (ret);
}

t_vec3	*vec3_dup(t_vec3 *vctr)
{
	t_vec3	*ret;

	ret = malloc(sizeof(t_vec3));
	ret->raw_matrix = m_dup(vctr->raw_matrix);
	return (ret);
}
