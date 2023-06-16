# include "../headers/minirt.h"

// runs under the assumtion that the orientation is (0, 0, 1)
matrix_type	get_plane_intersect(matrix_type *point, matrix_type *normal)
{
	matrix_type	val;

	val = (-1 * ((normal[0] * point[0]) + (normal[1] * point[1]))) / normal[2];
	free(normal);
	return (val);
}

double	intersect_plane(t_ray *ray, t_object *o)
{
	t_vec3	*modified_ray_pos;
	t_vec3	*zeroed_pos;

	modified_ray_pos = v_difference(ray->pos_vector, o->ob_coords);
	zeroed_pos = v_difference(o->ob_coords, o->ob_coords);

	// ipad notes... again
	// a = -k(b)
	double	values[2];
	double	k;

	values[0] = v_dotproduct(modified_ray_pos, o->ob_planes->pl_vec_normal);
	values[1] = v_dotproduct(ray->dir_vector, o->ob_planes->pl_vec_normal);

	k = -(values[0] / values[1]);
	free_vector(&modified_ray_pos);
	free_vector(&zeroed_pos);
	if (k < 0)
		return (ERROR);
	return (k);
}