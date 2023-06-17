#ifndef __VEC4__
# define __VEC4__

#define _USE_MATH_DEFINES 
#include "matrix.h"
#include "vec3.h"

/*
Vec4 datatype, used in coordinate calculations
[x, y, z, w], where xyz = coordinates in 3d space and w = 1
*/
typedef struct s_vec4
{
	t_matrix	*raw_matrix;
} t_vec4;

t_vec4	*vec4_init(double x, double y, double z, double w);
t_vec4	*vec4_init_from_matrix(t_matrix *matrix);
t_vec4	*vec4_init_from_array(matrix_type array[4]);
t_vec4	*vec_4_init_from_coordinates(matrix_type coordinates[3]);
t_vec4	*vec4_dup(t_vec4 *vector);

matrix_type	*vec4_to_array(t_vec4 *vector);

void	vec4_print(t_vec4 *vector);
void	vec4_free(t_vec4 **vector);

double	vec4_dotproduct(t_vec4 *left_vector, t_vec4 *right_vector);
double	vec4_magnitude(t_vec4 *vector);
double	vec4_magnitude_sqrd(t_vec4 *vector);

t_vec4	*vec4_add(t_vec4 *left_vector, t_vec4 *right_vector);
t_vec4	*vec4_diff(t_vec4 *left_vector, t_vec4 *right_vector);
t_vec4	*vec4_scalar_mult(t_vec4 *vector, double scalar);
t_vec4	*vec4_normalize(t_vec4 *vector);
t_vec4	*vec4_projection(t_vec4 *vector1, t_vec4 *vector2);

#endif