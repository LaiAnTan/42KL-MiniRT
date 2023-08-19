/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:42:05 by tlai-an           #+#    #+#             */
/*   Updated: 2023/08/19 20:10:23 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	apply_matrix(t_vec3 **to, t_matrix *trans_mtrx)
{
	t_vec4	*to_vec4;
	t_vec4	*res;
	t_vec3	*ret;

	to_vec4 = vec3_to_vec4((*to));
	res = vec4_init_from_matrix(m_multiplication(trans_mtrx,
				to_vec4->raw_matrix));
	ret = vec4_to_vec3(res);
	vec4_free(&to_vec4);
	vec4_free(&res);
	vec3_free(to);
	(*to) = ret;
}

// need a specific center bottom getter
// (since the cylinder axis isnt constantly 0,0,1)
t_vec3	*cyn_get_centre_bottom(t_vec3 *center, t_vec3 *vec_axis, double diff)
{
	t_vec3	*ret;
	t_vec3	*to_min;

	to_min = vec3_scalar_multi(vec_axis, diff, O_CREATE);
	ret = vec3_difference(center, to_min, O_CREATE);
	vec3_free(&to_min);
	return (ret);
}

void	transform_plane(t_plane *pl, t_camera *mrtx)
{
	apply_matrix(&(pl->pl_vec_normal), mrtx->orr_matrix);
	pl->pl_vec_normal = vec3_normalize(pl->pl_vec_normal, O_REPLACE);
}

void	transform_cylinder(t_vec3 *center, t_cylinder *cy, t_camera *mtrx)
{
	apply_matrix(&(cy->cy_vec_axis), mtrx->orr_matrix);
	vec3_normalize(cy->cy_vec_axis, O_REPLACE);
	cy->cy_bottom = cyn_get_centre_bottom(center, cy->cy_vec_axis,
			cy->cy_height / 2);
}

void	transform_cone(t_vec3 *center, t_cone *cn, t_camera *mtrx)
{
	apply_matrix(&(cn->cn_vec_axis), mtrx->orr_matrix);
	vec3_normalize(cn->cn_vec_axis, O_REPLACE);
	cn->cn_bottom = cyn_get_centre_bottom(center, cn->cn_vec_axis,
			cn->cn_height);
}

// known errors -> if the cam is at {0,1,0} or {0,-1,0} 
// (parallel to the UP vector) everything breaks
// solution -> hardcode
void	change_to_view_port(t_scene *scn)
{
	t_light		*l;
	t_object	*o;
	t_camera	*cam;

	cam = scn->sc_cameras;
	cam_view_matrix(cam);
	apply_matrix(&cam->cam_coords, cam->view_matrix);
	apply_matrix(&cam->cam_vec_orient, cam->orr_matrix);
	vec3_normalize(cam->cam_vec_orient, O_REPLACE);
	l = scn->sc_lights;
	while (l)
	{
		apply_matrix(&(l->l_coords), cam->view_matrix);
		l = l->next;
	}
	o = scn->sc_objs;
	while (o)
	{
		apply_matrix(&(o->ob_coords), cam->view_matrix);
		vec3_print(o->ob_coords);
		if (o->ob_type == PLANE)
			transform_plane(o->ob_planes, cam);
		else if (o->ob_type == CYLINDER)
			transform_cylinder(o->ob_coords, o->ob_cylinders, cam);
		else if (o->ob_type == CONE)
			transform_cone(o->ob_coords, o->ob_cones, cam);
		o = o->next;
	}
}
