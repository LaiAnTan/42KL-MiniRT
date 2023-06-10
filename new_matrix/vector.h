#ifndef __VECTOR_H__
#define __VECTOR_H__

#define _USE_MATH_DEFINES 
#include "matrix.h"

// vectors usually is expressed in [x,y,z]
// HOWEVER, not using a 3x3 matrix for a vector will make calculation, VERY painful
// so we just have a raw value and pointers pointing to the first value of each row
typedef struct s_vector
{
	t_matrix	*raw_matrix;
} t_vector;

t_vector	*init_vector(t_matrix	*stuff);
t_vector	*init_vector_intarr(matrix_type	array[3]);
t_vector	*dup_vct(t_vector *vctr);

matrix_type	*get_val(t_vector *vector);

void		print_vector(t_vector	*stuff);
void		free_vector(t_vector **stuff);

double		v_dotproduct(t_vector *left, t_vector *right);
double		v_magnitude(t_vector *vctr);
double		v_magnitude_sqrd(t_vector *vctr);
t_vector	*v_difference(t_vector *left, t_vector *right);
t_vector	*v_addition(t_vector *left, t_vector *right);
t_vector	*v_scalar_multi(t_vector *vctr, double value);
t_vector	*v_get_unit_vector(t_vector *vctr);
t_vector	*v_projection(t_vector *a, t_vector *b);
double		*v_direction_cosines(t_vector *vctr);
double		*v_u_direction_cosines(t_vector *v_norm);
t_vector	*v_crossproduct(t_vector *left, t_vector *right);

#endif