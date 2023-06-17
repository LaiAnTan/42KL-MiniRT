# include "../headers/minirt.h"

double	intersect_plane(t_ray *ray, t_object *o)
{
	t_vec3	*modified_ray_pos;
	t_vec3	*zeroed_pos;

	modified_ray_pos = vec3_difference(ray->pos_vector, o->ob_coords);
	zeroed_pos = vec3_difference(o->ob_coords, o->ob_coords);

	// ipad notes... again
	// a = -k(b)
	double	values[2];
	double	k;

	values[0] = vec3_dotproduct(modified_ray_pos, o->ob_planes->pl_vec_normal);
	values[1] = vec3_dotproduct(ray->dir_vector, o->ob_planes->pl_vec_normal);

	k = -(values[0] / values[1]);
	vec3_free(&modified_ray_pos);
	vec3_free(&zeroed_pos);
	if (k < 0)
		return (ERROR);
	return (k);
}