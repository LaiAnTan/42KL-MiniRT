#include "../headers/minirt.h"


// rotation matrix
t_matrix *construct_rotation(t_vec3 *right, t_vec3 *true_up, t_vec3 *forward)
{
	t_matrix *rotation;

	rotation = m_init_empty(4, 4);

	// rotation->m[0][0] = right->raw_matrix->m[0][0]; 
	// rotation->m[1][0] = right->raw_matrix->m[1][0];
	// rotation->m[2][0] = right->raw_matrix->m[2][0];

	// rotation->m[0][1] = true_up->raw_matrix->m[0][0];
	// rotation->m[1][1] = true_up->raw_matrix->m[1][0];
	// rotation->m[2][1] = true_up->raw_matrix->m[2][0];

	// rotation->m[0][2] = -forward->raw_matrix->m[0][0];
	// rotation->m[1][2] = -forward->raw_matrix->m[1][0];
	// rotation->m[2][2] = -forward->raw_matrix->m[2][0];

	rotation->m[0][0] = right->raw_matrix->m[0][0]; 
	rotation->m[0][1] = right->raw_matrix->m[1][0];
	rotation->m[0][2] = right->raw_matrix->m[2][0];

	rotation->m[1][0] = true_up->raw_matrix->m[0][0];
	rotation->m[1][1] = true_up->raw_matrix->m[1][0];
	rotation->m[1][2] = true_up->raw_matrix->m[2][0];

	rotation->m[2][0] = -forward->raw_matrix->m[0][0];
	rotation->m[2][1] = -forward->raw_matrix->m[1][0];
	rotation->m[2][2] = -forward->raw_matrix->m[2][0];

	rotation->m[3][3] = 1;

	printf("rotation = \n");
	m_print_matrix(rotation);
	return (rotation);
}

static t_matrix *construct_translation(t_vec3 *position)
{
	t_matrix *translation = m_init_identity(4, 4);

	translation->m[0][3] = -position->raw_matrix->m[0][0];
	translation->m[1][3] = -position->raw_matrix->m[1][0];
	translation->m[2][3] = -position->raw_matrix->m[2][0];

	printf("translation = \n");
	m_print_matrix(translation);
	return (translation);
}

// function that creates a 4x4 view matrix 
// t_matrix *get_view_matrix(t_vec3 *position, t_vec3 *forward, t_vec3 *up)
// {
// 	// t_vec3	*forward;
// 	t_vec3	*right;
// 	t_vec3	*true_up;

// 	t_matrix	*res;

// 	// find the forward vector, from cam to reference
// 	// forward = vec3_difference(reference, position);
// 	// forward = vec3_normalize(forward);
// 	printf("forward = \n");
// 	vec3_print(forward);
// 	right = vec3_crossproduct(forward, up);
// 	printf("right = \n");
// 	vec3_print(right);
// 	true_up = vec3_crossproduct(right, forward);
// 	printf("true up = \n");
// 	vec3_print(true_up);
// 	res = m_multiplication(construct_translation(position), construct_rotation(right, true_up, forward));
// 	// res = m_multiplication(construct_rotation(right, true_up, forward), construct_translation(position));

// 	// vec3_free(&forward);
// 	vec3_free(&right);
// 	vec3_free(&true_up);
// 	return (res);
// }

t_vec3	*get_right(t_vec3 *forward, t_vec3 *up)
{
    matrix_type	y_val;

    y_val = forward->raw_matrix->m[1][0];
    if (y_val == 1)
        return (vec3_init(1,0,0));
    else if (y_val == -1)
        return (vec3_init(-1,0,0));
    else
        return (vec3_crossproduct(forward, up));
}

// heres to not break anything
void	cam_view_matrix(t_camera *cam)
{
	t_vec3	*position;
	matrix_type	up_val[3] = {0,1,0};
	t_vec3	*up;
	t_vec3	*forward;
	t_vec3	*right;
	t_vec3	*true_up;
	t_matrix	*trans;

	position = cam->cam_coords;
	forward = cam->cam_vec_orient;
	up = vec3_init_from_array(up_val);

	printf("forward = \n");
	vec3_print(forward);

	right = get_right(forward, up);
	printf("right = \n");
	vec3_print(right);

	true_up = vec3_crossproduct(right, forward);
	printf("true up = \n");
	vec3_print(true_up);

	cam->orr_matrix = construct_rotation(right, true_up, forward);
	trans = construct_translation(position);
	cam->view_matrix = m_multiplication(trans, cam->orr_matrix);

	vec3_free(&up);
	vec3_free(&right);
	vec3_free(&true_up);
	free_matrix(&trans);
}

t_matrix	*get_rotation_inverse(t_matrix *transform)
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
			rotation->m[i][j] = transform->m[i][j];
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

t_matrix	*get_translation_inverse(t_matrix *transform)
{
	t_matrix	*translation_inverse;

	translation_inverse = m_init_identity(4, 4);

	translation_inverse->m[0][3] = -transform->m[0][3];
	translation_inverse->m[1][3] = -transform->m[1][3];
	translation_inverse->m[2][3] = -transform->m[2][3];

	return (translation_inverse);
}

t_matrix	*get_inverse_transform(t_matrix *transform)
{
	t_matrix	*rotation_inverse;
	t_matrix	*translation_inverse;
	t_matrix	*res;

	rotation_inverse = get_rotation_inverse(transform);
	translation_inverse = get_translation_inverse(transform);
	res = m_multiplication(translation_inverse, rotation_inverse);

	free_matrix(&rotation_inverse);
	free_matrix(&translation_inverse);

	return (res);
}