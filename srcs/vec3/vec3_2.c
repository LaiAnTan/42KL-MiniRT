/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 13:41:11 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:03:12 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vec3.h"

void	vec3_store_val(t_vec3 *vector, t_matrix_type array[3])
{
	array[0] = vector->raw_matrix->m[0][0];
	array[1] = vector->raw_matrix->m[1][0];
	array[2] = vector->raw_matrix->m[2][0];
}

void	vec3_print(t_vec3 *stuff)
{
	t_matrix	*mtrx;

	mtrx = stuff->raw_matrix;
	printf("[ %.2f, %.2f, %.2f ]\n",
		mtrx->m[0][0], mtrx->m[1][0], mtrx->m[2][0]);
}

void	vec3_free(t_vec3 **stuff)
{
	if (!(*stuff))
		return ;
	free_matrix(&(*stuff)->raw_matrix);
	free((*stuff));
	*stuff = NULL;
}

int	vec3_isequal(t_vec3 *a, t_vec3 *b)
{
	return (a->raw_matrix->m[0][0] == b->raw_matrix->m[0][0] &&
	a->raw_matrix->m[1][0] == b->raw_matrix->m[1][0] &&
	a->raw_matrix->m[2][0] == b->raw_matrix->m[2][0]);
}

t_matrix_type	*vec3_get_val(t_vec3 *vector)
{
	t_matrix_type	*array;

	array = malloc(3 * sizeof(t_matrix_type));
	array[0] = vector->raw_matrix->m[0][0];
	array[1] = vector->raw_matrix->m[1][0];
	array[2] = vector->raw_matrix->m[2][0];
	return (array);
}
