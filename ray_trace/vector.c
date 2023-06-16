#include "vector.h"

// PLEASE MALLOC STUFF
t_vector	*init_vector(t_matrix *stuff)
{
	t_vector	*ret;

	if (!stuff)
		return (NULL);
	ret = malloc (sizeof(t_vector));
	ret->raw_matrix = stuff;
	return (ret);
}

t_vector	*init_vector_intarr(matrix_type	array[3])
{
	t_vector	*ret;

	ret = malloc (sizeof(t_vector));
	ret->raw_matrix = init_matrix(array, 1, 3);
	return (ret);
}

t_vector	*dup_vct(t_vector *vctr)
{
	t_vector	*ret;

	ret = malloc(sizeof(t_vector));
	ret->raw_matrix = m_dup(vctr->raw_matrix);
	return (ret);
}

void	get_val(t_vector *vector, matrix_type array[3])
{
	array[0] = vector->raw_matrix->stuff[0][0]; // x i
	array[1] = vector->raw_matrix->stuff[1][0]; // y j
	array[2] = vector->raw_matrix->stuff[2][0]; // z k
}

void	free_vector(t_vector **stuff)
{
	if (!(*stuff))
		return ;
	
	free_matrix(&(*stuff)->raw_matrix);
	free((*stuff));

	*stuff = NULL;
}

void	print_vector(t_vector *stuff)
{
	t_matrix	*mtrx;

	mtrx = stuff->raw_matrix;
	printf("( %.2f, %.2f, %.2f )\n", 
		mtrx->stuff[0][0], mtrx->stuff[1][0], mtrx->stuff[2][0]);
}

// we gonna happily assume its i, j, k (so perpendicular, so cancel each other out)
double	v_dotproduct(t_vector *left, t_vector *right)
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
t_vector	*v_projection(t_vector *a, t_vector *b)
{
	double		project_mag;
	t_vector	*norm_b;
	t_vector	*ret;

	project_mag = v_dotproduct(a, b) / v_magnitude(b);
	norm_b = v_get_unit_v(b);
	ret = v_scalar_multi(norm_b, project_mag);
	free_vector(&norm_b);
	return (ret);
}

// oh WE ARE DEFINATELY OPTIMIZING THIS LATER
double	v_magnitude(t_vector *vctr)
{
	double	x;
	double	y;
	double	z;

	x = vctr->raw_matrix->stuff[0][0];
	y = vctr->raw_matrix->stuff[1][0];
	z = vctr->raw_matrix->stuff[2][0];
	return (sqrt( (x * x) + (y * y) + (z * z)));
}

// magnitude, but not square-rooted
// use this if posible as this is faster (no sqrt)
double	v_magnitude_sqrd(t_vector *vctr)
{
	double	x;
	double	y;
	double	z;

	x = vctr->raw_matrix->stuff[0][0];
	y = vctr->raw_matrix->stuff[1][0];
	z = vctr->raw_matrix->stuff[2][0];
	return ((x * x) + (y * y) + (z * z));
}

t_vector	*v_difference(t_vector *left, t_vector *right)
{
	return (init_vector(m_substraction(left->raw_matrix, right->raw_matrix)));
}

t_vector	*v_addition(t_vector *left, t_vector *right)
{
	return (init_vector(m_addition(left->raw_matrix, right->raw_matrix)));
}

t_vector	*v_scalar_multi(t_vector *vctr, double value)
{
	return (init_vector(m_scalar_multi(vctr->raw_matrix, value)));
}

t_vector	*v_scalar_divide(t_vector *vctr, double value)
{
	return (v_scalar_multi(vctr, 1/value));
}

t_vector	*v_get_unit_v(t_vector *vctr)
{
	double	mag;

	mag = v_magnitude_sqrd(vctr);
	if (mag == 1)
		return (dup_vct(vctr));
	return (v_scalar_multi(vctr, 1/sqrt(mag)));
}

double	*v_direction_cosines(t_vector *vctr)
{
	double	*ret;
	double	mag;

	ret = malloc(sizeof(double) * 3);
	mag = v_magnitude(vctr);

	ret[0] = acos(vctr->raw_matrix->stuff[0][0] / mag);
	ret[1] = acos(vctr->raw_matrix->stuff[1][0] / mag); 
	ret[2] = acos(vctr->raw_matrix->stuff[2][0] / mag);
	return (ret);
}

double	*v_u_direction_cosines(t_vector *v_norm)
{
	double	*ret;

	ret = malloc(sizeof(double) * 3);
	ret[0] = acos(v_norm->raw_matrix->stuff[0][0]);
	ret[1] = acos(v_norm->raw_matrix->stuff[1][0]); 
	ret[2] = acos(v_norm->raw_matrix->stuff[2][0]);
	return (ret);
}

t_vector	*v_crossproduct(t_vector *left, t_vector *right)
{
	matrix_type	stuff[3];
	matrix_type	left_val[3];
	matrix_type	right_val[3];

	get_val(left, left_val);
	get_val(right, right_val);
	stuff[0] = (left_val[1] * right_val[2]) - (left_val[2] * right_val[1]);
	stuff[1] = -1 * ((left_val[0] * right_val[2]) - (left_val[2] * right_val[0]));
	stuff[2] = (left_val[0] * right_val[1]) - (left_val[1] * right_val[0]);
	return (init_vector_intarr(stuff));
}