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

/*
OPTIONS:
O_CREATE - stores the output in a new malloced vector and returns it
O_REPLACE - replaces the value of the input vector (left vector if more than 1) with the output and returns the same vector (No malloc)
*/
typedef int options;
#define O_CREATE	0
#define O_REPLACE	1

// functions with return valeus: returns NULL if operation failed for some reason

t_vec3	*vec3_init(double x, double y, double z);
t_vec3	*vec3_init_from_matrix(t_matrix *stuff);
t_vec3	*vec3_init_from_array(matrix_type array[3]);
t_vec3	*vec3_dup(t_vec3 *vctr);

matrix_type	*vec3_get_val(t_vec3 *vector);
void		vec3_store_val(t_vec3 *vector, matrix_type array[3]);

void	vec3_print(t_vec3 *stuff);
void	vec3_free(t_vec3 **stuff);

double	vec3_dotproduct(t_vec3 *left, t_vec3 *right);
double	vec3_magnitude(t_vec3 *vctr);
double	vec3_magnitude_sqrd(t_vec3 *vctr);
double	*vec3_direction_cosines(t_vec3 *vctr);
double	*vec3_u_direction_cosines(t_vec3 *vec3_norm);

t_vec3	*vec3_negate(t_vec3 *vctr);
t_vec3	*vec3_difference(t_vec3 *left, t_vec3 *right, options op);
t_vec3	*vec3_multi_each_elem(t_vec3 *left, t_vec3 *right, options op);
t_vec3	*vec3_addition(t_vec3 *left, t_vec3 *right, options op);
t_vec3	*vec3_scalar_multi(t_vec3 *vctr, double value, options op);
t_vec3	*vec3_normalize(t_vec3 *vctr, options op);
t_vec3	*vec3_projection(t_vec3 *a, t_vec3 *b, options op);
t_vec3	*vec3_crossproduct(t_vec3 *left, t_vec3 *righ, options op);

int		vec3_isequal(t_vec3 *a, t_vec3 *b);
#endif