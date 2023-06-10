#include "../headers/minirt.h"

t_matrix *construct_rotation(t_vec3 *s, t_vec3 *u, t_vec3 *direction)
{
	t_matrix *rotation;

	rotation = init_empty_matrix(4, 4);

	rotation->stuff[0][0] = s->raw_matrix->stuff[0][0]; 
	rotation->stuff[1][0] = s->raw_matrix->stuff[1][0];
	rotation->stuff[2][0] = s->raw_matrix->stuff[2][0];

	rotation->stuff[0][1] = u->raw_matrix->stuff[0][0];
	rotation->stuff[1][1] = u->raw_matrix->stuff[1][0];
	rotation->stuff[2][1] = u->raw_matrix->stuff[2][0];

	rotation->stuff[0][2] = -direction->raw_matrix->stuff[0][0];
	rotation->stuff[1][2] = -direction->raw_matrix->stuff[1][0];
	rotation->stuff[2][2] = -direction->raw_matrix->stuff[2][0];

	rotation->stuff[3][3] = 1;

	return (rotation);
}

t_matrix *construct_translation(t_vec3 *position)
{
	t_matrix *translation = init_empty_matrix(4, 4);

	translation->stuff[0][0] = 1;
	translation->stuff[1][1] = 1;
	translation->stuff[2][2] = 1;
	translation->stuff[3][3] = 1;

	translation->stuff[3][0] = -position->raw_matrix->stuff[0][0];
	translation->stuff[3][1] = -position->raw_matrix->stuff[1][0];
	translation->stuff[3][2] = -position->raw_matrix->stuff[2][0];

	return (translation);
}

// function that creates a 4x4 view matrix 
t_matrix *look_at(t_vec3 *position, t_vec3 *direction, t_vec3 *up)
{
	t_vec3	*s;
	t_vec3	*u;
	t_matrix *rotation;
	t_matrix *translation;

	s = v_crossproduct(direction, up);
	u = v_crossproduct(v_get_unit_v(s), direction);
	rotation = construct_rotation(s, u, direction);
	translation = construct_translation(position);

	return (m_multiplication(rotation, translation));
}