# include "../headers/minirt.h"

/*
shits depreciated wooo

*/

// function that generates a 4x4 perspective projection matrix
t_matrix	*perspective(float fov, float aspect_ratio, float z_near_clip, float z_far_clip)
{
	t_matrix	*res;

	res = m_init_empty(4, 4);
	res->m[0][0] = aspect_ratio * (1 / tan(fov / 2));
	res->m[1][1] = 1 / tan(fov / 2);
	res->m[2][2] = z_far_clip / (z_far_clip - z_near_clip);
	res->m[2][3] = (-z_far_clip * z_near_clip) / (z_far_clip - z_near_clip);
	res->m[3][2] = 1;
	return (res);
}

t_vec4	*apply_projection(t_matrix *projection_matrix, t_vec4 *vector)
{
	t_vec4	*res;

	// apply projection matrix
	res = vec3_init_from_matrix(m_multiplication(projection_matrix, vector->raw_matrix));

	if (res->raw_matrix->m[3][0] != 0.0f) // perspective divide
	{
		res->raw_matrix->m[0][0] /= res->raw_matrix->m[3][0];
		res->raw_matrix->m[1][0] /= res->raw_matrix->m[3][0];
		res->raw_matrix->m[2][0] /= res->raw_matrix->m[3][0];
	}
	return (res);
}