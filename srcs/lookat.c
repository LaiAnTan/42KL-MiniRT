#include "../headers/minirt.h"

t_matrix *construct_rotation(t_vec3 *s, t_vec3 *u, t_vec3 *direction)
{
	t_matrix *rotation;

	rotation = init_empty_matrix(4, 4);

	rotation->m[0][0] = s->raw_matrix->m[0][0]; 
	rotation->m[1][0] = s->raw_matrix->m[1][0];
	rotation->m[2][0] = s->raw_matrix->m[2][0];

	rotation->m[0][1] = u->raw_matrix->m[0][0];
	rotation->m[1][1] = u->raw_matrix->m[1][0];
	rotation->m[2][1] = u->raw_matrix->m[2][0];

	rotation->m[0][2] = -direction->raw_matrix->m[0][0];
	rotation->m[1][2] = -direction->raw_matrix->m[1][0];
	rotation->m[2][2] = -direction->raw_matrix->m[2][0];

	rotation->m[3][3] = 1;

	return (rotation);
}

t_matrix *construct_translation(t_vec3 *position)
{
	t_matrix *translation = init_empty_matrix(4, 4);

	translation->m[0][0] = 1;
	translation->m[1][1] = 1;
	translation->m[2][2] = 1;
	translation->m[3][3] = 1;

	translation->m[3][0] = -position->raw_matrix->m[0][0];
	translation->m[3][1] = -position->raw_matrix->m[1][0];
	translation->m[3][2] = -position->raw_matrix->m[2][0];

	return (translation);
}

// function that creates a 4x4 view matrix 
t_matrix *look_at_1(t_vec3 *position, t_vec3 *direction, t_vec3 *up)
{
	t_vec3	*s;
	t_vec3	*u;
	t_matrix *rotation;
	t_matrix *translation;
	t_matrix	*res;

	s = vec3_crossproduct(direction, up);
	u = vec3_crossproduct(vec3_normalize(s), direction);
	rotation = construct_rotation(s, u, direction);
	translation = construct_translation(position);
	res = m_multiplication(rotation, translation);

	free_vector(&s);
	free_vector(&u);
	free_matrix(&rotation);
	free_matrix(&translation);
	return (res);
}

t_matrix *look_at_2(t_vec3 *position, t_vec3 *direction, t_vec3 *up)
{
	t_vec3	*x;
	t_vec3	*y;
	t_vec3	*z;
	t_matrix	*res = init_empty_matrix(4, 4);

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

	free_vector(&x);
	free_vector(&y);
	free_vector(&z);

	return (res);
}