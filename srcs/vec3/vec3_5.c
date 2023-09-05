/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 13:45:38 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:37:48 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vec3.h"

// psa, normalize isnt unit vector
t_vec3	*vec3_normalize(t_vec3 *vctr, t_options op)
{
	double	mag;

	mag = vec3_magnitude(vctr);
	if (op == O_CREATE)
		return (vec3_scalar_multi(vctr, 1 / mag, O_CREATE));
	else if (op == O_REPLACE)
		return (vec3_scalar_multi(vctr, 1 / mag, O_REPLACE));
	return (NULL);
}

// projecting vector a on vector b
t_vec3	*vec3_projection(t_vec3 *a, t_vec3 *b, t_options op)
{
	double		project_mag;
	t_vec3		*norm_b;
	t_vec3		*ret;

	ret = NULL;
	project_mag = vec3_dotproduct(a, b) / vec3_magnitude(b);
	norm_b = vec3_normalize(b, O_CREATE);
	if (op == O_CREATE)
		ret = vec3_scalar_multi(norm_b, project_mag, O_CREATE);
	else if (op == O_REPLACE)
		ret = vec3_scalar_multi(norm_b, project_mag, O_REPLACE);
	vec3_free(&norm_b);
	return (ret);
}

// A x B = |A| |B| sin theta ^n
// ^n is the unit vector perpendicular to the both vectors
// no cross product for vec4
t_vec3	*vec3_crossproduct(t_vec3 *left, t_vec3 *right, t_options op)
{
	int				i;
	t_matrix_type	stuff[3];
	t_matrix_type	*left_val;
	t_matrix_type	*right_val;

	i = -1;
	left_val = vec3_get_val(left);
	right_val = vec3_get_val(right);
	stuff[0] = (left_val[1] * right_val[2]) - (left_val[2] * right_val[1]);
	stuff[1] = -1 * ((left_val[0] * right_val[2])
			- (left_val[2] * right_val[0]));
	stuff[2] = (left_val[0] * right_val[1]) - (left_val[1] * right_val[0]);
	free(left_val);
	free(right_val);
	if (op == O_CREATE)
		return (vec3_init_from_array(stuff));
	else if (op == O_REPLACE)
	{
		while (++i < 3)
			left->raw_matrix->m[i][0] = stuff[i];
		return (left);
	}
	return (NULL);
}
