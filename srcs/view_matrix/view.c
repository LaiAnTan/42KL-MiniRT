/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:42:11 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:03:12 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

// rotation matrix
t_matrix	*construct_rotation(t_vec3 *right, t_vec3 *true_up, t_vec3 *forward)
{
	t_matrix	*rotation;

	rotation = m_init_empty(4, 4);
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
	return (rotation);
}

static t_matrix	*construct_translation(t_vec3 *position)
{
	t_matrix	*translation;

	translation = m_init_identity(4, 4);
	translation->m[0][3] = -position->raw_matrix->m[0][0];
	translation->m[1][3] = -position->raw_matrix->m[1][0];
	translation->m[2][3] = -position->raw_matrix->m[2][0];
	return (translation);
}

t_vec3	*get_right(t_vec3 *forward, t_vec3 *up)
{
	t_matrix_type	y_val;

	y_val = forward->raw_matrix->m[1][0];
	if (y_val == 1)
		return (vec3_init(1, 0, 0));
	else if (y_val == -1)
		return (vec3_init(-1, 0, 0));
	else
		return (vec3_crossproduct(forward, up, O_CREATE));
}

//	camera position = cam->cam_coords;
//	camera forward direction = cam->cam_vec_orient;
void	cam_view_matrix(t_camera *cam)
{
	t_vec3		*up;
	t_vec3		*right;
	t_vec3		*true_up;
	t_matrix	*translation;

	up = vec3_init(0, 1, 0);
	right = get_right(cam->cam_vec_orient, up);
	true_up = vec3_crossproduct(right, cam->cam_vec_orient, O_CREATE);
	cam->orr_matrix = construct_rotation(right, true_up, cam->cam_vec_orient);
	translation = construct_translation(cam->cam_coords);
	cam->view_matrix = m_multiplication(cam->orr_matrix, translation);
	vec3_free(&up);
	vec3_free(&right);
	vec3_free(&true_up);
	free_matrix(&translation);
}

// gosh i love depreciating functions that i wrote
// rotation is 3x3 top left of 4x4 view matrix
// t_matrix	*get_rotation_inverse(t_matrix *transform)
// {
// 	int			i;
// 	int			j;
// 	t_matrix	*rotation;
// 	t_matrix	*mat3_rotation_inverse;
// 	t_matrix	*mat4_rotation_inverse;

// 	rotation = m_init_empty(3, 3);
// 	i = -1;
// 	j = -1;
// 	while (++i < 3)
// 	{
// 		while (++j < 3)
// 			rotation->m[i][j] = transform->m[i][j];
// 		j = -1;
// 	}
// 	mat3_rotation_inverse = m_transpose(rotation);
// 	mat4_rotation_inverse = m_init_identity(4, 4);
// 	i = -1;
// 	j = -1;
// 	while (++i < 3)
// 	{
// 		while (++j < 3)
// 			mat4_rotation_inverse->m[i][j] = mat3_rotation_inverse->m[i][j];
// 		j = -1;
// 	}
// 	return (mat4_rotation_inverse);
//}

// t_matrix	*get_translation_inverse(t_matrix *transform)
// {
// 	t_matrix	*translation_inverse;

// 	translation_inverse = m_init_identity(4, 4);
// 	translation_inverse->m[0][3] = -transform->m[0][3];
// 	translation_inverse->m[1][3] = -transform->m[1][3];
// 	translation_inverse->m[2][3] = -transform->m[2][3];
// 	return (translation_inverse);
// }

// t_matrix	*get_inverse_transform(t_matrix *transform)
// {
// 	t_matrix	*rotation_inverse;
// 	t_matrix	*translation_inverse;
// 	t_matrix	*res;

// 	rotation_inverse = get_rotation_inverse(transform);
// 	translation_inverse = get_translation_inverse(transform);
// 	res = m_multiplication(translation_inverse, rotation_inverse);
// 	free_matrix(&rotation_inverse);
// 	free_matrix(&translation_inverse);
// 	return (res);
// }
