/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:42:22 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:12:20 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vec3.h"

t_vec3	*vec3_init(double x, double y, double z)
{
	t_vec3	*ret;

	ret = malloc(sizeof(t_vec3));
	ret->raw_matrix = m_init_empty(1, 3);
	ret->raw_matrix->m[0][0] = x;
	ret->raw_matrix->m[1][0] = y;
	ret->raw_matrix->m[2][0] = z;
	return (ret);
}

t_vec3	*vec3_init_from_matrix(t_matrix *stuff)
{
	t_vec3	*ret;

	if (!stuff)
		return (NULL);
	ret = malloc (sizeof(t_vec3));
	ret->raw_matrix = stuff;
	return (ret);
}

t_vec3	*vec3_init_from_array(t_matrix_type array[3])
{
	t_vec3	*ret;

	ret = malloc (sizeof(t_vec3));
	ret->raw_matrix = m_init(array, 1, 3);
	return (ret);
}

t_vec3	*vec3_dup(t_vec3 *vctr)
{
	t_vec3	*ret;

	ret = malloc(sizeof(t_vec3));
	ret->raw_matrix = m_dup(vctr->raw_matrix);
	return (ret);
}

t_matrix_type	*vec3_get_val(t_vec3 *vector)
{
	t_matrix_type	*array;

	array = malloc(3 * sizeof(t_matrix_type));
	array[0] = vector->raw_matrix->m[0][0];
	array[1] = vector->raw_matrix->m[1][0];
	array[2] = vector->raw_matrix->m[2][0];
	return (array);
}

void	vec3_store_val(t_vec3 *vector, t_matrix_type array[3])
{
	array[0] = vector->raw_matrix->m[0][0];
	array[1] = vector->raw_matrix->m[1][0];
	array[2] = vector->raw_matrix->m[2][0];
}

void	vec3_print(t_vec3 *stuff)
{
	t_matrix	*mtrx;

	mtrx = stuff->raw_matrix;
	printf("[ %.2f, %.2f, %.2f ]\n", 
		mtrx->m[0][0], mtrx->m[1][0], mtrx->m[2][0]);
}

void	vec3_free(t_vec3 **stuff)
{
	if (!(*stuff))
		return ;
	
	free_matrix(&(*stuff)->raw_matrix);
	free((*stuff));

	*stuff = NULL;
}

// we gonna happily assume its i, j, k (so perpendicular, so cancel each other out)
double	vec3_dotproduct(t_vec3 *left, t_vec3 *right)
{
	t_matrix	*left_m;
	t_matrix	*right_m;

	left_m = left->raw_matrix;
	right_m = right->raw_matrix;

	// epic hard code
	return (
		(left_m->m[0][0] * right_m->m[0][0]) +
		(left_m->m[1][0] * right_m->m[1][0]) +
		(left_m->m[2][0] * right_m->m[2][0]) 
	);
}

// oh WE ARE DEFINATELY OPTIMIZING THIS LATER
double	vec3_magnitude(t_vec3 *vctr)
{
	double	x;
	double	y;
	double	z;

	x = vctr->raw_matrix->m[0][0];
	y = vctr->raw_matrix->m[1][0];
	z = vctr->raw_matrix->m[2][0];
	return (sqrt((x * x) + (y * y) + (z * z)));
}

// magnitude, but not square-rooted
double	vec3_magnitude_sqrd(t_vec3 *vctr)
{
	double	x;
	double	y;
	double	z;

	x = vctr->raw_matrix->m[0][0];
	y = vctr->raw_matrix->m[1][0];
	z = vctr->raw_matrix->m[2][0];
	return ((x * x) + (y * y) + (z * z));
}

// 0 - angle between ray and x axis
// 1 - angle between ray and y axis
// 2 - angle between ray and z axis
// dont port this to t_vec3 (good luck figuring out angle between the 4th dimension )
double	*vec3_direction_cosines(t_vec3 *vctr)
{
    double	*ret;
    double	mag;

    ret = malloc(sizeof(double) * 3);
    mag = vec3_magnitude(vctr);

    ret[0] = acos(vctr->raw_matrix->m[0][0] / mag);
    ret[1] = acos(vctr->raw_matrix->m[1][0] / mag); 
    ret[2] = acos(vctr->raw_matrix->m[2][0] / mag);
    return (ret);
}


double	*vec3_u_direction_cosines(t_vec3 *vec3_norm)
{
	double	*ret;

	ret = malloc(sizeof(double) * 3);
	ret[0] = acos(vec3_norm->raw_matrix->m[0][0]);
	ret[1] = acos(vec3_norm->raw_matrix->m[1][0]); 
	ret[2] = acos(vec3_norm->raw_matrix->m[2][0]);
	return (ret);
}


