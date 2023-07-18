# include "../headers/minirt.h"

double	intersect_plane(t_ray *ray, t_object *o)
{
	t_vec3	*modified_ray_pos;

	modified_ray_pos = vec3_difference(ray->pos_vector, o->ob_coords, O_CREATE);

	// ipad notes... again
	// a = -k(b)
	double	values[2];
	double	k;

	values[0] = vec3_dotproduct(modified_ray_pos, o->ob_planes->pl_vec_normal);
	values[1] = vec3_dotproduct(ray->dir_vector, o->ob_planes->pl_vec_normal);

	k = -(values[0] / values[1]);
	vec3_free(&modified_ray_pos);
	if (k < 0)
		return (ERROR);
	return (k);
}