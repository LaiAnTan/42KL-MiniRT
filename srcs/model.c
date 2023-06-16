# include "../headers/minirt.h"

static t_matrix	*construct_model_translation(t_cylinder *cylinder)
{
	t_matrix	*translation;

	translation = m_init_identity(4, 4);

	translation->m[0][3] = -cylinder->cy_coords->raw_matrix->m[0][0];
	translation->m[1][3] = -cylinder->cy_coords->raw_matrix->m[1][0];
	translation->m[2][3] = -cylinder->cy_coords->raw_matrix->m[2][0];

	printf("translation = \n");
	m_print_matrix(translation);
	return (translation);
}

static t_matrix	*construct_model_rotation(t_cylinder *cylinder)
{
	t_vec3		*model_orientation; // we are transforming default model orientation (0, 0, 1) to world orientation
	t_vec3		*world_orientation;
	t_matrix	*rotation;

	model_orientation = vec3_init(0, 0, 1);
	world_orientation = vec3_init(cylinder->cy_vec_axis->raw_matrix->m[0][0], cylinder->cy_vec_axis->raw_matrix->m[1][0], cylinder->cy_vec_axis->raw_matrix->m[2][0]);
	
	// no normalization because it is already normalized
	
	rotation = m_init_identity(4, 4);

	rotation->m[0][0] = vec3_dotproduct(model_orientation, world_orientation);
	rotation->m[0][1] = -vec3_magnitude(vec3_crossproduct(model_orientation, world_orientation));

	rotation->m[1][0] = vec3_magnitude(vec3_crossproduct(model_orientation, world_orientation));
	rotation->m[1][1] = vec3_dotproduct(model_orientation, world_orientation);

	vec3_free(&model_orientation);
	vec3_free(&world_orientation);

	printf("rotation = \n");
	m_print_matrix(rotation);
	return (rotation);
}

static t_matrix	*construct_model_rotation_2(t_cylinder *cylinder)
{
	t_vec3		*model_orientation; // we are transforming default model orientation (0, 0, 1) to world orientation
	t_vec3		*world_orientation;

	t_vec3		*v;
	double		c;

	t_matrix	*v_mat; //skew symmetric cross product matrix of v
	t_matrix	*rotation_mat3;
	t_matrix	*rotation_mat4;

	model_orientation = vec3_init(0, 0, 1);
	world_orientation = vec3_init(cylinder->cy_vec_axis->raw_matrix->m[0][0], cylinder->cy_vec_axis->raw_matrix->m[1][0], cylinder->cy_vec_axis->raw_matrix->m[2][0]);
	
	// no normalization because it is already normalized
	v = vec3_crossproduct(model_orientation, world_orientation);
	c = vec3_dotproduct(model_orientation, world_orientation);
	v_mat = m_init_empty(3, 3);
	rotation_mat3 = m_init_empty(3, 3);
	rotation_mat4 = m_init_identity(4, 4);

	v_mat->m[0][1] = -v->raw_matrix->m[2][0];
	v_mat->m[0][2] = v->raw_matrix->m[1][0];

	v_mat->m[1][0] = v->raw_matrix->m[2][0];
	v_mat->m[1][2] = -v->raw_matrix->m[0][0];

	v_mat->m[2][0] = -v->raw_matrix->m[2][0];
	v_mat->m[2][1] = v->raw_matrix->m[0][0];

	// R = I + [v] + [v]^2 * (1 / (1 + c))
	rotation_mat3 = m_addition(m_addition(m_init_identity(3, 3), v_mat), m_scalar_multi(m_multiplication(v_mat, v_mat), (1 / (1 + c))));

	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		while (j < 3)
		{
			rotation_mat4->m[i][j] = rotation_mat3->m[i][j];
			++j;
		}
		j = 0;
		++i;
	}

	vec3_free(&model_orientation);
	vec3_free(&world_orientation);

	printf("rotation = \n");
	m_print_matrix(rotation_mat4);
	return (rotation_mat4);
}

// returns a 4x4 model to world matrix for a cylinder (no scaling because not orthogonal = no inverse)
t_matrix	*get_model_matrix(t_cylinder *cylinder)
{
	t_matrix	*translation;
	t_matrix	*rotation;
	t_matrix	*res;

	rotation = construct_model_rotation_2(cylinder);
	translation = construct_model_translation(cylinder);
	res = m_multiplication(rotation, translation);

	free_matrix(&translation);
	free_matrix(&rotation);
	return (res);
}