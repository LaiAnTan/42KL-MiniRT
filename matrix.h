#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef	double	matrix_type;

typedef struct	s_matrix
{
	matrix_type	**stuff;
	int	x;
	int	y;
} t_matrix;

t_matrix	*init_matrix(matrix_type *values, int x, int y);
t_matrix	*init_empty_matrix(int x, int y);
t_matrix	*init_matrix_resized(t_matrix *values, int new_x, int new_y, matrix_type fill);
t_matrix	*m_dup(t_matrix *source);
t_matrix	*m_dup_emptymatrix(t_matrix *source);

matrix_type	*m_convert_to_1d(t_matrix *source);
void		m_print_matrix(t_matrix *m);

t_matrix	*m_addition(t_matrix *left, t_matrix *right);
t_matrix	*m_substraction(t_matrix *left, t_matrix *right);
t_matrix	*m_multiplication(t_matrix *left, t_matrix *right);
t_matrix	*m_scalar_multi(t_matrix *left, double val);
t_matrix	*m_scalar_divide(t_matrix *left, double val);

// uhh
// does this ->
// [ 1 ]     [ 1 , 0 , 0 ]
// [ 2 ] --> [ 0 , 2 , 0 ]
// [ 3 ]     [ 0 , 0 , 3 ]
t_matrix	*m_make_diagonal_matrix(t_matrix *o);

void		free_matrix(t_matrix **t_free);
#endif