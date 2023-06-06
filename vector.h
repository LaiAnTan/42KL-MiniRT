#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "matrix.h"

// vectors usually is expressed in [x,y,z]
// HOWEVER, not using a 3x3 matrix for a vector will make calculation, VERY painful
// so we just have a raw value and pointers pointing to the first value of each thingy
typedef struct s_vector
{
	t_matrix	*raw_matrix;
	matrix_type	*values[3];
} t_vector;

t_vector	*init_vector(t_matrix	*stuff);
t_vector	*init_vector_intarr(matrix_type	array[3]);
t_vector	*dup_vct(t_vector *vctr);
void		print_vector(t_vector	*stuff);
void		free_vector(t_vector **stuff);

double		v_dotproduct(t_vector *left, t_vector *right);
double		v_magnitude(t_vector *vctr);
t_vector	*v_difference(t_vector *left, t_vector *right);
t_vector	*v_addition(t_vector *left, t_vector *right);
t_vector	*v_scalar_multi(t_vector *vctr, double value);
t_vector	*v_normalize(t_vector *vctr);
t_vector	*v_projection(t_vector *a, t_vector *b);

#endif