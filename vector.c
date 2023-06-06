#include "vector.h"

static	void	set_links(t_vector *ret)
{
	ret->values[0] = &ret->raw_matrix->matrix[0][0];
	ret->values[1] = &ret->raw_matrix->matrix[1][0];
	ret->values[2] = &ret->raw_matrix->matrix[2][0];
}

// PLEASE MALLOC STUFF
t_vector	*init_vector(t_matrix *stuff)
{
	t_vector	*ret;
	ret = malloc (sizeof(t_vector));

	ret->raw_matrix = stuff;
	set_links(ret);
	return (ret);
}

t_vector	*init_vector_intarr(matrix_type	array[3])
{
	matrix_type			temp[9];
	int			i;
	t_vector	*ret;

	i = -1;
	while (++i < 9)
		temp[i] = 0;
	ret = malloc (sizeof(t_vector));
	temp[0] = array[0];
	temp[3] = array[0];
	temp[6] = array[0];
	ret->raw_matrix = init_matrix(temp);
	set_links(ret);
	return (ret);
}

t_vector	*dup_vct(t_vector *vctr)
{
	t_vector	*ret;

	ret = malloc(sizeof(t_vector));
	ret->raw_matrix = dup_matrix(vctr->raw_matrix);
	set_links(ret);
	return (ret);
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
	printf("[ %.2f, %.2f, %.2f ]\n", 
		*(stuff->values[0]), *(stuff->values[1]), *(stuff->values[2]));
}

// we gonna happily assume its i, j, k (so perpendicular, so cancel each other out)
double	v_dotproduct(t_vector *left, t_vector *right)
{
	return (
		(*(left->values[0]) * *(right->values[0])) +
		(*(left->values[1]) * *(right->values[1])) +
		(*(left->values[2]) * *(right->values[2]))
	);
}

// projecting vector a on vector b
t_vector	*v_projection(t_vector *a, t_vector *b)
{
	double		project_mag;
	t_vector	*norm_b;
	t_vector	*ret;

	project_mag = v_dotproduct(a, b) / v_magnitude(b);
	norm_b = v_normalize(b);
	ret = v_scalar_multi(norm_b, project_mag);
	free_vector(&norm_b);
	return (ret);
}

// oh WE ARE DEFINATELY OPTIMIZING THIS LATER
double	v_magnitude(t_vector *vctr)
{
	int	x;
	int	y;
	int	z;

	x = *(vctr->values[0]);
	y = *(vctr->values[1]);
	z = *(vctr->values[2]);
	return (sqrt( (x * x) + (y * y) + (z * z)));
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

t_vector	*v_normalize(t_vector *vctr)
{
	double	mag;

	mag = v_magnitude(vctr);
	return (v_scalar_multi(vctr, 1/mag));
}