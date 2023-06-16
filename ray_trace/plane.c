#include "minirt.h"

// runs under the assumtion that the orientation is (0, 0, 1)
matrix_type	get_plane_intersect(matrix_type *point, matrix_type *normal)
{
	matrix_type	val;

	val = (-1 * ((normal[0] * point[0]) + (normal[1] * point[1]))) / normal[2];
	free(normal);
	return (val);
}

double	intersect_plane(t_ray *ray, t_objects *o)
{
	t_vector	*modified_ray_pos;
	t_vector	*zeroed_pos;

	modified_ray_pos = v_difference(ray->pos_vector, o->position);
	zeroed_pos = v_difference(o->position, o->position);

	// ipad notes... again
	// a = -k(b)
	double	values[2];
	double	k;

	values[0] = v_dotproduct(modified_ray_pos, o->plane->normal_vect);
	values[1] = v_dotproduct(ray->dir_vector, o->plane->normal_vect);

	k = -(values[0] / values[1]);
	free_vector(&modified_ray_pos);
	free_vector(&zeroed_pos);
	if (k < 0)
		return (ERROR);
	return (k);
}