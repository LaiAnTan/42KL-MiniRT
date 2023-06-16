#include "matrix.h"

t_matrix	*init_matrix(matrix_type *values, int x, int y)
{
	t_matrix	*ret;
	int	i;
	int	j;

	ret = malloc(sizeof(t_matrix));
	ret->stuff = malloc(sizeof(matrix_type *) * y);
	
	ret->x = x;
	ret->y = y;
	j = 0;
	while (j < ret->y)
	{
		i = 0;
		ret->stuff[j] = malloc(sizeof(matrix_type) * x);
		while (i < ret->x)
		{
			ret->stuff[j][i] = values[(j * ret->x) + i];
			++i;
		}
		++j;
	}
	return (ret);
}

t_matrix	*init_empty_matrix(int x, int y)
{
	t_matrix	*ret;
	int	i;
	int	j;

	ret = malloc(sizeof(t_matrix));
	ret->stuff = malloc(sizeof(matrix_type *) * y);
	
	ret->x = x;
	ret->y = y;
	j = 0;
	while (j < y)
	{
		i = 0;
		ret->stuff[j] = malloc(sizeof(matrix_type) * x);
		while (i < x)
		{
			ret->stuff[j][i] = 0;
			++i;
		}
		++j;
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
			ret[(j * source->x) + i] = source->stuff[j][i];
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
	ret = init_matrix(temp, source->x, source->y);
	free(temp);
	return (ret);
}

t_matrix	*m_dup_emptymatrix(t_matrix *source)
{
	return (init_empty_matrix(source->x, source->y));
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
			ret->stuff[y][x] = left->stuff[y][x] + right->stuff[y][x];
			++x;
		}
		++y;
	}
	return (ret);
}

t_matrix	*m_substraction(t_matrix *left, t_matrix *right)
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
			ret->stuff[y][x] = left->stuff[y][x] - right->stuff[y][x];
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
		ret += left->stuff[y][x1] * right->stuff[y1][x];
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
	ret = init_empty_matrix(right->x, left->y);
	y = 0;
	while (y < ret->y)
	{
		x = 0;
		while (x < ret->x)
		{
			ret->stuff[y][x] = line_multiplication(left, right, x, y);
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
			ret->stuff[y][x] = left->stuff[y][x] * val;
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
			printf("%.2f ", m->stuff[y][x]);
		}
		printf("]\n");
	}
}

void	free_matrix(t_matrix **t_free)
{
	int	y;

	y = 0;
	while (y < (*t_free)->y)
	{
		free((*t_free)->stuff[y]);
		++y;
	}
	free((*t_free)->stuff);
	free((*t_free));
}