#include "../headers/minirt.h"

static t_matrix *construct_rotation(t_vec3 *right, t_vec3 *true_up, t_vec3 *forward)
{
	t_matrix *rotation;

	rotation = m_init_empty(4, 4);

	rotation->m[0][0] = right->raw_matrix->m[0][0]; 
	rotation->m[1][0] = right->raw_matrix->m[1][0];
	rotation->m[2][0] = right->raw_matrix->m[2][0];

	rotation->m[0][1] = true_up->raw_matrix->m[0][0];
	rotation->m[1][1] = true_up->raw_matrix->m[1][0];
	rotation->m[2][1] = true_up->raw_matrix->m[2][0];

	rotation->m[0][2] = -forward->raw_matrix->m[0][0];
	rotation->m[1][2] = -forward->raw_matrix->m[1][0];
	rotation->m[2][2] = -forward->raw_matrix->m[2][0];

	rotation->m[3][3] = 1;

	printf("rotation = \n");
	m_print_matrix(rotation);
	return (rotation);
}

static t_matrix *construct_translation(t_vec3 *position)
{
	t_matrix *translation = m_init_empty(4, 4);

	translation->m[0][0] = 1;
	translation->m[1][1] = 1;
	translation->m[2][2] = 1;
	translation->m[3][3] = 1;

	translation->m[0][3] = -position->raw_matrix->m[0][0];
	translation->m[1][3] = -position->raw_matrix->m[1][0];
	translation->m[2][3] = -position->raw_matrix->m[2][0];

	printf("translation = \n");
	m_print_matrix(translation);
	return (translation);
}

// function that creates a 4x4 view matrix 
t_matrix *get_view_1(t_vec3 *position, t_vec3 *orientation, t_vec3 *up)
{
	t_vec3	*forward;
	t_vec3	*right;
	t_vec3	*true_up;

	t_matrix	*res;

	forward = orientation;
	printf("forward = \n");
	vec3_print(forward);
	right = vec3_crossproduct(forward, up);
	printf("right = \n");
	vec3_print(right);
	true_up = vec3_crossproduct(right, forward);
	printf("true up = \n");
	vec3_print(true_up);
	res = m_multiplication(construct_rotation(right, true_up, forward), construct_translation(position));

	vec3_free(&forward);
	vec3_free(&right);
	vec3_free(&true_up);
	return (res);
}

t_matrix *get_view_2(t_vec3 *position, t_vec3 *direction, t_vec3 *up)
{
	t_vec3	*x;
	t_vec3	*y;
	t_vec3	*z;
	t_matrix	*res = m_init_empty(4, 4);

	z = direction;
	y = up;
	x = vec3_crossproduct(y, z);
	y = vec3_crossproduct(z, x);
	x = vec3_normalize(x);
	y = vec3_normalize(y);
	res->m[0][0] = x->raw_matrix->m[0][0];
	res->m[1][0] = x->raw_matrix->m[1][0];
	res->m[2][0] = x->raw_matrix->m[2][0];
	res->m[3][0] = -vec3_dotproduct(x, position);

	res->m[0][1] = y->raw_matrix->m[0][0];
	res->m[1][1] = y->raw_matrix->m[1][0];
	res->m[2][1] = y->raw_matrix->m[2][0];
	res->m[3][1] = -vec3_dotproduct(z, position);

	res->m[0][2] = z->raw_matrix->m[0][0];
	res->m[1][2] = z->raw_matrix->m[1][0];
	res->m[2][2] = z->raw_matrix->m[2][0];
	res->m[3][2] = -vec3_dotproduct(z, position);

	res->m[3][3] = 1.0f;

	vec3_free(&x);
	vec3_free(&y);
	vec3_free(&z);

	return (res);
}

t_matrix	*get_rotation_inverse(t_matrix *view)
{
	int			i;
	int			j;

	t_matrix	*rotation; //3x3 top left of 4x4 view matrix
	t_matrix	*mat3_rotation_inverse;
	t_matrix	*mat4_rotation_inverse;

	rotation = m_init_empty(3, 3);
	i = 0;
	j = 0;
	while (i < 3)
	{
		while (j < 3)
		{
			rotation->m[i][j] = view->m[i][j];
			++j;
		}
		j = 0;
		++i;
	}
	mat3_rotation_inverse = m_transpose(rotation);
	mat4_rotation_inverse = m_init_identity(4, 4);
	i = 0;
	j = 0;
	while (i < 3)
	{
		while (j < 3)
		{
			mat4_rotation_inverse->m[i][j] = mat3_rotation_inverse->m[i][j];
			++j;
		}
		j = 0;
		++i;
	}
	return (mat4_rotation_inverse);
}

t_matrix	*get_translation_inverse(t_matrix *view)
{
	t_matrix	*translation_inverse;

	translation_inverse = m_init_identity(4, 4);

	translation_inverse->m[0][3] = -view->m[0][3];
	translation_inverse->m[1][3] = -view->m[1][3];
	translation_inverse->m[2][3] = -view->m[2][3];

	return (translation_inverse);
}

t_matrix	*get_inverse_view(t_matrix *view)
{
	t_matrix	*rotation_inverse;
	t_matrix	*translation_inverse;

	rotation_inverse = get_rotation_inverse(view);
	translation_inverse = get_translation_inverse(view);

	return (m_multiplication(translation_inverse, rotation_inverse));
}