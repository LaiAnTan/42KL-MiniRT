/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:26:50 by tlai-an           #+#    #+#             */
/*   Updated: 2023/08/20 12:30:45 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/matrix.h"

t_matrix	*m_scalar_multi(t_matrix *left, double val)
{
	int			x;
	int			y;
	t_matrix	*ret;

	ret = m_dup_emptymatrix(left);
	y = 0;
	while (y < left->y)
	{
		x = 0;
		while (x < left->x)
		{
			ret->m[y][x] = left->m[y][x] * val;
			++x;
		}
		++y;
	}
	return (ret);
}

t_matrix	*m_scalar_divide(t_matrix *left, double val)
{
	return (m_scalar_multi(left, 1 / val));
}

t_matrix	*m_transpose(t_matrix *m)
{
	int			x;
	int			y;
	t_matrix	*ret;

	ret = malloc(sizeof(t_matrix));
	ret->x = m->y;
	ret->y = m->x;
	y = 0;
	ret->m = malloc(sizeof(matrix_type *) * (ret->y));
	while (y < ret->y)
	{
		x = 0;
		ret->m[y] = malloc(sizeof(matrix_type) * (ret->x));
		while (x < ret->x)
		{
			ret->m[y][x] = m->m[x][y];
			++x;
		}
		++y;
	}
	return (ret);
}

void	free_matrix(t_matrix **t_free)
{
	int	y;

	y = 0;
	if ((*t_free) == NULL)
		return ;
	while (y < (*t_free)->y)
	{
		free((*t_free)->m[y]);
		++y;
	}
	free((*t_free)->m);
	free((*t_free));
}

// debug
void	m_print_matrix(t_matrix *m)
{
	int	x;
	int	y;

	y = 0;
	while (y < m->y)
	{
		x = 0;
		printf("[ ");
		while (x < m->x)
		{
			printf("%.2f ", m->m[y][x]);
			++x;
		}
		printf("]\n");
		++y;
	}
}
