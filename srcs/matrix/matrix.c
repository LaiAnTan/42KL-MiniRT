/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:03 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:38:33 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/matrix.h"

t_matrix	*m_init(t_matrix_type *values, int x, int y)
{
	int			i;
	int			j;
	t_matrix	*ret;

	ret = malloc(sizeof(t_matrix));
	ret->x = x;
	ret->y = y;
	j = 0;
	ret->m = malloc(sizeof(t_matrix_type *) * y);
	while (j < ret->y)
	{
		i = 0;
		ret->m[j] = malloc(sizeof(t_matrix_type) * x);
		while (i < ret->x)
		{
			ret->m[j][i] = values[(j * ret->x) + i];
			++i;
		}
		++j;
	}
	return (ret);
}

t_matrix	*m_init_empty(int x, int y)
{
	int			i;
	int			j;
	t_matrix	*ret;

	ret = malloc(sizeof(t_matrix));
	ret->x = x;
	ret->y = y;
	j = 0;
	ret->m = malloc(sizeof(t_matrix_type *) * y);
	while (j < y)
	{
		i = 0;
		ret->m[j] = malloc(sizeof(t_matrix_type) * x);
		while (i < x)
		{
			ret->m[j][i] = 0;
			++i;
		}
		++j;
	}
	return (ret);
}

t_matrix	*m_init_identity(int x, int y)
{
	int			i;
	t_matrix	*ret;

	i = 0;
	ret = m_init_empty(x, y);
	while (i < x)
	{
		ret->m[i][i] = 1;
		++i;
	}
	return (ret);
}

t_matrix	*m_dup(t_matrix *source)
{
	t_matrix		*ret;
	t_matrix_type	*temp;

	temp = m_convert_to_1d(source);
	ret = m_init(temp, source->x, source->y);
	free(temp);
	return (ret);
}

t_matrix	*m_dup_emptymatrix(t_matrix *source)
{
	return (m_init_empty(source->x, source->y));
}
