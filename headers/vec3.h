#ifndef __VEC3_H__
#define __VEC3_H__

#define _USE_MATH_DEFINES 
#include "matrix.h"

// vectors usually is expressed in [x,y,z]
// HOWEVER, not using a 3x3 matrix for a vector will make calculation, VERY painful
// so we just have a raw value and pointers pointing to the first value of each row
typedef struct s_vec3
{
	t_matrix	*raw_matrix;
} t_vec3;


t_vec3	*init_vec3_from_matrix(t_matrix *stuff);
t_vec3	*init_vec3_from_array(matrix_type array[3]);
t_vec3	*dup_vct(t_vec3 *vctr);

matrix_type	*get_val(t_vec3 *vector);

void		print_vec3(t_vec3	*stuff);
void		free_vector(t_vec3 **stuff);

double	v_dotproduct(t_vec3 *left, t_vec3 *right);
double	v_magnitude(t_vec3 *vctr);
double	v_magnitude_sqrd(t_vec3 *vctr);
t_vec3	*v_difference(t_vec3 *left, t_vec3 *right);
t_vec3	*v_addition(t_vec3 *left, t_vec3 *right);
t_vec3	*v_scalar_multi(t_vec3 *vctr, double value);
t_vec3	*v_normalize(t_vec3 *vctr);
t_vec3	*v_projection(t_vec3 *a, t_vec3 *b);
double	*v_get_direction_angles(t_vec3 *vctr);

#endif