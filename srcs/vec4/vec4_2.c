/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 13:54:41 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:03:12 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vec4.h"

t_matrix_type	*vec4_to_array(t_vec4 *vector)
{
	t_matrix_type	*array;

	array = malloc(4 * sizeof(t_matrix_type));
	array[0] = vector->raw_matrix->m[0][0];
	array[1] = vector->raw_matrix->m[1][0];
	array[2] = vector->raw_matrix->m[2][0];
	array[3] = vector->raw_matrix->m[3][0];
	return (array);
}

void	vec4_free(t_vec4 **vector)
{
	if (!(*vector))
		return ;
	free_matrix(&(*vector)->raw_matrix);
	free((*vector));
	*vector = NULL;
}

void	vec4_print(t_vec4 *vector)
{
	t_matrix	*matrix;

	matrix = vector->raw_matrix;
	printf("[ %.2f, %.2f, %.2f, %.2f ]\n",
		matrix->m[0][0],
		matrix->m[1][0],
		matrix->m[2][0],
		matrix->m[3][0]);
}

t_vec4	*vec3_to_vec4(t_vec3 *vector)
{
	return (vec4_init(vector->raw_matrix->m[0][0],
		vector->raw_matrix->m[1][0], vector->raw_matrix->m[2][0], 1));
}

t_vec3	*vec4_to_vec3(t_vec4 *vector)
{
	return (vec3_init(vector->raw_matrix->m[0][0],
		vector->raw_matrix->m[1][0], vector->raw_matrix->m[2][0]));
}
