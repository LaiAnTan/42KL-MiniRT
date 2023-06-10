#include "../headers/vec3.h"

// PLEASE MALLOC STUFF
t_vec3	*init_vec3_from_matrix(t_matrix *stuff)
{
	t_vec3	*ret;

	if (!stuff)
		return (NULL);
	ret = malloc (sizeof(t_vec3));
	ret->raw_matrix = stuff;
	return (ret);
}

t_vec3	*init_vec3_from_array(matrix_type	array[3])
{
	t_vec3	*ret;

	ret = malloc (sizeof(t_vec3));
	ret->raw_matrix = init_matrix(array, 1, 3);
	return (ret);
}

t_vec3	*dup_vct(t_vec3 *vctr)
{
	t_vec3	*ret;

	ret = malloc(sizeof(t_vec3));
	ret->raw_matrix = m_dup(vctr->raw_matrix);
	return (ret);
}

matrix_type	*get_val(t_vec3 *vector)
{
	matrix_type	*array;

	array = malloc(3 * sizeof(matrix_type));
	array[0] = vector->raw_matrix->stuff[0][0];
	array[1] = vector->raw_matrix->stuff[1][0];
	array[2] = vector->raw_matrix->stuff[2][0];
	return (array);
}

void	free_vector(t_vec3 **stuff)
{
	if (!(*stuff))
		return ;
	
	free_matrix(&(*stuff)->raw_matrix);
	free((*stuff));

	*stuff = NULL;
}

void	print_vec3(t_vec3 *stuff)
{
	t_matrix	*mtrx;

	mtrx = stuff->raw_matrix;
	printf("[ %.2f, %.2f, %.2f ]\n", 
		mtrx->stuff[0][0], mtrx->stuff[1][0], mtrx->stuff[2][0]);
}

// we gonna happily assume its i, j, k (so perpendicular, so cancel each other out)
double	v_dotproduct(t_vec3 *left, t_vec3 *right)
{
	t_matrix	*left_m;
	t_matrix	*right_m;

	left_m = left->raw_matrix;
	right_m = right->raw_matrix;

	// epic hard code
	return (
		(left_m->stuff[0][0] * right_m->stuff[0][0]) +
		(left_m->stuff[1][0] * right_m->stuff[1][0]) +
		(left_m->stuff[2][0] * right_m->stuff[2][0]) 
	);
}

// projecting vector a on vector b
t_vec3	*v_projection(t_vec3 *a, t_vec3 *b)
{
	double		project_mag;
	t_vec3	*norm_b;
	t_vec3	*ret;

	project_mag = v_dotproduct(a, b) / v_magnitude(b);
	norm_b = v_normalize(b);
	ret = v_scalar_multi(norm_b, project_mag);
	free_vector(&norm_b);
	return (ret);
}

// oh WE ARE DEFINATELY OPTIMIZING THIS LATER
double	v_magnitude(t_vec3 *vctr)
{
	double	x;
	double	y;
	double	z;

	x = vctr->raw_matrix->stuff[0][0];
	y = vctr->raw_matrix->stuff[1][0];
	z = vctr->raw_matrix->stuff[2][0];
	return (sqrt((x * x) + (y * y) + (z * z)));
}

// magnitude, but not square-rooted
double	v_magnitude_sqrd(t_vec3 *vctr)
{
	double	x;
	double	y;
	double	z;

	x = vctr->raw_matrix->stuff[0][0];
	y = vctr->raw_matrix->stuff[1][0];
	z = vctr->raw_matrix->stuff[2][0];
	return ((x * x) + (y * y) + (z * z));
}

t_vec3	*v_difference(t_vec3 *left, t_vec3 *right)
{
	return (init_vec3_from_matrix(m_subtraction(left->raw_matrix, right->raw_matrix)));
}

t_vec3	*v_addition(t_vec3 *left, t_vec3 *right)
{
	return (init_vec3_from_matrix(m_addition(left->raw_matrix, right->raw_matrix)));
}

t_vec3	*v_scalar_multi(t_vec3 *vctr, double value)
{
	return (init_vec3_from_matrix(m_scalar_multi(vctr->raw_matrix, value)));
}

t_vec3	*v_normalize(t_vec3 *vctr)
{
	double	mag;

	mag = v_magnitude(vctr);
	return (v_scalar_multi(vctr, 1/mag));
}

// double	*v_get_direction_angles(t_vec3 *vctr)
// {
	
// }