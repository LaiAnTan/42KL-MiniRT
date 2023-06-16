#include "../headers/vec4.h"

t_vec4	*vec4_init(double x, double y, double z, double w)
{
	t_vec4	*ret;

	ret = malloc(sizeof(t_vec4));
	ret->raw_matrix = m_init_empty(1, 4);
	ret->raw_matrix->m[0][0] = x;
	ret->raw_matrix->m[1][0] = y;
	ret->raw_matrix->m[2][0] = z;
	ret->raw_matrix->m[3][0] = w;
	return (ret);
}

t_vec4	*vec4_init_from_matrix(t_matrix *matrix)
{
	t_vec4	*ret;

	if (!matrix)
		return (NULL);
	ret = (t_vec4 *) malloc(sizeof(t_vec4));
	ret->raw_matrix = matrix;
	return (ret);
}

t_vec4	*vec4_init_from_array(matrix_type array[4])
{
	t_vec4	*ret;

	ret = (t_vec4 *) malloc(sizeof(t_vec4));
	ret->raw_matrix = m_init(array, 1, 4);
	return (ret);
}

t_vec4	*vec_4_init_from_coordinates(matrix_type coordinates[3])
{
	double	*arr;

	arr = (double *) malloc(sizeof(double) * 4);
	arr[0] = coordinates[0];
	arr[1] = coordinates[1];
	arr[2] = coordinates[2];
	arr[3] = 1; // w

	return (vec4_init_from_array(arr));
}

t_vec4	*vec4_dup(t_vec4 *vector)
{
	t_vec4	*ret;

	ret = (t_vec4 *) malloc(sizeof(t_vec4));
	ret->raw_matrix = m_dup(vector->raw_matrix);
	return (ret);
}

matrix_type	*vec4_to_array(t_vec4 *vector)
{
	matrix_type	*array;

	array = malloc(4 * sizeof(matrix_type));
	array[0] = vector->raw_matrix->m[0][0];
	array[1] = vector->raw_matrix->m[1][0];
	array[2] = vector->raw_matrix->m[2][0];
	array[3] = vector->raw_matrix->m[3][0];
	return (array);
}

void	vec4_free(t_vec4 **vector)
{
	if (!(*vector))
		return ;
	
	free_matrix(&(*vector)->raw_matrix);
	free((*vector));

	*vector = NULL;
}

void	vec4_print(t_vec4 *vector)
{
	t_matrix	*matrix;

	matrix = vector->raw_matrix;
	printf("[ %.2f, %.2f, %.2f, %.2f ]\n", 
		matrix->m[0][0], 
		matrix->m[1][0], 
		matrix->m[2][0], 
		matrix->m[3][0]);
}

// does this exist? idk whoop whoop
double	vec4_dotproduct(t_vec4 *left_vec3, t_vec4 *right_vec3)
{
	int			i;
	double		res;

	t_matrix	*left_m;
	t_matrix	*right_m;

	i = 0;
	res = 0;
	left_m = left_vec3->raw_matrix;
	right_m = right_vec3->raw_matrix;

	while (i < 4)
	{
		res += left_m->m[i][0] * right_m->m[i][0];
		++i;
	}
	return (res);
}

double	vec4_magnitude(t_vec4 *vector)
{
	int		i;
	double	res;

	i = 0;
	res = 0;
	while (i < 4)
	{
		res += vector->raw_matrix->m[i][0] * vector->raw_matrix->m[i][0];
		++i;
	}
	return (sqrt(res));
}

double	vec4_magnitude_sqrd(t_vec4 *vector)
{
	int		i;
	double	res;

	i = 0;
	res = 0;
	while (i < 4)
	{
		res += vector->raw_matrix->m[i][0] * vector->raw_matrix->m[i][0];
		++i;
	}
	return (res);
}

t_vec4	*vec4_diff(t_vec4 *left_vec3, t_vec4 *right_vec3)
{
	return (vec4_init_from_matrix(m_subtraction(left_vec3->raw_matrix, right_vec3->raw_matrix)));
}

t_vec4	*vec4_add(t_vec4 *left_vec3, t_vec4 *right_vec3)
{
	return (vec4_init_from_matrix(m_addition(left_vec3->raw_matrix, right_vec3->raw_matrix)));
}

t_vec4	*vec4_scalar_mult(t_vec4 *vector, double scalar)
{
	return (vec4_init_from_matrix(m_scalar_multi(vector->raw_matrix, scalar)));
}

t_vec4	*vec4_normalize(t_vec4 *vector)
{
	double	mag;

	mag = vec4_magnitude(vector);
	return (vec4_scalar_mult(vector, 1/mag));
}

// i dont think, this exists in the 4th dimention
t_vec4	*vec4_projection(t_vec4 *vector1, t_vec4 *vector2)
{
	double	project_mag;
	t_vec4	*vector2_norm;
	t_vec4	*ret;

	project_mag = vec4_dotproduct(vector1, vector2) / vec4_magnitude(vector2);
	vector2_norm = vec4_normalize(vector2);
	ret = vec4_scalar_mult(vector2_norm, project_mag);
	vec4_free(&vector2_norm);
	return (ret);
}