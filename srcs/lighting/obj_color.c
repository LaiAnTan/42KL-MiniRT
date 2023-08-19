

#include "../headers/lighting.h"

void	normalize_yourmother(double uv[2])
{
	double	cool_shit;

	cool_shit = sqrt((uv[0] * uv[0]) + (uv[1] * uv[1]));
	// printf("%.2f\n", cool_shit);
	uv[0] = uv[0] / cool_shit; 
	uv[1] = uv[1] / cool_shit;
}

void	calculate_uv_circle(t_ray *ray, t_object *o, double store[2])
{
	// x = 0, y = 0, z = 0
	t_vec3	*zeroed_please_kill_me;
	double	coord[3];

	zeroed_please_kill_me = vec3_difference(ray->pos_vector, o->ob_coords, O_CREATE);
	vec3_store_val(vec3_normalize(zeroed_please_kill_me, O_REPLACE), coord);
	vec3_free(&zeroed_please_kill_me);


	// wiki
	store[0] = 0.5 + (atan2(coord[2], coord[0]) / (2 * PI));
	store[1] = 0.5 + (asin(coord[1]) / (PI));

	store[0] = 0.25 - store[0];
	store[1] = 1 - store[1];

	// psa, this equation is pulled straight from my ass

	// store[0] = (1 / PI) * atan( sqrt((coord[2] * coord[2]) + (coord[1] * coord[1])) / coord[0] ) + 0.5; 
	// store[1] = (1 / PI) * atan( coord[1] / coord[2] ) + 0.5;

	// hacks
	// store[0] = 0.5 - store[0];
	// store[1] = 1 - store[1];

	// printf("(%f %f)\n", store[0], store[1]);
}

double	clamp(double first, double min, double max)
{
	if (first < min)
		return (min);
	if (first > max)
		return (max);
	return (first);
}

// only for sphere
t_vec3	*get_object_color(t_ray *ray, t_object *o)
{
	// im gonna regret this later, watch
	// u is 0, v is 1
	double	uv_coord[2];

	if (!o->has_texture)
	{
		return (vec3_dup(o->ob_rgb));
	}
	else
	{
		if (o->ob_type == CIRCLE)
		{
			calculate_uv_circle(ray, o, uv_coord);
			return (get_rgb(o->ob_texture, uv_coord[0], uv_coord[1]));
		}
	}
	return (NULL);
}