/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:25:05 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:03:12 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/matrix.h"

t_matrix_type	*m_convert_to_1d(t_matrix *source)
{
	int			i;
	int			j;
	t_matrix_type	*ret;

	ret = malloc(sizeof(t_matrix_type) * (source->x * source->y));
	j = 0;
	while (j < source->y)
	{
		i = 0;
		while (i < source->x)
		{
			ret[(j * source->x) + i] = source->m[j][i];
			++i;
		}
		++j;
	}
	return (ret);
}

t_matrix	*m_addition(t_matrix *left, t_matrix *right)
{
	int			x;
	int			y;
	t_matrix	*ret;

	if (left->x != right->x || left->y != right->y)
		return (NULL);
	ret = m_dup_emptymatrix(left);
	y = 0;
	while (y < left->y)
	{
		x = 0;
		while (x < left->x)
		{
			ret->m[y][x] = left->m[y][x] + right->m[y][x];
			++x;
		}
		++y;
	}
	return (ret);
}

t_matrix	*m_subtraction(t_matrix *left, t_matrix *right)
{
	int			x;
	int			y;
	t_matrix	*ret;

	if (left->x != right->x || left->y != right->y)
		return (NULL);
	ret = m_dup_emptymatrix(left);
	y = 0;
	while (y < left->y)
	{
		x = 0;
		while (x < left->x)
		{
			ret->m[y][x] = left->m[y][x] - right->m[y][x];
			++x;
		}
		++y;
	}
	return (ret);
}

static	t_matrix_type	line_multiplication(t_matrix *left, t_matrix *right,
		int x, int y)
{
	int			x1;
	int			y1;
	t_matrix_type	ret;

	ret = 0;
	x1 = 0;
	y1 = 0;
	while (x1 < left->x && y1 < right->y)
	{
		ret += left->m[y][x1] * right->m[y1][x];
		++x1;
		++y1;
	}
	return (ret);
}

t_matrix	*m_multiplication(t_matrix *left, t_matrix *right)
{
	int			x;
	int			y;
	t_matrix	*ret;

	if (left->x != right->y)
		return (NULL);
	ret = m_init_empty(right->x, left->y);
	y = 0;
	while (y < ret->y)
	{
		x = 0;
		while (x < ret->x)
		{
			ret->m[y][x] = line_multiplication(left, right, x, y);
			++x;
		}
		++y;
	}
	return (ret);
}
