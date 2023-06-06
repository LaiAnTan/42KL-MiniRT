#include "matrix.h"

// accepts a 9 value array
t_matrix	*init_matrix(matrix_type values[9])
{
	t_matrix	*ret;
	int			x;
	int			y;

	ret = malloc (sizeof(t_matrix));
	y = 0;
	x = 0;
	while (y < 3)
	{
		ret->matrix[y][x] = values[(y * 3) + x];
		++x;
		if (x == 3)
		{
			x = 0;
			++y;
		}
	}
	return (ret);
}

t_matrix	*dup_matrix(t_matrix *ori)
{
	t_matrix	*ret;
	int			x;
	int			y;

	ret = malloc (sizeof(t_matrix));
	y = 0;
	x = 0;
	while (y < 3)
	{
		ret->matrix[y][x] = ori->matrix[y][x];
		++x;
		if (x == 3)
		{
			x = 0;
			++y;
		}
	}
	return (ret);
}

// does what it said
void	print_matrix(t_matrix *stuff)
{
	for (int y = 0; y < 3; ++y)
	{
		printf("[ ");
		for (int x = 0; x < 3; ++x)
		{
			printf("%.2f ", stuff->matrix[y][x]);
		}
		printf("]\n");
	}
}

// this is hilarious
void	free_matrix(t_matrix **stuff)
{
	free((*stuff));
	(*stuff) = NULL;
	return ;
}

t_matrix	*m_addition(t_matrix *left, t_matrix *right)
{
	matrix_type	values[9];
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (y < 3)
	{
		values[(y * 3) + x] = left->matrix[y][x] + right->matrix[y][x]; 
		++x;
		if (x==3)
		{
			x = 0;
			++y;
		}
	}
	return (init_matrix(values));
}

t_matrix	*m_substraction(t_matrix *left, t_matrix *right)
{
	matrix_type	values[9];
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (y < 3)
	{
		values[(y * 3) + x] = left->matrix[y][x] - right->matrix[y][x]; 
		++x;
		if (x == 3)
		{
			x = 0;
			++y;
		}
	}
	return (init_matrix(values));
}

static	matrix_type	line_multiplication(t_matrix *left, t_matrix *right, int x, int y)
{
	matrix_type	ret;
	int			x1;
	int			y1;

	ret = 0;
	x1 = 0;
	y1 = 0;

	while (x1 < 3 && y1 < 3)
	{
		ret += left->matrix[y][x1] * right->matrix[y1][x];
		++x1;
		++y1;
	}
	return (ret);
}

t_matrix	*m_multiplication(t_matrix *left, t_matrix *right)
{
	matrix_type values[9];
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (y < 3)
	{
		values[(y * 3) + x] = line_multiplication(left, right, x, y);
		++x;
		if (x == 3)
		{
			x = 0;
			++y;
		}
	}
	return (init_matrix(values));
}

t_matrix	*m_scalar_multi(t_matrix *left, double val)
{
	matrix_type values[9];
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (y < 3)
	{
		values[(y * 3) + x] = left->matrix[y][x] * val;
		++x;
		if (x == 3)
		{
			x = 0;
			++y;
		}
	}
	return (init_matrix(values));
}

t_matrix	*m_scalar_divide(t_matrix *left, double val)
{
	return (m_scalar_multi(left, 1/val));
}


static void	get_top_three_val(t_matrix *mtrx, matrix_type *storage)
{
	storage[0] = mtrx->matrix[0][0];
	storage[1] = mtrx->matrix[0][1];
	storage[2] = mtrx->matrix[0][2];
}

// https://www.chilimath.com/lessons/advanced-algebra/determinant-3x3-matrix/
// probably use a better method next time ehe
double	get_determinant(t_matrix *mtrx)
{
	double		ret;
	matrix_type	top_3[3];
	
	get_top_three_val(mtrx, top_3);
	ret = top_3[0] * ((mtrx->matrix[1][1] * mtrx->matrix[2][2]) - (mtrx->matrix[1][2] * mtrx->matrix[2][1]));
	ret -= top_3[1] * ((mtrx->matrix[1][0] * mtrx->matrix[2][2]) - (mtrx->matrix[1][2] * mtrx->matrix[2][0]));
	ret += top_3[2] * ((mtrx->matrix[1][0] * mtrx->matrix[2][1]) - (mtrx->matrix[1][1] * mtrx->matrix[2][0]));
	return (ret);
}

static	void	swap(matrix_type *a, matrix_type *b)
{
	matrix_type temp;

	temp = (*a);
	(*a) = (*b);
	(*b) = temp;
}

// reflecting the matrix about the main diagonal
// too lazy to do an algorithm woohooooooo
static	void	transpose(t_matrix *mrtx)
{
	swap(&(mrtx->matrix[0][1]), &(mrtx->matrix[1][0]));
	swap(&(mrtx->matrix[0][2]), &(mrtx->matrix[2][0]));
	swap(&(mrtx->matrix[1][2]), &(mrtx->matrix[2][1]));
}

static matrix_type	minor_matrix_calc(t_matrix *mtrx, int ig_x, int ig_y)
{
	matrix_type	value;
	int			y1;
	int			y2;
	int			x1;
	int			x2;

	x1 = !(ig_x);
	y1 = !(ig_y);
	x2 = 2 - (ig_x == 2);
	y2 = 2 - (ig_y == 2);
	value = (mtrx->matrix[y1][x1] * mtrx->matrix[y2][x2]) - (mtrx->matrix[y1][x2] * mtrx->matrix[y2][x1]);
	return (value);
}

// what the fuck
static t_matrix	*minor_matrix(t_matrix *mrtx)
{
	matrix_type	value[9];
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < 3)
	{
		value[(y * 3) + x] = minor_matrix_calc(mrtx, x, y);
		++x;
		if (x == 3)
		{
			x = 0;
			++y;
		}
	}
	return (init_matrix(value));
}

static	t_matrix *get_cofactor(t_matrix *mrtx)
{
	t_matrix	*dup;
	t_matrix	*store;

	dup = dup_matrix(mrtx);
	transpose(dup);
	store = minor_matrix(dup); 
	free_matrix(&dup);
	return (store);
}

static void	reverse_sign(t_matrix *mrtx)
{
	int	x;
	int	y;
	int	negative;

	x = 0;
	y = 0;
	negative = 1;
	while (y < 3)
	{
		mrtx->matrix[y][x] = mrtx->matrix[y][x] * negative;
		negative *= -1;
		++x;
		if (x == 3)
		{
			x = 0;
			++y;
		}
	}
}

// just in case
// i dont think we will be using this tho
t_matrix	*inverse_mtrx(t_matrix	*mtrx)
{
	t_matrix	*co_fac;
	t_matrix	*ret;
	float		dtrmnt;

	dtrmnt = get_determinant(mtrx);
	if (!dtrmnt)
		return (NULL);
	co_fac = get_cofactor(mtrx);
	reverse_sign(co_fac);
	ret = m_scalar_divide(co_fac, dtrmnt);
	return (ret);
}