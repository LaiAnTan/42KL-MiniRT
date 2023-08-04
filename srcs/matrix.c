/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshi-xia <cshi-xia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:03 by tlai-an           #+#    #+#             */
/*   Updated: 2023/08/04 21:24:30 by cshi-xia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/matrix.h"

t_matrix	*m_init(matrix_type *values, int x, int y)
{
	t_matrix	*ret;
	int	i;
	int	j;

	ret = malloc(sizeof(t_matrix));
	ret->x = x;
	ret->y = y;
	j = 0;
	ret->m = malloc(sizeof(matrix_type *) * y);
	while (j < ret->y)
	{
		i = 0;
		ret->m[j] = malloc(sizeof(matrix_type) * x);
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
	t_matrix	*ret;
	int	i;
	int	j;

	ret = malloc(sizeof(t_matrix));
	ret->x = x;
	ret->y = y;
	j = 0;
	ret->m = malloc(sizeof(matrix_type *) * y);
	while (j < y)
	{
		i = 0;
		ret->m[j] = malloc(sizeof(matrix_type) * x);
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
	ret = m_init_empty(x , y);
	while (i < x)
	{
		ret->m[i][i] = 1;
		++i;
	}
	return (ret);
}

matrix_type	*m_convert_to_1d(t_matrix *source)
{
	matrix_type	*ret;
	int	i;
	int	j;

	ret = malloc(sizeof(matrix_type) * (source->x * source->y));
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

t_matrix	*m_dup(t_matrix *source)
{
	t_matrix	*ret;
	matrix_type	*temp;

	temp = m_convert_to_1d(source);
	ret = m_init(temp, source->x, source->y);
	free(temp);
	return (ret);
}

t_matrix	*m_dup_emptymatrix(t_matrix *source)
{
	return (m_init_empty(source->x, source->y));
}

t_matrix	*m_addition(t_matrix *left, t_matrix *right)
{
	t_matrix	*ret;
	int			x;
	int			y;

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
	t_matrix	*ret;
	int			x;
	int			y;

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

static	matrix_type	line_multiplication(t_matrix *left, t_matrix *right, int x, int y)
{
	matrix_type	ret;
	int			x1;
	int			y1;

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
	t_matrix	*ret;
	int			x;
	int			y;

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

t_matrix	*m_scalar_multi(t_matrix *left, double val)
{
	t_matrix	*ret;
	int			x;
	int			y;

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
	return (m_scalar_multi(left, 1/val));
}

void		m_print_matrix(t_matrix *m)
{
	for (int y = 0; y < m->y; ++y)
	{
		printf("[ ");
		for (int x = 0; x < m->x; ++x)
		{
			printf("%.2f ", m->m[y][x]);
		}
		printf("]\n");
	}
}

t_matrix	*m_transpose(t_matrix *m)
{
	t_matrix	*ret;
	int			x;
	int			y;

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