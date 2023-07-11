#include "../headers/minirt.h"

void	apply_matrix(t_vec3 **to, t_matrix *trans_mtrx)
{
	t_vec4	*to_vec4;
	t_vec4	*res;
	t_vec3	*ret;

	to_vec4 = vec3_to_vec4((*to));
	res =  vec4_init_from_matrix(m_multiplication(trans_mtrx, to_vec4->raw_matrix));
	ret = vec4_to_vec3(res);
	vec4_free(&to_vec4);
	vec4_free(&res);
	vec3_free(to);
	(*to) = ret;
}

// known errors -> if the cam is at {0,1,0} or {0,-1,0} (parallel to the UP vector) everything breaks
// solution -> idk hardcode :D
void	change_to_view_port(t_scene *scn)
{
	// get view matrix and orientation matrix
	t_camera	*cam;

	cam = scn->sc_cameras;
	cam_view_matrix(cam);

	printf("cam matrix = \n");
	m_print_matrix(cam->view_matrix);

	// apply on camera
	apply_matrix(&cam->cam_coords, cam->view_matrix);

	// apply on all lights
	t_light		*l;

	l = scn->sc_lights;

	while (l)
	{
		apply_matrix(&(l->l_coords), cam->view_matrix);
		l = l->next;
	}

	// apply on all objects
	t_object	*o;

	o = scn->sc_objs;
	while (o)
	{
		apply_matrix(&(o->ob_coords), cam->view_matrix);
		vec3_print(o->ob_coords);
		if (o->ob_type == PLANE)
		{
			apply_matrix(&(o->ob_planes->pl_vec_normal), cam->orr_matrix);
			o->ob_planes->pl_vec_normal = vec3_normalize(o->ob_planes->pl_vec_normal);
		}
		o = o->next;
	}
}