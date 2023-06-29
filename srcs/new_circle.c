# include "../headers/minirt.h"

// old circle is cringe and gay and slow
// will (attempt) to make a faster way to count

// see we dont really need 2 k values, only one
// the equation way also used sqrt, which is gay and slow
// if only there is a way to calculate 1 k value

// return k value btw
double	intersect_circle(t_ray	*ray, t_object *o)
{
	t_vec3	*modified_ray_pos;
	t_vec3	*zeroed_pos;

	modified_ray_pos = vec3_difference(ray->pos_vector, o->ob_coords);
	zeroed_pos = vec3_difference(o->ob_coords, o->ob_coords);

	
}
