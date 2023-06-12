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

// returns a 4x4 model to world matrix for a cylinder (no scaling because not orthogonal = no inverse)
t_matrix	*get_model_matrix(t_cylinder *cylinder)
{
	t_matrix	*translation;
	t_matrix	*rotation;
	t_matrix	*res;

	rotation = construct_model_rotation(cylinder);
	translation = construct_model_translation(cylinder);
	res = m_multiplication(rotation, translation);

	free_matrix(&translation);
	free_matrix(&rotation);
	return (res);
}