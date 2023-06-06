#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef double matrix_type;

typedef struct s_matrix
{
	matrix_type	matrix[3][3];
} t_matrix;

t_matrix	*init_matrix(matrix_type values[9]);
t_matrix	*dup_matrix(t_matrix *ori);
void		print_matrix(t_matrix *stuff);
void		free_matrix(t_matrix **stuff);

// operasi
t_matrix	*m_addition(t_matrix *left, t_matrix *right);
t_matrix	*m_substraction(t_matrix *left, t_matrix *right);
t_matrix	*m_multiplication(t_matrix *left, t_matrix *right);
t_matrix	*m_scalar_multi(t_matrix *left, double val);
t_matrix	*m_scalar_divide(t_matrix *left, double val);
double		get_determinant(t_matrix *mtrx);
t_matrix	*inverse_mtrx(t_matrix	*mtrx);


#endif