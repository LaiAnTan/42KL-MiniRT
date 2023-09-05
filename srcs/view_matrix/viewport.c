/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:42:05 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/03 21:57:04 by tlai-an          ###   ########.fr       */
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

void	rotate_objects(t_object *o, t_camera *cam)
{
	apply_matrix(&(o->ob_coords), cam->view_matrix);
	if (o->ob_type == PLANE)
		transform_plane(o->ob_planes, cam);
	else if (o->ob_type == CYLINDER)
		transform_cylinder(o->ob_coords, o->ob_cylinders, cam);
	else if (o->ob_type == CONE)
		transform_cone(o->ob_coords, o->ob_cones, cam);
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
		rotate_objects(o, cam);
		o = o->next;
	}
}