// projecting vector a on vector b
t_vec3	*vec3_projection(t_vec3 *a, t_vec3 *b, t_options op)
{
	double		project_mag;
	t_vec3	*norm_b;
	t_vec3	*ret;

	project_mag = vec3_dotproduct(a, b) / vec3_magnitude(b);
	norm_b = vec3_normalize(b, O_CREATE);

	if (op == O_CREATE)
		ret = vec3_scalar_multi(norm_b, project_mag, O_CREATE);
	else if (op == O_REPLACE)
		ret = vec3_scalar_multi(norm_b, project_mag, O_REPLACE);
	vec3_free(&norm_b);
	return (ret);
}

t_vec3	*vec3_multi_each_elem(t_vec3 *left, t_vec3 *right, t_options op)
{
	t_matrix_type	store[3];
	int			i;

	i = 0;
	while (i < 3)
	{
		store[i] = left->raw_matrix->m[i][0] * right->raw_matrix->m[i][0];
		++i;
	}

	// O_CREATE
	if (op == O_CREATE)
		return (vec3_init_from_array(store));

	// O_REPLACE
	i = 0;
	while (i < 3)
	{
		left->raw_matrix->m[i][0] = store[i];
		++i;
	}
	return (left);
}

t_vec3	*vec3_difference(t_vec3 *left, t_vec3 *right, t_options op)
{
	int	i;

	i = 0;
	if (op == O_CREATE)
		return (vec3_init_from_matrix(m_subtraction(left->raw_matrix, right->raw_matrix)));
	else if (op == O_REPLACE)
	{
		while (i < 3)
		{
			left->raw_matrix->m[i][0] -= right->raw_matrix->m[i][0];
			++i;
		}
		return (left);
	}
}

t_vec3	*vec3_addition(t_vec3 *left, t_vec3 *right, t_options op)
{
	int	i;

	i = 0;
	if (op == O_CREATE)
		return (vec3_init_from_matrix(m_addition(left->raw_matrix, right->raw_matrix)));
	else if (op == O_REPLACE)
	{
		while (i < 3)
		{
			left->raw_matrix->m[i][0] += right->raw_matrix->m[i][0];
			++i;
		}
		return (left);
	}
	
}

t_vec3	*vec3_scalar_multi(t_vec3 *vctr, double value, t_options op)
{
	int	i;

	i = 0;
	if (op == O_CREATE)
		return (vec3_init_from_matrix(m_scalar_multi(vctr->raw_matrix, value)));
	else if (op == O_REPLACE)
	{
		while (i < 3)
		{
			vctr->raw_matrix->m[i][0] *= value;
			++i;
		}
		return (vctr);
	}
}

// my bad, normalize isnt unit vector :P
t_vec3	*vec3_normalize(t_vec3 *vctr, t_options op)
{
	double	mag;

	mag = vec3_magnitude(vctr);
	if (op == O_CREATE)
		return (vec3_scalar_multi(vctr, 1/mag, O_CREATE));
	else if (op == O_REPLACE)
		return (vec3_scalar_multi(vctr, 1/mag, O_REPLACE));
}

// A x B = |A| |B| sin theta ^n
// ^n is the unit vector perpendicular to the both vectors
// ONLY WORKS FOR VEC3
// THERE IS NO CROSSPRODUCT FOR A 4-D VECTOR
t_vec3	*vec3_crossproduct(t_vec3 *left, t_vec3 *right, t_options op)
{
	int			i;
	t_matrix_type	stuff[3];
	t_matrix_type	*left_val;
	t_matrix_type	*right_val;

	left_val = vec3_get_val(left);
	right_val = vec3_get_val(right);
	stuff[0] = (left_val[1] * right_val[2]) - (left_val[2] * right_val[1]);
	stuff[1] = -1 * ((left_val[0] * right_val[2]) - (left_val[2] * right_val[0]));
	stuff[2] = (left_val[0] * right_val[1]) - (left_val[1] * right_val[0]);
	free(left_val);
	free(right_val);

	if (op == O_CREATE)
		return (vec3_init_from_array(stuff));
	else if (op == O_REPLACE)
	{
		i = 0;
		while (i < 3)
		{
			left->raw_matrix->m[i][0] = stuff[i];
			++i;
		}
		return (left);
	}
}

t_vec3	*vec3_negate(t_vec3 *vctr)
{
	vctr->raw_matrix->m[0][0] = -vctr->raw_matrix->m[0][0];
	vctr->raw_matrix->m[1][0] = -vctr->raw_matrix->m[1][0];
	vctr->raw_matrix->m[2][0] = -vctr->raw_matrix->m[2][0];
	return (vctr);
}

int	vec3_isequal(t_vec3 *a, t_vec3 *b)
{
	return 
	(a->raw_matrix->m[0][0] == b->raw_matrix->m[0][0] &&
	a->raw_matrix->m[1][0] == b->raw_matrix->m[1][0] &&
	a->raw_matrix->m[2][0] == b->raw_matrix->m[2][0]);
}